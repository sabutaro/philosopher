# new_philosophe

42 project about inter-process communication. A program that can monitor multiple instances of itself, either processes or threads, using semaphores or mutexes.
Philosophers (represented by parts of a program) sit around a table, with a big plate of spaghetti at its center. They each have a fork, but they need two forks to eat ; so they need to borrow their neighbor's fork to eat.

Of course, if they borrow a neighbor's fork, the neighbor can't use the fork. The processes / threads must communicate, to know the state of the forks (and of the other philosophers) at all times. There must also be a parent process that monitors everything.

philo does this using threads as philosophers, and mutexes as forks.
philo_bonus forks itself, making philosophers processes. Its forks are semaphores. It uses threads too, but only for monitoring.

HOW TO USE IT:
Using make will create the philo executable. if you use make bonus will create the philo executable and the philo_bonus executable.

You run it specifying, in order :

The number of philosophers
The time in milliseconds until a philosopher dies from starvation
The time in milliseconds it takes for a philosopher to eat
The time in milliseconds it takes for a philosopher to sleep
(Optional) The number of meals before the program stops
`./philo 6 400 200 100 5`
Here, the program will create 6 philosophers, who will die if they go without eating for 400 milliseconds. It takes them 200 milliseconds to eat, and 100 milliseconds to sleep. The program will stop after each philosopher has had 5 meals (or if any one of them dies prematurely).
`./philo 4 410 200 200`
Here, the program will create 4 philosophers, who will die if they go without eating for 410 milliseconds. It takes them 200 milliseconds to eat, and 200 milliseconds to sleep. No one should die.
`./philo 4 310 200 100`
Here, the program will create 4 philosophers, who will die if they go without eating for 310 milliseconds. It takes them 200 milliseconds to eat, and 100 milliseconds to sleep. A philosopher should die.


OUTPUT:
The program outputs every action with a timestamp (in milliseconds) and the philosopher's number. For example, if Philosopher 2 starts eating 412 milliseconds after the beginning of the program, it will output :\n
`./philo 3 410 200 200\n
0ms 1 has taken a fork\n
0ms 1 has taken a fork\n
0ms 1 is eating\n
0ms 3 has taken a fork\n
205ms 1 is sleeping\n
205ms 3 has taken a fork\n
205ms 3 is eating\n
205ms 2 has taken a fork\n
408ms 1 is thinking\n
408ms 2 has taken a fork\n
408ms 2 is eating\n
408ms 1 has taken a fork\n
408ms 3 is sleeping\n
412ms 1 died\n`


