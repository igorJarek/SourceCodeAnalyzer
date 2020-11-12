#pragma once

#include "HtmlTemplates.h"
#include "OutputTree/OutputTree.h"

#include <iostream>

#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <map>

using std::fstream;
using std::string;
using std::vector;
using std::pair;
using std::map;

enum class DivDescriptorType
{
    DCT_TABLE,
    DCT_TREE
};

struct DivDescriptor
{
    DivDescriptorType m_type;
    string m_containerHeader;
    string m_id;
};

struct TableContent
{
    vector<string> m_columnNames;
    vector<vector<string>> m_rows;
};

struct TreeNode
{
    TreeNode() = default;

    TreeNode(string data) : m_data(data)
    {

    }

    string m_data;
    
    list<shared_ptr<TreeNode>> m_children;
};

struct TreeContent
{
    shared_ptr<TreeNode> m_root;
};

class HTMLBuilder
{
public:
    HTMLBuilder() {}
    ~HTMLBuilder() {}

    HTMLBuilder(const HTMLBuilder&)             = delete;
    HTMLBuilder(HTMLBuilder&&) noexcept         = delete;
    HTMLBuilder& operator=(const HTMLBuilder&)  = delete;
    HTMLBuilder& operator=(HTMLBuilder&)        = delete;

public:
    void clear();

    void setIndexTitle(const string& title)         { m_indexTitle = title; }
    void setFileNameHeader(const string& fileName)  { m_fileNameHeader = fileName; }
    void setFilePathHeader(const string& filePath)  { m_filePathHeader = filePath; }

    void addTable(const string& contentTitle, const string& id, vector<string> columnNames);
    void addTable(const string& contentTitle, const string& id, const OutputTree& outputTree);
    void addTableRow(const string& id, vector<string> rowsContent);
    void addTableRows(const string& id, const OutputTree& outputTree);

    void addTree(const string& contentTitle, const string& id);
    void addTreeElement(const string& id, pair<uint32_t, string> treeElement);

    bool saveFile(const string& path);

private:
    void buildPage(string& pageContent);
    void buildContent(string& divContent, const size_t tabsCount);

    void buildTable(string& divContainer, const DivDescriptor& divDescriptor, const size_t tabsCount);
    void buildTree(string& divContainer, const DivDescriptor& divDescriptor, const size_t tabsCount);

    void addTableRowRecursive(uint32_t& nodeCount, uint32_t level, uint32_t treeLevel, TableContent& tableContent, shared_ptr<OutputTreeNode> node);

    void iterateTree(shared_ptr<TreeNode> node, string& rootContent, const size_t tabsCount);

    void replaceKeyword(string& source, const string& keyword, const string& newContent, bool move = false, size_t moveOffset = 0);

    size_t countTabs(const string& source, const string& keyword);
    void addTabsInTemplate(string& source, const size_t tabsCount);

private:
    string m_indexTitle;
    string m_fileNameHeader;
    string m_filePathHeader;

    vector<DivDescriptor>       m_divDescriptorVec;

    map<string, TableContent>   m_tableContentMap;
    map<string, TreeContent>    m_treeContentMap;
};