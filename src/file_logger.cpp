#include "logger.h"

namespace fs = std::filesystem;


/*!
 В конструкторе создается файл, в который будет записана строка.
 @param filepath Путь до лог-файла.
 */
File::File(fs::path filepath) {
    m_file.open(filepath, std::ios_base::out);
}


/*!
 В деструкторе закрывается соединение с файлом.
 */
File::~File() {
    m_file.close();
}


/*!
 Записывает переданную стркоу в лог-файл.
 @param info Логируемая строка.
 */
void File::write(const std::string& info) {
    m_file << info;
}


/*!
 Создает объект FileLogger.
 @param dir Путь до директории, куда будут сохранятся лог-файлы.
 */
FileLogger::FileLogger()
    : m_dir_exists(fs::exists(m_dir))
{}


/*!
 Устанавливает директорию для сохранения файлов с логами.
 @throw std::runtime_error В случае, если по переданному пути лежит не директория.
 */
void FileLogger::setOutputDirectory(const fs::path& dir) {
    // Проверить что передали именно директорию
    // Если ее не существует -- создать
    
    bool exists = fs::exists(dir);
    bool is_dir = fs::is_directory(dir);
    
    if (exists && !is_dir) {
        std::string error_message = std::string(dir) + " is not a directory.";
        throw std::runtime_error(error_message);
    }
    
    m_dir = dir;
    m_dir_exists = exists;
}



/*!
 Формирует имя файла.
 @return Имя файла.
 */
std::string FileLogger::makeFileName(time_t timestamp) const {
    return m_prefix + std::to_string(timestamp) + ".log";
}


/*!
 Осуществляет запись сообщение от Publisher в лог-файл.
 @param message сообщение от Publisher.
 @throw std::runtime_error В случае, когда не удалось создать директорию для записи лог-файлов.
 */
void FileLogger::update(const std::string& message, time_t timestamp) {
    if (!m_dir_exists) {
        m_dir_exists = fs::create_directory(m_dir);
        if (!m_dir_exists) {
            std::string error_message = "Failed to create a directory ";
            error_message += fs::absolute(m_dir);
            throw std::runtime_error(error_message);
        }
    }
        
    File file(m_dir / makeFileName(timestamp));
    file.write(prepare(message));
}
