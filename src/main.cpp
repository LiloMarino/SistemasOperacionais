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
        return 1;
    }

    std::ifstream addresses("addresses.txt");
    if (!addresses)
    {
        std::cerr << "Erro ao abrir o arquivo addresses.txt!" << std::endl;
        return 1;
    }

    uint32_t address;
    addresses >> address;

    binary::print_binary(address);
    binary::print_binary(binary::get_low_bits<16>(address));
    binary::print_binary(binary::get_low_bits<8>(binary::get_low_bits<16>(address)));
    binary::print_binary(binary::get_high_bits<8>(binary::get_low_bits<16>(address)));
}
