#include "hospitalsystem.h"

/**
 * MAIN FUNCTION - APPLICATION ENTRY POINT
 * 
 * DESIGN PRINCIPLES:
 * - Simplicity: Delegates all functionality to HospitalSystem class
 * - Maintainability: Easy to understand and modify
 * - Exception Safety: All exceptions handled by HospitalSystem
 * 
 * RETURN CODES:
 * - 0: Normal successful execution
 * - 1: Unexpected error occurred (handled by exception mechanism)
 * 
 * MEMORY MANAGEMENT:
 * - All memory management handled by HospitalSystem class
 * - RAII ensures proper cleanup on normal and exceptional paths
 */
int main() {
    // Delegate all application functionality to HospitalSystem class
    // This follows the facade pattern and keeps main() simple
    HospitalSystem::runApplication();
    
    // Return success code - program executed successfully
    return 0;
}
