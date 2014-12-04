//------------------------------------------------------------------------------
// Copyright (c) 2011-2014 Christopher Jon Horvath. All rights reserved.
//------------------------------------------------------------------------------

#include <iostream>

using namespace std;

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

int main(int, char**) {
    testGenericLambdas();
    return 0;
}