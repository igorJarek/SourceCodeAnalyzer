#include <html/Html.h>

void HTMLBuilder::clear()
{
    m_indexTitle.clear();
    m_fileNameHeader.clear();
    m_filePathHeader.clear();

    m_divDescriptorVec.clear();

    m_tableContentMap.clear();
    m_treeContentMap.clear();
}

void HTMLBuilder::addTable(const string& contentTitle, const string& id, vector<string> columnNames)
{
    DivDescriptor divDescriptor;
    divDescriptor.m_type = DivDescriptorType::DCT_TABLE;
    divDescriptor.m_containerHeader = contentTitle;
    divDescriptor.m_id = id;

    TableContent tableContent;
    tableContent.m_columnNames = columnNames;

    m_divDescriptorVec.push_back(divDescriptor);
    m_tableContentMap.insert({ id, tableContent });
}

void HTMLBuilder::addTable(const string& contentTitle, const string& id, const OutputTree& outputTree)
{
    auto&         rootChildren = outputTree.getRoot()->m_children;
    uint32_t      treeHeight   = outputTree.getHeight();

    DivDescriptor divDescriptor;
    TableContent  tableContent;

    divDescriptor.m_type = DivDescriptorType::DCT_TABLE;
    divDescriptor.m_containerHeader = contentTitle;
    divDescriptor.m_id = id;

    vector<string> columnsVec(treeHeight);

    for(uint32_t index{0}; index < treeHeight; ++index)
        columnsVec.at(index) = std::to_string(index + 1);

    tableContent.m_columnNames = columnsVec;

    for(list<shared_ptr<OutputTreeNode>>::iterator iter = rootChildren.begin(); iter != rootChildren.end(); ++iter)
        addTableRowRecursive(0, treeHeight, tableContent, *iter);

    m_divDescriptorVec.push_back(divDescriptor);
    m_tableContentMap.insert({ id, tableContent });
}

void HTMLBuilder::addTableRow(const string& id, vector<string> rowsContent)
{
    TableContent& tableContent = m_tableContentMap.at(id);
    tableContent.m_rows.push_back(rowsContent);
}

void HTMLBuilder::addTableRows(const string& id, const OutputTree& outputTree)
{
    auto&         rootChildren = outputTree.getRoot()->m_children;
    uint32_t      treeHeight   = outputTree.getHeight();

    TableContent& tableContent = m_tableContentMap.at(id);

    for(list<shared_ptr<OutputTreeNode>>::iterator iter = rootChildren.begin(); iter != rootChildren.end(); ++iter)
        addTableRowRecursive(0, treeHeight, tableContent, *iter);
}

void HTMLBuilder::addTree(const string& contentTitle, const string& id)
{
    DivDescriptor divDescriptor;
    divDescriptor.m_type = DivDescriptorType::DCT_TREE;
    divDescriptor.m_containerHeader = contentTitle;
    divDescriptor.m_id = id;

    TreeContent treeContent;
    treeContent.m_root = std::make_shared<TreeNode>();

    m_divDescriptorVec.push_back(divDescriptor);
    m_treeContentMap.insert({id ,treeContent });
}

void HTMLBuilder::addTreeElement(const string& id, pair<uint32_t, string> treeElement)
{
    uint32_t& treeLevel = treeElement.first;
    string& str         = treeElement.second;

    TreeContent& treeContent = m_treeContentMap.at(id);
    shared_ptr<TreeNode> parentNode = treeContent.m_root;
    uint32_t currentLevel{ 0 };

    while (treeLevel > currentLevel)
    {
        parentNode = parentNode->m_children.back();
        ++currentLevel;
    }

    shared_ptr<TreeNode> newNode(new TreeNode(str));
    parentNode->m_children.push_back(newNode);
}

