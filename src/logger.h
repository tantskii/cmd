/*!
 @file
 @brief Заголовочный файл, содержащий объявление интерфейса логгера.
 */

#pragma once
#include "publisher.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <ctime>


#define UNUSED(x) (void)(x)

class Logger;
class OStreamLogger;
class FileLogger;
class File;

using LoggerPtr = std::shared_ptr<Logger>; ///< Указатель на базовый класс логгера.



/*!
 @brief Базовый класс логгера.
 */
class Logger {
public:
    virtual ~Logger() = default;
    virtual void setPrefix(const std::string& prefix);   ///< Устанавливает префикс для сообщений.
protected:
    virtual std::string prepare(const std::string& message) const; ///< Собирает финальное логгируемое
                                                                   /// сообщение.
    std::string m_prefix = "";
};


/*!
 @brief Логгер, который выводит информацию в  std::ostream.
 */
class OStreamLogger : public Logger, public ISubscriber {
public:
    OStreamLogger(std::ostream& stream);
    void update(const std::string& message, time_t timestamp) override; ///< Логгирует переданное сообщение.
private:
    std::ostream& m_stream;
};


/*!
 @brief Обертка над std::ofstream, созданная для соблюдения идиомы RAII.
 */
class File {
public:
    File(std::filesystem::path);    ///< Открывает файл.
    void write(const std::string&); ///< Записывает в файл переданную строку.
    ~File();                        ///< Закрывает файл.
private:
    std::ofstream m_file;
};


/*!
 @brief Логгер, который выводит информацию в файлы.
 */
class FileLogger : public Logger, public ISubscriber {
public:
    FileLogger();
    void setOutputDirectory(const std::filesystem::path&);
    void update(const std::string&, time_t) override; ///< Логгирует переданное сообщение.
private:
    std::string makeFileName(time_t) const;  ///< Создает название лог-файла.
    
    std::filesystem::path m_dir = std::filesystem::current_path() / "log";
    bool m_dir_exists;
};

