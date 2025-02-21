#include "memory_manager.hpp"
#include "binary.hpp"

MemoryManager::MemoryManager(std::ifstream &&backing_store, ReplacementPolicy policy, int num_frames)
    : backing_store(std::move(backing_store)), tlb(policy), physical_memory(num_frames, policy)
{
    physical_memory.setPageRemoveCallback(
        [this](int page_number)
        {
            page_table.removePage(page_number);
        });
}

std::tuple<int, char> MemoryManager::getContent(int page_number, int offset)
{
    address_accesses++;
    int physical_address = -1;
    char content = '\0';

    // Consulta a TLB
    int frame_index = tlb.getFrame(page_number);
    if (frame_index != -1)
    {
        // Encontrou na TLB
        physical_address = frame_index * Page::PAGE_SIZE + offset;
        content = physical_memory.getFrame(frame_index).getByte(offset);
    }
    else
    {
        // Não encontrou na TLB (TLB miss)
        frame_index = page_table.getPage(page_number);
        if (frame_index != -1)
        {
            // Encontrou na tabela de páginas
            tlb.addPage(page_number, frame_index);
            physical_address = frame_index * Page::PAGE_SIZE + offset;
            content = physical_memory.getFrame(frame_index).getByte(offset);
        }
        else
        {
            // Não encontrou na tabela de páginas (Page fault)
            Page page = binary::readPage(page_number, backing_store);
            frame_index = physical_memory.addPage(std::move(page));
            page_table.addPage(page_number, frame_index);
            tlb.addPage(page_number, frame_index);
            physical_address = frame_index * Page::PAGE_SIZE + offset;
            content = physical_memory.getFrame(frame_index).getByte(offset);
        }
    }

    return {physical_address, content};
}

void MemoryManager::printPageTable()
{
    page_table.printPageTable();
}

void MemoryManager::printTLB()
{
    tlb.printTLB();
}

void MemoryManager::getSummary()
{
    std::cout << "=== Resumo das estatísticas ===" << std::endl;
    std::cout << "Acessos de memória: " << address_accesses << std::endl;
    std::cout << "TLB misses: " << tlb.getTLBMiss() << std::endl;
    std::cout << "Page faults: " << page_table.getPageFault() << std::endl;
    std::cout << "TLB hit rate: " << (static_cast<double>(address_accesses - tlb.getTLBMiss()) / address_accesses) * 100 << "% " << std::endl;
    std::cout << "Page fault rate: " << (static_cast<double>(page_table.getPageFault()) / address_accesses) * 100 << "% " << std::endl;
}
