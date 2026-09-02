#include <iostream>
// #include <filesystem>
#include <format>
#include <print>
#include "create_potential.h"
#include "eigprob.h"
#include "paramdb.h"

int main(int argc, char* argv[])
{
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
        const size_t out_points     = ParamDb::GetSize_t( "Out_points" );
        bool create_log_file    = ParamDb::GetBool( "Out_create_log_file" );
        const std::string out_directory  = ParamDb::GetString( "Out_directory" );

        std::unique_ptr<Fun1D> pot = create_potential();

        EigProb eigProb( ell,
                        rc,
                        eigNode,
                        eigDeg,
                        *pot,
                        eigNo,
                        absMaxCoef,
                        abstol,
                        create_log_file,
                        out_directory,
                        out_points );

        eigProb.SolveAdapt();
        eigProb.WriteAllEigFun();

        for(size_t eig = 0; eig < eigNo; eig++ )
        {
            std::print( "{:16.9e}\n", eigProb.GetEigVal(eig) );
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



//
// cmake -B build && cmake --build build/ &&  ctest --test-dir build && ./build/src/eigenrad ./results/aaa.inp
//
// cmake -B build && cmake --build build/ &&  ./build/src/eigenrad ./results/aaa.inp
//
