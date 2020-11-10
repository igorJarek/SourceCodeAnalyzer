#pragma once

#include <string>
#include <map>

using namespace std;

class GlobalColumnDict;
class TokenColumnDict;
class CursorColumnDict;
class TypeColumnDict;
class LinkingColumnDict;

extern GlobalColumnDict  g_globalColumnDict;
extern TokenColumnDict   g_tokenColumnDict;
extern CursorColumnDict  g_cursorColumnDict;
extern TypeColumnDict    g_typeColumnDict;
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

class TypeColumnDict : public DatabaseColumnDict
{
public:
    TypeColumnDict();
    ~TypeColumnDict() {}
};

class LinkingColumnDict : public DatabaseColumnDict
{
public:
    LinkingColumnDict();
    ~LinkingColumnDict() {}
};
