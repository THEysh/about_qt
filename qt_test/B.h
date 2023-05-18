#ifndef B_H_
#define B_H_

#include "A.h"  // 类 A 的头文件在此处被包含
class A;
class B:A {
public:
    B();
    // 成员函数使用类 A 的头文件需要在实现文件中 #include "A.h"
    void funb1(A* a);
    void funb(){

    }
    A* b;
    int num_;
};

#endif // B_H_
