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
};

#endif
