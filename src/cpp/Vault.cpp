#include "../headers/Vault.h"
#include "../headers/FileStorage.h"

Vault::Vault(const UserAccount& user)
	: m_user{user}
{
	m_entries = FileStorage::loadFile(m_user);
}

Vault::~Vault() { save(); }

void Vault::addLogEntry(const string& site, const string& username, const string& password) {
	LogEntry newEntry(site, username, password);
	m_entries.emplace_back(newEntry);
}

void Vault::removeLogEntry(const string& site) {
	auto it = remove_if(m_entries.begin(), m_entries.end(),
		[&site](const LogEntry& entry) { return entry.getSite() == site; });
	m_entries.erase(it, m_entries.end());
}

void Vault::modifySite(const string& oldSite, const string& newSite) {
	for (auto& entry : m_entries) {
		if (entry.getSite() == oldSite) {
			entry.setSite(newSite);
		}
	}
}

void Vault::modifyUsername(const string& site, const string& newUsername) {
	for (auto& entry : m_entries) {
		if (entry.getSite() == site) {
			entry.setUsername(newUsername);
		}
	}
}

void Vault::modifyPassword(const string& site, const string& newPassword) {
	for (auto& entry : m_entries) {
		if (entry.getSite() == site) {
			entry.setPassword(newPassword);
		}
	}
}

void Vault::displayAllEntries() const {
	for (const auto& entry : m_entries) {
		cout << entry << endl;
	}
}

void Vault::searchLogEntry(const string& site) const {
	for (const auto& entry : m_entries) {
		if (entry.getSite() == site) {
			cout << entry << endl;
			return;
		}
	}
	cout << "Aucun site trouvée pour le libelle : " << site << endl;
}

bool Vault::save() const {
	return FileStorage::saveFile(m_entries, m_user);
}

void Vault::load() {
	m_entries = FileStorage::loadFile(m_user);
}

void Vault::clear() {
	m_entries.clear();
}