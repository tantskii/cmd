/*!
 @file
 @brief Заголовчный файл к классом, который осуществляет
        контроль взаимодействия других объектов.
 */


#pragma once
#include "publisher.h"
#include "mediator.h"
#include "logger.h"
#include "command_block.h"
#include <vector>
#include <memory>
#include <filesystem>


/*!
 Bulk реализуют логику контроля взаимодействия между парсером и логгерами.
 */
class Bulk : public IPublisher, public Mediator {
public:
    void attach(ISubscriberPtr subscriber) override; ///< Добавлят логгер.
    void notify(const std::string& message, time_t timestamp) const override; ///< Оповещает логгеры о новом событии.
    void notify(CommandBlockPtr block) const override; ///< Получает командный блок от парсера.
private:
    std::vector<ISubscriberPtr> m_obervers; ///< Набор логгеров.
};
