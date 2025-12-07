///
/// Query.cxx - Implementación de los ejercicios del examen
///

#include "Query.h"
#include "Carrera.h"
#include "Estudiante.h"
#include "Calificacion.h"
#include "Asignatura.h"
#include "Departamento.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using std::string;
using std::vector;

// ==========================================
// FUNCIONES AUXILIARES
// ==========================================

// Busca el código de una carrera dado una parte de su descripción
Codigo buscar_carrera(const string& substring) {
    const auto& tabla = Carrera::tabla();
    for (const auto& c : tabla) {
        // Se usa const_cast porque los getters de la clase base no son const
        string desc = const_cast<Carrera&>(c).descripcion(); 
        if (desc.find(substring) != string::npos) {
            return const_cast<Carrera&>(c).clave();
        }
    }
    return Codigo(""); 
}

// Busca el código de un departamento
Codigo buscar_departamento(const string& substring) {
    const auto& tabla = Departamento::tabla();
    for (const auto& d : tabla) {
        string desc = const_cast<Departamento&>(d).descripcion();
        if (desc.find(substring) != string::npos) {
            return const_cast<Departamento&>(d).clave();
        }
    }
    return Codigo("");
}

// Busca el código de una asignatura
Codigo buscar_asignatura(const string& substring) {
    const auto& tabla = Asignatura::tabla();
    for (const auto& a : tabla) {
        string desc = const_cast<Asignatura&>(a).descripcion();
        if (desc.find(substring) != string::npos) {
            return const_cast<Asignatura&>(a).codigo();
        }
    }
    return Codigo("");
}

// Obtiene las UC de una asignatura dado su código
int obtener_uc(Codigo codigo_asignatura) {
    const auto& tabla = Asignatura::tabla();
    for (const auto& a : tabla) {
        if (const_cast<Asignatura&>(a).codigo().str() == codigo_asignatura.str()) {
            return const_cast<Asignatura&>(a).uc();
        }
    }
    return 0;
}

// ==========================================
// IMPLEMENTACIÓN DE QUERIES
// ==========================================

// Query 0: Para el anio 2044, promedio de Ingenieria Electronica.
int Query::q0() {
    fprintf(stdout, "--- Ejecutando Query 0 ---\n");
    
    // 1. Buscar código de la carrera
    Codigo cod_elec = buscar_carrera("Electronica");
    if (cod_elec.str().empty()) {
        fprintf(stderr, "Error: No se encontro la carrera Ingenieria Electronica\n");
        return EXIT_FAILURE;
    }

    // 2. Filtrar carnets de estudiantes de esa carrera
    std::set<string> carnets_electronica;
    const auto& estudiantes = Estudiante::tabla();
    for (const auto& e : estudiantes) {
        if (const_cast<Estudiante&>(e).carrera().str() == cod_elec.str()) {
            carnets_electronica.insert(const_cast<Estudiante&>(e).carnet().str());
        }
    }

    // 3. Calcular promedio de notas en 2044
    double suma_notas = 0;
    int conteo = 0;
    const auto& calificaciones = Calificacion::tabla();

    for (const auto& cal : calificaciones) {
        // Verificar año y si el estudiante pertenece a la carrera
        if (cal.year() == 2044) {
            if (carnets_electronica.count(cal.carnet().str())) {
                suma_notas += cal.nota();
                conteo++;
            }
        }
    }

    if (conteo == 0) {
        fprintf(stdout, "Promedio: 0.0 (Sin datos en 2044)\n");
    } else {
        float promedio = (float)(suma_notas / conteo);
        fprintf(stdout, "Promedio Ing. Electronica (2044): %.2f\n", promedio);
    }

    return EXIT_SUCCESS;
}

// Query 1: Cantidad de graduados de Computacion y Electronica en el anio 2050.
int Query::q1() {
    fprintf(stdout, "--- Ejecutando Query 1 ---\n");

    Codigo cod_comp = buscar_carrera("Computacion");
    Codigo cod_elec = buscar_carrera("Electronica");

    int cantidad = 0;
    const auto& estudiantes = Estudiante::tabla();

    for (const auto& e : estudiantes) {
        Estudiante& est = const_cast<Estudiante&>(e); 
        
        bool es_target = (est.carrera().str() == cod_comp.str()) || 
                         (est.carrera().str() == cod_elec.str());
        
        // Condición: Año 2050, Graduado y Carrera correcta
        if (est.year() == 2050 && est.graduado() && es_target) {
            cantidad++;
        }
    }

    fprintf(stdout, "Total graduados Comp/Elec en 2050: %d\n", cantidad);
    return EXIT_SUCCESS;
}

