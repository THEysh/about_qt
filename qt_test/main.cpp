#include <iostream>
#include <functional>
#include <vector>

class Signal {
public:
    typedef std::function<int (float a)> Slot;

    void connect(const Slot& slot) {
        m_slots.push_back(slot);
    }

    void emit(float a) {
        for (const auto& slot : m_slots) {
            slot(a);
        }
    }
private:
    std::vector<Slot> m_slots;
};

int main() {
    Signal signal;
    auto lambda = [](float a)->int { std::cout << "Lambda function called" << std::endl; return a;};
    auto lambda2 = [](float a)->int { std::cout << "Lambda function called" << std::endl; return a;};
    signal.connect(lambda);
    signal.connect(lambda2);

    signal.emit(12.4);

    return 0;
}
