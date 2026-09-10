#pragma once

//
// Boundary conditions
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//




//
// Vertex boundary conditions
//
enum BndrType
{
    BndrType_Emp = 0, // Empty
    BndrType_Dir, // Dirichlet
    BndrType_Neu // Neumann
};

