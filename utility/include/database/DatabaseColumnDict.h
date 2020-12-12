#pragma once

#include <string>
#include <map>

using namespace std;

class GlobalColumnDict;
class FileListColumnDict;
class TokenColumnDict;

extern GlobalColumnDict   g_globalColumnDict;
extern FileListColumnDict g_fileListColumnDict;
extern TokenColumnDict    g_tokenColumnDict;

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

class FileListColumnDict : public DatabaseColumnDict
{
public:
    FileListColumnDict();
    ~FileListColumnDict() {}
};

class TokenColumnDict : public DatabaseColumnDict
{
public:
    TokenColumnDict();
    ~TokenColumnDict() {}
};
