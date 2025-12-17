#include <stdio.h>
#include <string.h>
#include "fs.h"

void fs_init(FILE *fs, int block_count)
{
  // init allocation table
  int alloc_table_buffer[block_count];
  memset(alloc_table_buffer, 0, block_count * sizeof(int));
  // write allocation table to disk
  rewind(fs);
  fwrite(alloc_table_buffer, sizeof(int), block_count, fs);
  fseek(fs, sizeof(Block), SEEK_SET);

  // init inodes
  Inode inodes_buffer[INODES_PER_BLOCK];
  int k = 0; // number of inodes initialized so far
  for (int i = 0; i < INODE_BLOCK_COUNT; i++)
  {
    for (int j = 0; j < INODES_PER_BLOCK; j++)
    {
      if (k < INODE_COUNT)
      {
        initInode(&inodes_buffer[j]); // initialize valid inodes
        k++;
      }
      else
      {
        initInode(&inodes_buffer[j]); // initialize remaining slots as empty
      }
    }
    // write inodes block to disk
    fseek(fs, (i + 1) * sizeof(Block), SEEK_SET); // +1: block 0 = allocation table
    fwrite(inodes_buffer, sizeof(Inode), INODES_PER_BLOCK, fs);
  }
  fseek(fs, FIRST_DATA_BLOCK * sizeof(Block), SEEK_SET);
}

FILE *create_fs(int block_count)
{
  FILE *fs = fopen("disk.bin", "wb+");
  fs_init(fs, block_count);
  return fs;
}

void printFileSystem(FILE *fs, int block_count)
{
  // --- Print Allocation Table ---
  printf("Allocation Table:\n");
  int alloc_table_buffer[block_count];
  read_alloc_table(fs, alloc_table_buffer, block_count);
  for (int i = 0; i < block_count; i++)
    printf("%d ", alloc_table_buffer[i]);
  printf("\n\n");

  // --- Print Inodes ---
  printf("Inodes (Meta Data):\n");
  Inode inode_buffer[INODES_PER_BLOCK];
  int total_inode_blocks = INODE_BLOCK_COUNT;
  int k = 0; // number of inodes printed so far

  for (int i = 0; i < total_inode_blocks; i++)
  {
    // Seek to the correct block: block 0 = allocation table
    fseek(fs, (i + 1) * sizeof(Block), SEEK_SET);
    fread(inode_buffer, sizeof(Inode), INODES_PER_BLOCK, fs);

    for (int j = 0; j < INODES_PER_BLOCK && k < INODE_COUNT; j++)
    {
      printf("File name: %s, First Block: %d, FileSizeInBlocks: %d, FileSizeInRecords: %d, g_mode: %d, i_mode: %d\n",
             inode_buffer[j].filename,
             inode_buffer[j].first_block_index,
             inode_buffer[j].block_count,
             inode_buffer[j].record_count,
             inode_buffer[j].g_mode,
             inode_buffer[j].i_mode);
      k++;
    }
  }
}

void initInode(Inode *inode)
{
  strcpy(inode->filename, "");
  inode->first_block_index = -1;
  inode->block_count = 0;
  inode->record_count = 0;
  inode->g_mode = -1;
  inode->i_mode = -1;
}

void read_alloc_table(FILE *fs, int alloc_table_buffer[], int block_count)
{
  rewind(fs);
  fread(alloc_table_buffer, sizeof(int), block_count, fs);
  fseek(fs, sizeof(Block), SEEK_SET);
}
