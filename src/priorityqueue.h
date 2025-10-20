#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "array.h"
#include "list.h"
#include "patient.h"
#include <iostream>

/**
 * PRIORITY QUEUE - IMPLEMENTACIÓN CORRECTA
 * 
 * ESTRUCTURA: Array de Lists (como mencionó el profesor)
 * - Array de tamaño fijo = número de prioridades
 * - Cada bucket del Array contiene una List de pacientes
 * - Prioridades: 0=Alta, 1=Media, 2=Baja
 */

template <typename T>
class PriorityQueue {
private:
    Array<List<T>>* priorityBuckets;  // ⬅️ ARRAY de LISTAS
    int totalPatients;                // Contador total de pacientes
    int numPriorities;                // Número de niveles de prioridad

public:
    /**
     * CONSTRUCTOR
     * @param priorities: Número de niveles de prioridad (default: 3)
     */
    PriorityQueue(int priorities = 3) : totalPatients(0), numPriorities(priorities) {
        // Crear array de listas para cada nivel de prioridad
        priorityBuckets = new Array<List<T>>(numPriorities, numPriorities);
        
        // Inicializar cada bucket con una lista vacía
        for (int i = 0; i < numPriorities; i++) {
            (*priorityBuckets)[i] = List<T>();
        }
        
        std::cout << "PriorityQueue initialized with " << numPriorities 
                  << " priority levels" << std::endl;
    }

    /**
     * DESTRUCTOR
     */
    ~PriorityQueue() {
        delete priorityBuckets;
    }

    /**
     * ADD PATIENT TO PRIORITY QUEUE
     * @param data: Patient to add
     * 
     * ALGORITHM:
     * 1. Determine bucket index from patient priority
     * 2. Add patient to the corresponding list (FIFO within same priority)
     */
    void add(T data) {
        // Convert priority to bucket index (1=High -> 0, 2=Medium -> 1, 3=Low -> 2)
        int bucketIndex = data->priority - 1;
        
        // Validate priority range
        if (bucketIndex < 0 || bucketIndex >= numPriorities) {
            throw std::runtime_error("Invalid patient priority");
        }
        
        // Add to the appropriate priority bucket
        (*priorityBuckets)[bucketIndex].add(data);
        totalPatients++;
        
        std::cout << "Patient added to priority bucket " << bucketIndex 
                  << " (Priority " << data->priority << ")" << std::endl;
    }

    /**
     * REMOVE AND RETURN HIGHEST PRIORITY PATIENT
     * @return Highest priority patient
     * 
     * ALGORITHM:
     * 1. Search from highest priority bucket (index 0) to lowest
     * 2. Return first patient from first non-empty bucket
     */
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        // Search from highest to lowest priority
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
     * PEEK AT HIGHEST PRIORITY PATIENT WITHOUT REMOVING
     * @return Highest priority patient
     */
    T peek() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        // Search from highest to lowest priority
        for (int i = 0; i < numPriorities; i++) {
            if (!(*priorityBuckets)[i].isEmpty()) {
                // To peek without removing, we need to access the head
                // This requires adding a peek method to List or using iterator
                return (*priorityBuckets)[i].peek();
            }
        }
        
        throw std::runtime_error("Unexpected error in priority queue");
    }

    /**
     * CHECK IF QUEUE IS EMPTY
     * @return true if no patients in any bucket
     */
    bool isEmpty() {
        return totalPatients == 0;
    }

    /**
     * GET TOTAL NUMBER OF PATIENTS
     * @return Total patients in all buckets
     */
    int len() {
        return totalPatients;
    }

    /**
     * GET NUMBER OF PATIENTS IN SPECIFIC PRIORITY
     * @param priority: Priority level (1=High, 2=Medium, 3=Low)
     * @return Number of patients in that priority
     */
    int getPriorityCount(int priority) {
        int bucketIndex = priority - 1;
        if (bucketIndex < 0 || bucketIndex >= numPriorities) {
            throw std::runtime_error("Invalid priority level");
        }
        return (*priorityBuckets)[bucketIndex].len();
    }

    /**
     * DISPLAY CURRENT STATE OF PRIORITY QUEUE
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
            std::cout << "Priority " << (i + 1) << " (" << getPriorityName(i + 1) 
                      << "): " << patientCount << " patients" << std::endl;
            
            // Display patients in this priority bucket if any
            if (patientCount > 0) {
                displayPatientsInBucket(i);
            }
        }
    }

private:
    /**
     * GET PRIORITY NAME FOR DISPLAY
     */
    std::string getPriorityName(int priority) {
        switch (priority) {
            case 1: return "High";
            case 2: return "Medium"; 
            case 3: return "Low";
            default: return "Unknown";
        }
    }

    /**
     * DISPLAY PATIENTS IN A SPECIFIC BUCKET
     * Note: This requires adding iteration capability to List
     */
    void displayPatientsInBucket(int bucketIndex) {
        // For now, we'll just show the count
        // To display individual patients, we'd need to add iteration to List
        std::cout << "  - Patients waiting: " << (*priorityBuckets)[bucketIndex].len() << std::endl;
    }

    /**
     * CHECK IF SPECIFIC PATIENT IS IN QUEUE
     * @param patientId: ID to search for
     * @return true if found in any bucket
     */
    bool contains(int patientId) {
        for (int i = 0; i < numPriorities; i++) {
            // This would require adding search capability to List
            // For now, we'll implement a basic version
            if (containsInBucket(i, patientId)) {
                return true;
            }
        }
        return false;
    }

    /**
     * CHECK IF PATIENT IS IN SPECIFIC BUCKET
     */
    bool containsInBucket(int bucketIndex, int patientId) {
        // This is a simplified version - would need proper list iteration
        // For now, we'll use the existing list functionality
        List<T> tempList = (*priorityBuckets)[bucketIndex];
        while (!tempList.isEmpty()) {
            T patient = tempList.pop();
            if (patient->id == patientId) {
                return true;
            }
        }
        return false;
    }
};

#endif
