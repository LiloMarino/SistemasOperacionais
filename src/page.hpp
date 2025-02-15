#ifndef PAGE_HPP
#define PAGE_HPP

#include <array>

class Page
{
public:
    static constexpr int PAGE_SIZE = 256;

private:
    std::array<char, PAGE_SIZE> data;
    int page_number;

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
};

/**
 * @brief Alias para representar um quadro (frame) na memória física.
 */
using Frame = Page;

#endif