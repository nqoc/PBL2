// =====================================================================
//  BT7.4 - Doc loi lien ket khi dat dinh nghia template vao .cpp
//
//  BUOC 1 - chay ban SAI:
//      g++ -std=c++17 main.cpp Stack.cpp -o sai.exe
//    -> undefined reference to `Stack<int>::push(int const&)'
//       (loi o khau LIEN KET, khong phai bien dich)
//
//  BUOC 2 - doi dong #include duoi day sang "Stack_dung.h", roi:
//      g++ -std=c++17 main.cpp -o dung.exe   &   dung.exe
//    -> chay binh thuong, va KHONG can Stack.cpp nua
//
//  VI SAO?
//    Moi tep .cpp duoc dich DOC LAP. Stack.cpp khong he biet ai can Stack<int>,
//    nen no khong sinh ban nao ca - trong no chi co CAI KHUON.
//    main.cpp thi can Stack<int>::push nhung khong co dinh nghia trong tay.
//    Ket qua: ham do khong ton tai o dau -> undefined reference.
//    Dat het vao .h thi main.cpp co ca khuon lan dinh nghia -> tu sinh duoc.
// =====================================================================
#include "Stack.h"           // <<< DOI THANH "Stack_dung.h" O BUOC 2
#include <iostream>
using namespace std;

int main() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    cout << "pop het: ";
    while (!s.rong()) cout << s.pop() << " ";
    cout << "\n(neu ban thay dong nay -> ban dang dung Stack_dung.h)\n";
    return 0;
}
