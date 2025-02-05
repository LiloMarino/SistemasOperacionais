#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "checkPassword.h"

#define ASCII_MIN 33
#define ASCII_MAX 126
#define PASSWORD_LEN 12

void bruteForce(int start, int writePipe, bool usePipe) {
    char attempt[4] = {0};
    for (int i = ASCII_MIN; i <= ASCII_MAX; i++) {
        for (int j = ASCII_MIN; j <= ASCII_MAX; j++) {
            for (int k = ASCII_MIN; k <= ASCII_MAX; k++) {
                attempt[0] = i;
                attempt[1] = j;
                attempt[2] = k;
                if (checkPassword(attempt, start) == 0) {
                    if (usePipe) {
                        // Envia a senha encontrada para o processo pai pelo pipe
                        write(writePipe, attempt, sizeof(attempt));
                        close(writePipe);
                    } else {
                        // Imprime diretamente no terminal
                        printf("Senha encontrada: %s (range: %d-%d)\n", attempt, start, start + 2);
                    }
                    return;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    bool useFork = false;

    // Verifica se deve usar o fork
    if (argc > 1 && strcmp(argv[1], "-f") == 0) {
        useFork = true;
    }

    printf("Processo %d com pai %d quebrando a senha...\n", getpid(), getppid());
    if (useFork) {
        int pipes[4][2]; // Um pipe para cada processo filho

        // Cria os pipes
        for (int i = 0; i < 4; i++) {
            if (pipe(pipes[i]) == -1) {
                perror("Erro ao criar pipe");
                return EXIT_FAILURE;
            }
        }

        // Criação dos processos filhos
        for (int i = 0; i < 4; i++) {
            pid_t pid = fork();
            if (pid == -1) {
                perror("Erro ao criar processo filho");
                return EXIT_FAILURE;
            }

            if (pid == 0) { 
                // Código do processo filho
                close(pipes[i][0]);
                bruteForce(i * 3, pipes[i][1], true);
                exit(0);
            } else { 
                // Código do processo pai
                close(pipes[i][1]);
            }
        }

        // Espera todos os processos filhos
        for (int i = 0; i < 4; i++) {
            wait(NULL);
        }
        
        // O pai lê as respostas dos filhos
        char password[4] = {0};
        for (int i = 0; i < 4; i++) {
            ssize_t bytesRead = read(pipes[i][0], password, sizeof(password));
            if (bytesRead > 0) {
                printf("Processo pai recebeu a senha: %s\n", password);
            }
            close(pipes[i][0]);
        }

    } else {
        // Sem fork, testar todas as partes da senha sequencialmente
        for (int i = 0; i < 4; i++) {
            bruteForce(i * 3, -1, false);
        }
    }

    return EXIT_SUCCESS;
}
