#pragma once
#include <string>
#include "./CryptoAES.h"

using namespace std;

class UserAccount {
	public:
		UserAccount();
		UserAccount(string username, string password);

		string getPassword() const;
		void setPassword(string password);

		string getUsername() const;
		void setUsername(string username);

	private:
		string m_username;
		string m_password;
};