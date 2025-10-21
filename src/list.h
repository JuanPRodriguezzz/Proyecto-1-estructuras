#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdio>
#include <functional>

/**
 * NODE TEMPLATE CLASS
 * 
 * BASIC BUILDING BLOCK FOR LINKED LIST:
 * - Stores data of any type T
 * - Contains pointer to next node in sequence
 * - Forms the foundation for all list operations
 */
template <typename T>
class Node {
public:
    T data;           ///< Data element stored in the node
    Node<T>* next;    ///< Pointer to the next node in the list

    /**
     * NODE CONSTRUCTOR
     * @param d: Data element to store in the node
     * 
     * INITIALIZATION:
     * - Sets data to provided value
     * - Initializes next pointer to NULL (safe state)
     */
    Node(T d) {
        data = d;
        next = NULL;
    }
};

/**
 * LINKED LIST TEMPLATE CLASS (CONCRETE IMPLEMENTATION)
 * 
 * MAJOR CHANGE: Converted from abstract to concrete class
 * - Removed pure virtual add() method
 * - Added default FIFO (First-In-First-Out) add behavior
 * - Can now be instantiated directly in Array and other containers
 * 
 * DESIGN PHILOSOPHY:
 * - Provides sensible default behavior (FIFO)
 * - Maintains polymorphism for specialized behaviors (Stack/Queue)
 * - Solves compilation errors with Array instantiation
 */
template <typename T>
class List {
protected:
    Node<T>* head;    ///< Pointer to the first node in the list
    Node<T>* last;    ///< Pointer to the last node in the list  
    int length;       ///< Current number of elements in the list

public:
    /**
     * LIST CONSTRUCTOR
     * 
     * INITIAL STATE:
     * - Empty list (head and last are NULL)
     * - Zero length
     * - Ready for element insertion
     */
    List() {
        head = NULL;
        last = NULL;
        length = 0;
    }

    /**
     * VIRTUAL DESTRUCTOR
     * 
     * CRITICAL FOR POLYMORPHISM:
     * - Ensures proper cleanup of derived classes
     * - Automatically calls clear() to free all nodes
     * - Prevents memory leaks in inheritance hierarchies
     */
    virtual ~List() {
        clear();
    }

    /**
     * CLEAR LIST - FREE ALL MEMORY
     * 
     * MEMORY MANAGEMENT:
     * - Traverses entire list from head to tail
     * - Deletes each node individually
     * - Resets pointers and length to initial state
     * - Called automatically by destructor
     */
    void clear() {
        while (!isEmpty()) {
            Node<T>* temp = head;  // Store current head
            head = head->next;     // Advance head to next node
            delete temp;           // Free current node memory
        }
        head = last = NULL;  // Reset pointers to safe state
        length = 0;          // Reset element count
    }

    /**
     * ADD METHOD - NOW CONCRETE WITH DEFAULT FIFO BEHAVIOR
     * @param data: Element to add to the list
     * 
     * KEY CHANGE: No longer abstract - provides default implementation
     * BEHAVIOR: FIFO (First-In-First-Out) - adds to end of list
     * 
     * USE CASES:
     * - Default list operations
     * - Queue-like behavior (inherited by Queue class)
     * - Direct instantiation in containers like Array
     * 
     * TIME COMPLEXITY: O(1) - constant time operation
     */
    virtual void add(T data) {
        if (isEmpty()) {
            // First element in list - initialize both head and last
            head = new Node<T>(data);
            last = head;
        } else {
            // Append to end of list - maintain FIFO order
            Node<T>* temp = new Node<T>(data);
            last->next = temp;  // Current last points to new node
            last = temp;        // New node becomes the last
        }
        length++;  // Increment element count
    }

    /**
     * CHECK IF LIST IS EMPTY
     * @return true if list contains no elements, false otherwise
     * 
     * EFFICIENCY: O(1) - constant time check
     */
    bool isEmpty() {
        return head == NULL;
    }

    /**
     * GET CURRENT NUMBER OF ELEMENTS
     * @return Current length of the list
     * 
     * EFFICIENCY: O(1) - maintains length counter
     */
    int len() {
        return length;
    }

    /**
     * PEEK AT FIRST ELEMENT WITHOUT REMOVAL
     * @return Data from the first node in the list
     * 
     * USAGE:
     * - Inspect next element to be processed
     * - Useful for queue and stack operations
     * 
     * EXCEPTION: Throws runtime_error if list is empty
     */
    T peek() {
        if (!isEmpty()) {
            return head->data;
        }
        throw std::runtime_error("List is empty - cannot peek");
    }

