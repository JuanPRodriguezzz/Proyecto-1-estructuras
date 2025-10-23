#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include "list.h"
#include <stdexcept>

/**
 * CIRCULAR QUEUE TEMPLATE CLASS - LINKED LIST IMPLEMENTATION
 * 
 * IMPLEMENTATION: Uses a circular linked list to manage fixed-capacity queues
 * BEHAVIOR: True circular structure where tail node points to head node
 * HOSPITAL APPLICATION: Manages consultation rooms with circular reuse pattern
 * 
 * CIRCULAR LINKED LIST CONCEPT:
 * - Nodes form a continuous circle: head ←→ node1 ←→ node2 ←→ ... ←→ tail → head
 * - No null termination in the circular chain
 * - Natural wrap-around behavior without index calculations
 * 
 * PERFORMANCE CHARACTERISTICS:
 * - Enqueue: O(1) - constant time insertion at tail
 * - Dequeue: O(1) - constant time removal from head  
 * - Search: O(n) - linear search through circular list
 * - Memory: Dynamic allocation per node
 */
template <typename T>
class CircularQueue {
private:
    Node<T>* head;           ///< Pointer to the first node in the circular queue (front)
    Node<T>* tail;           ///< Pointer to the last node in the circular queue (rear)
    int currentSize;         ///< Current number of elements in the queue
    int capacity;            ///< Maximum capacity of the queue (fixed at construction)

public:
    /**
     * CONSTRUCTOR - Initializes an empty circular queue with specified capacity
     * @param cap: Maximum number of elements the queue can hold
     * 
     * INITIALIZATION:
     * - head and tail set to nullptr (empty queue)
     * - currentSize set to 0 (no elements)
     * - capacity set to provided value (consultation room limit)
     * 
     * MEMORY STATE: No dynamic allocation until elements are added
     */
    CircularQueue(int cap) : head(nullptr), tail(nullptr), currentSize(0), capacity(cap) {
        // Validation: Ensure positive capacity
        if (cap <= 0) {
            throw std::invalid_argument("Circular queue capacity must be positive");
        }
    }

    /**
     * DESTRUCTOR - Ensures complete cleanup of all dynamically allocated nodes
     * 
     * MEMORY MANAGEMENT:
     * - Calls clear() to delete all nodes in the circular list
     * - Prevents memory leaks by freeing all allocated memory
     * - Handles circular structure cleanup correctly
     */
    ~CircularQueue() {
        clear();
    }

    /**
     * CLEAR - Removes all elements from the queue and frees memory
     * 
     * CLEANUP PROCESS:
     * 1. Traverses the circular list from head to tail
     * 2. Deletes each node individually
     * 3. Breaks circular references before deletion
     * 4. Resets pointers and size to initial state
     */
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    /**
     * ENQUEUE - Adds an element to the rear of the circular queue
     * @param data: Element to be added to the queue
     * 
     * CIRCULAR BEHAVIOR:
     * - When queue is empty: Creates first node and establishes circularity (tail->next = head)
     * - When queue has elements: Appends to tail and maintains circularity
     * - Rejects operation if queue is at capacity
     * 
     * HOSPITAL CONTEXT: Represents assigning a patient to a consultation room
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error if queue is at maximum capacity
     * - Strong exception safety guarantee
     */
    void enqueue(T data) {
        if (isFull()) {
            throw std::runtime_error("Circular queue is full - No available consultation rooms");
        }
        
        // Create new node with provided data
        Node<T>* newNode = new Node<T>(data);
        
        if (isEmpty()) {
            // First element in queue - establish circular structure
            head = newNode;
            tail = newNode;
            tail->next = head;  // Circular reference: last node points to first
        } else {
            // Append to end of circular list
            tail->next = newNode;  // Current tail points to new node
            tail = newNode;        // New node becomes tail
            tail->next = head;     // Maintain circularity: new tail points to head
        }
        
        currentSize++;  // Increment element count
    }

