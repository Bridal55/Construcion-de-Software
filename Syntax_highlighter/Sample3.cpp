#include <iostream>

class Counter {
private:
    int value;
    int step;

public:
    Counter(int start, int step) {
        this->value = start;
        this->step  = step;
    }

    void increment() { value += step; }
    void decrement() { value -= step; }
    void reset()     { value = 0; }

    bool is_positive() { return value > 0; }
    bool is_zero()     { return value == 0; }

    int get() { return value; }
};

int main() {
    Counter c(0, 5);

    c.increment();
    c.increment();
    c.increment();

    std::cout << "Value: " << c.get() << std::endl;

    if (c.is_positive() && !c.is_zero()) {
        std::cout << "Counter is positive" << std::endl;
    }

    c.reset();
    std::cout << "After reset: " << c.get() << std::endl;

    return 0;
}