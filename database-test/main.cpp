#include "DatabaseBuilder/DatabaseBuilder.h"

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
    folderBrowser.addIgnoreFilePath("..\\lib\\src\\TestPrimitives.cpp");
    folderBrowser.addIgnoreFilePath("..\\lib\\include\\TestPrimitives.h");
    folderBrowser.startFolderBrowse(LIB_PATH);

    Database database;
    DatabaseBuilder databaseBuilder(database, APP_NAME, APP_VERSION, folderBrowser, COMPILATION_ARGS, 2);
    databaseBuilder.buildDatabase
    (
        [](const string& filePath, size_t fileIndex, size_t fileCount) -> void
        {
            cout << fileIndex + 1 << '/' << fileCount << " -> " << filePath << endl;
        }
    );

    QueryResults queryResults;
    DatabaseQueryErrMsg queryErrMsg = database.recvQuery("SELECT * FROM [..\\file_list]", queryResults);
    if(database.isNotOK())
        cout << "Recv Error : " << queryErrMsg << endl;

    for(std::vector<string>& row : queryResults.rows)
    {
        string& idStr = row[0];
        string& fileNameStr = row[1];

        cout << fileNameStr << endl;
    }

    database.saveAsDatabase
    (
        DATABASE_PATH,
        [](double currentPercent) -> void
        {
            cout << currentPercent << endl;
        }
    );

    if(database.isNotOK())
        cout << "Database hasn't saved correctly." << endl;

    return EXIT_SUCCESS;
}

