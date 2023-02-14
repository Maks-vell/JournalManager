#pragma once

#include <ctime>
#include <iostream>

#include "Entity.h"
#include "ThemeEnum.h"
#include "Json.h"

#define STDBUF_SIZE 100

class Journal : public Entity
{
public:
	int circulation;

protected:
	wchar_t* name;
	ThemeEnum::Theme theme;
	int release_year;
	wchar_t* autor;


public:
	Journal(const wchar_t autor_[STDBUF_SIZE] = NULL, const wchar_t name_[STDBUF_SIZE] = NULL,
		ThemeEnum::Theme theme_ = ThemeEnum::Theme::OTHER, int circulation_ = 0, int release_year_ = -1);

	Journal(Journal& journal_copy);

	~Journal();

	void Input() override;

	void Output() override;

	void Serialize(wchar_t* buf) override;

	void Deserialize(const wchar_t* buf) override;

	bool operator>(const Entity& i2) override;
	bool operator<(const Entity& i2) override;

protected:
	void CleanWcin();

	int getAge() const
	{
		return get_current_year() - this->release_year;
	}

private:
	static int get_current_year()
	{

		time_t t = time(nullptr);
		tm* now = localtime(&t);

		if (now != nullptr) {
			return now->tm_year;
		}
		else {
			return 0;
		}
	}

};