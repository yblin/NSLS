//
// Copyright 2011 Yangbin Lin. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// This file is part of the Code Library.
//

#ifndef UTIL_POOL_OBJECT_POOL_H_
#define UTIL_POOL_OBJECT_POOL_H_

#include <cassert>
#include <cstdlib>

#include "codelibrary/base/macros.h"

namespace cl {

/// A Simple but Efficient Object Memory Pool.
/**
 * ObjectPool is used for dynamic management of objects,
 * it can allocate and free object's memory quickly.
 *
 * The time comparison between ObjectPool and new/delete is show below:
 *                        ObjectPool       new/delete
 * 10,000,000 allocate     0.093(s)         1.609(s)
 * 10,000,000 free         0.032(s)         1.625(s)
 */
template <typename T>
class ObjectPool {
public:
    /**
     * ObjectPool is perform as a free chunk list.
     * The default size of first chunk is 1024, if user do not give it.
     */
    explicit ObjectPool(int first_chunk_size = 1024)
        : size_(0),
          head_(NULL),
          cur_chunk_(NULL),
          first_chunk_size_(first_chunk_size) {
        assert(first_chunk_size_ > 0);
        head_ = cur_chunk_ = new Chunk(first_chunk_size_);
    }

    ~ObjectPool() {
        while (head_) {
            Chunk* p = head_->next;
            delete[] head_->data;
            delete[] head_->ptr_data;
            delete head_;
            head_ = p;
        }
    }

    /**
     * Allocate a object memory from pool.
     */
    T* Allocate() {
        if (cur_chunk_->used_size == cur_chunk_->size) {
            if (cur_chunk_->next == NULL) {
                assert(cur_chunk_->size + cur_chunk_->size > 0);

                // If not enough memory, we create a new chunk, this chunk's
                // size is double of the previous one.
                Chunk *p = new Chunk(cur_chunk_->size + cur_chunk_->size);
                cur_chunk_->next = p;
                p->prev = cur_chunk_;
            }
            cur_chunk_ = cur_chunk_->next;
        }
        ++size_;
        assert(size_ >= 0); // Assert the size is not overflow.

        return cur_chunk_->ptr_data[cur_chunk_->used_size++];
    }

    /**
     * Recycle the object, by putting it back to the pool.
     * If pool is full do nothing.
     * Will assert() if object is NULL.
     */
    void Free(T* object) {
        assert(object);  // The object can not be NULL.

        if (cur_chunk_->used_size == 0) {
            if (cur_chunk_->prev == NULL) {
                return;
            }
            cur_chunk_ = cur_chunk_->prev;
        }
        --size_;
        cur_chunk_->ptr_data[--cur_chunk_->used_size] = object;
    }

    /**
     * Clear the object pool.
     */
    void clear() {
        while (head_) {
            Chunk* p = head_->next;
            delete[] head_->data;
            delete[] head_->ptr_data;
            delete head_;
            head_ = p;
        }
        size_ = 0;
        head_ = cur_chunk_ = new Chunk(first_chunk_size_);
    }

    /**
     * Current objects' size.
     */
    int size() const {
        return size_;
    }

private:
    // The chunk for ObjectPool.
    struct Chunk {
        explicit Chunk(int _size)
            : prev(NULL),
              next(NULL),
              size(_size),
              used_size(0),
              data(new T[_size]),
              ptr_data(new T*[_size]) {
            for (int i = 0; i < size; ++i) {
                ptr_data[i] = &data[i];
            }
        }

        Chunk* prev;    // The previous chunk of chunk list.
        Chunk* next;    // The next chunk of chunk list.
        int size;       // The size of chunk.
        int used_size;  // The size of used memory.
        T* data;        // The actual data pointer.
        T** ptr_data;   // The pointer to the actual data.
    };

    int size_;             // The current used size of memory pool.
    Chunk* head_;          // The head pointer of chunk list.
    Chunk* cur_chunk_;     // The current chunk.
    int first_chunk_size_; // The size of first chunk.

    DISALLOW_COPY_AND_ASSIGN(ObjectPool);
};

} // namespace cl

#endif // UTIL_POOL_OBJECT_POOL_H_
