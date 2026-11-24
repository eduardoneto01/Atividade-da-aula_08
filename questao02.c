#include <stdio.h>
#include <stdlib.h>

int main() {
    int *v, *posPares, *negImpares;
    int i, j, aux;
    int qtdPP = 0, qtdNI = 0;

    v = (int*) malloc(10 * sizeof(int));
    posPares = (int*) malloc(10 * sizeof(int));
    negImpares = (int*) malloc(10 * sizeof(int));

    for (i = 0; i < 10; i++) {
        printf("Digite o valor %d: ", i + 1);
        scanf("%d", &v[i]);
    }

    // separa em dois vetores
    for (i = 0; i < 10; i++) {
        if (v[i] > 0 && v[i] % 2 == 0) {
            posPares[qtdPP] = v[i];
            qtdPP++;
        }
        if (v[i] < 0 && v[i] % 2 != 0) {
            negImpares[qtdNI] = v[i];
            qtdNI++;
        }
    }

    // ordem crescente - positivos e pares
    for (i = 0; i < qtdPP - 1; i++) {
        for (j = 0; j < qtdPP - 1 - i; j++) {
            if (posPares[j] > posPares[j + 1]) {
                aux = posPares[j];
                posPares[j] = posPares[j + 1];
                posPares[j + 1] = aux;
            }
        }
    }

    // ordem crescente - negativos e impares
    for (i = 0; i < qtdNI - 1; i++) {
        for (j = 0; j < qtdNI - 1 - i; j++) {
            if (negImpares[j] > negImpares[j + 1]) {
                aux = negImpares[j];
                negImpares[j] = negImpares[j + 1];
                negImpares[j + 1] = aux;
            }
        }
    }

    printf("\nPositivos e pares: ");
    if (qtdPP == 0) {
        printf("nenhum");
    }
    for (i = 0; i < qtdPP; i++) {
        printf("%d ", posPares[i]);
    }

    printf("\nNegativos e impares: ");
    if (qtdNI == 0) {
        printf("nenhum");
    }
    for (i = 0; i < qtdNI; i++) {
        printf("%d ", negImpares[i]);
    }
    printf("\n");

    free(v);
    free(posPares);
    free(negImpares);

    return 0;
}
