#ifndef STACK_H
#define STACK_H

#include "list.h"

/**
 * STACK TEMPLATE CLASS
 * 
 * LIFO (Last-In-First-Out) DATA STRUCTURE
 * Inherits from List class
 * 
 * BEHAVIOR:
 * - Elements added to top (push)
 * - Elements removed from top (pop)
 * - Can peek at top element without removing
 */
template <typename T>
class Stack : public List<T> {
public:
    /**
     * STACK CONSTRUCTOR
     * Calls base List constructor
     */
    Stack() : List<T>() {}

    /**
     * ADD ELEMENT TO STACK (PUSH OPERATION)
     * @param data: Element to add to stack
     * 
     * STACK BEHAVIOR:
     * - New element becomes the new head
     * - Implements LIFO ordering
     */
    void add(T data) {
        if (this->isEmpty()) {
            // First element in stack
            this->head = new Node<T>(data);
            this->last = this->head;
        } else {
            // Add to front (top of stack)
            Node<T>* temp = new Node<T>(data);
            temp->next = this->head;  // New node points to old head
            this->head = temp;        // New node becomes head
        }
        this->length++;  // Increment length
    }

    /**
     * PEEK AT TOP ELEMENT WITHOUT REMOVING
     * @return Element at top of stack
     * 
     * USAGE:
     * - Check top element without modifying stack
     * - Useful for viewing most recent element
     * 
     * EXCEPTION HANDLING:
     * - Throws runtime_error if stack is empty
     */
    T peek() {
        if (this->isEmpty()) {
            throw std::runtime_error("Stack is empty - cannot peek");
        }
        return this->head->data;  // Return data from top node
    }

    /**
     * CHECK IF STACK CONTAINS SPECIFIC ELEMENT
     * @param data: Element to search for
     * @return true if element found, false otherwise
     */
    bool contains(T data) {
        Node<T>* current = this->head;
        while (current != nullptr) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

#endif
