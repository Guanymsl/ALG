#!/bin/bash
ulimit -s 262144

OUTPUT_CSV="sort_results.csv"
echo "File,Sort Option,CPU Time (ms),Memory (KB)" > $OUTPUT_CSV

SORT_OPTIONS=("IS" "MS" "BMS" "QS" "RQS")
INPUT_FILES=("4000.case2" "4000.case3" "4000.case1"
             "16000.case2" "16000.case3" "16000.case1"
             "32000.case2" "32000.case3" "32000.case1"
             "1000000.case2" "1000000.case3" "1000000.case1")

for CASE_NAME in "${INPUT_FILES[@]}"
do
    INPUT_FILE="./inputs/${CASE_NAME}.in"

    for SORT_OPTION in "${SORT_OPTIONS[@]}"
    do
        OUTPUT_FILE="./outputs/${CASE_NAME}.out"

        COMMAND_OUTPUT=$(./bin/NTU_sort -$SORT_OPTION "$INPUT_FILE" "$OUTPUT_FILE" 2>&1)

        CPU_TIME=$(echo "$COMMAND_OUTPUT" | grep "The total CPU time" | awk '{print $5}' | sed 's/ms//')
        MEMORY=$(echo "$COMMAND_OUTPUT" | grep "memory:" | awk '{print $2}' | sed 's/KB//')

        if [ -z "$MEMORY" ]; then
            MEMORY=0
        fi

        echo "$CASE_NAME,$SORT_OPTION,$CPU_TIME,$MEMORY" >> $OUTPUT_CSV

        echo "Processed $INPUT_FILE -> $OUTPUT_FILE using $SORT_OPTION | CPU Time: $CPU_TIME ms | Memory: $MEMORY KB"
    done
done
