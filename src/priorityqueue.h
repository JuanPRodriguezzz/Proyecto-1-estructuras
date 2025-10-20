/**
 * PRIORITY QUEUE - ARRAY OF LISTS IMPLEMENTATION
 * 
 * IMPLEMENTATION DETAILS:
 * - Uses an Array where each position contains a List
 * - Array index 0 = Priority 1 (Highest) 
 * - Array index 1 = Priority 2 (Medium)
 * - Array index 2 = Priority 3 (Lowest)
 * - Each List maintains FIFO order within the same priority level
 * 
 * TIME COMPLEXITY:
 * - Enqueue: O(1) - direct access to priority bucket
 * - Dequeue: O(1) - constant time to find highest non-empty bucket
 * - Perfect for hospital triage systems with fixed priority levels
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "array.h"
#include "list.h"
#include "patient.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class PriorityQueue {
private:
    // ARRAY OF LISTS - Core data structure
    Array<List<T>>* priorityBuckets;  // Each bucket = list for that priority
    int totalPatients;                // Total patients across all priorities
    int numPriorities;                // Number of priority levels (default: 3)

public:
    /**
     * CONSTRUCTOR - Initializes array with empty lists for each priority
     */
    PriorityQueue(int priorities = 3) : totalPatients(0), numPriorities(priorities) {
        priorityBuckets = new Array<List<T>>(numPriorities, numPriorities);
        for (int i = 0; i < numPriorities; i++) {
            (*priorityBuckets)[i] = List<T>();
        }
    }

    /**
     * DESTRUCTOR - Cleans up the array (lists clean themselves automatically)
     */
    ~PriorityQueue() {
        delete priorityBuckets;
    }

    /**
     * ENQUEUE - Adds patient to appropriate priority bucket
     * @param data: Patient pointer to add
     * 
     * ALGORITHM:
     * 1. Convert patient priority (1,2,3) to array index (0,1,2)
     * 2. Add patient to the list at that array position
     * 3. Maintains FIFO order within same priority level
     */
    void add(T data) {
        int bucketIndex = data->priority - 1;
        
        if (bucketIndex < 0 || bucketIndex >= numPriorities) {
            throw std::runtime_error("Invalid patient priority");
        }
        
        (*priorityBuckets)[bucketIndex].add(data);
        totalPatients++;
    }

    /**
     * DEQUEUE - Removes and returns highest priority patient
     * @return Patient with highest priority (lowest number)
     * 
     * ALGORITHM:
     * 1. Search buckets from highest priority (index 0) to lowest (index 2)
     * 2. Return first patient from first non-empty bucket found
     * 3. If all buckets empty, throw exception
     */
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        // Linear search from highest to lowest priority
        for (int i = 0; i < numPriorities; i++) {
            if (!(*priorityBuckets)[i].isEmpty()) {
                T patient = (*priorityBuckets)[i].pop();
                totalPatients--;
                return patient;
            }
        }
        
        throw std::runtime_error("Unexpected error in priority queue");
    }

    /**
     * PEEK - Returns highest priority patient without removal or changes
     */
    T peek() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        for (int i = 0; i < numPriorities; i++) {
            if (!(*priorityBuckets)[i].isEmpty()) {
                return (*priorityBuckets)[i].peek();
            }
        }
        
        throw std::runtime_error("Unexpected error in priority queue");
    }

    bool isEmpty() {
        return totalPatients == 0;
    }

    int len() {
        return totalPatients;
    }
    /**
     * CONTAINS - CHECKS IF A PATIENT WITH SPECIFIED ID EXISTS IN ANY PRIORITY BUCKET
     * @param patientId: The unique identifier of the patient to search for
     * @return true if patient found in any priority level, false otherwise
     * 
     * SEARCH ALGORITHM:
     * - Iterates through all priority buckets (high, medium, low)
     * - For each bucket, performs linear search through the patient list
     * - Returns immediately when patient is found to optimize performance
     * 
     * USE CASE:
     * - Patient status tracking in display functions
     * - Preventing duplicate patient registrations
     * - Patient lookup and system monitoring
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
     * DISPLAY STATE - Shows current status of all priority buckets
     */
    void displayState() {
        if (isEmpty()) {
            std::cout << "Priority queue is empty - no patients in triage" << std::endl;
            return;
        }
        
        std::cout << "\n=== PRIORITY QUEUE STATE (ARRAY OF LISTS) ===" << std::endl;
        std::cout << "Total patients: " << totalPatients << std::endl;
        std::cout << "==============================================" << std::endl;
        
        for (int i = 0; i < numPriorities; i++) {
            int patientCount = (*priorityBuckets)[i].len();
            std::string priorityName;
            switch (i + 1) {
                case 1: priorityName = "High"; break;
                case 2: priorityName = "Medium"; break;
                case 3: priorityName = "Low"; break;
                default: priorityName = "Unknown";
            }
            std::cout << "Priority " << (i + 1) << " (" << priorityName 
                      << "): " << patientCount << " patients" << std::endl;
        }
    }
};

#endif
