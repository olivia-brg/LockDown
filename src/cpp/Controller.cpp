#include "../headers/Controller.h"
#include "../headers/LogEntry.h"
#include <string>
#include <iostream>

Controller::Controller(const UserAccount& user) {
	start(user);
}

void Controller::start(const UserAccount& user) {
    Vault vault(user);
    bool running = true;

    while (running) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore();
        handleChoice(choice, vault, running);
    }
}


void Controller::showMenu() const {
    cout << "\n=== MENU ===\n";
    cout << "1. Ajouter une entree\n";
    cout << "2. Supprimer une entree\n";
    cout << "3. Modifier un mot de passe\n";
    cout << "4. Modifier un nom d'utilisateur\n";
    cout << "5. Modifier un libelle\n";
    cout << "6. Afficher tout\n";
    cout << "7. Rechercher un site grace au libelle\n";
    cout << "8. Sauvegarder\n";
    cout << "0. Quitter\n";
    cout << "Choix : " ;
    
}

void Controller::handleChoice(int choice, Vault& vault, bool& running) const {
    string site, user, pass, oldSite;

    switch (choice) {
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
        vault.searchLogEntry(site);
        break;
    case 8:cout << "Sauvegarde" << endl;
        vault.save();
        break;
    case 0:
        running = false;
        vault.save();
        break;
    default:
        cout << "Choix invalide.\n";
    }

    cout << "\nAppuyez sur Entree pour continuer...";
    cin.get();
}