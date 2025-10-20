#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdio>

/**
 * NODE TEMPLATE CLASS
 * 
 * LINKED LIST NODE STRUCTURE:
 * - Contains data of type T
 * - Contains pointer to next node
 * - Forms the building block of linked list
 */
template <typename T>
class Node {
public:
    T data;           // Data stored in node
    Node<T>* next;    // Pointer to next node

    /**
     * NODE CONSTRUCTOR
     * @param d: Data to store in node
     * 
     * POINTER INITIALIZATION:
     * - 'next' is initialized to NULL
     * - Prevents dangling pointer issues
     */
    Node(T d) {
        data = d;
        next = NULL;
    }
};

/**
 * LINKED LIST TEMPLATE CLASS (ABSTRACT)
 * 
 * FEATURES:
 * - Base class for Stack and Queue
 * - Virtual add method for polymorphism
 * - Memory management with clear() method
 * - Sorting using merge sort algorithm
 */
template <typename T>
class List {
protected:
    Node<T>* head;    // Pointer to first node in list
    Node<T>* last;    // Pointer to last node in list
    int length;       // Number of elements in list

public:
    /**
     * LIST CONSTRUCTOR
     * 
     * POINTER INITIALIZATION:
     * - head and last initialized to NULL
     * - Indicates empty list
     */
    List() {
        head = NULL;
        last = NULL;
        length = 0;
    }

    /**
     * LIST DESTRUCTOR
     * 
     * MEMORY MANAGEMENT:
     * - Calls clear() to free all node memory
     * - Prevents memory leaks by cleaning up nodes
     */
    ~List() {
        clear();
    }

    /**
     * CLEAR LIST - FREE ALL MEMORY
     * 
     * MEMORY CLEANUP PROCESS:
     * 1. Traverse list from head to tail
     * 2. Delete each node
     * 3. Reset head, last pointers and length
     */
    void clear() {
        while (!isEmpty()) {
            Node<T>* temp = head;  // Store current head
            head = head->next;     // Move head to next node
            delete temp;           // Free current node memory
        }
        head = last = NULL;  // Reset pointers
        length = 0;          // Reset length
    }

    /**
     * VIRTUAL ADD METHOD
     * @param data: Data to add to list
     * 
     * POLYMORPHISM:
     * - Pure virtual function (must be implemented by derived classes)
     * - Allows different addition strategies (LIFO vs FIFO)
     */
    virtual void add(T data) = 0;

    /**
     * CHECK IF LIST IS EMPTY
     * @return true if list is empty, false otherwise
     */
    bool isEmpty() {
        return head == NULL;
    }

    /**
     * GET NUMBER OF ELEMENTS IN LIST
     * @return Current length of list
     */
    int len() {
        return length;
    }
    /**
     * PEEK - if list is not empty returns the data in the first node of the list pointed by head
     */
    T peek() {
    if (!isEmpty()) {
        return head->data;
    }
    throw std::runtime_error("List is empty - cannot peek");
        }
    /**
     * CONTAINS - CHECKS IF ANY NODE FULLFILLS THE CONDITION ESPECIFIED IN @param
     */
    bool contains(std::function<bool(T)> condition) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (condition(current->data)) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    /**
     * REMOVE AND RETURN FIRST ELEMENT
     * @return Data from first element
     * 
     * MEMORY MANAGEMENT:
     * - Deletes the node after retrieving data
     * - Updates head pointer to next node
     * - Throws exception if list is empty
     */
    T pop() {
        if (!isEmpty()) {
            Node<T>* temp = head;      // Store current head
            T data = head->data;       // Retrieve data
            head = head->next;         // Move head to next node
            
            delete temp;               // Free old head memory
            
            // Update last pointer if list becomes empty
            if (isEmpty()) {
                last = NULL;
            }
            
            length--;                  // Decrement length
            return data;               // Return retrieved data
        }
        throw 0; // Throw exception if list is empty
    }

