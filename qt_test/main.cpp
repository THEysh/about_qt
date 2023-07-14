#include <iostream>
// 基类
class Base {
public:
    virtual void print() {
        std::cout << "Base::print()" << std::endl;
    }
};

// 派生类
class Derived : public Base {
public:
    void print(double value) {
        std::cout << "Derived::print(int): " << value << std::endl;
    }
};

// 抽象产品类
class Product {
public:
    virtual void use() = 0;
};

// 具体产品类 A
class ConcreteProductA : public Product {
public:
    void use() override {
        std::cout << "Using ConcreteProductA" << std::endl;
    }
};

// 具体产品类 B
class ConcreteProductB : public Product {
public:
    void use() override {
        std::cout << "Using ConcreteProductB" << std::endl;
    }
};

// 工厂类
class Factory {
public:
    // 创建产品的方法
    virtual Product* createProduct() = 0;
};

// 具体工厂类 A，用于创建产品 A
class ConcreteFactoryA : public Factory {
public:
    Product* createProduct() override {
        return new ConcreteProductA();
    }
};

// 具体工厂类 B，用于创建产品 B
class ConcreteFactoryB : public Factory {
public:
    Product* createProduct() override {
        return new ConcreteProductB();
    }
};

int main() {
    // 使用具体工厂类 A 创建产品
    Factory* factoryA = new ConcreteFactoryA();
    Product* productA = factoryA->createProduct();
    productA->use();

    // 使用具体工厂类 B 创建产品
    Factory* factoryB = new ConcreteFactoryB();
    Product* productB = factoryB->createProduct();
    productB->use();

    delete factoryA;
    delete productA;

    delete factoryB;
    delete productB;

    return 0;
}
