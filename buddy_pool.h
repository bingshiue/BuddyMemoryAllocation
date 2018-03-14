#ifndef BUDDY_POOL_H_
#define BUDDY_POOL_H_

#include "buddy.h"
#include <mutex>
#include <cstdint>
#include <cstddef>

class buddy_pool {
private:
  std::mutex    mutex_;  // mutex
  buddy*        buddy_;  // Buddy
  std::uint8_t* buffer_; // memory pool
  std::size_t   block_;  // bytes per block

public:
  buddy_pool(int level, std::size_t block, void* pool) 
    : buffer_(static_cast<uint8_t*>(pool)), block_(block) {
    buddy_ = buddy_new(level);
  }

  ~buddy_pool() {
    buddy_delete(buddy_);
  }

  void* allocate(std::size_t n) {
    std::lock_guard<std::mutex> guard(mutex_);
    int nblock = static_cast<int>((n + block_ -1U)/block_);
    int offset = buddy_alloc(buddy_, nblock);
    return offset < 0 ? nullptr : buffer_ + offset * block_;
  }

  void deallocate(void* ptr) {
    std::lock_guard<std::mutex> guard(mutex_);
    int offset = static_cast<int>((static_cast<uint8_t*>(ptr) - buffer_)/block_);
    buddy_free(buddy_, offset);
  }

  void dump(void (*func)(const char*)) const { 
    buddy_dump_f(buddy_, func); 
  }

  void dump() const { 
    buddy_dump(buddy_);
  }

  static std::size_t required(int level, std::size_t block) {
    return block << level;
  }

  static buddy_pool* make(int level, std::size_t block, void* pool) {
    return new buddy_pool(level, block, pool);
  }

};

#endif
