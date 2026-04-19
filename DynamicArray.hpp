#pragma once
#include "exceptions.hpp"

template <typename T>
class DynamicArray {
private:
    T* data;
    int size;

public:
    // Конструкторы
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

    // Базовые методы
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

    // Новые методы для единообразия с LinkedList
    T GetFirst() const {
        if (size == 0) throw EmptyContainerError("DynamicArray::GetFirst");
        return Get(0);
    }

    T GetLast() const {
        if (size == 0) throw EmptyContainerError("DynamicArray::GetLast");
        return Get(size - 1);
    }

    void Append(T item) {
        Resize(size + 1);
        Set(size - 1, item);
    }

    void Prepend(T item) {
        Resize(size + 1);
        for (int i = size - 1; i > 0; --i)
            Set(i, Get(i - 1));
        Set(0, item);
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > size) throw IndexOutOfRange("DynamicArray::InsertAt");
        Resize(size + 1);
        for (int i = size - 1; i > index; --i)
            Set(i, Get(i - 1));
        Set(index, item);
    }

    DynamicArray<T> GetSubArray(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex >= size || startIndex > endIndex)
            throw IndexOutOfRange("DynamicArray::GetSubArray");
        int newLen = endIndex - startIndex + 1;
        DynamicArray<T> sub(newLen);
        for (int i = 0; i < newLen; ++i)
            sub.Set(i, Get(startIndex + i));
        return sub;
    }

    void Concat(const DynamicArray<T>& other) {
        int oldSize = size;
        Resize(size + other.GetSize());
        for (int i = 0; i < other.GetSize(); ++i)
            Set(oldSize + i, other.Get(i));
    }
};