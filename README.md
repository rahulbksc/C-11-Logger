# C-11-Logger
Thread-safe Simple logger utility which accepts different targets (file , db , std , etc)  by means of callbacks. 

Requirement was to send log messages on DB (redis or mysql, files and std-out).

usage: 
  
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
  
  P.S. This is currently at very early stage.
  
  
