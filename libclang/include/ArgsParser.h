#pragma once

#include <string>
#include <vector>

class ArgsParser
{
public:
    ArgsParser (int argc, char **argv)
    {
        for (int i = 1; i < argc; ++i)
            m_tokens.push_back(std::string(argv[i]));
    }

public:
    bool isCmdOptionExists(const std::string &option) const
    {
        return std::find(m_tokens.begin(), m_tokens.end(), option)
               != 
               m_tokens.end();
    }

    bool isCmdOptionAndArgExists(const std::string &option) const
    {
        std::vector<std::string>::const_iterator itr = std::find(m_tokens.begin(), m_tokens.end(), option);

        if(itr != m_tokens.end())
        if(++itr != m_tokens.end())
        if(itr->front() != '-')
            return true;

        return false;
    }

    const std::string& getCmdArg(const std::string &option) const
    {
        std::vector<std::string>::const_iterator itr = std::find(m_tokens.begin(), m_tokens.end(), option);
        if (itr != m_tokens.end() && ++itr != m_tokens.end())
            return *itr;

        static const std::string empty_string("");
        return empty_string;
    }

private:
    std::vector <std::string> m_tokens;
};
