#pragma once

#include <iostream>

#include "LogEntry.h"


using namespace std;

class FileStorage
{
	public :
		static void saveFile(const vector<LogEntry>& entries, const string& key, const string& path);
		static vector<LogEntry> loadFile(const string& key, const string& path);
};

