#include <LockDown/Controller.h>
#include <LockDown/MasterAuth.h>
#include <LockDown/CryptoAES.h>
#include <iostream>
#include "../build/MY_GLOBALS_H.h"

const string USER_DB = "users.dat";

int main()
{
    bool authenticated = false;
    MasterAuth auth(USER_DB);
    string username;
    string password;
    string hashedPass;
    UserAccount user;

    while (!authenticated) {

        std::cout << "Nom d'utilisateur : ";
        getline(cin, username);
        std::cout << "Mot de passe maitre : ";
        getline(cin, password);

        hashedPass = CryptoAES::hashPassword(password);
        password = "";
        user.m_username = username;
        user.m_password = hashedPass;

        authenticated = auth.authenticate(user);

        if (!authenticated) {
            std::cout << "Utilisateur inconnu. Creer un nouveau compte ? (y/n) : ";
            string choix;
            getline(cin, choix);

            if (choix == "y" || choix == "Y") {
                if (!auth.registerUser(user)) {
                    cerr << "Erreur : utilisateur deja existant." << endl;
                    return 1;
                }
                std::cout << "Compte cree avec succes.\n";
            }
            else {
                std::cout << "Entrez a nouveau vos identifiants.\n";

            }
        }
        else {
            std::cout << "Authentification reussie.\n";
        }
    }
        Controller controller(hashedPass, user.m_username);
        hashedPass = "";




    return 0;
}