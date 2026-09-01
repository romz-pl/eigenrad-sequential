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

target_include_directories( ${LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


SET( EXE_NAME eigenrad )

add_executable( ${EXE_NAME}
    create_potential.cpp
    main.cpp
    paramdb.cpp
)

target_link_libraries(${EXE_NAME}
    PRIVATE
    eigenradengine
    LAPACK::LAPACK
    BLAS::BLAS
)
