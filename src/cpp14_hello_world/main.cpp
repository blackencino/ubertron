//------------------------------------------------------------------------------
// Copyright 2014 Christopher Jon Horvath
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <typeinfo>
#include <array>
#include <type_traits>

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
void test_generic_lambdas() {
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
void test_binary_literals_and_digit_separators() {
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

//------------------------------------------------------------------------------
void test_variable_templates() {
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
void test_tuple_addressing() {
    tuple<string, string, int> t("foo", "bar", 7);
    int i = get<int>(t);        // i == 7
    int j = get<2>(t);          // Same as before: j == 7
    // string s = get<string>(t);  // Compile-time error due to ambiguity
}

//------------------------------------------------------------------------------
class [[deprecated]] flaky {
};

//------------------------------------------------------------------------------
[[deprecated("Consider using something other than cranky")]]
int cranky() {
   return 0;
}

//------------------------------------------------------------------------------
void test_deprecated() {
    auto f = flaky{};
    auto i = cranky();
}

//------------------------------------------------------------------------------
void test_lambda_capture() {
    auto ptr = make_unique<int>(10);
    auto lambda = [value = move(ptr)] { return *value; };
    cout << "Captured lambda value: " << lambda() << endl;
}

//------------------------------------------------------------------------------
constexpr int fibonacci(int i) {
    if (i == 0) {
        return 0;
    } else if (i == 1) {
        return 1;
    } else {
        return fibonacci(i-1) + fibonacci(i-2);
    }
}

//------------------------------------------------------------------------------
void test_better_constexpr() {
    auto fib_array = array<float,fibonacci(4)>{};
    cout << "Size of constexpr fibonacci array: "
        << fib_array.size() << endl
        << "Fibonacci(4): " << fibonacci(4) << endl;
}

//------------------------------------------------------------------------------
int main(int, char**) {
    test_recursive_deduced_return_type();
    test_generic_lambdas();
    test_binary_literals_and_digit_separators();
    test_variable_templates();
    test_make_unique();
    test_tuple_addressing();
    test_deprecated();
    test_lambda_capture();
    test_better_constexpr();
    return 0;
}