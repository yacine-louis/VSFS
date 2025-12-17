#ifndef FS_H
#define FS_H

#include <record.h>

#define FILENAME_MAX_LEN 32

typedef struct
{
  Record* records;
  int record_count;
  int next;
} Block;

typedef struct
{
  char filename[FILENAME_MAX_LEN];
  int first_block;
  int block_count;
  int record_count;
  int g_mode; // global organization (0 = contiguous, 1 = chained)
  int i_mode; // internal organization (0 = unsorted, 1 = sorted)
} Inode;

typedef struct
{
  int block_index;
  int record_index;
} Position;

#endif