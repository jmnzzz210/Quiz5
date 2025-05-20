/* Quiz 5: Matriz dinámica
 * 
 * Autores: [Jafet Cruz, Brandon Jimenez]
 * Fecha: [19-5-2025]
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Función para imprimir la matriz 
void imprimir_matriz(const int *matriz, int filas, int columnas) {
    // Pointer guard
    if (matriz ==  NULL) {
        printf("Error: matriz nula.\n");
        return;
    }
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%5d ", matriz[i * columnas + j]);
        }
        putchar('\n');
    }
}

//Aquí se le solicita las dimensiones al usuario
int solicitar_dimensiones(const char *mensaje, int *m, int *n) {
    printf("%s", mensaje);
    if (scanf("%d %d", m, n) != 2 || *m <= 0 || *n <= 0) {
        fprintf(stderr, "Entrada inválida. Intente de nuevo.\n");
        return 0;
    }
    return 1;
}

#define RANGO_ALEATORIO 100 // Constante para el rango del número aleatorio (1-100)

int main(void) {
    int filas, columnas, nuevas_filas, nuevas_columnas;
    int *matriz = NULL;

    // Inicializa el generador de números aleatorios
    srand((unsigned)time(NULL));

    // Solicita las dimensiones iniciales
    if (!solicitar_dimensiones("Dimensiones iniciales (filas columnas): ", &filas, &columnas))
        return EXIT_FAILURE;

    // Reserva memoria dinámica para la matriz
    matriz = malloc((size_t)filas * columnas * sizeof *matriz);
    if (matriz == NULL) {
        return EXIT_FAILURE;
    }

    // Rellena la matriz con números aleatorios entre 1 y RANGO_ALEATORIO
    for (int i = 0; i < filas * columnas; i++)
        matriz[i] = rand() % RANGO_ALEATORIO + 1;

    printf("\nMatriz original:\n");
    imprimir_matriz(matriz, filas, columnas);

    // Solicita nuevas dimensiones
    if (!solicitar_dimensiones("\nNuevo tamaño (filas columnas): ", &nuevas_filas, &nuevas_columnas)) {
        free(matriz);
        return EXIT_FAILURE;
    }

    // Pointer guard
    if (matriz == NULL) {
        fprintf(stderr, "Error: la matriz no fue inicializada correctamente.\n");
        return EXIT_FAILURE;
    }

    // Crea una nueva matriz con las dimensiones actualizadas
    int *nueva_matriz = malloc((size_t)nuevas_filas * nuevas_columnas * sizeof *nueva_matriz);
    if (nueva_matriz == NULL) {
        free(matriz);
        return EXIT_FAILURE;
    }

    // Aqui se copian los valores existentes y rellena las nuevas celdas
    for (int i = 0; i < nuevas_filas; i++) {
        for (int j = 0; j < nuevas_columnas; j++) {
            if (i < filas && j < columnas) {
                nueva_matriz[i * nuevas_columnas + j] = matriz[i * columnas + j];
            } else {
                nueva_matriz[i * nuevas_columnas + j] = rand() % RANGO_ALEATORIO + 1;
            }
        }
    }

    // Libera la memoria de la matriz original y actualiza el puntero
    free(matriz);
    matriz = nueva_matriz;

    printf("\nMatriz redimensionada:\n");
    imprimir_matriz(matriz, nuevas_filas, nuevas_columnas);

    // Libera la memoria utilizada
    free(matriz);
    matriz = NULL; //Se utiliza una buena práctica, la cual es colocar el pointer apuntando a NULL

    return EXIT_SUCCESS;
}
