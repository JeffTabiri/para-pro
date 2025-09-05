
# Start application helloWorld with four process.

trapezoidal: trapezoidal.o
	mpirun -n 2 trapezoidal.o

trapezoidal.o: trapezoidal.c
	mpicc trapezoidal.c -o trapezoidal.o

helloWorld: helloWorld.o
	mpirun -n 4 helloWorld.o

helloWorld.o: helloWorld.c
	mpicc helloWorld.c -o helloWorld.o

clean:
	rm -f helloWorld.o trapezoidal.o