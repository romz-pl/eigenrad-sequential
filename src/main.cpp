#include <iostream>
// #include <filesystem>
#include <format>
#include <print>
#include "create_potential.h"
#include "eigprob.h"
#include "paramdb.h"

static void Intro(FILE* out);


int main(int argc, char* argv[])
{
    Intro(stdout);

    if(argc != 2)
    {
        printf("Usage: eigenrad <input_file>\n\n");
        return 1;
    }

    try
    {
        ParamDb db( argv[ 1 ] );

        const size_t ell        = ParamDb::GetSize_t( "Solver_Ell" );
        const size_t eigNo      = ParamDb::GetSize_t( "Solver_EigNo" );
        const double rc         = ParamDb::GetDouble( "Solver_Rc" );
        const size_t eigNode    = ParamDb::GetSize_t( "Solver_EigNode" );
        const size_t eigDeg     = ParamDb::GetSize_t( "Solver_EigDeg" );
        const double abstol     = ParamDb::GetDouble( "Solver_EigAbsTol" );
        const double absMaxCoef = ParamDb::GetDouble( "Solver_EigAbsMaxCoef" );
        const size_t points     = ParamDb::GetSize_t( "Out_points" );
        const std::string directory  = ParamDb::GetString( "Out_directory" );

        std::unique_ptr<Fun1D> pot = create_potential();

        EigProb eigProb( ell,
                        rc,
                        eigNode,
                        eigDeg,
                        *pot,
                        eigNo,
                        absMaxCoef,
                        abstol );

        const std::string path = directory + "/" + "coefficients.dat";
        eigProb.SolveAdapt( path );

        for(size_t eig = 0; eig < eigNo; eig++ )
        {
            std::print( "{:15.6e}\n", eigProb.GetEigVal(eig) );

            std::string filename = std::format("ell{}_n{}.dat", ell, eig + 1);
            const std::string path = directory + "/" + filename;
            // const std::filesystem::path path = std::filesystem::path{directory} / filename;
            eigProb.WriteEigFun( path, eig, points );
        }

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

    printf("\n\n********** CALCULATIONS FINISHED SUCCESSFULLY! **********\n\n\n");
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

//
// cmake -B build && cmake --build build/ &&  ctest --test-dir build && ./build/src/eigenrad ./results/aaa.inp
//
// cmake -B build && cmake --build build/ &&  ./build/src/eigenrad ./results/aaa.inp
//
