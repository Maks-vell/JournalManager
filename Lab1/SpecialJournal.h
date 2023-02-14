#pragma once

#include "Journal.h"

class SpecialJournal : public Journal
{

protected:
	wchar_t* special_info;

public:
	SpecialJournal(const wchar_t autor_[STDBUF_SIZE] = NULL, const wchar_t name_[STDBUF_SIZE] = NULL,
		ThemeEnum::Theme theme_ = ThemeEnum::Theme::OTHER, int circulation_ = 0, int release_year_ = -1,
		const wchar_t special_info_[STDBUF_SIZE] = NULL);

	SpecialJournal(SpecialJournal& journal_copy);

	~SpecialJournal();

	void Input();

	void Output();

	void Serialize(wchar_t* buf) override;

	void Deserialize(const wchar_t* buf) override;

};