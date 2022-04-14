So far we have two executables.
One is called prolific where a parent process creates a child and that child waits for a certain amount of random time and returns with a random exit code.

The second one has a root parent process that makes a child who will make children of its own. This is done by making a random number and for every child that is made it decrements that 
random number until it reaches 0. When a process see's that value as 0 it returns with an exit value of zero. then that process parent will read that exit code and return an exit code 1 more than the exit code it
recieved until we get to the root process.
