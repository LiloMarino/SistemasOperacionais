#include <iostream>
#include <fstream>
#include <string>
#include "binary.hpp"
#include "memory_manager.hpp"

int main(int argc, char const *argv[])
{
    std::ifstream backing_store("BACKING_STORE.bin", std::ios::binary);
    if (!backing_store)
    {
        std::cerr << "Erro ao abrir o arquivo BACKING_STORE.bin!" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream addresses("addresses.txt");
    if (!addresses)
    {
        std::cerr << "Erro ao abrir o arquivo addresses.txt!" << std::endl;
        return EXIT_FAILURE;
    }

    MemoryManager memory_manager(std::move(backing_store));

    // Inicia o gerenciamento de memória
    uint32_t address;
    while (addresses >> address)
    {
        uint16_t logical_address = binary::get_low_bits<16>(address);
        uint8_t page_number = binary::get_high_bits<8>(logical_address);
        uint8_t offset = binary::get_low_bits<8>(logical_address);
        auto [physical_address, content] = memory_manager.getContent(page_number, offset);
        std::cout << "Endereço Virtual: " << address << " Endereço Físico: " << physical_address << "  Conteúdo: " << content << std::endl;
    }

    return EXIT_SUCCESS;
}
