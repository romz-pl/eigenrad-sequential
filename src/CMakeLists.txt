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
    gauss_integral.cpp
    lobatto.cpp
    mesh.cpp
    potential_coulomb.cpp
    potential_hgh_hydrogen.cpp
    potential_soft_coulomb.cpp
    step_info.cpp
)

target_compile_options( ${LIB_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -march=native
    -mtune=native
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

target_compile_options( ${EXE_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -march=native
    -mtune=native
)

target_link_libraries(${EXE_NAME}
    PRIVATE
    eigenradengine
    LAPACK::LAPACK
    BLAS::BLAS
)
