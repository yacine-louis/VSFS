#ifndef RECORD_H
#define RECORD_H

#include <stdbool.h>
#define NAME_MAX_LEN 30

typedef struct
{
  int client_id;
  char name[NAME_MAX_LEN];
  int age;
  float balance;
} Client;

typedef struct {
  Client data;
  bool deleted; // used for logical deletion
} Record;




#endif