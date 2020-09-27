#include "command_block.h"
#include "logger.h"
#include "parser.h"
#include "bulk.h"
#include "log_dir.h"
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        throw std::runtime_error("Pass size of static command block as an argument");
    }
    
    const int StaticBlockSize = std::stoi(argv[1]);
    
//    std::istringstream input;
//    input.str("cmd1\ncmd2\n{\ncmd3\ncmd4\n}\n{\ncmd5\ncmd6\n{\ncmd7\ncmd8\n}\ncmd9\n}\n{\ncmd10\ncmd11\n");
    
    auto bulk = std::make_shared<Bulk>();
    
    
    auto logger_1 = std::make_shared<OStreamLogger>(std::cout);
    logger_1->setPrefix("bulk");
    
    
    auto logger_2 = std::make_shared<FileLogger>();
    logger_2->setPrefix("bulk");
    logger_2->setOutputDirectory(LOG_DIRECTORY);
    
    
    bulk->attach(logger_1);
    bulk->attach(logger_2);
    
    Parser parser;
    parser.setStaticBlockSize(StaticBlockSize);
    parser.setMediator(bulk);
    
    parser.parse(std::cin);
    
    return 0;
}
