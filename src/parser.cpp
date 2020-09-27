#include "parser.h"

/*!
 Конструирует парсер. По умолчанию в m_handler кладется обработчик распределения состояния.
 */
Parser::Parser()
    : m_handler(std::make_unique<StateDistributionHandler>())
{}


/*!
 Задает максимальный размер статического блока команд.
 @param static_block_size Максимальный размер статического блока команд.
 */
void Parser::setStaticBlockSize(size_t static_block_size) {
    m_capacity = static_block_size;
}


/*!
 Устанавливает обработчик команд.
 @param handler  Указатель на базовый класс обработчика.
 */
void Parser::setHandler(IHandlerPtr handler) {
    m_handler = std::move(handler);
}


/*!
 Парсит данные из входного потока.
 @param stream Входной поток данных.
 */
void Parser::parse(std::istream& stream) {
    while (!stream.eof()) {
        m_handler->parse(*this, stream);
    }
}


/*!
 Создает обработчик распределения состояния.
 @return Указатель на статический обработчик команд.
 */
std::unique_ptr<StateDistributionHandler> Parser::createStateDistributionHandler() const {
    return std::make_unique<StateDistributionHandler>();
}


/*!
 Создает обработчик статического блока команд.
 @return Указатель на статический обработчик команд.
 */
std::unique_ptr<StaticCommandBlockHandler> Parser::createStaticCommandBlockHandler() const {
    return std::make_unique<StaticCommandBlockHandler>(m_capacity);
}


/*!
 Создает обработчик динамического блока команд.
 @return Указатель на динамический обработчик команд.
 */
std::unique_ptr<DynamicCommandBlockHandler> Parser::createDynamicCommandBlockHandler() const {
    return std::make_unique<DynamicCommandBlockHandler>();
}


/*!
 Передает указатель на командный блок в медиатор.
 */
void Parser::pass(CommandBlockPtr block) const {
    m_mediator->notify(std::move(block));
}


/*!
 Определяет тип следующего командного блока и передает ему выполнение обработки.
 @param parser Сслыка на парсер.
 @param stream  Ссылка на входной поток данных.
 */
void StateDistributionHandler::parse(Parser& parser, std::istream& stream) {
    /*
     * 1. Если перый символ это '{' -- следющий блок является динамическим;
     * 2. В противном случае        -- следющий блок является статическим;
     */

    char ch;
    stream >> ch;
    
    switch (ch) {
        case '{':
            // п. 1
            stream.putback('{');
            parser.setHandler(parser.createDynamicCommandBlockHandler());
            break;
        default:
            // п. 2
            stream.putback(ch);
            parser.setHandler(parser.createStaticCommandBlockHandler());
            break;
    }
}


/*!
 Конструктор обработчика статического блока команд.
 @param capacity Максимальный размер статического блока команд.
 */
StaticCommandBlockHandler::StaticCommandBlockHandler(size_t capacity)
    : m_capacity(capacity)
{}


/*!
 Обрабатывает входной поток.
 @param parser Ссылка на парсер.
 @param stream Ссылка  на входной поток данных.
 */
void StaticCommandBlockHandler::parse(Parser& parser, std::istream& stream) {
    StaticCommandBlockPtr block = std::make_unique<StaticCommandBlock>(m_capacity);
    std::string input;
    bool next_dynamic = false;

    while (!next_dynamic && !block->isFulled() && std::getline(stream, input)) {
        if (input == "{") {
            stream.putback('\n');
            stream.putback('{');
            next_dynamic = true;
        } else {
            block->addCommand({std::move(input)});
        }
    }
    
    if (next_dynamic) {
        parser.setHandler(parser.createDynamicCommandBlockHandler());
    } else {
        parser.setHandler(parser.createStateDistributionHandler());
    }
    
    parser.pass(std::move(block));
}

/*!
 Обрабатывает входной поток.
 @param parser Ссылка на парсер.
 @param stream Ссылка  на входной поток данных.
 */
void DynamicCommandBlockHandler::parse(Parser& parser, std::istream& stream) {
    DynamicCommandBlockPtr block = std::make_unique<DynamicCommandBlock>();
    std::string input;
    size_t counter = 0;
    bool stop = false;
    
    while (!stop && std::getline(stream, input)) {
        if (input == "{") {
            ++counter;
        } else if (input == "}") {
            --counter;
        } else {
            block->addCommand({std::move(input)});
        }
        
        stop = counter == 0;
    }
    
    // Если данные закончились внутри динамического блока,
    // весь динамический блок игнорируется.
    if (counter > 0) {
        return;
    }
    
    parser.pass(std::move(block));
    parser.setHandler(parser.createStateDistributionHandler());
}
