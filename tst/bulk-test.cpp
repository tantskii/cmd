#include "parser.h"
#include "bulk.h"
#include "gtest/gtest.h"
#include <sstream>


TEST(Bulk, StaticBlockExample) {
    size_t static_block_size = 3;
    std::istringstream is;
    std::ostringstream os;
    auto bulk   = std::make_shared<Bulk>();
    auto logger = std::make_shared<OStreamLogger>(os);
    auto parser = Parser();
    std::string input = "cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n";
    std::string output = "bulk: cmd1, cmd2, cmd3\nbulk: cmd4, cmd5\n";
    
    logger->setPrefix("bulk");
    bulk->attach(logger);
    is.str(input);
    parser.setMediator(bulk);
    parser.setStaticBlockSize(static_block_size);
    
    parser.parse(is);
    
    ASSERT_EQ(output, os.str());
}


TEST(Bulk, DynamicBlockExample) {
    size_t static_block_size = 3;
    std::istringstream is;
    std::ostringstream os;
    auto bulk = std::make_shared<Bulk>();
    auto logger = std::make_unique<OStreamLogger>(os);
    auto parser = Parser();
    std::string input = "cmd1\ncmd2\n{\ncmd3\ncmd4\n}\n{\ncmd5\ncmd6\n{\ncmd7\ncmd8\n}\ncmd9\n}\n{\ncmd10\ncmd11\n";
    std::string output = "bulk: cmd1, cmd2\nbulk: cmd3, cmd4\nbulk: cmd5, cmd6, cmd7, cmd8, cmd9\n";
    
    
    logger->setPrefix("bulk");
    bulk->attach(std::move(logger));
    is.str(input);
    parser.setMediator(bulk);
    parser.setStaticBlockSize(static_block_size);
    
    parser.parse(is);
    
    ASSERT_EQ(output, os.str());
}
