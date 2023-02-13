#include "limited_journal.h"

LimitedJournal::LimitedJournal(const wchar_t autor_[STDBUF_SIZE], const wchar_t name_[STDBUF_SIZE],
	theme_enum::Theme theme_, int circulation_, int release_year_, int limited_edition_):
Journal(autor_, name_, theme_, circulation_, release_year_)
{
	this->limited_edition = limited_edition_;
}

LimitedJournal::LimitedJournal(LimitedJournal& journal_copy):Journal(journal_copy)
{
	this->limited_edition = journal_copy.limited_edition;
}


LimitedJournal::~LimitedJournal()
{
	this->limited_edition = -1;
}


void LimitedJournal::Input()
{
	this->Journal::Input();

	std::wcout << L"Enter limited edition (number): ";
	std::wcin >> this->limited_edition;
}

void LimitedJournal::Output()
{
	this->Journal::Output();

	std::wcout << L"Limited edition - " << this->limited_edition << std::endl;
}

void LimitedJournal::Serialize(wchar_t* buf)
{
	Json::SetJsonBeginTag(buf, L"LimitedJournal");

	Json::SetJsonValue(buf, L"name", this->name);
	Json::SetJsonValue(buf, L"autor", this->autor);
	Json::SetJsonValue(buf, L"theme", theme_enum::to_wchars(this->theme));
	Json::SetJsonValue(buf, L"circulation", std::to_wstring(this->circulation).c_str());
	Json::SetJsonValue(buf, L"release_year", std::to_wstring(this->release_year).c_str());
	Json::SetJsonValue(buf, L"limited_edition", std::to_wstring(this->limited_edition).c_str());

	Json::SetJsonEndTag(buf);
}

void LimitedJournal::Deserialize(const wchar_t* buf)
{
	std::wstring buf_str = std::wstring(buf);

	std::wstring value1 = Json::GetJsonValue(buf_str, L"autor").c_str();
	wcscpy(this->autor, value1.c_str());

	std::wstring value2 = Json::GetJsonValue(buf_str, L"name").c_str();
	wcscpy(this->name, value2.c_str());

	this->theme = theme_enum::from_wchars(Json::GetJsonValue(buf_str, L"theme").c_str());

	this->circulation = std::stoi(Json::GetJsonValue(buf_str, L"circulation"));

	this->release_year = std::stoi(Json::GetJsonValue(buf_str, L"release_year"));

	this->limited_edition = std::stoi(Json::GetJsonValue(buf_str, L"limited_edition"));
}
