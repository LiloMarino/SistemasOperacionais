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
    unsigned int page_fault = 0;

public:
    
    /**
     * @brief Adiciona uma entrada na tabela de paginas
     * @param page_number Número da página
     * @param frame_index Índice do quadro associado
     */
    void addPage(int page_number, int frame_index);

    /**
     * @brief Remove uma entrada da tabela de páginas
     * @param page_number Número da página
     */
    void removePage(int page_number);

    /**
     * @brief Obtém o quadro associado a uma página
     * @param page_number Número da página
     * @return Índice do quadro associado
     */
    int getPage(int page_number);

    /**
     * @brief Obtém o número de falta de páginas
     * @return Número de falta de páginas
     */
    int getPageFault() const; 
    
    /**
     * @brief Imprime o conteúdo da tabela de páginas
     */
    void printPageTable();
};

#endif