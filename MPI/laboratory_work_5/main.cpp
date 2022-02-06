#include <iostream>
#include <mpi.h>

int main(int argc, char ** argv)
{
    int * elements = nullptr;
    int num_elements;

    int * chunk_buffer = nullptr;
    int chunk_capacity;

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

    chunk_buffer = new int[chunk_capacity];
    MPI_Scatter(elements, chunk_capacity, MPI_INT,
                chunk_buffer, chunk_capacity, MPI_INT,
                0, MPI_COMM_WORLD);

    int chunk_size =
        (num_elements >= (chunk_capacity * (thread_num + 1)))
            ? chunk_capacity
            : num_elements - chunk_capacity * thread_num;

    int sum = 0;
    for (int i = 0; i < chunk_size; ++i) {
        sum += chunk_buffer[i];
    }

    if (thread_num != 0) {
        std::cout << "sending: [ " << thread_num << " --> " << 0 << " ]\n";
        MPI_Send(&sum, 1, MPI_INT,
                 0,
                 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (thread_num == 0) {
        for (int i = 1; i < num_threads; ++i) {
            std::cout << "receive: [ " << thread_num << " <-- " << i << " ]\n";
            int sum_buffer;
            MPI_Recv(&sum_buffer, 1, MPI_INT,
                     i,
                     0,
                     MPI_COMM_WORLD,
                     &status);
            sum += sum_buffer;
        }

        std::cout << "sum: " << sum << '\n';
    }

    delete[] elements;

    MPI_Finalize();

    return 0;
}