#ifndef FS_H
#define FS_H

#include <record.h>

#define RECORDS_PER_BLOCK 3
#define INODE_COUNT 10 /* files count */

#define BLOCK_HEADER_SIZE (2 * sizeof(int)) /* next_block + record_count */
#define INODES_PER_BLOCK ((sizeof(Block) - BLOCK_HEADER_SIZE) / sizeof(Inode))
#define INODE_BLOCK_COUNT ((INODE_COUNT + INODES_PER_BLOCK - 1) / INODES_PER_BLOCK)
#define FIRST_DATA_BLOCK (INODE_BLOCK_COUNT + 1)

#define FILENAME_MAX_LEN 32

typedef struct
{
  Record records[RECORDS_PER_BLOCK];
  int record_count;
  int next_block;
} Block;

typedef struct
{
  char filename[FILENAME_MAX_LEN - 1];
  int first_block_index;
  int block_count;
  int record_count;
  int g_mode; // global organization (0 = contiguous, 1 = chained)
  int i_mode; // internal organization (0 = unsorted, 1 = sorted)
} Inode;

typedef struct
{
  int block_index;
  int record_index;
} RecordPosition;

void fs_init(FILE *fs, int block_count);
FILE *create_fs(int block_count);
void printFileSystem(FILE *fs, int block_count);
void initInode(Inode *inode);
void read_alloc_table(FILE *MS, int alloc_table_buffer[], int block_count);

#endif