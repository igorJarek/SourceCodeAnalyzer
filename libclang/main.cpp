#include "UtilityFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
    processBeforeAll();

    recursiveFolderSearch(LIB_PATH);

    processAfterAll();

    system("pause");
    return EXIT_SUCCESS;
}
