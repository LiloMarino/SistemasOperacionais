#ifndef BINARY_HPP
#define BINARY_HPP

#include <fstream>
#include "page.hpp"

namespace binary
{
    /**
     * @brief Lê uma página no arquivo binário
     * @param page_number Número da página
     * @param file Arquivo a ser lido
     * @return Retorna a página
     */
    Page readPage(int page_number, std::ifstream &file);
}

#endif