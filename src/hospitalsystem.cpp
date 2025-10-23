#include "hospitalsystem.h"
#include <iostream>
#include <limits>

using namespace std;

/**
 * HOSPITAL SYSTEM CONSTRUCTOR IMPLEMENTATION
 * @param numRooms: Number of consultation rooms to create
 * 
 * MEMORY ALLOCATION BREAKDOWN:
 * - registeredPatients: Array of Patient pointers (capacity 200)
 * - triage: PriorityQueue with 5 levels for Colombian triage
 * - consultationRooms: CircularQueue for room management  
 * - history: Stack for patient history (LIFO order)
 * 
 * INITIALIZATION:
 * - Patient ID counter starts at 1
 * - All data structures start empty
 * - Consultation rooms configured with specified capacity
 */
HospitalSystem::HospitalSystem(int numRooms) 
    : nextPatientID(1), numberOfConsultationRooms(numRooms) {
    
    // Initialize all data structures with dynamic allocation
    registeredPatients = new Array<Patient*>(200);  // Capacity for 200 patients
    triage = new PriorityQueue<Patient*>();         // Default 5 priority levels
    consultationRooms = new CircularQueue<Patient*>(numberOfConsultationRooms);
    history = new Stack<Patient*>();
    
    cout << "=== HOSPITAL MANAGEMENT SYSTEM INITIALIZED ===" << endl;
    cout << "Consultation rooms: " << numberOfConsultationRooms << endl;
    cout << "Triage system: Colombian 5-level priority" << endl;
    cout << "Patient database capacity: 200" << endl;
    cout << "=============================================" << endl;
}

/**
 * HOSPITAL SYSTEM DESTRUCTOR IMPLEMENTATION
 * 
 * MEMORY CLEANUP PROCESS:
 * 1. Delete all Patient objects in registeredPatients array
 * 2. Delete the data structure containers themselves
 * 3. All linked list nodes are automatically cleaned by List destructors
 * 
 * EXCEPTION SAFETY:
 * - No-throw guarantee: destructor should not throw exceptions
 * - All cleanup operations are exception-safe
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
 * @param age: Patient's age in years
 * @param priority: Triage priority level (1-5 according to Colombian system)
 * @param symptom: Medical symptom description
 * 
 * PATIENT LIFECYCLE - REGISTRATION PHASE:
 * 1. Input validation for all parameters
 * 2. Patient object creation in heap memory
 * 3. Addition to registeredPatients array for permanent storage
 * 4. Addition to triage queue for medical attention prioritization
 * 5. Same pointer used in both structures - no object copying
 * 
 * EXCEPTION SAFETY:
 * - Strong exception guarantee: if registration fails, system state unchanged
 * - Patient object deleted if any operation fails to prevent memory leak
 * - Patient ID counter rolled back on failure
 */
void HospitalSystem::registerPatient(string name, int age, int priority, string symptom) {
    // Validate input parameters
    if (name.empty()) {
        throw invalid_argument("Patient name cannot be empty");
    }
    if (age <= 0 || age > 150) {
        throw invalid_argument("Invalid age. Must be between 1 and 150");
    }
    if (priority < 1 || priority > 5) {
        throw invalid_argument("Invalid priority. Must be 1 (TRIAGE I) to 5 (TRIAGE V)");
    }
    if (symptom.empty()) {
        throw invalid_argument("Symptom description cannot be empty");
    }

    // Create new Patient object in heap memory
    Patient* newPatient = new Patient(nextPatientID++, name, age, priority, symptom);
    
    try {
        // Add patient to database (registeredPatients array)
        registeredPatients->append(newPatient);
        
        // Add patient to triage system (priority queue)
        triage->add(newPatient);
        
        // Success notification with detailed information
        cout << "\n[DONE] PATIENT REGISTERED SUCCESSFULLY" << endl;
        cout << "Patient ID: " << newPatient->id << endl;
        cout << "Name: " << newPatient->name << endl;
        cout << "Age: " << newPatient->age << endl;
        cout << "Priority: " << newPatient->getPriorityDescription() << endl;
        cout << "Symptom: " << newPatient->symptom << endl;
        cout << "Added to triage queue. Waiting patients: " << triage->len() << endl;
    }
    catch (...) {
        // Exception safety: if anything fails, delete the patient to prevent memory leak
        delete newPatient;
        nextPatientID--;  // Rollback ID counter
        throw;  // Re-throw the exception to be handled by caller
    }
}

