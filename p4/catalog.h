#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"
/** Initial capacity of the Catalog list of courses */
#define INITIAL_CAT_CAPACITY 5
/** Initial length of the department string */
#define DEPT_LEN 3
/** Initial length of the number string */
#define NUM_LEN 3
/** Initial Length of the days string */
#define DAYS_LEN 2
/** Maximum length of the time string */
#define MAX_TIME_LEN 5
/** The length of the name string on a Course*/
#define NAME_LEN 30
/** This is only for one character and the null terminator read after "name" */
#define EXTRA 2
/** This is the number of fields in Course */
#define NUM_FIELDS 5
/** The multiplier to increment Catalog size by */
#define CAT_INC 2

/**
  @file catalog.h
  @author Jeremiah Knizley
  Header file for catalog.c contains all methods and structs
*/

typedef struct {
  char dept[DEPT_LEN + 1];
  int number;
  char days[DAYS_LEN + 1];
  char time[MAX_TIME_LEN + 1];
  char name[NAME_LEN + 1];
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
