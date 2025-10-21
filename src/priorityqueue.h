#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "array.h"
#include "list.h"       // Using concrete List class instead of abstract
#include "patient.h"
#include <iostream>
#include <stdexcept>

/**
 * PRIORITY QUEUE TEMPLATE CLASS
 * 
 * IMPLEMENTATION: Array of Lists (Bucket Sort Approach)
 * - Uses Array where each position contains a List for that priority level
 * - Array index 0 = Priority 1 (TRIAGE I - Emergency)
 * - Array index 1 = Priority 2 (TRIAGE II - Urgent) 
 * - Array index 2 = Priority 3 (TRIAGE III - Priority)
 * - Array index 3 = Priority 4 (TRIAGE IV - Routine)
 * - Array index 4 = Priority 5 (TRIAGE V - Non-urgent)
 * - Each List maintains FIFO order within the same priority level
 * 
 * COLOMBIAN TRIAGE SYSTEM:
 * - 5 priority levels according to Colombian healthcare standards
 * - Lower priority number = higher urgency
 * - Perfect for hospital emergency department triage
 * 
 * TIME COMPLEXITY:
 * - Enqueue: O(1) - direct array access to priority bucket
 * - Dequeue: O(1) - constant time to find highest non-empty bucket
 * - Optimal for fixed priority level systems
 */
template <typename T>
class PriorityQueue {
private:
    Array<List<T>>* priorityBuckets;  ///< Array of List objects, one for each priority level
    int totalPatients;                ///< Total patients across all priority levels
    int numPriorities;                ///< Number of priority levels (5 for Colombian system)

public:
    /**
     * CONSTRUCTOR - Initializes priority queue with Colombian triage system
     * @param priorities: Number of priority levels (default: 5)
     * 
     * KEY IMPROVEMENT: Now works because List is concrete class
     * - Array<List<T>> can be instantiated directly
     * - No more abstract class instantiation errors
     * - Each bucket automatically initialized with empty List
     * 
     * MEMORY ALLOCATION:
     * - Creates Array of specified size
     * - Each array position contains a default-constructed List
     * - Total patient count starts at zero
     */
    PriorityQueue(int priorities = 5) : totalPatients(0), numPriorities(priorities) {
        // Array constructor now works because List is concrete
        priorityBuckets = new Array<List<T>>(numPriorities, numPriorities);
        
        // Each bucket is automatically initialized with empty List
        // No additional initialization needed due to Array constructor
    }

    /**
     * DESTRUCTOR - Cleans up dynamically allocated memory
     * 
     * MEMORY MANAGEMENT:
     * - Deletes the Array object
     * - Array destructor automatically deletes all contained Lists
     * - List destructors automatically free all node memory
     * - Complete cleanup with no memory leaks
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
     * 2. Validate priority level is within Colombian system range
     * 3. Add patient to the List at calculated array position
     * 4. Increment total patient count
     * 
     * BEHAVIOR: 
     * - Uses List::add() which provides FIFO ordering within bucket
     * - Patients with same priority are processed in arrival order
     * - Constant time operation - direct array access
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error for invalid priority levels
     * - Strong exception safety guarantee
     */
    void add(T data) {
        int bucketIndex = data->priority - 1;  // Convert to zero-based index
        
        // Validate priority level according to Colombian system
        if (bucketIndex < 0 || bucketIndex >= numPriorities) {
            throw std::runtime_error("Invalid patient priority. Must be between 1 (TRIAGE I) and 5 (TRIAGE V)");
        }
        
        // Add patient to the appropriate priority bucket
        (*priorityBuckets)[bucketIndex].add(data);
        totalPatients++;  // Update total count
    }

