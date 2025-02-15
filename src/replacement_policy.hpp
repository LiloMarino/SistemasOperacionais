#ifndef REPLACEMENT_POLICY_HPP
#define REPLACEMENT_POLICY_HPP

#include <queue>
#include <unordered_map>

/**
 * @brief Define o tipo da política de substituição como um ponteiro para função.
 */
using ReplacementPolicy = int (*)(std::queue<int> &, std::unordered_map<int, int> &);

/**
 * @brief Implementação FIFO (First-In, First-Out).
 * @param fifo_queue Fila que mantém a ordem de inserção das páginas.
 * @param _ (Parâmetro ignorado, pois FIFO não usa contador de acessos).
 * @return Página a ser removida.
 */
int fifo_policy(std::queue<int> &fifo_queue, std::unordered_map<int, int> &);

/**
 * @brief Implementação LRU (Least Recently Used).
 * @param _ (Parâmetro ignorado, pois LRU não usa fila FIFO).
 * @param access_counters Mapa que armazena os tempos de acesso das páginas.
 * @return Página a ser removida.
 */
int lru_policy(std::queue<int> &, std::unordered_map<int, int> &access_counters);

#endif