/**
 * ATTEND NEXT PATIENT - TRIAGE TO CONSULTATION TRANSITION
 * 
 * PATIENT FLOW - CONSULTATION PHASE:
 * 1. Remove highest priority patient from triage queue
 * 2. Assign to available consultation room
 * 3. Patient moves from waiting state to active consultation
 * 4. Update system statistics and notifications
 * 
 * PRECONDITIONS:
 * - Triage queue must not be empty
 * - At least one consultation room must be available
 * 
 * EXCEPTION SCENARIOS:
 * - No patients in triage queue
 * - All consultation rooms occupied
 * - Memory allocation failures (handled by exception mechanism)
 */
void HospitalSystem::attendNextPatient() {
    // Check if there are patients waiting in triage
    if (triage->isEmpty()) {
        cout << "\n[ERROR!] No patients waiting in triage" << endl;
        return;
    }

    // Check if consultation rooms are available
    if (consultationRooms->isFull()) {
        cout << "\n[ERROR!] All consultation rooms are occupied" << endl;
        cout << "Please free a room before attending next patient" << endl;
        return;
    }

    try {
        // Get next patient from triage (highest priority according to Colombian system)
        Patient* nextPatient = triage->pop();
        
        // Assign patient to consultation room
        consultationRooms->enqueue(nextPatient);
        
        // Success notification with system status update
        cout << "\n[DONE] PATIENT ASSIGNED TO CONSULTATION ROOM" << endl;
        cout << "Patient: " << *nextPatient << endl;
        cout << "Consultation rooms occupied: " << consultationRooms->size() 
             << "/" << consultationRooms->getCapacity() << endl;
        cout << "Patients remaining in triage: " << triage->len() << endl;
    }
    catch (const exception& e) {
        cout << "\n!! Error attending patient: " << e.what() << endl;
    }
}

/**
 * FREE CONSULTATION ROOM - COMPLETE PATIENT CONSULTATION
 * 
 * PATIENT FLOW - COMPLETION PHASE:
 * 1. Remove patient from consultation room
 * 2. Add patient to history stack (most recent first)
 * 3. Room becomes available for next patient
 * 4. Update system statistics and notifications
 * 
 * DATA STRUCTURE INTERACTION:
 * - CircularQueue.dequeue(): removes patient from room (FIFO)
 * - Stack.add(): adds patient to history (LIFO order)
 * - Memory: Patient object persists in registeredPatients array
 */
void HospitalSystem::freeConsultationRoom() {
    // Check if there are occupied consultation rooms
    if (consultationRooms->isEmpty()) {
        cout << "\n[ERROR!] No consultation rooms are currently occupied" << endl;
        return;
    }

    try {
        // Remove patient from consultation room (FIFO order)
        Patient* completedPatient = consultationRooms->dequeue();
        
        // Add patient to history stack (LIFO order - most recent first)
        history->add(completedPatient);
        
        // Success notification with system status
        cout << "\n[DONE] CONSULTATION ROOM FREED" << endl;
        cout << "Patient consultation completed: " << *completedPatient << endl;
        cout << "Patient added to history stack" << endl;
        cout << "Available rooms: " << consultationRooms->getCapacity() - consultationRooms->size() 
             << "/" << consultationRooms->getCapacity() << endl;
    }
    catch (const exception& e) {
        cout << "\n!! Error freeing consultation room: " << e.what() << endl;
    }
}

/**
 * DISPLAY COMPLETE SYSTEM STATE
 * 
 * COMPREHENSIVE SYSTEM OVERVIEW:
 * - Triage queue status with Colombian priority levels
 * - Consultation room occupancy and details
 * - Recent patient history from stack
 * - System statistics and summary information
 * 
 * USAGE:
 * - Administrative monitoring and system health checks
 * - Patient flow analysis and resource utilization
 * - Debugging and system maintenance
 */
