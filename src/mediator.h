/*!
 @file
 @brief Заголовочный файл, содержит объявление интерфейсов шаблона Mediator.
 */

#pragma once
#include "command_block.h"
#include <memory>

class IComponent;
class IMediator;

using IComponentPtr = std::unique_ptr<IComponent>; ///< Указатель на Component.
using IMediatorPtr  = std::shared_ptr<IMediator>;  ///< Указатель на Mediator.


/*!
 Интерфейс медиатора.
 */
class IMediator {
public:
    virtual ~IMediator() = default;
    virtual void notify(CommandBlockPtr) const = 0; ///< Получение командного блока от компонента.
};


/*!
 Интерфейс компонента.
 */
class IComponent {
public:
    virtual ~IComponent() = default;
    void setMediator(IMediatorPtr); ///< Установка медиатора.
protected:
    IMediatorPtr m_mediator = nullptr;
};
