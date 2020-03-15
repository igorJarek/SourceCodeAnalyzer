#include <iostream>
#include "Html.h"

int main()
{
    HTMLBuilder htmlBuilder;

    htmlBuilder.setIndexTitle("main.cpp");
    htmlBuilder.setFileNameHeader("main.cpp");
    htmlBuilder.setFilePathHeader("libclangAPITest\\testLib\\main.cpp");

    htmlBuilder.addTable("1. File manipulation routines", {"ID", "Function name", "Value type", "Value"});
    htmlBuilder.addTableRow({ "1", "clang_getFileName", "return", "C:\\Users\\Igor\\Desktop\\libclangAPITest\\testLib\\main.cpp" });
    htmlBuilder.addTableRow({ "2", "clang_getFileTime", "return", "Thu Feb 20 00:22:35 2020" });

    htmlBuilder.saveFile("main.cpp.html");

    return EXIT_SUCCESS;
}
