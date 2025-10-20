void HospitalSystem::displaySystemState() {
    cout << "\n==================================================" << endl;
    cout << "         HOSPITAL SYSTEM COMPLETE STATUS" << endl;
    cout << "==================================================" << endl;
    
    // Display triage system state
    triage->displayState();
    
    // Display consultation rooms state
    consultationRooms->displayState();
    
    // Display history information - CORREGIDO: usar peek() solo si no está vacío
    cout << "\n=== RECENT PATIENT HISTORY (STACK) ===" << endl;
    if (history->isEmpty()) {
        cout << "No patients in history - no consultations completed yet" << endl;
    } else {
        // USO SEGURO DE PEEK(): solo llamamos peek() cuando sabemos que no está vacío
        cout << "Most recent patient: " << *(history->peek()) << endl;
        cout << "Total patients in history: " << history->len() << endl;
        
        // Show history depth information
        if (history->len() > 1) {
            cout << "History tracks last " << history->len() << " completed consultations" << endl;
        }
    }
    
    // System summary
    cout << "\n=== SYSTEM SUMMARY ===" << endl;
    cout << "Total registered patients: " << registeredPatients->len() << endl;
    cout << "Patients waiting in triage: " << triage->len() << endl;
    cout << "Patients in consultation: " << consultationRooms->size() << endl;
    cout << "Patients in history: " << history->len() << endl;
    cout << "Next available patient ID: " << nextPatientID << endl;
}
