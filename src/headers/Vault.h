#pragma once

#include <string>
#include "LogEntry.h"
#include "UserAccount.h"

using namespace std;

class Vault {

	public:
		Vault(const UserAccount& user);
		~Vault();
		void addLogEntry(const string& site, const string& m_username, const string& password);
		void removeLogEntry(const string& site);
		void modifySite(const string& oldSite, const string& newSite);
		void modifyUsername(const string& site, const string& newUsername);
		void modifyPassword(const string& site, const string& newPassword);

		void displayAllEntries() const;
		void searchLogEntry(const string& site) const;
		bool save() const;
		void load();
		void clear();

	private:
		UserAccount m_user;
		vector<LogEntry> m_entries;
};