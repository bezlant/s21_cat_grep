#!/bin/bash

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'
TESTFILE=test.txt
PATFILE=pattern.txt
PAT='aboba'
EXE="-g s21_grep.c"

printf "${GREEN}-----RUNNING TESTS-----${NC}\n"

grep $PAT $TESTFILE > a
gcc $EXE && ./a.out $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $PAT $TESTFILE

i=1
failed=0

# TEST 1
if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 2
grep -v $PAT $TESTFILE > a
gcc $EXE && ./a.out -v $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out -v $PAT $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 3
grep -i $PAT $TESTFILE > a
gcc $EXE && ./a.out -i $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out -i $PAT $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 4
grep -s $PAT non_existent_file > a
gcc $EXE && ./a.out -s $PAT non_existent_file > b
result=$(diff a b)
leaks -atExit -- ./a.out -s $PAT $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 5
grep -f $PATFILE $TESTFILE > a
gcc $EXE && ./a.out -f $PATFILE $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out -f $PATFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 6
FLAGS='-c'
grep $FLAGS $PAT $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 7
FLAGS='-l'
grep $FLAGS $PAT $TESTFILE $TESTFILE $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE $TESTFILE $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE $TESTFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 8
FLAGS='-n'
grep $FLAGS $PAT $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE


if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 9
FLAGS='-ivc'
grep $FLAGS $PAT $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 10
FLAGS='-cl'
grep $FLAGS $PAT $TESTFILE $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 11
FLAGS='-hn'
grep $FLAGS $PAT $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 12
FLAGS='-cl'
grep $FLAGS 123 $TESTFILE > a
gcc $EXE && ./a.out $FLAGS 123 $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE $TESTFILE


if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 13
FLAGS='-o'
grep $FLAGS $PAT $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 14
FLAGS='-on'
grep $FLAGS $PAT $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 15
FLAGS='-onf'
grep $FLAGS $PATFILE $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PATFILE $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PATFILE $TESTFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

((i++))

# TEST 16
FLAGS='-lco'
grep $FLAGS $PAT $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi


((i++))

# TEST 17
FLAGS='-cvie'
grep $FLAGS $PAT $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi
((i++))

# TEST 18
FLAGS='-cvie'
grep $FLAGS $PAT $TESTFILE $TESTFILE $TESTFILE $TESTFILE > a
gcc $EXE && ./a.out $FLAGS $PAT $TESTFILE $TESTFILE $TESTFILE $TESTFILE > b
result=$(diff a b)
leaks -atExit -- ./a.out $FLAGS $PAT $TESTFILE $TESTFILE $TESTFILE $TESTFILE

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result\n"
    ((failed++))
fi

printf " ${GREEN}-----DONE[$((i - failed))/$((i))]-----${NC}\n"
rm a.out a b
