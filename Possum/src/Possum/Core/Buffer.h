#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Ferret/Core/Log.h"

#include "ErrorThrows.h"

namespace Possum
{
    struct Buffer
    {
    private:
        char* data;
        size_t size;
        size_t capacity;
    public:
        Buffer(size_t initialCapacity)
        {
            data = (char*)malloc(initialCapacity);
            if (data == nullptr)
            {
                free(data);
                throw NullExeption("Could not malloc buffer data!");
            }

            size = 0;
            capacity = initialCapacity;
        }

        void Resize(size_t newCapacity)
        {
            char* newData = (char*)realloc(data, newCapacity);
            if (newData == nullptr)
            {
                throw NullExeption("Could not resize buffer!");
            }

            data = newData;
            capacity = newCapacity;
        }

        void Copy(const char* inData)
        {
            size_t str_len = strlen(inData);
            if (size + str_len + 1 > capacity) {
                size_t newCapacity = (size + str_len + 1) * 2;
                Resize(newCapacity);
            }

            strcpy(data, inData);
            size += str_len;
        }

        char* GetData() { return data; }
        size_t& GetSize() { return size; }

        char operator[](size_t index)
        {
            if (index >= size)
                throw OutOfRangeException("index is out of range!");
            return data[index];
        }

        void FreeBuffer()
        {
            free(data);
        }
    };
}
