#pragma once
#include "Sequence.hpp"
#include <iostream>

class Bit 
{
    private:
        bool value;

    public:
        Bit(bool v = false) : value(v) {}
        Bit(int v) : value(v != 0) {}
        operator bool() const 
        { 
            return value; 
        }

        Bit operator&(const Bit& other) const 
        {
            return Bit(value && other.value); 
        }
        Bit operator|(const Bit& other) const 
        { 
            return Bit(value || other.value); 
        }
        Bit operator~() const 
        { 
            return Bit(!value); 
        }
        Bit operator^(const Bit& other) const 
        { 
            return Bit(value ^ other.value); 
        }

        friend std::ostream& operator<<(std::ostream& os, const Bit& b) {
            os << (b.value ? '1' : '0');
            return os;
        }
    };

    class BitSequence 
    {
    private:
        Sequence<Bit, 0> seq;

    public:
        BitSequence() = default;
        explicit BitSequence(const Sequence<Bit, 0>& s) : seq(s) {}
        BitSequence(const BitSequence& other) = default;

        Bit GetFirst() const 
        { 
            return seq.GetFirst(); 
        }
        Bit GetLast()  const 
        { 
            return seq.GetLast();  
        }
        Bit Get(int index) const 
        { 
            return seq.Get(index); 
        }
        int GetLength() const 
        { 
            return seq.GetLength(); 
        }

        BitSequence GetSubsequence(int start, int end) const 
        {
            BitSequence res;
            res.seq = seq.GetSubsequence(start, end);
            return res;
        }

        void Append(Bit b)   
        { 
            seq.Append(b); 
        }
        void Prepend(Bit b)  
        { 
            seq.Prepend(b); 
        }
        void InsertAt(Bit b, int index) 
        { 
            seq.InsertAt(b, index); 
        }
        void Concat(const BitSequence& other) 
        { 
            seq.Concat(other.seq); 
        }

        BitSequence AppendImm(Bit b) const 
        {
            BitSequence copy = *this;
            copy.Append(b);
            return copy;
        }
        BitSequence PrependImm(Bit b) const 
        {
            BitSequence copy = *this;
            copy.Prepend(b);
            return copy;
        }
        BitSequence InsertAtImm(Bit b, int index) const 
        {
            BitSequence copy = *this;
            copy.InsertAt(b, index);
            return copy;
        }
        BitSequence ConcatImm(const BitSequence& other) const 
        {
            BitSequence copy = *this;
            copy.Concat(other);
            return copy;
        }

        BitSequence And(const BitSequence& other) const 
        {
            BitSequence res;
            int len = std::min(GetLength(), other.GetLength());
            for (int i = 0; i < len; ++i) {
                res.Append(Get(i) & other.Get(i));
            }
            return res;
        }

        BitSequence Or(const BitSequence& other) const 
        {
            BitSequence res;
            int len = std::max(GetLength(), other.GetLength());
            for (int i = 0; i < len; ++i) 
            {
                Bit a = (i < GetLength()) ? Get(i) : Bit(false);
                Bit b = (i < other.GetLength()) ? other.Get(i) : Bit(false);
                res.Append(a | b);
            }
            return res;
        }

        BitSequence Xor(const BitSequence& other) const 
        {
            BitSequence res;
            int len = std::max(GetLength(), other.GetLength());
            for (int i = 0; i < len; ++i) 
            {
                Bit a = (i < GetLength()) ? Get(i) : Bit(false);
                Bit b = (i < other.GetLength()) ? other.Get(i) : Bit(false);
                res.Append(a ^ b);
            }
            return res;
        }

        BitSequence Not() const 
        {
            BitSequence res;
            for (int i = 0; i < GetLength(); ++i) 
            {
                res.Append(Bit(!Get(i)));
            }
            return res;
        }
        BitSequence operator&(const BitSequence& other) const 
        { 
            return And(other); 
        }
        BitSequence operator|(const BitSequence& other) const 
        { 
            return Or(other); 
        }
        BitSequence operator^(const BitSequence& other) const 
        { 
            return Xor(other); 
        }
        BitSequence operator~() const 
        { 
            return Not(); 
        }
};