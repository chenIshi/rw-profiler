# rw-profiler
Simple profiler for tracing IO instructions

A simple interpositioning tool for profiling IO usage (basically `read` and `write` system call).

# User guide
1. `Make` to generate dynamic link library (by default installed in /tmp)  
2. `Make test` to test with a simple clone program

# Reference
1. [你所不知道的 C 語言：動態連結器篇](https://hackmd.io/@sysprog/c-dynamic-linkage)

# To-do
1. Improve testbench versatility
	For example, test the usage of other file IO API like `fgets`'s usage on system calls