# Due Date: November 8, 2018 at 11:59 PM.

TODO Please edit the following information in your assignment

- Name: Zongru Wang
- How many hours did it take you to complete this assignment? 3
- Did you collaborate with any other students/TAs/Professors? Yes
- Did you use any external resources? (Cite them below)
  - Lecture slides
  - http://web.eecs.umich.edu/~aprakash/482/notes/deadlocks.pdf
- (Optional) What was your favorite part of the assignment?
- (Optional) How would you improve the assignment?


# Logistics

For this assignment, you must login into the servers. your_ccis_name@login.ccs.neu.edu to complete the assignment. The reason is because the examples I will provide below are compiled strictly for our machines architecture, and this is where I will test your code.

# Assignemnt Strategy

* Part 0-3 are all related.
* Part 4 can be independently completed if you get stuck in parts 1-3. The motivation for part 4, is you may be overwhelmed by looking at lots of C code you have not written (i.e. Part 0-3). Part 4 is an opportunity to practice your fundamentals.

## SSH and images

Typically when we ssh, we do so from a terminal window. Since we are working with images, we will want some sort of graphical output. There is a program called 'display' that you can run in order to view images.

Unfortunately, if we run `display image_name.ppm` we get an error.
```
-bash-4.2$ display image.ppm
display: unable to open X server `' @ error/display.c/DisplayImageCommand/431.
```

If we look at the man page for display, we get some more information about how display works, and that it needs an *X server*.
```
display(1)                         General Commands Manual                        display(1)

NAME
       display - displays an image or image sequence on any X server.
```

### XServer

The X Windowing System is Unix's way to draw graphical elements to our screen. https://en.wikipedia.org/wiki/X_Window_System. When we ssh into a terminal, the information we are passing back and forth between our client terminal(on our machine) and the server(a CCIS machine) is purely text. We want to open up our ssh connection, so we can also pass graphical information back and forth.

In order to do this, when you ssh type: `ssh -Y username@login.ccs.neu.edu`

### Mac Users

You may download [xquartz](https://www.xquartz.org) which has an X11 server running. When you perform `ssh -Y username@login.ccs.neu.edu`, the 'display canvas.ppm' will magically work!

### Windows Users

- You can download this shell: https://mobaxterm.mobatek.net/

### Unix Users

- Unix users should be in luck, an X11 window is running. Just ssh with 

### Other

If none of those options work, then you may resort to these options below.

- Use this web interface and drag in your PPM: http://paulcuth.me.uk/netpbm-viewer/
- Download your respository locally after you commit any changes. Then view your .ppm in an image editor like GIMP(https://www.gimp.org).


## Part 0 - Makefiles

In this homework, there is what is called a 'makefile'. These are special files that have instructions on how to compile your programs. Make itself is a 'build system' that saves us time in typing out commands. Build systems may also have additional optimizations, such as only recompiling files that you have changed.

For this assignment, compile your program by typing in : `make` from the root directory. That is it! You can inspect the makefile to learn how to create your own makefiles for future assignments.

**Note:** Makefiles are particularly strict about using tabs instead of spaces to indent commands. If you make modifications and you get an error, the first thing to check is that your text editor is using tabs instead of spaces.

## Part 1 - Multiprocessing with Threads (Investigating the support code)

<img align="right" src="monet.jpg" width="200px" alt="picture">

The artists from our previous exercise are frustrated! They did not believe they got to be creative enough in how they were constrained on painting on the previous canvas. 

> Artists: "We are very frustrated!"
>
> You: You have calmly explain, "We were exploiting data parallelism, you had one whole row of pixels to draw on without interruption."
>
> You: "Did you not enjoy working so efficiently(without the use of locks) without inteferring with the others 64 artists?"
>
> Artists: "We did not! This time we want to use threads, locks, ... , whatever it takes for our masterpiece!"

The artists haev spoken...for this assignment you will be be working with [posix threads](https://computing.llnl.gov/tutorials/pthreads/) to help them create a masterpiece. This time, you will start working with exactly four artists: Michaelangelo, Donatello, Rapheal, and Leonardo. These artists egos have grown out of control and they want to move around and paint wherever they want on the canvas. And as we know when there is a shared resource we will have to coordinate the artists much more carefully!

### Prompt/Specification

Michaelangelo, Rapheal, Donatello, and Leonardo are amongst great artists who have been commissed to paint on a shared 256x256 canvas. The canvas itself starts with RGB values of (255,255,255) on each pixel.  Read on for more specifications:

- 4 total artists will paint on one canvas (for now).
- Each artist wants to paint as much as possible, and they each start in their own corner.
- Artists are not allowed to 'jump' to different locations. They may only paint next to pixels that are white, or pixels that are the same brush color the artist has. 
		- Michaelangelo paints in orange: rgb(255,140,0)
		- Leonardo paints in blue: rgb(0,0,255)
		- Donatello paints in Purple: rgb(128,0,128)
		- Raphael paints in red: rgb(255,0,0)
	- Because artists cannot jump around, there should be no "islands" where the artist has painted.
		- Again, to be clear, this means each color should be continuous.
- Artists only carry so much paint with them. They may attempt to 'paint' on the canvas 5000 times maximum. 
	- This also ensures the program eventually terminates.


Provided below are some snippets from support code.

An artist structure stores its paint color and its current position where they are painting on the campus.
```c
// This is our data structure for each artist
typedef struct artist{
	int x,y;	// Store the position of where an artist is painting
	int r,g,b;	// The color an artist paints in.
}artist_t;
```

An artist moves around to adjacent and diagonol pixels. This is done through randomly selecting where the next move will be after trying to paint.
```c
const int movement[][2] ={
    {-1, 0}, // to the left 
    {-1, 1}, // to the left and down
    {0, 1}, // down
    {1, 1}, // to the right and down
    {1, 0}, // to the right
    {1, -1}, // to the right and up
    {0, -1}, // up
    {-1, -1} // to the left and up
};
```

Creating a new artist is done using malloc and populating their attributes. Each artist also has a seperate thread id.
```c
	artist_t* Michaelangelo = malloc(sizeof(artist_t));
	
	Michaelangelo->x = 0;
	Michaelangelo->y = 0;
	Michaelangelo->r = 255;
	Michaelangelo->g = 0;
	Michaelangelo->b = 165;
	
	pthread_t Michaelangelo_tid;
