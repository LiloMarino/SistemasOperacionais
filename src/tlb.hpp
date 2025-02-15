#ifndef TLB_HPP
#define TLB_HPP

#include <array>

struct TLBMap
{
    int page_number;
    int frame_index;
};

class TLB
{
public:
    static constexpr int TLB_SIZE = 16;

private:
    std::array<TLBMap, TLB_SIZE> data;

public:
    /**
     * @brief Adiciona uma entrada na TLB
     * @param page_number Número da página
     * @param frame_index Índice do quadro associado
     */
    void addPage(int page_number, int frame_index);

    /**
     * @brief Obtém o quadro associado a uma página
     * @param page_number Número da página
     * @return Índice do quadro associado
     */
    int getFrame(int page_number);

    /**
     * @brief Imprime o conteúdo da TLB
     */
    void printTLB();
};

#endif