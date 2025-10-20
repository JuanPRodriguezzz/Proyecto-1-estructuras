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
 * - Array: Patient database
 * - PriorityQueue: Triage system  
 * - CircularQueue: Consultation rooms
 * - Stack: Patient history
 * 
 * DESIGN PATTERN:
 * - Facade pattern: provides simple interface to complex subsystem
 * - RAII: manages memory automatically through constructors/destructors
 * - Singleton-like: static method for application entry point
 */

class HospitalSystem {
private:
    // DATA STRUCTURES USING PATIENT POINTERS
    Array<Patient*>* registeredPatients;  // Dynamic array - all patients database
    PriorityQueue<Patient*>* triage;      // Priority queue - waiting patients by urgency
    CircularQueue<Patient*>* consultationRooms; // Circular queue - active consultations
    Stack<Patient*>* history;             // Stack - recently completed patients

    int nextPatientID;           // Auto-incrementing patient ID generator
    int numberOfConsultationRooms; // Fixed number of consultation rooms

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
     * - Initializes patient ID counter
     */
    HospitalSystem(int numRooms = 3);
    
    /**
     * HOSPITAL SYSTEM DESTRUCTOR
     * 
     * MEMORY CLEANUP:
     * - Deletes all patient objects to prevent memory leaks
     * - Deletes all data structure objects
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
     */
    static void runApplication();

    // Delete copy constructor and assignment operator to prevent copying
    HospitalSystem(const HospitalSystem&) = delete;
    HospitalSystem& operator=(const HospitalSystem&) = delete;
};

#endif
