#include "command_block.h"

/*!
 Добавляет переданную команду в список  комманд
 @param command Добавляемая команда.
 */
void CommandBlock::addCommand(const Command& command) {
    m_commands.push_back(command);
}


/*!
 Возвращает набор команд.
 @return std::vector<Command> Набор комманд.
 */
std::vector<Command> CommandBlock::getCommands() const {
    return m_commands;
}


/*!
 Возвращает размер набора команд.
 @return size_t Количество комманд в блоке.
 */
size_t CommandBlock::size() const {
    return m_commands.size();
}


/*!
 Выполняет поочередно набор команд.
 @return Строка вывода.
 */
std::string CommandBlock::execute() const {
    std::ostringstream ss;
    for (size_t i = 0; i < m_commands.size() - 1; ++i) {
        ss << m_commands[i].execute() << ", ";
    }
    ss << m_commands[m_commands.size() - 1];
    return ss.str();
};
