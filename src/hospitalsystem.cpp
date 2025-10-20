#include "sistemahospital.h"
#include <iostream>

using namespace std;

// Constructor
SistemaHospital::SistemaHospital(int numConsultorios) 
    : siguienteID(1), numConsultorios(numConsultorios) {
    
    pacientesRegistrados = new Array<Paciente*>(100);
    triage = new PriorityQueue<Paciente*>();
    consultorios = new CircularQueue<Paciente*>(numConsultorios);
    historial = new Stack<Paciente*>();
    
    cout << "Sistema hospitalario inicializado con " << numConsultorios 
              << " consultorios" << endl;
}

// Destructor
SistemaHospital::~SistemaHospital() {
    // Liberar memoria de todos los pacientes
    for (int i = 0; i < pacientesRegistrados->len(); i++) {
        delete (*pacientesRegistrados)[i];
    }
    
    // Liberar las estructuras principales
    delete pacientesRegistrados;
    delete triage;
    delete consultorios;
    delete historial;
    
    cout << "Memoria del sistema hospitalario liberada" << endl;
}

void SistemaHospital::registrarPaciente(string nombre, int edad, int prioridad, string sintoma) {
    Paciente* nuevoPaciente = new Paciente(siguienteID++, nombre, edad, prioridad, sintoma);
    
    try {
        pacientesRegistrados->append(nuevoPaciente);
        triage->add(nuevoPaciente);
        
        cout << "Paciente registrado exitosamente: " << *nuevoPaciente << endl;
    }
    catch (...) {
        delete nuevoPaciente;
        throw;
    }
}

void SistemaHospital::atenderSiguientePaciente() {
    if (triage->isEmpty()) {
        cout << "No hay pacientes en espera" << endl;
        return;
    }

    if (consultorios->isFull()) {
        cout << "Todos los consultorios estan ocupados" << endl;
        return;
    }

    try {
        Paciente* paciente = triage->pop();
        consultorios->enqueue(paciente);
        
        cout << "Paciente asignado a consultorio: " << *paciente << endl;
    }
    catch (const exception& e) {
        cout << "Error al atender paciente: " << e.what() << endl;
    }
}

void SistemaHospital::liberarConsultorio() {
    if (consultorios->isEmpty()) {
        cout << "No hay consultorios ocupados" << endl;
        return;
    }

    try {
        Paciente* paciente = consultorios->dequeue();
        historial->add(paciente);
        
        cout << "Consultorio liberado. Paciente completado: " << *paciente << endl;
    }
    catch (const exception& e) {
        cout << "Error al liberar consultorio: " << e.what() << endl;
    }
}

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


void SistemaHospital::menuPrincipal() {
    int opcion;
    
    do {
        cout << "\n=== SISTEMA HOSPITALARIO ===" << endl;
        cout << "1. Registrar nuevo paciente" << endl;
        cout << "2. Atender siguiente paciente (Triage -> Consultorio)" << endl;
        cout << "3. Liberar consultorio (Consultorio -> Historial)" << endl;
        cout << "4. Mostrar estado del sistema" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string nombre, sintoma;
                int edad, prioridad;
                
                cout << "Nombre del paciente: ";
                getline(cin, nombre);
                
                cout << "Edad: ";
                cin >> edad;
                
                cout << "Prioridad (1-Alta, 2-Media, 3-Baja): ";
                cin >> prioridad;
                
                cin.ignore();
                cout << "Sintoma: ";
                getline(cin, sintoma);
                
                try {
                    registrarPaciente(nombre, edad, prioridad, sintoma);
                } catch (const exception& e) {
                    cout << "Error al registrar paciente: " << e.what() << endl;
                }
                break;
            }
            
            case 2:
                atenderSiguientePaciente();
                break;
                
            case 3:
                liberarConsultorio();
                break;
                
            case 4:
                mostrarEstadoSistema();
                break;
                
            case 5:
                cout << "Saliendo del sistema..." << endl;
                break;
                
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
        
    } while (opcion != 5);
}

/*
 * MÉTODO ESTÁTICO - Punto de entrada de la aplicación
 * No requiere instancia de la clase para ser llamado
 */
void SistemaHospital::ejecutarAplicacion() {
    cout << "🎯 INICIALIZANDO SISTEMA HOSPITALARIO" << endl;
    
    try {
        // Crear instancia del sistema
        SistemaHospital hospital(3);
        
        // Ejecutar menú principal
        hospital.menuPrincipal();
    }
    catch (const exception& e) {
        cout << "❌ Error critico en el sistema: " << e.what() << endl;
    }
    
    cout << "👋 Sistema hospitalario finalizado" << endl;
}
