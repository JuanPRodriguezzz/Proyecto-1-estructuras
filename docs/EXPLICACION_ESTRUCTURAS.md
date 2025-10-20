
# 📊 Explicación de Estructuras de Datos

## 🎯 Introducción

Este documento explica el porqué y cómo se utilizaron cada una de las estructuras de datos lineales en el Sistema de Gestión Hospitalaria.

## 🏗 Estructuras Implementadas

### 1. Array Dinámico (`Array`)

**Propósito**: Base de datos principal de pacientes

**Por qué Array**:
- ✅ **Acceso aleatorio**: Búsqueda eficiente por ID
- ✅ **Persistencia**: Pacientes permanecen después del procesamiento
- ✅ **Capacidad dinámica**: Crece automáticamente cuando es necesario

**Uso en el Sistema**:
- Almacenamiento permanente de todos los pacientes
- Búsqueda de pacientes por ID
- Generación de reportes completos

### 2. Cola de Prioridad (`PriorityQueue`)

**Propósito**: Sistema de triage para ordenar pacientes por urgencia

**Implementación**: Array de Listas
```cpp
Array<List<Patient*>>* priorityBuckets;
// [0] → Lista prioridad ALTA
// [1] → Lista prioridad MEDIA  
// [2] → Lista prioridad BAJA
```

**Por qué Array de Listas**:

- ✅ **Eficiencia**: O(1) para encontrar siguiente prioridad
- ✅ **FIFO por prioridad**: Justo dentro de cada nivel
- ✅ **Visualización clara**: Representación natural del triage

**Uso en el Sistema**:
- Recepción de pacientes en orden de llegada
- Clasificación automática por prioridad médica
- Extracción ordenada por urgencia

### 3. Cola Circular (`CircularQueue`)

**Propósito**: Gestión de consultorios médicos limitados

**Por qué Array para Cola Circular**:
- ✅ **Recursos fijos**: Consultorios son limitados físicamente
- ✅ **Eficiencia memoria**: Array contiguo vs nodos dispersos
- ✅ **Acceso directo**: O(1) a cualquier consultorio

**Uso en el Sistema**:
- Gestión de consultorios disponibles/ocupados
- Reutilización cíclica de recursos
- Control de capacidad máxima

### 4. Pila (`Stack`)

**Propósito**: Historial de pacientes atendidos recientemente

**Por qué Pila**:
- ✅ **Natural para historial**: Los más recientes son más relevantes
- ✅ **Eficiencia**: O(1) para operaciones básicas

**Uso en el Sistema**:
- Almacenamiento de consultas completadas
- Acceso rápido al paciente más reciente

