#include "../headers/Controller.h"
#include "../headers/MasterAuth.h"
#include "../headers/CryptoAES.h"
#include "../headers/UserAccount.h"
#include "../MY_GLOBALS_H.h"
#include <iostream>

const string USER_DB = "users.dat";

int main()
{
    bool authenticated = false;
    MasterAuth auth(USER_DB);
    string username;
    string password;
    UserAccount user;

    while (!authenticated) {

        std::cout << "Nom d'utilisateur : ";
        getline(cin, username);
        std::cout << "Mot de passe maitre : ";
        getline(cin, password);

        
        user.setUsername(username);
        user.setPassword(password);
        password = "";

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
        Controller controller(user);




    return 0;
}