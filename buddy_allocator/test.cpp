#include "buddy_allocator.h"
#include <cstdio>
#include <vector>
#include <list>

int main() {
  const size_t block = sizeof(int);
  const int level = 8;
  char buffer[block << level];
  buddy_pool pool(level, block, &buffer);

  buddy_allocator<int> alloc(&pool);
  {
    std::vector<int,buddy_allocator<int>> v(alloc);
    std::list<int,buddy_allocator<int>> l(alloc);
    for ( int i = 0; i < 10; ++i ) {
      v.push_back(i);
      l.push_back(i);
      pool.dump();
      printf("\n");
    }
    for ( int i = 0; i < 5; ++i ) {
      l.pop_front();
      pool.dump();
      printf("\n");
    }
    printf("\n vector : ");
    for ( int item : v ) printf("%3d", item);
    printf("\n list   : ");
    for ( int item : l ) printf("%3d", item);
  }
  printf("\n");
  pool.dump();
}
