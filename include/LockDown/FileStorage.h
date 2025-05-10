#pragma once

#include <iostream>

#include "LogEntry.h"
#include "MasterAuth.h"


using namespace std;

class FileStorage
{
	public :
		static bool saveFile(const vector<LogEntry>& entries, const string& key, const string& path);
		static vector<LogEntry> loadFile(const string& key, const string& path);

		static bool saveUser(const UserAccount& user, const string& path);
		static vector<UserAccount> loadUsers(const string& path);
};

