#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Ponto;

float AreaTriangulo(Ponto A, Ponto B, Ponto C) {
    return fabs((A.x * B.y + A.y * C.x + B.x * C.y) - (C.x * B.y + C.y * A.x + B.x * A.y));
}

double areaPoligono(Ponto *vertices, int numVertices) {
    double area = 0.0;
    for (int i = 1; i < numVertices - 1; i++) {
        area += AreaTriangulo(vertices[0], vertices[i], vertices[i + 1]);
    }
    return area / 2.0;
}

int main() {
    FILE *arquivo;

    arquivo = fopen("arquivo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    int numVertices;
    if (fscanf(arquivo, "%d", &numVertices) != 1) {
        printf("Erro ao ler o numero de vertices do arquivo.");
        fclose(arquivo);
        return 1;
    }

    Ponto *vertices = (Ponto *)malloc(numVertices * sizeof(Ponto));
    if (vertices == NULL) {
        printf("Erro ao alocar memoria para os vertices.");
        fclose(arquivo);
        return 1;
    }

    for (int i = 0; i < numVertices; i++) {
        if (fscanf(arquivo, "%f %f", &vertices[i].x, &vertices[i].y) != 2) {
            printf("Erro ao ler os vertices do arquivo.");
            fclose(arquivo);
            free(vertices);
            return 1;
        }
    }

    fclose(arquivo);

    double area = areaPoligono(vertices, numVertices);
    printf("A area do poligono e: %.2lf\n", area);

    free(vertices);

    return 0;
}

