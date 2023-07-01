#pragma once
#include <string> // TODO: use char*
#include <vector>
#include <map>
#include <Windows.h>

namespace ali
{
	using namespace std;
	namespace saved {
		string deafultvariablesection = "Variables";

		string iniPath() {
			TCHAR buffer[MAX_PATH] = { 0 };
			GetModuleFileName(NULL, buffer, MAX_PATH);
			wstring wstr = wstring(buffer);
			string ret = string(wstr.begin(), wstr.end());
			size_t pos = ret.find_last_of("\\/");
			return ret.substr(0, pos);
		}


		namespace raw {
			string to_str(wstring wstr)
			{
				return string(wstr.begin(), wstr.end());
			}

			wstring to_wstr(string str)
			{
				return wstring(str.begin(), str.end());
			}
			void writeFile(string section, string variable, string value, string path = iniPath() + "\\settings.ini") {
				WritePrivateProfileString(to_wstr(section).c_str(), to_wstr(variable).c_str(), to_wstr(value).c_str(), to_wstr(path).c_str());
			}
			string readFile(string section, string variable, string path = iniPath() + "\\settings.ini") {
				wchar_t txt[500];
				GetPrivateProfileString(to_wstr(section).c_str(), to_wstr(variable).c_str(), NULL, txt, ARRAYSIZE(txt), to_wstr(path).c_str());
				wstring ws(txt);
				return string(ws.begin(), ws.end());
			}
		}

		namespace mirror {
			class variable
			{
			public:
				variable(string name, string value = "", string path = iniPath() + "\\settings.ini")
				{
					string x = raw::readFile(deafultvariablesection, name);
					if (value != "") {
						this->name = name;
						this->value = value;
						this->path = path;
						set(value);
					}
					else {
						this->name = name;
						this->value = x;
						this->path = path;
					}
				}
				~variable() {}

				void set(string value)
				{
					raw::writeFile(deafultvariablesection, name, value, path);
					this->value = value;
				}
				string get()
				{
					return value;
				}
				void operator=(const string& val) {
					raw::writeFile(deafultvariablesection, name, val, path);
					value = val;
				}
				operator std::string const()
				{
					return value;
				}
			private:
				string path;
				string name;
				string value;
			};
			class vector
			{
			public:
				vector(string name) {
					this->name = name;
					string x = raw::readFile(name, "size");
					try {
						p_size = std::stoi(x);
					}
					catch (...) {
						raw::writeFile(name, "size", "0");
						p_size = 0;
					}
					for (size_t i = 0; i < p_size; i++)
					{
						vec.push_back(raw::readFile(name, to_string(i)));
					}
				}
				~vector() {}
				void push_back(string element)
				{
					raw::writeFile(name, "size", to_string(p_size + 1));
					raw::writeFile(name, to_string(p_size), element);
					vec.push_back(element);
					p_size++;
				}
				std::string operator [](const size_t& index) {
					return vec[index];
				}
				void operator+=(string element) {
					push_back(element);
				}
				size_t size() { return p_size; }
			private:
				string name;
				size_t p_size;
				std::vector<string> vec;
			};
		}

		class variable
		{
		public:
			variable(string name, string value = "", string path = iniPath() + "\\settings.ini")
			{
				string x = raw::readFile(deafultvariablesection, name);
				if (value != "") 
					set(value);
				this->name = name;
				this->path = path;
			}
			~variable() {}

			void set(string value)
			{
				raw::writeFile(deafultvariablesection, name, value, path);
			}
			string get()
			{
				return raw::readFile(deafultvariablesection, name, path);
			}
			void operator=(const string& val) {
				raw::writeFile(deafultvariablesection, name, val, path);
			}
			operator std::string const()
			{
				return raw::readFile(deafultvariablesection, name, path);
			}
		private:
			string path;
			string name;
		};
		class vector
		{
		public:
			vector(string name) {
				this->name = name;
				string x = raw::readFile(name, "size");
				try {
					p_size = std::stoi(x);
				}
				catch (...) {
					raw::writeFile(name, "size", "0");
					p_size = 0;
				}
			}
			~vector(){}
			void push_back(string element)
			{
				raw::writeFile(name, "size", to_string(p_size+1));
				raw::writeFile(name, to_string(p_size), element);
				p_size++;
			}
			std::string operator [](const size_t& index) {
				return raw::readFile(name, to_string(index));
			}
			size_t size() { return p_size; }
		private:
			string name;
			size_t p_size;
		};
		class map // Currently not supported in ali::saved::mirror
		{
		public:
			map(string name, string path = iniPath() + "\\settings.ini") {
				this->name = name;
			}
			~map(){}

			string operator[] (string key) const
			{
				return raw::readFile(name, key);
			}

			void addelement(string key, string value)
			{
				raw::writeFile(name, key, value);
			}
		private:
			string name;
			string path;
		};

	}
}