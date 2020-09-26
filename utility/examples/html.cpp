#include "Html.h"

int main()
{
    HTMLBuilder htmlBuilder;

    htmlBuilder.setIndexTitle("main.cpp");
    htmlBuilder.setFileNameHeader("main.cpp");
    htmlBuilder.setFilePathHeader("lib\\main.cpp");

    string tableID{ "FMR" };
    string treeID{ "AST" };

    htmlBuilder.addTable("1. File manipulation routines", tableID, {"ID", "Function name", "Value type", "Value"});
    htmlBuilder.addTableRow(tableID, { "1", "clang_getFileName", "return", "C:\\Users\\Igor\\Desktop\\libclangAPITest\\testLib\\main.cpp" });
    htmlBuilder.addTableRow(tableID, { "2", "clang_getFileTime", "return", "Thu Feb 20 00:22:35 2020" });

    htmlBuilder.addTree("2. AST", treeID);

    htmlBuilder.addTreeElement(treeID, { 0, "1" });
    htmlBuilder.addTreeElement(treeID, { 0, "2" });
    htmlBuilder.addTreeElement(treeID, { 0, "3" });
        htmlBuilder.addTreeElement(treeID, { 1, "4" });
        htmlBuilder.addTreeElement(treeID, { 1, "5" });
        htmlBuilder.addTreeElement(treeID, { 1, "6" });
            htmlBuilder.addTreeElement(treeID, { 2, "7" });
                htmlBuilder.addTreeElement(treeID, { 3, "8" });
    htmlBuilder.addTreeElement(treeID, { 0, "9" });
        htmlBuilder.addTreeElement(treeID, { 1, "10" });
            htmlBuilder.addTreeElement(treeID, { 2, "11" });
            htmlBuilder.addTreeElement(treeID, { 2, "12" });

    htmlBuilder.saveFile("main.cpp.html");

    return EXIT_SUCCESS;
}
