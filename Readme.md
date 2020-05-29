# C++ Efficiency stuff

This is meant to be a short set of examples for how to get the most out of your code, they should give some background into how computers work as well as offer tips for how to leverage that knowledge to speed up your code.

I'm not yet sure what I'll cover.

Reading order:

1. StackAndHeap

# Final note:

Be careful benchmarking your code, compilers can be very smart, and often guarentee the same output regardless of optimizations, but don't guarentee how they get there. If you're timing things and suddenly it doesn't match what you're expecting, it's possible the compiler found a way to completely omit a loop, or moved a function call after the thing that was supposed to time how long the function took. Benchmarking is hard, so spend a little time thinking about how to get it right the first time.