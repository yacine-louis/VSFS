#ifndef RECORD_H
#define RECORD_H

#include <stdbool.h>

#define NAME_MAX_LEN 36

typedef struct
{
  int id;
  char name[NAME_MAX_LEN - 1];
  int age;
  float balance;
} Client;

typedef struct
{
  Client data;
  bool deleted; // used for logical deletion
} Record;

#endif