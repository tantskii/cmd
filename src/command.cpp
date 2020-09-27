#include "command.h"


/*!
 Конструктор класса Команды.
 @param value Название команды.
 */
Command::Command(std::string value)
    : m_value(value)
    , m_timestamp(std::time(nullptr))
{}


/*!
 Исполняет команду.
 @return Название команды.
 */
std::string Command::execute() const {
    return m_value;
}


/*!
 Возвращает время создания команды.
 @return Временная метка создания команды.
 */
time_t Command::getTimestamp() const {
    return m_timestamp;
}


/*!
 Выводит команду в поток вывода.
 @return Ссылка на поток вывода.
 */
std::ostream& operator<<(std::ostream& os, const Command& command) {
    os << command.m_value;
    return os;
}


/*!
 Считывает команду из потока ввода.
 @return Ссылка на поток ввода.
 */
std::istream& operator>>(std::istream& is, Command& command) {
    std::getline(is, command.m_value);
    return is;
}
