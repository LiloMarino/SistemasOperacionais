#ifndef BINARY_HPP
#define BINARY_HPP

#include <fstream>
#include <bitset>
#include <iostream>
#include "page.hpp"

namespace binary
{
    /**
     * @brief Retorna o menor tipo inteiro unsigned que cabe N bits
     * @tparam N Número de bits
     */
    template <size_t N>
    using smallest_uint_t =
        std::conditional_t<
            (N <= 8), uint8_t,
            std::conditional_t<
                (N <= 16), uint16_t,
                std::conditional_t<
                    (N <= 32), uint32_t,
                    uint64_t>>>;

    /**
     * @brief Lê uma página no arquivo binário
     * @param page_number Número da página
     * @param file Arquivo a ser lido
     * @return Retorna a página
     */
    Page readPage(int page_number, std::ifstream &file);
    
    /**
     * @brief Obtém os n bits mais significativos de um número.
     * @tparam T Tipo original de num
     * @tparam N Número de bits a serem obtidos
     * @param num Número a ser processado
     * @return Retorna o número com os n bits mais significativos com o 
     * tipo mais compacto possível
     */
    template <size_t N, typename T>
    constexpr auto get_high_bits(T num) -> smallest_uint_t<N> {
        static_assert(N <= sizeof(T) * 8, "N não pode ser maior que o número de bits do tipo original.");
        return static_cast<smallest_uint_t<N>>(num >> (sizeof(T) * 8 - N));
    }
    
    /**
     * @brief Obtém os n bits menos significativos de um número.
     * @tparam T Tipo original de num
     * @tparam N Número de bits a serem obtidos
     * @param num Número a ser processado
     * @return Retorna o número com os n bits menos significativos com o 
     * tipo mais compacto possível
     */
    template <size_t N, typename T>
    constexpr auto get_low_bits(T num) -> smallest_uint_t<N> {
        static_assert(N <= sizeof(T) * 8, "N não pode ser maior que o número de bits do tipo original.");
        return static_cast<smallest_uint_t<N>>(num & ((T(1) << N) - 1));
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