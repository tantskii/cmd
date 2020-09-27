/*!
 @file
 @brief Заголовочный файл, содержащий объявление класса базового блока.
        От этого класса будут унаследованы классы DynamicBlock и StaticBlock.
*/

#pragma once
#include "command.h"
#include <vector>
#include <sstream>

class CommandBlock;
class StaticCommandBlock;
class DynamicCommandBlock;

using CommandBlockPtr        = std::unique_ptr<CommandBlock>;        ///< Указатель на базовый командный блок.
using StaticCommandBlockPtr  = std::unique_ptr<StaticCommandBlock>;  ///< Указатель на статический командный блок.
using DynamicCommandBlockPtr = std::unique_ptr<DynamicCommandBlock>; ///< Указатель на динамический командный блок.

/*!
 @brief Базовй класс блока команд, задачей которого является хранение набора комманд.
 */
class CommandBlock {
public:
    virtual ~CommandBlock() = default;
    virtual void addCommand(const Command&);          ///< Добавляет команду в список команд.
    virtual std::vector<Command> getCommands() const; ///< Возвращает список команд.
    virtual std::string execute() const;              ///< Выполняет блок команд.
    virtual size_t size() const;                      ///< Возвращает количество комманд в блоке.
protected:
    std::vector<Command> m_commands; ///< Набор команд.
};


/*!
 @brief Статический блок команд, который может содержать ровно StaticCommandBlock::m_block_size комманд.
 */
class StaticCommandBlock : public CommandBlock {
public:
    StaticCommandBlock(size_t);    ///< Конструктор статического блока команд.
    void addCommand(const Command&) override; ///< Добавляет команду в список команд.
    bool isFulled() const;                    ///< Проверка на заполенность блока команд.
private:
    size_t m_capacity; ///< Максимальное число хранимых команд.
};


/*!
 @brief Динамический блок команд, который может содержать произваольное число комманд.
 */
class DynamicCommandBlock : public CommandBlock {};