void HospitalSystem::displaySystemState() {
    cout << "\n==================================================" << endl;
    cout << "         HOSPITAL SYSTEM COMPLETE STATUS" << endl;
    cout << "==================================================" << endl;
    
    // Display triage system state with Colombian priority levels
    triage->displayState();
    
    // Display consultation rooms state and occupancy
    consultationRooms->displayState();
    
    // Display patient history information (LIFO order)
    cout << "\n=== RECENT PATIENT HISTORY (STACK - LIFO) ===" << endl;
    if (history->isEmpty()) {
        cout << "No patients in history - no consultations completed yet" << endl;
    } else {
        cout << "Most recent patient: " << *(history->peek()) << endl;
        cout << "Total patients in history: " << history->len() << endl;
        
        // History depth information for context
        if (history->len() > 1) {
            cout << "History tracks last " << history->len() << " completed consultations" << endl;
            cout << "Displayed in reverse chronological order (most recent first)" << endl;
        }
    }
    
    // Comprehensive system summary
    cout << "\n=== SYSTEM SUMMARY ===" << endl;
    cout << "Total registered patients: " << registeredPatients->len() << endl;
    cout << "Patients waiting in triage: " << triage->len() << endl;
    cout << "Patients in consultation: " << consultationRooms->size() << endl;
    cout << "Patients in history: " << history->len() << endl;
    cout << "Next available patient ID: " << nextPatientID << endl;
    cout << "Consultation room capacity: " << consultationRooms->getCapacity() << endl;
}

/**
 * DISPLAY ALL PATIENTS IN DATABASE WITH CURRENT STATUS
 * 
 * DATABASE VIEW FEATURES:
 * - Shows all patients ever registered in the system
 * - Includes current status (waiting, in consultation, completed)
 * - Provides comprehensive patient information
 * - Useful for administrative reports and patient tracking
 * 
 * STATUS INDICATORS:
 * - [STATUS: Waiting in triage]: Patient in priority queue
 * - [STATUS: In consultation room X]: Patient currently in consultation
 * - [STATUS: Consultation completed]: Patient in history stack
 */
