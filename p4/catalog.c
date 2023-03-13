typedef struct 
{
  char *dept;
  int number;
  char *days;
  char *time;
  char *name;
} Course;

typedef struct
{
  Course *list;
  int count;
  int capacity;
} Catalog;

Catalog *makeCatalog()
{
  Catalog *catalog = (Catalog *)malloc(sizeof(Catalog));
  catalog.list = malloc(5 * sizeof(Course));
  catalog.count = 0;
  catalog.capacity = 5;
  return catalog;
}

void freeCatalog(Catalog *catalog) 
{
  free(catalog.list);
  free(catalog);
}