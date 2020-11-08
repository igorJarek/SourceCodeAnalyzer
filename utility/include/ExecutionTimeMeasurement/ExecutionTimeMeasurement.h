#pragma once

#include <string>
#include <chrono>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class ExecutionTimeMeasurement
{
public:
    ExecutionTimeMeasurement(string&& text) : m_text(text)
    {
        m_startTime = std::chrono::system_clock::now();
    }

    ~ExecutionTimeMeasurement()
    {
        m_endTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::ratio<1, 1000>> elapsedSeconds = m_endTime - m_startTime;

        cout << m_text << " " <<  elapsedSeconds.count() << " milliseconds." << endl;
    }

private:
    const string m_text;

    std::chrono::time_point<std::chrono::system_clock> m_startTime; 
    std::chrono::time_point<std::chrono::system_clock> m_endTime; 
};
