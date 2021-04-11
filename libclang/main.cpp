#include "UtilityFunctions.h"
#include "ArgsParser.h"

uint32_t g_appOptions;

int main(int argc, char* argv[])
{
    ArgsParser args(argc, argv);

    if(args.isCmdOptionExists("-html"))
        g_appOptions |= HTML_ENABLED;

    if(args.isCmdOptionExists("-cAll"))
        g_appOptions = 0x3FFFFE;
    else
    {
        for(int categoryNum = 1; categoryNum <= 21; ++categoryNum)
            if(args.isCmdOptionExists(std::string("-c") + std::to_string(categoryNum)))
                g_appOptions |= (1 << categoryNum);
    }

    processBeforeAll();

    recursiveFolderSearch(LIB_PATH);

    processAfterAll();

    system("pause");
    return EXIT_SUCCESS;
}
