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

    htmlBuilder.addTree("2. AST");

    htmlBuilder.addTreeElement({ 0, "1" });
    htmlBuilder.addTreeElement({ 0, "2" });
    htmlBuilder.addTreeElement({ 0, "3" });
        htmlBuilder.addTreeElement({ 1, "4" });
        htmlBuilder.addTreeElement({ 1, "5" });
        htmlBuilder.addTreeElement({ 1, "6" });
            htmlBuilder.addTreeElement({ 2, "7" });
                htmlBuilder.addTreeElement({ 3, "8" });
    htmlBuilder.addTreeElement({ 0, "9" });
        htmlBuilder.addTreeElement({ 1, "10" });
            htmlBuilder.addTreeElement({ 2, "11" });
            htmlBuilder.addTreeElement({ 2, "12" });

    htmlBuilder.saveFile("main.cpp.html");

    return EXIT_SUCCESS;
}
