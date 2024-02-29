#include <iostream>
#include "include/ClassExample.h"
#include "LoggerDll/Logger.h"

int main(int argc, char* argv[]) {

	ClassExample ce;
	ce.print();
	ce.set(1);
	ce.print();
	ce.setAndPrint(11);
	KOD::Logger log;
	log.log(KOD::Logger::LogSeverity::DEBUG, "TEST LOG CMAKE");
	log.stop();
	return 0;
}