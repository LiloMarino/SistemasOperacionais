## Problema do Barbeiro Sonolento

O problema do barbeiro sonolento é um problema clássico de sincronização e comunicação entre processos. Ele pode ser descrito assim:

1. Um barbeiro tem uma cadeira de trabalho e uma sala de espera com um número limitado de cadeiras.
2. Se não há clientes, o barbeiro dorme.
3. Quando um cliente chega:
   - Se o barbeiro está dormindo, o cliente o acorda.
   - Se todas as cadeiras de espera estão ocupadas, o cliente sai.
   - Se há cadeiras disponíveis, o cliente senta na sala de espera.
4. O barbeiro corta o cabelo do cliente enquanto houver clientes na fila.

## Código da Solução do Problema

```c++
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

const int NUM_CADEIRAS = 3; // Número de cadeiras na sala de espera

sem_t sem_clientes;    // Contagem de clientes esperando
sem_t sem_barbeiro;    // Indica se o barbeiro está pronto
sem_t sem_mutex;       // Semáforo binário para exclusão mútua
int clientes_esperando = 0;

void* barbeiro(void*) {
    while (true) {
        sem_wait(&sem_clientes);    // Espera um cliente
        sem_wait(&sem_mutex);       // Exclusão mútua para ajustar fila
        clientes_esperando--;       
        std::cout << "Barbeiro cortando cabelo. Clientes esperando: " << clientes_esperando << std::endl;
        sem_post(&sem_mutex);       // Libera exclusão mútua
        sem_post(&sem_barbeiro);    // Indica que o barbeiro está pronto
        sleep(2);                   // Simula o tempo do corte de cabelo
    }
    return nullptr;
}

void* cliente(void*) {
    sem_wait(&sem_mutex);           // Exclusão mútua para verificar fila
    if (clientes_esperando < NUM_CADEIRAS) {
        clientes_esperando++;
        std::cout << "Cliente entrou. Clientes esperando: " << clientes_esperando << std::endl;
        sem_post(&sem_mutex);       // Libera exclusão mútua
        sem_post(&sem_clientes);    // Notifica chegada do cliente
        sem_wait(&sem_barbeiro);    // Espera o barbeiro
        std::cout << "Cliente sendo atendido." << std::endl;
    } else {
        std::cout << "Sala cheia. Cliente saiu." << std::endl;
        sem_post(&sem_mutex);       // Libera exclusão mútua
    }
    return nullptr;
}

int main() {
    pthread_t tid_barbeiro;
    pthread_t tid_clientes[10];

    sem_init(&sem_clientes, 0, 0); // Inicialmente nenhum cliente
    sem_init(&sem_barbeiro, 0, 0); // Barbeiro dormindo
    sem_init(&sem_mutex, 0, 1);    // Semáforo binário para exclusão mútua

    pthread_create(&tid_barbeiro, nullptr, barbeiro, nullptr);

    for (int i = 0; i < 10; i++) {
        pthread_create(&tid_clientes[i], nullptr, cliente, nullptr);
        sleep(1); // Simula a chegada dos clientes
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(tid_clientes[i], nullptr);
    }

    pthread_cancel(tid_barbeiro); // Cancela o barbeiro para encerrar o programa

    sem_destroy(&sem_clientes);
    sem_destroy(&sem_barbeiro);
    sem_destroy(&sem_mutex);

    return 0;
}
```

## Explicação da Solução