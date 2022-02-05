#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iomanip>
#include <forward_list>

#include "omp.h"

int main()
{
    std::size_t size;
    std::cout << "Enter number of elements: ";
    std::cin >> size;

    std::int32_t k;
    std::cout << "Enter number of threads: ";
    std::cin >> k;

    std::cout << "\n1 task: \n";

    auto data = std::vector<std::int32_t>();
    data.reserve(size);

    auto histogram = std::vector<int32_t>(size, 0);

#pragma omp parallel num_threads(k)
    {
#pragma omp for
        for (std::size_t i = 0; i < size; ++i) {
            std::int32_t rand_value = static_cast<std::int32_t>(rand()) % size;
            data.emplace_back(rand_value);

            if ((i == 0) || (data[i] > data[i - 1])) {
#pragma omp critical
                std::cout << "[" << i << "] -> "
                           << data[i] << '\n';
            }
        }
    }

    if (data.empty())
    {
        throw std::runtime_error("array doesn't have any data");
    }

    double sum = 0;
    for(auto v : data)
    {
        sum += v;
    }
    const auto avrg_value = sum / data.size();

    std::cout << "\n2 task:"
                 "\naverage value: " << std::setprecision(3) << avrg_value;

    auto cir_buffer = std::forward_list<double>();

#pragma omp parallel num_threads(k)
    {
#pragma omp for
        for (std::size_t i = 0; i < size; ++i) {
            auto value = data[i];
            if (value > avrg_value)
            {
                cir_buffer.push_front(value);
            }

            if (i != (size - 1))
            {
                std::int32_t h_index = std::abs(data[i] - data[i + 1]);
#pragma omp atomic
                histogram[h_index]++;
            }
        }
    }

    std::cout << "\nforward-list: ";
    for (auto v : cir_buffer)
    {
        std::cout << std::setprecision(3) << v << ' ';
    }

    std::cout << "\n\n3 task:"
                 "\nhistogram:\n";
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << '[' << i << ", " << (1 + i) << "] -> " << histogram[i] << '\n';
    }

    return 2;
}