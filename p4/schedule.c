#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "catalog.h"
#include "input.h"

/** Number needed to change to military time */
#define MIL_TIME_CONV 12
/** Upper bound on the time that can be used in Course (PM)*/
#define TIME_UP_BND 5
/** capacity for the list of courses in a schedule */
#define SCHED_CAP 10
/** The number of times possible */
#define NUM_TIMES 6
/** The number of days a course can be held */
#define NUM_DAYS 4
/** The length of the string for the days in calendar, ex. "Mon", "Tue", etc.*/
#define CAL_DAY_LEN 3

/**
  @file schedule.c
  @author Jeremiah Knizley
  This file maintains a schedule of courses. Users can load course catalogs in and then add courses
  to their schedule and view them as they wish. They can also load a calendar visualization for their schedule
*/

/**
  Compares aptr and bptr by ID (dept and number). 
  @param aptr the first course to be compared
  @param bptr the second course to be compared
  @return a number < 0 if aptr comes before bptr, 0 if they are the same, otherwise 1
*/
static int idComp(const void *aptr, const void *bptr)
{
  Course const *a = *((Course **)aptr);
  Course const *b = *((Course **)bptr);
  //If one of them is null, we want it to go after the non-null one. If
  //With our implementation, both being NULL should be impossible.
  if (a == NULL) {
    return 1;
  }
  if (b == NULL) {
    return -1;
  }
  char idA[DEPT_LEN + 1];
  char idB[DEPT_LEN + 1];
  strcpy(idA, a->dept);
  strcpy(idB, b->dept);


  if (strcmp(idA, idB) < 0) {
    return -1;
  }
  else if (strcmp(idA, idB) == 0) {
    if (a->number < b->number) {
      return -1;
    }
    else if (a-> number > b->number) {
      return 1;
    }
    else {
      return 0;
    }
  }
  else {
    return 1;
  }

}
/**
  Compares aptr with bptr by name
  @param aptr the first course to be compared
  @param bptr the second course to be compared
  @return a number < 0 if aptr comes before bptr, 0 if they are the same, otherwise 1
*/
static int nameComp(const void *aptr, const void *bptr)
{
  Course const *a = *((Course **)aptr);
  Course const *b = *((Course **)bptr);
  if (a == NULL) {
    return 1;
  }
  if (b == NULL) {
    return -1;
  }
  char nameA[NAME_LEN + 1];
  char nameB[NAME_LEN + 1];
  strcpy(nameA, a->name);
  strcpy(nameB, b->name);

  if (strcmp(nameA, nameB) < 0) {
    return -1;
  }
  else if (strcmp(nameA, nameB) > 0) {
    return 1;
  }
  //If they have the same name, fall back on ID comparison
  else {
    return idComp(aptr, bptr);
  }
}

