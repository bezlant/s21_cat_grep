find . -type f -name "*.c" | xargs python3 ./cpplint.py --extensions=c
find . -type f -name "*.h" | xargs python3  ./cpplint.py --extensions=c
find . -type f -name "*.c" | xargs cppcheck --enable=all --suppress=missingIncludeSystem
