#include "Html.h"

void HTMLBuilder::addTable(const string& contentTitle, vector<string> columnNames)
{
	DivDescriptor divDescriptor;
	divDescriptor.m_type = DivDescriptorType::DCT_TABLE;
	divDescriptor.m_containerHeader = contentTitle;
	divDescriptor.m_tableVecrIndex = m_tableContentVec.size();

	TableContent tableContent;
	tableContent.m_columnNames = columnNames;

	m_divDescriptorVec.push_back(divDescriptor);
	m_tableContentVec.push_back(tableContent);
}

void HTMLBuilder::addTableRow(vector<string> rowsContent)
{
	TableContent& tableContent = m_tableContentVec.back();
	tableContent.m_rows.push_back(rowsContent);
}
}

void HTMLBuilder::buildPage(string& pageContent)
{
	pageContent = INDEX_TEMPLATE;

	string titleKeyword		{ "<?title?>" };
	string fileNameKeyword	{ "<?fileName?>" };
	string filePathKeyword	{ "<?filePath?>" };
	string contentKeyword	{ "<?content?>" };

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
		string divContainer				{ CONTAINER_TEMPLATE };
		string containerHeaderKeyword	{ "<?containerHeader?>" };
		string containerBodyKeyword		{ "<?containerBody?>" };

		size_t containerBodyTabsCount	{ tabsCount + countTabs(divContainer, containerBodyKeyword) };

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
	const TableContent& tableContentVecElem = m_tableContentVec.at(divDescriptor.m_tableVecrIndex);

	string tableContent			{ TABLE_TEMPLATE };
	string tableBodyKeyword		{ "<?tableBody?>" };

	string tableColumnTrKeyword	{ "<?tableColumnTr?>" };
	string tableColumnThKeyword	{ "<?tableColumnTh?>" };
	string tableRowTrKeyword	{ "<?tableRowTr?>" };
	string tableRowTdKeyword	{ "<?tableRowTd?>" };

	size_t tableBodyTabsCount	{ tabsCount + countTabs(tableContent, tableBodyKeyword) };

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