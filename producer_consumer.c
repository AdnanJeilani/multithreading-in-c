#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE]; // Shared buffer
int fill = 0;            // Index to fill the buffer
int use = 0;             // Index to use (consume) the buffer

sem_t empty;             // Semaphore to track empty slots in the buffer
sem_t full;              // Semaphore to track filled slots in the buffer
pthread_mutex_t mutex;   // Mutex for protecting shared data access

void put(int value) {
    buffer[fill] = value;  // Put the value into the buffer
    fill = (fill + 1) % BUFFER_SIZE;  // Update the fill index, wrapping around if necessary
}

int get() {
    int tmp = buffer[use];  // Get a value from the buffer
    use = (use + 1) % BUFFER_SIZE;  // Update the use index, wrapping around if necessary
    return tmp;
}

void *producer(void *arg) {
    int i;
    for (i = 0; i < 20; i++) {
        sem_wait(&empty);  // Wait until there is an empty slot in the buffer
        pthread_mutex_lock(&mutex);  // Acquire the mutex to protect shared data access
        put(i);  // Put the value into the buffer
        pthread_mutex_unlock(&mutex);  // Release the mutex
        sem_post(&full);  // Increment the count of filled slots in the buffer
    }
    return NULL;
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < 20; i++) {
        sem_wait(&full);  // Wait until there is a filled slot in the buffer
        pthread_mutex_lock(&mutex);  // Acquire the mutex to protect shared data access
        int tmp = get();  // Get a value from the buffer
        pthread_mutex_unlock(&mutex);  // Release the mutex
        sem_post(&empty);  // Increment the count of empty slots in the buffer
        printf("%d\n", tmp);  // Print the consumed value
    }
    return NULL;
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);  // Initialize the empty semaphore with the buffer size
    sem_init(&full, 0, 0);  // Initialize the full semaphore with 0 (no filled slots initially)
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);  // Create the producer thread
    pthread_create(&consumer_thread, NULL, consumer, NULL);  // Create the consumer thread
    pthread_join(producer_thread, NULL);  // Wait for the producer thread to finish
    pthread_join(consumer_thread, NULL);  // Wait for the consumer thread to finish

    sem_destroy(&empty);  // Destroy the empty semaphore
    sem_destroy(&full);  // Destroy the full semaphore
    pthread_mutex_destroy(&mutex);  // Destroy the mutex

    return 0;
}
