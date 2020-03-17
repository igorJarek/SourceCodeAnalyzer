#include "Html.h"

string const HTMLBuilder::m_indexTemplate
{  
	"<!DOCTYPE html>\n"
	"<html lang=\"en\">\n"
	"<head>\n"
	"	<meta charset=\"utf-8\"/>\n"
	"	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\n"

	"	<title><?title?></title>\n\n"

	"	<style>\n"
	"		@font-face {\n"
	"			font-family: 'JetBrainsMono-Regular';\n"
	"			src: url('https://raw.githubusercontent.com/igorJarek/SourceCodeAnalyzer/master/html/fonts/JetBrainsMono-Regular.woff') format('woff');\n"
	"			font-weight: normal;\n"
	"			font-style: normal;\n"
	"		}\n\n"

	"		@font-face {\n"
	"			font-family: 'JetBrainsMono-Bold';\n"
	"			src: url('https://raw.githubusercontent.com/igorJarek/SourceCodeAnalyzer/master/html/fonts/JetBrainsMono-Bold.woff') format('woff');\n"
	"			font-weight: bold;\n"
	"			font-style: normal;\n"
	"		}\n\n"

	"		body {\n"
	"			background-color: rgb(255, 255, 220);\n"
	"			font-family: 'JetBrainsMono-Regular';\n"
	"		}\n\n"

	"		#site {\n"
	"			width: 80%;\n"
	"			margin-left: auto;\n"
	"			margin-right: auto;\n"
	"			min-width: 1000px;\n"
	"		}\n\n"

	"		#site-logo {\n"
	"			text-align: center;\n"
	"			-webkit-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
	"			-moz-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
	"			box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
	"			background-color: rgb(255, 255, 150);\n"
	"			padding: 10px;\n"
	"			border-radius: 10px;\n"
	"			margin: 10px 0 0 0;\n"
	"			font-family: 'JetBrainsMono-Bold';\n"
	"		}\n\n"

	"		#site-logo-fileName {\n"
	"			color: rgb(255, 50, 50);\n"
	"			height: 60px;\n"
	"			font-size: 40px;\n"
	"		}\n\n"

	"		#site-logo-filePath {\n"
	"			height: 30px;\n"
	"			font-size: 18px;\n"
	"		}\n\n"

	"		.site-content-container {\n"
	"			-webkit-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
	"			-moz-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
	"			box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
	"			background-color: rgb(255, 255, 200);\n"
	"			padding: 10px;\n"
	"			border-radius: 10px;\n"
	"			margin: 10px 0 0 0;\n"
	"		}\n\n"

	"		.site-content-container-containerHeader {\n"
	"			font-family: 'JetBrainsMono-Bold';\n"
	"			background-color: rgb(248, 207, 125);\n"
	"			font-size: 20px;\n"
	"			text-align: center;\n"
	"			padding: 7px 0;\n"
	"		}\n\n"

	"		.site-content-container-containerBody {\n"
	"			padding: 10px 0;\n"
	"		}\n\n"

	"		table, th, td {\n"
	"			border: 1px solid black;\n"
	"			border-collapse: collapse;\n"
	"		}\n\n"

	"		#footer {\n"
	"			margin: 10px 0 0 0;\n"
	"			text-align: center;\n"
	"		}\n\n"

	"	</style>\n"
	"</head>\n\n"

	"<body>\n"
	"	<div id =\"site\">\n"
	"		<div id =\"site-logo\">\n"
	"			<div id =\"site-logo-fileName\">\n"
	"				<?fileName?>\n"
	"			</div>\n"
	"			<div id =\"site-logo-filePath\">\n"
	"				<?filePath?>\n"
	"			</div>\n"
	"		</div>\n\n"

	"		<div id =\"site-content\">\n"
	"			<?content?>"
	"		</div>\n\n"

	"		<div id =\"footer\">\n"
	"			Created by : Igor Jarek, <a href =\"https://github.com/igorJarek\" target = \"_blank\">GitHub</a><br/>\n"
	"			Font : <a href =\"https://www.jetbrains.com/lp/mono/\" target = \"_blank\">JetBrains Mono</a>\n"
	"		</div>\n"
	"	</div>\n"
	"</body>\n"
	"</html>"
};

string const HTMLBuilder::m_containerTemplate
{
	// Fix formatting
	"<div class =\"site-content-container\">\n"
	"	<div class =\"site-content-container-containerHeader\">\n"
	"		<?containerHeader?>\n"
	"	</div>\n"
	"	<div class =\"site-content-container-containerBody\">\n"
	"		<?containerBody?>"
	"	</div>\n"
	"</div>\n"
};

string const HTMLBuilder::m_tableTemplate
{
	// Fix formatting
	"<table style = \"width:100%\">\n"
	"	<?tableBody?>"
	"</table>\n"
};

const string HTMLBuilder::m_tableColumnTrTemplate
{
	// Fix formatting
	"<tr>\n"
	"	<?tableColumnTr?>"
	"</tr>\n"
};

const string HTMLBuilder::m_tableColumnThTemplate
{
	// Fix formatting
	"<th><?tableColumnTh?></th>\n"
};

const string HTMLBuilder::m_tableRowTrTemplate
{
	// Fix formatting
	"<tr>\n"
	"	<?tableRowTr?>"
	"</tr>\n"
};

const string HTMLBuilder::m_tableRowTdTemplate
{
	// Fix formatting
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

void HTMLBuilder::replaceKeyword(string& source, const string& keyword, const string& newContent, size_t* tabsInLineCount /* = nullptr */)
{
	size_t pos = source.find(keyword);
	if (pos != std::string::npos)
	{
		if (tabsInLineCount)
		{
			*tabsInLineCount = 0;
			for (size_t index{ pos - 1 }; index >= 0; --index)
			{
				char c{ source.at(index) };
				if (c == '\n' || c != '\t')
					break;
				else
					++(*tabsInLineCount);
			}
		}

		source.erase(pos, keyword.size());
		if (newContent.empty())
			source.insert(pos, "--NULL--");
		else
			source.insert(pos, newContent);
	}
}