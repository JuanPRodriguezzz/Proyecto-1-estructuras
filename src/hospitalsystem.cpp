#include "hospitalsystem.h"
#include <iostream>
#include <limits>

using namespace std;

/**
 * HOSPITAL SYSTEM CONSTRUCTOR IMPLEMENTATION
 * @param numRooms: Number of consultation rooms to create
 * 
 * MEMORY ALLOCATION BREAKDOWN:
 * - registeredPatients: Array of Patient pointers (capacity 100)
 * - triage: PriorityQueue for patient triage
 * - consultationRooms: CircularQueue for room management  
 * - history: Stack for patient history
 */
HospitalSystem::HospitalSystem(int numRooms) 
    : nextPatientID(1), numberOfConsultationRooms(numRooms) {
    
    // Initialize all data structures with dynamic allocation
    registeredPatients = new Array<Patient*>(100);  // Capacity for 100 patients
    triage = new PriorityQueue<Patient*>();
    consultationRooms = new CircularQueue<Patient*>(numberOfConsultationRooms);
    history = new Stack<Patient*>();
    
    cout << "=== HOSPITAL MANAGEMENT SYSTEM INITIALIZED ===" << endl;
    cout << "Consultation rooms: " << numberOfConsultationRooms << endl;
    cout << "Patient database capacity: 100" << endl;
    cout << "Triage system: Ready" << endl;
    cout << "History tracking: Enabled" << endl;
    cout << "=============================================" << endl;
}

/**
 * HOSPITAL SYSTEM DESTRUCTOR IMPLEMENTATION
 * 
 * MEMORY CLEANUP PROCESS:
 * 1. Delete all Patient objects in registeredPatients array
 * 2. Delete the data structure objects themselves
 * 3. All linked list nodes are automatically cleaned by List destructor
 */
HospitalSystem::~HospitalSystem() {
    // STEP 1: Delete all Patient objects to prevent memory leaks
    cout << "\n=== SYSTEM SHUTDOWN INITIATED ===" << endl;
    cout << "Cleaning up patient records..." << endl;
    
    int patientCount = registeredPatients->len();
    for (int i = 0; i < patientCount; i++) {
        delete (*registeredPatients)[i];  // Delete each Patient object
    }
    cout << "Deleted " << patientCount << " patient records" << endl;

    // STEP 2: Delete the data structure containers
    delete registeredPatients;  // Delete Array object
    delete triage;              // Delete PriorityQueue object  
    delete consultationRooms;   // Delete CircularQueue object
    delete history;             // Delete Stack object
    
    cout << "Memory cleanup completed successfully" << endl;
    cout << "=== SYSTEM SHUTDOWN COMPLETE ===" << endl;
}

/**
 * REGISTER NEW PATIENT METHOD
 * @param name: Patient's full name
 * @param age: Patient's age
 * @param priority: Triage priority (1=High, 2=Medium, 3=Low)
 * @param symptom: Medical symptom description
 * 
 * PATIENT LIFECYCLE:
 * 1. Patient object created in heap with new
 * 2. Added to registeredPatients array for permanent storage
 * 3. Added to triage queue for medical attention
 * 4. Same pointer used in both structures - no object copying
 */
void HospitalSystem::registerPatient(string name, int age, int priority, string symptom) {
    // Validate input parameters
    if (name.empty()) {
        throw invalid_argument("Patient name cannot be empty");
    }
    if (age <= 0 || age > 150) {
        throw invalid_argument("Invalid age. Must be between 1 and 150");
    }
    if (priority < 1 || priority > 3) {
        throw invalid_argument("Invalid priority. Must be 1 (High), 2 (Medium), or 3 (Low)");
    }
    if (symptom.empty()) {
        throw invalid_argument("Symptom description cannot be empty");
    }

    // Create new Patient object in heap
    Patient* newPatient = new Patient(nextPatientID++, name, age, priority, symptom);
    
    try {
        // Add patient to database (registeredPatients array)
        registeredPatients->append(newPatient);
        
        // Add patient to triage system (priority queue)
        triage->add(newPatient);
        
        cout << "\n✅ PATIENT REGISTERED SUCCESSFULLY" << endl;
        cout << "Patient ID: " << newPatient->id << endl;
        cout << "Name: " << newPatient->name << endl;
        cout << "Age: " << newPatient->age << endl;
        cout << "Priority: " << newPatient->priority;
        
        // Display priority description
        switch (newPatient->priority) {
            case 1: cout << " (High - Immediate attention required)"; break;
            case 2: cout << " (Medium - Attention within 30 minutes)"; break;
            case 3: cout << " (Low - Routine consultation)"; break;
        }
        cout << endl;
        
        cout << "Symptom: " << newPatient->symptom << endl;
        cout << "Added to triage queue. Waiting patients: " << triage->len() << endl;
    }
    catch (...) {
        // Exception safety: if anything fails, delete the patient to prevent memory leak
        delete newPatient;
        nextPatientID--;  // Rollback ID counter
        throw;  // Re-throw the exception
    }
}

