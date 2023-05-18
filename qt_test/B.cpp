#include "A.h"
#include "B.h"

B::B() : num_(0) {}

void B::funb1(A* a) {
    // 使用类 A 的成员变量或函数需要在实现文件中 #include "A.h"
    a->num_ = num_;
}
