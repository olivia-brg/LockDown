#pragma once
#include <string>

using namespace std;

class UserAccount {
	public:
		string username;
		string password;

		UserAccount& operator=(const UserAccount& other) {
			if (this != &other) {
				username = other.username;
				password = other.password;
			}
			return *this;
		};
};

class MasterAuth {
	public:
		MasterAuth(string userFilePath);

		bool authenticate(const UserAccount& user);
		bool registerUser(const UserAccount& user);

	private:
		string m_path;
		UserAccount m_user;
};
