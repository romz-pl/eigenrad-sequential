#include <fstream>
#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <print>
#include <chrono>
#include "eigprob.h"
#include "lobatto.h"
#include "gauss.h"

const double EigProb::m_gamma = 0.5;

//
// Constructor
//
EigProb::EigProb(size_t ell,
                 double rc,
                 size_t eigNode,
                 size_t eigDeg,
                 const Fun1D& g,
                 size_t eigNo,
                 double absMaxCoef,
                 double abstol,
                 bool create_log_file,
                 const std::string& out_directory,
                 size_t out_points )
    : m_ell( ell )
    , m_rc( rc )
    , m_eigNode( eigNode )
    , m_eigDeg( eigDeg )
    , m_g( g )
    , m_eigNo( eigNo )
    , m_absMaxCoef( absMaxCoef )
    , m_abstol( abstol )
    , m_create_log_file( create_log_file )
    , m_out_directory( out_directory )
    , m_out_points( out_points )

{
    if( m_create_log_file )
    {
        const std::string path = out_directory + "/" + "eigenrad.log";
        m_log = std::fopen(path.c_str(), "w");
        if( m_log == nullptr )
        {
            throw std::runtime_error( "Cannot open file: " + path );
        }
        write_intro();
        std::print(m_log, "{}\n\n", get_now_as_string());
    }

    m_mesh.GenLin( 0, m_rc, m_eigNode, m_eigDeg );
    m_mesh.CreateCnnt( BndrType_Dir, BndrType_Dir );
}

EigProb::~EigProb()
{
    if( m_create_log_file )
    {
        assert( m_log );
        std::print( m_log, "{}\n\n", get_now_as_string());
        std::print( m_log, "=== END OF LOG FILE ===\n" );
        std::fclose( m_log );
    }
}

std::string EigProb::get_now_as_string()
{
    const auto now = std::chrono::floor<std::chrono::seconds>( std::chrono::system_clock::now() );
    const auto local = std::chrono::zoned_time{
        std::chrono::current_zone(), now
    };

    return std::format("\nDATETIME: {:%d %b %Y %H:%M:%S}", local);
}


//
// Solves the eigenproblem, WITHOUT adaptive procedure
//
void EigProb::Solve( )
{
    Malloc();
    Assemble( );
    m_s.EigenGen(m_eigNo, m_abstol, m_w, m_z, m_o);
}

void EigProb::append_step_info( size_t step )
{
    step_info si;
    si.m_step = step;
    si.m_dofs = GetDofs();
    si.m_rmax = m_mesh.XBack();

    for(size_t eig = 0; eig < m_eigNo; eig++ )
    {
        si.m_eigenvalues.push_back( GetEigVal(eig) );
    }
    m_step_info.push_back( si );
}


//
// Solve the eigenproblem adatively
//
void EigProb::SolveAdapt( )
{
    std::vector< EltInfo > eltInfo( m_eigNo );
    std::vector< size_t > eltToSplit;

    size_t step = 0;
    while( true )
    {
        Solve( );
        append_step_info( step );
        write_solution( step );
        MaxMinCoef( eltInfo );
        std::sort( eltInfo.begin(), eltInfo.end() );
        const auto newEnd = std::unique( eltInfo.begin(), eltInfo.end() );

        double maxCoef = 0;
        for( size_t i = 0; i < eltInfo.size(); ++i )
        {
            if( eltInfo[i].GetMaxMinCoef() > maxCoef )
                maxCoef = eltInfo[i].GetMaxMinCoef();
        }
        if( maxCoef < m_absMaxCoef )
            break;

        // The Elt was splitted

        eltToSplit.clear();
        for( auto ii = eltInfo.begin(); ii != newEnd; ++ii )
        {
            eltToSplit.push_back( ii->GetEltId() );
        }

        log_elements_to_split( eltToSplit );
        m_mesh.AddToMesh( eltToSplit );
        m_mesh.CreateCnnt( BndrType_Dir, BndrType_Dir );
        step++;
    }
}


//
// Allocates the required memory
//
void EigProb::Malloc()
{
    const size_t M = m_mesh.Dim( BndrType_Dir, BndrType_Dir );
    const size_t band = m_mesh.GetBand();

    m_s.Assign( M, band, 0, 0 );
    m_w.assign( M, 0 );
    m_z.Assign( M, M, 0 );
    m_o.Assign( M, band, 0, 0 );
}

