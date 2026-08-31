SET( LIB_NAME eigenradengine )

add_library( ${LIB_NAME}
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
    mesh.cpp
    potential_coulomb.cpp
)


SET( EXE_NAME eigenrad )

add_executable( ${EXE_NAME}
    main.cpp
    paramdb.cpp
)

target_link_libraries(${EXE_NAME}
    PRIVATE
    eigenradengine
    LAPACK::LAPACK
    BLAS::BLAS
)
