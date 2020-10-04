#include "mediator.h"

/*!
 Устанавливает медиатор (контроллер).
 @param mediator Указатель на медиатор.
 */
void Component::setMediator(MediatorPtr mediator) {
    m_mediator = mediator;
}
