#ifndef PAGE_TABLE_HPP
#define PAGE_TABLE_HPP

#include <array>

struct PageTableMap
{
    int frame_index = 0;
    bool present = false;
};

class PageTable
{
public:
    static constexpr int PAGES = 256;

private:
    std::array<PageTableMap, PAGES> data;

public:
    
    /**
     * @brief Adiciona uma entrada na tabela de paginas
     * @param frame_index Índice do quadro associado
     * @param present Indica se a página está presente na memória
     */
    void addPage(int frame_index, bool present);

    /**
     * @brief Obtém o quadro associado a uma página
     * @param page_number Número da página
     * @return Índice do quadro associado
     */
    int getPage(int page_number);
    
    /**
     * @brief Imprime o conteúdo da tabela de páginas
     */
    void printPageTable();
};

#endif