cmake .
make
find -iwholename '*cmake*' -not -name CMakeLists.txt -delete
find -iwholename 'makefile' -delete
