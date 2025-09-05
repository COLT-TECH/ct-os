#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stddef.h>

template<typename TYPE, size_t MAX_SIZE>
class fixed_vector {
    private:
        TYPE data[MAX_SIZE];
        size_t count = 0;
    public:
        void push_back(const TYPE& item) {
            if (count < MAX_SIZE) data[count++] = item;
        }

        TYPE& operator[](size_t i) { return data[i]; }
        const TYPE& operator[](size_t i) const { return data[i]; }
        size_t size() const { return count; }
        bool empty() const { return count == 0; }

        TYPE* begin() { return data; }
        TYPE* end() { return data + count; }
};

#endif
