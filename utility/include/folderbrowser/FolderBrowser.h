#pragma once

#include <filesystem>
#include <string>
#include <list>
#include <set>

namespace fs = std::filesystem;
using std::string;
using std::list;
using std::set;

class FolderBrowser
{
public:
    FolderBrowser();
    ~FolderBrowser();

public:
    void                startFolderBrowse(const string& folderPath);

    void                clearLists()
    { 
        m_sourceFilesList.clear(); 
        m_headerFilesList.clear(); 
    }

    void                addIgnoreFilePath(const string& filePath);
    void                addIgnoreDirPath(const string& dirPath);

    const list<string>& getSourceFileList()  const { return m_sourceFilesList; }
    size_t              getSourceFileCount() const { return m_sourceFilesList.size(); }

    const list<string>& getHeaderFileList()  const { return m_headerFilesList; }
    size_t              getHeaderFileCount() const { return m_headerFilesList.size(); }

protected:
    bool                isHeaderFile(const string& extension);
    bool                isSourceFile(const string& extension);

protected:
    list<string>        m_sourceFilesList;
    list<string>        m_headerFilesList;

    set<string>         m_ignoredFilesSet;
    set<string>         m_ignoredDirsSet;
};
