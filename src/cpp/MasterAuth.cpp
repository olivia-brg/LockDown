#include "../headers/MasterAuth.h"
#include "../headers/FileStorage.h"
#include "../headers/CryptoAES.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>



MasterAuth::MasterAuth(string userFilePath) : m_path{ move(userFilePath) } {}

bool MasterAuth::authenticate(const UserAccount& user) {
	ifstream file(m_path);
	if (!file) return false;

	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		UserAccount storedUser;

		if (!getline(ss, storedUser.m_username, ':')) continue;
		if (!getline(ss, storedUser.m_password)) continue;

		if (storedUser.m_username == user.m_username && storedUser.m_password == user.m_password) {
			m_user = { user.m_username, user.m_password };
			return true;
		}
	}
	cout << "Nom d'utilisateur ou mot de passe incorrect." << endl;
	return false;
}


bool MasterAuth::registerUser(const UserAccount& user) {
    // Vérifie si déjà existant
    ifstream inFile(m_path);
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string existingUser;
        if (getline(ss, existingUser, ';') && existingUser == user.m_username) {
			cout << "L'utilisateur existe deja." << endl;
            return false;
        }
    }
    inFile.close();

	
	return FileStorage::saveUser(m_user, m_path);
}