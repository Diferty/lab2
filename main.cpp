#include <iostream>
#include "Sequence.hpp"
#include "BitSequence.hpp"
#include <windows.h> 
// ¬спомогательна€ функци€ дл€ печати любой последовательности (шаблонна€)
template <typename T, int CT>
void Print(const Sequence<T, CT>& seq) {
    std::cout << "[";
    for (int i = 0; i < seq.GetLength(); ++i) {
        std::cout << seq.Get(i);
        if (i != seq.GetLength() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

// —пециализаци€ дл€ печати битовой последовательности (выводит 0/1)
void Print(const BitSequence& seq) {
    std::cout << "[";
    for (int i = 0; i < seq.GetLength(); ++i) {
        std::cout << (seq.Get(i) ? '1' : '0');
        if (i != seq.GetLength() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main() {
    SetConsoleCP(1251);          // устанавливаем кодировку ввода
    SetConsoleOutputCP(1251);    // устанавливаем кодировку вывода
    std::cout << "========== ƒемонстраци€ Mutable Sequence (на основе DynamicArray) ==========\n";
    int arr1[] = {1, 2, 3, 4, 5};
    Sequence<int, 0> seqArray(arr1, 5);   // используем DynamicArray (тип 0)
    std::cout << "»сходна€: "; Print(seqArray);

    seqArray.Append(6);
    std::cout << "After Append(6): "; Print(seqArray);

    seqArray.Prepend(0);
    std::cout << "After Prepend(0): "; Print(seqArray);

    seqArray.InsertAt(99, 2);
    std::cout << "After InsertAt(99,2): "; Print(seqArray);

    std::cout << "\n========== Immutable Sequence (на основе DynamicArray) ==========\n";
    int arr2[] = {10, 20, 30};
    Sequence<int, 0> imm(arr2, 3);
    std::cout << "»сходна€ (immutable оригинал): "; Print(imm);
    auto imm2 = imm.AppendImm(40);
    std::cout << "imm.AppendImm(40) вернула: "; Print(imm2);
    std::cout << "ќригинал не изменилс€: "; Print(imm);

    std::cout << "\n========== BitSequence ==========\n";
    BitSequence bs1;
    bs1.Append(Bit(1));
    bs1.Append(Bit(0));
    bs1.Append(Bit(1));
    bs1.Append(Bit(1));
    std::cout << "bs1 = "; Print(bs1);

    BitSequence bs2;
    bs2.Append(Bit(1));
    bs2.Append(Bit(1));
    bs2.Append(Bit(0));
    std::cout << "bs2 = "; Print(bs2);

    BitSequence andRes = bs1.And(bs2);
    std::cout << "bs1 & bs2 = "; Print(andRes);

    BitSequence orRes = bs1.Or(bs2);
    std::cout << "bs1 | bs2 = "; Print(orRes);

    BitSequence xorRes = bs1.Xor(bs2);
    std::cout << "bs1 ^ bs2 = "; Print(xorRes);

    BitSequence notRes = bs1.Not();
    std::cout << "~bs1 = "; Print(notRes);

    std::cout << "\n========== ƒополнительно: Concat и GetSubsequence ==========\n";
    Sequence<int, 0> a(arr1, 3);  // [1,2,3]
    Sequence<int, 0> b(arr2, 2);  // [10,20]
    a.Concat(b);  // mutable Concat
    std::cout << "a.Concat(b) -> a стало: "; Print(a);

    auto sub = a.GetSubsequence(1, 3);
    std::cout << "a.GetSubsequence(1,3) -> "; Print(sub);

    std::cout << "\n========== BitSequence: immutable версии ==========\n";
    BitSequence bs3 = bs1.AppendImm(Bit(0));
    std::cout << "bs1.AppendImm(0) -> нова€: "; Print(bs3);
    std::cout << "bs1 осталась: "; Print(bs1);

    return 0;
}