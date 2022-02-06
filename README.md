## Сборка проекта

```sh
$ mkdir build .
$ cd build
$ cmake ..
$ make
```

## Инструкция по запуску

Для запуска лабораторных работ из секции `MPI` необходимо использовать приложение `mpiexec`, доступное в пакете `mpich`.
```sh
$ sudo apt update
$ sudo apt install mpich -y
```
Пример сборки и запуска:

```sh
$ mkdir build .
$ cd build
$ cmake ..
$ make
$ cd MPI/laboratory_work_5
$ mpiexec -n 4 ./laboratory_work_5
```
Параметр `-n 4` задает количество исполяемых потоков.

