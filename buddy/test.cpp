#include <stdio.h>
#include "buddy.h"

int test_alloc(struct buddy* b, int sz) {
  int r = buddy_alloc(b, sz);
  printf("alloc %d (sz= %d)\n",r,sz);
  buddy_dump(b);
  return r;
}

void test_free(struct buddy* b, int addr) {
  printf("free %d\n",addr);
  buddy_free(b, addr);
  buddy_dump(b);
}

int main() {
  struct buddy* b = buddy_new(4);

  printf("--- 1. initial ----------------:\n");
  buddy_dump(b);
  printf("--- 2. A allocates 1 block ----: ");
  int mA = test_alloc(b, 1);
  printf("--- 3. B allocates 2 blocks ---: ");
  int mB = test_alloc(b, 2);
  printf("--- 4. C allocates 1 block ----: ");
  int mC = test_alloc(b, 1);
  printf("--- 5. D allocates 2 blocks ---: ");
  int mD = test_alloc(b, 2);
  printf("--- 6. B frees ----------------: ");
  test_free(b,mB);
  printf("--- 7. D frees ----------------: ");
  test_free(b,mD);
  printf("--- 8. A frees ----------------: ");
  test_free(b,mA);
  printf("--- 9. C frees ----------------: ");
  test_free(b,mC);
  printf("\n");

  buddy_delete(b);
}