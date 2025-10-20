#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

/**
 * PATIENT CLASS
 * 
 * Represents a hospital patient with Colombian triage system (5 levels)
 * 
 * COLOMBIAN TRIAGE SYSTEM:
 * - TRIAGE I (1): Emergency - Immediate attention required
 * - TRIAGE II (2): Urgent - High priority conditions  
 * - TRIAGE III (3): Priority - Requires prompt attention
 * - TRIAGE IV (4): Routine - Standard priority conditions
 * - TRIAGE V (5): Non-urgent - Lowest priority conditions
 * 
 * DESIGN:
 * - Uses operator overloading for comparison and sorting
 * - Provides descriptive priority level information
 * - Follows RAII principles for memory safety
 */
class Patient {
public:
    int id;              ///< Unique patient identifier
    std::string name;    ///< Patient's full name
    int age;             ///< Patient's age in years
    int priority;        ///< Triage priority level (1-5 according to Colombian system)
    std::string symptom; ///< Medical symptom description

    /**
     * PATIENT CONSTRUCTOR
     * @param _id: Unique patient identifier
     * @param _name: Patient's full name
     * @param _age: Patient's age in years
     * @param _priority: Triage priority level (1-5)
     * @param _symptom: Medical symptom description
     * 
     * MEMBER INITIALIZATION:
     * - Uses member initialization list for efficient construction
     * - Directly initializes all member variables
     */
    Patient(int _id, std::string _name, int _age, int _priority, std::string _symptom)
        : id(_id), name(_name), age(_age), priority(_priority), symptom(_symptom) {}

    /**
     * LESS-THAN OPERATOR OVERLOADING
     * @param other: Patient to compare against
     * @return true if this patient has higher priority (lower number)
     * 
     * USAGE:
     * - Enables sorting by priority level
     * - Used by merge sort algorithms in Array and List classes
     */
    bool operator<(const Patient& other) const {
        return this->priority < other.priority;
    }

    /**
     * GREATER-THAN OPERATOR OVERLOADING
     * @param other: Patient to compare against
     * @return true if this patient has lower priority (higher number)
     */
    bool operator>(const Patient& other) const {
        return this->priority > other.priority;
    }

    /**
     * EQUALITY OPERATOR OVERLOADING
     * @param other: Patient to compare against
     * @return true if patients have identical IDs
     * 
     * PURPOSE:
     * - Patient identification and duplicate checking
     * - Used in search and contains operations
     */
    bool operator==(const Patient& other) const {
        return this->id == other.id;
    }

    /**
     * GET PRIORITY DESCRIPTION
     * @return String description of the priority level
     * 
     * COLOMBIAN TRIAGE LEVELS:
     * - Level 1: Emergency (life-threatening conditions)
     * - Level 2: Urgent (risk of rapid deterioration)
     * - Level 3: Priority (requires prompt attention)
     * - Level 4: Routine (standard medical conditions)
     * - Level 5: Non-urgent (chronic/minor conditions)
     */
    std::string getPriorityDescription() const {
        switch(priority) {
            case 1: return "TRIAGE I - Emergency";
            case 2: return "TRIAGE II - Urgent";
            case 3: return "TRIAGE III - Priority";
            case 4: return "TRIAGE IV - Routine";
            case 5: return "TRIAGE V - Non-urgent";
            default: return "Unknown Priority";
        }
    }

    /**
     * OUTPUT STREAM OPERATOR OVERLOADING
     * @param os: Output stream reference
     * @param p: Patient object to output
     * @return Output stream reference for chaining
     * 
     * FORMAT:
     * "ID: [id] | [name] | Age: [age] | [priority description] | Symptom: [symptom]"
     * 
     * FRIEND FUNCTION:
     * - Can access private members of Patient class
     * - Enables natural syntax: std::cout << patient
     */
    friend std::ostream& operator<<(std::ostream& os, const Patient& p) {
        os << "ID: " << p.id << " | " << p.name << " | Age: " << p.age 
           << " | " << p.getPriorityDescription() << " | Symptom: " << p.symptom;
        return os;
    }
};

#endif
