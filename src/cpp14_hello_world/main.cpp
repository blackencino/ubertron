//------------------------------------------------------------------------------
// Copyright (c) 2011-2014 Christopher Jon Horvath. All rights reserved.
//------------------------------------------------------------------------------

#include <iostream>
#include <memory>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
auto recursive_deduced_return_type(int i) {
    if (i == 1) {
        return i;
    } else {
        return recursive_deduced_return_type(i-1) + i;
    }
}

//------------------------------------------------------------------------------
void test_recursive_deduced_return_type() {
    auto val = recursive_deduced_return_type(7);
    cout << "val = " << val << typeid(val).name() << endl;
}

//------------------------------------------------------------------------------
void testGenericLambdas() {
    auto add_arguments = [](auto x, auto y) { return x + y; };

    auto val1 = add_arguments(1, 2);
    auto val2 = add_arguments(1.f, 2);
    auto val3 = add_arguments(1., 2);
    auto val4 = add_arguments(1., 2.f);

    cout << "val1 = " << val1 << typeid(val1).name() << endl
        << "val2 = " << val2 << typeid(val2).name() << endl
        << "val3 = " << val3 << typeid(val3).name() << endl
        << "val4 = " << val4 << typeid(val4).name() << endl;
}

//------------------------------------------------------------------------------
void testBinaryLiteralsAndDigitSeparators() {
    int val = 0b11110000;
    cout << "Output mask: "
        << 0b1000'0001'1000'0000
        << endl;
    cout << "Proposed salary: $"
        << 300'000.00
        << endl;
}

//------------------------------------------------------------------------------
template <typename T>
constexpr T pi = T(3.1415926535897932385);

void testVariableTemplate() {
    cout << "int pi (for indiana): " << pi<int> << endl
        << "float pi: " << pi<float> << endl
        << "double pi: " << pi<double> << endl;
}

//------------------------------------------------------------------------------
void test_make_unique() {
    auto unique_string = make_unique<string>("Hello world");
    cout << "Unique string: " << *unique_string << endl;
}

//------------------------------------------------------------------------------
int main(int, char**) {
    test_recursive_deduced_return_type();
    testGenericLambdas();
    testBinaryLiteralsAndDigitSeparators();
    testVariableTemplate();
    test_make_unique();
    return 0;
}