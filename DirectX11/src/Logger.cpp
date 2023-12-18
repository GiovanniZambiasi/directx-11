#include "pch.h"
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <thread>

#include "ErrorHandling.h"


std::unique_ptr<Logger> Logger::instance{};

void Logger::Init(LoggerConfig&& config)
{
    assert(!instance);
    instance = std::unique_ptr<Logger>{new Logger{std::move(config)}};
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

Logger::Logger(LoggerConfig&& config)
    : config(std::move(config))
{
    SetupFile();
    RedirectStdoutToFile();
    outputThread = std::thread{&Logger::OpenConsoleWindow, this};
}

void Logger::SetupFile()
{
    std::remove(config.logFilePath.c_str());
    fileStream.open(config.logFilePath);
}

void Logger::RedirectStdoutToFile()
{
    std::remove(config.stdoutFilePath.c_str());
    freopen(config.stdoutFilePath.c_str(), "w", stdout);

    std::remove(config.stderrFilePath.c_str());
    freopen(config.stderrFilePath.c_str(), "w", stderr);
}

void Logger::OpenConsoleWindow()
{
    std::stringstream logFileNames{};
    logFileNames << "python.exe res/logger.py ";
    logFileNames << '\"' << config.stdoutFilePath.c_str() << "\" ";
    logFileNames << '\"' << config.stderrFilePath.c_str() << "\" ";
    std::string command = logFileNames.str();
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