void HTMLBuilder::buildPage(string& pageContent)
{
    pageContent = INDEX_TEMPLATE;

    string titleKeyword     { "<?title?>" };
    string fileNameKeyword  { "<?fileName?>" };
    string filePathKeyword  { "<?filePath?>" };
    string contentKeyword   { "<?content?>" };

    replaceKeyword(pageContent, titleKeyword,	 m_indexTitle);
    replaceKeyword(pageContent, fileNameKeyword, m_fileNameHeader);
    replaceKeyword(pageContent, filePathKeyword, m_filePathHeader);

    string divContent;
    buildContent(divContent, countTabs(pageContent, contentKeyword));

    replaceKeyword(pageContent, contentKeyword, divContent);
}

void HTMLBuilder::buildContent(string& divContent, const size_t tabsCount)
{
    for (DivDescriptor& divDescriptor : m_divDescriptorVec)
    {
        string divContainer             { CONTAINER_TEMPLATE };
        string containerHeaderKeyword   { "<?containerHeader?>" };
        string containerBodyKeyword     { "<?containerBody?>" };

        size_t containerBodyTabsCount   { tabsCount + countTabs(divContainer, containerBodyKeyword) };

        replaceKeyword(divContainer, containerHeaderKeyword, divDescriptor.m_containerHeader);

        string divContainerContent;
        switch (divDescriptor.m_type)
        {
            case DivDescriptorType::DCT_TABLE:
                buildTable(divContainerContent, divDescriptor, containerBodyTabsCount);
                break;

            case DivDescriptorType::DCT_TREE:
                buildTree(divContainerContent, divDescriptor, containerBodyTabsCount);
                break;
        }

        replaceKeyword(divContainer, containerBodyKeyword, divContainerContent, true, tabsCount);
        
        divContent += divContainer;
    }
}

void HTMLBuilder::buildTable(string& divContainer, const DivDescriptor& divDescriptor, const size_t tabsCount)
{
    const TableContent& tableContentVecElem = m_tableContentMap.at(divDescriptor.m_id);

    string tableContent         { TABLE_TEMPLATE };
    string tableBodyKeyword     { "<?tableBody?>" };

    string tableColumnTrKeyword { "<?tableColumnTr?>" };
    string tableColumnThKeyword { "<?tableColumnTh?>" };
    string tableRowTrKeyword    { "<?tableRowTr?>" };
    string tableRowTdKeyword    { "<?tableRowTd?>" };

    size_t tableBodyTabsCount   { tabsCount + countTabs(tableContent, tableBodyKeyword) };

    // Columns
    string tableColumnsTr{ TABLE_COLUMN_TR_TEMPLATE };
    size_t tableColumnTrTabsCount{ countTabs(tableColumnsTr, tableColumnTrKeyword) };

    string tableColumnsThs;
    for (const string& columnName : tableContentVecElem.m_columnNames)
    {
        string tableColumnsTh{ TABLE_COLUMN_TH_TEMPLATE };
        replaceKeyword(tableColumnsTh, tableColumnThKeyword, columnName, true, tableBodyTabsCount + tableColumnTrTabsCount);
        tableColumnsThs += tableColumnsTh;
    }

    replaceKeyword(tableColumnsTr, tableColumnTrKeyword, tableColumnsThs, true, tableBodyTabsCount);

    // Rows
    string tableRowsTrs;
    for (const vector<string>& row : tableContentVecElem.m_rows)
    {
        string tableRowsTr{ TABLE_ROW_TR_TEMPLATE };
        size_t tableRowsTrTabsCount{ countTabs(tableRowsTr, tableRowTrKeyword) };

        string tableRowsTds;
        for (const string& rowName : row)
        {
            string tableRowsTd{ TABLE_ROW_TD_TEMPLATE };
            replaceKeyword(tableRowsTd, tableRowTdKeyword, rowName, true, tableBodyTabsCount + tableRowsTrTabsCount);

            tableRowsTds += tableRowsTd;
        }

        replaceKeyword(tableRowsTr, tableRowTrKeyword, tableRowsTds, true, tableBodyTabsCount);

        tableRowsTrs += tableRowsTr;
    }

    replaceKeyword(tableContent, tableBodyKeyword, tableColumnsTr + tableRowsTrs, true, tabsCount);

    divContainer += tableContent;
}

