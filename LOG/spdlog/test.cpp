#include "log.h"
 

void test()
{
}

int main()
{
	Hlog log;
	log.Init(".log/test.log", 1024*1024*1000, 10, 
			   Hlog::SYNC, Hlog::CONSOLE_AND_FILE, Hlog::LEVEL_WARN);
 
	LOG_TRACE("test {}", 1);
	LOG_DEBUG("test {:.2f}", 1.0000);
	LOG_INFO("test {}", 1.23456789);
	LOG_WARN("test {}", 'A');
	LOG_ERROR("test {}", "ABC");
	LOG_CRITI("test {}", std::string("abc"));
 
	return 0;
}