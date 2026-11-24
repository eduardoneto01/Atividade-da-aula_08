#include <stdio.h>
#include <stdlib.h>

int ehPrimo(int n) {
    int i;
    if (n < 2) {
        return 0;
    }
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int *v, *distintos, *cont, *primeiraPos;
    int i, j, achou;
    int qtdDist = 0;
    int temPrimo = 0;
    int soma, pos;
    char animais[20][30];
    int qtdAnimais = 0;

    v = (int*) malloc(15 * sizeof(int));
    distintos = (int*) malloc(15 * sizeof(int));
    cont = (int*) malloc(15 * sizeof(int));
    primeiraPos = (int*) malloc(15 * sizeof(int));

    for (i = 0; i < 15; i++) {
        printf("Digite o numero %d: ", i + 1);
        scanf("%d", &v[i]);
    }

    // conta as ocorrencias de cada numero e guarda a primeira posicao (comecando em 1)
    for (i = 0; i < 15; i++) {
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
            primeiraPos[qtdDist] = i + 1;
            qtdDist++;
        }
    }

    // mostra a tabela
    printf("\nNumero | Ocorrencias | Classificacao\n");
    for (i = 0; i < qtdDist; i++) {
        printf("%6d | %11d | ", distintos[i], cont[i]);
        if (cont[i] == 1) {
            printf("Nao repetido\n");
        } else if (ehPrimo(distintos[i]) == 1) {
            temPrimo = 1;
            if (cont[i] % 2 != 0) {
                printf("Primo - impar\n");
            } else {
                printf("Primo - par\n");
            }
        } else {
            if (cont[i] % 2 != 0) {
                printf("Impar\n");
            } else {
                printf("Par\n");
            }
        }
    }

    // cadastro dos animais (so precisa se tiver algum primo repetido)
    if (temPrimo == 1) {
        printf("\nQuantos animais deseja cadastrar (maximo 20)? ");
        scanf("%d", &qtdAnimais);
        if (qtdAnimais > 20) {
            qtdAnimais = 20;
        }
        for (i = 0; i < qtdAnimais; i++) {
            printf("Nome do animal %d: ", i + 1);
            scanf(" %29[^\n]", animais[i]);
        }
    }

    printf("\n===== ANIMAIS CORRESPONDENTES =====\n");
    if (temPrimo == 0) {
        printf("Nenhum numero primo repetido.\n");
    }

    for (i = 0; i < qtdDist; i++) {
        if (cont[i] > 1 && ehPrimo(distintos[i]) == 1) {
            if (cont[i] % 2 != 0) {
                // ocorrencia impar: usa a soma de todas as ocorrencias
                soma = distintos[i] * cont[i];
                printf("Numero %d (soma %d): ", distintos[i], soma);
                pos = soma;
            } else {
                // ocorrencia par: usa a posicao no vetor
                printf("Numero %d (posicao %d): ", distintos[i], primeiraPos[i]);
                pos = primeiraPos[i];
            }

            if (pos >= 1 && pos <= qtdAnimais) {
                printf("%s\n", animais[pos - 1]);
            } else {
                printf("Nao existe correspondencia.\n");
            }
        }
    }

    free(v);
    free(distintos);
    free(cont);
    free(primeiraPos);

    return 0;
}
