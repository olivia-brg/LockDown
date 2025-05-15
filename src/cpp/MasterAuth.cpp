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
		string storedUsername;
		string storedPassword;

		if (!getline(ss, storedUsername, ':')) continue;
		if (!getline(ss, storedPassword)) continue;

		if (storedUsername == user.getUsername() && storedPassword == user.getPassword()) {
			m_user = { user.getUsername(), user.getPassword() };
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
        if (getline(ss, existingUser, ';') && existingUser == user.getUsername()) {
			cout << "L'utilisateur existe deja." << endl;
            return false;
        }
    }
    inFile.close();

	
	return FileStorage::saveUser(user, m_path);
}