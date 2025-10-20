#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "array.h"
#include "list.h"
#include "patient.h"
#include <iostream>
#include <stdexcept>

/**
 * PRIORITY QUEUE TEMPLATE CLASS
 * 
 * IMPLEMENTATION: Array of Linked Lists
 * - Uses Array where each position contains a List
 * - Array index 0 = Priority 1 (TRIAGE I - Highest)
 * - Array index 1 = Priority 2 (TRIAGE II)
 * - Array index 2 = Priority 3 (TRIAGE III) 
 * - Array index 3 = Priority 4 (TRIAGE IV)
 * - Array index 4 = Priority 5 (TRIAGE V - Lowest)
 * - Each List maintains FIFO order within same priority level
 * 
 * TIME COMPLEXITY:
 * - Enqueue: O(1) - direct access to priority bucket
 * - Dequeue: O(1) - constant time to find highest non-empty bucket
 * - Perfect for hospital triage systems with fixed priority levels
 * 
 * MEMORY MANAGEMENT:
 * - Uses Array of List objects
 * - Automatic memory cleanup through destructors
 */
template <typename T>
class PriorityQueue {
private:
    Array<List<T>>* priorityBuckets;  ///< Array of lists, one for each priority level
    int totalPatients;                ///< Total patients across all priority levels
    int numPriorities;                ///< Number of priority levels (5 for Colombian system)

public:
    /**
     * CONSTRUCTOR - Initializes priority queue with specified number of levels
     * @param priorities: Number of priority levels (default: 5 for Colombian system)
     * 
     * INITIALIZATION PROCESS:
     * 1. Creates Array of specified size
     * 2. Initializes empty List in each array position
     * 3. Sets total patient count to zero
     */
    PriorityQueue(int priorities = 5) : totalPatients(0), numPriorities(priorities) {
        priorityBuckets = new Array<List<T>>(numPriorities, numPriorities);
        for (int i = 0; i < numPriorities; i++) {
            (*priorityBuckets)[i] = List<T>();
        }
    }

    /**
     * DESTRUCTOR - Cleans up dynamically allocated memory
     * 
     * MEMORY CLEANUP:
     * - Deletes the Array object
     * - Array destructor automatically cleans up contained Lists
     * - List destructors automatically clean up all nodes
     */
    ~PriorityQueue() {
        delete priorityBuckets;
    }

    /**
     * ENQUEUE - Adds patient to appropriate priority bucket
     * @param data: Patient pointer to add to the queue
     * 
     * ALGORITHM:
     * 1. Convert patient priority (1-5) to array index (0-4)
     * 2. Validate priority level is within bounds
     * 3. Add patient to the list at calculated array position
     * 4. Increment total patient count
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error for invalid priority levels
     */
    void add(T data) {
        int bucketIndex = data->priority - 1;
        
        if (bucketIndex < 0 || bucketIndex >= numPriorities) {
            throw std::runtime_error("Invalid patient priority. Must be between 1 and 5");
        }
        
        (*priorityBuckets)[bucketIndex].add(data);
        totalPatients++;
    }

    /**
     * DEQUEUE - Removes and returns highest priority patient
     * @return Patient with highest priority (lowest number)
     * 
     * ALGORITHM:
     * 1. Check if queue is empty
     * 2. Search buckets from highest priority (index 0) to lowest (index 4)
     * 3. Return first patient from first non-empty bucket found
     * 4. Decrement total patient count
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error if queue is empty
     */
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty - no patients to dequeue");
        }
        
        // Linear search from highest to lowest priority
        for (int i = 0; i < numPriorities; i++) {
            if (!(*priorityBuckets)[i].isEmpty()) {
                T patient = (*priorityBuckets)[i].pop();
                totalPatients--;
                return patient;
            }
        }
        
        throw std::runtime_error("Unexpected error in priority queue - no patients found");
    }

    /**
     * PEEK - Returns highest priority patient without removal
     * @return Patient with highest priority (lowest number)
     * 
     * USAGE:
     * - Check next patient to be served without modifying queue
     * - Useful for preview and monitoring operations
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error if queue is empty
     */
    T peek() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty - cannot peek");
        }
        
        for (int i = 0; i < numPriorities; i++) {
            if (!(*priorityBuckets)[i].isEmpty()) {
                return (*priorityBuckets)[i].peek();
            }
        }
        
        throw std::runtime_error("Unexpected error in priority queue - no patients found");
    }

    /**
     * CHECK IF QUEUE IS EMPTY
     * @return true if no patients in any priority bucket, false otherwise
     */
    bool isEmpty() {
        return totalPatients == 0;
    }

    /**
     * GET TOTAL NUMBER OF PATIENTS
     * @return Current number of patients across all priority levels
     */
    int len() {
        return totalPatients;
    }

    /**
     * CHECK IF PATIENT EXISTS IN ANY PRIORITY BUCKET
     * @param patientId: Unique identifier of patient to search for
     * @return true if patient found in any priority level, false otherwise
     * 
     * SEARCH ALGORITHM:
     * - Iterates through all priority buckets (TRIAGE I to TRIAGE V)
     * - Uses List::contains with lambda function for patient ID matching
     * - Returns immediately when patient is found (early termination)
     */
    bool contains(int patientId) {
        for (int i = 0; i < numPriorities; i++) {
            if ((*priorityBuckets)[i].contains([patientId](T patient) {
                return patient->id == patientId;
            })) {
                return true;
            }
        }
        return false;
    }

    /**
     * DISPLAY CURRENT STATE OF PRIORITY QUEUE
     * 
     * OUTPUT FORMAT:
     * - Shows total patients waiting
     * - Displays patient count for each priority level
     * - Only shows priority levels that have patients
     * - Uses Colombian triage terminology
     */
    void displayState() {
        if (isEmpty()) {
            std::cout << "Priority queue is empty - no patients in triage" << std::endl;
            return;
        }
        
        std::cout << "\n=== PRIORITY QUEUE STATE (COLOMBIAN TRIAGE SYSTEM) ===" << std::endl;
        std::cout << "Total patients waiting: " << totalPatients << std::endl;
        std::cout << "======================================================" << std::endl;
        
        for (int i = 0; i < numPriorities; i++) {
            int patientCount = (*priorityBuckets)[i].len();
            
            if (patientCount > 0) {
                std::string priorityName;
                switch (i + 1) {
                    case 1: priorityName = "TRIAGE I - Emergency"; break;
                    case 2: priorityName = "TRIAGE II - Urgent"; break;
                    case 3: priorityName = "TRIAGE III - Priority"; break;
                    case 4: priorityName = "TRIAGE IV - Routine"; break;
                    case 5: priorityName = "TRIAGE V - Non-urgent"; break;
                    default: priorityName = "Unknown Priority";
                }
                std::cout << priorityName << ": " << patientCount << " patients" << std::endl;
            }
        }
    }
};

#endif
