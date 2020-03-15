#include "Html.h"

string const HTMLBuilder::m_indexTemplate
{  
	"<!DOCTYPE html>\n"
	"<html lang=\"en\">\n"
	"<head>\n"
		"\t<meta charset=\"utf-8\"/>\n"
		"\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\n"

		"\t<title><?title?></title>\n\n"

		"\t<style>\n"
			"\t\t@font-face {\n"
				"\t\t\tfont-family: 'JetBrainsMono-Regular';\n"
				"\t\t\tsrc: url('https://raw.githubusercontent.com/igorJarek/SourceCodeAnalyzer/master/html/fonts/JetBrainsMono-Regular.woff') format('woff');\n"
				"\t\t\tfont-weight: normal;\n"
				"\t\t\tfont-style: normal;\n"
			"\t\t}\n\n"

			"\t\t@font-face {\n"
				"\t\t\tfont-family: 'JetBrainsMono-Bold';\n"
				"\t\t\tsrc: url('https://raw.githubusercontent.com/igorJarek/SourceCodeAnalyzer/master/html/fonts/JetBrainsMono-Bold.woff') format('woff');\n"
				"\t\t\tfont-weight: bold;\n"
				"\t\t\tfont-style: normal;\n"
			"\t\t}\n\n"

			"\t\tbody {\n"
				"\t\t\tbackground-color: rgb(255, 255, 220);\n"
				"\t\t\tfont-family: 'JetBrainsMono-Regular';\n"
			"\t\t}\n\n"

			"\t\t#site {\n"
				"\t\t\twidth: 80%;\n"
				"\t\t\tmargin-left: auto;\n"
				"\t\t\tmargin-right: auto;\n"
				"\t\t\tmin-width: 1000px;\n"
			"\t\t}\n\n"

			"\t\t#site-logo {\n"
				"\t\t\ttext-align: center;\n"
				"\t\t\t-webkit-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"\t\t\t-moz-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"\t\t\tbox-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"\t\t\tbackground-color: rgb(255, 255, 150);\n"
				"\t\t\tpadding: 10px;\n"
				"\t\t\tborder-radius: 10px;\n"
				"\t\t\tmargin: 10px 0 0 0;\n"
				"\t\t\tfont-family: 'JetBrainsMono-Bold';\n"
			"\t\t}\n\n"

			"\t\t#site-logo-fileName {\n"
				"\t\t\tcolor: rgb(255, 50, 50);\n"
				"\t\t\theight: 60px;\n"
				"\t\t\tfont-size: 40px;\n"
			"\t\t}\n\n"

			"\t\t#site-logo-filePath {\n"
				"\t\t\theight: 30px;\n"
				"\t\t\tfont-size: 18px;\n"
			"\t\t}\n\n"

			"\t\t.site-content-container {\n"
				"\t\t\t-webkit-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"\t\t\t-moz-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"\t\t\tbox-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"\t\t\tbackground-color: rgb(255, 255, 200);\n"
				"\t\t\tpadding: 10px;\n"
				"\t\t\tborder-radius: 10px;\n"
				"\t\t\tmargin: 10px 0 0 0;\n"
			"\t\t}\n\n"

			"\t\t.site-content-container-containerHeader {\n"
				"\t\t\tfont-family: 'JetBrainsMono-Bold';\n"
				"\t\t\tbackground-color: rgb(248, 207, 125);\n"
				"\t\t\tfont-size: 20px;\n"
				"\t\t\ttext-align: center;\n"
				"\t\t\tpadding: 7px 0;\n"
			"\t\t}\n\n"

			"\t\t.site-content-container-containerBody {\n"
				"\t\t\tpadding: 10px 0;\n"
			"\t\t}\n\n"

			"\t\ttable, th, td {\n"
				"\t\t\tborder: 1px solid black;\n"
				"\t\t\tborder-collapse: collapse;\n"
			"\t\t}\n\n"

			"\t\t#footer {\n"
				"\t\t\tmargin: 10px 0 0 0;\n"
				"\t\t\ttext-align: center;\n"
			"\t\t}\n\n"

		"\t</style>\n"
	"</head>\n\n"

	"<body>\n"
		"\t<div id =\"site\">\n"
			"\t\t<div id =\"site-logo\">\n"
				"\t\t\t<div id =\"site-logo-fileName\">\n"
					"\t\t\t\t<?fileName?>\n"
				"\t\t\t</div>\n"
				"\t\t\t<div id =\"site-logo-filePath\">\n"
					"\t\t\t\t<?filePath?>\n"
				"\t\t\t</div>\n"
			"\t\t</div>\n\n"

			"\t\t<div id =\"site-content\">\n"
				"\t\t\t<?content?>\n"
			"\t\t</div>\n\n"

			"\t\t<div id =\"footer\">\n"
				"\t\t\tCreated by : Igor Jarek, <a href =\"https://github.com/igorJarek\" target = \"_blank\">GitHub</a><br/>\n"
				"\t\t\tFont : <a href =\"https://www.jetbrains.com/lp/mono/\" target = \"_blank\">JetBrains Mono</a>\n"
				"\t\t\t</div>\n"
			"\t\t</div>\n"
	"</body>\n"
	"</html>"
};

