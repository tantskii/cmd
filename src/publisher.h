/*!
 @file
 @brief Заголовочный файл, содержит объявление интерфейсов шаблона Publisher-Subscriber.
 */

#pragma once
#include "string"
#include <ctime>
#include <memory>

class ISubscriber;
class IPublisher;

using ISubscriberPtr = std::shared_ptr<ISubscriber>; ///< Указатель на Subscriber'a.
using IPublisherPtr  = std::shared_ptr<IPublisher>;   ///< Указатель на Publisher'a.


/*!
 Интерфейс Subscriber'a.
 */
class ISubscriber {
public:
    virtual ~ISubscriber() = default;
    virtual void update(const std::string&, time_t) = 0; ///< Принимает сообщение от Publisher'a.
};


/*!
 Интерфейс Publisher'a.
 */
class IPublisher {
public:
    virtual ~IPublisher() = default;
    virtual void attach(ISubscriberPtr observer) = 0; ///< Добавляет Subscriber'a.
    virtual void notify(const std::string&, time_t) const = 0; ///< Передает сообщение подписчикам.
};
