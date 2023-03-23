#include "catalog.h"
/**
  Creates a new catalog and returns it
  @return the new catalog
*/
Catalog *makeCatalog()
{
  Catalog *catalog = (Catalog *)malloc(sizeof(Catalog));
  //Allocate room for the list of course pointers
  catalog->list = (Course **)malloc(5 * sizeof(Course *));
  catalog->count = 0;
  catalog->capacity = 5;
  return catalog;
}

/**
  Frees a catalog, including it's courses, the list containing the courses, and itself
  @param catalog the catalog to be freed
*/
void freeCatalog(Catalog *catalog) 
{
  int listSize = catalog->count;
  for (int i = 0; i < listSize; i++) { 
    free(catalog->list[i]); //Free the course pointers in the list
  }
  free(catalog->list); //Free the list of pointers itself
  free(catalog); //Free the catalog
}

/**
  Reads a file and parses it for Courses
  @param filename the name of the file where the Courses are stored
  @param catalog the catalog to store the courses into
*/
void readCourses(char const *filename, Catalog *catalog) 
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "Can't open file: %s\n", filename);
    freeCatalog(catalog);
    exit(1);
  }
  bool end = false;
  while ( !end ) { //May need to free line on each pass

    char *reading = readLine(fp);
    if (reading != NULL) {
      char line[strlen(reading)];
      strcpy(line, reading);
      free(reading);

      char dept[4];
      int number = 0;
      char tempNumber[4];
      char days[3];
      char time[6];
      char name[31];
      char extra[2];
      int matches = sscanf(line, " %[A-Z] %[0-9] %s %s %30[A-Za-z 0-9] %1s", dept, tempNumber, days, time, name, extra);

      if (matches != 5 || (strlen(dept) != 3)) {
        fprintf(stderr, "Invalid course file: %s\n", filename);
        fclose(fp);
        freeCatalog(catalog);
        exit(1);
      }
      if (strlen(tempNumber) != 3) {
        fprintf(stderr, "Invalid course file: %s\n", filename);
        fclose(fp);
        freeCatalog(catalog);
        exit(1);
      }
      if ((strcmp(days, "MW") != 0) && (strcmp(days, "TH") != 0)) {
        fprintf(stderr, "Invalid course file: %s\n", filename);
        fclose(fp);
        freeCatalog(catalog);
        exit(1);
      }
      if ((strcmp(time, "8:30") != 0) && (strcmp(time, "10:00") != 0) && (strcmp(time, "11:30") != 0)
        && (strcmp(time, "1:00") != 0) && (strcmp(time, "2:30") != 0) && (strcmp(time, "4:00") != 0)) {
        fclose(fp);
        freeCatalog(catalog);
        fprintf(stderr, "Invalid course file: %s\n", filename);
        exit(1);
      }
      //Put number into an int for Course struct
      number = atoi(tempNumber);
      //All checks completed except checking if course and dept names are the same as another course

      if (catalog->count == catalog->capacity) {
        catalog->list = (Course **)realloc(catalog->list, catalog->capacity * 2 * sizeof(Course *));
        catalog->capacity *= 2;
      }
      Course course = {};
      strcpy(course.dept, dept);
      course.number = number;
      strcpy(course.days, days);
      strcpy(course.time, time);
      strcpy(course.name, name);

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

/**
  Sorts the courses using qsort and the given function parameter as a rule
  @param catalog the catalog where the courses are
  @param compare the function to be used to compare courses
*/
void sortCourses(Catalog *catalog, int (* compare) (void const *va, void const *vb))
{
  qsort(catalog->list, catalog->count, sizeof(catalog->list[0]), compare);
}

/**
  Lists the courses according to the given function parameter and strings as a rule
  @param catalog the catalog containing the courses
  @param test the function pointer that will tell if the course should be printed or not.
  @param str1 the first string to be used in test
  @param str2 the second string to be used in test.
  */
void listCourses(Catalog *catalog, bool (*test) (Course const *course, char const *str1, char const *str2), char const *str1, char const *str2)
{
  printf("Course  Name                           Timeslot\n");
  for (int i = 0; i < catalog->count; i++) {
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
