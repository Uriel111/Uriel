cmake .
make
find . -iwholename '*cmake*' -not -name CMakeLists.txt -not -name CMakeTest.cpp -not -name CMakeTest -delete
find . -iwholename '*makefile' -delete
find . -iwholename '*.a' -delete