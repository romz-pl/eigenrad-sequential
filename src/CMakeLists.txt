SET( EXE_NAME eigenrad )

add_executable( ${EXE_NAME}
    bndr.cpp
    clpmtx.cpp
    clpmtxband.cpp
    eigprob.cpp
    element.cpp
    eltinfo.cpp
    fun1D.cpp
    gauleg.cpp
    gauss.cpp
    lobatto.cpp
    main.cpp
    mesh.cpp
    paramdb.cpp
    potential_coulomb.cpp
)

target_link_libraries(${EXE_NAME}
    PRIVATE
    LAPACK::LAPACK
    BLAS::BLAS
)
