#include "command_block.h"

/*!
 Конструктор статического блока команд.
 @param capacity Максимальный размер  статического блока команд.
 */
StaticCommandBlock::StaticCommandBlock(size_t capacity)
    : m_capacity(capacity)
{}


/*!
 Провекра на заполненность блока команд.
 @return bool true если количество хранимых в блоке комманд равняется максимальному значению.
 */
bool StaticCommandBlock::isFulled() const {
    return m_capacity == m_commands.size();
}


/*!
 Добавление команды в список команд.
 @param command Добавляемая команда.
 @throw std::runtime_error  В случае, если осуществляется попытка добавления комманды в заполенный блок.
 */
void StaticCommandBlock::addCommand(const Command& command) {
    if (isFulled()) {
        std::string error_message;
        error_message += "Attempt to add a command to ";
        error_message += "the completed command block. ";
        error_message += "The max block size is ";
        error_message += std::to_string(m_capacity);
        throw std::runtime_error(error_message);
    }
    
    CommandBlock::addCommand(command);
}
