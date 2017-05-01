#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

template<long long n, typename enable_if<n >= 0>::type* = nullptr>
constexpr unsigned long long factorial() {
    return n * factorial<n - 1>();
}

template<long long n, typename enable_if<n < 0>::type* = nullptr>
constexpr unsigned long long factorial() {
    static_assert(n > 0, "Could not be evaluated for negative numbers");
    return 0;
}

template<>
constexpr unsigned long long factorial<0LL>() {
    return 1;
}

template<long long n, long long k, typename enable_if<n >= k>::type* = nullptr>
constexpr unsigned long long C_n_k() {
    static_assert(n != 0 || k != 0, "Could not be evaluated for n=0, k=0");
    return integral_constant<long long, factorial<n>() / factorial<n - k>() / factorial<k>()>::value;
}

template<long long n, long long k, typename enable_if<n < k>::type* = nullptr>
constexpr unsigned long long C_n_k() {
    static_assert(n >= 0 && k >= 0, "Could not be evaluated for negative numbers");
    return 0;
}


int main() {
    cout << C_n_k<5, 4>() << endl;
    return 0;
}
