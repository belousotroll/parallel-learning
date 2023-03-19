#include <iostream>
#include <chrono>
#include <cmath>
#include <iomanip>

#include "omp.h"

void serial_function(int, int);
void parallel_function(int, int);
void print_array(char, long double *, std::size_t);

int main()
{
    std::int32_t x;
    std::cout << "Enter x: ";
    std::cin >> x;

    std::int32_t n;
    std::cout << "Enter n: ";
    std::cin >> n;

    serial_function(x, n);
    parallel_function(x, n);

    return 0;
}

void serial_function(int x, int n)
{
    auto * a = new long double[n];
    auto * b = new long double[n];
    auto * c = new long double[n];

    auto start_time = std::chrono::system_clock::now();

    a[0] = 1.0 / x;
    for (auto i = 1; i < n; ++i) {
        a[i] = std::sin(x * i);
    }

    b[0] = 1.0 / x;
    for (auto i = 1; i < n; ++i) {
        b[i] = (a[i - 1] + x) / i;
    }

    for (auto i = 0; i < n; ++i) {
        c[i] = i * (a[(n - 1) - i] + b[i]) / 2.0;
    }

    for (auto i = 1; i < n; i++) {
        b[i] = (a[i] + c[(n - 1) - i]) / i;
    }

    auto finish_time = std::chrono::system_clock::now();

#ifdef OUTPUT
    print_array('a', a, n);
    print_array('b', b, n);
    print_array('c', c, n);
#endif

    std::cout << "End of serial section, execution time is\t"
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                  finish_time - start_time
              ).count() << " ms\n";

    delete[] a;
    delete[] b;
    delete[] c;
}

void parallel_function(int x, int n)
{
    auto * a = new long double[n];
    auto * b = new long double[n];
    auto * c = new long double[n];

    auto start_time = std::chrono::system_clock::now();

    a[0] = 1.0 / x;
#pragma omp parallel for
    for (auto i = 1; i < n; i++) {
        a[i] = std::sin(x * i);
    }

    b[0] = 1.0 / x;
#pragma omp parallel for
    for (auto i = 1; i < n; i ++) {
        b[i] = (a[i - 1] + x) / i;
    }

#pragma omp parallel for
    for (auto i = 0; i < n; i++) {
        c[i] = i * (a[(n - 1) - i] + b[i]) / 2.0;
    }

#pragma omp parallel for
    for (auto i = 1; i < n; i++) {
        b[i] = (a[i] + c[(n - 1) - i]) / i;
    }

    auto finish_time = std::chrono::system_clock::now();

#ifdef OUTPUT
    print_array('a', a, n);
    print_array('b', b, n);
    print_array('c', c, n);
#endif

    std::cout << "End of parallel section, execution time is\t"
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                  finish_time - start_time
              ).count() << " ms\n";

    delete[] a;
    delete[] b;
    delete[] c;
}

void print_array(char name_of_array, long double * array, std::size_t array_size)
{
    std::cout << name_of_array << ": ";
    for (auto array_ptr = array; array_ptr < array + array_size; array_ptr++) {
        std::cout << *array_ptr << '\t';
    }
    std::cout << '\n';
}
