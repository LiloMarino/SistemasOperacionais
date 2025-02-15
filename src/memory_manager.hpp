#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <fstream>
#include <tuple>
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
     * @param policy Política de substituição
     * @param num_frames Número de quadros
     */
    MemoryManager(std::ifstream &&backing_store, ReplacementPolicy policy, int num_frames);

    /**
     * @brief Obtém o conteúdo de um endereço da memória
     * @param page_number Número da página
     * @param offset Offset dentro da página
     * @return O endereço físico e seu conteúdo
     */
    std::tuple<int, char> getContent(int page_number, int offset);
};

#endif