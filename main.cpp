#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream sourceFile("source.html", std::ios::binary);
    std::ofstream destFile("dest.html", std::ios::binary);

    // Verifica se os arquivos foram abertos
    if (!sourceFile.is_open() || !destFile.is_open()) {
        std::cerr << "Erro ao abrir os arquivos!" << std::endl;
        return 1;
    }

    // Copia o conteúdo do arquivo de origem para o arquivo de destino em binário
    destFile << sourceFile.rdbuf();
    std::cout << "Cópia concluída com sucesso!" << std::endl;

    sourceFile.close();
    destFile.close();

    return 0;
}