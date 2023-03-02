/**
  @file syntax.h
  @author Jeremiah Knizley
  header file for syntax.c Contains preprocessor macros
  as well as methods that will be used in ident.c */

#include <stdbool.h>

bool validIdentifier(char ident[]);

bool markIdentifier(char word[], char line[], int color[]);
