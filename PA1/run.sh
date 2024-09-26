#!/bin/bash

# CSV file to store the results
OUTPUT_CSV="sort_results.csv"

# Write the header to the CSV file
echo "File,Sort Option,CPU Time (ms),Memory (KB)" > $OUTPUT_CSV

# Array of sorting options
SORT_OPTIONS=("IS" "MS" "BMS" "QS" "RQS")

# Array of specific input files (based on the names in your image)
INPUT_FILES=("4000.case2" "4000.case3" "4000.case1"
             "16000.case2" "16000.case3" "16000.case1"
             "32000.case2" "32000.case3" "32000.case1"
             "1000000.case2" "1000000.case3" "1000000.case1")

# Loop through the specified input files
for BASE_NAME in "${INPUT_FILES[@]}"
do
    INPUT_FILE="./inputs/$BASE_NAME.in"

    # Loop through all sort options
    for SORT_OPTION in "${SORT_OPTIONS[@]}"
    do
        # Construct the output file name by changing the extension to .out
        OUTPUT_FILE="./outputs/${BASE_NAME}.out"

        # Capture the time and memory output by redirecting stderr to stdout, then parsing the result
        COMMAND_OUTPUT=$(./bin/NTU_sort -$SORT_OPTION "$INPUT_FILE" "$OUTPUT_FILE" 2>&1)

        # Extract the CPU time and memory usage from the command output
        CPU_TIME=$(echo "$COMMAND_OUTPUT" | grep "The total CPU time" | awk '{print $5}')
        MEMORY=$(echo "$COMMAND_OUTPUT" | grep "memory:" | awk '{print $2}' | sed 's/KB//')

        # If memory is not captured, set it to 0 as default
        if [ -z "$MEMORY" ]; then
            MEMORY=0
        fi

        # Log the file, sort option, CPU time, and memory usage to the CSV
        echo "$BASE_NAME,$SORT_OPTION,$CPU_TIME,$MEMORY" >> $OUTPUT_CSV

        # Notify the user about the processing status
        echo "Processed $INPUT_FILE -> $OUTPUT_FILE using $SORT_OPTION | CPU Time: $CPU_TIME ms | Memory: $MEMORY KB"
    done
done
