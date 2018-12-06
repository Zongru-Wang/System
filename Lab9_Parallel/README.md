# Lab 9 Parallel Programming

We have discovered that if we want to write parallel software, our compilers are not yet capable of figuring out our intentions and automatically parallelizing our code. We have however explored how a tool like OpenMP can be used to provide hints and try to make code run in parallel by utilizing threads. In today's lab we are going to work with the OpenMP library using special parallelism #pragma statements.

# Motivation

Writing code that can run in parallel is important for reasons of [performance](http://www.gotw.ca/publications/concurrency-ddj.htm) and [reducing power consumption](https://en.wikipedia.org/wiki/Dennard_scaling). In languages like C (C++, Rust, etc.)  parallel programming is a real thing that people are using today, so we should keep up with the times! We have previously explored this in our artists homework and lab.

## Part 1 -- Finding your machines specs

* Type `lscpu` on the terminal to find out how many cpus you have.
* You can additionally find some information from the kernel by:
  * cd `cd /sys/devices/system/cpu/cpu0/cache/`
  * then `cd index0` and run `cat coherency_line_size`
    * This gives us a report of how big the cacheline size is.
  * Progamattically, you may be able to query `sysconf (_SC_LEVEL1_DCACHE_LINESIZE)` for example to find your cache line size.
    * [sysconf man page](http://man7.org/linux/man-pages/man3/sysconf.3.html)
    * [Stack overflow article](https://stackoverflow.com/questions/794632/programmatically-get-the-cache-line-size)

Note, if you are curious about your GPUs on Linux: You can try on the terminal: `lspci` (or look under Systems/Preferences/Hardware Information.)

## Part 2 - OpenMP

Today we are going to primarily work on a fork-join parallelism tasks. We are going to be using OpenMP, which is a mature libray that will help transform our serial code into parallel code.

### Task 1 - OpenMP

#### Example 1 - Hello World

Let's first do a little hello world to make sure OpenMP is setup and running properly. The thing to note is that we will have to include OpenMP as a compiler flag to make sure the library is properly linked in.

```c
// A basic hello world with OMP
// Compile with: gcc omp1.c -o omp1
#include <stdio.h>
#include <omp.h>

int main(){
  
  // Create our pragma, and then within curly braces
  // run OpenMP on this structuerd block.
  #pragma omp parallel
  {
      int ID = omp_get_thread_num();
      printf("hello (%d)\n",ID);
      printf(" world(%d)\n",ID);
  }

  return 0;
}

```

Go ahead and run the program with `./omp1`.

**Discuss with your partner and answer:** *answer in a sentence here, what your output is, and whether you expected it to be as such.*

Our output is a series of disordered "hello" and "world", with the thread ID in no particular order either. 
It makes sense that there is no order or structure in the output since we are doing parallel programing. 


#### Example 2 - For-loops

Loops are a common structure that can be looked at for potential parallelism. We must know the exact number of iterations for this to run however, in order for it to be successful.

```c
// gcc -std=c99 -fopenmp omp2.c -o omp2
#include <stdio.h>
#include <omp.h>

int main(){

  // Attempt to parallelize this block of code
  #pragma omp parallel
  {
    // Parallel-for loop
    #pragma omp for
    for(int n=0; n <100; ++n){
      printf(" %d",n);
    }
  }
  return 0;
}
```

**Discuss with your partner and answer:** 
Since we are doing the for-loop in pararell and this will run in dis-order.
Each thread was being langched in different order at the same time, and the order is random. So the result of the for loop 
will become disorder. 

#### Example 3 - Synchronization

The previous example does a nice job of spawning many threads that print off the thread id. However, we do not have any information about how many threads were launched within our parallel-for loop. Let's go ahead and record this information, by storing the number of threads launched. In addition, we will also add some synchronization (i.e. using the barrier pattern) to print the number of threads. The barrier pattern waits for all active threads to arrive, and then proceeds.

```c
// gcc -std=c99 -fopenmp omp3.c -o omp3
#include <stdio.h>
#include <omp.h>

int main(){
   int nthreads;

  // Attempt to parallelize this block of code
  #pragma omp parallel
  {
    // Parallel-for loop
    #pragma omp for
    for(int n=0; n <100; ++n){
      printf(" %d",n);
    }
    // Master thread waits
    #pragma omp barrier
    if(omp_get_thread_num()==0){
        nthreads = omp_get_num_threads();
    }
  }

  printf("\nSolved problem with %d threads\n",nthreads);
 
  return 0;
}

```

#### Example 4 - Fibonacci Sequence

For our first example, take a look at the following code which generates a number in the [fibonacci sequence](https://en.wikipedia.org/wiki/Fibonacci_number).

```c
// This program computes the fibonacci sequence.
// Compile with: gcc omp4.c -o omp4

#include <stdio.h>

int fib_recursive(int n){
  // base case
  if(n < 2){
   return 1;
  }
  // Accumulate our result 
  return fib_recursive(n-1)+fib_recursive(n-2);
}


int main(){
  
  // Computes the 45th number(n+1) in the fibonacci sequence
  printf("%d ",fib_recursive(40));
  printf("\n");
  
  return 0;
}
```
**Run the program above**: With `time ./omp4`

So the question now is, with this algorithm is there any potential parallelism? Well, in our current implementation, not so much. We need to transform our algorithm slightly, so we can remove data dependency.

Take a look below and see how OpenMP can be used to separate work into different tasks.

```c
// A new snippet
// Compile with: gcc -std=c11 -fopenmp omp4.c -o omp4

int fib_recursive(int n){
  // base case
  if(n < 2){
   return 1;
  }
  // Some shared variables
  int x,y;

  // Accumulate our result
  #pragma omp task shared(x) 
  x = fib_recursive(n-1);
  #pragma omp task shared(y)
  y = fib_recursive(n-2);
  #pragma omp taskwait
  return x + y;
}
```

**Run the program above**: With `time ./omp4`

Note that you may not see any performance gain--why?

**Discuss with your partner and answer:** *answer in a sentence here, why there may not be any performance gain here*
In both ways, we are doing the recurcive call and in second way, even if we call two recursive parelly, we still need to wait the x to be calculated and adds it to y. Which is the very same way as the first way. So, there is no performance gain.
 For the worth case, it will worse than the first way. 

#### Example 5 - Computing PI 3.1415....

You may remember that we watched a [video](https://www.youtube.com/watch?v=FQ1k_YpyG_A&list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG&index=6) on computing PI. Let's go ahead and type in this code, first in serial, and then you can parallelize it. Again, this is a nice example, because you can check that your solution does indeed add up to PI.

```c
// gcc -std=c11 -fopenmp omp5.c -o omp5
#include <stdio.h>

static long num_steps = 100000;
double step;

int main(){
  int i;
  double x, pi, sum = 0.0;
  
  step = 1.0/(double)num_steps;
  for(i =0; i < num_steps; i++){
    x = (i+0.5)*step;
    sum = sum+ 4.0/(1.0+x*x);
  }
  pi = step * sum;
  
  printf("PI = %f\n", pi);
 
  return 0;
}

```

Now we are going to try to solve this problem in parallel.

In general, this is a type of [Reduction](http://www.drdobbs.com/architecture-and-design/parallel-pattern-7-reduce/222000718) algorithm, in that we are chunking our problem and solving pieces of it, and then rebuilding the result.

**Discuss with your partner and answer:** *What is a strategy for solving this problem? Try to avoid false sharing by adding the amount of padded bits needed programmatically*

We watched and followed the video, the strategy is use num_threads and PAD to calculate the different part and sum them together so that we can parallelly cauculate the PI and in the end use the sum to get the result. 

**Now implement in omp5.c your strategy and time it:** Implement your strategy and fill out the table below with how much time it takes per thread.

Note: You can revisit [Tim Mattson's video](https://www.youtube.com/watch?v=OuzYICZUthM&list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG&index=7) if you get stuck.

<table>
  <tbody>
    <tr>
      <th>1 thread(ms)</th>
      <th>2 threads(ms)</th>
      <th>8 threads(ms)</th>          
    </tr>
    <tr>
      <td>4.033 </td>
      <td>2.020 </td>
      <td>0.502 </td>
    </tr>   
  </tbody>
</table>

#### Example 6 - Quick Sort (+0.5 bonus)

Do a little bit of research with your partner to understand [quick sort](https://en.wikipedia.org/wiki/Quicksort). Implement a parallel version of quick sort in omp6.c sorting 10000 randomly generated numbers. A nice sample pdf of [Quick Sort](https://www.openmp.org/wp-content/uploads/sc16-openmp-booth-tasking-ruud.pdf) is provided if you get stuck.

![alt text](https://upload.wikimedia.org/wikipedia/commons/6/6a/Sorting_quicksort_anim.gif "Quicksort from wikipedia animation")



## Lab Deliverable

1. Complete Part 2, task 1 and commit your 5 OpenMP examples to the repository.
      * Modify and implement the parallel solutions to: omp1.c omp2.c omp3.c omp4.c omp5.c
2. (Optional) For a 0.5 point bonus on this lab, try to implement quicksort.

## More Resources to Help

* The following guide provides some insight into using OpenMP. 
  * https://bisqwit.iki.fi/story/howto/openmp/#ParallelConstruct 
  * Lawrence Livermore National Labroratory https://computing.llnl.gov/tutorials/openMP/exercise.html 
  * Tim's video series https://www.youtube.com/watch?v=nE-xN4Bf8XI&list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG&index=1

* The following resources may be useful to observe for those interested in GPGPU programming
   * OpenCL for MacOS https://developer.apple.com/opencl/
   * The following guide will get you started for CUDA: https://devblogs.nvidia.com/even-easier-introduction-cuda/
   * The following guide will get you started for OpenCL: https://www.eriksmistad.no/getting-started-with-opencl-and-gpu-computing/
   
* For fun
  * Parallel Programming Patterns: http://www.drdobbs.com/architecture-and-design/parallel-pattern-7-reduce/222000718
  * See other Parallel Programming libraries in C/C++ here: https://www.youtube.com/watch?v=y0GSc5fKtl8

## Going Further

- Investigate OpenMP's `#pragma omp simd`
