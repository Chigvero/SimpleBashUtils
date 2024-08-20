#!/bin/bash

TRUE_TEST=0
FALSE_TEST=0
FILE_1="f1.txt"
FILE_2="f2.txt"
FILE_3="f3.txt"
FILE_4="f4.txt"
FILE_5="f5.txt"
TEMPLATE_1="cat"
TEMPLATE_2="q"
COMMAND_1="grep"
COMMAND_2="./s21_grep"
RES_1="grep_res.txt"
RES_2="s21_grep_res.txt"


for flag in -i -v -c -l -n -h -s -o
do
    for file in $FILE_1 $FILE_2 $FILE_3 $FILE_4
    do
        TEST_1="$flag $TEMPLATE_1 $file"
        echo "$TEST_1"
        $COMMAND_1 $TEST_1 > $RES_1
        $COMMAND_2 $TEST_1 > $RES_2
        DIFF=$(diff $RES_1 $RES_2) 
        if [ "$DIFF" = "" ] 
        then
            let "TRUE_TEST+=1"
        else
            echo "Error"
            let "FALSE_TEST+=1"
        fi
        
    done
done


for flag in -i -v -c -l -n -h -s -o
do
    for file1 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
    do
        for file2 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
        do
            TEST_1="$flag $TEMPLATE_1 $file1 $file2"
            echo "$TEST_1"
            $COMMAND_1 $TEST_1 > $RES_1
            $COMMAND_2 $TEST_1 > $RES_2
            DIFF=$(diff $RES_1 $RES_2)
            if [ "$DIFF" = "" ]
            then
                let "TRUE_TEST+=1"
            else
                echo "Error"
                let "FALSE_TEST+=1"
            fi

        done
    done
done


  for file1 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
    do
        for file2 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
        do
            TEST_1="-e $TEMPLATE_1 -e $TEMPLATE_2 $file1 $file2"
            echo "$TEST_1"
            $COMMAND_1 $TEST_1 > $RES_1
            $COMMAND_2 $TEST_1 > $RES_2
            DIFF=$(diff $RES_1 $RES_2)
            if [ "$DIFF" = "" ]
            then
                let "TRUE_TEST+=1"
            else
                echo "Error"
                let "FALSE_TEST+=1"
            fi

        done
    done


    for file3 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
    do
      for file1 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
        do
            for file2 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
            do
                TEST_1="-f $file3 $file1 $file2"
                echo "$TEST_1"
                $COMMAND_1 $TEST_1 > $RES_1
                $COMMAND_2 $TEST_1 > $RES_2
                DIFF=$(diff $RES_1 $RES_2)
                if [ "$DIFF" = "" ]
                then
                    let "TRUE_TEST+=1"
                else
                    echo "Error"
                    let "FALSE_TEST+=1"
                fi

            done
        done
    done

rm $RES_1 $RES_2
echo "SUCCESFUL: $TRUE_TEST"
echo "FAILED: $FALSE_TEST"