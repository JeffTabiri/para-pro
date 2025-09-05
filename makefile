mpi: main.o
	mpirun -n 4 main.o

main.o: main.c
	mpicc main.c -o main.o

clean:
	rm -f main.o