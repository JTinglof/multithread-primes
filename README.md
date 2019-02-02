# CS530Assignment2

Joseph

Tinglof

jbtinglof@gmail.com

## **Files Included:**

* this README
* prog2_1.h 
* prog2_1.c 
* prog2_2.c

## **Compile Instructions**

Nagivate to the proper directory in the terminal and compile with the following
command. Make sure you have downloaded GMP.

prog2_2.c prog2_1.c -lgmp -lpthread -o prog2_2

## **Usage**

Pass in command line arguments in the following order.

./prog2_2 [A] [B]

Where A is the number of prime numbers and B is the point from which the program
should start to search for prime numbers. 

## **Design Choices**

The point of this project was to take the computationally expensive task of
finding prime numbers and split it among 4 threads which could work simultaneously
with one another. They all place their found primes in the same queue style
data structure. This structure uses a mutex to make the enqueue and dequeue 
functions atomic. The driver also uses a mutex to prevent the threads from 
working on the same prime number.

## **Common Bugs**

No bugs have been found. 