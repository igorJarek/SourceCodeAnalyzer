#pragma once

#include <string>
#include <map>

using namespace std;

class GlobalColumnDict;
class TokenColumnDict;
class SourceCodeColumnDict;

extern GlobalColumnDict     g_globalColumnDict;
extern TokenColumnDict      g_tokenColumnDict;
extern SourceCodeColumnDict g_sourceCodeColumnDict;

class DatabaseColumnDict : public map<uint32_t, string>
{
public:
    DatabaseColumnDict() {};
    virtual ~DatabaseColumnDict() {}
};

class GlobalColumnDict : public DatabaseColumnDict
{
public:
    GlobalColumnDict();
    ~GlobalColumnDict() {}
};

class TokenColumnDict : public DatabaseColumnDict
{
public:
    TokenColumnDict();
    ~TokenColumnDict() {}
};

class SourceCodeColumnDict : public DatabaseColumnDict
{
public:
    SourceCodeColumnDict();
    ~SourceCodeColumnDict() {}
};