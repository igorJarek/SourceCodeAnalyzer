#pragma once

#include <string>
#include <map>

using namespace std;

class GlobalColumnDict;
class TokenColumnDict;
class CursorColumnDict;
class LinkingColumnDict;

extern GlobalColumnDict  g_globalColumnDict;
extern TokenColumnDict   g_tokenColumnDict;
extern CursorColumnDict  g_cursorColumnDict;
extern LinkingColumnDict g_linkingColumnDict;

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

class CursorColumnDict : public DatabaseColumnDict
{
public:
    CursorColumnDict();
    ~CursorColumnDict() {}
};

class LinkingColumnDict : public DatabaseColumnDict
{
public:
    LinkingColumnDict();
    ~LinkingColumnDict() {}
};
