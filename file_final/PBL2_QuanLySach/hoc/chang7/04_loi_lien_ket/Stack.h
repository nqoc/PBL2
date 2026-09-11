// =====================================================================
//  BT7.4 - BAN SAI: chi KHAI BAO o .h, dinh nghia nam o Stack.cpp
//  Bien dich se BAO LOI LIEN KET. Do la muc dich cua bai nay.
// =====================================================================
#ifndef STACK_H
#define STACK_H

template <class T>
class Stack {
private:
    T   duLieu[100];
    int dinh;
public:
    Stack();                    // chi khai bao
    void push(const T& x);      // chi khai bao
    T    pop();                 // chi khai bao
    bool rong() const;          // chi khai bao
};

#endif
