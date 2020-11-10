#pragma once

#include <filesystem>
#include <string>
#include <list>
#include <set>

namespace fs = std::filesystem;
using std::string;
using std::list;
using std::set;

enum FileType : uint8_t
{
    SOURCE_FILE             = (1 << 0),
    HEADER_FILE             = (1 << 1),
    SOURCE_AND_HEADER_FILE  = SOURCE_FILE | HEADER_FILE
};

class FolderBrowser
{
public:
    FolderBrowser();
    ~FolderBrowser();

public:
    void                clearFileList()                                     { m_filesList.clear(); }
    void                setFileTypeBrowser(uint8_t fileType);
    void                addIgnoreFilePath(const string& filePath);
    void                startFolderBrowse(const string& folderPath);

    const list<string>& getFileList() const { return m_filesList; }
    size_t              getFileCount() const                                { return m_filesList.size(); }

protected:
    bool                isHeaderFile(const string& extension);
    bool                isSourceFile(const string& extension);

protected:
    list<string>        m_filesList;
    set<string>         m_ignoredFilesSet;

    uint8_t             m_fileTypeOptions = 0;
};
