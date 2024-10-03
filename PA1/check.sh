#!/bin/bash
ulimit -s 262144
chmod u+x ./utility/PA1_Result_Checker

SORT_OPTIONS=("IS" "MS" "BMS" "QS" "RQS")
INPUT_FILES=("5.case1"
             "1000.case1" "1000.case2" "1000.case3"
             "2000.case1" "2000.case2" "2000.case3"
             "4000.case1" "4000.case2" "4000.case3"
             "8000.case1" "8000.case2" "8000.case3"
             "16000.case1" "16000.case2" "16000.case3"
             "32000.case1" "32000.case2" "32000.case3"
             "1000000.case1" "1000000.case2" "1000000.case3")

for SORT_OPTION in "${SORT_OPTIONS[@]}"
do
    for CASE_NAME in "${INPUT_FILES[@]}"
    do
        INPUT_FILE="./inputs/${CASE_NAME}.in"
        OUTPUT_FILE="./outputs/${CASE_NAME}.out"

        COMMAND_OUTPUT=$(./bin/NTU_sort -$SORT_OPTION "$INPUT_FILE" "$OUTPUT_FILE" 2>&1)
        CHECKER_OUTPUT=$(./utility/PA1_Result_Checker "$INPUT_FILE" "$OUTPUT_FILE")

        echo "Checker result for $CASE_NAME with $SORT_OPTION:"
        echo "$CHECKER_OUTPUT"
    done
done