    /**
     * REVERSE THE LINKED LIST
     * 
     * ALGORITHM:
     * - Uses three pointers: previous, current, next
     * - Traverses list reversing link directions
     * - Updates head and last pointers
     */
    void reverse() {
        if (!isEmpty() && head != last) {
            Node<T>* current = head;
            Node<T>* nextNode = NULL;
            Node<T>* previous = NULL;
            
            // Reverse links while traversing
            while (current != NULL) {
                nextNode = current->next;  // Store next node
                current->next = previous;  // Reverse link
                previous = current;        // Move previous forward
                current = nextNode;        // Move current forward
            }
            
            // Swap head and last pointers
            current = head;
            head = last;
            last = current;
        }
    }

    /**
     * MERGE SORT IMPLEMENTATION (RECURSIVE)
     * @param h: Head of sublist to sort
     * @return Sorted list head
     * 
     * ALGORITHM STEPS:
     * 1. Split list into two halves
     * 2. Recursively sort each half
     * 3. Merge the two sorted halves
     */
    Node<T>* mergeSort(Node<T>* h) {
        if (h->next != NULL) {
            // Split list into two halves
            Node<T>* left = h;
            Node<T>* right = h->next;
            Node<T>* lastLeft = left;
            Node<T>* lastRight = right;
            bool flag = true;
            Node<T>* current = right->next;
            
            // Alternate nodes between left and right lists
            while (current != NULL) {
                if (flag) {
                    lastLeft->next = current;
                    lastLeft = current;
                } else {
                    lastRight->next = current;
                    lastRight = current;
                }
                current = current->next;
                flag = !flag;
            }
            
            // Terminate both lists
            lastLeft->next = NULL;
            lastRight->next = NULL;
            
            // Recursively sort both halves
            left = mergeSort(left);
            right = mergeSort(right);
            
            // Merge the sorted halves
            if (left->data < right->data) {
                h = left;
                left = left->next;
            } else {
                h = right;
                right = right->next;
            }
            
            Node<T>* currentTail = h;
            
            // Merge process
            while (left != NULL && right != NULL) {
                if (left->data < right->data) {
                    currentTail->next = left;
                    currentTail = left;
                    left = left->next;
                } else {
                    currentTail->next = right;
                    currentTail = right;
                    right = right->next;
                }
            }
            
            // Append remaining elements
            if (left != NULL) {
                currentTail->next = left;
            } else {
                currentTail->next = right;
            }
        }
        return h;
    }

    /**
     * SORT THE LINKED LIST
     * 
     * WRAPPER FUNCTION:
     * - Calls recursive mergeSort method
     * - Updates last pointer after sorting
     */
    void sort() {
        if (head != NULL) {
            head = mergeSort(head);
            
            // Update last pointer to point to tail
            last = head;
            while (last->next != NULL) { 
                last = last->next; 
            }
        }
    }

    /**
     * PRINT LIST TO OUTPUT STREAM
     * @param os: Output stream reference
     * 
     * FORMAT: "length data1 data2 ... dataN"
     */
    void print(std::ostream& os) {
        os << length;  // Print length first
        Node<T>* current = head;
        
        // Print each element
        while (current != NULL) {
            os << ' ' << current->data;
            current = current->next;
        }
    }

    /**
     * READ LIST FROM INPUT STREAM
     * @param is: Input stream reference
     * 
     * FORMAT: "length data1 data2 ... dataN"
     */
    void read(std::istream& is) {
        clear();  // Clear existing list
        
        T data;
        int n;
        is >> n;  // Read number of elements
        
        // Read and add each element
        for (int i = 0; i < n; i++) {
            is >> data;
            if (isEmpty()) {
                // Create first node
                head = new Node<T>(data);
                last = head;
            } else {
                // Append to end of list
                last->next = new Node<T>(data);
                last = last->next;
            }
            length++;
        }
    }
};

/**
 * OUTPUT STREAM OPERATOR OVERLOADING
 * @param os: Output stream
 * @param l: List to print
 * @return Output stream reference
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, List<T>& l) {
    l.print(os);
    return os;
}

/**
 * INPUT STREAM OPERATOR OVERLOADING
 * @param is: Input stream
 * @param l: List to read into
 * @return Input stream reference
 */
template <typename T>
std::istream& operator>>(std::istream& is, List<T>& l) {
    l.read(is);
    return is;
}

#endif
