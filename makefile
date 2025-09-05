
# Start application helloWorld with four process.
mpi helloWorld: helloWorld.o
	mpirun -n 4 helloWorld.o

helloWorld.o: helloWorld.c
	mpicc helloWorld.c -o helloWorld.o

clean:
	rm -f helloWorld.o