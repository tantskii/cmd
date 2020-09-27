/*!
 @file
 @brief Заголовочный файл, содержит объявление класса команды.
 */

#pragma once
#include <string>
#include <iostream>
#include <ctime>


/*!
 Класс Команда.
 */
class Command {
public:
    Command(std::string value);
    std::string execute() const;  //< Выполняет команду.
    time_t getTimestamp() const;  //< Возвращает временную метку создания команды.
    
    friend std::ostream& operator<<(std::ostream&, const Command&); ///< Выводит команду в поток вывода.
    friend std::istream& operator>>(std::istream&,       Command&); ///< Считывает каманду из потока ввода.
private:
    std::string m_value; ///< Хранит название команды.
    time_t m_timestamp;  ///< Хранит временную метку создания команды.
};

