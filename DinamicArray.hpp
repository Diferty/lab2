#pragma once
#include "Exceptions.hpp"

template <typename T>
class DynamicArray {
private:
    T* data;
    int size;

public:
    DynamicArray(T* items, int count) : size(count) {
        data = new T[count];
        for (int i = 0; i < count; ++i) data[i] = items[i];
    }

    explicit DynamicArray(int size) : size(size) {
        data = new T[size]();
    }

    DynamicArray(const DynamicArray& other) : size(other.size) {
        data = new T[size];
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }

    ~DynamicArray() {
        delete[] data;
    }

    T Get(int index) const {
        if (index < 0 || index >= size) throw IndexOutOfRange("DynamicArray::Get");
        return data[index];
    }

    void Set(int index, T value) {
        if (index < 0 || index >= size) throw IndexOutOfRange("DynamicArray::Set");
        data[index] = value;
    }

    int GetSize() const {
        return size;
    }

    void Resize(int newSize) {
        T* newData = new T[newSize]();
        int copyCount = (newSize < size) ? newSize : size;
        for (int i = 0; i < copyCount; ++i) newData[i] = data[i];
        delete[] data;
        data = newData;
        size = newSize;
    }
};