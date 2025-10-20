#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "list.h"
#include "patient.h"

/**
 * PRIORITY QUEUE TEMPLATE CLASS
 * 
 * SPECIALIZED QUEUE WHERE ELEMENTS ARE ORDERED BY PRIORITY
 * Inherits from Professor's List class
 * 
 * HOSPITAL APPLICATION:
 * - Used for patient triage system
 * - Higher priority patients (lower number) are served first
 * - Maintains sorted order based on patient urgency
 * 
 * MEMORY MANAGEMENT:
 * - Stores pointers to Patient objects (Patient*)
 * - Does NOT own the memory - just references existing Patients
 */

template <typename T>
class PriorityQueue : public List<T> {
public:
    /**
     * PRIORITY QUEUE CONSTRUCTOR
     * 
     * INHERITANCE:
     * - Calls base List constructor automatically
     * - Initializes head, last to NULL and length to 0
     */
    PriorityQueue() : List<T>() {}

    /**
     * ADD METHOD - OVERRIDES VIRTUAL METHOD FROM LIST
     * @param data: Pointer to Patient object to add
     * 
     * ALGORITHM:
     * 1. Create new node containing the patient pointer
     * 2. Find correct position based on patient priority
     * 3. Insert node at correct position to maintain sorted order
     * 
     * POINTER MANAGEMENT:
     * - Stores Patient pointers, not Patient objects
     * - Avoids object copying and maintains data consistency
     */
    void add(T data) {
        // Create new node with the patient pointer
        Node<T>* newNode = new Node<T>(data);
        
        // CASE 1: Empty list - new node becomes both head and last
        if (this->isEmpty()) {
            this->head = newNode;
            this->last = newNode;
        } 
        // CASE 2: New patient has higher priority than current head
        // Higher priority = lower priority number (1 > 2 > 3)
        else if (*data < *(this->head->data)) {
            newNode->next = this->head;  // New node points to current head
            this->head = newNode;        // New node becomes new head
        }
        // CASE 3: Find correct position in the middle/end of list
        else {
            Node<T>* current = this->head;    // Start from head
            Node<T>* previous = nullptr;      // Track previous node
            
            // Traverse until we find the correct position
            // Continue while current exists AND current patient has 
            // higher or equal priority than new patient
            while (current != nullptr && *current->data < *data) {
                previous = current;          // Move previous forward
                current = current->next;     // Move current forward
            }
            
            // Insert new node between previous and current
            previous->next = newNode;    // Previous points to new node
            newNode->next = current;     // New node points to current
            
            // If we inserted at the end, update last pointer
            if (current == nullptr) {
                this->last = newNode;
            }
        }
        this->length++;  // Increment element count
    }

    /**
     * PEEK AT NEXT PATIENT WITHOUT REMOVING
     * @return Pointer to next patient in queue
     * 
     * USAGE:
     * - Check who's next without affecting queue
     * - Useful for preview and status displays
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error if queue is empty
     */
    T peek() {
        if (this->isEmpty()) {
            throw std::runtime_error("Priority queue is empty - no patients waiting");
        }
        return this->head->data;  // Return patient pointer at head
    }

    /**
     * DISPLAY CURRENT STATE OF PRIORITY QUEUE
     * 
     * VISUALIZATION:
     * - Shows all patients in priority order
     * - Displays patient details and queue position
     * - Helpful for debugging and system monitoring
     */
    void displayState() {
        if (this->isEmpty()) {
            std::cout << "Priority queue is empty - no patients in triage" << std::endl;
            return;
        }
        
        std::cout << "\n=== PRIORITY QUEUE STATE (TRIAGE SYSTEM) ===" << std::endl;
        std::cout << "Patients ordered by urgency (1=Highest, 3=Lowest)" << std::endl;
        std::cout << "==============================================" << std::endl;
        
        Node<T>* current = this->head;  // Start from highest priority
        int position = 1;
        
        // Traverse and display all patients
        while (current != nullptr) {
            std::cout << position << ". " << *(current->data) << std::endl;
            current = current->next;
            position++;
        }
        std::cout << "Total patients waiting: " << this->length << std::endl;
    }

    /**
     * CHECK IF SPECIFIC PATIENT IS IN QUEUE
     * @param patientId: ID of patient to search for
     * @return true if patient found, false otherwise
     * 
     * SEARCH ALGORITHM:
     * - Linear search through linked list
     * - Uses patient ID for comparison
     */
    bool contains(int patientId) {
        Node<T>* current = this->head;
        
        while (current != nullptr) {
            if (current->data->id == patientId) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    /**
     * GET PATIENT BY POSITION IN QUEUE
     * @param position: Queue position (1-based)
     * @return Pointer to patient at specified position
     * 
     * USAGE:
     * - Access patients by their queue position
     * - Position 1 = highest priority patient
     */
    T getPatientAt(int position) {
        if (position < 1 || position > this->length) {
            throw std::runtime_error("Invalid queue position");
        }
        
        Node<T>* current = this->head;
        for (int i = 1; i < position; i++) {
            current = current->next;
        }
        return current->data;
    }
};

#endif
