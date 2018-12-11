#include "logger.h"

int main()
{

	initLogger("info.txt", "warning.txt", "error.txt");

	//LOG(TYPE) << "your info";
	LOG(ERROR) << "this is test";
	LOG(INFO) << "this is the log system test";
	return 0;
}
