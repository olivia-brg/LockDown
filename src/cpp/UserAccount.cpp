#include "../headers/UserAccount.h"

UserAccount::UserAccount() {};

UserAccount::UserAccount(string username, string password) 
	: m_username{ move(username) }, m_password{ move(CryptoAES::hashPassword(password)) } {};

string UserAccount::getPassword() const { return m_password; }

void UserAccount::setPassword(string password) {
	m_password = CryptoAES::hashPassword(password);
}

string UserAccount::getUsername() const { return m_username; }

void UserAccount::setUsername(string username) {
	m_username = username;
}