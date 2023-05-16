//#include <iostream>
//
//void callbackFunc(int result) {
//    std::cout << "Result: " << result << std::endl;
//}
//
//void callbackFunc2(int result) {
//    std::cout << "Result: " << result << std::endl;
//}
//void doSomething(int a, int b, void (*callback)(int)) {
//    int result = a + b;
//    callback(result);
//}
//
//int main() {
//    doSomething(11, 2, callbackFunc2);
//    doSomething(1, 2, callbackFunc);
//    return 0;
//}