#include <DatabaseBuilder/DatabaseBuilder.hpp>

int main()
{
    const string APP_NAME("database-test");
    const string APP_VERSION("1.0");

    const string LIB_PATH("..\\lib\\");
    const string DATABASE_PATH("..\\lib\\lib.sqlite3");

    const char* ARGS_INCLUDE_PREFIX = "-I";
    const char* ARGS_INCLUDE_PATH   = "..\\lib\\include\\";
    const char* COMPILATION_ARGS[2] = { ARGS_INCLUDE_PREFIX, ARGS_INCLUDE_PATH };

    FolderBrowser folderBrowser;
    folderBrowser.clearFileList();
    folderBrowser.setFileTypeBrowser(FileType::SOURCE_FILE);
    folderBrowser.addIgnoreFilePath("..\\lib\\src\\TestPrimitives.cpp");
    folderBrowser.startFolderBrowse(LIB_PATH);

    Database database(DATABASE_PATH);

    DatabaseBuilder databaseBuilder(database, APP_NAME, APP_VERSION, folderBrowser, COMPILATION_ARGS, 2);
    databaseBuilder.buildDatabase();

    return EXIT_SUCCESS;
}

