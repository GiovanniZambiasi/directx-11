#pragma once

#include <fstream>
#include <thread>

/**
 * Logs a message to the console and log file with file and line number information.
 * \param Type Log, Warning or Error. See the LogType enum for reference 
 */
#define GIO_LOG(Type, Message) Logger::Log(LogType::Type, Message, __FILE__, __LINE__)

/**
 * Logs a formatted message to the console and log file with file and line number information.
 * \param Type Log, Warning or Error. See the LogType enum for reference 
 */
#define GIO_LOG_F(Type, Format, ...) Logger::Log(LogType::Type, Logger::FormatToString(Format, __VA_ARGS__), __FILE__, __LINE__)


enum class LogType
{
    Log,
    Warning,
    Error,
};

class Logger
{
    static std::unique_ptr<Logger> instance;

    std::string logFilePath{};

    std::ofstream fileStream{};

    std::thread outputThread{};
    
public:
    static void Init(const std::string& logFilePath);
    
    static void Log(LogType type, const std::string& log, const std::string& file, int line);

    template <typename... Args>
    static std::string FormatToString(const char* format, Args...args)
    {
        constexpr size_t maxSize = 256;
        char buffer[maxSize];
        sprintf_s(buffer, sizeof(buffer), format, args...);
        return {buffer};
    }

    ~Logger();
    
private:
    Logger(const std::string& inFilePath);

    void SetupFile();

    void RedirectStdoutToFile();

    void OpenConsoleWindow();
    
    void LogInternal(LogType type, const std::string& log, const std::string& file, int line);

    std::string FormatString(LogType type, const std::string& log, const std::string& file, int line) const;

    void WriteToFile(const std::string& log);
};
