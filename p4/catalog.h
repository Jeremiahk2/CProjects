#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"

/**
  @file catalog.h
  @author Jeremiah Knizley
  Header file for catalog.c contains all methods and structs
*/

typedef struct {
  char dept[4];
  int number;
  char days[3];
  char time[6];
  char name[31];
} Course;

typedef struct {
  Course **list;
  int count;
  int capacity;
} Catalog;

Catalog *makeCatalog();

void freeCatalog(Catalog *);

void readCourses(char const *, Catalog *);

void sortCourses(Catalog *, int (* compare) (void const *va, void const *vb));

void listCourses(Catalog *, bool (*test) (Course const *course, char const *str1, char const *str2), char const *str1, char const *str2);
