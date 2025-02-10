#ifndef BINARY_HPP
#define BINARY_HPP

#include <fstream>
#include <bitset>
#include <iostream>
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

    /**
     * @brief Obtém os n bits menos significativos de um número.
     *
     * @tparam T Tipo de retorno desejado (ex: uint8_t, uint16_t, uint32_t).
     * @param num Número de entrada.
     * @param n Quantidade de bits a serem extraídos.
     * @return T Valor contendo os n bits menos significativos.
     */
    template <typename T>
    T get_low_bits(T num, uint32_t n)
    {
        return static_cast<T>(num & ((1U << n) - 1));
    }

    /**
     * @brief Obtém os n bits mais significativos de um número.
     *
     * @tparam T Tipo de retorno desejado (ex: uint8_t, uint16_t, uint32_t).
     * @param num Número de entrada.
     * @param n Quantidade de bits a serem extraídos.
     * @return T Valor contendo os n bits mais significativos.
     */
    template <typename T>
    T get_high_bits(T num, uint32_t n)
    {
        return static_cast<T>(num >> (sizeof(T) * 8 - n));
    }

    /**
     * @brief Imprime o número em formato binário.
     *
     * @param num Número a ser impresso.
     */
    template <typename T>
    void print_binary(T num)
    {
        std::cout << "0b" << std::bitset<sizeof(T) * 8>(num) << std::endl;
    }
}

#endif