```

This is a reminder on how to launch a single thread and how to join the thread.
```c
	pthread_create(&Michaelangelo_tid,NULL,(void*)paint,Michaelangelo);
	pthread_join(Michaelangelo_tid, NULL);		   

```

**Go ahead and investigate and run the support code provided in painters.c**

## Part 2 - 50 More artists.

Unfortunately the work the four artists are doing is not fast enough. Lets add 50 more rookie artists to speed up the work being done. All artists however do not want their work to be painted over by others, so you will have to enforce this with some locking mechanism as well.

### Specifications (The Actual assignment)

- Add 50 more 'rookieArtists' threads that paint.
	- You may initialize their paint colors and starting positions randomly in a for-loop.
- Each artist has also agreed that they will not paint over each others work (the artists do respect each other--even the rookies). 
This means you need to enforce some locking mechanism.
	- I suggest using a 'trylock' 
	- An example is provided under trylock.c
- There should be no deadlock in this program.
	- Note: Care should be taken to minimze and only put locks around code that needs to be protected. 
		- Locals in threads for example, do not need to be locked if they are not shared. 
- All of the artists should congregate (i.e. join) at the end of the program to admire their work.
- You should output an image called "canvas.ppm" at the end of the program.
	- You may reference code from previous labs/assignments to understand the PPM format.

## Part 3 - Starvation

**Discuss(in a few sentences)** how starvation may occur in the above program, and how you would possibly fix it? (You may fix it in your implementation if you like--the art may be more beaufiful!)

*edit and add your response here*
The starvation will occur when one or more threads(Artists) are trying to access some data(pixels) but the data(pixels) was kept accessing by other threads which will make some threads(Artists) wait forever. For this homework, an artist must draw continuious, but when all possible pisitions for the next step are blocked by other threads' drawing, this artist can't draw more. Which makes data starvation.


## Part 4 - Catch Up

Often times in a semester long course, a few weeks in you can get in the habit of rushing through material and not truly understanding what is going on. For part 4, you will play a little catch up.

**Honor System** Spend 1-2 hours(no more or less) sitting down and learning something from this course you skipped over and did not really understand.

Some tutorial series that look reasonable (you can search around for others): 
* C Programming
	* https://www.lynda.com/C-tutorials/Up-Running-C/173754-2.html
	* https://www.youtube.com/playlist?list=PL6gx4Cwl9DGAKIXv8Yr6nhGJ9Vlcjyymq
	* https://www.youtube.com/watch?v=DWWQEmyVplU&list=PLZ1QII7yudbdFfKY1eKV3x_bag04AMPJq
	* memory/allocation: https://www.youtube.com/watch?v=xDVC3wKjS64&t=34s and https://www.youtube.com/watch?v=_8-ht2AKyH4
* Posix Threads
	* https://computing.llnl.gov/tutorials/pthreads/
	
**Write a few sentences here:** describing what you got caught up on. If you were caught up on 100% of things, write a few sentences about what new things you sat down and learned for 1-2 hours.

(*write your sentences here, share any tutorials you found*)

I was a little confused about the lab5 with about the fork() and pid() part. I know how to use fork and pid to create process but it kind of follow the formula to write the code. After reviewing the lecture I can visualize hwo to make fork and child process. I redone labs and assignments and have a better understand of them. It is also related to the Assignemnt 6. It makes my homework easier.

And I also failed for the if-statement which can let user choose the add or subsrtract operations for the assembly assignment.
There was no time at that time to fix that problem, but now I fixed them so user can choose which operations they like. 
I put the work locklly since I am afraid that will affect my grade if I post new things on the resp

## Rubric

1. 90% for part 2 - 50 More Artists 
	1. 80% for a correct implementation Part 2
		- There should be no deadlock
		- There should be no data races
		- I will know your implementation is correct if I do not see overlap of colors with your 50+ artistss.
			- Additionally creativity is encouraged when you get things working. :)
	2. 10% for your response to Part 3 on starvation
2. 10% for your response in part 4	

# Resources to help

- Makefile tutorial: https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html


### Glossary and Tips
1. Commit your code changes to the repository often, this is best practice.
2. Do not commit your .o file or your executable file to the repository, this is considered bad practice!
3. On Functionality/Style
	1. You should have comments in your code to explain what is going on, and use good style (80 characters per line maximum for example, functions that are less than 50 lines, well named variables, well named functions etc.).

1. Do not duplicate code (i.e. you should only have 1 function in which artists 'paint' in a loop)
2. It may be useful to have some struct that holds artists current position, how many attempts/brushes they have made, and what color they paint in.
3. Write as many helper functions as you like (getPixelColor(), checkIfPixelIsMyPaintColor(), etc.)
4. Make sure you join all of your threads
5. When passing arguments you should allocate memory
	1. See some examples here: https://courses.engr.illinois.edu/cs241/fa2010/ppt/10-pthread-examples.pdf

# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

- Check out The Little Book of Semaphores by Allen Downey.