//
// Assembling algorithm for eigenvalue problem
//
void EigProb::Assemble( )
{
    const size_t N = m_mesh.EltNo(); // Number of elements

    // Element loop
    for( size_t n = 0; n < N; n++ )
    {
        const Element& e = m_mesh.Elt( n );
        const size_t DofNo = e.DofNo();

        // Loop over basis functions
        for( size_t i = 0; i < DofNo; i++ )
        {
            const int ni = e.m_dof[ i ];
            if( ni < 0 )
                continue;

            const size_t psiI = e.PsiId( i );

            // Loop over basis functions
            for( size_t j = i; j < DofNo; j++ )
            {
                const size_t psiJ = e.PsiId( j );

                const int nj = e.m_dof[ j ];
                if( nj > -1 )
                {
                    m_s.Set( ni, nj ) += CalcS( e, psiI, psiJ );
                    m_o.Set( ni, nj ) += CalcK( e, psiI, psiJ );
                }
            }
        }
    }
}

//
// Returns the element (ni, nj) of the stiffness matrix element.
// The elements are read from precomputed array.
//
double EigProb::CalcS( const Element& e, size_t ni, size_t nj ) const
{
    const double v1 = m_gamma * Lobatto::GetS( ni, nj );
    double v0 = 0;

    for( size_t n = 0; n < Gauss::Size(); n++ )
    {
        const double s = Gauss::X( n );
        const double w = Gauss::W( n );
        const double r = e.X( s );
        v0 += w * Lobatto::Basis( ni, s ) * Lobatto::Basis( nj, s ) * GetPot( r );
    }

    const double jac = e.Jac();
    return v1 / jac + v0 * jac;
}

//
// For given $r$ it returns the value
//    g(r) + L*(L + 1)/(2 r^2)
//
double EigProb::GetPot( double r ) const
{
    assert( r > 0 );
    const double a = m_g.Get( r );
    const double b = m_ell * ( m_ell + 1 ) / ( 2 * r * r );
    return a + b;
}

//
// Returns the element $o[i][j]$ overlap matrix element
// The elements are read from precomputed array.
//
double EigProb::CalcK( const Element& e, size_t ni, size_t nj ) const
{
    return e.Jac() * Lobatto::GetK( ni, nj );
}


//
// Returns the value of $eig$ eigenfunction at point $r$
//
double EigProb::GetEigFun( size_t eig, double r ) const
{
    assert( eig < m_w.size() );
    assert( m_mesh.IsInRange( r ) );

    const size_t n = m_mesh.FindElt( r );
    const Element& e = m_mesh.Elt( n );

    // s - local variable for element "e"
    const double s = e.Xinv( r );

    // Sum over all basis function with support on the element $e$
    double val = 0;

    for( size_t i = 0; i < e.m_dof.size(); i++ )
    {
        const int mi = e.m_dof[ i ];
        if( mi < 0 )
            continue;

        const size_t psiI = e.PsiId( i );

        val += m_z.Get( mi, eig ) * Lobatto::Basis( psiI, s );
    }
    return val;
}




//
// Returns the value of the $eig$ eigenvalue
//
double EigProb::GetEigVal( size_t eig ) const
{
    assert( eig < m_w.size() );

    return m_w[ eig ];
}


//
// Finds the element with the largest coefficient contained in the minimal coefficients
// BUBBLE functins are considered only.
//
void EigProb::MaxMinCoef( std::vector< EltInfo >& eltInfo ) const
{
    const size_t eigNo = eltInfo.size();
    double minCoef;


    for( size_t i = 0; i < eigNo; i++ ) // For each eigenfunction
    {
        eltInfo[ i ].Set( 0, -1 ); // Inicjalizacja
        for( size_t n = 0; n < m_mesh.EltNo(); n++ ) // For each element
        {
            const Element& e = m_mesh.Elt( n );
            minCoef = DBL_MAX;

            for( size_t j = 1; j < e.DofNo() - 1; j++ ) // For each BUBBLE DOF at element
            {
                const int dof = e.m_dof[ j ];
                if( dof < 0 ) // Skip Dirichlet boundary conditions
                    continue;

                // Find the minimal coefficient for element "e"
                const double coef = fabs( m_z.Get( dof, i ) );
                if( coef < minCoef )
                    minCoef = coef;
            }

            // Set the largest coefficient for the smallest coefficients
            if( minCoef > eltInfo[ i ].GetMaxMinCoef() )
            {
                eltInfo[ i ].Set( minCoef, n );
            }
        }
    }
}


