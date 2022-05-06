#!/bin/bash

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'
TESTFILE=test.txt
PATFILE=pattern.txt
PAT='aboba'

printf "${GREEN}-----RUNNING TESTS-----${NC}\n"

grep $PAT $TESTFILE > a
gcc grep.c && ./a.out $PAT $TESTFILE > b
result=$(diff a b)

i=1

# TEST 1
if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 2
grep -v $PAT $TESTFILE > a
gcc grep.c && ./a.out -v $PAT $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 3
grep -i $PAT $TESTFILE > a
gcc grep.c && ./a.out -i $PAT $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 4
grep -s $PAT non_existent_file > a
gcc grep.c && ./a.out -s $PAT non_existent_file > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 5
grep -f $PATFILE $TESTFILE > a
gcc grep.c && ./a.out -f $PATFILE $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 6
FLAGS='-c'
grep $FLAGS $PAT $TESTFILE > a
gcc grep.c && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 7
FLAGS='-l'
grep $FLAGS $PAT $TESTFILE $TESTFILE $TESTFILE > a
gcc grep.c && ./a.out $FLAGS $PAT $TESTFILE $TESTFILE $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 8
FLAGS='-n'
grep $FLAGS $PAT $TESTFILE > a
gcc grep.c && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 9
FLAGS='-ivc'
grep $FLAGS $PAT $TESTFILE > a
gcc grep.c && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 10
FLAGS='-cl'
grep $FLAGS $PAT $TESTFILE $TESTFILE > a
gcc grep.c && ./a.out $FLAGS $PAT $TESTFILE $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 11
FLAGS='-hn'
grep $FLAGS $PAT $TESTFILE > a
gcc grep.c && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi

((i++))

# TEST 12
FLAGS='-cl'
grep $FLAGS 123 $TESTFILE > a
gcc grep.c && ./a.out $FLAGS 123 $TESTFILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
fi


rm a.out a b
