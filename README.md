# Project 1: Simple Shell
*Author: Caitlyn Nelson
*Class: CS 452 - Operating Systems
*Semester: Fall 2024

# Overview of Project

For this project we had to create a simple shell with built in commands and creating processes. Our shell can provide the version of the shell, change or set the prompt variable, built in commands (exit, cd, pwd, history), and then creating a process ls -l -a that lists the folders from the process. 

# Project 1 Summary - Caitlyn Nelson
Overall, this has been a difficult project to complete. I have as of right now spent close to 65 hours and my project isn't completely implemented. It took me a bit of time to figure out what exactly I was doing and how I was going to approach the problem. At first, I went through the documentation of the project and just started to build the lab piece by piece. So this started with printing out the version.

## Task 3 Print Version:
For this I just used getop and a switch to grab that argument and process it. Then with leveraging the major and minor version type, it prints out the Version 1.0.

## Task 4 User Input:
For this I simply copied the given code and after plenty of trial and error figured out where it needed to go. This turned out to be right after my get prompt code as this would allow for the user to see every command utilized since the first call of the program.

## Task 5 Custom Prompt:
I can say this section wasn't too bad. I simply created and malloced the shell pointer sh. Then I called the sh_init(sh) to initialize the entire shell. Once that was done, I also created a variable for prompt and made that equal to the return of get prompt method utilizing the MY_PROMPT variable. I then completed the get_prompt method setting up for if the getprompt has one or is null. Then I will initialize one. Once the prompt variable was set I could dereference and point to the sh prompt variable from inside the struct and set that equal to the prompt variable which in turn sets the prompt variable for my shell. This was able to complete this task.

## Task 6 Custom Prompt:
This task is where I have spent the majority of the hours of work. Initially, I realize I should have gone through the documentation and written out exactly how each piece of the program interacts with each other. This would have streamlined the process from writing a bit of code and then having to go back and restructuring it to align with how everything was working. I believe I have restructured 3 times up to this point. I then begin just focusing on getting the methods in lab.c. I found that this was a hard task as I started with the parsing the commands. This was simpler than I thought as it is then just being passed back and then passed into the do_builtin method. From there then if was working through the do_builtin in which was where the handling of the commands is actually taking place. 

So I started with the exit and cd commands. This turned sort of into a mess as I was dealing with a lot of memory leak allocation or freeing problems. I did find that I needed to malloc the shell * in main.c and not inside the sh_init function because this caused it to register as never being malloced and then freeing an address that was never allocated. Upon these errors, I also figured out what exactly needed to be in the cmd_free method and how to dereference the pointer enough to free it and along with this the same sort of deal when it came to the sh_destory method. Then I began writing the code for the cd. I found that I was able to go through this code wanting it to be simple yet get the job done for the various situations "cd" and "cd PATH". The biggest problem that I had with this was running into both of the tests failing. I couldn't figure out while as the cmd_parse and do_builtin was collecting the command and had all the arguments in the right place. I realized that when I was changing the directory that when I was passing in the **directory, I only needed to reference each arguments variable as directory[1] which in this case is what we want. If null then it goes to the home directory. If not it changes to that directory. So that then seemed to solve my issues.

I also within taking care of this other functionality also wrote the trim line functionality which passes all the tests.

Afterwards, I implemented the pwd command which at first I thought had it printing out the path environment variable but then realized after consulting my windows terminal that pwd prints out only the working directory path. So I then found getcwd which I was able to utilize to implement this function with this command. 

I have completed the history command in which I utilized the history library in order to figure out how to print out the specific commands on each line. At first I tried to use the data element, but found a block here with the histdata_t type which doesn't refer to a specific type to print. So then I decided to mess with the char * line initialized in the struct itself and this worked as a charm so that it prints out all the commands entered in the history. You can also see the previous commands by pressing the up arrow when running the shell itself as it tells you all the commands you have used since the initial command to start it up.

## Task 7 Create a Process:

For this task, I really had to dig into the documentation to figure out what and how to create the process. This in itself was a process. At first I had to dig into fork() and make sure that I was understanding the child and parent process are executing in congurrence with each other. This lead me to call the fork if the function was not a built in function and then execute which works when ls -l -a is tested. Pressing the enter key does not work as I choose to continue on with the functionality to take a stab at creating the background and foregrounds processes.

## Task 8 Signals:

This wasn't very bad as the init_sh I restructured based on the code from the glibc initializing the shell. This turned out well to utilize this and then placing the other signal update code within the area of code dealing with the child process. For the most part this section was fairly simple to implement and didn't effect the functionality up to this point.

## Task 9 and 10 Background Process and Jobs:

I can say this was the section that really gave me a hard time. You will be able to see the code that I was working on implementing which is all commented out. I was able to get the processes to run however, the termination of the child process isn't working and I don't have that connected properly so it hangs the process. This is still in troubleshooting and has been over the past several days trying to figure it out, yet alas the due date has arrived and so I am going to submit what I have as the majority of the project is complete. The functionality of the shell is 95% there with what is asked for within the requirements:

Passed built-in Test-lab (30pts)
Passed Manual tests for Shell Program (40pts)
Print Version: ./myprogram -v
Custom Prompt: MY_PROMPT="foo" ./myprogram
Built in Commands: exit, cd, pwd, history
Create a Process: ls -l -a
Summary of Project 1 (30pts)

The deadline on this was a challenge and I wish I had more time to completely work through this to finish the programming assignment, however am proud of the work and time that I dedicated to this learning exericse. I would after everything is graded to see a full working shell as an example of the professors working code to have for reference and future.

Overall, I felt I learned a heck of a lot when it comes to the hours I spent with this. It isn't 100% completed as I had hoped I could get to even with starting the project the day it was assigned, but made great strides in learning which is what really counts. This was a difficult project and for the future a bit more help on the front end and more in depth discussions of forks and processes will go a long way in helping do the later parts of this project.

## Run the Code
Run the general make clean - this will get all the files set up
Run the make command

Then you can run the following commands to output results:

./myprogram -v - This will tell you the version
MY_PROMPT="foo>" ./myprogram <-v> - This will show you the prompt variable and that it gets set. Adding the -v will also give you the version.

After running ./myprogram
Commands to utilize:
cd
pwd
history
exit
ls -l -a

Also can run ./test-lab to run the test file.


# Makefile Project Template

Steps to configure, build, run, and test the project.

## Building

```bash
make
```

## Testing

```bash
make check
```

## Clean

```bash
make clean
```

## Install Dependencies

In order to use git send-mail you need to run the following command:

```bash
make install-deps
```