void EigProb::write_intro() const
{
    if( !m_create_log_file )
        return;

    std::print( m_log,
               "===============================================================================\n"
               " EEEEE I   GGG  EEEEE N   N RRRR   AAA  DDDD         Zbigniew Romanowski       \n"
               " E     I  G     E     NN  N R   R A   A D   D                                  \n"
               " EEE   I  G  GG EEE   N N N RRRR  AAAAA D   D        romz@wp.pl                \n"
               " E     I  G   G E     N  NN R  R  A   A D   D                                  \n"
               " EEEEE I   GGG  EEEEE N   N R   R A   A DDDD         https://github.com/romz-pl\n"
               "===============================================================================\n\n\n");
}

void EigProb::log_elements_to_split( const std::vector< size_t >& eltToSplit ) const
{
    if( !m_create_log_file )
        return;

    std::print( m_log, "\n----- ELEMENTS TO SPLIT -----\n" );
    for(const size_t e : eltToSplit)
    {
        std::print( m_log, "{}\n", e);
    }
}

void EigProb::write_step_eigenvalues() const
{
    const std::string path = m_out_directory + "/" + "eigenvalues.dat";
    FILE* out = std::fopen( path.c_str(), "w" );
    if( out == nullptr )
    {
        throw std::runtime_error( "Cannot open file: " + path );
    }

    std::print( out,
        "# Eigenvalues for each adaptive steps.\n"
        "# This is a format suitable for GNUplot.\n"
        "# Column 1: step\n"
        "# Column 2: dofs\n"
        "# Column 3: rmax\n"
        "# Column 4, 5,...: eigenvalues\n"
        );

    for( const auto& si : m_step_info )
    {
        std::print( out, "{} {} {:16.9E}", si.m_step, si.m_dofs, si.m_rmax );

        for( const auto v : si.m_eigenvalues )
            std::print( out, " {:16.9E}", v );

        std::print( out, "\n" );
    }

    std::fclose( out );
}

void EigProb::write_step_eigenvalues_convergence() const
{
    const std::string path = m_out_directory + "/" + "eigenvalues-convergence.dat";
    FILE* out = std::fopen( path.c_str(), "w" );
    if( out == nullptr )
    {
        throw std::runtime_error( "Cannot open file: " + path );
    }

    std::print( out,
       "# Data for each adaptive steps.\n"
       "# This is a format suitable for GNUplot.\n"
       "# Column 1: step\n"
       "# Column 2: dofs\n"
       "# Column 3: rmax\n"
       "# Column 4, 5,...: eigenvalues\n"
       );

    const step_info base = m_step_info.back();

    for( const auto& si : m_step_info )
    {
        std::print( out, "{} {} {:16.9E}", si.m_step, si.m_dofs, si.m_rmax );

        for( size_t i = 0; i < base.m_eigenvalues.size(); i++ )
        {
            const double v = si.m_eigenvalues[i] - base.m_eigenvalues[i];
            std::print( out, " {:16.9E}", v );
        }

        std::print( out, "\n" );
    }

    std::fclose( out );
}

void EigProb::write_all_eigenfunctions() const
{
    for( size_t eig = 0; eig < m_eigNo; eig++ )
    {
        std::string filename = std::format("n{}.dat", eig);
        const std::string path = m_out_directory + "/" + filename;
        // const std::filesystem::path path = std::filesystem::path{directory} / filename;
        write_eigenfunction( path, eig );
    }
}

