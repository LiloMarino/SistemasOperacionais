#ifndef PHYSICAL_MEMORY_HPP
#define PHYSICAL_MEMORY_HPP

#include <array>
#include <functional>
#include "page.hpp"
#include "replacement_policy.hpp"

class PhysicalMemory
{
private:
    std::vector<Frame> memory;
    std::queue<int> fifo_queue;
    std::unordered_map<int, int> access_counters;
    ReplacementPolicy replacement_policy;
    std::function<void(int)> on_page_remove; // Callback para "evento" de remoção de página
    int timestamp = 0;

public:
    /**
     * @brief Construtor de PhysicalMemory
     * @param num_frames Número de quadros na memória física
     * @param policy Política de substituição
     */
    PhysicalMemory(int num_frames, ReplacementPolicy policy);

    /**
     * @brief Define o callback para o evento de remoção de uma página
     * @param callback Callback para o evento de remoção
     */
    void setPageRemoveCallback(std::function<void(int)> callback);

    /**
     * @brief Adiciona uma página na memória física
     * @param page Página a ser adicionada
     * @return Índice do quadro onde a página foi adicionada
     */
    int addPage(Page &&page);

    /**
     * @brief Obtém um quadro da memória física pelo índice
     * @param index Índice do quadro
     * @return Referência para o quadro na memória
     */
    Frame &getFrame(int index);
};

#endif