// Query 2: Las asignaturas del departamento de Computacion.
int Query::q2() {
    fprintf(stdout, "--- Ejecutando Query 2 ---\n");

    Codigo cod_dpto = buscar_departamento("Computacion");
    
    if (cod_dpto.str().empty()) {
         fprintf(stderr, "Error: No se encontro el Dpto de Computacion\n");
         // Intento fallback
         cod_dpto = buscar_departamento("Tecnologia"); 
         if (cod_dpto.str().empty()) return EXIT_FAILURE;
    }

    const auto& asignaturas = Asignatura::tabla();
    
    fprintf(stdout, "Asignaturas Dpto. Computacion:\n");
    for (const auto& a : asignaturas) {
        Asignatura& asig = const_cast<Asignatura&>(a);
        
        if (asig.departamento().str() == cod_dpto.str()) {
            fprintf(stdout, " [%s] %s (UC: %d)\n", 
                asig.codigo().str().c_str(),
                asig.descripcion().c_str(),
                asig.uc());
        }
    }

    return EXIT_SUCCESS;
}

// Query 3: Activos que cursaron Matematicas VII y pasaron Fisica I (nota >= 4).
int Query::q3() {
    fprintf(stdout, "--- Ejecutando Query 3 ---\n");

    Codigo cod_mate7 = buscar_asignatura("Matematicas VII");
    Codigo cod_fisica1 = buscar_asignatura("Fisica I"); 

    if (cod_mate7.str().empty()) fprintf(stderr, "Warning: Mate VII no encontrada\n");
    if (cod_fisica1.str().empty()) fprintf(stderr, "Warning: Fisica I no encontrada\n");

    std::set<string> cursaron_mate7;
    std::set<string> pasaron_fisica1;

    const auto& calificaciones = Calificacion::tabla();
    for (const auto& cal : calificaciones) {
        string carnet = cal.carnet().str();
        string asig = cal.asignatura().str();

        if (asig == cod_mate7.str()) {
            cursaron_mate7.insert(carnet);
        }
        if (asig == cod_fisica1.str() && cal.nota() >= 4) {
            pasaron_fisica1.insert(carnet);
        }
    }

    fprintf(stdout, "Estudiantes activos (Mate VII y Fisica I >= 4):\n");
    
    const auto& estudiantes = Estudiante::tabla();
    for (const auto& e : estudiantes) {
        Estudiante& est = const_cast<Estudiante&>(e);
        string c = est.carnet().str();
        
        if (est.activo()) {
            // Intersección de conjuntos
            if (cursaron_mate7.count(c) && pasaron_fisica1.count(c)) {
                fprintf(stdout, " - %s (%s)\n", est.nombre().c_str(), c.c_str());
            }
        }
    }

    return EXIT_SUCCESS;
}

// Query 4: UC aprobadas por activos de Electronica hasta 2046 que tomaron Mate IV.
int Query::q4() {
    fprintf(stdout, "--- Ejecutando Query 4 ---\n");

    Codigo cod_elec = buscar_carrera("Electronica");
    Codigo cod_mate4 = buscar_asignatura("Matematicas IV");

    // 1. Identificar estudiantes objetivo (Activos de Electronica)
    const auto& estudiantes = Estudiante::tabla();
    vector<string> targets;
    
    for (const auto& e : estudiantes) {
        Estudiante& est = const_cast<Estudiante&>(e);
        if (est.activo() && est.carrera().str() == cod_elec.str()) {
            targets.push_back(est.carnet().str());
        }
    }

    fprintf(stdout, "Unidades Credito (UC) aprobadas hasta 2046:\n");

    // 2. Para cada estudiante, verificar historial
    const auto& calificaciones = Calificacion::tabla();

    for (const string& carnet : targets) {
        bool tomo_mate4 = false;
        int total_uc = 0;

        // Recorrido de calificaciones para este estudiante
        for (const auto& cal : calificaciones) {
            if (cal.carnet().str() == carnet) {
                // Chequeo Mate IV
                if (cal.asignatura().str() == cod_mate4.str()) {
                    tomo_mate4 = true;
                }
                
                // Suma de UC si el año es <= 2046. Asumimos nota >= 3 es aprobado.
                if (cal.year() <= 2046) {
                    total_uc += obtener_uc(cal.asignatura());
                }
            }
        }

        if (tomo_mate4) {
             fprintf(stdout, " Carnet: %s | Total UC: %d\n", carnet.c_str(), total_uc);
        }
    }

    return EXIT_SUCCESS;
}