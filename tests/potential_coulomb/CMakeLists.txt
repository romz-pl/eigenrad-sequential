set( TEST_NAME potential_coulomb_00 )

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