void HTMLBuilder::buildTree(string& divContainer, const DivDescriptor& divDescriptor, const size_t tabsCount)
{
    const TreeContent& TreeContentVecElem = m_treeContentMap.at(divDescriptor.m_id);

    string treeRoot{ TREE_ROOT_UL_TEMPLATE };
    string treeRootKeyword{ "<?rootBody?>" };

    size_t treeRootTabsCount{ tabsCount + countTabs(treeRoot, treeRootKeyword) };

    string rootContent;
    iterateTree(TreeContentVecElem.m_root, rootContent, treeRootTabsCount);

    replaceKeyword(treeRoot, treeRootKeyword, rootContent, true, tabsCount);

    divContainer += treeRoot;
}

void HTMLBuilder::addTableRowRecursive(uint32_t level, uint32_t treeLevel, TableContent& tableContent, shared_ptr<OutputTreeNode> node)
{
    vector<string> row(treeLevel, " ");

    row[level] = node->m_string;

    tableContent.m_rows.push_back(row);

    for(list<shared_ptr<OutputTreeNode>>::iterator iter = node->m_children.begin(); iter != node->m_children.end(); ++iter)
        addTableRowRecursive(level + 1, treeLevel, tableContent, *iter);
}

void HTMLBuilder::iterateTree(shared_ptr<TreeNode> parent, string& rootContent, const size_t tabsCount)
{
    string treeLiBodyKeyword    { "<?liBody?>" };
    string treeUlLiHeaderKeyword{ "<?ulluHeader?>" };
    string treeUlLiBodyKeyword  { "<?ulliBody?>" };

    for (shared_ptr<TreeNode> node : parent->m_children)
    {
        if (node->m_children.size())
        {
            string treeUlLi{ TREE_UL_LI_TEMPLATE };
            replaceKeyword(treeUlLi, treeUlLiHeaderKeyword, node->m_data);
            size_t treeUlLiTabsCount = tabsCount + countTabs(treeUlLi, treeUlLiBodyKeyword);

            string treeUlLiChildren;
            iterateTree(node, treeUlLiChildren, treeUlLiTabsCount);

            replaceKeyword(treeUlLi, treeUlLiBodyKeyword, treeUlLiChildren, true, tabsCount);

            rootContent += treeUlLi;
        }
        else
        {
            string treeLi{ TREE_LI_TEMPLATE };
            replaceKeyword(treeLi, treeLiBodyKeyword, node->m_data, true, tabsCount);
            rootContent += treeLi;
        }
    }
}

bool HTMLBuilder::saveFile(const string& path)
{
    fstream stream;
    stream.open(path, std::fstream::out | std::fstream::trunc);
    if (stream.is_open())
    {
        string content;
        buildPage(content);

        stream << content;
        stream.flush();
        stream.close();
        return true;
    }
    else
        return false;
}

void HTMLBuilder::replaceKeyword(string& source, const string& keyword, const string& newContent, bool move /* = false */, size_t moveOffset /* = 0 */)
{
    if(move)
        addTabsInTemplate(source, moveOffset);

    size_t pos = source.find(keyword);
    if (pos != std::string::npos)
    {
        source.erase(pos, keyword.size());

        if (newContent.empty())
            source.insert(pos, "--NULL--");
        else
            source.insert(pos, newContent);
    }
}

size_t HTMLBuilder::countTabs(const string& source, const string& keyword)
{
    size_t tabsCount{0};

    size_t pos = source.find(keyword);
    if (pos != std::string::npos)
    {
        for (size_t index{ pos - 1 }; index >= 0; --index)
        {
            char c{ source.at(index) };
            if (c == '\n' || c != '\t')
                break;
            else
                ++tabsCount;
        }
    }

    return tabsCount;
}

void HTMLBuilder::addTabsInTemplate(string& source, const size_t tabsCount)
{
    string tabsStr(tabsCount, '\t');

    // \n
    size_t pos = source.find('\n');
    while (pos != std::string::npos)
    {
        source.insert(pos + 1, tabsStr);
        pos = source.find('\n', pos + 1);
    }
}