/**
 * ATTEND NEXT PATIENT FROM TRIAGE TO CONSULTATION
 * 
 * PATIENT FLOW:
 * 1. Remove highest priority patient from triage queue
 * 2. Assign to available consultation room
 * 3. Patient moves from waiting state to active consultation
 * 
 * EXCEPTION SCENARIOS:
 * - No patients in triage queue
 * - All consultation rooms occupied
 */
void HospitalSystem::attendNextPatient() {
    // Check if there are patients waiting
    if (triage->isEmpty()) {
        cout << "\n❌ No patients waiting in triage" << endl;
        return;
    }

    // Check if consultation rooms are available
    if (consultationRooms->isFull()) {
        cout << "\n❌ All consultation rooms are occupied" << endl;
        cout << "Please free a room before attending next patient" << endl;
        return;
    }

    try {
        // Get next patient from triage (highest priority)
        Patient* nextPatient = triage->pop();
        
        // Assign patient to consultation room
        consultationRooms->enqueue(nextPatient);
        
        cout << "\n✅ PATIENT ASSIGNED TO CONSULTATION ROOM" << endl;
        cout << "Patient: " << *nextPatient << endl;
        cout << "Consultation rooms occupied: " << consultationRooms->size() 
             << "/" << consultationRooms->getCapacity() << endl;
        cout << "Patients remaining in triage: " << triage->len() << endl;
    }
    catch (const exception& e) {
        cout << "\n❌ Error attending patient: " << e.what() << endl;
    }
}

/**
 * FREE CONSULTATION ROOM - COMPLETE PATIENT CONSULTATION
 * 
 * PATIENT FLOW:
 * 1. Remove patient from consultation room
 * 2. Add patient to history stack (most recent first)
 * 3. Room becomes available for next patient
 * 
 * DATA STRUCTURE INTERACTION:
 * - CircularQueue.dequeue(): removes patient from room
 * - Stack.add(): adds patient to history (LIFO order)
 */
void HospitalSystem::freeConsultationRoom() {
    // Check if there are occupied rooms
    if (consultationRooms->isEmpty()) {
        cout << "\n❌ No consultation rooms are currently occupied" << endl;
        return;
    }

    try {
        // Remove patient from consultation room
        Patient* completedPatient = consultationRooms->dequeue();
        
        // Add patient to history stack
        history->add(completedPatient);
        
        cout << "\n✅ CONSULTATION ROOM FREED" << endl;
        cout << "Patient consultation completed: " << *completedPatient << endl;
        cout << "Patient added to history stack" << endl;
        cout << "Available rooms: " << consultationRooms->getCapacity() - consultationRooms->size() 
             << "/" << consultationRooms->getCapacity() << endl;
    }
    catch (const exception& e) {
        cout << "\n❌ Error freeing consultation room: " << e.what() << endl;
    }
}

/**
 * DISPLAY COMPLETE SYSTEM STATE
 * 
 * COMPREHENSIVE OVERVIEW:
 * - Triage queue status and patients
 * - Consultation room occupancy
 * - Recent patient history
 * - System statistics and summary
 */
void HospitalSystem::displaySystemState() {
    cout << "\n==================================================" << endl;
    cout << "         HOSPITAL SYSTEM COMPLETE STATUS" << endl;
    cout << "==================================================" << endl;
    
    // Display triage system state
    triage->displayState();
    
    // Display consultation rooms state
    consultationRooms->displayState();
    
    // Display history information
    cout << "\n=== RECENT PATIENT HISTORY (STACK) ===" << endl;
    if (history->isEmpty()) {
        cout << "No patients in history - no consultations completed yet" << endl;
    } else {
        cout << "Most recent patient: " << *(history->peek()) << endl;
        cout << "Total patients in history: " << history->len() << endl;
        
        // Show history depth information
        if (history->len() > 1) {
            cout << "History tracks last " << history->len() << " completed consultations" << endl;
        }
    }
    
    // System summary
    cout << "\n=== SYSTEM SUMMARY ===" << endl;
    cout << "Total registered patients: " << registeredPatients->len() << endl;
    cout << "Patients waiting in triage: " << triage->len() << endl;
    cout << "Patients in consultation: " << consultationRooms->size() << endl;
    cout << "Patients in history: " << history->len() << endl;
    cout << "Next available patient ID: " << nextPatientID << endl;
}

/**
 * DISPLAY ALL PATIENTS IN DATABASE
 * 
 * DATABASE VIEW:
 * - Shows all patients ever registered
 * - Includes current status (waiting, in consultation, completed)
 * - Useful for administrative purposes
 */
void HospitalSystem::displayPatientDatabase() {
    cout << "\n=== COMPLETE PATIENT DATABASE ===" << endl;
    cout << "Total patients: " << registeredPatients->len() << endl;
    cout << "=================================" << endl;
    
    if (registeredPatients->len() == 0) {
        cout << "No patients in database" << endl;
        return;
    }

    for (int i = 0; i < registeredPatients->len(); i++) {
        Patient* patient = (*registeredPatients)[i];
        cout << (i + 1) << ". " << *patient;
        
        // Display current status
        if (triage->contains(patient->id)) {
            cout << " [STATUS: Waiting in triage]";
        } else if (consultationRooms->isPatientInConsultation(patient->id)) {
            int room = consultationRooms->findPatientRoom(patient->id);
            cout << " [STATUS: In consultation room " << room << "]";
        } else {
            cout << " [STATUS: Consultation completed]";
        }
        cout << endl;
    }
}

