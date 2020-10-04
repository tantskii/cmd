#include "logger.h"

/*!
 Устанавливает префикс для сообщений.
 @param prefix Префикс.
 */
void Logger::setPrefix(const std::string& prefix) {
    m_prefix = prefix;
}

/*!
 Добавляет префикс к сообщению.
 @param message Сообщение.
 */
std::string Logger::prepare(const std::string& message) const {
    return m_prefix + ": " + message + "\n";
}

