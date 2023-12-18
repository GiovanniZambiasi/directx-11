#include "pch.h"
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <thread>

#include "ErrorHandling.h"


std::unique_ptr<Logger> Logger::instance{};

void Logger::Init(const std::string& logFilePath, const std::string& stdoutFilePath)
{
    assert(!instance);
    instance = std::unique_ptr<Logger>{new Logger{logFilePath, stdoutFilePath}};
}

void Logger::Log(LogType type, const std::string& log, const std::string& file, int line)
{
    assert(instance);
    instance->LogInternal(type, log, file, line);
}

Logger::~Logger()
{
    outputThread.detach();
}

Logger::Logger(const std::string& inFilePath, const std::string& stdoutFilePath)
    : logFilePath(inFilePath), stdoutFilePath(stdoutFilePath)
{
    SetupFile();
    RedirectStdoutToFile();
    outputThread = std::thread{&Logger::OpenConsoleWindow, this};
}

void Logger::SetupFile()
{
    fileStream.open(logFilePath);
}

void Logger::RedirectStdoutToFile()
{
    std::remove(stdoutFilePath.c_str());
    freopen(stdoutFilePath.c_str(), "w", stdout);
}

void Logger::OpenConsoleWindow()
{
    // TODO - Use python instead of powershell
    std::string command = FormatToString("powershell.exe Get-Content '%s' -Wait -Tail -1", stdoutFilePath.c_str());
    std::system(command.c_str());
}

void Logger::LogInternal(LogType type, const std::string& log, const std::string& file, int line)
{
    std::string str = FormatString(type, log, file, line);
    std::cout << str << std::endl;
    WriteToFile(str);
}

std::string Logger::FormatString(LogType type, const std::string& log, const std::string& file, int line) const
{
    std::stringstream formatted{};

    switch (type)
    {
    case LogType::Log:
        formatted << "[Log]: ";
        break;
    case LogType::Warning:
        formatted << "[Warning]: ";
        break;
    case LogType::Error:
        formatted << "[Error]: ";
        break;
    default:
        formatted << "[Unknown]: ";
        break;
    }
    
    formatted << log << " (" << file << " @ " << line << ")";
    return formatted.str();
}

void Logger::WriteToFile(const std::string& log)
{
    if(fileStream.is_open())
    {
        fileStream << log << std::endl;
    }
    else
    {
        
        std::cout << "no";
    }
}
