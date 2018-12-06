# Terminal Overview
<img align="right" width="150px" src="./images/Color-of-the-LinkedIn-Logo.jpg">

> "Name 10 terminal commands"

That was a prompt I was given when interviewing for LinkedIn several years ago, and that was not the first time someone had asked me about the terminal at an interview! It's not that you should memorize 10 terminal commands, but rather you should understand that working on the terminal is an essential skill.

In this lab, you are going to perform a few terminal commands to get familiar with the Unix Environment.

## Part 0 - Obtain the mono repo

1. Make sure you have accepted the invitation to the monorepo from the main course page.
2. Run through the following github tutorial if you are not familiar with git.
  - https://guides.github.com/introduction/git-handbook/
  - This is worth the 15 minutes it takes to avoid headaches later on!
  - Video guides if needed: https://www.youtube.com/githubguides

## Part 1 - SSH

**I don't care what operating system you use locally as long as you have a terminal and internet access**

* For Windows Users installing Putty is sufficient. (https://www.putty.org/)
  * You might prefer to also install the bash shell from the Windows Store as well. (https://docs.microsoft.com/en-us/windows/wsl/install-win10)
* For Linux/Mac users, you already have a terminal available! Just search for 'terminal'.
* We additionally will install a virtual machine which you may work from, and which has a terminal.
* Once your terminal is open, 'ssh' into ccis with: `ssh ccis_user_name_here@login.ccs.neu.edu`
  * If for some reason you do not have a ccis username, [follow these instructions](https://www.ccis.northeastern.edu/systems/getting-started/)
* After you have successfully ssh'd, you are now running programs on the ccis servers (i.e. not locally on your machine).

<center><img align="center"  src="./images/ssh.PNG"></center>

## Part 1.5 - Obtaining your repo

When you have successfully ssh'd into your repository (Part 1) you should download a copy of your repository on the ccis servers. The rough workflow for using git is the following.

1. Run `git clone your_repository_url` to establish a git repository on your system. *your_repository_url* is found by clicking the 'green' button on you Monorepo homepage(move one directory up from this folder).

	i. It should look something like `https://github.com/Fall18Systems/Monorepo-yourname.git`
	
2. When you make a change to a file within this directory you can see what is different.

	i. run `git status` to see what you have changed locally on your computer. Changes you have made locally have not yet been saved to github's servers. 
	
3. When you are happy with your changes do `git add whatever_file.c` which prepares that specific file to be added to the master. [[git add documentation](https://git-scm.com/docs/git-add)]
4. Next, you will do `git commit -m "some informative message about your changes"` to record changes in your repository [[git-commit documentation](https://git-scm.com/docs/git-commit)]
5. Finally, do a `git push` to actually make things happen--meaning everything you have added will go to the github server. You can check your github.com repository to see exactly what I will see. [[git push documentation](https://git-scm.com/docs/git-push)]

A cheatsheet has been added to the repository (Under /ExternalResources) that may be helpful!

## Part 2 - The (at least) 10 Commands

Try running the following commands (See deliverables section at the end for copying and pasting to output.txt).

1. ls - lists the files and folders in the current directory.
2. mkdir - Create a new directory
3. cd - Change directory
4. man - Manual pages
5. rmdir - Removes an empty directory
6. sort - Sorts information
7. cat - Concatenates files and prints them to standard output
8. nl - Outputs a file with number of lines
9. cut - Remove sections from each file
10. grep - Prints lines that match a pattern.

### Navigating the terminal quickly.

Here are some other nice things to know with the terminal.

* Pressing up and down arrowkeys iterates through your command history (There is also a commmand called *history* you can checkout).
* Pressing *tab* autocompletes if it finds a program, command, or file path.
* Pressing Ctrl+C sends a signal to the terminal to terminate a program if it gets stuck.
* Pressing Ctrl+Z sends a signal to the terminal to suspend a program and give you back control.
  * You can play with these by typing in *sleep 10* (which puts the terminal to sleep) for 10 seconds, and see how you can terminate this program.
* Practice getting help by typing `man ssh` into the terminal. (Press q to quit the manual pages).

### A bit of precision
Calling each of these 'commands' (i.e. ls, sort, cat, etc.) is not really correct. Each of these is itself a program (typically implemented in C or some other language).

As an example, here is the source code for 'ls': http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/ls.c
Each of these commands are part of the coreutils package in Unix. If you look through the source tree, you will additionally find many other programs (i.e. terminal commands you run in your shell) here: http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/.

## Part 3 - Learn-C
<img align="center"  src="./images/learnc.PNG">
The main programming language we will be using in this course is "C".

Complete the 'Learn the Basics' section of the C tutorial on the web from http://www.learn-c.org/

- Hello, World!
- Variables and Types
- Arrays
- Multidimensional Arrays
- Strings
- For loops
- While loops
- Functions
- Static

Once you are comfortable write a C program on the ccis machines in the file **main.c**.

1. The program will contain a function with the signature 'int power(int base, int n)'.
2. Your program will call this function in a loop in the main function, computing the first power(2,1) to power(2,10) and print out these results to the terminal.  
3. You can compile your program with: `clang main.c -o main` to see if it works. 

Here is a little tutorial on VIM as a resource: https://www.howtoforge.com/vim-basics (Note I use VIM, and have limited knowledge of other editors, but you are free to use what you like).


## More resources to help

- There is a lovely user manual on Virtual Box here: https://www.virtualbox.org/manual/
- There is another example of installing an older Ubuntu on an older version of virtual box here with pictures: https://askubuntu.com/questions/142549/how-to-install-ubuntu-on-virtualbox
- If you are not comfortable with compiling a C program on the terminal, take a look at this resource: https://www.cs.fsu.edu/~myers/howto/g++compiling.txt
- Hackerrank has an excellent series of shell tutorials here: https://www.hackerrank.com/domains/shell/bash
  - I highly recommend going through them if you are not comfortable with the shell.
- **If you accidently delete something** you can navigate to `cd .snapshot/` which will show files that have been periodically backed up for that current directory. This is yet anothe reason to make sure you are working within the CCIS systems which provide this backup service.

## Deliverable

* Copy and Paste the output from the command-line interface of you running five different terminal commands above into a file called "output.txt" (no capitalization, exactly as named.)
  * Make sure to 'add/commit/push' this file to the repo in this directory.
* Modify the file called 'main.c' in your respository containing the power example.
  * Make sure to 'add/commit/push' this file to the repo in this directory.
  
## Going Further

(Some more programs to research and try out

1. history
2. tree
3. touch
4. awk
5. sed
