set( TEST_NAME lobatto )

add_executable( ${TEST_NAME}
    main.cpp
)

target_link_libraries( ${TEST_NAME}
    eigenradengine
    LAPACK::LAPACK
    BLAS::BLAS
    GTest::gtest_main
)

gtest_discover_tests( ${TEST_NAME} )
