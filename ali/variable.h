#pragma once
#include <string>

namespace ali{
	class variable // A dynamic runtime-evaluated non-type variable type. Currently supports integers, floating point numbers and strings.
	{
	public:
		enum type {
			string,
			integer,
			floating
		};
		variable(std::string value) {
			strType = value;
			type = string;
		}
		variable(int value){
			intType = value;
			type = integer;
		}
		variable(float value) {
			floatType = value;
			type = floating;
		}
		~variable() {
			// For pointer types
		}
		void operator=(std::string x) {
			strType = x;
			type = string;
		}
		void operator=(int x) {
			intType = x;
			type = integer;
		}
		void operator=(float x) {
			floatType = x;
			type = floating;
		}
		operator std::string() const {
			if (type == string)
				return strType;
			else if (type == integer)
				return std::to_string(intType);
			else
				return std::to_string(floatType);
		}
		operator int() const {
			if (type == string)
				return std::stoi(strType);
			else if (type == integer)
				return intType;
			else
				return (int)floatType;
		}
		operator float() const {
			if (type == string)
				return std::stof(strType);
			else if (type == integer)
				return (float)intType;
			else
				return floatType;
		}
		int Number() {
			if (type == integer)
				return intType;
			else if (type == string)
				return std::stoi(strType);
			else
				return (int)floatType;
		}
		float Float() {
			if (type == integer)
				return (float)intType;
			else if (type == string)
				return std::stoi(strType);
			else
				return floatType;
		}
		std::string String()
		{
			if (type == string)
				return strType;
			else if (type == integer)
				return std::to_string(intType);
			else
				return std::to_string(floatType);
		}
		int type = string;
	private:
		std::string strType = "";
		int intType = NULL;
		float floatType = NULL;
	};
}