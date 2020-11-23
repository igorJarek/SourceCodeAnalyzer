#include <OutputTree/OutputTree.h>
#include <LibClangStruct2Str/LibClangStruct2Str.h>
#include <LibClangStruct2Str/PrintingPolicy.h>

#include <fstream>

OutputTree::OutputTree()
{
    m_rootPtr = std::make_shared<OutputTreeNode>();
    m_rootPtr->m_string = "ROOT";
}

OutputTree::~OutputTree()
{
    
}

OutputTree& OutputTree::operator=(const OutputTree& other)
{
    if( this != &other)
    {
        m_rootPtr = other.m_rootPtr;
        m_nodesCount = other.m_nodesCount;
        m_treeHeight = other.m_treeHeight;
    }

    return *this;
}

OutputTree& OutputTree::operator+=(const OutputTree& other)
{
    if( this != &other)
    {
        m_nodesCount = other.m_nodesCount;
        m_treeHeight = other.m_treeHeight;
    }

    return *this;
}

void OutputTree::addString(uint32_t level, const string& str)
{
    shared_ptr<OutputTreeNode> node = allocateNode(level);

    node->m_string = str;
}

void OutputTree::addString(uint32_t level, const string&& str)
{
    shared_ptr<OutputTreeNode> node = allocateNode(level);

    node->m_string = str;
}

void OutputTree::addNewLine(uint32_t level)
{
    shared_ptr<OutputTreeNode> node = allocateNode(level);

    //node->m_string = '\n';
}

void OutputTree::addCXStringSet(uint32_t level, const string&& str, CXStringSet* stringSet)
{
    addString(level, str);

    if(stringSet)
    {
        for (uint32_t index{ 0 }; index < stringSet->Count; ++index)
        {
            CXString cxString = stringSet->Strings[index];
            addValue(level + 1, clang_getCString(cxString));
        }

        clang_disposeStringSet(stringSet);
    }
    else
        addString(level, "--Empty--");
}

void OutputTree::addCXSourceLocation (uint32_t level, const string&& str, const CXSourceLocation& sourceLocation)
{
    CXFile   expansionFile,  spellingFile;
    uint32_t expansionLine,  spellingLine;
    uint32_t expansioColumn, spellingColumn;
    uint32_t expansioOffset, spellingOffset;

    clang_getExpansionLocation(sourceLocation, &expansionFile, &expansionLine, &expansioColumn, &expansioOffset);
    clang_getSpellingLocation (sourceLocation, &spellingFile,  &spellingLine,  &spellingColumn, &spellingOffset);

    addString(level + 0, str);

    string strData;
    
    strData += "File : "   + std::to_string(clang_getFileName(expansionFile)) + ", ";
    strData += "Line : "   + std::to_string(expansionLine)                    + ", ";
    strData += "Column : " + std::to_string(expansioColumn)                   + ", ";
    strData += "Offset : " + std::to_string(expansioOffset);

    addString(level + 1, "ExpansionLocation : ", strData);

    strData.clear();

    strData += "File : "   + std::to_string(clang_getFileName(spellingFile)) + ", ";
    strData += "Line : "   + std::to_string(spellingLine)                    + ", ";
    strData += "Column : " + std::to_string(spellingColumn)                  + ", ";
    strData += "Offset : " + std::to_string(spellingOffset);

    addString(level + 1, "SpellingLocation  : ", strData);
}

void OutputTree::addCXSourceRange(uint32_t level, const string&& str, const CXSourceRange& sourceRange)
{
    CXSourceLocation rangeStart = clang_getRangeStart(sourceRange);
    CXSourceLocation rangeEnd   = clang_getRangeEnd(sourceRange);

    addString(level + 0, str);

    addCXSourceLocation(level + 1, "RangeStart", rangeStart);
    addCXSourceLocation(level + 1, "RangeEnd", rangeEnd);
}

