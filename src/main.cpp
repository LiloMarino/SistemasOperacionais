#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
#include "binary.hpp"
#include "memory_manager.hpp"

int main(int argc, char const *argv[])
{
    // Recebe os argumentos
    if (argc != 4)
    {
        std::cerr << "Uso incorreto! A sintaxe correta é:" << std::endl;
        std::cerr << "<executável> address.txt [Quadros] [Alg Subst Página]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string address_file = argv[1];
    std::ifstream addresses(address_file);
    if (!addresses)
    {
        std::cerr << "Erro ao abrir o arquivo: " << address_file << std::endl;
        return EXIT_FAILURE;
    }

    int num_frames = std::stoi(argv[2]);
    if (num_frames <= 0 || (num_frames & (num_frames - 1)) != 0)
    {
        std::cerr << "O número de quadros deve ser uma potência de 2!" << std::endl;
        return EXIT_FAILURE;
    }

    std::string replacement_algorithm = argv[3];
    ReplacementPolicy replacement_policy;
    if (replacement_algorithm == "FIFO")
    {
        replacement_policy = fifo_policy;
    }
    else if (replacement_algorithm == "LRU")
    {
        replacement_policy = lru_policy;
    }
    else
    {
        std::cerr << "Erro: O algoritmo de substituição deve ser FIFO ou LRU." << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream backing_store("BACKING_STORE.bin", std::ios::binary);
    if (!backing_store)
    {
        std::cerr << "Erro ao abrir o arquivo BACKING_STORE.bin!" << std::endl;
        return EXIT_FAILURE;
    }

    // Inicia o gerenciamento de memória
    MemoryManager memory_manager(std::move(backing_store), replacement_policy, num_frames);
    std::string line;
    while (std::getline(addresses, line))
    {
        if (!line.empty() && std::isdigit(line[0]))
        {
            // É um endereço então processa
            uint32_t address = std::stoul(line);
            uint16_t logical_address = binary::get_low_bits<16>(address);
            uint8_t page_number = binary::get_high_bits<8>(logical_address);
            uint8_t offset = binary::get_low_bits<8>(logical_address);
            auto [physical_address, content] = memory_manager.getContent(page_number, offset);
            std::cout << "Endereço Virtual: " << std::setw(6) << address
                      << " Endereço Físico: " << std::setw(6) << physical_address
                      << " Conteúdo: " << std::right << static_cast<int>(content) << std::endl;
        }
        else if (line == "PageTable")
        {
            memory_manager.printPageTable();
        }
        else if (line == "TLB")
        {
            memory_manager.printTLB();
        }
        else
        {
            std::cerr << "Comando desconhecido ignorado: " << line << std::endl;
        }
    }
    memory_manager.getSummary();

    return EXIT_SUCCESS;
}
