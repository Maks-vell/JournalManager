#include "PsuJournal.h"

#include "util.h"

PsuJournal::PsuJournal(const wchar_t autor_[STDBUF_SIZE], const wchar_t name_[STDBUF_SIZE],
                       ThemeEnum::Theme theme_, int circulation_, int release_year_, const wchar_t special_info_[STDBUF_SIZE],
                       const wchar_t faculty_[STDBUF_SIZE]) :
	SpecialJournal(autor_, name_, theme_, circulation_, release_year_, special_info_)
{
	this->faculty = new wchar_t[STDBUF_SIZE];
	if (faculty_ != NULL)
	{
		for (int i = 0; i < wcslen(faculty_) + 1; i++)
		{
			this->faculty[i] = faculty_[i];
		}
	}
	else
	{
		wchar_t unknown[] = L"Unknown";

		memcpy(this->faculty, unknown, std::wcslen(unknown) * sizeof(wchar_t));
	}
}

PsuJournal::PsuJournal(PsuJournal& journal_copy) :SpecialJournal(journal_copy)
{
	this->faculty = new wchar_t[STDBUF_SIZE];
	for (int i = 0; i < wcslen(journal_copy.faculty) + 1; i++)
	{
		this->faculty[i] = journal_copy.faculty[i];
	}
}


PsuJournal::~PsuJournal()
{
	delete this->faculty;
}


void PsuJournal::Input() {
	this->SpecialJournal::Input();

	std::wcout << L"Enter Faculty (string): ";
	util::CleanWcin();
	std::wcin.getline(this->faculty, STDBUF_SIZE);
}

void PsuJournal::Output()
{
	this->SpecialJournal::Output();

	std::wcout << L"Faculty - " << this->faculty << std::endl;
}

void PsuJournal::Serialize(wchar_t* buf)
{
	Json::SetJsonBeginTag(buf, L"PsuJournal");

	Json::SetJsonValue(buf, L"name", this->name);
	Json::SetJsonValue(buf, L"autor", this->autor);
	Json::SetJsonValue(buf, L"theme", ThemeEnum::to_wchars(this->theme));
	Json::SetJsonValue(buf, L"circulation", util::to_wstring(this->circulation).c_str());
	Json::SetJsonValue(buf, L"release_year", util::to_wstring(this->release_year).c_str());
	Json::SetJsonValue(buf, L"special_info", this->special_info);
	Json::SetJsonValue(buf, L"faculty", this->faculty);

	Json::SetJsonEndTag(buf);
}


void PsuJournal::Deserialize(const wchar_t* buf)
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

	std::wstring value4 = Json::GetJsonValue(buf_str, L"faculty").c_str();
	wcscpy(this->faculty, value4.c_str());
}