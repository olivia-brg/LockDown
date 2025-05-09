#pragma once

#include <string>
#include "LogEntry.h"

using namespace std;

class Vault {

	public:
		Vault(const string& key, const string& path);
		~Vault();
		void addLogEntry(const string& site, const string& username, const string& password);
		void removeLogEntry(const string& site);
		void modifySite(const string& oldSite, const string& newSite);
		void modifyUsername(const string& site, const string& newUsername);
		void modifyPassword(const string& site, const string& newPassword);

		void displayAllEntries() const;
		void searchPasswordEntry(const string& site) const;
		void save() const;
		void load();
		void clear();

	private:
		string m_key;
		string m_path;
		vector<LogEntry> m_entries;
};