#include "B.h"
#include "A.h"

A::A() : num_(0) { B *ptb = new B();ptb->funb();}
void A::funa1(B* b) {
    b->funb1(this);



    // 使用类 B 的成员变量或函数需要在实现文件中 #include "B.h"
}
void A::funa2() {

}
B A::b1class() {
    return B();
}
