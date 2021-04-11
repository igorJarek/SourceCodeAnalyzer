#include "FolderBrowser/FolderBrowser.h"

FolderBrowser::FolderBrowser()
{
    
}

FolderBrowser::~FolderBrowser()
{
    
}

bool FolderBrowser::isHeaderFile(const string& extension)
{
    if (extension.compare(".h") == 0 || extension.compare(".hpp") == 0)
        return true;
    else
        return false;
}

bool FolderBrowser::isSourceFile(const string& extension)
{
    if (extension.compare(".c") == 0 || extension.compare(".cpp") == 0)
        return true;
    else
        return false;
}

void FolderBrowser::addIgnoreFilePath(const string& filePath)
{
    m_ignoredFilesSet.insert(filePath);
}

void FolderBrowser::addIgnoreDirPath(const string& dirPath)
{
    m_ignoredDirsSet.insert(dirPath);
}

void FolderBrowser::startFolderBrowse(const string& folderPath)
{
    fs::path folderPathFS(folderPath);

    if (fs::exists(folderPathFS) && fs::is_directory(folderPathFS))
    {
        for (const fs::directory_entry& dirEntry : fs::directory_iterator(folderPathFS))
        {
            const fs::file_status fileStatus = dirEntry.status();
            const fs::path&       path       = dirEntry.path();

            if (fs::is_directory(fileStatus))
            {
                const string dirPath = path.string();

                if(m_ignoredDirsSet.find(dirPath) == m_ignoredDirsSet.end())
                    startFolderBrowse(dirPath);
            }
            else if (fs::is_regular_file(fileStatus))
            {
                const string fileExtension = path.extension().string();

                if(isSourceFile(fileExtension))
                {
                    string filePath = path.string();

                    if(m_ignoredFilesSet.find(filePath) == m_ignoredFilesSet.end())
                        m_sourceFilesList.push_back(filePath);
                }
                else if(isHeaderFile(fileExtension))
                {
                    string filePath = path.string();

                    if(m_ignoredFilesSet.find(filePath) == m_ignoredFilesSet.end())
                        m_headerFilesList.push_back(filePath);
                }
            }
        }
    }
}
