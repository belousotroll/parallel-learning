#include <iostream>
#include <mpi.h>

int main(int argc, char ** argv)
{
    int * elements = nullptr;
    int num_elements;

    int * chunk_buffer = nullptr;
    int chunk_capacity;

    int global_sum = 0;

    int num_threads;
    int thread_num;

    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &num_threads);
    MPI_Comm_rank(MPI_COMM_WORLD, &thread_num);

    if (thread_num == 0)
    {
        std::cout << "Enter number of elements: ";
        std::cin >> num_elements;

        chunk_capacity = num_elements / num_threads;
        if (num_elements % num_threads)
        {
            chunk_capacity++;
        }

        std::cout << "chunk capacity: " << chunk_capacity << '\n';

        const int cap_elements = num_threads * chunk_capacity;

        elements = new int[cap_elements];

        for (int i = 0; i < num_elements; i++)
        {
            elements[i] = rand() % num_elements;
        }

        std::cout << "elements: ";
        for (int i = 0; i < num_elements; ++i)
        {
            std::cout << elements[i] << ' ';
        }
        std::cout << "\n";

        for (int i = num_elements; i < cap_elements; i++)
        {
            elements[i] = 0;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Bcast(&chunk_capacity, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&num_elements,   1, MPI_INT, 0, MPI_COMM_WORLD);

    chunk_buffer = new int[chunk_capacity];
    MPI_Scatter(elements, chunk_capacity, MPI_INT,
                chunk_buffer, chunk_capacity, MPI_INT,
                0, MPI_COMM_WORLD);

    int chunk_size =
        (num_elements >= (chunk_capacity * (thread_num + 1)))
            ? chunk_capacity
            : num_elements - chunk_capacity * thread_num;

    int local_sum = 0;
    for (int i = 0; i < chunk_size; ++i) {
        local_sum += chunk_buffer[i];
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (thread_num == 0)
    {
        std::cout << "global sum: " << global_sum << '\n';
        delete[] elements;
    }

    delete[] chunk_buffer;

    MPI_Finalize();

    return 0;
}