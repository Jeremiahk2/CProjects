#include "catalog.h"

/**
  @file catalog.c
  @author Jeremiah Knizley
  Contains methods necessary for handling the Catalog struct.
  It creates the catalog, frees the catalog, reads courses into the catalog,
  sorts the list of courses in the catalog, and lists the courses in the catalog.
*/


Catalog *makeCatalog()
{
  Catalog *catalog = (Catalog *)malloc(sizeof(Catalog));
  //Allocate room for the list of course pointers
  catalog->list = (Course **)malloc(INITIAL_CAT_CAPACITY * sizeof(Course *));
  catalog->count = 0;
  catalog->capacity = INITIAL_CAT_CAPACITY;
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
  if (fp == NULL) {
    fprintf(stderr, "Can't open file: %s\n", filename);
    freeCatalog(catalog);
    exit(1);
  }
  bool end = false;
  while ( !end ) { 

    char *reading = readLine(fp);
    if (reading != NULL) {
      //Shift around memory to static line since we don't need any resizes.
      char line[strlen(reading) + 1];
      strcpy(line, reading);
      free(reading);

      char dept[DEPT_LEN + 1];
      int number = 0;
      char tempNumber[NUM_LEN + 1];
      char days[DAYS_LEN + 1];
      char time[MAX_TIME_LEN + 1];
      char name[NAME_LEN + 1];
      //This is for any extra string that is found after the name string.
      //So we can check if anything is in it and report a fail if there is.
      char extra[EXTRA];
      int matches = sscanf(line, " %[A-Z] %[0-9] %s %s %30[A-Za-z 0-9] %1s", dept, tempNumber, days, time, name, extra);
      //We only want 5 matches. Any less means missing info. Any more means extra info.
      //Also the length of dept needs to be correct
      if (matches != NUM_FIELDS || (strlen(dept) != DEPT_LEN)) {
        fprintf(stderr, "Invalid course file: %s\n", filename);
        fclose(fp);
        freeCatalog(catalog);
        exit(1);
      }
      //If the length of the number string isn't 3, fail.
      if (strlen(tempNumber) != NUM_LEN) {
        fprintf(stderr, "Invalid course file: %s\n", filename);
        fclose(fp);
        freeCatalog(catalog);
        exit(1);
      }
      //Don't need a length comparison since all days can be is "MW" or "TH"
      if ((strcmp(days, "MW") != 0) && (strcmp(days, "TH") != 0)) {
        fprintf(stderr, "Invalid course file: %s\n", filename);
        fclose(fp);
        freeCatalog(catalog);
        exit(1);
      }
      //Need to explicitly check for correct times.
      if ((strcmp(time, "8:30") != 0) && (strcmp(time, "10:00") != 0) && (strcmp(time, "11:30") != 0)
        && (strcmp(time, "1:00") != 0) && (strcmp(time, "2:30") != 0) && (strcmp(time, "4:00") != 0)) {
        fclose(fp);
        freeCatalog(catalog);
        fprintf(stderr, "Invalid course file: %s\n", filename);
        exit(1);
      }
      //Put number into an int for Course struct. We know it matches an int so no need to check this.
      number = atoi(tempNumber);
      //All checks completed except checking if course and dept names are the same as another course

      //If we're at capacity, increase capacity of the list by 2
      if (catalog->count == catalog->capacity) {
        catalog->list = (Course **)realloc(catalog->list, catalog->capacity * CAT_INC * sizeof(Course *));
        catalog->capacity *= CAT_INC;
      }
      //Create the course
      Course course = {};
      strcpy(course.dept, dept);
      course.number = number;
      strcpy(course.days, days);
      strcpy(course.time, time);
      strcpy(course.name, name);

      //Put it in a pointer to a course, put it in the catalog
      Course *coursePointer = (Course *)malloc(sizeof(Course));
      *coursePointer = course;
      catalog->list[catalog->count] = coursePointer;
      catalog->count++;
      //Pretty sure this next part goes here, but I didn't put alot of thought into it.
      for (int i = 0; i < catalog->count - 1; i++) {
        Course current = *(catalog->list[i]);
        if (strcmp(current.dept, dept) == 0 && current.number == number) {
          fprintf(stderr, "Invalid course file: %s\n", filename);
          freeCatalog(catalog);
          fclose(fp);
          exit(1);
        }
      }
    }
    else {
      end = true;
    }
  }
  fclose(fp);
}

void sortCourses(Catalog *catalog, int (* compare) (void const *va, void const *vb))
{
  qsort(catalog->list, catalog->count, sizeof(catalog->list[0]), compare);
}

void listCourses(Catalog *catalog, bool (*test) (Course const *course, char const *str1, char const *str2), char const *str1, char const *str2)
{
  printf("Course  Name                           Timeslot\n");
  for (int i = 0; i < catalog->count; i++) {
    //If the test string says the course is the one we want, print it.
    if (test(catalog->list[i], str1, str2)) {
      char *dept = (catalog->list[i])->dept;
      int number = (catalog->list[i])->number;
      char *days = (catalog->list[i])->days;
      char *time = (catalog->list[i])->time;
      char *name = (catalog->list[i])->name;
      printf("%s %d %-30s %s %5s\n", dept, number, name, days, time);
    }
  }
  printf("\n");
}
