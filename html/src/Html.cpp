#include "Html.h"

string const HTMLBuilder::m_indexTemplate
{  
	"<!DOCTYPE html>\n"
	"<html lang=\"en\">\n"
	"<head>\n"
		"\t<meta charset=\"utf-8\"/>\n"
		"\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\n"

		"\t<title><?title?></title>\n\n"

		"<style>\n"
			"@font-face {\n"
				"font-family: 'JetBrainsMono-Regular';\n"
				"src: url('https://raw.githubusercontent.com/igorJarek/SourceCodeAnalyzer/master/html/fonts/JetBrainsMono-Regular.woff') format('woff');\n"
				"font-weight: normal;\n"
				"font-style: normal;\n"
			"}\n"

			"@font-face {\n"
				"font-family: 'JetBrainsMono-Bold';\n"
				"src: url('https://raw.githubusercontent.com/igorJarek/SourceCodeAnalyzer/master/html/fonts/JetBrainsMono-Bold.woff') format('woff');\n"
				"font-weight: bold;\n"
				"font-style: normal;\n"
			"}\n\n"

			"body {\n"
				"background-color: rgb(255, 255, 220);\n"
				"font-family: 'JetBrainsMono-Regular';\n"
			"}\n\n"

			"#site {\n"
				"width: 80%;\n"
				"margin-left: auto;\n"
				"margin-right: auto;\n"
				"min-width: 1000px;\n"
			"}\n\n"

			"#site-logo {\n"
				"text-align: center;\n"
				"-webkit-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"-moz-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"background-color: rgb(255, 255, 150);\n"
				"padding: 10px;\n"
				"border-radius: 10px;\n"
				"margin: 10px 0 0 0;\n"
				"font-family: 'JetBrainsMono-Bold';\n"
			"}\n\n"

			"#site-logo-fileName {\n"
				"color: rgb(255, 50, 50);\n"
				"height: 60px;\n"
				"font-size: 40px;\n"
			"}\n\n"

			"#site-logo-filePath {\n"
				"height: 30px;\n"
				"font-size: 18px;\n"
			"}\n\n"

			".site-content-container {\n"
				"-webkit-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"-moz-box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"box-shadow: 2px 2px 10px 1px rgba(0, 0, 0, 0.75);\n"
				"background-color: rgb(255, 255, 200);\n"
				"padding: 10px;\n"
				"border-radius: 10px;\n"
				"margin: 10px 0 0 0;\n"
			"}\n\n"

			".site-content-container-containerHeader {\n"
				"font-family: 'JetBrainsMono-Bold';\n"
				"background-color: rgb(248, 207, 125);\n"
				"font-size: 20px;\n"
				"text-align: center;\n"
				"padding: 7px 0;\n"
			"}\n\n"

			".site-content-container-containerBody {\n"
				"padding: 10px 0;\n"
			"}\n\n"

			"table, th, td {\n"
				"border: 1px solid black;\n"
				"border-collapse: collapse;\n"
			"}\n\n"

			"#footer {\n"
				"margin: 10px 0 0 0;\n"
				"text-align: center;\n"
			"}\n\n"

		"</style>\n"
	"</head>\n\n"

	"<body>\n"
		"<div id =\"site\">\n"
			"<div id =\"site-logo\">\n"
				"<div id =\"site-logo-fileName\">\n"
					"<?fileName?>\n"
				"</div>\n"
				"<div id =\"site-logo-filePath\">\n"
					"<?filePath?>\n"
				"</div>\n"
			"</div>\n\n"

			"<div id =\"site-content\">\n"
				"<?content?>\n"
			"</div>\n\n"

			"<div id =\"footer\">\n"
				"Created by : Igor Jarek, <a href =\"https://github.com/igorJarek\" target = \"_blank\">GitHub</a><br/>\n"
				"Font : <a href =\"https://www.jetbrains.com/lp/mono/\" target = \"_blank\">JetBrains Mono</a>\n"
				"</div>\n"
			"</div>\n"
	"</body>\n"
	"</html>"
};

string const HTMLBuilder::m_containerTemplate
{
	"<div class = \"site-content-container\">"
		"<div class = \"site-content-container-containerHeader\">"
			"<?containerHeader?>"
		"</div>"
		"<div class = \"site-content-container-containerBody\">"
			"<?containerBody?>"
		"</div>"
	"</div>"
};

string const HTMLBuilder::m_tableTemplate
{
	"<table style = \"width:100%\">"
		"<?tableBody?>"
	"</table>"
};

string const HTMLBuilder::m_tableColumnTemplate
{

};

string const HTMLBuilder::m_tableRowTemplate
{
	
};

HTMLBuilder::HTMLBuilder()
{
	
}

HTMLBuilder::~HTMLBuilder()
{

}

void HTMLBuilder::buildPage(string& content)
{
	content = m_indexTemplate;

	string titleKeyword		{ "<?title?>" };
	string fileNameKeyword	{ "<?fileName?>" };
	string filePathKeyword	{ "<?filePath?>" };
	string contentKeyword	{ "<?content?>" };

	size_t titlePos = content.find(titleKeyword);
	if (titlePos != std::string::npos)
	{
		content.erase(titlePos, titleKeyword.size());
		if(m_indexTitle.empty())
			content.insert(titlePos, "--NULL--");
		else
			content.insert(titlePos, m_indexTitle);
	}

	size_t fileNamePos = content.find(fileNameKeyword);
	if (fileNamePos != std::string::npos)
	{
		content.erase(fileNamePos, fileNameKeyword.size());
		if (m_fileNameHeader.empty())
			content.insert(fileNamePos, "--NULL--");
		else
			content.insert(fileNamePos, m_fileNameHeader);
	}

	size_t filePathPos = content.find(filePathKeyword);
	if (filePathPos != std::string::npos)
	{
		content.erase(filePathPos, filePathKeyword.size());
		if (m_filePathHeader.empty())
			content.insert(filePathPos, "--NULL--");
		else
			content.insert(filePathPos, m_filePathHeader);
	}

	size_t contentPos = content.find(contentKeyword);
	if (contentPos != std::string::npos)
	{
		content.erase(contentPos, contentKeyword.size());
		buildContent(content, contentPos);
	}
}

void HTMLBuilder::buildContent(string& content, size_t contentPos)
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