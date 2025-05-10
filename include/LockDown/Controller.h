#pragma once
#include <string>

#include "LockDown/Vault.h"

using namespace std;

class Controller
{
	public:
		Controller(string key, string path);
		void start();

	private:
		string m_key;
		string m_path;

		void showMenu() const;
		void handleChoice(int choice, Vault& vault, bool& running) const;
};

