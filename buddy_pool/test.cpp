#define _CRT_SECURE_NO_WARNINGS
#include "buddy_pool.h"
#include <cstring>
#include <cstdio>

int main() {
  char buffer[1024];
  buddy_pool pool(4, 8, buffer);
  char* hello = (char*)pool.allocate(14);
  char* world = (char*)pool.allocate(6);
  pool.dump();
  strcpy(hello, "Hello, ");
  strcpy(world, "world");
  strcat(hello, world);
  printf("%s\n", hello);
  pool.deallocate(hello);
  pool.deallocate(world);
}