void HospitalSystem::displayPatientDatabase() {
    cout << "\n=== COMPLETE PATIENT DATABASE ===" << endl;
    cout << "Total patients: " << registeredPatients->len() << endl;
    cout << "=================================" << endl;
    
    if (registeredPatients->len() == 0) {
        cout << "No patients in database" << endl;
        return;
    }

    // Iterate through all registered patients
    for (int i = 0; i < registeredPatients->len(); i++) {
        Patient* patient = (*registeredPatients)[i];
        cout << (i + 1) << ". " << *patient;
        
        // Determine and display current patient status
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
 * SEARCH FOR SPECIFIC PATIENT BY ID ACROSS ALL DATA STRUCTURES
 * @param patientId: Unique identifier of patient to search for
 * 
 * SEARCH FUNCTIONALITY:
 * - Searches all data structures for patient with specified ID
 * - Provides comprehensive status and location information
 * - Useful for patient tracking, inquiries, and administrative tasks
 * 
 * SEARCH ALGORITHM:
 * - Linear search through registeredPatients array (primary storage)
 * - Status determination through contains() methods of other structures
 * - Early termination when patient is found
 */
void HospitalSystem::searchPatient(int patientId) {
    cout << "\n=== PATIENT SEARCH ===" << endl;
    cout << "Searching for patient ID: " << patientId << endl;
    
    bool found = false;
    
    // Search in registered patients database (primary storage)
    for (int i = 0; i < registeredPatients->len(); i++) {
        Patient* patient = (*registeredPatients)[i];
        if (patient->id == patientId) {
            found = true;
            cout << "! PATIENT FOUND IN DATABASE" << endl;
            cout << "Details: " << *patient << endl;
            
            // Determine and display current patient status
            if (triage->contains(patientId)) {
                cout << "[WAITING] CURRENT STATUS: Waiting in triage queue" << endl;
                cout << "   Priority: " << patient->getPriorityDescription() << endl;
            } else if (consultationRooms->isPatientInConsultation(patientId)) {
                int room = consultationRooms->findPatientRoom(patientId);
                cout << "[ACTIVE] CURRENT STATUS: In consultation room " << room << endl;
            } else {
                cout << "[DONE] CURRENT STATUS: Consultation completed" << endl;
                cout << "   Patient is in system history" << endl;
            }
            break;
        }
    }
    
    if (!found) {
        cout << "[ERROR!] Patient ID " << patientId << " not found in system" << endl;
        cout << "Please verify the patient ID and try again" << endl;
    }
}

/**
 * MAIN MENU - USER INTERFACE FOR HOSPITAL SYSTEM
 * 
 * MENU-DRIVEN INTERFACE FEATURES:
 * - Intuitive navigation with numbered options
 * - Comprehensive input validation and error handling
 * - Clear user prompts and feedback messages
 * - Exception handling at user interface level
 * 
 * MENU OPTIONS:
 * 1. Patient registration with Colombian triage priorities
 * 2. Patient transition from triage to consultation
 * 3. Consultation completion and room freeing
 * 4. Comprehensive system status display
 * 5. Complete patient database view
 * 6. Patient search by ID across all structures
 * 7. Graceful system exit and cleanup
 */
void HospitalSystem::mainMenu() {
    int choice;
    
    do {
        cout << "\n=======================================" << endl;
        cout << "     HOSPITAL MANAGEMENT SYSTEM     " << endl;
        cout << "=========================================" << endl;
        cout << "1. Register New Patient" << endl;
        cout << "2. Attend Next Patient (Triage -> Consultation)" << endl;
        cout << "3. Free Consultation Room (Consultation -> History)" << endl;
        cout << "4. Display Complete System State" << endl;
        cout << "5. View Patient Database" << endl;
        cout << "6. Search Patient by ID" << endl;
        cout << "7. Exit System" << endl;
        cout << "==========================================" << endl;
        cout << "Select an option (1-7): ";
        
        cin >> choice;
        
        // Clear input buffer to prevent issues with subsequent inputs
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
                    
                    cout << "Enter priority (1=TRIAGE I, 2=TRIAGE II, 3=TRIAGE III, 4=TRIAGE IV, 5=TRIAGE V): ";
                    cin >> priority;
                    
                    cin.ignore(); // Clear newline from input buffer
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
                    cout << "System developed with Colombian triage standards" << endl;
                    break;
                    
                default:
                    cout << "\n!! Invalid option. Please select a number between 1 and 7." << endl;
            }
        }
        catch (const exception& e) {
            cout << "\n[ERROR!]: " << e.what() << endl;
            cout << "Please try again with valid input." << endl;
        }
        
    } while (choice != 7);
}

/**
 * STATIC APPLICATION ENTRY POINT
 * 
 * APPLICATION LIFECYCLE MANAGEMENT:
 * 1. System initialization with exception handling
 * 2. Main menu execution (blocking call)
 * 3. Automatic resource cleanup through RAII
 * 4. Graceful error handling and user notification
 * 
 * EXCEPTION HANDLING:
 * - Catches all exceptions at application level
 * - Provides user-friendly error messages
 * - Ensures proper system shutdown on critical errors
 */
void HospitalSystem::runApplication() {
    cout << "[STARTING] INITIALIZING HOSPITAL MANAGEMENT SYSTEM" << endl;
    cout << "Version: 2.0 | Colombian Triage System (5 levels)" << endl;
    cout << "Data Structures: Array, PriorityQueue, CircularQueue, Stack" << endl;
    
    try {
        // Create hospital system instance with default consultation rooms
        HospitalSystem hospital(10);
        
        // Run the main menu - blocking call until user exits
        hospital.mainMenu();
    }
    catch (const exception& e) {
        // Handle any critical system initialization errors
        cout << "\n!! CRITICAL SYSTEM ERROR: " << e.what() << endl;
        cout << "The system must shut down due to an unrecoverable error." << endl;
        cout << "Please contact system administrator." << endl;
    }
    
    cout << "\n👋 Hospital Management System terminated" << endl;
}
