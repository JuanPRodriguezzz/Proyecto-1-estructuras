#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H

#include "priorityqueue.h"
#include "circularqueue.h"
#include "stack.h"
#include "array.h"
#include "patient.h"
#include <iostream>
#include <string>

/**
 * HOSPITAL SYSTEM MAIN CLASS
 * 
 * INTEGRATES ALL DATA STRUCTURES:
 * - Array: Patient database for permanent storage
 * - PriorityQueue: Triage system with 5 priority levels
 * - CircularQueue: Consultation rooms management
 * - Stack: Patient consultation history (LIFO)
 * 
 * PATIENT FLOW:
 * 1. Registration → Array + PriorityQueue
 * 2. Triage waiting → PriorityQueue  
 * 3. Consultation → CircularQueue
 * 4. Completion → Stack (history)
 */
class HospitalSystem {
private:
    // DATA STRUCTURES USING PATIENT POINTERS
    Array<Patient*>* registeredPatients;  ///< Dynamic array - all patients database
    PriorityQueue<Patient*>* triage;      ///< Priority queue - waiting patients by urgency
    CircularQueue<Patient*>* consultationRooms; ///< Circular queue - active consultations
    Stack<Patient*>* history;             ///< Stack - recently completed patients

    int nextPatientID;           ///< Auto-incrementing patient ID generator
    int numberOfConsultationRooms; ///< Fixed number of consultation rooms

    // PRIVATE METHODS - Implementation details
    void registerPatient(std::string name, int age, int priority, std::string symptom);
    void attendNextPatient();
    void freeConsultationRoom();
    void displaySystemState();
    void displayPatientDatabase();
    void searchPatient(int patientId);
    void mainMenu();

public:
    /**
     * HOSPITAL SYSTEM CONSTRUCTOR
     * @param numRooms: Number of consultation rooms (default: 3)
     * 
     * MEMORY ALLOCATION:
     * - Dynamically allocates all data structures
     * - Initializes patient ID counter starting from 1
     * - Sets up Colombian triage system with 5 priority levels
     */
    HospitalSystem(int numRooms = 3);
    
    /**
     * HOSPITAL SYSTEM DESTRUCTOR
     * 
     * MEMORY CLEANUP:
     * - Deletes all Patient objects to prevent memory leaks
     * - Deletes all data structure containers
     * - Called automatically when object goes out of scope
     */
    ~HospitalSystem();
    
    /**
     * STATIC APPLICATION ENTRY POINT
     * 
     * DESIGN:
     * - Static method doesn't require object instance
     * - Creates HospitalSystem instance and runs main menu
     * - Handles exceptions at application level
     * - Ensures proper cleanup through RAII
     */
    static void runApplication();

    // Delete copy constructor and assignment operator to prevent copying
    HospitalSystem(const HospitalSystem&) = delete;
    HospitalSystem& operator=(const HospitalSystem&) = delete;
};

#endif