    /**
     * DEQUEUE - Removes and returns highest priority patient
     * @return Patient with highest priority (lowest number)
     * 
     * ALGORITHM:
     * 1. Check if queue is empty (early termination)
     * 2. Linear search from highest priority (index 0) to lowest (index 4)
     * 3. Return first patient from first non-empty bucket found
     * 4. Decrement total patient count
     * 
     * PRIORITY SEARCH ORDER:
     * - TRIAGE I (Emergency) → index 0
     * - TRIAGE II (Urgent) → index 1  
     * - TRIAGE III (Priority) → index 2
     * - TRIAGE IV (Routine) → index 3
     * - TRIAGE V (Non-urgent) → index 4
     * 
     * TIME COMPLEXITY: O(1) - fixed number of priority levels (5)
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error if queue is empty
     */
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty - no patients to dequeue");
        }
        
        // Search from highest to lowest priority
        for (int i = 0; i < numPriorities; i++) {
            if (!(*priorityBuckets)[i].isEmpty()) {
                // Remove and return patient from this bucket
                T patient = (*priorityBuckets)[i].pop();
                totalPatients--;  // Update total count
                return patient;
            }
        }
        
        // This should never be reached if isEmpty() check passes
        throw std::runtime_error("Unexpected error in priority queue - no patients found despite non-empty state");
    }

    /**
     * PEEK - Returns highest priority patient without removal
     * @return Patient with highest priority (lowest number)
     * 
     * USAGE:
     * - Preview next patient to be served
     * - System monitoring and status display
     * - Does not modify queue state
     * 
     * BEHAVIOR:
     * - Searches buckets in priority order (TRIAGE I to TRIAGE V)
     * - Returns patient from first non-empty bucket
     * - Patient remains in queue for future processing
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
        
        throw std::runtime_error("Unexpected error in priority queue - no patients found despite non-empty state");
    }

    /**
     * CHECK IF QUEUE IS EMPTY
     * @return true if no patients in any priority bucket, false otherwise
     * 
     * EFFICIENCY: O(1) - uses maintained total patient count
     * 
     * USAGE:
     * - Condition checking before dequeue operations
     * - System status monitoring
     * - Loop termination condition
     */
    bool isEmpty() {
        return totalPatients == 0;
    }

    /**
     * GET TOTAL NUMBER OF PATIENTS
     * @return Current number of patients across all priority levels
     * 
     * EFFICIENCY: O(1) - uses maintained counter
     * 
     * USE CASES:
     * - System statistics and reporting
     * - Wait time estimation
     * - Resource allocation planning
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
     * - Searches all buckets regardless of priority level
     * 
     * TIME COMPLEXITY: O(n) worst case, but optimized with early termination
     * 
     * USE CASES:
     * - Patient status tracking
     * - Duplicate registration prevention
     * - Patient lookup and information retrieval
     */
    bool contains(int patientId) {
        // Search all priority buckets for patient with matching ID
        for (int i = 0; i < numPriorities; i++) {
            if ((*priorityBuckets)[i].contains([patientId](T patient) {
                return patient->id == patientId;
            })) {
                return true;  // Patient found - early termination
            }
        }
        return false;  // Patient not found in any bucket
    }

    /**
     * DISPLAY CURRENT STATE OF PRIORITY QUEUE
     * 
     * OUTPUT FORMAT:
     * - Shows total patients waiting
     * - Displays patient count for each priority level
     * - Only shows priority levels that have patients
     * - Uses Colombian triage terminology and descriptions
     * 
     * VISUALIZATION:
     * - Clear hierarchy of priority levels
     * - Immediate understanding of system load
     * - Useful for administrative monitoring
     */
    void displayState() {
        if (isEmpty()) {
            std::cout << "Priority queue is empty - no patients in triage" << std::endl;
            return;
        }
        
        std::cout << "\n=== PRIORITY QUEUE STATE (COLOMBIAN TRIAGE SYSTEM) ===" << std::endl;
        std::cout << "Total patients waiting: " << totalPatients << std::endl;
        std::cout << "======================================================" << std::endl;
        
        // Display each priority level that has patients
        for (int i = 0; i < numPriorities; i++) {
            int patientCount = (*priorityBuckets)[i].len();
            
            // Only display non-empty buckets
            if (patientCount > 0) {
                std::string priorityName;
                std::string priorityDescription;
                
                // Map priority level to Colombian triage terminology
                switch (i + 1) {
                    case 1: 
                        priorityName = "TRIAGE I - Emergency";
                        priorityDescription = "Life-threatening conditions";
                        break;
                    case 2: 
                        priorityName = "TRIAGE II - Urgent"; 
                        priorityDescription = "Risk of rapid deterioration";
                        break;
                    case 3: 
                        priorityName = "TRIAGE III - Priority";
                        priorityDescription = "Requires prompt attention";
                        break;
                    case 4: 
                        priorityName = "TRIAGE IV - Routine";
                        priorityDescription = "Standard medical conditions";
                        break;
                    case 5: 
                        priorityName = "TRIAGE V - Non-urgent";
                        priorityDescription = "Chronic/minor conditions";
                        break;
                    default: 
                        priorityName = "Unknown Priority";
                        priorityDescription = "Undefined priority level";
                }
                
                std::cout << priorityName << ": " << patientCount << " patients" << std::endl;
                std::cout << "  ↳ " << priorityDescription << std::endl;
            }
        }
        
        // Additional system insights
        std::cout << "\n=== SYSTEM INSIGHTS ===" << std::endl;
        
        // Find highest priority with patients
        for (int i = 0; i < numPriorities; i++) {
            if (!(*priorityBuckets)[i].isEmpty()) {
                std::cout << "Highest priority with patients: " << (*priorityBuckets)[i].peek()->getPriorityDescription() << std::endl;
                std::cout << "Next patient: " << *((*priorityBuckets)[i].peek()) << std::endl;
                break;
            }
        }
        
        // Show distribution summary
        int highPriorityPatients = 0;
        for (int i = 0; i < 2; i++) {  // TRIAGE I and II
            highPriorityPatients += (*priorityBuckets)[i].len();
        }
        
        if (highPriorityPatients > 0) {
            std::cout << "High priority patients (TRIAGE I-II): " << highPriorityPatients << std::endl;
        }
    }
};

#endif
