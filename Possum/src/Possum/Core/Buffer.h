#pragma once

#include <cstdlib>
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

        int i = 0;
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

            data = (char*)malloc(newCapacity);
            data = newData;
            capacity = newCapacity;
        }

        void Copy(const char* inData)
        {
            size_t len = strlen(inData);
            if (size + len + 1 > capacity) {
                size_t newCapacity = (size + len + 1) * 2;
                Resize(newCapacity);
            }

            strcpy(data, inData);
            size += len;
        }

        // This should be called every time you edit the buffer
        void ShouldResize()
        {
            size_t len = strlen(data);
            if (len >= capacity)
            {
                Resize((len + 1) * 2);
            }

            size = len;
        }

        char* GetData() { return data; }

		bool HasData()
		{
			if (strlen(data) > 0)
				return true;
			return false;
		}

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
