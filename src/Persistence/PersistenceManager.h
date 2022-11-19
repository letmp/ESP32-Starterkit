#ifndef PERSISTENCE_MANAGER_H
#define PERSISTENCE_MANAGER_H

#include <Arduino.h>
#include "SPIFFS.h"
#include <Streaming.h>

class PersistenceManager
{

private:
	void initSPIFFS();

public:
	PersistenceManager();

	String readFileFromSPIFFS(fs::FS &fs, String path);
	void writeFileToSPIFFS(fs::FS &fs, String path, const char *message);
	void removeFiles();
};

#endif