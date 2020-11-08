#pragma once

#include <clang-c/Index.h>
#include <LibClangStruct2Str/LibClangStruct2Str.h>

#include <list>
#include <string>
#include <memory>

using std::list;
using std::string;

using std::shared_ptr;

struct OutputTreeNode
{
    list<shared_ptr<OutputTreeNode>>    m_children;
    string                              m_string;
};

class OutputTree
{
public:
    OutputTree();
    ~OutputTree();

    OutputTree(const OutputTree&)               = delete;
    OutputTree(OutputTree&&) noexcept           = delete;
    OutputTree& operator=(OutputTree&)          = delete;
    OutputTree& operator=(const OutputTree& other);
    OutputTree& operator+=(const OutputTree& other);

public:
    const shared_ptr<OutputTreeNode>& getRoot() const { return m_rootPtr; }

public:
    void                              addString(uint32_t level, const string&  str);
    void                              addString(uint32_t level, const string&& str);

    template<typename T>
    void                              addString(uint32_t level, const string&& str, const T& value)
    {
        shared_ptr<OutputTreeNode> node = allocateNode(level);

        node->m_string = str + std::to_string(value);
    }

    template<typename T>
    void                              addValue(uint32_t level, const T& value)
    {
        shared_ptr<OutputTreeNode> node = allocateNode(level);

        node->m_string = std::to_string(value);
    }

    void                              addNewLine               (uint32_t level);

    void                              addCXStringSet           (uint32_t level, const string&& str, CXStringSet*                  stringSet);
    void                              addCXSourceLocation      (uint32_t level, const string&& str, const CXSourceLocation&       sourceLocation);
    void                              addCXSourceRange         (uint32_t level, const string&& str, const CXSourceRange&          sourceRange);
    void                              addCXTUResourceUsage     (uint32_t level, const string&& str, const CXTUResourceUsage&      TUResourceUsage);
    void                              addCXVersion             (uint32_t level, const string&& str, const CXVersion&              version);
    void                              addCXPlatformAvailability(uint32_t level, const string&& str, const CXPlatformAvailability& platformAvailability);
    void                              addCXPrintingPolicy      (uint32_t level, const string&& str, const CXPrintingPolicy&       printingPolicy);
    void                              addCXFileInfo            (uint32_t level, const string&& str, const CXFile&                 file, const CXTranslationUnit& translationUnit);

    uint64_t                          getNodesCount() const { return m_nodesCount; }
    uint32_t                          getHeight() const { return m_treeHeight; }

    bool                              saveToFile(const string& path);

private:
    void                              saveNode(std::fstream& stream, const std::string& prefix, shared_ptr<OutputTreeNode> node);
    shared_ptr<OutputTreeNode>        allocateNode(uint32_t level);

private:
    shared_ptr<OutputTreeNode>        m_rootPtr;
    uint64_t                          m_nodesCount = 0;
    uint32_t                          m_treeHeight = 0;
};
