#include "journal.h"

Journal::Journal(const wchar_t autor_[STDBUF_SIZE], const wchar_t name_[STDBUF_SIZE],
	theme_enum::Theme theme_, int circulation_, int release_year_)
{
	this->theme = theme_;
	this->circulation = circulation_;
	this->release_year = release_year_;

	this->autor = new wchar_t[STDBUF_SIZE];
	if (autor_ != NULL)
	{
		for (int i = 0; i < wcslen(autor_) + 1; i++)
		{
			this->autor[i] = autor_[i];
		}
	}
	else
	{
		wchar_t unknown[] = L"Unknown";

		memcpy(this->autor, unknown, std::wcslen(unknown) * sizeof(wchar_t));
	}

	this->name = new wchar_t[STDBUF_SIZE];
	if (name_ != NULL)
	{
		for (int i = 0; i < wcslen(name_) + 1; i++)
		{
			this->name[i] = name_[i];
		}
	}
	else
	{
		wchar_t unknown[] = L"Unknown";

		memcpy(this->name, unknown, std::wcslen(unknown) * sizeof(wchar_t));
	}

	if (release_year_ < 0)
	{
		release_year = get_current_year();
	}
}

Journal::Journal(Journal& journal_copy)
{
	this->circulation = journal_copy.circulation;
	this->theme = journal_copy.theme;
	this->release_year = journal_copy.release_year;

	this->name = new wchar_t[STDBUF_SIZE];
	for (int i = 0; i < wcslen(journal_copy.name) + 1; i++)
	{
		this->name[i] = journal_copy.name[i];
	}

	this->autor = new wchar_t[STDBUF_SIZE];
	for (int i = 0; i < wcslen(journal_copy.autor) + 1; i++)
	{
		this->autor[i] = journal_copy.autor[i];
	}
}

Journal::~Journal()
{
	delete this->autor;
	delete this->name;
	theme = theme_enum::Theme::OTHER;
	circulation = -1;
	release_year = -1;
}

void Journal::CleanWcin()
{
	if (char(std::wcin.peek()) == '\n')
		std::wcin.ignore();

	if (std::wcin.fail())
	{
		std::wcin.clear();
		std::wcin.ignore(32767, '\n');
	}
}

void Journal::Input()
{
	std::wcout << L"Enter data about this journal \n";

	std::wcout << L"Enter name (string): ";
	CleanWcin();
	std::wcin.getline(this->name, STDBUF_SIZE);


	std::wcout << L"Enter autor (string): ";
	CleanWcin();
	std::wcin.getline(this->autor, STDBUF_SIZE);

	std::wcout << theme_enum::get_description() << L"Enter theme: ";
	wchar_t new_theme[STDBUF_SIZE];
	CleanWcin();
	std::wcin.getline(new_theme, STDBUF_SIZE);
	this->theme = theme_enum::from_wchars(new_theme);

	std::wcout << L"Enter circulation (number): ";
	std::wcin >> this->circulation;

	std::wcout << L"Enter release year (number): ";
	std::wcin >> this->release_year;
}

void Journal::Output()
{
	std::wcout << L"Journal: \n";

	std::wcout << L"Name - " << this->name << std::endl;

	std::wcout << L"Autor - " << this->autor << std::endl;

	std::wcout << L"Theme - " << theme_enum::to_wchars(this->theme) << std::endl;

	std::wcout << L"Circulation - " << this->circulation << std::endl;

	std::wcout << L"Release year - " << this->release_year << std::endl;
}


void Journal::Serialize(wchar_t* buf)
{
	Json::SetJsonBeginTag(buf, L"Journal");

	Json::SetJsonValue(buf, L"name", this->name);
	Json::SetJsonValue(buf, L"autor", this->autor);
	Json::SetJsonValue(buf, L"theme", theme_enum::to_wchars(this->theme));
	Json::SetJsonValue(buf, L"circulation", std::to_wstring(this->circulation).c_str());
	Json::SetJsonValue(buf, L"release_year", std::to_wstring(this->release_year).c_str());

	Json::SetJsonEndTag(buf);
}


void Journal::Deserialize(const wchar_t* buf)
{
	std::wstring buf_str = std::wstring(buf);

	std::wstring value1 = Json::GetJsonValue(buf_str, L"autor").c_str();
	wcscpy(this->autor, value1.c_str());

	std::wstring value2 = Json::GetJsonValue(buf_str, L"name").c_str();
	wcscpy(this->name, value2.c_str());

	this->theme = theme_enum::from_wchars(Json::GetJsonValue(buf_str, L"theme").c_str());

	this->circulation = std::stoi(Json::GetJsonValue(buf_str, L"circulation"));

	this->release_year = std::stoi(Json::GetJsonValue(buf_str, L"release_year"));
}

bool Journal::operator>( const Interface& i2)
{
	const Journal& j2 = (const Journal&) i2;
	return this->circulation > j2.circulation;
}

bool Journal::operator<(const Interface& i2)
{
	const Journal& j2 = (const Journal&)i2;
	return this->circulation < j2.circulation;
}