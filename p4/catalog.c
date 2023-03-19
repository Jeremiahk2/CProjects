#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct CourseStruct
{
  char *dept;
  int number;
  char *days;
  char *time;
  char *name;
};
typedef struct CourseStruct Course;

struct CatalogStruct
{
  Course **list;
  int count;
  int capacity;
};
typedef struct CatalogStruct Catalog;

Catalog *makeCatalog()
{
  Catalog *catalog = (Catalog *)malloc(sizeof(Catalog));
  //Allocate room for the list of course pointers
  catalog->list = (Course **)malloc(5 * sizeof(Course *));
  catalog->count = 0;
  catalog->capacity = 5;
  return catalog;
}

void freeCatalog(Catalog *catalog) 
{
  int listSize = catalog->count;
  for (int i = 0; i < listSize; i++) { 
    free(catalog->list[i]); //Free the course pointers in the list
  }
  free(catalog->list); //Free the list of pointers itself
  free(catalog); //Free the catalog
}

void readCourses(char const *filename, Catalog *catalog) 
{
  FILE *fp = fopen(filename, "r");
  char *line;
  while (line = readLine(fp)) {
    char dept[4];
    int number;
    char days[3];
    char time[6];
    char name[31];
    int matches = sscanf(line, " %[A-Z] %d %s %s %[A-Za-z]", dept, number, days, time, name);
    if (matches != 5) {
      fprintf(stderr, "Invalid course file: %s", filename);
      exit(1);
    }
    if (dept < 100 || dept > 999) {
      fprintf(stderr, "Invalid course file: %s", filename);
      exit(1);
    }
    if (strcmp(days, "MW") != 0 && strcmp(days, "TH") != 0) {
      fprintf(stderr, "Invalid course file: %s", filename);
      exit(1);
    }
    if (strcmp(time, "8:30") != 0 && strcmp(time, "10:00") != 0 && strcmp(time, "11:30") != 0 
      && strcmp(time, "1:00") != 0 && strcmp(time, "2:30") != 0 && strcmp(time, "4:00") != 0) {

      fprintf(stderr, "Invalid course file: %s", filename);
      exit(1);
    }
    //All checks completed except checking if course and dept names are the same as another course

    if (catalog->count == catalog->capacity) {
      catalog->list = (Course **)realloc(catalog->list, catalog->capacity * 2 * sizeof(Course *));
      catalog->capacity *= 2;
    }
    Course course = {.dept = dept,
                     .number = number,
                     .days = days,
                     .time = time,
                     .name = name};
    Course *coursePointer = (Course *)malloc(sizeof(Course));
    *coursePointer = course;
    catalog->list[count] = coursePointer;
    catalog->count++;
  }
  for (int i = 0; i < catalog->count - 1; i++) {
    Course current = *(catalog->list[i]);
    if (strcmp(current.dept, dept) == 0 && current.number == number) {
      fprintf(stderr, "Invalid course file: %s", filename);
      exit(1);
    }
  }
}