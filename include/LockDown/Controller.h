#pragma once
#include <string>

using namespace std;

class Controller
{
	public:
		Controller(string key);
		void start();

	private:
		string m_key;
		string m_path;
};

