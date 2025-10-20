#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include "array.h"
#include <stdexcept>

/**
 * CIRCULAR QUEUE TEMPLATE CLASS
 * 
 * FIXED-SIZE QUEUE WITH WRAP-AROUND BEHAVIOR
 * Uses Professor's Array class as circular buffer
 * 
 * HOSPITAL APPLICATION:
 * - Manages limited consultation rooms
 * - Rooms are reused in circular fashion
 * - Efficient O(1) enqueue and dequeue operations
 * 
 * CIRCULAR BUFFER CONCEPT:
 * - Front and rear pointers wrap around array boundaries
 * - Uses modulo arithmetic for circular behavior
 * - Efficient use of fixed memory space
 */

template <typename T>
class CircularQueue {
private:
    Array<T>* buffer;    // Circular buffer using Array
    int capacity;        // Maximum number of elements
    int front;           // Index of front element
    int rear;            // Index of rear element  
    int currentSize;     // Current number of elements

public:
    /**
     * CIRCULAR QUEUE CONSTRUCTOR
     * @param cap: Maximum capacity of queue
     * 
     * MEMORY ALLOCATION:
     * - Creates Array of specified capacity
     * - Initializes front, rear, and currentSize
     */
    CircularQueue(int cap) : capacity(cap), front(0), rear(-1), currentSize(0) {
        buffer = new Array<T>(capacity);  // Allocate fixed-size array
    }

    /**
     * CIRCULAR QUEUE DESTRUCTOR
     * 
     * MEMORY MANAGEMENT:
     * - Deletes the dynamically allocated Array
     * - Array destructor automatically deletes internal buffer
     */
    ~CircularQueue() {
        delete buffer;  // Free the Array object
    }

    /**
     * CHECK IF QUEUE IS EMPTY
     * @return true if no elements, false otherwise
     */
    bool isEmpty() {
        return currentSize == 0;
    }

    /**
     * CHECK IF QUEUE IS FULL
     * @return true if queue reached capacity, false otherwise
     */
    bool isFull() {
        return currentSize == capacity;
    }

    /**
     * GET CURRENT NUMBER OF ELEMENTS
     * @return Number of elements in queue
     */
    int size() {
        return currentSize;
    }

    /**
     * GET MAXIMUM CAPACITY
     * @return Maximum number of elements queue can hold
     */
    int getCapacity() {
        return capacity;
    }

    /**
     * ADD ELEMENT TO QUEUE (ENQUEUE)
     * @param data: Element to add to queue
     * 
     * CIRCULAR BEHAVIOR:
     * - rear = (rear + 1) % capacity - wraps around
     * - Throws exception if queue is full
     * 
     * HOSPITAL CONTEXT:
     * - Represents assigning patient to consultation room
     */
    void enqueue(T data) {
        if (isFull()) {
            throw std::runtime_error("Circular queue is full - No available consultation rooms");
        }
        
        // Calculate new rear position with wrap-around
        rear = (rear + 1) % capacity;
        
        // Store data at rear position
        (*buffer)[rear] = data;
        
        currentSize++;  // Increment element count
    }

    /**
     * REMOVE ELEMENT FROM QUEUE (DEQUEUE)
     * @return Element removed from front of queue
     * 
     * CIRCULAR BEHAVIOR:
     * - front = (front + 1) % capacity - wraps around
     * - Throws exception if queue is empty
     * 
     * HOSPITAL CONTEXT:
     * - Represents freeing consultation room
     */
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Circular queue is empty - No occupied consultation rooms");
        }
        
        // Retrieve data from front position
        T data = (*buffer)[front];
        
        // Move front forward with wrap-around
        front = (front + 1) % capacity;
        
        currentSize--;  // Decrement element count
        return data;    // Return retrieved data
    }

    /**
     * PEEK AT FRONT ELEMENT WITHOUT REMOVING
     * @return Element at front of queue
     * 
     * USAGE:
     * - Check which patient is in the next room to be freed
     * - Doesn't modify queue state
     */
    T peekFront() {
        if (isEmpty()) {
            throw std::runtime_error("Circular queue is empty");
        }
        return (*buffer)[front];
    }

    /**
     * GET ELEMENT AT SPECIFIC POSITION
     * @param index: Position in queue (0 to currentSize-1)
     * @return Element at specified position
     * 
     * CIRCULAR ACCESS:
     * - Uses modulo arithmetic to handle wrap-around
     * - Position 0 = front, position currentSize-1 = rear
     */
    T getAt(int index) {
        if (index < 0 || index >= currentSize) {
            throw std::runtime_error("Invalid queue index");
        }
        
        int actualIndex = (front + index) % capacity;
        return (*buffer)[actualIndex];
    }

    /**
     * DISPLAY CURRENT STATE OF CIRCULAR QUEUE
     * 
     * VISUALIZATION:
     * - Shows occupancy status of all consultation rooms
     * - Displays patients currently in consultation
     * - Helpful for monitoring room utilization
     */
    void displayState() {
        std::cout << "\n=== CONSULTATION ROOMS STATE (CIRCULAR QUEUE) ===" << std::endl;
        std::cout << "Rooms occupied: " << currentSize << "/" << capacity << std::endl;
        std::cout << "Front index: " << front << ", Rear index: " << rear << std::endl;
        std::cout << "==================================================" << std::endl;
        
        if (isEmpty()) {
            std::cout << "All consultation rooms are available" << std::endl;
            return;
        }

        // Display occupied rooms in order
        for (int i = 0; i < currentSize; i++) {
            int roomIndex = (front + i) % capacity;
            std::cout << "Room " << (i + 1) << " -> " << *((*buffer)[roomIndex]) << std::endl;
        }
    }

    /**
     * GET ROOM NUMBER FOR A SPECIFIC PATIENT
     * @param patientId: ID of patient to find
     * @return Room number (1-based) or -1 if not found
     * 
     * SEARCH FUNCTIONALITY:
     * - Linear search through occupied rooms
     * - Returns human-readable room number
     */
    int findPatientRoom(int patientId) {
        for (int i = 0; i < currentSize; i++) {
            int roomIndex = (front + i) % capacity;
            if ((*buffer)[roomIndex]->id == patientId) {
                return i + 1;  // Convert to 1-based room number
            }
        }
        return -1;  // Patient not found in any room
    }

    /**
     * CHECK IF SPECIFIC PATIENT IS IN CONSULTATION
     * @param patientId: ID of patient to check
     * @return true if patient is in consultation, false otherwise
     */
    bool isPatientInConsultation(int patientId) {
        return findPatientRoom(patientId) != -1;
    }
};

#endif
