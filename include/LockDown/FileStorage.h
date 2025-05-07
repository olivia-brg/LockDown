#pragma once

#include <iostream>

#include "PasswordEntry.h"


using namespace std;

class FileStorage
{
	public :
		static void saveFile(const vector<PasswordEntry>& entries, const string& key, const string& path);
		static vector<PasswordEntry> loadFile(const string& key, const string& path);
};

