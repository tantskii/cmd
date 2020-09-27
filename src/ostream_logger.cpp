#include "logger.h"


/*!
 Конструктор ostream-логгера.
 @param stream ссылка на std::ostream.
 */
OStreamLogger::OStreamLogger(std::ostream& stream)
    : m_stream(stream)
{}


/*!
 Записывает сообщение от Publisher в std::ostream.
 @param message Сообщение от Publisher.
 */
void OStreamLogger::update(const std::string& message, time_t timestamp) {
    UNUSED(timestamp);
    m_stream << prepare(message);
}
