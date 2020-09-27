/*!
 @file
 @brief Заголовочный файл, объявление парсера данных из входного потока, интерфейса обработчика,
        а так же обработчиков статического, динамического и распределительного блоков.
 */

#pragma once
#include "command_block.h"
#include "mediator.h"
#include <string>
#include <iostream>


class Parser;
class IHandler;
class StateDistributionHandler;
class StaticCommandBlockHandler;
class DynamicCommandBlockHandler;

using IHandlerPtr = std::unique_ptr<IHandler>; ///< Сокращение для указателя на базовый класс обработчика.


/*!
 Интерфейс обработчика командного блока.
 */
class IHandler {
public:
    virtual ~IHandler() = default;
    virtual void parse(Parser&, std::istream&) = 0; ///< Обрабатывает данные из входного потока.
};


/*!
 Класс парсера входного потока.
 */
class Parser : public IComponent {
public:
    Parser();                              ///< Конструктор.
    void setStaticBlockSize(size_t);       ///< Задает максимальный размер статического блока команд.
    void parse(std::istream&);             ///< Парсит входной поток.
    void pass(CommandBlockPtr) const;      ///< Передает командный блок медиатору.
    
    void setHandler(IHandlerPtr);          ///< Задает обработчика.
    std::unique_ptr<StateDistributionHandler> createStateDistributionHandler() const;     ///< Создает распределительный обрабочик.
    std::unique_ptr<StaticCommandBlockHandler> createStaticCommandBlockHandler() const;   ///< Создает обработчик статического блока команд.
    std::unique_ptr<DynamicCommandBlockHandler> createDynamicCommandBlockHandler() const; ///< Создает обработчик динамического блока команд.
private:
    IHandlerPtr m_handler;   ///< Указатель на обработчик.
    size_t m_capacity = 3;   ///< Размер статичекого блока команд.
};


/*!
 Обработчик распределения состояния. Его задачей является определение следующего состояния
 и выбор соответсвующего обработчика.
 */
class StateDistributionHandler : public IHandler {
public:
    void parse(Parser&, std::istream&) override; ///< Выбирает следующего обработчика и передает ему входной поток.
};


/*!
 Обработчик статического блока команд.
 */
class StaticCommandBlockHandler : public IHandler {
public:
    StaticCommandBlockHandler(size_t capacity);
    void parse(Parser&, std::istream&) override; ///< Заполняет статический блок команд данными из переданного входного потока.
private:
    const size_t m_capacity; ///< Размер статичекого блока команд.
};


/*!
 Обработчик динамического блока команд.
 */
class DynamicCommandBlockHandler : public IHandler {
public:
    void parse(Parser&, std::istream&) override; ///< Заполняет динамический блок команд данными из переданного входного потока.
};




