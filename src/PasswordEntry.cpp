#include <sstream>
#include <iostream>

#include "LockDown/PasswordEntry.h"

PasswordEntry::PasswordEntry(const string& site, const string& username, const string& password)
	: m_site{ site }, m_username{ username }, m_password{ password } {};

string PasswordEntry::getSite() const { return m_site; }

string PasswordEntry::getUsername() const {	return m_username; }

string PasswordEntry::getPassword() const {	return m_password; }

void PasswordEntry::setPassword(const string& newPassword) {
	m_password = newPassword;
}

string PasswordEntry::serialize() const {
	stringstream ss;
	ss << m_site << ";" << m_username << ";" << m_password << endl;
	return ss.str();
}

PasswordEntry PasswordEntry::deserialize(const string& ligne) {

	stringstream ss(ligne);
	//cout << "[DEBUG] chiffre : " << ligne << endl;
	string site, user, pass;

	getline(ss, site, ';');
	getline(ss, user, ';');
	getline(ss, pass, ';');
	//if (site.empty())
	//	cout << "[DEBUG] site empty" << endl;
	//else
	//	cout << "[DEBUG] site : " << site << endl;
	//if (user.empty())
	//	cout << "[DEBUG] user empty" << endl;
	//else
	//	cout << "[DEBUG] user : " << user << endl;
	//if (pass.empty())
	//	cout << "[DEBUG] pass empty" << endl;
	//else
	//	cout << "[DEBUG] pass : " << pass << endl;

	return PasswordEntry(site, user, pass);
}

ostream& operator<<(ostream& flux, PasswordEntry const& passwordEntry) {
	return flux << "Site : \n" << passwordEntry.m_site << "\n\n"
				<< "Username : \n" << passwordEntry.m_username << "\n\n"
				<< "Password : \n" << passwordEntry.m_password << endl;
}