void OutputTree::addCXTUResourceUsage(uint32_t level, const string&& str, const CXTUResourceUsage& TUResourceUsage)
{
    if (TUResourceUsage.numEntries)
    {
        addString(level, str);

        for (uint32_t index{ 0 }; index < TUResourceUsage.numEntries; ++index)
        {
            CXTUResourceUsageEntry resourceUsageEntry = TUResourceUsage.entries[index];
            CXTUResourceUsageKind  kind               = resourceUsageEntry.kind;
            uint64_t               amount             = resourceUsageEntry.amount;

            addValue(level + 1, kind);
            addString(level + 1, "Amount : ", amount);
        }
    }
    else
        addString(level, "0");
}

void OutputTree::addCXVersion(uint32_t level, const string&& str, const CXVersion& version)
{
    string strData;

    strData += "Major : "    + std::to_string(version.Major) + ", ";
    strData += "Minor : "    + std::to_string(version.Minor) + ", ";
    strData += "Subminor : " + std::to_string(version.Subminor);

    addString(level + 0, str);
    addString(level + 1, strData);
}

void OutputTree::addCXPlatformAvailability(uint32_t level, const string&& str, const CXPlatformAvailability& platformAvailability)
{
    CXString  platform    = platformAvailability.Platform;
    CXVersion introduced  = platformAvailability.Introduced;
    CXVersion deprecated  = platformAvailability.Deprecated;
    CXVersion obsoleted   = platformAvailability.Obsoleted;
    int32_t   unavailable = platformAvailability.Unavailable;
    CXString  message     = platformAvailability.Message;

    addString   (level, "Platform",    platform);
    addCXVersion(level, "Introduced",  introduced);
    addCXVersion(level, "Deprecated",  deprecated);
    addCXVersion(level, "Obsoleted",   obsoleted);
    addString   (level, "Unavailable", unavailable);
    addString   (level, "Message",     message);
}

void OutputTree::addCXPrintingPolicy(uint32_t level, const string&& str, const CXPrintingPolicy& printingPolicy)
{
    PrintingPolicy* pp = reinterpret_cast<PrintingPolicy*>(printingPolicy);

    uint32_t indentation                           = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Indentation);
    uint32_t suppressSpecifiers                    = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressSpecifiers);
    uint32_t suppressTagKeyword                    = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressTagKeyword);
    uint32_t includeTagDefinition                  = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_IncludeTagDefinition);
    uint32_t suppressScope                         = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressScope);
    uint32_t suppressUnwrittenScope                = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressUnwrittenScope);
    uint32_t suppressInitializers                  = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressInitializers);
    uint32_t constantArraySizeAsWritten            = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_ConstantArraySizeAsWritten);
    uint32_t anonymousTagLocations                 = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_AnonymousTagLocations);
    uint32_t suppressStrongLifetime                = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressStrongLifetime);
    uint32_t suppressLifetimeQualifiers            = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressLifetimeQualifiers);
    uint32_t suppressTemplateArgsInCXXConstructors = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressTemplateArgsInCXXConstructors);
    uint32_t boolean                               = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Bool);
    uint32_t restrict                              = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Restrict);
    uint32_t alignOf                               = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Alignof);
    uint32_t underscoreAlignof                     = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_UnderscoreAlignof);
    uint32_t useVoidForZeroParams                  = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_UseVoidForZeroParams);
    uint32_t terseOutput                           = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_TerseOutput);
    uint32_t polishForDeclaration                  = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_PolishForDeclaration);
    uint32_t half                                  = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Half);
    uint32_t mswChar                               = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_MSWChar);
    uint32_t includeNewlines                       = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_IncludeNewlines);
    uint32_t mSVCFormatting                        = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_MSVCFormatting);
    uint32_t constantsAsWritten                    = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_ConstantsAsWritten);
    uint32_t suppressImplicitBase                  = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressImplicitBase);
    uint32_t fullyQualifiedName                    = clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_FullyQualifiedName);

    addString(level + 0, str);
    addString(level + 1, "CXPrintingPolicy");

    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_Indentation) : ",                           indentation);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressSpecifiers) : ",                    suppressSpecifiers);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressTagKeyword) : ",                    suppressTagKeyword);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_IncludeTagDefinition) : ",                  includeTagDefinition);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressScope) : ",                         suppressScope);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressUnwrittenScope) : ",                suppressUnwrittenScope);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressInitializers) : ",                  suppressInitializers);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_ConstantArraySizeAsWritten) : ",            constantArraySizeAsWritten);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_AnonymousTagLocations) : ",                 anonymousTagLocations);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressStrongLifetime) : ",                suppressStrongLifetime);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressLifetimeQualifiers) : ",            suppressLifetimeQualifiers);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressTemplateArgsInCXXConstructors) : ", suppressTemplateArgsInCXXConstructors);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_Bool) : ",                                  boolean);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_Restrict) : ",                              restrict);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_Alignof) : ",                               alignOf);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_UnderscoreAlignof) : ",                     underscoreAlignof);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_UseVoidForZeroParams) : ",                  useVoidForZeroParams);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_TerseOutput) : ",                           terseOutput);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_PolishForDeclaration) : ",                  polishForDeclaration);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_Half) : ",                                  half);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_MSWChar) : ",                               mswChar);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_IncludeNewlines) : ",                       includeNewlines);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_MSVCFormatting) : ",                        mSVCFormatting);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_ConstantsAsWritten) : ",                    constantsAsWritten);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressImplicitBase) : ",                  suppressImplicitBase);
    addString(level + 2, "clang_PrintingPolicy_getProperty(CXPrintingPolicy_FullyQualifiedName) : ",                    fullyQualifiedName);
}

