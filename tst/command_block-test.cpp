#include "command_block.h"
#include "gtest/gtest.h"


TEST(CommandBlock, AddCommand) {
    CommandBlock block;
    
    block.addCommand({"cmd1"});
    block.addCommand({"cmd2"});
    
    ASSERT_EQ(block.getCommands()[0].execute(), "cmd1");
    ASSERT_EQ(block.getCommands()[1].execute(), "cmd2");
}


TEST(CommandBlock, Size) {
    CommandBlock block;
    
    block.addCommand({"cmd1"});
    block.addCommand({"cmd2"});
    
    ASSERT_EQ(block.size(), 2);
}


TEST(CommandBlock, Execute) {
    CommandBlock block;
    
    block.addCommand({"cmd1"});
    block.addCommand({"cmd2"});
    
    ASSERT_EQ(block.execute(), "cmd1, cmd2");
}


TEST(CommandBlock, GetCommands) {
    CommandBlock block;
    std::vector<Command> expected_commands = {{"cmd1"}, {"cmd2"}};
    
    block.addCommand({"cmd1"});
    block.addCommand({"cmd2"});
    std::vector<Command> real_commands = block.getCommands();
    
    ASSERT_EQ(real_commands[0].execute(), expected_commands[0].execute());
    ASSERT_EQ(real_commands[1].execute(), expected_commands[1].execute());
}


TEST(CommandBlock, ExecuteEmptyCommandBlock) {
    CommandBlock block;
    
    ASSERT_THROW(block.execute(), std::runtime_error);
}
