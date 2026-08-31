#include <gtest/gtest.h>

#include <stdio.h>

#include "../../src/eigprob.h"
#include "../../src/gauss.h"
#include "../../src/lobatto.h"
#include "../../src/paramdb.h"
#include "../../src/potential_coulomb.h"

TEST(coulomb, simple)
{
    Lobatto m_lobatto;
    Gauss m_gauss;

    ParamDb db( "./aaa.inp" );
    potential_coulomb pot;
    const size_t ell = ParamDb::GetSize_t( "Solver_Ell" );
    const size_t eigNo = ParamDb::GetSize_t( "Solver_EigNo" );
    EigProb eigProb( ell );
    ASSERT_NO_THROW( eigProb.SolveAdapt( pot, eigNo) );

    for(size_t eig = 0; eig < eigNo; eig++ )
        ASSERT_LE( eigProb.GetEigVal(eig), 0 );

}