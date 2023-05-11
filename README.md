# multithreading-in-c


This repository contains an example of a threaded producer-consumer problem implemented in C. The code demonstrates how to synchronize the production and consumption of data using threads and semaphores.

## Description

The threaded producer-consumer problem is a classic synchronization problem in concurrent programming. It involves two entities: a producer that produces data and puts it into a shared buffer, and a consumer that retrieves and consumes the data from the buffer. The challenge is to ensure that the producer and consumer threads operate correctly and avoid issues like data races, resource contention, and buffer overflow/underflow.

This example code provides a solution to the producer-consumer problem by utilizing threads and semaphores for synchronization and a mutex for protecting shared data access. It serves as a learning resource for understanding the concepts of multithreading, synchronization mechanisms (such as semaphores), and mutual exclusion (using a mutex) in C.

## Overview

The code consists of a shared buffer with a fixed size and two threads: a producer thread and a consumer thread. The producer thread generates data items and inserts them into the buffer, while the consumer thread retrieves and consumes the items from the buffer.

To ensure synchronization, the implementation uses two semaphores: `empty` and `full`. The `empty` semaphore keeps track of the number of empty slots in the buffer, while the `full` semaphore counts the number of filled slots. The producer thread waits on the `empty` semaphore before adding an item to the buffer and signals the `full` semaphore after insertion. On the other hand, the consumer thread waits on the `full` semaphore before retrieving an item and signals the `empty` semaphore after consumption.

A mutex (`mutex`) is used to protect shared data access. The producer and consumer threads acquire the mutex before accessing the buffer to prevent simultaneous access and maintain data integrity.