void OutputTree::addCXFileInfo(uint32_t level, const string&& str, const CXFile& file, const CXTranslationUnit& translationUnit)
{
    char            timeBuff[255]          = { 0 };
    CXFileUniqueID  fileUniqueIDStruct;
    size_t          size                   = 0;

    time_t          fileTime               = clang_getFileTime(file);
    int32_t         fileUniqueID           = clang_getFileUniqueID(file, &fileUniqueIDStruct);
    uint32_t        multipleIncludeGuarded = clang_isFileMultipleIncludeGuarded(translationUnit, file);
    const char*     fileContents           = clang_getFileContents(translationUnit, file, &size);

    ctime_s(timeBuff, sizeof(timeBuff), &fileTime);

    addString(level + 0, str);

    addString(level + 1, "_8_getFileName : ",                    clang_getFileName(file));
    addString(level + 1, "_8_getFileTime : ",                    timeBuff);
    addString(level + 1, "_8_getFileUniqueID [return value] : ", fileUniqueID);
    addString(level + 1, "_8_getFileUniqueID [outID] : ",        std::to_string(fileUniqueIDStruct.data[0]) + ", " +
                                                                 std::to_string(fileUniqueIDStruct.data[1]) + ", " +
                                                                 std::to_string(fileUniqueIDStruct.data[2])        );
    addString(level + 1, "_8_isFileMultipleIncludeGuarded : ",   multipleIncludeGuarded);
    addString(level + 1, "_8_getFileContents [return] : ",       fileContents);
    addString(level + 1, "_8_File_tryGetRealPathName : ",        clang_File_tryGetRealPathName(file));
}

bool OutputTree::saveToFile(const string& path)
{
    std::fstream stream;
    stream.open(path, std::fstream::out | std::fstream::trunc);
    if (stream.is_open())
    {
        auto& rootChildren = m_rootPtr->m_children;
        for(auto& elem : rootChildren)
            saveNode(stream, "", elem);

        stream.close();

        return true;
    }
    else
        return false;
}

void OutputTree::saveNode(std::fstream& stream, const std::string& prefix, shared_ptr<OutputTreeNode>& node)
{
    stream << prefix;

    stream << node->m_string << std::endl;

    auto& children = node->m_children;
    for(auto& elem : children)
        saveNode(stream, prefix + "    ", elem);
}

shared_ptr<OutputTreeNode> OutputTree::allocateNode(uint32_t level)
{
    if(level + 1 > m_treeHeight)
        m_treeHeight = level + 1;

    shared_ptr<OutputTreeNode> currentNode = m_rootPtr;

    for(uint32_t indexLevel = 0; indexLevel < level; ++indexLevel)
    {
        if(!currentNode->m_children.empty())
            currentNode = currentNode->m_children.back();
    }

    shared_ptr<OutputTreeNode> newNode = std::make_shared<OutputTreeNode>();

    currentNode->m_children.push_back(newNode);

    ++m_nodesCount;

    return newNode;
}
