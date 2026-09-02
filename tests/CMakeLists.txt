set( TEST_NAME eigenrad_tests )

add_executable( ${TEST_NAME}
    lobatto.cpp
    potential_coulomb.cpp
)

target_link_libraries( ${TEST_NAME}
    eigenradengine
    LAPACK::LAPACK
    BLAS::BLAS
    GTest::gtest_main
)

gtest_discover_tests( ${TEST_NAME} )
