#include "binary.hpp"
#include "page.hpp"

Page binary::readPage(int page_number, std::ifstream &file)
{
    Page page;
    page.setPageNumber(page_number);
    std::streampos position = Page::PAGE_SIZE * page_number;
    file.seekg(position);
    file.read(page.getData().data(), Page::PAGE_SIZE);
    return page;
}
