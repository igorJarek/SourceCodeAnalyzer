#pragma once

#include <iostream>

#include <string>
#include <fstream>
#include <initializer_list>

using namespace std;

class HTMLBuilder
{
public:
	HTMLBuilder();
	~HTMLBuilder();

	HTMLBuilder(const HTMLBuilder&)				= delete;
	HTMLBuilder(HTMLBuilder&&) noexcept			= delete;
	HTMLBuilder& operator=(const HTMLBuilder&)	= delete;
	HTMLBuilder& operator=(HTMLBuilder&)		= delete;

public:
	void setIndexTitle(const string& title)			{ m_indexTitle = title; }
	void setFileNameHeader(const string& fileName)	{ m_fileNameHeader = fileName; }
	void setFilePathHeader(const string& filePath)	{ m_filePathHeader = filePath; }

	void addTableColumns(const string& contentTitle, initializer_list<string> columnNames);

	bool saveFile(const string& path);

private:
	void buildPage(string& content);
	void buildContent(string& content, size_t contentPos);

private:
	string m_indexTitle;
	string m_fileNameHeader;
	string m_filePathHeader;

	static const string m_indexTemplate;
	static const string m_containerTemplate;

	static const string m_tableTemplate;
	static const string m_tableColumnTemplate;
	static const string m_tableRowTemplate;
};