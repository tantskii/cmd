#include "logger.h"
#include "gtest/gtest.h"
#include <sstream>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;


TEST(OStreamLogger, Update) {
    std::ostringstream stream;
    auto logger = std::make_shared<OStreamLogger>(stream);
    time_t timestamp = 420;
    std::string prefix = "bulk";
    std::string write_message = "message";
    std::string read_message = prefix + ": " + write_message + "\n";
    
    logger->setPrefix(prefix);
    logger->update(write_message, timestamp);
    
    ASSERT_EQ(stream.str(), read_message);
}


TEST(File, Open) {
    fs::path log_dir  = fs::current_path() / "tmp";
    fs::path log_file = log_dir / "logfile.log";
    std::string write_message = "message";
    
    fs::create_directory(log_dir);

    {
        File file(log_file);
        file.write(write_message);
    }
    
    ASSERT_TRUE(fs::exists(log_dir));
    
    fs::remove_all(log_dir);
}


TEST(File, Write) {
    fs::path log_dir  = fs::current_path() / "tmp";
    fs::path log_file = log_dir / "logfile.log";
    std::string write_message = "message";
    std::string read_message;
    
    fs::create_directory(log_dir);

    {
        File file(log_file);
        file.write(write_message);
    }
    
    std::fstream stream(log_file, std::fstream::in);
    std::getline(stream, read_message, '\0');
    
    ASSERT_EQ(write_message, read_message);
    
    fs::remove_all(log_dir);
}


TEST(FileLogger, CreateDirAndFile) {
    fs::path log_dir  = fs::current_path() / "tmp";
    time_t timestamp  = 420;
    std::string prefix = "bulk";
    std::string write_message = "message";
    fs::path log_file = log_dir / (prefix + std::to_string(timestamp) + ".log");
    
    auto logger = std::make_shared<FileLogger>();
    
    logger->setPrefix(prefix);
    logger->setOutputDirectory(log_dir);
    logger->update(write_message, timestamp);
    
    ASSERT_TRUE(fs::exists(log_dir));
    ASSERT_TRUE(fs::is_directory(log_dir));
    ASSERT_TRUE(fs::exists(log_file));
    
    fs::remove_all(log_dir);
}


TEST(FileLogger, Update) {
    fs::path log_dir  = fs::current_path() / "tmp";
    time_t timestamp  = 420;
    std::string prefix = "bulk";
    std::string write_message = "message";
    std::string read_message;
    fs::path log_file = log_dir / (prefix + std::to_string(timestamp) + ".log");
    
    auto logger = std::make_shared<FileLogger>();
    
    logger->setPrefix(prefix);
    logger->setOutputDirectory(log_dir);
    logger->update(write_message, timestamp);
    
    std::fstream stream(log_file, std::fstream::in);
    std::getline(stream, read_message, '\0');
    
    ASSERT_EQ(read_message, "bulk: message\n");
    
    fs::remove_all(log_dir);
}


TEST(FileLogger, PassFileInsteadOfDir) {
    fs::path dirname = fs::current_path() / "tmp";
    fs::path filename = dirname / "file.txt";
    std::string write_message = "I am just a message";
    auto logger = std::make_shared<FileLogger>();
    
    fs::create_directory(dirname);
    {
        File file(filename);
        file.write(write_message);
    }
    
    ASSERT_THROW(logger->setOutputDirectory(filename), std::runtime_error);
    
    fs::remove_all(dirname);
}

