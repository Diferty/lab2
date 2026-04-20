#pragma once

#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "exceptions.hpp"

template <typename T, int ContainerType = 0>
class Sequence 
{
    private:
        DynamicArray<T>* arr;
        LinkedList<T>* list;  

        void copyFrom(const Sequence& other) 
        {
            if (ContainerType == 0)
            {
                arr = new DynamicArray<T>(*other.arr);
            }
            else
            {
                list = new LinkedList<T>(*other.list);
            }
        }
        void clear() 
        {
            if (ContainerType == 0)
            {
                delete arr;
            }
            else
            {
                delete list;
            }
        }
    public:
        Sequence() 
        {
            if (ContainerType == 0)
            {
                arr = new DynamicArray<T>(0);
            }
            else
            {
                list = new LinkedList<T>();
            }
        }
        Sequence(T* items, int count) 
        {
            if (ContainerType == 0)
            {
                arr = new DynamicArray<T>(items, count);
            }
            else
            {
                list = new LinkedList<T>(items, count);
            }
        }
        Sequence(const Sequence& other) 
        {
            copyFrom(other);
        }
        ~Sequence() {
            clear();
        }
        Sequence& operator=(const Sequence& other) 
        {
            if (this != &other) 
            {
                clear();
                copyFrom(other);
            }
            return *this;
        }
        T GetFirst() const 
        {
            if (ContainerType == 0)
            {
                return arr->GetFirst();
            }
            else
                return list->GetFirst();
        }
        T GetLast() const 
        {
            if (ContainerType == 0)
            {
                return arr->GetLast();
            }
            else
            {
                return list->GetLast();
            }
        }
        T Get(int index) const 
        {
            if (ContainerType == 0)
            {
                return arr->Get(index);
            }
            else
            {
                return list->Get(index);
            }
        }
        int GetLength() const 
        {
            if (ContainerType == 0)
            {
                return arr->GetSize();
            }
            else
            {
                return list->GetLength();
            }
        }
        Sequence<T, ContainerType> GetSubsequence(int startIndex, int endIndex) const {
            Sequence<T, ContainerType> result;
            if (ContainerType == 0) {
                DynamicArray<T> subArr = arr->GetSubArray(startIndex, endIndex);
                int len = subArr.GetSize();
                T* temp = new T[len];
                for (int i = 0; i < len; ++i)
                    temp[i] = subArr.Get(i);
                result = Sequence<T, ContainerType>(temp, len);
                delete[] temp;
            } 
            else 
            {
                LinkedList<T> subList = list->GetSubList(startIndex, endIndex);
                int len = subList.GetLength();
                T* temp = new T[len];
                for (int i = 0; i < len; ++i)
                    temp[i] = subList.Get(i);
                result = Sequence<T, ContainerType>(temp, len);
                delete[] temp;
            }
            return result;
        }

        void Append(T item) 
        {
            if (ContainerType == 0)
            {
                arr->Append(item);
            }
            else
            {
                list->Append(item);
            }
        }
        void Prepend(T item) 
        {
            if (ContainerType == 0)
            {
                arr->Prepend(item);
            }
            else
            {
                list->Prepend(item);
            }
        }
        void InsertAt(T item, int index) 
        {
            if (ContainerType == 0)
            {
                arr->InsertAt(item, index);
            }
            else
            {
                list->InsertAt(item, index);
            }
        }
        void Concat(const Sequence<T, ContainerType>& other) 
        {
            for (int i = 0; i < other.GetLength(); ++i)
                Append(other.Get(i));
        }

        Sequence<T, ContainerType> AppendImm(T item) const 
        {
            Sequence<T, ContainerType> copy = *this;
            copy.Append(item);
            return copy;
        }
        Sequence<T, ContainerType> PrependImm(T item) const 
        {
            Sequence<T, ContainerType> copy = *this;
            copy.Prepend(item);
            return copy;
        }
        Sequence<T, ContainerType> InsertAtImm(T item, int index) const 
        {
            Sequence<T, ContainerType> copy = *this;
            copy.InsertAt(item, index);
            return copy;
        }
        Sequence<T, ContainerType> ConcatImm(const Sequence<T, ContainerType>& other) const 
        {
            Sequence<T, ContainerType> copy = *this;
            copy.Concat(other);
            return copy;
        }
};