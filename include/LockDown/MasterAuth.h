#pragma once
#include <string>
#include "UserAccount.h"

using namespace std;

class MasterAuth {
	public:
		MasterAuth(string userFilePath);

		bool authenticate(const UserAccount& user);
		bool registerUser(const UserAccount& user);

	private:
		string m_path;
		UserAccount m_user;
};
