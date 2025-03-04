#ifndef PAGE_HPP
#define PAGE_HPP

#include <array>

class Page
{
public:
    static constexpr int PAGE_SIZE = 256;

private:
    std::array<char, PAGE_SIZE> data;
    int page_number = -1;

public:
    /**
     * @brief Define o número da página
     * @param page_number Número da página
     */
    void setPageNumber(int page_number);

    /**
     * @brief Obtém uma referência os dados da página
     * @return Referência para os dados da página
     */
    std::array<char, PAGE_SIZE> &getData();

    /**
     * @brief Obtém um byte da página
     * @param offset Offset dentro da página
     * @return O byte na posição especificada
     */
    char getByte(int offset);

    /**
     * @brief Obtém o número da página
     * @return Número da página
     */
    int getPageNumber();

    /**
     * @brief Verifica se a página está vazia
     * @return Verdadeiro se a página estiver vazia, falso caso contrário
     */
    bool isEmpty();
};

/**
 * @brief Alias para representar um quadro (frame) na memória física.
 */
using Frame = Page;

#endif