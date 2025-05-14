#pragma once

#include <string>
#include <vector>

using namespace std;

class LogEntry {
    public:
        LogEntry(string site, string username, string password);

        const string getSite() const;
        const string getUsername() const;
        const string getPassword() const;

        void setPassword(const string& newPassword);
		void setUsername(const string& newUsername);
		void setSite(const string& newSite);

        string serialize() const;
        static LogEntry deserialize(const string& ligne);

    private:
        string m_site;
        string m_username;
        string m_password;

		static string trim(const string& str);
        friend ostream& operator<<(ostream& flux, LogEntry const& LogEntry);
};

