#pragma once
#include "exceptions.hpp"

template <typename T>
class LinkedList {
private:
    struct Elem {
        T value;
        Elem* prev;
        Elem* next;
        Elem(const T& val, Elem* p = nullptr, Elem* n = nullptr) : value(val), prev(p), next(n) {}
    };
    Elem* head;
    Elem* tail;
    int length;

    Elem* getElem(int index) const {
        if (index < 0 || index >= length) throw IndexOutOfRange("LinkedList::getElem");
        Elem* cur = head;
        for (int i = 0; i < index; ++i) cur = cur->next;
        return cur;
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(T* items, int count) : head(nullptr), tail(nullptr), length(0) 
    {
        for (int i = 0; i < count; ++i) Append(items[i]);
    }

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), length(0) 
    {
        Elem* cur = other.head;
        while (cur) 
        { 
            Append(cur->value); cur = cur->next; 
        }
    }

    ~LinkedList() 
    {
        while (head) 
        { 
            Elem* tmp = head; head = head->next; delete tmp; 
        }
    }

    T GetFirst() const 
    {
        if (length == 0) throw EmptyContainerError("LinkedList::GetFirst");
        return head->value;
    }

    T GetLast() const 
    {
        if (length == 0) throw EmptyContainerError("LinkedList::GetLast");
        return tail->value;
    }

    T Get(int index) const 
    { 
        return getElem(index)->value; 
    }

    LinkedList<T> GetSubList(int startIndex, int endIndex) const 
    {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
        {
            throw IndexOutOfRange("GetSubList");
        }
        LinkedList<T> sub;
        Elem* cur = getElem(startIndex);
        for (int i = startIndex; i <= endIndex; ++i) 
        {
            sub.Append(cur->value);
            cur = cur->next;
        }
        return sub;
    }

    int GetLength() const 
    { 
        return length; 
    }

    void Append(T item) 
    {
        Elem* newElem = new Elem(item, tail, nullptr);
        if (tail) tail->next = newElem;
        else head = newElem;
        tail = newElem;
        ++length;
    }

    void Prepend(T item) 
    {
        Elem* newElem = new Elem(item, nullptr, head);
        if (head) head->prev = newElem;
        else tail = newElem;
        head = newElem;
        ++length;
    }

    void InsertAt(T item, int index) 
    {
        if (index < 0 || index > length) throw IndexOutOfRange("InsertAt");
        if (index == 0) Prepend(item);
        else if (index == length) Append(item);
        else 
        {
            Elem* nextElem = getElem(index);
            Elem* prevElem = nextElem->prev;
            Elem* newElem = new Elem(item, prevElem, nextElem);
            prevElem->next = newElem;
            nextElem->prev = newElem;
            ++length;
        }
    }

    LinkedList<T> Concat(const LinkedList<T>& other) const 
    {
        LinkedList<T> result = *this;
        Elem* cur = other.head;
        while (cur) 
        {
            result.Append(cur->value);
            cur = cur->next;
        }
        return result;
    }
};