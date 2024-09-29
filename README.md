# Project 1 Summary - Caitlyn Nelson
Overall, this has been a difficult project to complete. I have as of right now spent close to 30 hours and my project isn't completely implemented. It took me a bit of time to figure out what exactly I was doing and how I was going to approach the problem. At first, I went through the documentation of the project and just started to build the lab piece by piece. So this started with printing out the version.

Task 3 Print Version:
For this I just used getop and a switch to grab that argument and process it. Then with leveraging the major and minor version type, it prints out the Version 1.0.

Task 4 User Input:
For this I simply copied the given code and after plenty of trial and error figured out where it needed to go. This turned out to be right after my get prompt code as this would allow for the user to see every command utilized since the first call of the program.

Task 5 Custom Prompt:
I can say this section wasn't too bad. I simply created and malloced the shell pointer sh. Then I called the sh_init(sh) to initialize the entire shell. Once that was done, I also created a variable for prompt and made that equal to the return of get prompt method utilizing the MY_PROMPT variable. I then completed the get_prompt method setting up for if the getprompt has one or is null. Then I will initialize one. Once the prompt variable was set I could dereference and point to the sh prompt variable from inside the struct and set that equal to the prompt variable which in turn sets the prompt variable for my shell. This was able to complete this task.

Task 6 Custom Prompt:
This task is where I have spent the majority of the hours of work. Initially, I realize I should have gone through the documentation and written out exactly how each piece of the program interacts with each other. This would have streamlined the process from writing a bit of code and then having to go back and restructuring it to align with how everything was working. I believe I have restructured 3 times up to this point. I then begin just focusing on getting the methods in lab.c. I found that this was a hard task as I started with the parsing the commands. This was simpler than I thought as it is then just being passed back and then passed into the do_builtin method. From there then if was working through the do_builtin in which was where the handling of the commands is actually taking place. 

So I started with the exit and cd commands. This turned sort of into a mess as I was dealing with a lot of memory leak allocation or freeing problems. I did find that I needed to malloc the shell * in main.c and not inside the sh_init function because this caused it to register as never being malloced and then freeing an address that was never allocated. Upon these errors, I also figured out what exactly needed to be in the cmd_free method and how to dereference the pointer enough to free it and along with this the same sort of deal when it came to the sh_destory method. Then I began writing the code for the cd. I found that I was able to go through this code wanting it to be simple yet get the job done for the various situations "cd" and "cd PATH". The biggest problem that I had with this was running into both of the tests failing. I couldn't figure out while as the cmd_parse and do_builtin was collecting the command and had all the arguments in the right place. I realized that when I was changing the directory that when I was passing in the **directory, I only needed to reference each arguments variable as directory[1] which in this case is what we want. If null then it goes to the home directory. If not it changes to that directory. So that then seemed to solve my issues.

I also within taking care of this also wrote the trim linen functionality which for the most part works although I am having trouble with the all the input being whitespace. Nevertheless, the tests are passing so I am moving forward. 

Afterwards, I implemented the pwd command which at first I thought had it printing out the path environment variable but then realized after consulting my windows terminal that pwd prints out only the working directory path. So I then found getcwd which I was able to utilize to implement this function with this command. 

I have completed the history command in which I utilized the history library in order to figure out how to print out the specific commands on each line. At first I tried to use the data element, but found a block here with the histdata_t type which doesn't refer to a specific type to print. So then I decided to mess with the char * line initialized in the struct itself and this worked as a charm so that it prints out all the commands entered in the history. You can also see the previous commands by pressing the up arrow when running the shell itself as it tells you all the commands you have used since the initial command to start it up.

Task 7 Create a Process:


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
