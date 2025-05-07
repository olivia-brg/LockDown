#include <sstream>
#include <iostream>

#include "LockDown/PasswordEntry.h"

PasswordEntry::PasswordEntry(string site, string username, string password)
    : m_site{ move(site) },
      m_username{ move(username) },
      m_password{ move(password) } {}

const string PasswordEntry::getSite()	  const { return m_site; }
const string PasswordEntry::getUsername() const { return m_username; }
const string PasswordEntry::getPassword() const { return m_password; }

void PasswordEntry::setPassword(const string& newPassword) { m_password = newPassword; }

string PasswordEntry::serialize() const {
	stringstream ss;
	ss << m_site << ";" << m_username << ";" << m_password << endl;
	return ss.str();
}

PasswordEntry PasswordEntry::deserialize(const string& ligne) {

	stringstream ss(ligne);
	string site, user, pass;

	getline(ss, site, ';');
	getline(ss, user, ';');
	getline(ss, pass, ';');

	return PasswordEntry(site, user, pass);
}

ostream& operator<<(ostream& flux, PasswordEntry const& passwordEntry) {
	return flux << "Site : " << passwordEntry.m_site << endl
				<< "Username : " << passwordEntry.m_username << endl
				<< "Password : " << passwordEntry.m_password << endl;
}
