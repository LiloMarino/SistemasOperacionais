#include <iostream>
#include <fstream>
#include <string>
#include "binary.hpp"

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

    uint32_t address;
    while(addresses >> address)
    {
        uint16_t logical_address = binary::get_low_bits<16>(address);
        uint8_t page_number = binary::get_high_bits<8>(logical_address);
        uint8_t offset = binary::get_low_bits<8>(logical_address);

        Page page = binary::readPage(page_number, backing_store);
    }

    return EXIT_SUCCESS;
}
