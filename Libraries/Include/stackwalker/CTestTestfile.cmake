# CMake generated Testfile for 
# Source directory: D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker
# Build directory: D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(StackWalker_test "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/Debug/StackWalker_test.exe")
  set_tests_properties(StackWalker_test PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/CMakeLists.txt;116;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(StackWalker_test "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/Release/StackWalker_test.exe")
  set_tests_properties(StackWalker_test PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/CMakeLists.txt;116;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(StackWalker_test "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/MinSizeRel/StackWalker_test.exe")
  set_tests_properties(StackWalker_test PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/CMakeLists.txt;116;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(StackWalker_test "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/RelWithDebInfo/StackWalker_test.exe")
  set_tests_properties(StackWalker_test PROPERTIES  _BACKTRACE_TRIPLES "D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/CMakeLists.txt;116;add_test;D:/Sources/Current Projects/Foxy/Foxy 1.XX.X/vendor/stackwalker/CMakeLists.txt;0;")
else()
  add_test(StackWalker_test NOT_AVAILABLE)
endif()
