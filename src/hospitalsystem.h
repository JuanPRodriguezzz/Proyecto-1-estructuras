#ifndef SISTEMAHOSPITAL_H
#define SISTEMAHOSPITAL_H

#include "priorityqueue.h"
#include "circularqueue.h" 
#include "stack.h"
#include "array.h"
#include "paciente.h"
#include <iostream>
#include <string>

/*
 * SISTEMA HOSPITALARIO PRINCIPAL
 * 
 * AHORA CON MÉTODO ESTÁTICO PARA INICIAR LA APLICACIÓN
 * Todo queda encapsulado dentro de la clase
 */

class SistemaHospital {
private:
    // ESTRUCTURAS DE DATOS - APUNTADORES A PACIENTES
    Array<Paciente*>* pacientesRegistrados;
    PriorityQueue<Paciente*>* triage;  
    CircularQueue<Paciente*>* consultorios;
    Stack<Paciente*>* historial;

    int siguienteID;
    int numConsultorios;

    // MÉTODOS PRIVADOS - Implementación interna
    void registrarPaciente(std::string nombre, int edad, int prioridad, std::string sintoma);
    void atenderSiguientePaciente();
    void liberarConsultorio();
    void mostrarEstadoSistema();
    void menuPrincipal();

public:
    // Constructor
    SistemaHospital(int numConsultorios = 3);
    
    // Destructor
    ~SistemaHospital();
    
    /*
     * MÉTODO ESTÁTICO PARA INICIAR LA APLICACIÓN
     * No necesita instanciar la clase para comenzar
     */
    static void ejecutarAplicacion();
};

#endif
