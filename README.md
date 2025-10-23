# 🏥 Sistema de Gestión Hospitalaria

Un sistema integral de gestión hospitalaria creado en C++ que demuestra la aplicación práctica de estructuras de datos en un escenario del mundo real.

## 🏗 Estructuras de datos usadas
   - **Arreglo dinamico:** Base de datos de pacientes
   - **Cola por Prioridad:** Triage de pacientes
   - **Cola Circular:** Gestión de la atención en los consultorios
   - **Pila:** Historial y seguimiento de diagnosticos
     
## Estructura repositorio
```text
HospitalManagementSystem/
├── src/
│   ├── main.cpp
│   ├── hospitalsystem.h
│   ├── hospitalsystem.cpp
│   ├── patient.h
│   ├── priorityqueue.h
│   ├── circularqueue.h
│   ├── array.h
│   ├── list.h
│   └── stack.h
├── docs/
│   └── EXPLICACION_ESTRUCTURAS.md
├── compile.bat
├── Makefile
└── README.md
```

## 🚀 Installation (Windows)
### Paso 1: Descargar el codigo
**Opcion A: Clonar repositorio (Recomendado)**

```bash
# Clone using Git
git clone https://github.com/your-username/HospitalManagementSystem.git

# Navigate to project directory
cd HospitalManagementSystem
```
**Opcion B: Descargar el archivo ZIP**

Go to the GitHub repository page
Click the green "Code" button
Select "Download ZIP"

Extract the ZIP file to your desired location
### Paso 2: Instalar compilador de C++
1. Descargar **MinGW-w64** from (https://www.mingw-w64.org/)
2. Ejecute el instalador y seleccione:
   - Architecture: `x86_64`
   - Threads: `posix`
   - Exception: `seh`
3. Instalar en: `C:\MinGW`

### Paso 3: Establecer las variables de entorno del sístema
1. Presione `Windows + R`, ingrese `sysdm.cpl`, presione Enter
2. Clickee "Environment Variables"
3. Bajo "System Variables", encuentre `Path`, clickee "Edit"
4. Clickee "New" y agregue: `C:\MinGW\bin`
5. Clickee "OK" para finalizar

### Paso 4: Verificar Instalación
Abra la consola de comandos e ingrese:
```cmd
g++ --version
```

### Paso 5: Compilación y ejecución
**Metodo 1: Use el script batch**
compile.bat

**Metodo 2: Compilación manual**
Ingrese:
```cmd
g++ -std=c++11 -Wall -g src/main.cpp src/hospitalsystem.cpp -o hospital_system.exe
hospital_system.exe
```
## 🎮 User Manual
## Opciones del menú principal
### 1. Register New Patient
  - Enter patient details: name, age, priority (I-V), symptoms
  - Patient is automatically added to triage system
### 2. Attend Next Patient
  - Moves highest priority patient from triage to available consultation room
  - Shows patient details and room assignment
### 3. Free Consultation Room
  - Releases the oldest occupied consultation room
  - Patient is moved to history
### 4. Display System State
  - Shows complete status of all data structures
  - Triage queue, room occupancy, recent history
### 5. View Patient Database
  - Lists all registered patients in the system
### 6. Search Patient by ID
  - Find specific patient using their unique ID
### 7. Exit System
  - Safely shuts down and cleans up memory
## Priority System
  - Priority 1 (High): Emergency cases - treated first
  - Priority 2 (Medium): Urgent cases - treated after emergencies
  - Priority 3 (Low): Routine cases - treated last
## Ejemplo de uso
```text
==================================================
          HOSPITAL MANAGEMENT SYSTEM
==================================================
1. Register New Patient
2. Attend Next Patient (Triage → Consultation)
3. Free Consultation Room (Consultation → History)
4. Display Complete System State
5. View Patient Database
6. Search Patient by ID
7. Exit System
==================================================

Select an option: 1

Enter patient name: John Smith
Enter patient age: 45
Enter priority (1=TRIAGE I, 2=TRIAGE II, 3=TRIAGE III, 4=TRIAGE IV, 5=TRIAGE V): 1
Enter symptoms: Chest pain

✅ PATIENT REGISTERED SUCCESSFULLY
Patient ID: 1 | John Smith | Age: 45 | Priority: 1 | Symptom: Chest pain
```

