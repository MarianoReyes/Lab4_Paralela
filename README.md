## Instrucciones de Compilación

### riemann.c

- gcc -o riemann riemann.c -lm
- ./riemann a b

### riemann_omp.c

- gcc -o riemann_omp riemann_omp.c -lm -fopenmp
- ./riemann_omp a b num_threads

### riemann_mpi.c

- mpicc -o riemann_mpi riemann_mpi.c -lm
- mpirun -np 4 ./riemann_mpi a b