    /**
     * DEQUEUE - Removes and returns the element from the front of the circular queue
     * @return Element that was removed from the front
     * 
     * CIRCULAR BEHAVIOR:
     * - Removes the head node and advances head to next node
     * - Maintains circularity by updating tail->next if necessary
     * - Special handling when removing the last element
     * 
     * HOSPITAL CONTEXT: Represents completing a consultation and freeing the room
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error if queue is empty
     * - Strong exception safety guarantee
     */
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Circular queue is empty - No occupied consultation rooms");
        }
        
        Node<T>* temp = head;  // Store current head for deletion
        T data = head->data;   // Retrieve data before node deletion
        
        if (head == tail) {
            // Single element case - reset to empty state
            head = nullptr;
            tail = nullptr;
        } else {
            // Multiple elements - advance head and maintain circularity
            head = head->next;     // Move head to next node
            tail->next = head;     // Update tail to point to new head (maintain circle)
        }
        
        delete temp;        // Free the old head node memory
        currentSize--;      // Decrement element count
        return data;        // Return the retrieved data
    }

    /**
     * CHECK IF QUEUE IS EMPTY
     * @return true if queue contains no elements, false otherwise
     * 
     * EFFICIENCY: O(1) - uses maintained size counter
     * 
     * USAGE: Precondition checking before dequeue operations
     */
    bool isEmpty() {
        return currentSize == 0;
    }

    /**
     * CHECK IF QUEUE IS FULL
     * @return true if queue has reached maximum capacity, false otherwise
     * 
     * EFFICIENCY: O(1) - compares currentSize with capacity
     * 
     * USAGE: Precondition checking before enqueue operations
     */
    bool isFull() {
        return currentSize == capacity;
    }

    /**
     * GET CURRENT NUMBER OF ELEMENTS
     * @return Number of elements currently in the queue
     * 
     * EFFICIENCY: O(1) - uses maintained counter
     */
    int size() {
        return currentSize;
    }

    /**
     * GET MAXIMUM CAPACITY
     * @return Maximum number of elements the queue can hold
     * 
     * EFFICIENCY: O(1) - returns stored capacity value
     */
    int getCapacity() {
        return capacity;
    }

    /**
     * PEEK AT FRONT ELEMENT WITHOUT REMOVING
     * @return Element at the front of the queue
     * 
     * USAGE:
     * - Inspect next element to be processed
     * - Useful for preview operations without modifying queue state
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error if queue is empty
     */
    T peekFront() {
        if (isEmpty()) {
            throw std::runtime_error("Circular queue is empty");
        }
        return head->data;
    }

    /**
     * FIND PATIENT ROOM BY PATIENT ID
     * @param patientId: Unique identifier of the patient to search for
     * @return Room number (1-based) if patient found, -1 if not found
     * 
     * SEARCH ALGORITHM:
     * 1. Start from head node and traverse circular list
     * 2. Compare patient ID at each node with target ID
     * 3. Return position (1-based) when match found
     * 4. Continue until complete circle is traversed
     * 
     * TIME COMPLEXITY: O(n) - linear search through circular list
     * 
     * HOSPITAL CONTEXT: Locates which consultation room a patient is in
     */
    int findPatientRoom(int patientId) {
        if (isEmpty()) {
            return -1;  // Quick return if queue is empty
        }
        
        Node<T>* current = head;
        int roomNumber = 1;  // 1-based room numbering for user-friendly output
        
        // Traverse circular list until we complete full circle
        do {
            if (current->data->id == patientId) {
                return roomNumber;  // Patient found - return room number
            }
            current = current->next;
            roomNumber++;
        } while (current != head);  // Stop when we return to starting point
        
        return -1;  // Patient not found in any room
    }

    /**
     * CHECK IF PATIENT IS IN CONSULTATION
     * @param patientId: Unique identifier of the patient to check
     * @return true if patient is found in any consultation room, false otherwise
     * 
     * EFFICIENCY: O(n) - uses findPatientRoom internally
     * 
     * USAGE: Quick status check for patient location
     */
    bool isPatientInConsultation(int patientId) {
        return findPatientRoom(patientId) != -1;
    }

    /**
     * DISPLAY CURRENT STATE OF CIRCULAR QUEUE
     * 
     * VISUALIZATION FEATURES:
     * - Shows occupancy statistics (current/maximum)
     * - Displays circular structure with arrow notation
     * - Lists all occupied consultation rooms in order
     * - Provides clear empty state message
     * 
     * OUTPUT FORMAT:
     * - Header with capacity information
     * - Circular structure visualization
     * - Detailed room-by-room listing
     */
    void displayState() {
        std::cout << "\n=== CONSULTATION ROOMS STATE (CIRCULAR QUEUE - LINKED LIST) ===" << std::endl;
        std::cout << "Rooms occupied: " << currentSize << "/" << capacity << std::endl;
        
        // Display circular structure visualization
        std::cout << "Circular structure: ";
        if (isEmpty()) {
            std::cout << "Empty" << std::endl;
        } else {
            Node<T>* current = head;
            std::cout << "HEAD → ";
            do {
                std::cout << "Room[" << *current->data << "]";
                if (current->next != head) {
                    std::cout << " → ";
                }
                current = current->next;
            } while (current != head);
            std::cout << " → HEAD (circular)" << std::endl;
        }
        
        std::cout << "=============================================================" << std::endl;
        
        // Display detailed room information
        if (isEmpty()) {
            std::cout << "All consultation rooms are available" << std::endl;
            return;
        }

        // List all occupied consultation rooms in order
        Node<T>* current = head;
        int roomNumber = 1;
        do {
            std::cout << "Consultation Room " << roomNumber << " → " << *current->data << std::endl;
            current = current->next;
            roomNumber++;
        } while (current != head);
    }

    /**
     * GET ELEMENT AT SPECIFIC POSITION IN QUEUE
     * @param index: Position in queue (0 to currentSize-1)
     * @return Element at the specified position
     * 
     * BEHAVIOR:
     * - Position 0 returns head element
     * - Position currentSize-1 returns tail element
     * - Traverses circular list linearly to reach position
     * 
     * TIME COMPLEXITY: O(n) - linear traversal to position
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error for invalid indices
     */
    T getAt(int index) {
        if (index < 0 || index >= currentSize) {
            throw std::runtime_error("Invalid queue index");
        }
        
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
};

#endif
