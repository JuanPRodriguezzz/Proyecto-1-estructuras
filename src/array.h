#ifndef ARRAY_H
#define ARRAY_H

/**
 * DYNAMIC ARRAY TEMPLATE CLASS
 * 
 * FEATURES:
 * - Dynamic memory allocation with growth/shrink strategies
 * - Automatic resizing when capacity is exceeded
 * - Sorting using merge sort algorithm
 * - Bounds checking with exception handling
 * 
 * MEMORY MANAGEMENT:
 * - Uses pointer 'buffer' to manage dynamic memory
 * - Implements RAII (Resource Acquisition Is Initialization)
 * - Automatic memory cleanup in destructor
 */

template <typename T>
class Array {
protected:
    T* buffer;    // Pointer to dynamically allocated array
    int size;     // Current capacity of the array
    int length;   // Current number of elements in array

public:
    /**
     * CONSTRUCTOR
     * @param m: Maximum initial capacity
     * @param l: Initial length (default 0)
     * 
     * POINTER NOTE:
     * - 'new T[size]' allocates memory on the heap
     * - 'buffer' points to the first element of the array
     */
    Array(int m, int l = 0) {
        length = l;
        size = m;
        buffer = new T[size]; // Dynamic memory allocation
    }

    /**
     * DESTRUCTOR
     * 
     * MEMORY MANAGEMENT:
     * - 'delete[] buffer' deallocates the entire array
     * - Prevents memory leaks by freeing allocated memory
     */
    ~Array() {
        delete[] buffer; // Free dynamically allocated array
    }

    /**
     * SORT METHOD - Implements Merge Sort Algorithm
     * 
     * ALGORITHM BREAKDOWN:
     * 1. Divide array into two halves
     * 2. Recursively sort each half
     * 3. Merge the sorted halves back together
     * 
     * TIME COMPLEXITY: O(n log n)
     */
    void sort() {
        // Base case: array with 2 elements
        if (length == 2) {
            if (buffer[0] > buffer[1]) {
                // Swap elements if they're in wrong order
                T temp = buffer[0];
                buffer[0] = buffer[1];
                buffer[1] = temp;
            }
        }
        // Recursive case: array with more than 2 elements
        else if (length > 2) {
            int middle = length / 2;
            
            // Create left and right subarrays
            Array<T> leftArray(middle, middle);
            Array<T> rightArray(length - middle, length - middle);
            
            // Copy data to left subarray
            for (int i = 0; i < leftArray.length; i++) {
                leftArray[i] = buffer[i];
            }
            
            // Copy data to right subarray
            for (int i = 0; i < rightArray.length; i++) {
                rightArray[i] = buffer[i + middle];
            }
            
            // Recursively sort both halves
            leftArray.sort();
            rightArray.sort();
            
            // Merge the sorted halves
            int leftIndex = 0;
            int rightIndex = 0;
            int mainIndex = 0;
            
            while (leftIndex < leftArray.length && rightIndex < rightArray.length) {
                if (leftArray.buffer[leftIndex] < rightArray.buffer[rightIndex]) {
                    buffer[mainIndex] = leftArray.buffer[leftIndex];
                    leftIndex++;
                } else {
                    buffer[mainIndex] = rightArray.buffer[rightIndex];
                    rightIndex++;
                }
                mainIndex++;
            }
            
            // Copy remaining elements from left array
            if (leftIndex == leftArray.length) {
                while (rightIndex < rightArray.length) {
                    buffer[mainIndex] = rightArray.buffer[rightIndex];
                    rightIndex++;
                    mainIndex++;
                }
            }
            // Copy remaining elements from right array
            else {
                while (leftIndex < leftArray.length) {
                    buffer[mainIndex] = leftArray.buffer[leftIndex];
                    leftIndex++;
                    mainIndex++;
                }
            }
        }
    }

    /**
     * SUBSCRIPT OPERATOR OVERLOADING
     * @param index: Position to access
     * @return Reference to element at position 'index'
     * 
     * EXCEPTION HANDLING:
     * - Throws exception if index is out of bounds
     * - Provides bounds checking for safe array access
     */
    T& operator[](int index) {
        if (0 <= index && index < length) {
            return buffer[index];
        } else {
            throw -1; // Index out of bounds exception
        }
    }

    /**
     * INSERT ELEMENT AT SPECIFIC POSITION
     * @param index: Position to insert at
     * @param data: Element to insert
     * @return true if successful, false otherwise
     * 
     * MEMORY MANAGEMENT:
     * - Calls grow() to ensure sufficient capacity
     * - Shifts elements to make space for new element
     */
    bool insert(int index, T data) {
        if (0 <= index && index <= length) {
            grow(); // Ensure array has enough capacity
            
            // Shift elements to the right to make space
            for (int i = length; i > index; i--) {
                buffer[i] = buffer[i - 1];
            }
            
            // Insert new element
            buffer[index] = data;
            length++;
            return true;
        }
        return false;
    }

    /**
     * APPEND ELEMENT TO END OF ARRAY
     * @param data: Element to append
     */
    void append(T data) {
        insert(length, data);
    }

    /**
     * REMOVE ELEMENT AT SPECIFIC POSITION
     * @param index: Position to remove from
     * @return true if successful, false otherwise
     */
    bool remove(int index) {
        if (0 <= index && index < length) {
            length--;
            
            // Shift elements to the left to fill gap
            for (int i = index; i < length; i++) {
                buffer[i] = buffer[i + 1];
            }
            
            shrink(); // Potentially reduce capacity to save memory
            return true;
        }
        return false;
    }

    /**
     * DELETE LAST ELEMENT
     * @return true if successful, false otherwise
     */
    bool del() {
        return remove(length - 1);
    }

    /**
     * GET CURRENT NUMBER OF ELEMENTS
     * @return Current length of array
     */
    int len() {
        return length;
    }

protected:
    /**
     * GROW ARRAY CAPACITY WHEN FULL
     * 
     * MEMORY STRATEGY:
     * - Uses golden ratio (1.618) for growth factor
     * - Allocates new larger array
     * - Copies existing elements to new array
     * - Deletes old array to prevent memory leaks
     */
    void grow() {
        if (length == size) {
            int newSize = (int)(size * 1.618); // Golden ratio growth
            T* newBuffer = new T[newSize];     // Allocate new larger array
            
            // Copy existing elements to new array
            for (int i = 0; i < size; i++) {
                newBuffer[i] = buffer[i];
            }
            
            delete[] buffer; // Free old array memory
            buffer = newBuffer; // Point to new array
            size = newSize; // Update capacity
        }
    }

    /**
     * SHRINK ARRAY CAPACITY WHEN UNDERUTILIZED
     * 
     * MEMORY STRATEGY:
     * - Shrinks when size is large and utilization is low
     * - Uses golden ratio for shrink factor
     * - Prevents excessive memory usage
     */
    void shrink() {
        if (size > 20 && length <= (int)(size / (1.618 * 1.618))) {
            int newSize = size / 1.618; // Golden ratio shrink
            T* newBuffer = new T[newSize]; // Allocate new smaller array
            
            // Copy existing elements to new array
            for (int i = 0; i < newSize; i++) {
                newBuffer[i] = buffer[i];
            }
            
            delete[] buffer; // Free old array memory
            buffer = newBuffer; // Point to new array
            size = newSize; // Update capacity
        }
    }
};

#endif