/**
  Compares aptr with bptr by date and time
  @param aptr the first course to be compared
  @param bptr the second course to be compared
  @return a number < 0 if aptr comes before bptr, 0 if they are the same, otherwise 1
*/
static int scheduleComp(const void *aptr, const void *bptr)
{
  Course const *a = *((Course **)aptr);
  Course const *b = *((Course **)bptr);
  if (a == NULL) {
    return 1;
  }
  if (b == NULL) {
    return -1;
  }
  char daysA[DAYS_LEN + 1];
  char daysB[DAYS_LEN + 1];
  strcpy(daysA, a->days);
  strcpy(daysB, b->days);

  if (strcmp(daysA, daysB) < 0) {
    return -1;
  }
  else if (strcmp(daysA, daysB) > 0) {
    return 1;
  }
  else {
    int timeA = 0;
    int timeB = 0;
    sscanf(a->time, "%d:", &timeA);
    sscanf(b->time, "%d:", &timeB);
    //If the time is in the afternoon, convert to military time.
    if (timeA < TIME_UP_BND) {
      timeA += MIL_TIME_CONV;
    }
    if (timeB < TIME_UP_BND) {
      timeB += MIL_TIME_CONV;
    }
    if (timeA < timeB) {
      return -1;
    }
    else if (timeA > timeB) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

/**
  Returns true if the course parameter should be listed according to str1 and str2
  If both str1 and str2 are null, true is returned. if str2 is NULL, and the dept of course equals str1,
  true is returned, false if not. 
  otherwise if course's days and course's time equals str1 and str2 respectively, true is returned, false if not.
  @param str1 the first string requirement (if needed)
  @param str2 the second string requirement (if needed)
  @return true if the course should be listed, false if not
*/
static bool listTest( const Course *course, const char *str1, const char *str2)
{
  //This means it is the list courses command
  if (str1 == NULL && str2 == NULL) {
    return true;
  }
  //This means it is the list department command
  else if (str2 == NULL) {
    return strcmp(course->dept, str1) == 0;
  }
  return strcmp(course->days, str1) == 0 && strcmp(course->time, str2) == 0;
}

/**
  The main part of the program. Courses are loaded in from user arguments, and 
  a catalog is created. Then the user can issue commands to list courses in the catalog, schedule,
  or to add and drop courses from the schedule.
  @param argc the number of arguments
  @param argv the arguments from index 1 onward should contain the files containing the catalog of courses.
*/
int main(int argc, char *argv[]) 
{
  if (argc == 1) {
    fprintf(stderr, "usage: schedule <course-file>*\n");
    exit(1);
  }
  Catalog *catalog = makeCatalog();
  for (int i = 1; i < argc; i++) {
    readCourses(argv[i], catalog);
  }
  //Making schedule a catalog too because it reduces redundancy by ALOT. Resizability isn't used after initial setup
  //So the only drawback is that the memory is a little bit more expensive. But trade-off wise it seems like the play.
  Catalog *schedule = makeCatalog();
  schedule->list = (Course **)realloc(schedule->list, SCHED_CAP * sizeof(Course *));
  schedule->capacity = SCHED_CAP;

  bool quit = false;
  while (!quit) {
    printf("cmd> ");
    // int schedSize = 0;

    //Get first part of the command.
    char *temp = readLine(stdin);
    if (temp != NULL) {
      char command[strlen(temp) + 1];
      strcpy(command, temp);
      free(temp);

      int pos = 0;
      printf("%s\n", command);
      char first[strlen(command)];
      int matches = sscanf(command, "%s%n", first, &pos);

      //Check the first part of the command.
      if (matches && (strcmp(first, "list") == 0)) {
        //If it's list, check the second parameter of the command.
        char second[strlen(command)];
        int newPos = 0;
        int secondMatches = sscanf(command + pos, "%s%n", second, &newPos);
        pos = pos + newPos;

        //If the command is "list courses"
        if (secondMatches && (strcmp(second, "courses") == 0)) {
          //First, sort courses by ID
          sortCourses(catalog, idComp);
          //Then list all courses
          listCourses(catalog, listTest, NULL, NULL);
        }

        //If the command is "list names"
        else if (secondMatches && (strcmp(second, "names") == 0)) {
          //Sort courses by name first.
          sortCourses(catalog, nameComp);
          //Then list all courses
          listCourses(catalog, listTest, NULL, NULL);
        }

        //If the command is "list department <dept>"
        else if (secondMatches && (strcmp(second, "department") == 0)) {
          char third[strlen(command)]; //Department string, ex. "CSC"
          int thirdMatches = sscanf(command + pos, " %[A-Z]", third);
          if (thirdMatches == 0 || strlen(third) != DEPT_LEN) {
            printf("Invalid command\n\n");
          }
          else {
            //First sort courses by ID
            sortCourses(catalog, idComp);
            //Print out courses that contain the department
            listCourses(catalog, listTest, third, NULL);
          }
        }

        //If the command is "list timeslot <days> <time>"
        else if (secondMatches && (strcmp(second, "timeslot") == 0)) {
          char third[strlen(command)]; //Contains days
          char fourth[strlen(command)]; //Contains time
          sscanf(command + pos, "%s %s", third, fourth);
          if (((strcmp(third, "MW") != 0) && (strcmp(third, "TH") != 0))
              || ((strcmp(fourth, "8:30") != 0) && (strcmp(fourth, "10:00") != 0) && (strcmp(fourth, "11:30") != 0) 
              && (strcmp(fourth, "1:00") != 0) && (strcmp(fourth, "2:30") != 0) && (strcmp(fourth, "4:00") != 0))) {
            
            printf("Invalid command\n\n");
          }
          else {
            //First sort courses by ID
            sortCourses(catalog, idComp);
            //Then print courses with the given days and timeslot
            listCourses(catalog, listTest, third, fourth);
          }
        }

        //If the command is "list schedule"
        else if (secondMatches && (strcmp(second, "schedule") == 0)) {
          //First sort the courses
          sortCourses(schedule, scheduleComp);
          //Print all courses in schedule
          listCourses(schedule, listTest, NULL, NULL);
        }

        //If the command is anything else after "list"
        else {
          printf("Invalid command\n\n");
        }
      }


      //If the command is "add <dept> <number>"
      else if (matches && (strcmp(first, "add") == 0)) {
        //If the schedule is already at capacity, we don't want to do any of this
        if (!(schedule->capacity == schedule->count)) {
          char dept[strlen(command)]; //the department to add
          int number = 0; //the number to add
          sscanf(command + pos, "%s %d", dept, &number);
          bool found = false;
          //Loop through the catalog to find the requested course
          bool invalid = false;
          for (int i = 0; i < catalog->count; i++) {
            //Test if this course is the one
            if (strcmp(catalog->list[i]->dept, dept) == 0 && catalog->list[i]->number == number) {
              //If it is the right one, run a test to see if it is already in the schedule, or if the timeslot is already taken.
              // bool invalid = false;
              for (int j = 0; j < schedule->count; j++) {
                //If the current course in the schedule equals the target course, or if the current course has the same timeslot as the desired course.
                if (((strcmp(schedule->list[j]->dept, catalog->list[i]->dept) == 0) && (schedule->list[j]->number == catalog->list[i]->number))
                    || ((strcmp(schedule->list[j]->time, catalog->list[i]->time) == 0) && (strcmp(schedule->list[j]->days, catalog->list[i]->days) == 0))) { //idComp(schedule->list[j], catalog->list[i]) || scheduleComp(schedule->list[i], catalog->list[j])) { //Problem here
                  printf("Invalid command\n\n");
                  invalid = true;
                }
              }
              //If no duplicates were found, we are good to add it.
              if (!invalid) {
                schedule->list[schedule->count] = catalog->list[i];
                schedule->count += 1;
                printf("\n");
                found = true;
              }
            }
          }
          if (!found && !invalid) {
            printf("Invalid command\n\n");
          }
        }
        //Invalid if the schedule is at capacity
        else {
          printf("Invalid command\n\n");
        }
      }

      //If the command is "drop <dept> <number>"
      else if (matches && (strcmp(first, "drop") == 0)) {
        char dept[strlen(command)]; //the department to add
        int number = 0; //the number to add
        sscanf(command + pos, "%s %d", dept, &number);

        bool found = false;
        for (int i = 0; i < schedule->count; i++) {
          //If the current course in the schedule equals the target course, remove it
          if ((strcmp(schedule->list[i]->dept, dept) == 0) && (schedule->list[i]->number == number)) {
            schedule->list[i] = NULL;
            // schedule->count -= 1;
            found = true;
            sortCourses(schedule, scheduleComp);
            schedule->count -= 1;
            printf("\n");
          }
        }
        if (!found) {
          printf("Invalid command\n\n");
        }
      }
      //If the command is "list calendar" for extra credit
      else if (matches && (strcmp(first, "calendar") == 0)) {
        //Need an array for automated looping
        char timeStrings[NUM_TIMES][MAX_TIME_LEN + 1] = {
          "8:30", 
          "10:00",
          "11:30",
          "1:00",
          "2:30",
          "4:00"
        };
        //Print header
        printf("%12s%9s%9s%9s\n", "Mon", "Tue", "Wed", "Thu");

        //Loop through the rows (the 6 different times)
        for (int i = 0; i < NUM_TIMES; i++) {
          //Print the time string
          printf("%5s", *(timeStrings + i));
          //Loop through the columns (the 4 different days)
          for (int j = 0; j < NUM_DAYS; j++) {
            bool found = false;
            //Header space
            printf("  ");
            //Loop through the schedule to see if we have one that has the same time and day.
            for (int k = 0; k < schedule->count; k++) {
              char curDays[DAYS_LEN + 1];
              //If the day is even (j is 0 or 2), it's monday and wednesday, if odd, tuesday and thursday.
              if (j % 2 == 0) {
                strcpy(curDays, "MW");
              }
              else {
                strcpy(curDays, "TH");
              }
              if (strcmp(schedule->list[k]->days, curDays) == 0 && strcmp(schedule->list[k]->time, *(timeStrings + i)) == 0) {
                printf("%s %d", schedule->list[k]->dept, schedule->list[k]->number);
                found = true;
              }
            }
            //If we didn't find one, just print seven spaces as placeholder
            if (!found) {
              printf("       ");
            }
          }
          //Print a new line after each row
          printf("\n");
        }
        //Print a new line after the whole calendar
        printf("\n");
      }
      //If the command is NULL (we reached EOF) or is "quit" then we quit
      else if (command == NULL || strcmp(first, "quit") == 0) {
        quit = true;
      }

      //If the command is anything else, it's invalid
      else {
        printf("Invalid command\n\n");
      }
    }
    else {
      quit = true;
      free(temp);
    }
  }
  freeCatalog(catalog);
  // freeCatalog(schedule);
  free(schedule->list);
  free(schedule);

  return EXIT_SUCCESS;
}
