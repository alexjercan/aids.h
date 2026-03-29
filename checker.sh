#!/usr/bin/env bash

MEMCHECKER=valgrind
BUILD_DIR=build
TESTS_DIR=tests
TOTAL_TESTS=0
PASSED_TESTS=0
MEMCHECK=0
VERBOSE=0

usage() {
    echo "Usage: $0 [--memcheck] [-v | --verbose] [-h | --help]"
    echo
    echo "Options:"
    echo "  --memcheck      Enable memory leak checking with valgrind."
    echo "  -v, --verbose   Show more details in case of errors."
    echo "  -h, --help      Show this help message and exit."
}

run_tests() {
    echo "Running tests"

    passed=0
    total=0

    for file_path in $(ls $BUILD_DIR/$TESTS_DIR/*); do
        if [ ! -x "$file_path" ]; then
            continue
        fi

        file_name=$(basename $file_path)
        echo -en "Testing $file_name ... "

        memcheck_result=1
        if [ "$MEMCHECK" -eq 1 ]; then
            $MEMCHECKER --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=42 $file_path > /dev/null 2>&1
            if [ $? -eq 42 ]; then
                memcheck_result=0
            else
                memcheck_result=1
            fi
        fi

        output=$($file_path 2>&1)
        test_status=$?

        if [ "$test_status" -eq 0 ] && [ "$memcheck_result" -eq 1 ]; then
            echo -e "\e[32mPASSED\e[0m"
            passed=$((passed + 1))
        else
            echo -e "\e[31mFAILED\e[0m"
            if [ "$VERBOSE" -eq 1 ]; then
                if [ "$test_status" -ne 0 ]; then
                    echo "  Exit code: $test_status"
                    echo "$output"
                fi
                if [ "$MEMCHECK" -eq 1 ] && [ "$memcheck_result" -eq 0 ]; then
                    echo "  Memory leak detected"
                    $MEMCHECKER --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all $file_path 2>&1 | grep -A 10 "LEAK SUMMARY"
                fi
            fi
        fi

        total=$((total + 1))
    done

    echo "Passed $passed/$total tests"

    TOTAL_TESTS=$((TOTAL_TESTS + total))
    PASSED_TESTS=$((PASSED_TESTS + passed))
}

# Parse arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        --memcheck)
            MEMCHECK=1
            shift
            ;;
        -v|--verbose)
            VERBOSE=1
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            usage
            exit 1
            ;;
    esac
done

make clean && make

if [ $? -ne 0 ]; then
    echo -e "\e[31mBuild failed\e[0m"
    exit 1
fi

run_tests

if [ $PASSED_TESTS -eq $TOTAL_TESTS ]; then
    echo -e "\e[32mAll tests passed\e[0m"
    exit 0
else
    echo -e "\e[31mSome tests failed\e[0m"
    exit 1
fi
