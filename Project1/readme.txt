1. Names and CSM Campus IDs of the students of project team
  Demonna Wade ; CWID: 10679707

2. What Programming language is used?
  C
  
  There may be a little bit of C++ used in various places, but majority of the source code is written
  in C. I was trying to make sure that I get comnfortable with C because of CSCI 442. 

3. What OS is usd to compile and run the code?
  Linux is the OS I used to write, run, and compile my code. More specfically, I used the linux server
  provided on campus (isengard.mines.edu).

4. How the code is structured?
  There are 4 main files that are essential to the source code. Regarding the C code, 
  uninformedSearch.c, uninformedSearch.h, and main.c is where the core functionaliy of the program
  exist. The MakeFile is include which compiles the code and creates an executable file called 
  'find_route'. This executable file depends on three arguments to run succesfully: input text
  file, the origin city, and the desination city (that order is required to match the project
  requirements).

5. How to run the code
  To run the code, you will need g++ and Make. g++ is the compiler that my program depends on. To
  remove work required by the TA, I have provided a Makefile that runs a build on the core C files. 
  The steps to build and run my code are the following:
    - make sure to be in the directory that has Makefile and all the .c and .h files
    - Linux command: $ make
      (This will build the executable reqired to run the program)
    - Linux command: $ ./find_route input.txt origin_city destination_city

I emailed the TA regarding the requirement: "Code that does not run on Windows 7/8/10 machines
gets AT MOST half credit. On 2/6/2020 at 10:35, the TA responded with the following statement:

"Please read the requirements carefull before starting your project next time. Since the due
 time is tonight and I do believe that you have already put efforts on it, I will not dedcut
 any points regarding this issue this time."

Please refer to the main file for the structure of the program and the flow. 
Modification to the start() function in uniformedSearch.c can be done to use the helper functions
such as showTreeMap(...) and searchTreeMap(...).


Complications:

- I must admit that I was unable to determine a proper method to insert a city that was not linked to
  the orginal map. With this fact in the example input, cities such as Manchester, Birmingham, Bristol,
  and London were not include in the tree I build. I did not consider unconnected cities in the design
  of my algorithm and that was my short coming in the implementation of this project.
- Unable to find the most optimal route. I was able to determine multiple routes but because of my 
  limited time (my fault), I was unable to determine an algorithm for the most optimal route.        
