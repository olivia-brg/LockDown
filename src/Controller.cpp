#include "LockDown/Controller.h"
#include "LockDown/LogEntry.h"
#include "LockDown/Vault.h"
#include <string>
#include <iostream>

Controller::Controller(string key) : m_key{ move(key) } {
    m_path = "vault.dat";
}

void Controller::start() {
    string path; 

    Vault vault(m_key, path);

    bool running = true;
    while (running) {
        cout << "\n=== MENU ===\n";
        cout << "1. Ajouter une entree\n";
        cout << "2. Supprimer une entree\n";
        cout << "3. Modifier un mot de passe\n";
        cout << "4. Modifier un nom d'utilisateur\n";
        cout << "5. Modifier un libelle\n";
        cout << "6. Afficher tout\n";
        cout << "7. Rechercher un site grace au libelle\n";
        cout << "0. Quitter\n";
        cout << "Choix : ";

        int choix;
        cin >> choix;
        cin.ignore();

        string site, user, pass, oldSite;
        switch (choix) {
        case 1:
            cout << "Libelle : ";
            getline(cin, site);
            cout << "Nom d'utilisateur : ";
            getline(cin, user);
            cout << "Mot de passe : ";
            getline(cin, pass);
            vault.addLogEntry(site, user, pass);
            break;
        case 2:
            cout << "Libelle du site a supprimer : ";
            getline(cin, site);
            vault.removeLogEntry(site);
            break;
        case 3:
            cout << "Libelle du site a modifier : ";
            getline(cin, site);
            cout << "Nouveau mot de passe : ";
            getline(cin, pass);
            vault.modifyPassword(site, pass);
            break;
        case 4:
            cout << "Libelle du site a modifier : ";
            getline(cin, site);
            cout << "Nouveau nom d'utilisateur : ";
            getline(cin, user);
            vault.modifyUsername(site, user);
            break;
        case 5:
            cout << "Libelle actuel du site a modifier : ";
            getline(cin, oldSite);
            cout << "Nouveau libelle : ";
            getline(cin, site);
            vault.modifySite(oldSite, site);
            break;
        case 6:
            vault.displayAllEntries();
            break;
        case 7:
            cout << "Libelle a rechercher : ";
            getline(cin, site);
            vault.searchPasswordEntry(site);
            break;
        case 0:
            running = false;
            break;
        default:
            cout << "Choix invalide.\n";
        }
    }
}