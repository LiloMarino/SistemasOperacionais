#include <iostream>
#include <fstream>
#include <string>

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
    
    std::string linha;
    while (std::getline(addresses, linha))
    {
        int address = std::stoi(linha);
    }
}
