#!/bin/bash
FAIL=0

# Function to run a single test of the infix_10 program.
testinfix_10() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt
  
  echo "Test $TESTNO: ./infix_10 < input-10-$TESTNO.txt > output.txt"
  ./infix_10 < input-10-$TESTNO.txt > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** FAILED - Expected an exit status of $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if ! diff -q expected-10-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output didn't match expected output."
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Function to run a single test of the infix_12 program.
testinfix_12() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt
  
  echo "Test $TESTNO: ./infix_12 < input-12-$TESTNO.txt > output.txt"
  ./infix_12 < input-12-$TESTNO.txt > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** FAILED - Expected an exit status of $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if ! diff -q expected-12-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output didn't match expected output."
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Try to get a fresh compile of the project.
echo "Running make clean"
make clean

echo "Building infix_10 with make"
make infix_10
if [ $? -ne 0 ]; then
    echo "**** Make didn't run succesfully when trying to build your infix_10 program."
    FAIL=1
fi

# Run tests for infix_10
if [ -x infix_10 ] ; then
    testinfix_10 01 0
    testinfix_10 02 0
    testinfix_10 03 0
    testinfix_10 04 0
    testinfix_10 05 0
    testinfix_10 06 0
    testinfix_10 07 0
    testinfix_10 08 0
    testinfix_10 09 0
    testinfix_10 10 0
    testinfix_10 11 0
    testinfix_10 12 100
    testinfix_10 13 102
    testinfix_10 14 101
    testinfix_10 15 0
    testinfix_10 16 100
else
    echo "**** Your infix_10 program couldn't be tested since it didn't compile successfully."
    FAIL=1

fi

echo "Building infix_12 with make"
make infix_12
if [ $? -ne 0 ]; then
    echo "**** Make didn't run succesfully when trying to build your infix_12 program."
    FAIL=1
fi

# Run tests for infix_12
if [ -x infix_12 ] ; then
    testinfix_12 01 0
    testinfix_12 02 0
    testinfix_12 03 0
    testinfix_12 04 0
    testinfix_12 05 0
    testinfix_12 06 0
    testinfix_12 07 0
    testinfix_12 08 102
    testinfix_12 09 100
    testinfix_12 10 100
    testinfix_12 11 102
else
    echo "**** Your infix_12 program couldn't be tested since it didn't compile successfully."
    FAIL=1

fi

if [ $FAIL -ne 0 ]; then
  echo "**** There were failing tests"
  exit 1
else 
  echo "Tests successful"
  exit 0
fi
