#pragma once
#include <string>
using namespace std;


class UserAccount {
	public:
		UserAccount() {};
		UserAccount(string username, string password) : m_username{ move(username) }, m_password{ move(password) } {};

		string m_username;
		string m_password;

		UserAccount& operator=(const UserAccount& other) {
			
				m_username = other.m_username;
				m_password = other.m_password;
			
			return *this;
		};
};