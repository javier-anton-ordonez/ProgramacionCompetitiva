# Explicación Completa del Programa - Torres y Reinas

## Índice
1. [Problema](#problema)
2. [Estructuras de Datos](#estructuras-de-datos)
3. [Variables Globales](#variables-globales)
4. [Main - Inicialización](#main---inicialización)
5. [Algoritmo de Backtracking](#algoritmo-de-backtracking)
6. [Sistema de Diagonales](#sistema-de-diagonales)
7. [Podas (Optimizaciones)](#podas-optimizaciones)
8. [Ejemplo Paso a Paso](#ejemplo-paso-a-paso)

---

## Problema

Dado un tablero NxN con valores en cada casilla:
- Colocar **Q reinas** y **R torres**
- Ninguna pieza puede atacarse (ni por fila, columna o diagonal)
- **Reinas** atacan en las 8 direcciones (↑↓←→↖↗↙↘)
- **Torres** atacan en 4 direcciones (↑↓←→)
- Maximizar la suma de valores de las casillas ocupadas

**Restricción importante**: Si no es posible colocar TODAS las piezas, el resultado es 0.

---

## Estructuras de Datos

### Clase `Posicion`
```java
class Posicion {
  public int Valor;  // Valor de la casilla
  public int I;      // Fila
  public int J;      // Columna
}
```
Representa una casilla del tablero con su posición y valor.

### Clase `infoTablero`
```java
class infoTablero {
  boolean[] Columnas; // Columnas[j] = true si la columna j está ocupada
  boolean[] Filas;    // Filas[i] = true si la fila i está ocupada
}
```
Rastrea qué filas y columnas están ocupadas en O(1).

---

## Variables Globales

```java
static int mejorGlobal;           // Mejor suma encontrada hasta ahora
static int[] diag1, diag2;        // Diagonales ocupadas por REINAS
static int[] diagTorre1, diagTorre2; // Diagonales ocupadas por CUALQUIER pieza
```

### ¿Por qué dos pares de arrays de diagonales?

**diag1, diag2** (solo reinas):
- Se incrementan cuando colocas una **reina**
- Se usan para verificar si puedes colocar otra **reina**
- Las torres NO importan aquí (no atacan en diagonal)

**diagTorre1, diagTorre2** (todas las piezas):
- Se incrementan cuando colocas **cualquier pieza** (reina o torre)
- Se usan para verificar si una casilla está libre de ataques diagonales
- Importante: aunque las torres no atacan en diagonal, **ocupan** la diagonal y bloquean a las reinas

**Ejemplo**:
```
Tablero 3×3:
  0 1 2
0 R . .   R = Reina en (0,0)
1 . . .   T = Torre en (1,1)
2 . . T

¿Puedo colocar otra reina en (2,0)?

1. Verifico diag1, diag2:
   - La reina en (0,0) marcó sus diagonales
   - La diagonal ↘ de (0,0) pasa por (1,1) y (2,2)
   
2. Verifico diagTorre1, diagTorre2:
   - La torre en (1,1) también marcó sus "diagonales ocupadas"
   - Aunque no ataca en diagonal, OCUPA el espacio
   - La diagonal ↖ de (2,0) pasaría por (1,1) ← BLOQUEADA

Resultado: NO puedo colocar reina en (2,0) aunque la torre no ataca en diagonal
```

---

## Main - Inicialización

### Paso 1: Leer entrada
```java
int Q = Integer.parseInt(st.nextToken()); // Número de reinas
int R = Integer.parseInt(st.nextToken()); // Número de torres
int N = Q + R;                            // Tamaño del tablero
```

### Paso 2: Crear lista de posiciones
```java
List<Posicion> Posiciones = new ArrayList<>();
for (int i = 0; i < N; i++) {
  for (int j = 0; j < N; j++) {
    tablero[i][j] = Integer.parseInt(st.nextToken());
    Posiciones.add(new Posicion(tablero[i][j], i, j));
  }
}
```
Guardamos TODAS las casillas del tablero en una lista.

### Paso 3: **CLAVE** - Ordenar por valor descendente
```java
Collections.sort(Posiciones, (a, b) -> b.Valor - a.Valor);
```

**Ejemplo**:
```
Tablero 3×3:
1 5 2
9 3 7
4 8 6

Después de ordenar Posiciones:
[(9, 1,0), (8, 2,1), (7, 1,2), (6, 2,2), (5, 0,1), (4, 2,0), (3, 1,1), (2, 0,2), (1, 0,0)]
```

**¿Por qué ordenar?**
- Exploramos primero las casillas con mayor valor
- Encontramos buenas soluciones rápido
- Las podas funcionan mejor (cortan más ramas)

### Paso 4: Inicializar estructuras
```java
mejorGlobal = 0;
infoTablero info = new infoTablero(N);

diag1 = new int[2 * N - 1];        // Tamaño: 2N-1 diagonales posibles
diag2 = new int[2 * N - 1];
diagTorre1 = new int[2 * N - 1];
diagTorre2 = new int[2 * N - 1];
```

### Paso 5: Calcular cota superior inicial
```java
int cotaSup = 0;
for (int i = 0; i < N; i++) {
  cotaSup += Posiciones.get(i).Valor;
}
```
Suma de los N valores más altos (las N primeras posiciones después de ordenar).

**Ejemplo**:
```
N = 3, valores ordenados: [9, 8, 7, 6, 5, 4, 3, 2, 1]
cotaSup = 9 + 8 + 7 = 24
```

---

## Algoritmo de Backtracking

```java
public static void Torres_y_Reinas(
    List<Posicion> Posiciones,  // Lista de casillas ordenadas
    int start,                  // Índice desde donde empezar a buscar
    int[][] tablero,            // Matriz de valores
    infoTablero info,           // Filas/columnas ocupadas
    int Q,                      // Reinas restantes por colocar
    int R,                      // Torres restantes por colocar
    int N,                      // Tamaño del tablero
    int valor,                  // Suma acumulada hasta ahora
    int cotaSup                 // Valor máximo que podemos sumar aún
)
```

### Caso base: Solución encontrada
```java
if (Q == 0 && R == 0) {
  mejorGlobal = Math.max(mejorGlobal, valor);
  return;
}
```
Si colocamos todas las piezas, actualizamos el mejor resultado.

---

## Podas (Optimizaciones)

### Poda 1: Cota superior básica
```java
if (valor + cotaSup <= mejorGlobal) return;
```

**Ejemplo**:
```
mejorGlobal = 20 (ya encontramos una solución de 20)
valor actual = 5
cotaSup = 10

5 + 10 = 15 ≤ 20 → Esta rama NUNCA superará 20 → CORTAR
```

### Poda 2: Casillas insuficientes
```java
int restantes = Posiciones.size() - start;
if (restantes < Q + R) return;
```

**Ejemplo**:
```
start = 60, Posiciones.size() = 64
restantes = 64 - 60 = 4 casillas

Q = 3, R = 2 → necesitamos 5 piezas
4 < 5 → IMPOSIBLE completar → CORTAR
```

### Poda 3: **PODA AGRESIVA** (la más importante)

```java
int piezasRestantes = Q + R;
int sumaMaxPosible = 0;
int contadas = 0;

for (int idx = start; idx < Posiciones.size() && contadas < piezasRestantes; idx++) {
  int ti = Posiciones.get(idx).I;
  int tj = Posiciones.get(idx).J;
  
  // Solo contar casillas DISPONIBLES (fila y columna libres)
  if (!info.Filas[ti] && !info.Columnas[tj]) {
    sumaMaxPosible += Posiciones.get(idx).Valor;
    contadas++;
  }
}

if (valor + sumaMaxPosible <= mejorGlobal) return;
```

#### ¿Qué hace exactamente?

Calcula el **valor máximo REAL** que podemos obtener considerando las restricciones actuales.

#### Ejemplo detallado:

**Situación**:
```
Tablero 4×4
Ya colocamos 2 piezas:
- Reina en (0, 0) → fila 0 y columna 0 OCUPADAS
- Torre en (1, 1) → fila 1 y columna 1 OCUPADAS

Quedan por colocar: Q=1, R=1 (2 piezas)

Posiciones ordenadas restantes (desde start):
índice  valor  (i,j)     ¿Disponible?
0       100    (0,1)     NO (fila 0 ocupada)
1       90     (1,2)     NO (fila 1 ocupada)
2       85     (0,3)     NO (fila 0 ocupada)
3       80     (2,0)     NO (columna 0 ocupada)
4       75     (2,2)     SÍ ✓ (fila 2 y columna 2 libres)
5       70     (3,1)     NO (columna 1 ocupada)
6       65     (2,3)     SÍ ✓ (fila 2 y columna 3 libres)
7       60     (3,2)     SÍ ✓ (fila 3 y columna 2 libres)
...
```

**Poda básica (incorrecta)**:
```
cotaSup = 100 + 90 = 190
"En teoría puedo sumar hasta 190"
```

**Poda agresiva (correcta)**:
```
Recorro las posiciones y cuento solo las disponibles:
- (0,1) valor 100 → BLOQUEADA (fila 0)
- (1,2) valor 90  → BLOQUEADA (fila 1)
- (0,3) valor 85  → BLOQUEADA (fila 0)
- (2,0) valor 80  → BLOQUEADA (columna 0)
- (2,2) valor 75  → DISPONIBLE ✓ → contadas=1, sumaMaxPosible=75
- (3,1) valor 70  → BLOQUEADA (columna 1)
- (2,3) valor 65  → DISPONIBLE ✓ → contadas=2, sumaMaxPosible=140

Necesito 2 piezas, encontré 2 disponibles
sumaMaxPosible = 75 + 65 = 140

Si valor actual = 50 y mejorGlobal = 200:
50 + 140 = 190 ≤ 200 → CORTAR (no mejorará)
```

**Impacto**:
- Poda básica: "tal vez pueda sumar 190" → sigue explorando
- Poda agresiva: "máximo real es 140" → corta inmediatamente

---

## Sistema de Diagonales

### ¿Cómo identificar una diagonal?

En un tablero NxN, hay **2 tipos de diagonales**:

#### Diagonales tipo ↘ (de arriba-izquierda a abajo-derecha)
```
Tablero 4×4:
  0 1 2 3
0 A B C D
1 E F G H
2 I J K L
3 M N O P

Diagonales ↘:
0: A
1: E, B
2: I, F, C
3: M, J, G, D
4: N, K, H
5: O, L
6: P

Fórmula: d1 = i - j + (N - 1)
(0,0): 0-0+3=3 ✓
(1,0): 1-0+3=4 (no es 1) ✗
```

Espera, corrijamos:

```
d1 = i - j + (N - 1)

Ejemplos:
(0,0): 0-0+3=3
(0,1): 0-1+3=2
(0,2): 0-2+3=1
(0,3): 0-3+3=0

(1,0): 1-0+3=4
(1,1): 1-1+3=3  ← misma diagonal que (0,0) ✓
(1,2): 1-2+3=2  ← misma diagonal que (0,1) ✓

(3,3): 3-3+3=3  ← misma diagonal que (0,0), (1,1), (2,2) ✓
```

#### Diagonales tipo ↗ (de abajo-izquierda a arriba-derecha)
```
d2 = i + j

Ejemplos:
(0,0): 0+0=0
(0,1): 0+1=1
(1,0): 1+0=1  ← misma diagonal que (0,1) ✓
(2,0): 2+0=2
(1,1): 1+1=2  ← misma diagonal que (2,0) ✓
(3,3): 3+3=6
```

### Verificar si una diagonal está libre

```java
static boolean diagonalLibre(int i, int j, int N) {
  int d1 = i - j + N - 1;
  int d2 = i + j;
  return diagTorre1[d1] == 0 && diagTorre2[d2] == 0;
}
```

- Si `diagTorre1[d1] == 0` → ninguna pieza en diagonal ↘
- Si `diagTorre2[d2] == 0` → ninguna pieza en diagonal ↗
- Ambos cero → casilla libre de ataques diagonales

### Marcar/desmarcar diagonales

**Al colocar una reina en (i,j)**:
```java
int d1 = i - j + N - 1;
int d2 = i + j;

diag1[d1]++;         // Marca para otras reinas
diag2[d2]++;
diagTorre1[d1]++;    // Marca para todas las piezas
diagTorre2[d2]++;
```

**Al quitar la reina** (backtrack):
```java
diag1[d1]--;
diag2[d2]--;
diagTorre1[d1]--;
diagTorre2[d2]--;
```

**Al colocar una torre en (i,j)**:
```java
// Las torres NO atacan en diagonal, pero OCUPAN la casilla
diagTorre1[d1]++;  // Solo marca para evitar que reinas usen esta diagonal
diagTorre2[d2]++;
// NO marcamos diag1, diag2 (solo para reinas entre sí)
```

---

## Bucle Principal del Backtracking

```java
for (int k = start; k < Posiciones.size(); k++) {
  int i = Posiciones.get(k).I;
  int j = Posiciones.get(k).J;

  // Saltar casillas con fila/columna ocupada
  if (info.Filas[i] || info.Columnas[j]) continue;

  int d1 = i - j + N - 1;
  int d2 = i + j;

  // Intentar colocar REINA
  if (Q > 0 && diagonalLibre(i, j, N)) {
    // Marcar todo como ocupado
    info.Columnas[j] = true;
    info.Filas[i] = true;
    diag1[d1]++;
    diag2[d2]++;
    diagTorre1[d1]++;
    diagTorre2[d2]++;

    // Recursión con una reina menos
    Torres_y_Reinas(Posiciones, k + 1, tablero, info, Q - 1, R, N, 
                    valor + tablero[i][j], cotaSup - Posiciones.get(k).Valor);

    // BACKTRACK: deshacer cambios
    info.Columnas[j] = false;
    info.Filas[i] = false;
    diag1[d1]--;
    diag2[d2]--;
    diagTorre1[d1]--;
    diagTorre2[d2]--;
  }

  // Intentar colocar TORRE
  if (R > 0 && diagonalLibre(i, j, N)) {
    info.Columnas[j] = true;
    info.Filas[i] = true;
    diagTorre1[d1]++;  // Solo marca diagonales ocupadas, no ataca
    diagTorre2[d2]++;

    Torres_y_Reinas(Posiciones, k + 1, tablero, info, Q, R - 1, N,
                    valor + tablero[i][j], cotaSup - Posiciones.get(k).Valor);

    info.Columnas[j] = false;
    info.Filas[i] = false;
    diagTorre1[d1]--;
    diagTorre2[d2]--;
  }
}
```

### Detalles importantes:

1. **`k + 1` en la recursión**: Nunca revisitamos casillas anteriores
2. **`cotaSup - Posiciones.get(k).Valor`**: Actualizamos la cota al usar una casilla
3. **Backtracking**: Deshacemos TODOS los cambios para probar otras opciones

---

## Ejemplo Paso a Paso

### Entrada:
```
1 1
10 5
3  8
```
- Q=1 reina, R=1 torre
- Tablero 2×2:
  ```
  10  5
   3  8
  ```

### Ejecución:

**Inicialización**:
```
Posiciones ordenadas: [(10, 0,0), (8, 1,1), (5, 0,1), (3, 1,0)]
cotaSup = 10 + 8 = 18
mejorGlobal = 0
```

**Llamada inicial**: `Torres_y_Reinas(Posiciones, 0, ..., Q=1, R=1, valor=0, cotaSup=18)`

**Iteración 1**: Casilla (0,0) valor 10
- ¿Fila 0 libre? Sí. ¿Columna 0 libre? Sí.
- **Intentar REINA**:
  - Marcar: fila 0, columna 0, diag1[0], diag2[0]
  - Llamar: `Torres_y_Reinas(..., 1, Q=0, R=1, valor=10, cotaSup=8)`
  
  **Sub-llamada**:
  - Poda agresiva: busco 1 casilla disponible
    - (8, 1,1): fila 1 libre, columna 1 libre → sumaMaxPosible=8
    - 10 + 8 = 18 > 0 → continuar
  - Iteración casilla (1,1) valor 8:
    - Fila 1 libre ✓, columna 1 libre ✓
    - Diagonal libre ✓ (diag1[0], diag2[2] ambos 0)
    - **Intentar TORRE**:
      - Marcar: fila 1, columna 1
      - Llamar: `Torres_y_Reinas(..., Q=0, R=0, valor=18)`
      - **¡SOLUCIÓN!** mejorGlobal = 18
      - Desmarcar (backtrack)
  - Fin sub-llamada
  
  - Desmarcar fila 0, columna 0, diagonales
  
- **Intentar TORRE en (0,0)**:
  - Similar, pero Q=1, R=0
  - No encontrará mejor solución (las diagonales bloquearán)

**Resultado**: 18

---

## Resumen de Complejidad

| Aspecto | Implementación | Complejidad |
|---------|----------------|-------------|
| Verificar diagonal | Arrays indexados | O(1) |
| Marcar/desmarcar | Incremento/decremento | O(1) |
| Poda agresiva | Recorrer casillas restantes | O(N²) |
| Backtracking | Exponencial con poda | O(N! × 2^N) peor caso, mucho menor en práctica |

**Clave del éxito**: Las podas reducen el factor de ramificación dramáticamente, haciendo viable el backtracking.

