#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

/**
 * PATIENT CLASS
 * 
 * REPRESENTS A HOSPITAL PATIENT WITH:
 * - Unique identifier
 * - Personal information
 * - Medical priority level
 * - Medical symptoms
 * 
 * OPERATOR OVERLOADING:
 * - Comparison operators for priority-based sorting
 * - Output stream operator for easy printing
 */
class Patient {
public:
    int id;              // Unique patient identifier
    std::string name;    // Patient's full name
    int age;             // Patient's age
    int priority;        // Triage priority (1=High, 2=Medium, 3=Low)
    std::string symptom; // Medical symptom description

    /**
     * PATIENT CONSTRUCTOR
     * @param _id: Unique patient ID
     * @param _name: Patient's name
     * @param _age: Patient's age
     * @param _priority: Triage priority level
     * @param _symptom: Medical symptom
     * 
     * INITIALIZATION:
     * - Uses member initialization list for efficiency
     * - Directly initializes all member variables
     */
    Patient(int _id, std::string _name, int _age, int _priority, std::string _symptom)
        : id(_id), name(_name), age(_age), priority(_priority), symptom(_symptom) {}

    /**
     * LESS-THAN OPERATOR OVERLOADING
     * @param other: Patient to compare against
     * @return true if this patient has higher priority
     * 
     * PRIORITY SYSTEM:
     * - Lower priority number = higher urgency
     * - Used for sorting in priority queue
     */
    bool operator<(const Patient& other) const {
        return this->priority < other.priority;
    }

    /**
     * GREATER-THAN OPERATOR OVERLOADING
     * @param other: Patient to compare against
     * @return true if this patient has lower priority
     */
    bool operator>(const Patient& other) const {
        return this->priority > other.priority;
    }

    /**
     * EQUALITY OPERATOR OVERLOADING
     * @param other: Patient to compare against
     * @return true if patients have same ID
     * 
     * USAGE:
     * - Patient identification and searching
     */
    bool operator==(const Patient& other) const {
        return this->id == other.id;
    }

    /**
     * OUTPUT STREAM OPERATOR OVERLOADING (FRIEND FUNCTION)
     * @param os: Output stream
     * @param p: Patient to output
     * @return Output stream reference
     * 
     * FRIEND FUNCTION:
     * - Can access private members of Patient class
     * - Allows natural syntax: cout << patient
     */
    friend std::ostream& operator<<(std::ostream& os, const Patient& p) {
        os << "ID: " << p.id << " | " << p.name << " | Age: " << p.age 
           << " | Priority: " << p.priority << " | Symptom: " << p.symptom;
        return os;
    }
};

#endif
