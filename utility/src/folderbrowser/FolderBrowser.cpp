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

void FolderBrowser::setFileTypeBrowser(uint8_t fileType)
{
    m_fileTypeOptions = fileType;
}

void FolderBrowser::addIgnoreFilePath(const string& filePath)
{
    m_ignoredFilesSet.insert(filePath);
}

void FolderBrowser::startFolderBrowse(const string& folderPath)
{
    fs::path path(folderPath);

    if (fs::exists(path) && fs::is_directory(path))
    {
        for (const fs::directory_entry& dirEntry : fs::directory_iterator(path))
        {
            const fs::file_status fileStatus = dirEntry.status();
            const fs::path&       path       = dirEntry.path();
            const fs::path&       filename   = path.filename();

            if (fs::is_directory(fileStatus))
                startFolderBrowse(path.string());
            else if (fs::is_regular_file(fileStatus))
            {
                const string& fileExtension = path.extension().string();

                if(isSourceFile(fileExtension))
                {
                    if(m_fileTypeOptions & SOURCE_FILE)
                    {
                        string filePath = path.string();

                        if(m_ignoredFilesSet.find(filePath) == m_ignoredFilesSet.end())
                            m_filesList.push_back(filePath);
                    }
                }
                else if(isHeaderFile(fileExtension))
                {
                    if(m_fileTypeOptions & HEADER_FILE)
                    {
                        string filePath = path.string();

                        if(m_ignoredFilesSet.find(filePath) == m_ignoredFilesSet.end())
                            m_filesList.push_back(filePath);
                    }
                }
            }
        }
    }
}
