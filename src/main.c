#include <stdio.h>
#include "fs.h"

int main()
{
  printf("inodes per block: %d\n", INODES_PER_BLOCK);
  int block_count;

  while (1)
  {

    printf("Enter number of blocks for file system:");
    if (scanf("%d", &block_count) != 1)
    {
      // not an integer, clear the keyboard buffer
      while (getchar() != '\n')
        ;
      printf("Invalid input! enter a number.\n");
      continue;
    }
    FILE *fs = create_fs(block_count);
    if (!fs)
    {
      perror("Failed to create filesystem");
      return -1;
    }
    printFileSystem(fs, block_count);
    return 0;
  }
}