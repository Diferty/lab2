#include <iostream>
#include "Sequence.hpp"
#include "BitSequence.hpp"

using namespace std;
template<typename T, int CT>
void print(const Sequence<T, CT>& seq, const string& name) 
{
    cout << name << ": [";
    for (int i = 0; i < seq.GetLength(); ++i) 
    {
        cout << seq.Get(i);
        if (i != seq.GetLength() - 1) cout << ", ";
    }
    cout << "]\n";
}

void printBits(const BitSequence& bs, const string& name) {
    cout << name << ": [";
    for (int i = 0; i < bs.GetLength(); ++i) 
    {
        cout << (bs.Get(i) ? '1' : '0');
        if (i != bs.GetLength() - 1) cout << ", ";
    }
    cout << "]\n";
}

int main() 
{
    cout << "Mutable Sequence\n";
    Sequence<int, 0> seq;
    seq.Append(10);
    seq.Append(20);
    seq.Append(30);
    print(seq, "Append(10,20,30)");
    seq.Prepend(5);
    print(seq, "Prepend(5)");
    seq.InsertAt(99, 2);
    print(seq, "InsertAt(99, 2)");

    cout << "Immutable Sequence\n";
    Sequence<int, 0> orig;
    orig.Append(1);
    orig.Append(2);
    orig.Append(3);
    print(orig, "Оригинал");

    Sequence<int, 0> newSeq = orig.AppendImm(4);
    print(newSeq, "Оригинал.AppendImm(4)");
    print(orig, "Оригинал (не изменился)");

    cout << "BitSequence\n";
    BitSequence bs1, bs2;
    bs1.Append(1); bs1.Append(0); bs1.Append(1); bs1.Append(1); 
    bs2.Append(1); bs2.Append(1); bs2.Append(0);                  
    printBits(bs1, "bs1");
    printBits(bs2, "bs2");
    BitSequence andRes = bs1.And(bs2);
    printBits(andRes, "bs1 & bs2");
    BitSequence orRes = bs1.Or(bs2);
    printBits(orRes, "bs1 | bs2");
    BitSequence xorRes = bs1.Xor(bs2);
    printBits(xorRes, "bs1 ^ bs2");
    BitSequence notRes = bs1.Not();
    printBits(notRes, "~bs1");
    return 0;
}