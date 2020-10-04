/*!
 @file
 @brief Заголовочный файл, содержит объявление базовых классов шаблона Mediator.
 */

#pragma once
#include "command_block.h"
#include <memory>

class Component;
class Mediator;

using ComponentPtr = std::unique_ptr<Component>; ///< Указатель на Component.
using MediatorPtr  = std::shared_ptr<Mediator>;  ///< Указатель на Mediator.


/*!
 Базовый класс медиатора.
 */
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void notify(CommandBlockPtr) const = 0; ///< Получение командного блока от компонента.
};


/*!
 Базовый класс компонента.
 */
class Component {
public:
    virtual ~Component() = default;
    void setMediator(MediatorPtr); ///< Установка медиатора.
protected:
    MediatorPtr m_mediator = nullptr;
};
