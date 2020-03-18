#pragma once

#include <iostream>

#include <string>
#include <fstream>
#include <initializer_list>
#include <vector>

using namespace std;

enum class DivDescriptorType
{
	DCT_TABLE,
	DCT_TREE
};

struct DivDescriptor
{
	DivDescriptorType type;
	string containerHeader;
	size_t vectorIndex;
};

struct TableContent
{
	vector<string> columnNames;
	vector<vector<string>> rows;
};

struct TreeContent
{

};

class HTMLBuilder
{
public:
	HTMLBuilder() {}
	~HTMLBuilder() {}

	HTMLBuilder(const HTMLBuilder&)				= delete;
	HTMLBuilder(HTMLBuilder&&) noexcept			= delete;
	HTMLBuilder& operator=(const HTMLBuilder&)	= delete;
	HTMLBuilder& operator=(HTMLBuilder&)		= delete;

public:
	void setIndexTitle(const string& title)			{ m_indexTitle = title; }
	void setFileNameHeader(const string& fileName)	{ m_fileNameHeader = fileName; }
	void setFilePathHeader(const string& filePath)	{ m_filePathHeader = filePath; }

	void addTable(const string& contentTitle, vector<string> columnNames);
	void addTableRow(vector<string> rowsContent);

	bool saveFile(const string& path);

private:
	void buildPage(string& pageContent);
	void buildContent(string& divContent, const size_t tabsCount);

	void buildTable(string& divContainer, const DivDescriptor& divDescriptor, const size_t tabsCount);
	void buildTree(string& divContainer, const DivDescriptor& divDescriptor, const size_t tabsCount);

	void replaceKeyword(string& source, const string& keyword, const string& newContent, bool move = false, size_t moveOffset = 0);

	size_t countTabs(const string& source, const string& keyword);
	void addTabsInTemplate(string& source, const size_t tabsCount);

private:
	string m_indexTitle;
	string m_fileNameHeader;
	string m_filePathHeader;

	vector<DivDescriptor>	m_divDescriptorVec;

	vector<TableContent>	m_tableContentVec;
	vector<TreeContent>		m_rreeContentVec;

	static const string		m_indexTemplate;
	static const string		m_containerTemplate;

	static const string		m_tableTemplate;
	static const string		m_tableColumnTrTemplate;
	static const string		m_tableColumnThTemplate;
	static const string		m_tableRowTrTemplate;
	static const string		m_tableRowTdTemplate;
};