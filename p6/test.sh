#!/bin/bash
# This is a shell script to check your program(s) on test cases.
# It usese the same language you normally use to type commands in
# a terminal window.  You can write whole programs in shell.

# Assume we've succeeded until we see otherwise.
FAIL=0

# Check the exit status.  The actual exit status (ASTATUS) should match
# the expected status (ESTATUS)
checkStatus() {
  ESTATUS="$1"
  ASTATUS="$2"

  # Make sure the program exited with the right exit status.
  if [ "$ASTATUS" -ne "$ESTATUS" ]; then
      echo "**** Test FAILED - incorrect program exit status. (expected $ESTATUS,  Got: $ASTATUS)"
      return 1
  fi

  return 0
}

# Check the contents of an a file.  If the expected file (EFILE)
# exists, then the actual file (AFILE) should exist and it should match.
checkFile() {
  NAME="$1"
  EFILE="$2"
  AFILE="$3"

  # Make sure we're really expecting this file.
  if [ ! -f "$EFILE" ]; then
      return 0
  fi

  # Make sure the output matches the expected output.
  diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
  if [ $? -ne 0 ]; then
      echo "**** Test FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
      return 1
  fi
}

# Same as checkFile, but if the expected file (EFILE) doesn't exist, the
# actual file (AFILE) should be empty.
checkFileOrEmpty() {
  NAME="$1"
  EFILE="$2"
  AFILE="$3"
  
  # if the expected output file doesn't exist, the actual file should be
  # empty.
  if [ ! -f "$EFILE" ]; then
      if [ -s "$AFILE" ]; then
	  echo "**** Test FAILED - $NAME ($AFILE) should be empty."
	  return 1
      fi
      return 0
  fi

  # Make sure the output matches the expected output.
  diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
  if [ $? -ne 0 ]; then
      echo "**** Test FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
      return 1
  fi
}

# Given AFILE should be empty.
checkEmpty() {
  NAME="$1"
  AFILE="$2"
  
  if [ -s "$AFILE" ]; then
      echo "**** Test FAILED - $NAME ($AFILE) should be empty."
      return 1
  fi
}

# Same as checkFile, but if the expected file (EFILE) doesn't exist, the
# actual file (AFILE) should not exist.
checkFileOrDNE() {
  NAME="$1"
  EFILE="$2"
  AFILE="$3"
  
  # if the expected output file doesn't exist, the actual file should be
  # empty.
  if [ ! -f "$EFILE" ]; then
      if [ -f "$AFILE" ]; then
	  echo "**** Test FAILED - $NAME ($AFILE) should not be created."
	  return 1
      fi
      return 0
  fi

  # Make sure the output matches the expected output.
  diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
  if [ $? -ne 0 ]; then
      echo "**** Test FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
      return 1
  fi
}

# Test the gq program.
testGq() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt  stderr.txt

  echo "Test $TESTNO: ./gq < input-$TESTNO.txt > output.txt"
  ./gq < input-$TESTNO.txt > output.txt 2> stderr.txt
  ASTATUS=$?

  if ! checkStatus "$ESTATUS" "$ASTATUS" ||
     ! checkFileOrEmpty "Standard Output" "expected-$TESTNO.txt" "output.txt" ||
     ! checkEmpty "Error Output" "stderr.txt"
  then
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make exited unsuccessfully"
  FAIL=1
fi

# Run test cases.
if [ -x gq ]; then
    testGq 01 0
    testGq 02 0
    testGq 03 0
    testGq 04 0
    testGq 05 0
    testGq 06 0
    testGq 07 0
    testGq 08 0
    testGq 09 0
    testGq 10 0
    testGq 11 0
    testGq 12 0
    testGq 13 0
else
  echo "Since your program didn't compile, we couldn't test it"
fi


if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "TESTS SUCCESSFUL"
  exit 0
fi
