#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *v, *distintos, *cont, *impares, *pares;
    int i, j, achou, aux;
    int qtdDist = 0, qtdImp = 0, qtdPar = 0;
    char nomes[12][50];
    float *precos;
    char tempNome[50];
    float tempPreco;

    v = (int*) malloc(12 * sizeof(int));
    distintos = (int*) malloc(12 * sizeof(int));
    cont = (int*) malloc(12 * sizeof(int));
    impares = (int*) malloc(12 * sizeof(int));
    pares = (int*) malloc(12 * sizeof(int));
    precos = (float*) malloc(12 * sizeof(float));

    // leitura dos 12 numeros
    for (i = 0; i < 12; i++) {
        printf("Digite o numero %d: ", i + 1);
        scanf("%d", &v[i]);
    }

    // a) conta quantas vezes cada numero aparece
    for (i = 0; i < 12; i++) {
        achou = 0;
        for (j = 0; j < qtdDist; j++) {
            if (distintos[j] == v[i]) {
                cont[j]++;
                achou = 1;
            }
        }
        if (achou == 0) {
            distintos[qtdDist] = v[i];
            cont[qtdDist] = 1;
            qtdDist++;
        }
    }

    // b) e c) separa os numeros com ocorrencia impar e par
    for (i = 0; i < qtdDist; i++) {
        if (cont[i] % 2 != 0) {
            impares[qtdImp] = distintos[i];
            qtdImp++;
        } else {
            pares[qtdPar] = distintos[i];
            qtdPar++;
        }
    }

    // ordena o vetor de pares em ordem decrescente
    for (i = 0; i < qtdPar - 1; i++) {
        for (j = 0; j < qtdPar - 1 - i; j++) {
            if (pares[j] < pares[j + 1]) {
                aux = pares[j];
                pares[j] = pares[j + 1];
                pares[j + 1] = aux;
            }
        }
    }

    // d) cadastro dos produtos (um para cada numero de ocorrencia impar)
    for (i = 0; i < qtdImp; i++) {
        printf("\nProduto %d (quantidade a comprar: %d)\n", i + 1, impares[i]);
        printf("Nome: ");
        scanf(" %49[^\n]", nomes[i]);
        printf("Preco unitario: ");
        scanf("%f", &precos[i]);
    }

    // e) ordena os produtos por ordem alfabetica
    for (i = 0; i < qtdImp - 1; i++) {
        for (j = 0; j < qtdImp - 1 - i; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                strcpy(tempNome, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], tempNome);

                tempPreco = precos[j];
                precos[j] = precos[j + 1];
                precos[j + 1] = tempPreco;

                aux = impares[j];
                impares[j] = impares[j + 1];
                impares[j + 1] = aux;
            }
        }
    }

    // resultados finais
    printf("\n===== RESULTADOS =====\n");

    printf("\nNumeros informados: ");
    for (i = 0; i < 12; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("\nNumero e quantidade de vezes que aparece:\n");
    for (i = 0; i < qtdDist; i++) {
        printf("%d -> %d vez(es)\n", distintos[i], cont[i]);
    }

    printf("\nProdutos para a compra (ordem alfabetica):\n");
    if (qtdImp == 0) {
        printf("Nenhum produto cadastrado.\n");
    }
    for (i = 0; i < qtdImp; i++) {
        printf("%s - R$ %.2f - quantidade: %d\n", nomes[i], precos[i], impares[i]);
    }

    printf("\nNumeros com ocorrencia par (ordem decrescente): ");
    if (qtdPar == 0) {
        printf("nenhum");
    }
    for (i = 0; i < qtdPar; i++) {
        printf("%d ", pares[i]);
    }
    printf("\n");

    free(v);
    free(distintos);
    free(cont);
    free(impares);
    free(pares);
    free(precos);

    return 0;
}
