
# 📊 Explicación de Estructuras de Datos

## 🎯 Introducción

Este documento explica el porqué y cómo se utilizaron cada una de las estructuras de datos lineales en el Sistema de Gestión Hospitalaria.

## 🏗 Estructuras Implementadas

### 1. Arreglo Dinámico (`Array`)

**Propósito**: Base de datos principal de pacientes

**Por qué**:
- ✅ **Acceso aleatorio**: Búsqueda eficiente por ID
- ✅ **Persistencia**: Pacientes permanecen después del procesamiento
- ✅ **Capacidad dinámica**: Crece automáticamente cuando es necesario (factor de crecimiento: razón áurea 1.618)
- ✅ **RAII**: Gestión automática de memoria

**Uso en el Sistema**:
```cpp
Array<Patient*>* registeredPatients;  // Capacidad inicial: 100 pacientes
- Almacenamiento permanente de todos los pacientes
- Búsqueda de pacientes por ID
- Generación de reportes completos
- Merge Sort incorporado para ordenamiento cuando sea necesario
```

### 2. Cola de Prioridad (`PriorityQueue`)

**Propósito**: Sistema de triage para ordenar la atención por prioridad

**Implementación**: Arreglo de listas donde la posición(indice) es la prioridad
```cpp
Array<List<Patient*>>* priorityBuckets;
// [0] → TRIAGE I (Emergencia) - Atención inmediata
// [1] → TRIAGE II (Urgencia) - Máximo 30 minutos
// [2] → TRIAGE III (Prioritario) - 2-4 horas
// [3] → TRIAGE IV (Rutinario) - 4-12 horas
// [4] → TRIAGE V (No urgente) - 12-24 horas
```

**Por qué Array de Listas**:

- ✅ **Eficiencia**: O(1) Acceso directo a cada nivel de prioridad
- ✅ **FIFO por prioridad**: Orden de llegada dentro de cada nivel
- ✅ **Visualización clara**: Representación natural del flujo triage

**Uso en el Sistema**:
- Recepción de pacientes en orden de llegada y según nivel de prioridad
- Clasificación automática por prioridad médica
- Extracción ordenada por urgencia, (siempre prioriza TRIAGE I primero)

### 3. Cola Circular (`CircularQueue`)

**Propósito**: Gestión de consultorios médicos limitados con comportamiento circular

**¿Por qué Lista Enlazada Circular?:**:
- ✅ **Comportamiento circular natural:** tail->next = head crea un anillo verdadero
- ✅ **Memoria dinamica**: Solo usa memoria para consultorios ocupados
- ✅ **Acceso directo**: 0(1) Inserción y eliminación en tiempo constante
- ✅ **Visualización clara**: Muestra la estructura circular real

**Uso en el Sistema**:
- Gestión de 8 consultorios médicos
- Asignación circular de pacientes a consultorios
- Liberación y reutilización cíclica de recursos
- Búsqueda eficiente de pacientes en consulta

### 4. Pila (`Stack`)

**Propósito**: Historial de pacientes atendidos recientemente

**Implementación**: Lista enlazada con comportamiento LIFO

**Por qué Pila**:
- ✅ **Natural para historial**: Los pacientes más recientes son más relevantes
- ✅ **Eficiencia**: O(1) para operaciones básicas, push y pop en tiempo constante
- ✅ **Sobreescribe add()**: Comportamiento específico para pila


**Uso en el Sistema**:
- Almacenamiento de consultas completadas
- Acceso rápido al paciente más reciente
- Seguimiento del flujo de trabajo reciente
- No requiere búsquedas complejas, solo acceso secuencial inverso

## 🔄 Flujo de Datos del Sistema

### Proceso Completo del Paciente:

1. Registro → Array (base de datos permanente)
2. Triaje → PriorityQueue (clasificación por urgencia)
3. Consulta → CircularQueue (asignación a consultorios)
4. Completado → Stack (historial reciente)

### Ventajas del Diseño:
- ✅ Separación de responsabilidades: Cada estructura tiene un propósito específico
- ✅ Eficiencia: Operaciones O(1) en caminos críticos
- ✅ Escalabilidad: Capacidad para 200 pacientes (inicial) y 8 consultorios
- ✅ Mantenibilidad: Código bien documentado y estructurado

