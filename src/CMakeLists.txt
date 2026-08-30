SET( EXE_NAME eigenrad )

add_executable( ${EXE_NAME}
    bndr.cpp
    clpmtx.cpp
    clpmtxband.cpp
    element.cpp
    fun1D.cpp
    gauleg.cpp
    gauss.cpp
    lobatto.cpp
    main.cpp
    mesh.cpp
)

target_link_libraries(${EXE_NAME}
    PRIVATE
    LAPACK::LAPACK
    BLAS::BLAS
)
