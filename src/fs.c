#include <stdio.h>
#include "fs.h"

void fs_init(FILE *fs, int block_count)
{
  // init allocation table
  int alloc_table_buffer[block_count];
  for (int i = 0; i < block_count; i++)
    alloc_table_buffer[i] = 0;

  // write allocation table to file system
  rewind(fs);
  fwrite(alloc_table_buffer, sizeof(int), block_count, fs);
  fseek(fs, sizeof(Block), SEEK_SET);

  // init inodes
  // Inode inodes_buffer[]
}

FILE *create_fs(int block_count)
{
}

// fs_read_block, fs_write_block