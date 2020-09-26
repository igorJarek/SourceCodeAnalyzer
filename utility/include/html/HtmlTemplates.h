#pragma once

#include <string>

using namespace std;

// ------- INDEX ------- //

const string INDEX_TEMPLATE
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
	"			<?content?>\n"
	"		</div>\n\n"

	"		<div id =\"footer\">\n"
	"			Created by : Igor Jarek, <a href =\"https://github.com/igorJarek\" target = \"_blank\">GitHub</a><br/>\n"
	"			Font : <a href =\"https://www.jetbrains.com/lp/mono/\" target = \"_blank\">JetBrains Mono</a>\n"
	"		</div>\n"
	"	</div>\n"
	"</body>\n"
	"</html>"
};

// ------- CONTAINER ------- //

const string CONTAINER_TEMPLATE
{
	"<div class =\"site-content-container\">\n"
	"	<div class =\"site-content-container-containerHeader\">\n"
	"		<?containerHeader?>\n"
	"	</div>\n"
	"	<div class =\"site-content-container-containerBody\">\n"
	"		<?containerBody?>\n"
	"	</div>\n"
	"</div>\n"
};

// ------- TABLE ------- //

const string TABLE_TEMPLATE
{
	"<table style = \"width:100%\">\n"
	"	<?tableBody?>\n"
	"</table>\n"
};

const string TABLE_COLUMN_TR_TEMPLATE
{
	"<tr>\n"
	"	<?tableColumnTr?>\n"
	"</tr>\n"
};

const string TABLE_COLUMN_TH_TEMPLATE
{
	"<th><?tableColumnTh?></th>\n"
};

const string TABLE_ROW_TR_TEMPLATE
{
	"<tr>\n"
	"	<?tableRowTr?>\n"
	"</tr>\n"
};

const string TABLE_ROW_TD_TEMPLATE
{
	"<td style =\"text-align:center;\"><?tableRowTd?></td>\n"
};

// ------- TREE ------- //

const string TREE_ROOT_UL_TEMPLATE
{
	"<ul>\n"
	"	<?rootBody?>\n"		
	"</ul>\n"
};

const string TREE_UL_LI_TEMPLATE
{
	"<li><?ulluHeader?>\n"
	"<ul>\n"
	"	<?ulliBody?>\n"
	"</ul>\n"
	"</li>\n"
};

const string TREE_LI_TEMPLATE
{
	"<li><?liBody?></li>\n"
};