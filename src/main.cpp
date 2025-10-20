#include "hospitalsystem.h"

/**
 * MAIN FUNCTION - APPLICATION ENTRY POINT
 * 
 * SIMPLICITY PRINCIPLE:
 * - Only calls static method to run application
 * - All complexity hidden in HospitalSystem class
 * - Easy to understand and maintain
 * 
 * RETURN CODES:
 * - 0: Normal successful execution
 * - 1: Unexpected error occurred
 */
int main() {
    // Delegate all functionality to HospitalSystem class
    HospitalSystem::runApplication();
    
    // Return success code
    return 0;
}
