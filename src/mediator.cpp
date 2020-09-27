#include "mediator.h"

/*!
 Устанавливает медиатор (контроллер).
 @param mediator Указатель на медиатор.
 */
void IComponent::setMediator(IMediatorPtr mediator) {
    m_mediator = mediator;
}
