#include "bulk.h"

/*!
 Добавляет логгера.
 @param observer Указатель на логгер.
 */
void Bulk::attach(ISubscriberPtr observer) {
    m_obervers.push_back(std::move(observer));
}


/*!
 Передает всем логгерам (подписчикам) информацию для сохранения.
 @param message Сообщение.
 @param timestamp Метка времени.
 */
void Bulk::notify(const std::string& message, time_t timestamp) const {
    for (const ISubscriberPtr& observer: m_obervers) {
        observer->update(message, timestamp);
    }
}


/*!
 Получает от  парсера (компонента) командный блок и выполняет его.
 @param block  Указатель на командный блок.
 */
void Bulk::notify(CommandBlockPtr block) const {
    notify(block->execute(), block->getCommands().front().getTimestamp());
}
