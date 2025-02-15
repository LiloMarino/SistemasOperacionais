#ifndef PHYSICAL_MEMORY_HPP
#define PHYSICAL_MEMORY_HPP

#include <array>
#include "page.hpp"

class PhysicalMemory
{
public:
    static constexpr int FRAMES = 256;

private:
    std::array<Frame, FRAMES> memory;

public:
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