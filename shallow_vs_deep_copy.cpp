#include <iostream>

class ShallowTest {
public:
    int* data;

    ShallowTest() {
        data = new int(1); // Allocates sizeof(int) (typically 4 bytes) on heap
    }

    ~ShallowTest() {
        delete data;
    }
};

class DeepTest {
public:
    int* data;

    DeepTest(int val = 0) {
        data = new int(val);
    }

    // Custom Deep Copy Constructor
    DeepTest(const DeepTest& other) {
        data = new int(*other.data);
    }

    // Copy Assignment Operator
    DeepTest& operator=(const DeepTest& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }

    ~DeepTest() {
        delete data;
    }
};

int main() {
    // 1. Deep Copy Test (Safe)
    {
        DeepTest d1(42);
        DeepTest d2 = d1; // Calls deep copy constructor

        std::cout << "DeepTest Success:\n";
        std::cout << "d1 addr: " << d1.data << " | val: " << *d1.data << "\n";
        std::cout << "d2 addr: " << d2.data << " | val: " << *d2.data << "\n";
    } // d1 and d2 destruct cleanly here

    // 2. Shallow Copy Test (Will trigger double-free crash)
    {
        std::cout << "\nRunning ShallowTest (expecting crash)...\n";
        ShallowTest s1;
        ShallowTest s2 = s1; // Default shallow copy
    } // Destructors collide on s1.data / s2.data

    return 0;
}
