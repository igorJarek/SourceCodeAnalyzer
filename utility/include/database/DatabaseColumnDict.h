#pragma once

#include <string>
#include <map>

using namespace std;

class GlobalColumnDict;
class FileListColumnDict;
class TokenColumnDict;
class CallingColumnDict;
class FunctionsColumnDict;

extern GlobalColumnDict    g_globalColumnDict;
extern FileListColumnDict  g_fileListColumnDict;
extern TokenColumnDict     g_tokenColumnDict;
extern CallingColumnDict   g_callingColumnDict;
extern FunctionsColumnDict g_functionsColumnDict;

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

class CallingColumnDict : public DatabaseColumnDict
{
public:
    CallingColumnDict();
    ~CallingColumnDict() {}
};

class FunctionsColumnDict : public DatabaseColumnDict
{
public:
    FunctionsColumnDict();
    ~FunctionsColumnDict() {}
};
