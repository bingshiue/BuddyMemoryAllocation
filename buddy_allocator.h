#ifndef BUDDY_ALLOCATOR_H_
#define BUDDY_ALLOCATOR_H_

#include "buddy_pool.h"
//#include <memory>

template<typename T>
class buddy_allocator {
private:
  buddy_pool* pool_;

public:
  template<typename U> friend class buddy_allocator;
  typedef T value_type;

  buddy_allocator(buddy_pool* pool) : pool_(pool) {}

  template<typename U>
  buddy_allocator(buddy_allocator<U> const& other) : pool_(other.pool_) {}
  
 ~buddy_allocator() {}

  // value_type nŒÂ•ª‚Ì—Ìˆæ‚ðŠm•Û‚·‚é
  value_type* allocate(std::size_t n) {
    return static_cast<value_type*>(pool_->allocate(n * sizeof(value_type)));
  }

  // —Ìˆæ‚ð‰ð•ú‚·‚é
  void deallocate(void* ptr, std::size_t) {
    pool_->deallocate(ptr);
  }

  template<typename U>
  bool operator==(buddy_allocator<U> const& other) {
    return pool_ == other.pool_;
  }

  template<typename U>
  bool operator!=(buddy_allocator<U> const& other) {
    return pool_ != other.pool_;
  }

};

#endif

