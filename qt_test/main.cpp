#include <iostream>

// 父类
class Parent {
public:
    virtual ~Parent() {}
    virtual void foo() = 0; // 纯虚函数

    // 创建子类对象的工厂方法
    static Parent* createChild(int type);

    // 其他父类的成员函数
};

// 子类1
class Child1 : public Parent {
public:
    void foo() override {
        std::cout << "Child1" << std::endl;
    }

    // 其他子类1的成员函数
};

// 子类2
class Child2 : public Parent {
public:
    void foo() override {
        std::cout << "Child2" << std::endl;
    }

    // 其他子类2的成员函数
};

// 在父类中实现创建子类对象的工厂方法
Parent* Parent::createChild(int type) {
    Parent* child = nullptr;

    switch (type) {
        case 1:
            child = new Child1();
            break;
        case 2:
            child = new Child2();
            break;
        default:
            // 错误处理
            break;
    }

    return child;
}

int main() {
    Parent* child1 = Parent::createChild(1);
    child1->foo(); // 通过父类指针调用子类1的函数

    Parent* child2 = Parent::createChild(2);
    child2->foo(); // 通过父类指针调用子类2的函数

    delete child1;
    delete child2;

    return 0;
}
