#include <chrono>
#include <ctime>
#include <iostream>

using namespace std::chrono;


// Some function that uses the data, it doesn't matter what it is really.
int process(int* arr, int len) {
	for (int i = 0; i<len; i++){
		// This stops the compiler from being really smart
		// and getting rid of the array entirely!
		// Try making it just +i to see.
		arr[i] = ((int)(long)arr) + i;
	}
	int tot = 0;
	for (int i = 0; i<len; i++){
		tot += i;
	}
	return tot;
}

int heap(int n, int l) {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	int acc = 0;
	for (int i = 0; i < l; i++) {
		int m = n + (i%n);
		// Get some space on the heap.
		// This is what happens under the hood when you
		// make a std::vector btw, so while you should
		// use those it won't make it much better.
		int* arr = new int[m];
		acc += process(arr, m);
		delete[] arr;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	
	duration<double, std::milli> stack_span = t2 - t1;
	std::cout << "Heap " << stack_span.count() << "ms." << std::endl;
	return acc;
}

int stack(int n, int l) {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	int acc = 0;
	for (int i = 0; i < l; i++) {
		int m = n + (i%n);
		// Get some space on the stack.
		int arr[m];
		acc += process(arr, m);
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	
	duration<double, std::milli> stack_span = t2 - t1;
	std::cout << "Stack " << stack_span.count() << "ms." << std::endl;
	return acc;
}

int arena(int n, int l) {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	// As big as we will need. This can be stack or heap, since it's not in
	// the loop it really doesn't matter much.
	int arena[2*n - 1];	

	int acc = 0;
	for (int i = 0; i < l; i++) {
		// Reuse the existing arena.
		int m = n + (i%n);
		acc += process(arena, m);
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	
	duration<double, std::milli> stack_span = t2 - t1;
	std::cout << "Arena " << stack_span.count() << "ms." << std::endl;
	return acc;
}

int main(int argc, char *argv[]) {
	const int N = 10;
	const int L = 10000000;

	heap(N,L);
	stack(N,L);
	arena(N,L);
}