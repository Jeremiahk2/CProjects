#!/bin/bash
# This is a shell script to check your program(s) on test cases.
# It usese the same language you normally use to type commands in
# a terminal window.  You can write whole programs in shell.

# Assume we've succeeded until we see otherwise.
FAIL=0

# Print an error message and set the fail flag.
fail() {
    echo "**** $1"
    FAIL=1
}

# Check the exit status.  The actual exit status (ASTATUS) should match
# the expected status (ESTATUS)
checkStatus() {
  ESTATUS="$1"
  ASTATUS="$2"

  # Make sure the program exited with the right exit status.
  if [ "$ASTATUS" -ne "$ESTATUS" ]; then
      fail "FAILED - incorrect program exit status. (expected $ESTATUS,  Got: $ASTATUS)"
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
  echo "   diff $EFILE $AFILE"
  diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
  if [ $? -ne 0 ]; then
      fail "FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
      return 1
  fi

  return 0
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
	  fail "FAILED - $NAME ($AFILE) should be empty."
	  return 1
      fi
      return 0
  fi

  # Make sure the output matches the expected output.
  echo "   diff $EFILE $AFILE"
  diff -q "$EFILE" "$AFILE" >/dev/null 2>&1
  if [ $? -ne 0 ]; then
      fail "FAILED - $NAME ($AFILE) doesn't match expected ($EFILE)"
      return 1
  fi

  return 0
}

# The given file should exist but should be empty.
checkEmpty() {
  NAME="$1"
  AFILE="$2"
  
  if [ -s "$AFILE" ]; then
      fail "FAILED - $NAME ($AFILE) should be empty."
      return 1
  fi

  return 0
}

# Test one execution of the encrypt program.
testEncrypt() {
  TESTNO=$1
  ESTATUS=$2

  echo "Encrypt Test $TESTNO"
  rm -f output.dat stderr.txt

  echo "   ./encrypt ${args[@]} output.dat 2> stderr.txt"
  ./encrypt ${args[@]} output.dat 2> stderr.txt
  ASTATUS=$?

  if ! checkStatus "$ESTATUS" "$ASTATUS" ||
     ! checkFile "Ciphertext output" "cipher-$TESTNO.dat" "output.dat" ||
     ! checkFileOrEmpty "Stderr output" "error-$TESTNO.txt" "stderr.txt"
  then
      FAIL=1
      return 1
  fi

  echo "Encrypt Test $TESTNO PASS"
  return 0
}

# Test one execution of the decrypt program.
testDecrypt() {
  TESTNO=$1
  ESTATUS=$2

  echo "Decrypt Test $TESTNO"
  rm -f output.dat stderr.txt

  echo "   ./decrypt ${args[@]} output.dat 2> stderr.txt"
  ./decrypt ${args[@]} output.dat 2> stderr.txt
  ASTATUS=$?

  if ! checkStatus "$ESTATUS" "$ASTATUS" ||
     ! checkFile "Plaintext output" "plain-$TESTNO.dat" "output.dat" ||
     ! checkFileOrEmpty "Stderr output" "error-$TESTNO.txt" "stderr.txt"
  then
      FAIL=1
      return 1
  fi

  echo "Decrypt Test $TESTNO PASS"
  return 0
}

# Get a clean build of the project.
make clean

# Run unit tests for the field component.
echo
echo "Running fieldTest unit tests"
make fieldTest

if [ -x fieldTest ]; then
    ./fieldTest
    
    if [ $? -ne 0 ]; then
	echo "**** Your program didn't pass all the fieldTest unit tests."
	FAIL=1
    fi
else
    echo "**** We couldn't build the fieldTest program with your implementation, so we couldn't run these unit tests."
    FAIL=1
fi


# Run unit tests for the aes component.
echo
echo "Running aesTest unit tests"
make aesTest

if [ -x aesTest ]; then
    ./aesTest
    
    if [ $? -ne 0 ]; then
	echo "**** Your program didn't pass all the aesTest unit tests."
	FAIL=1
    fi
else
    echo "**** We couldn't build the aesTest program with your implementation, so we couldn't run these unit tests."
    FAIL=1
fi

# Tests for the encrypt program.
echo
echo "Running encrypt tests"

# Default build should make both the encrypt and decrypt programs.
make

if [ -x encrypt ]; then
    args=(key-01.dat plain-01.dat)
    testEncrypt 01 0
    
    args=(key-02.dat plain-02.dat)
    testEncrypt 02 0
    
    args=(key-03.dat plain-03.dat)
    testEncrypt 03 0
    
    args=(key-04.dat plain-04.dat)
    testEncrypt 04 0
    
    args=(key-05.dat plain-05.dat)
    testEncrypt 05 0
    
    args=(key-06.dat plain-06.dat)
    testEncrypt 06 0
    
    args=(key-07.dat plain-07.dat)
    testEncrypt 07 1
    
    args=(key-08.dat)
    testEncrypt 08 1
else
    fail "Since your encrypt program didn't compile, it couldn't be tested"
fi

# Tests for the decrypt program.
echo
echo "Running decrypt tests"

if [ -x decrypt ]; then
    args=(key-01.dat cipher-01.dat)
    testDecrypt 01 0
    
    args=(key-02.dat cipher-02.dat)
    testDecrypt 02 0
    
    args=(key-03.dat cipher-03.dat)
    testDecrypt 03 0
    
    args=(key-04.dat cipher-04.dat)
    testDecrypt 04 0
    
    args=(key-05.dat cipher-05.dat)
    testDecrypt 05 0
    
    args=(key-06.dat cipher-06.dat)
    testDecrypt 06 0
    
    args=(key-09.dat cipher-09.dat)
    testDecrypt 09 1
else
    fail "Since your decrypt program didn't compile, it couldn't be tested"
fi

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "Tests successful"
  exit 0
fi
