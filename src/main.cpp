#include <iostream>
#include <fstream>

int main(int argc, char const *argv[])
{
    std::ifstream backing_store("BACKING_STORE.bin", std::ios::binary);
    if (!backing_store) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }

    
}