/**
 * SEARCH FOR SPECIFIC PATIENT BY ID
 * @param patientId: ID of patient to search for
 * 
 * SEARCH FUNCTIONALITY:
 * - Searches all data structures for patient
 * - Provides comprehensive status information
 * - Useful for patient tracking and inquiries
 */
void HospitalSystem::searchPatient(int patientId) {
    cout << "\n=== PATIENT SEARCH ===" << endl;
    cout << "Searching for patient ID: " << patientId << endl;
    
    bool found = false;
    
    // Search in registered patients database
    for (int i = 0; i < registeredPatients->len(); i++) {
        Patient* patient = (*registeredPatients)[i];
        if (patient->id == patientId) {
            found = true;
            cout << "✅ PATIENT FOUND IN DATABASE" << endl;
            cout << "Details: " << *patient << endl;
            
            // Check current status
            if (triage->contains(patientId)) {
                cout << "📍 CURRENT STATUS: Waiting in triage queue" << endl;
            } else if (consultationRooms->isPatientInConsultation(patientId)) {
                int room = consultationRooms->findPatientRoom(patientId);
                cout << "📍 CURRENT STATUS: In consultation room " << room << endl;
            } else {
                cout << "📍 CURRENT STATUS: Consultation completed" << endl;
            }
            break;
        }
    }
    
    if (!found) {
        cout << "❌ Patient ID " << patientId << " not found in system" << endl;
    }
}

/**
 * MAIN MENU - USER INTERFACE
 * 
 * MENU DRIVEN INTERFACE:
 * - Provides intuitive navigation
 * - Handles user input with validation
 * - Calls appropriate system methods
 */
void HospitalSystem::mainMenu() {
    int choice;
    
    do {
        cout << "\n==================================================" << endl;
        cout << "          HOSPITAL MANAGEMENT SYSTEM" << endl;
        cout << "==================================================" << endl;
        cout << "1. Register New Patient" << endl;
        cout << "2. Attend Next Patient (Triage → Consultation)" << endl;
        cout << "3. Free Consultation Room (Consultation → History)" << endl;
        cout << "4. Display Complete System State" << endl;
        cout << "5. View Patient Database" << endl;
        cout << "6. Search Patient by ID" << endl;
        cout << "7. Exit System" << endl;
        cout << "==================================================" << endl;
        cout << "Select an option (1-7): ";
        
        cin >> choice;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: {
                    string name, symptom;
                    int age, priority;
                    
                    cout << "\n--- PATIENT REGISTRATION ---" << endl;
                    cout << "Enter patient name: ";
                    getline(cin, name);
                    
                    cout << "Enter patient age: ";
                    cin >> age;
                    
                    cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
                    cin >> priority;
                    
                    cin.ignore(); // Clear newline
                    cout << "Enter symptoms: ";
                    getline(cin, symptom);
                    
                    registerPatient(name, age, priority, symptom);
                    break;
                }
                
                case 2:
                    attendNextPatient();
                    break;
                    
                case 3:
                    freeConsultationRoom();
                    break;
                    
                case 4:
                    displaySystemState();
                    break;
                    
                case 5:
                    displayPatientDatabase();
                    break;
                    
                case 6: {
                    int searchId;
                    cout << "Enter patient ID to search: ";
                    cin >> searchId;
                    searchPatient(searchId);
                    break;
                }
                    
                case 7:
                    cout << "\nThank you for using Hospital Management System!" << endl;
                    break;
                    
                default:
                    cout << "\n❌ Invalid option. Please select 1-7." << endl;
            }
        }
        catch (const exception& e) {
            cout << "\n❌ Error: " << e.what() << endl;
            cout << "Please try again with valid input." << endl;
        }
        
    } while (choice != 7);
}

/**
 * STATIC APPLICATION ENTRY POINT
 * 
 * APPLICATION LIFECYCLE:
 * 1. Create HospitalSystem instance
 * 2. Run main menu (blocking call)
 * 3. Automatic cleanup when menu exits
 * 4. Exception handling at application level
 */
void HospitalSystem::runApplication() {
    cout << "🚀 INITIALIZING HOSPITAL MANAGEMENT SYSTEM" << endl;
    cout << "Version: 1.0 | Data Structures: Array, PriorityQueue, CircularQueue, Stack" << endl;
    
    try {
        // Create hospital system instance with 3 consultation rooms
        HospitalSystem hospital(3);
        
        // Run the main menu - this blocks until user chooses to exit
        hospital.mainMenu();
    }
    catch (const exception& e) {
        // Handle any critical system errors
        cout << "\n💥 CRITICAL SYSTEM ERROR: " << e.what() << endl;
        cout << "The system must shut down due to an unrecoverable error." << endl;
    }
    
    cout << "\n👋 Hospital Management System terminated" << endl;
}
