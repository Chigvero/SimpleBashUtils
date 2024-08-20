#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="hidden.txt"
TEST_FILE2="test.txt"
TEST_FILE3="empty.txt"
TEST_FILE4="squeze.txt"
echo "" > log.txt


for test2 in $TEST_FILE $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
          TEST1="$test2"
          echo "$TEST1"

          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
              echo "error"
          fi
         rm s21_cat.txt cat.txt
done



for test in  $TEST_FILE $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
for test2 in $TEST_FILE $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
          TEST1="$test $test2"
          echo "$TEST1"

          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
              echo "error"
          fi
         rm s21_cat.txt cat.txt
done
done


for test in  $TEST_FILE $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
for test2 in $TEST_FILE $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
for var in -s -t -v 
do
          TEST1="$var $test $test2"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
              echo "error"
          fi
         rm s21_cat.txt cat.txt
done
done
done

for test in  $TEST_FILE $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
for test2 in $TEST_FILE $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
for var in -b -e -n
do
          TEST1="$var $test $test2"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
              echo "error"
          fi
        rm s21_cat.txt cat.txt
done
done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"