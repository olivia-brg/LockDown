#include "LockDown/MasterAuth.h"

#include <iostream>
#include <vector>
#include <LockDown/FileStorage.h>
#include <LockDown/CryptoAES.h>
#include <fstream>
#include <sstream>



MasterAuth::MasterAuth(string userFilePath) : m_path{ move(userFilePath) } {}

bool MasterAuth::authenticate(const UserAccount& user) {
	ifstream file(m_path);
	if (!file) return false;

	string line;
	string hashed = CryptoAES::hashPassword(user.password);

	while (getline(file, line)) {
		stringstream ss(line);
		UserAccount storedUser;

		if (!getline(ss, storedUser.username, ':')) continue;
		if (!getline(ss, storedUser.password)) continue;


		if (storedUser.username == user.username && storedUser.password == hashed) {
			m_user = { user.username, hashed };
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
        if (getline(ss, existingUser, ';') && existingUser == user.username) {
			cout << "L'utilisateur existe deja." << endl;
            return false;
        }
    }
    inFile.close();

    // Enregistre le nouvel utilisateur
    string hashed = CryptoAES::hashPassword(user.password);
	m_user = { user.username, hashed };
	return FileStorage::saveUser(m_user, m_path);
}