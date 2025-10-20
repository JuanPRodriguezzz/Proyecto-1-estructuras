# 🏥 Sistema de Gestión Hospitalaria

Un sistema integral de gestión hospitalaria creado en C++ que demuestra la aplicación práctica de estructuras de datos en un escenario del mundo real.

## 🚀 Installation (Windows)

### Paso 1: Instalar compilador de C++
1. Descargar **MinGW-w64** from (https://www.mingw-w64.org/downloads/)
2. Ejecute el instalador y seleccione:
   - Architecture: `x86_64`
   - Threads: `posix`
   - Exception: `seh`
3. Install to: `C:\MinGW`

### Paso 2: Establecer las variables de entorno
1. Presione `Windows + R`, ingrese `sysdm.cpl`, presione Enter
2. Clickee "Environment Variables"
3. Bajo "System Variables", encuentre `Path`, clickee "Edit"
4. Clickee "New" y agregue: `C:\MinGW\bin`
5. Clickee "OK" para finalizar

### Paso 3: Verificar Instalación
Abra la consola de comandos e ingrese:
```cmd
g++ --version
```

### Paso 4: Compilación y ejecución
Ingrese:
```cmd
g++ -std=c++11 -Wall -g src/main.cpp src/hospitalsystem.cpp -o hospital_system.exe
hospital_system.exe
```
## 🎮 User Manual
## Opciones del menú principal
### 1. Register New Patient
  - Enter patient details: name, age, priority (1-3), symptoms
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
