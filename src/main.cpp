#include <iostream>
#include "eigprob.h"
#include "gauss.h"
#include "lobatto.h"
#include "paramdb.h"
#include "potential_coulomb.h"

static void Intro(FILE* out);


int main(int argc, char* argv[])
{
    Intro(stdout);

    // argc = 2;
    // argv[ 1 ] = "/home/romz/code/eigenrad-sequential/results/aaa.inp";


    if(argc != 2)
    {
        printf("Usage: eigenrad <input_file>\n\n");
        return 1;
    }

    try
    {
        Lobatto m_lobatto;
        Gauss m_gauss;

        ParamDb db( argv[ 1 ] );
        potential_coulomb pot;

        const size_t ell = ParamDb::GetSize_t( "Solver_Ell" );
        const size_t eigNo = ParamDb::GetSize_t( "Solver_EigNo" );
        const double rc      = ParamDb::GetDouble( "Atom_Rc" );
        const size_t eigNode = ParamDb::GetSize_t( "Solver_EigNode" );
        const size_t eigDeg  = ParamDb::GetSize_t( "Solver_EigDeg" );
        const double abstol = ParamDb::GetDouble( "Solver_EigAbsTol" );
        const double absMaxCoef = ParamDb::GetDouble( "Solver_EigAbsMaxCoef" );

        EigProb eigProb( ell, rc, eigNode, eigDeg );
        eigProb.SolveAdapt( pot, eigNo, absMaxCoef, abstol );

        for(size_t eig = 0; eig < eigNo; eig++ )
            std::cout << eigProb.GetEigVal(eig) << "\n";


        printf("\n\n********** CALCULATIONS FINISHED SUCCESSFULLY! **********\n\n\n");
        return 0;
    }
    catch( std::exception& e )
    {
        printf("\n\nERROR! %s\n\n\n", e.what());
        return 1;
    }
    catch( ... )
    {
        printf( "Unexpected error!\n\n" );
        return 1;
    }


    std::cout << "EIGENRAD\n";
    return 0;
}

void Intro(FILE* out)
{
    fprintf(out,
        "===============================================================================\n"
        " EEEEE I   GGG  EEEEE N   N RRRR   AAA  DDDD         Zbigniew Romanowski       \n"
        " E     I  G     E     NN  N R   R A   A D   D                                  \n"
        " EEE   I  G  GG EEE   N N N RRRR  AAAAA D   D        romz@wp.pl                \n"
        " E     I  G   G E     N  NN R  R  A   A D   D                                  \n"
        " EEEEE I   GGG  EEEEE N   N R   R A   A DDDD         https://github.com/romz-pl\n"
        "===============================================================================\n\n\n");
}


