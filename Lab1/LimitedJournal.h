#pragma once

#include "Journal.h"


class LimitedJournal : public Journal
{

private:
	int limited_edition;

public:
	LimitedJournal(const wchar_t autor_[STDBUF_SIZE] = NULL, const wchar_t name_[STDBUF_SIZE] = NULL,
		ThemeEnum::Theme theme_ = ThemeEnum::Theme::OTHER, int circulation_ = 0, int release_year_ = -1,
		int limited_edition_ = -1);

	LimitedJournal(LimitedJournal& journal_copy);

	~LimitedJournal();

	void Input();

	void Output();

	void Serialize(wchar_t* buf) override;

	void Deserialize(const wchar_t* buf) override;

};