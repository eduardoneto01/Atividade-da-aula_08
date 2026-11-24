#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define QTD 4

double fatorial(int n) {
    double f = 1;
    int i;
    for (i = 2; i <= n; i++) {
        f = f * i;
    }
    return f;
}

double potencia(double base, int expoente) {
    double r = 1;
    int i;
    for (i = 0; i < expoente; i++) {
        r = r * base;
    }
    return r;
}

// verifica se o id da posicao pos aparece em outra posicao do vetor
int idRepetido(double ids[], int tam, int pos) {
    int i;
    for (i = 0; i < tam; i++) {
        if (i != pos && ids[i] == ids[pos]) {
            return 1;
        }
    }
    return 0;
}

// media ponderada: o primeiro valor tem peso 1, o segundo peso 2 e assim por diante
float mediaPonderada(float *valores, int qtd) {
    float soma = 0, pesos = 0;
    int i;
    for (i = 0; i < qtd; i++) {
        soma = soma + valores[i] * (i + 1);
        pesos = pesos + (i + 1);
    }
    return soma / pesos;
}

int main() {
    char nomes[QTD][50];
    int idades[QTD];
    double ids[QTD];
    int qtd[QTD];
    float medias[QTD];
    int classif[QTD];
    float **valores;
    char tempNome[50];
    int tempInt;
    double tempId;
    float *tempPtr;
    int i, j, metade;
    int achados = 0;
    float lado[2];
    float diagonal = 0;

    // ---------- 1. cadastro ----------
    for (i = 0; i < QTD; i++) {
        printf("Nome do participante %d: ", i + 1);
        scanf(" %49[^\n]", nomes[i]);
        do {
            printf("Idade de %s: ", nomes[i]);
            scanf("%d", &idades[i]);
        } while (idades[i] <= 0);

        ids[i] = fatorial(idades[i]) / 2;
    }

    // ---------- 2. captura dos valores ----------
    valores = (float**) malloc(QTD * sizeof(float*));
    for (i = 0; i < QTD; i++) {
        do {
            printf("\nQuantos valores deseja registrar para %s? ", nomes[i]);
            scanf("%d", &qtd[i]);
        } while (qtd[i] <= 0);

        valores[i] = (float*) malloc(qtd[i] * sizeof(float));
        for (j = 0; j < qtd[i]; j++) {
            printf("Valor %d: ", j + 1);
            scanf("%f", &valores[i][j]);
        }
    }

    // a quantidade de valores so e conhecida agora, entao os ids repetidos sao corrigidos aqui
    for (i = 0; i < QTD; i++) {
        if (idRepetido(ids, QTD, i) == 1) {
            metade = idades[i] / 2;
            ids[i] = potencia(fatorial(metade), qtd[i]);

            // se ainda repetir, refaz o calculo com a metade da metade...
            while (idRepetido(ids, QTD, i) == 1 && metade > 0) {
                metade = metade / 2;
                ids[i] = potencia(fatorial(metade), qtd[i]);
            }
            // ultimo recurso para garantir id exclusivo
            while (idRepetido(ids, QTD, i) == 1) {
                ids[i] = ids[i] + 1;
            }
        }
    }

    // ---------- guarda os dois primeiros valores nao negativos (na ordem da entrada) ----------
    for (i = 0; i < QTD; i++) {
        for (j = 0; j < qtd[i]; j++) {
            if (valores[i][j] >= 0 && achados < 2) {
                lado[achados] = valores[i][j];
                achados++;
            }
        }
    }

    // ---------- 3. ordena os participantes pelo nome ----------
    for (i = 0; i < QTD - 1; i++) {
        for (j = 0; j < QTD - 1 - i; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                strcpy(tempNome, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], tempNome);

                tempInt = idades[j];
                idades[j] = idades[j + 1];
                idades[j + 1] = tempInt;

                tempId = ids[j];
                ids[j] = ids[j + 1];
                ids[j + 1] = tempId;

                tempInt = qtd[j];
                qtd[j] = qtd[j + 1];
                qtd[j + 1] = tempInt;

                // troca a linha da matriz inteira
                tempPtr = valores[j];
                valores[j] = valores[j + 1];
                valores[j + 1] = tempPtr;
            }
        }
    }

    // ---------- 4. media ponderada ----------
    for (i = 0; i < QTD; i++) {
        medias[i] = mediaPonderada(valores[i], qtd[i]);
    }

    // ---------- 5. diagonal do retangulo ----------
    if (achados == 2) {
        diagonal = sqrt(lado[0] * lado[0] + lado[1] * lado[1]);
        printf("\nDiagonal do retangulo (lados %.2f e %.2f): %.2f\n", lado[0], lado[1], diagonal);
    } else {
        printf("\nNao foi possivel calcular a diagonal (menos de dois valores nao negativos).\n");
    }

    // ---------- 6. classificacao ----------
    if (achados == 2) {
        for (i = 0; i < QTD; i++) {
            if (fabs(medias[i] - diagonal) < 0.0001) {
                classif[i] = 0; // sobre
            } else if (medias[i] > diagonal) {
                classif[i] = 1; // acima
            } else {
                classif[i] = 2; // abaixo
            }
        }
    }

    // ---------- 7. saida ----------
    printf("\n========== CLASSIFICACAO FINAL ==========\n\n");
    for (i = 0; i < QTD; i++) {
        printf("%s (ID %.0f) ... media ponderada: %.2f", nomes[i], ids[i], medias[i]);
        if (achados == 2) {
            if (classif[i] == 0) {
                printf(" ... SOBRE A DIAGONAL");
            } else if (classif[i] == 1) {
                printf(" ... ACIMA DA DIAGONAL");
            } else {
                printf(" ... ABAIXO DA DIAGONAL");
            }
        }
        printf("\n");
    }
    printf("\n=========================================\n");

    for (i = 0; i < QTD; i++) {
        free(valores[i]);
    }
    free(valores);

    return 0;
}
