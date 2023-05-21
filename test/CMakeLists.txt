cmake_minimum_required(VERSION 3.20)
project(om_tests)
add_executable(${PROJECT_NAME}
  test.cpp
)

target_link_libraries(${PROJECT_NAME}
  GTest::gtest
  GTest::gtest_main
  object_mother
)

