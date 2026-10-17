#include <iostream>

class BaseClass {
private:
    virtual void func() = 0;
};

class DerivedClass : public BaseClass {
    // Private in derived class as well
    void func() override {
        std::cout << "Function overridden by derived class!" << std::endl;
    }
};

int main() {
    // 1. Allocate a real instance so the vptr is initialized
    DerivedClass derivedObj;

    // reinterpret_cast<T>(x) => Treat x as a T
    // 2. Point to the start of the object (where vptr resides)
    void*** vptr_location = reinterpret_cast<void***>(&derivedObj);

    // 3. Dereference once to reach the vtable (array of function pointers)
    void** vtable = *vptr_location;

    // 4. Extract the function pointer at index 0
    void* raw_func_addr = vtable[0];

    // 5. Define a function pointer signature accepting 'this' pointer
    typedef void (*FuncPtr)(void*); // Accepts a generic memory address
    FuncPtr hijacked_func = reinterpret_cast<FuncPtr>(raw_func_addr);

    // 6. Invoke the private virtual function directly via memory offset
    hijacked_func(&derivedObj);

    return 0;
}