    /**
     * CHECK IF ANY ELEMENT SATISFIES CONDITION
     * @param condition: Lambda function that takes T and returns bool
     * @return true if any element satisfies the condition, false otherwise
     * 
     * USE CASE:
     * - Search for specific patient by ID
     * - Check for existence of elements with certain properties
     * - Flexible condition-based searching
     * 
     * TIME COMPLEXITY: O(n) - linear search through list
     */
    bool contains(std::function<bool(T)> condition) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (condition(current->data)) {
                return true;  // Early termination when found
            }
            current = current->next;
        }
        return false;  // Condition not satisfied by any element
    }

    /**
     * REMOVE AND RETURN FIRST ELEMENT
     * @return Data from the removed first element
     * 
     * BEHAVIOR: FIFO - removes from front (head)
     * MEMORY MANAGEMENT: Deletes the node after retrieving data
     * 
     * EXCEPTION: Throws runtime_error if list is empty
     */
    T pop() {
        if (!isEmpty()) {
            Node<T>* temp = head;      // Store current head
            T data = head->data;       // Retrieve data before deletion
            head = head->next;         // Advance head to next node
            
            delete temp;               // Free the old head node
            
            // Update last pointer if list becomes empty
            if (isEmpty()) {
                last = NULL;
            }
            
            length--;                  // Decrement element count
            return data;               // Return retrieved data
        }
        throw std::runtime_error("List is empty - cannot pop");
    }

    /**
     * REVERSE THE LINKED LIST IN-PLACE
     * 
     * ALGORITHM: Three-pointer technique
     * - previous: Tracks the already reversed portion
     * - current: Current node being processed  
     * - nextNode: Temporary storage for next node
     * 
     * TIME COMPLEXITY: O(n) - single pass through list
     * MEMORY COMPLEXITY: O(1) - in-place reversal
     */
    void reverse() {
        if (!isEmpty() && head != last) {  // Only reverse if 2+ elements
            Node<T>* current = head;
            Node<T>* nextNode = NULL;
            Node<T>* previous = NULL;
            
            // Traverse list reversing pointer directions
            while (current != NULL) {
                nextNode = current->next;  // Store next node
                current->next = previous;  // Reverse pointer direction
                previous = current;        // Move previous forward
                current = nextNode;        // Move current forward
            }
            
            // Swap head and last pointers after reversal
            Node<T>* temp = head;
            head = last;    // Old last becomes new head
            last = temp;    // Old head becomes new last
        }
    }

    /**
     * MERGE SORT IMPLEMENTATION (RECURSIVE)
     * @param h: Head of the sublist to sort
     * @return Head of the sorted sublist
     * 
     * ALGORITHM STEPS:
     * 1. Split: Divide list into two halves using alternating nodes
     * 2. Conquer: Recursively sort each half
     * 3. Combine: Merge the two sorted halves
     * 
     * TIME COMPLEXITY: O(n log n) - optimal for linked lists
     * SPACE COMPLEXITY: O(log n) - recursion stack
     */
    Node<T>* mergeSort(Node<T>* h) {
        // Base case: list with 0 or 1 element is already sorted
        if (h == NULL || h->next == NULL) {
            return h;
        }
        
        // Split list into two halves using alternating nodes
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
            flag = !flag;  // Toggle between left and right
        }
        
        // Terminate both sublists
        lastLeft->next = NULL;
        lastRight->next = NULL;
        
        // Recursively sort both halves
        left = mergeSort(left);
        right = mergeSort(right);
        
        // Merge the two sorted halves
        Node<T>* mergedHead = NULL;
        if (left->data < right->data) {
            mergedHead = left;
            left = left->next;
        } else {
            mergedHead = right;
            right = right->next;
        }
        
        Node<T>* currentTail = mergedHead;
        
        // Merge process: compare and append smaller elements
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
        
        // Append remaining elements from whichever list is non-empty
        if (left != NULL) {
            currentTail->next = left;
        } else {
            currentTail->next = right;
        }
        
        return mergedHead;
    }

    /**
     * SORT THE ENTIRE LINKED LIST
     * 
     * WRAPPER FUNCTION:
     * - Calls recursive mergeSort on the entire list
     * - Updates last pointer after sorting
     * - Maintains list integrity throughout process
     */
    void sort() {
        if (head != NULL) {
            head = mergeSort(head);
            
            // Update last pointer to point to new tail
            last = head;
            while (last->next != NULL) { 
                last = last->next; 
            }
        }
    }

    /**
     * PRINT LIST TO OUTPUT STREAM
     * @param os: Output stream reference (e.g., std::cout, file stream)
     * 
     * FORMAT: "length data1 data2 ... dataN"
     * - First prints length, then space-separated elements
     * - Compatible with read() method for serialization
     */
    void print(std::ostream& os) {
        os << length;  // Output element count first
        Node<T>* current = head;
        
        // Output each element separated by spaces
        while (current != NULL) {
            os << ' ' << current->data;
            current = current->next;
        }
    }

    /**
     * READ LIST FROM INPUT STREAM
     * @param is: Input stream reference (e.g., std::cin, file stream)
     * 
     * FORMAT: "length data1 data2 ... dataN"
     * - Expects length first, then specified number of elements
     * - Clears existing list before reading new data
     * - Reconstructs complete list from serialized data
     */
    void read(std::istream& is) {
        clear();  // Remove existing elements
        
        T data;
        int n;
        is >> n;  // Read number of elements to read
        
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
 * @param l: List to output
 * @return Output stream reference for chaining
 * 
 * ENABLES NATURAL SYNTAX:
 * - std::cout << myList;
 * - file << myList;
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
 * @return Input stream reference for chaining
 * 
 * ENABLES NATURAL SYNTAX:
 * - std::cin >> myList;
 * - file >> myList;
 */
template <typename T>
std::istream& operator>>(std::istream& is, List<T>& l) {
    l.read(is);
    return is;
}

#endif
