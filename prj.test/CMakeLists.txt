# После добавления complex_test.cpp раскомментируй эти строки.
add_executable(complex_test complex_test.cpp)
target_link_libraries(complex_test PRIVATE complex)
add_test(NAME complex_test COMMAND complex_test)

add_executable(rational_test rational_test.cpp)
target_link_libraries(rational_test PRIVATE rational)
add_test(NAME rational_test COMMAND rational_test)

add_executable(arrayd_test arrayd_test.cpp)
target_link_libraries(arrayd_test PRIVATE arrayd)
add_test(NAME arrayd_test COMMAND arrayd_test)
