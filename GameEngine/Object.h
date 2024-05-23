#pragma once
#include <string>


class Object
{
public:
	std::string GetName()
	{
		return m_name;
	}

protected:
	std::string m_name = "";
	int m_instanceID = 0;

};

