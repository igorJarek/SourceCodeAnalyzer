#include <iostream>
#include "Html.h"

int main()
{
    HTMLBuilder htmlBuilder;
    htmlBuilder.setIndexTitle("main.cpp");
    htmlBuilder.setFileNameHeader("main.cpp");
    htmlBuilder.setFilePathHeader("libclangAPITest\\testLib\\main.cpp");

    htmlBuilder.saveFile("main.cpp.html");

    return EXIT_SUCCESS;
}
