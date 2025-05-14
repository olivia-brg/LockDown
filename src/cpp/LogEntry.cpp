#include <sstream>
#include <iostream>

#include "../headers/LogEntry.h"


LogEntry::LogEntry(string site, string username, string password)
    : m_site{	  move(site)	 },
      m_username{ move(username) },
      m_password{ move(password) } {}

const string LogEntry::getSite()	  const { return m_site; }
const string LogEntry::getUsername() const { return m_username; }
const string LogEntry::getPassword() const { return m_password; }

void LogEntry::setPassword(const string& newPassword) { m_password = newPassword; }
void LogEntry::setUsername(const string& newUsername) { m_username = newUsername; }
void LogEntry::setSite    (const string& newSite)	   { m_site = newSite; }

string LogEntry::serialize() const {
	stringstream ss;
	ss << m_site	 << ";"
	   << m_username << ";"
	   << m_password;
	return ss.str();
}

LogEntry LogEntry::deserialize(const string& ligne) {

	stringstream ss(ligne);
	string site, user, pass;

	getline(ss, site, ';');
	getline(ss, user, ';');
	getline(ss, pass, ';');

	return LogEntry(trim(site), trim(user), trim(pass));
}

string LogEntry::trim(const string& str) {
	size_t start = 0;
	size_t end = str.size();

	while (start < str.size() && isspace(static_cast<unsigned char>(str[start]))) ++start;
	while (end > start && isspace(static_cast<unsigned char>(str[end - 1]))) --end;

	return str.substr(start, end - start);
}

ostream& operator<<(ostream& flux, LogEntry const& LogEntry) {
	return flux << "Libelle : "		 << LogEntry.m_site
				<< "\t| Username : " << LogEntry.m_username
				<< "\t| Password : " << LogEntry.m_password << endl;
}

