#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <fstream>
#include "tlb.hpp"
#include "physical_memory.hpp"
#include "page_table.hpp"

class MemoryManager
{
private:
    std::ifstream backing_store;
    TLB tlb;
    PageTable page_table;
    PhysicalMemory physical_memory;

public:
    /**
     * @brief Construtor de MemoryManager
     * @param backing_store Arquivo de backing store
     */
    MemoryManager(std::ifstream &&backing_store);

    /**
     * @brief Obtém o conteúdo de um endereço da memória
     * @param page_number Número da página
     * @param offset Offset dentro da página
     * @return O conteúdo da memória
     */
    char getContent(int page_number, int offset);
};

#endif