// Dinh nghia dat o day -> DAY LA CHO SAI
#include "Stack.h"

template <class T> Stack<T>::Stack() : dinh(0) {}
template <class T> void Stack<T>::push(const T& x) { duLieu[dinh++] = x; }
template <class T> T    Stack<T>::pop()            { return duLieu[--dinh]; }
template <class T> bool Stack<T>::rong() const     { return dinh == 0; }
