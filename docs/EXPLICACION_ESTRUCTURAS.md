
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
