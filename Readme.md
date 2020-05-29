# C++ Efficiency stuff

This is meant to be a short set of examples for how to get the most out of your code, they should give some background into how computers work as well as offer tips for how to leverage that knowledge to speed up your code.

I'm not yet sure what I'll cover.

Reading order:

1. (This)
2. StackAndHeap

# Compiling and optimizations

If you want your code to go fast, one good starting place it to tell the compiler that's what you want. Using a compiler `CC` (which will typically be `clang++` or `g++`):

`CC --std=c++11 -O3 -Wall -g source.cpp -o executable`

Here `-O3` tells the compiler to enable all optimizations, and this will be good for most purposes. If you need to strectch a little further you can enable `AVX` operations on your machine (which can speed up very specific code by 8 to 16 times!) using `-march=native`. This binary may cause "Illegal instruction" errors if you move it to another machine, so keep that in mind. It's good for math heavy processing where you have long lists of numbers that need to be added or multiplied etc...

Be careful benchmarking your code, compilers can be very smart, and often guarentee the same output regardless of optimizations, but don't guarentee how they get there. If you're timing things and suddenly it doesn't match what you're expecting, it's possible the compiler found a way to completely omit a loop, or moved a function call after the thing that was supposed to time how long the function took. Benchmarking is hard, so spend a little time thinking about how to get it right the first time.