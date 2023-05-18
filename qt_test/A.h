#ifndef A_H_
#define A_H_

// 前向声明
class B;

class A {
public:
    A();
    // 成员函数使用类 B 的头文件需要在实现文件中 #include "B.h"
    void funa1(B* b);
    void funa2();
public:
    int num_;

    B b1class();


};

#endif  // A_H_
