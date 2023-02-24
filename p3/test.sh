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

# Test the ident program.
testIdent() {
  TESTNO=$1
  ESTATUS=$2

  echo "Test $TESTNO"
  rm -f output.txt stderr.txt

  echo "   ./ident ${args[@]} > output.txt 2> stderr.txt"
  ./ident ${args[@]} > output.txt 2> stderr.txt
  ASTATUS=$?

  if ! checkStatus "$ESTATUS" "$ASTATUS" ||
     ! checkFile "Program output" "expected-$TESTNO.txt" "output.txt" ||
     ! checkFileOrEmpty "Stderr output" "expected-stderr-$TESTNO.txt" "stderr.txt"
  then
      FAIL=1
      return 1
  fi

  echo "Test $TESTNO PASS"
  return 0
}

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  fail "Make exited unsuccessfully"
fi

# Run test cases
if [ -x ident ]; then
    args=(input-01.txt x)
    testIdent 01 0
    
    args=(input-02.txt word)
    testIdent 02 0
    
    args=(input-03.txt WORD)
    testIdent 03 0
    
    args=(input-04.txt abc123)
    testIdent 04 0
    
    args=(input-05.txt set)
    testIdent 05 0
    
    args=(input-06.txt horse)
    testIdent 06 0
    
    args=(input-07.txt test)
    testIdent 07 0
    
    args=(input-08.txt _abc123)
    testIdent 08 0
    
    args=(input-09.txt and)
    testIdent 09 0
    
    args=(-n input-10.txt that)
    testIdent 10 0
    
    args=(-c 1 input-11.txt printf)
    testIdent 11 0
    
    args=(-c 2 input-12.txt isPrime)
    testIdent 12 0
    
    args=(-c 3 input-13.txt printf)
    testIdent 13 0
    
    args=(-n -c 2 input-14.txt eight)
    testIdent 14 0
    
    args=(-n -c 1 input-15.txt ch)
    testIdent 15 0
    
    args=(-c 2 input-16.txt match)
    testIdent 16 0
    
    args=(-c 1000 input-17.txt for)
    testIdent 17 0
    
    args=(input-18.txt rechtsschutzversicherungsgesellschaften_arbeiterunfallverischerungsgesetz_nahrungsmittelunvertraglichkeit)
    testIdent 18 0
    
    args=(input-19.txt 123abc)
    testIdent 19 1
    
    args=(input-20.txt)
    testIdent 20 1
    
    args=(-x input-21.txt i)
    testIdent 21 1
    
    args=(input-22.txt counter)
    testIdent 22 1
    
    args=(input-23.txt has)
    testIdent 23 1
    
else
    fail "Since your program didn't compile, we couldn't test it"
fi

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "TESTS SUCCESSFUL"
  exit 0
fi
