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
  Header file for catalog.c contains all methods and structs (and typedefs)
*/

/**
  Struct for Courses
  Contains a course's
  department
  number,
  meeting days,
  meeting time,
  name.
*/
typedef struct {
  char dept[DEPT_LEN + 1];
  int number;
  char days[DAYS_LEN + 1];
  char time[MAX_TIME_LEN + 1];
  char name[NAME_LEN + 1];
} Course;

/**
  Struct for Catalogs
  Contains a list of Course pointers for keeping track of courses
  contains an int representing the number of course pointers in the list
  contains a capacity
*/
typedef struct {
  Course **list;
  int count;
  int capacity;
} Catalog;

/**
  Creates a new catalog and returns it
  Dynamically allocates the list of courses (resizable) and the catalog itself
  @return the new catalog
*/
Catalog *makeCatalog();

/**
  Frees a catalog, including it's courses, the list containing the courses, and itself
  @param catalog the catalog to be freed
*/
void freeCatalog(Catalog *);

/**
  Reads a file and parses it for Courses
  @param filename the name of the file where the Courses are stored
  @param catalog the catalog to store the courses into
*/
void readCourses(char const *, Catalog *);

/**
  Sorts the courses using qsort and the given function parameter as a rule
  @param catalog the catalog where the courses are
  @param compare the function to be used to compare courses
*/
void sortCourses(Catalog *, int (* compare) (void const *va, void const *vb));

/**
  Lists the courses according to the given function parameter and strings as a rule
  @param catalog the catalog containing the courses
  @param test the function pointer that will tell if the course should be printed or not.
  @param str1 the first string to be used in test
  @param str2 the second string to be used in test.
  */
void listCourses(Catalog *, bool (*test) (Course const *course, char const *str1, char const *str2), char const *str1, char const *str2);
