SET( EXE_NAME eigenrad )

add_executable( ${EXE_NAME}
    bndr.cpp
    clpmtx.cpp
    element.cpp
    main.cpp
    mesh.cpp
)

target_link_libraries(${EXE_NAME}
    PRIVATE
    LAPACK::LAPACK
    BLAS::BLAS
)
