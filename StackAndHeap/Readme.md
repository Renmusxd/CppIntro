# Stack and Heap

Consider memory to be a long array of writable locations, each one has an address (which is basically an index). We will ignore a lot of details for how this is actually accomplished in favor of the important bits. Memory is broken into many segments, we will here focus on the stack and the heap. Take a section of length L, the OS will defined the stack as starting from L and growing downwards towards 0, the heap lives near 0 and expands as needed. 

## The Stack
Consider a function call, and what it needs in order to be run, at very least it will need space to store the variables it requires in memory... but it can't use the same space in memory every time it's called, since it may call itself recursively and need to have multiple versions of the same variables stored at the same time, or else multiple threads may call it at the same time and they shouldn't have to fight over data! So to store not only the data, but also the series of calls which lead up to the call we use _the stack_.

Consider the following code:

```
void bar() {
	int x;
	int y;

	foo();
}

void foo() {
	int x;
	int y;
	int z;
}
```

When we first call `bar` it will make enough space for two integers, we will call this its stack frame and will represent that as so:

```
---- Memory ----
bar:    int x
		int y <-- sp
```

Now when `bar` calls `foo`, `foo` will use the last space occupied by `bar` (called the stack pointer, `sp`) to start its own stack frame, it also updates `sp`:

```
---- Memory ----
bar:    int x
		int y
foo:    int x
		int y
		int z <-- sp
```

Now when `foo` returns it will set `sp` to its old value, thus allowing the data it wrote to be overwritten by whoever may be called next.

## The Heap

Now we can store anything whose size we know in advance, and with a few tricks we can store things whose size we can calculate as well. But what about things that grow and whose size we do not know? For that we use the heap and a process known as _allocation_. The heap is basically just a pile of free memory to be used however you want, when you request a spot of it of a given size the OS will respond with a pointer, which is just an address/index as mentioned before. This process of finding free space and returning it, and the process of freeing that space when it's no longer in use (because we no longer have the "undo `sp`" trick from before) can be expensive, we will see in the code `stack_and_heap.cpp` proof of this. It can also be very useful, since the data doesn't live on the stack it's not in danger of being overwritten by a returning function call (as a matter of fact you should _never_ return pointers to things on the stack. It's fine to call functions with the pointers though, so long as they don't save them for later).

## Examples:

I wrote three basic examples of how to make some data for consumption, one uses a heap based technique where it makes some data on the heap, uses it, then frees it. The next one uses the stack, it makes some data on the stack on demand. Finally, the best option, makes the space for the largest possible set of data outside the loop then reuses it as needed.

When run on my machine I got the following:
```
Heap 196.433ms.
Stack 91.3031ms.
Arena 63.9888ms.
```

So the heap was half as fast as the stack, and a third as fast as the arena.