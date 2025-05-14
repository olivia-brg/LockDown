#pragma once
#include <string>

#include "Vault.h"
#include "UserAccount.h"

using namespace std;

class Controller
{
	public:
		Controller(const UserAccount& user);
		void start(const UserAccount& user);

	private:
		void showMenu() const;
		void handleChoice(int choice, Vault& vault, bool& running) const;
};

