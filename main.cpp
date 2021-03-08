
#include <iostream>
#include "logger.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <thread>

int main()
{
    
    auto logger = std::make_shared<user::logger>();

    auto cout_cb = [](const std::string& msg)-> void { std::cout << msg << std::endl; };    

    std::string file_name = "/tmp/sample_log.txt";

    auto file_cb = [ file_name](const std::string& msg)-> void { 
                                                                std::stringstream in_; in_ << msg << std::endl; 
                                                                std::ofstream f(file_name,std::ios::app); 
                                                                f.write(in_.str().data(), in_.str().size());
                                                                };

    logger->RegisterHandler("stdout", cout_cb);
    logger->RegisterHandler("file", file_cb);

    auto producer_thread = [] (std::shared_ptr<user::logger> logger) {

      int count = 100;
      while(count--)
      {
        
        logger->Info("I am writing from writer thread");
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));
      }

    };

    auto worker_thread = [] (std::shared_ptr<user::logger> logger) {

      while(100)
      {
        
        logger->WriteMessage();        
      }

    };    

    std::thread producer(producer_thread, logger);
    std::thread worker(worker_thread, logger);

    user::logger::log_level l{ user::logger::log_level::debug};
    
    logger->SetLogLevel(l);

    logger->Info("Hello logger");
    logger->Info("This is a test");
    logger->Debug("Hope you've written this!");

    producer.join();
    worker.join();

    std::cout << "This is the end of threads" << std::endl;    

    return 0;

}
