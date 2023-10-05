#pragma once

/**
 * Logs a message to the console and log file with file and line number information.
 * \param Type Log, Warning or Error. See the LogType enum for reference 
 */
#define GIO_LOG(Type, Message) Logger::Log(LogType::Type, Message, __FILE__, __LINE__)

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
    
public:
    static void Init(const std::string& logFilePath);
    
    static void Log(LogType type, const std::string& log, const std::string& file, int line);

private:
    Logger(const std::string& inFilePath);

    void SetupFile();
    
    void LogInternal(LogType type, const std::string& log, const std::string& file, int line);

    std::string FormatString(LogType type, const std::string& log, const std::string& file, int line) const;

    void WriteToFile(const std::string& log);
};
