#include <stdio.h>
#include <string.h>

// soma dos n primeiros termos da sequencia de Fibonacci (1, 1, 2, 3, 5...)
long long somaFibonacci(int n) {
    long long a = 1, b = 1, soma = 0, prox;
    int i;

    for (i = 1; i <= n; i++) {
        soma = soma + a;
        prox = a + b;
        a = b;
        b = prox;
    }
    return soma;
}

int ehPrimo(long long n) {
    long long i;
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
    char nomes[5][50];
    int termos[5];
    long long resultados[5];
    int premiado[5] = {0, 0, 0, 0, 0};
    int vencedor[3] = {-1, -1, -1}; // guarda o indice de quem ganhou cada lugar
    int i, ganhou = 0;
    long long soma = 0;
    float media;

    for (i = 0; i < 5; i++) {
        printf("Nome do apostador %d: ", i + 1);
        scanf(" %49[^\n]", nomes[i]);

        do {
            printf("Valor inteiro positivo de %s: ", nomes[i]);
            scanf("%d", &termos[i]);
        } while (termos[i] <= 0);

        resultados[i] = somaFibonacci(termos[i]);
        soma = soma + resultados[i];
    }

    media = (float) soma / 5;

    // 1o lugar: maior resultado primo
    for (i = 0; i < 5; i++) {
        if (ehPrimo(resultados[i]) == 1) {
            if (vencedor[0] == -1 || resultados[i] > resultados[vencedor[0]]) {
                vencedor[0] = i;
            }
        }
    }
    if (vencedor[0] != -1) {
        premiado[vencedor[0]] = 1;
    }

    // 2o lugar: maior resultado par entre quem ainda nao foi premiado
    for (i = 0; i < 5; i++) {
        if (premiado[i] == 0 && resultados[i] % 2 == 0) {
            if (vencedor[1] == -1 || resultados[i] > resultados[vencedor[1]]) {
                vencedor[1] = i;
            }
        }
    }
    if (vencedor[1] != -1) {
        premiado[vencedor[1]] = 1;
    }

    // 3o lugar: maior resultado acima da media entre quem ainda nao foi premiado
    for (i = 0; i < 5; i++) {
        if (premiado[i] == 0 && resultados[i] > media) {
            if (vencedor[2] == -1 || resultados[i] > resultados[vencedor[2]]) {
                vencedor[2] = i;
            }
        }
    }
    if (vencedor[2] != -1) {
        premiado[vencedor[2]] = 1;
    }

    // mostra so os vencedores
    printf("\n===== VENCEDORES =====\n");
    for (i = 0; i < 3; i++) {
        if (vencedor[i] != -1) {
            printf("%do lugar: %s\n", i + 1, nomes[vencedor[i]]);
            ganhou = 1;
        }
    }
    if (ganhou == 0) {
        printf("Nenhum apostador foi premiado.\n");
    }

    return 0;
}