string const HTMLBuilder::m_containerTemplate
{
	"<div class =\"site-content-container\">\n"
		"<div class =\"site-content-container-containerHeader\">\n"
			"<?containerHeader?>\n"
		"</div>\n"
		"<div class =\"site-content-container-containerBody\">\n"
			"<?containerBody?>\n"
		"</div>\n"
	"</div>\n\n"
};

string const HTMLBuilder::m_tableTemplate
{
	"<table style = \"width:100%\">\n"
		"<?tableBody?>\n"
	"</table>\n"
};

const string HTMLBuilder::m_tableColumnTrTemplate
{
	"<tr>\n"
		"<?tableColumnTr?>\n"
	"</tr>\n"
};

const string HTMLBuilder::m_tableColumnThTemplate
{
	"<th><?tableColumnTh?></th>\n"
};

const string HTMLBuilder::m_tableRowTrTemplate
{
	"<tr>\n"
		"<?tableRowTr?>\n"
	"</tr>\n"
};

const string HTMLBuilder::m_tableRowTdTemplate
{
	"<td style =\"text-align:center;\"><?tableRowTd?></td>\n"
};

void HTMLBuilder::addTable(const string& contentTitle, vector<string> columnNames)
{
	DivDescriptor divDescriptor;
	divDescriptor.type = DivDescriptorType::DCT_TABLE;
	divDescriptor.containerHeader = contentTitle;
	divDescriptor.vectorIndex = m_tableContentVec.size();

	TableContent tableContent;
	tableContent.columnNames = columnNames;

	m_divDescriptorVec.push_back(divDescriptor);
	m_tableContentVec.push_back(tableContent);
}

void HTMLBuilder::addTableRow(vector<string> rowsContent)
{
	TableContent& tableContent = m_tableContentVec.back();
	tableContent.rows.push_back(rowsContent);
}

void HTMLBuilder::buildPage(string& pageContent)
{
	pageContent = m_indexTemplate;

	string titleKeyword		{ "<?title?>" };
	string fileNameKeyword	{ "<?fileName?>" };
	string filePathKeyword	{ "<?filePath?>" };
	string contentKeyword	{ "<?content?>" };

	replaceKeyword(pageContent, titleKeyword,	 m_indexTitle);
	replaceKeyword(pageContent, fileNameKeyword, m_fileNameHeader);
	replaceKeyword(pageContent, filePathKeyword, m_filePathHeader);

	string divContent;
	buildContent(divContent);

	replaceKeyword(pageContent, contentKeyword, divContent);
}

void HTMLBuilder::buildContent(string& divContent)
{
	for (DivDescriptor& divDescriptor : m_divDescriptorVec)
	{
		string divContainer				{ m_containerTemplate };
		string containerHeaderKeyword	{ "<?containerHeader?>" };
		string containerBodyKeyword		{ "<?containerBody?>" };

		replaceKeyword(divContainer, containerHeaderKeyword, divDescriptor.containerHeader);

		string divContainerContent;
		switch (divDescriptor.type)
		{
			case DivDescriptorType::DCT_TABLE:
				buildTable(divContainerContent, divDescriptor);
				break;

			case DivDescriptorType::DCT_TREE:
				buildTree(divContainerContent, divDescriptor);
				break;
		}

		replaceKeyword(divContainer, containerBodyKeyword, divContainerContent);
		
		divContent += divContainer;
	}
}

void HTMLBuilder::buildTable(string& divContainer, const DivDescriptor& divDescriptor)
{
	const TableContent& tableContentVecElem = m_tableContentVec.at(divDescriptor.vectorIndex);

	string tableContent			{ m_tableTemplate };
	string tableBodyKeyword		{ "<?tableBody?>" };

	string tableColumnTrKeyword	{ "<?tableColumnTr?>" };
	string tableColumnThKeyword	{ "<?tableColumnTh?>" };
	string tableRowTrKeyword	{ "<?tableRowTr?>" };
	string tableRowTdKeyword	{ "<?tableRowTd?>" };

	// Columns
	string tableColumnsTr{ m_tableColumnTrTemplate };
	string tableColumnsThs;
	for (const string& columnName : tableContentVecElem.columnNames)
	{
		string tableColumnsTh{ m_tableColumnThTemplate };
		replaceKeyword(tableColumnsTh, tableColumnThKeyword, columnName);
		tableColumnsThs += tableColumnsTh;
	}

	replaceKeyword(tableColumnsTr, tableColumnTrKeyword, tableColumnsThs);

	// Rowsa
	string tableRowsTrs;
	for (const vector<string>& row : tableContentVecElem.rows)
	{
		string tableRowsTr{ m_tableRowTrTemplate };
		string tableRowsTds;
		for (const string& rowName : row)
		{
			string tableRowsTd{ m_tableRowTdTemplate };

			replaceKeyword(tableRowsTd, tableRowTdKeyword, rowName);

			tableRowsTds += tableRowsTd;
		}

		replaceKeyword(tableRowsTr, tableRowTrKeyword, tableRowsTds);

		tableRowsTrs += tableRowsTr;
	}

	replaceKeyword(tableContent, tableBodyKeyword, tableColumnsTr + tableRowsTrs);

	divContainer += tableContent;
}

void HTMLBuilder::buildTree(string& divContainer, const DivDescriptor& divDescriptor)
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

void HTMLBuilder::replaceKeyword(string& source, const string& keyword, const string& newContent)
{
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