// =====================================================================
//  BT7.4 - BAN DUNG: khai bao VA dinh nghia deu nam trong .h
//  Khong co Stack_dung.cpp di kem. Do la chuan cho moi lop template.
// =====================================================================
#ifndef STACK_DUNG_H
#define STACK_DUNG_H

template <class T>
class Stack {
private:
    T   duLieu[100];
    int dinh;
public:
    Stack();
    void push(const T& x);
    T    pop();
    bool rong() const;
};

// ---- dinh nghia NGAY TRONG FILE NAY ----
template <class T> Stack<T>::Stack() : dinh(0) {}
template <class T> void Stack<T>::push(const T& x) { duLieu[dinh++] = x; }
template <class T> T    Stack<T>::pop()            { return duLieu[--dinh]; }
template <class T> bool Stack<T>::rong() const     { return dinh == 0; }

#endif
