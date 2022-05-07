#!/bin/bash

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'

printf "${GREEN}-----RUNNING TESTS-----${NC}\n"

cat test.txt > a
gcc cat.c && ./a.out test.txt > b
result=$(diff a b)

i=1

# TEST 1
if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
fi

((i++))

# TEST 2
cat -b test1.txt > a
gcc cat.c && ./a.out -b test1.txt > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
fi

((i++))

# TEST 3
cat -n test2.txt test.txt > a
gcc cat.c && ./a.out -n test2.txt test.txt > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
fi

((i++))

# TEST 4
cat -s test3.txt > a
gcc cat.c && ./a.out -s test3.txt > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
fi

((i++))

# TEST 5
cat -t test.txt > a
gcc cat.c && ./a.out -t test.txt > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
fi

((i++))

# TEST 6
cat -e test.txt > a
gcc cat.c && ./a.out -e test.txt > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
fi

((i++))

# TEST 7
FILE=weirdo.txt
FLAGS=
cat $FILE > a
gcc cat.c && ./a.out $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
fi

((i++))

# TEST 8
FILE=weirdo.txt
FLAGS=-b
cat $FLAGS $FILE > a
gcc cat.c && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
fi


rm a.out a b
