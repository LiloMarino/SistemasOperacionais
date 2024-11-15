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

void bruteForce(int start) {
    char attempt[4] = {0};
    for (int i = ASCII_MIN; i <= ASCII_MAX; i++) {
        for (int j = ASCII_MIN; j <= ASCII_MAX; j++) {
            for (int k = ASCII_MIN; k <= ASCII_MAX; k++) {
                attempt[0] = i;
                attempt[1] = j;
                attempt[2] = k;
                if (checkPassword(attempt, start) == 0) {
                    printf("Processo %d com pai %d encontrou %d-%d: %s\n",
                           getpid(), getppid(), start, start + 2, attempt);
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
        // Com fork, para cada filho criado, ele irá quebrar uma parte da senha
        for (int i = 0; i < 4; i++) {
            pid_t pid = fork();
            // Verifica se conseguiu criar o processo filho
            if (pid == 0) {
                bruteForce(i * 3);
                exit(0);
            }
        }

        // Espera todos os processos filhos
        for (int i = 0; i < 4; i++) {
            wait(NULL);
        }
    } else {
        // Sem fork, testar todas as partes da senha sequencialmente
        for (int i = 0; i < 4; i++) {
            bruteForce(i * 3);
        }
    }

    return 0;
}
