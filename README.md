# C-11-Logger
Thread-safe Simple logger utility which accepts different targets (file , db , std , etc)  by means of callbacks. 

Requirement was to send log messages on DB (redis or mysql, files and std-out).

usage: 
  
  logger log;
	auto cb = [](const std::string& msg)-> void
	{
		std::cout << msg << reply << std::endl;		
	};

	log.registerHandler("myLogger", cb);

	user::logger::log_level l{ TDataStore::user::log_level::debug };
	tlogger.setLogLevel(l);

	log.info("Hello logger");
  log.debug("this would be freaking awesome");
	log.deRegisterHandler("myLogger");
	log.debug("I am dead dude");
  
  P.S. This is currently at very early stage.
  
  
