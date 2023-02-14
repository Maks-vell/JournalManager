#include "SpecialJournal.h"

SpecialJournal::SpecialJournal(const wchar_t autor_[STDBUF_SIZE], const wchar_t name_[STDBUF_SIZE],
                               ThemeEnum::Theme theme_, int circulation_, int release_year_,
                               const wchar_t special_info_[STDBUF_SIZE]) :
	Journal(autor_, name_, theme_, circulation_, release_year_)
{
	this->special_info = new wchar_t[STDBUF_SIZE];
	if (special_info_ != NULL)
	{
		for (int i = 0; i < wcslen(special_info_) + 1; i++)
		{
			this->special_info[i] = special_info_[i];
		}
	}
	else
	{
		wchar_t unknown[] = L"Unknown";

		memcpy(this->special_info, unknown, std::wcslen(unknown) * sizeof(wchar_t));
	}
}

SpecialJournal::SpecialJournal(SpecialJournal& journal_copy):Journal(journal_copy)
{

	this->special_info = new wchar_t[STDBUF_SIZE];
	for (int i = 0; i < wcslen(journal_copy.name) + 1; i++)
	{
		this->special_info[i] = journal_copy.special_info[i];
	}
}


SpecialJournal::~SpecialJournal()
{
	delete this->special_info;
}


void SpecialJournal::Input()
{
	this->Journal::Input();

	std::wcout << L"Enter special information (string): ";
	CleanWcin();
	std::wcin.getline(this->special_info, STDBUF_SIZE);
}

void SpecialJournal::Output()
{
	this->Journal::Output();

	std::wcout << L"Special information - " << this->special_info << std::endl;
}


void SpecialJournal::Serialize(wchar_t* buf)
{
	Json::SetJsonBeginTag(buf, L"SpecialJournal");

	Json::SetJsonValue(buf, L"name", this->name);
	Json::SetJsonValue(buf, L"autor", this->autor);
	Json::SetJsonValue(buf, L"theme", ThemeEnum::to_wchars(this->theme));
	Json::SetJsonValue(buf, L"circulation", std::to_wstring(this->circulation).c_str());
	Json::SetJsonValue(buf, L"release_year", std::to_wstring(this->release_year).c_str());
	Json::SetJsonValue(buf, L"special_info", this->special_info);

	Json::SetJsonEndTag(buf);
}


void SpecialJournal::Deserialize(const wchar_t* buf)
{
	std::wstring buf_str = std::wstring(buf);

	std::wstring value1 = Json::GetJsonValue(buf_str, L"autor").c_str();
	wcscpy(this->autor, value1.c_str());

	std::wstring value2 = Json::GetJsonValue(buf_str, L"name").c_str();
	wcscpy(this->name, value2.c_str());

	this->theme = ThemeEnum::from_wchars(Json::GetJsonValue(buf_str, L"theme").c_str());

	this->circulation = std::stoi(Json::GetJsonValue(buf_str, L"circulation"));

	this->release_year = std::stoi(Json::GetJsonValue(buf_str, L"release_year"));

	std::wstring value3 = Json::GetJsonValue(buf_str, L"special_info").c_str();
	wcscpy(this->special_info, value3.c_str());
}