//
// Writes eigen-function $eig$ to file
// Argument "pointNo" determines number of addtional points netween mesh nodes
// where the eigenfunction is stored.
//
void EigProb::write_eigenfunction( const std::string& path, size_t eig ) const
{
    std::ofstream out( path.c_str(), std::ios::out );
    if( !out )
    {
        throw std::invalid_argument( "Cannot open file for write. Path = " + path );
    }
    out << std::scientific;

    out << "# \n";
    out << "# Output from EIGENRAD program.\n";
    out << "# \n";
    out << "# Eigenfunction for specific electronic state.\n";
    out << "# The first column contains radius $r$ in bohr units.\n";
    out << "# The second column holds value of eginefunction.\n";
    out << "# \n";
    out << "# Use this file with gnuplot to create the plot.\n";
    out << "#\n";

    if( m_mesh.XNo() == 0 )
    {
        throw std::runtime_error( "Eigenfunction not calculated in function EigProb::WriteEigFun" );
    }
    assert( m_out_points > 0 );


    double r;
    for( size_t n = 0; n < m_mesh.XNo() - 1; n++ )
    {
        r = m_mesh.X( n );
        const double dr = ( m_mesh.X( n + 1 ) - m_mesh.X( n ) ) / m_out_points;
        for( size_t i = 0; i < m_out_points; i++ )
        {
            const double v = GetEigFun( eig, r );
            out << r << " " << v << " ";
            if(n == 0 && i == 0)
            {
                // linear extrapolation for r = 0
                // y(r) = a * r + b
                // y(0) = b
                //
                // Solve the set of two linear equations
                // y(w)   = y0 = a * w + b
                // y(2*w) = y1 = a * 2 * w + b
                //
                // a = (y1 - y0) / w
                // b = 2 * y0 - y1
                //
                //
                constexpr double w = 1E-4;
                const double y0 = GetEigFun( eig, w ) / w;
                const double y1 = GetEigFun( eig, 2 * w ) / ( 2 * w);
                const double b = 2 * y0 - y1;
                out << b;
            }
            else
            {
                out << v / r;
            }

            out << std::endl;
            r += dr;
        }
    }

    // The last point must be written (to avoid the rounding errors)
    r = m_mesh.XBack();
    out  << r << " " << GetEigFun( eig, r ) << std::endl;
}

//
// Write Lobbato coefficients into the file
//
void EigProb::write_coefficients( ) const
{
    if( !m_create_log_file )
        return;

    assert( m_log );


    // Element loop
    for( size_t n = 0; n < m_mesh.EltNo(); n++ )
    {
        std::print( m_log, "\n{} {:15.6E} {:15.6E}\n", n, m_mesh.X(n), m_mesh.X(n + 1));
        const Element& e = m_mesh.Elt( n );
        const size_t DofNo = e.DofNo();

        double max_coef = 0;

        for( size_t eig = 0; eig < m_eigNo; eig++ )
        {
            double min_coef = DBL_MAX;

            // Loop over basis functions
            for( size_t i = 0; i < DofNo; i++ )
            {
                const int ni = e.m_dof[ i ];
                if( ni < 0 )
                    continue;

                const double coef = m_z.Get(ni, eig);
                const double abs_coef = std::fabs(coef);
                if( abs_coef < min_coef )
                    min_coef = abs_coef;

                std::print( m_log, "{:15.6E} ", coef );
            }
            std::print( m_log, "| {:15.6E}\n", min_coef );

            if( max_coef < min_coef )
                max_coef = min_coef;
        }
        std::print( m_log, "max(min|c_i|) = {:15.6E}\n", max_coef );
    }
}

void EigProb::write_eigenvalues( size_t step ) const
{
    if( !m_create_log_file )
        return;

    std::print( m_log, "\n----- EIGENVALUES -----\n" );
    for(size_t eig = 0; eig < m_eigNo; eig++ )
    {
        std::print( m_log, "EIGENVALUE n={} {:16.9E}\n", eig, GetEigVal(eig) );
    }

    std::print( m_log, "\nALL_EIGENVALUES: | {} | {} | ", step, GetDofs());
    for(size_t eig = 0; eig < m_eigNo; eig++ )
    {
        std::print( m_log, " {:16.9E} |", GetEigVal(eig) );
    }
    std::print( m_log, "\n");
}

void EigProb::write_solution( size_t step ) const
{
    if( !m_create_log_file )
        return;

    std::print( m_log, "\n\n========== ADAPTIVE STEP {} ==========\n", step );
    std::print( m_log, "Number of elements: {}\n", m_mesh.EltNo() );
    std::print( m_log, "Degrees of freedom: {}\n", GetDofs() );
    std::print( m_log, "Domain: [0, {:15.9E}]\n", m_mesh.XBack());

    write_coefficients();
    write_eigenvalues( step );

}