#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 9

#define MINAS 25
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

typedef struct {
    int temMina;
    int revelado;
    int marcado;
    int minasAoRedor;
} Celula;

Celula campo[TAM][TAM];

void iniciarCampo() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            campo[i][j].temMina = 0;
            campo[i][j].revelado = 0;
            campo[i][j].marcado = 0;
            campo[i][j].minasAoRedor = 0;
        }
    }
}

void plantarMinas() {
    int colocadas = 0;
    while (colocadas < MINAS) {
        int x = rand() % TAM;
        int y = rand() % TAM;

        if (!campo[x][y].temMina) {
            campo[x][y].temMina = 1;
            colocadas++;
        }
    }



}

void calcularMinasVizinhas() {
    int inicio = 0;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (campo[i][j].temMina) {
                continue;
            }

            int minas = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int ni = i + dx;
                    int nj = j + dy;

                    if (ni >= 0 && ni < TAM && nj >= 0 && nj < TAM) {
                        if (campo[ni][nj].temMina) {
                            minas++;
                        }
                    }
                }
            }

            campo[i][j].minasAoRedor = minas;
            if(minas==0 && !inicio){
                campo[i][j].revelado = 1;
                inicio = 1;
            }
        }
    }
}


void mostrarCampoFinal() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (campo[i][j].temMina) {
                printf(RED " * " RESET);
            } else {
                printf(" . ");
            }
        }
        printf("\n");
    }
}



void mostrarCampoVisivel() {
    printf("\n    ");
    for (int j = 0; j < TAM; j++) {
        printf(" %d ", j+1);
    }
    printf("\n    --------------------------\n");

    for (int i = 0; i < TAM; i++) {
        printf(" %d |", i + 1);
        for (int j = 0; j < TAM; j++) {
            if (campo[i][j].revelado) {
                if (campo[i][j].temMina) {
                    printf(RED " * " RESET);
                } else {
                    printf(" %d ", campo[i][j].minasAoRedor);
                }
            } else if (campo[i][j].marcado) {
                printf(YELLOW " M " RESET);
            } else {
                printf(" - ");
            }
        }
        printf("\n");
    }
}

int verificarVitoria() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (!campo[i][j].temMina && !campo[i][j].revelado) {
                return 0;
            }
        }
    }
    return 1;
}


int verificarMarcacaoCorreta() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (campo[i][j].temMina && !campo[i][j].marcado) return 0;
            if (!campo[i][j].temMina && campo[i][j].marcado) return 0;
        }
    }
    return 1;
}

int lerCoordenada(char* nome) {
    int valor;
    char c;

    while (1) {
        printf("Digite o valor da %s (1 a %d): ", nome, TAM);
        if (scanf("%d%c", &valor, &c) != 2 || c != '\n') {
            printf(RED "Entrada invalida! Digite um numero inteiro!\n" RESET);
            while (getchar() != '\n');
        } else if (valor < 1 || valor > TAM) {
            printf(RED "Fora dos limites! %s deve estar entre 1 e %d!\n" RESET, nome, TAM);
        } else {
            return valor - 1;
        }
    }
}


void jogar() {
    int x, y;
    char acao;
    char c;
    char lixo;

    while (1) {
        mostrarCampoVisivel();

        do {
        printf("\nDigite A para abrir ou M para marcar/desmarcar: ");

        if (scanf(" %c%c", &acao, &lixo) != 2 || lixo != '\n') {
            printf(RED "Entrada invalida! Digite apenas uma letra (A ou M)!\n" RESET);
            while (getchar() != '\n'); // limpa o buffer até o Enter
            continue;
        }

        if (acao != 'A' && acao != 'a' && acao != 'M' && acao != 'm') {
            printf(RED "Acao invalida! Tem que ser A ou M!\n" RESET);
        }

        } while (acao != 'A' && acao != 'a' && acao != 'M' && acao != 'm');


        int x = lerCoordenada("linha");
        int y = lerCoordenada("coluna");

        if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
            printf(RED "Coordenadas invalidas!\n" RESET);
            continue;
        }

        if (acao == 'A' || acao == 'a') {
            if (campo[x][y].temMina) {
                system("cls");
                printf(RED "BOOM! Voce perdeu!\n" RESET);
                campo[x][y].revelado = 1;
                mostrarCampoFinal();
                break;
            } else if(campo[x][y].marcado){
                system("cls");
                printf(YELLOW "Espaco marcado melhor nao abrir aqui ou desmarque antes\n" RESET);
                continue;
            } else if(campo[x][y].revelado){
                system("cls");
                printf(YELLOW "Espaco ja aberto\n" RESET);
                continue;
            } else {
                campo[x][y].revelado = 1;

                if(verificarVitoria()){
                    system("cls");
                    printf(BLUE "Parabens, voce venceu abrindo todos os campos sem mina!\n" RESET);
                    mostrarCampoFinal();
                    break;
                }
            }
        } else if (acao == 'M' || acao == 'm') {
            if(campo[x][y].revelado){
                system("cls");
                printf(YELLOW "Espaco ja aberto\n" RESET);
                continue;
            }
            campo[x][y].marcado = !campo[x][y].marcado;

            if(verificarMarcacaoCorreta()){
                system("cls");
                printf(BLUE "Parabens, voce venceu marcando todas as minas!\n" RESET);
                mostrarCampoFinal();
                break;
            }
        }

        system("cls");
    }
}





int main() {
    srand(time(NULL));

    printf("   ---------------------------\n");
    printf("   |    CAMPO MINADO EM C    |\n");
    printf("   ---------------------------\n");



    iniciarCampo();
    plantarMinas();
    calcularMinasVizinhas();
    jogar();

    return 0;
}
