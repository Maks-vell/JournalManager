#include "User.h"


User::User(const wchar_t name_[BUFSIZE], const wchar_t pass_[BUFSIZE])
{
	this->name = new wchar_t[BUFSIZE];
	wcscpy(this->name, name_);
	this->pass = new wchar_t[BUFSIZE];
	wcscpy(this->pass, pass_);
}

User::~User()
{
	delete[] this->name;
	delete[] this->pass;
}

void User::Serialize(wchar_t* buf)
{
	Json::SetJsonBeginTag(buf, L"User");

	Json::SetJsonValue(buf, L"name", this->name);
	Json::SetJsonValue(buf, L"pass", this->pass);

	Json::SetJsonEndTag(buf);
}

void User::Deserialize(const wchar_t* buf)
{
	std::wstring buf_str = std::wstring(buf);

	std::wstring value2 = Json::GetJsonValue(buf_str, L"name").c_str();
	wcscpy(this->name, value2.c_str());

	std::wstring value1 = Json::GetJsonValue(buf_str, L"pass").c_str();
	wcscpy(this->pass, value1.c_str());
}