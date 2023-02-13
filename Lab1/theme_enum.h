#pragma once
#include <iostream> 

namespace theme_enum
{
	enum Theme
	{
		PHYSYCS, CHEMISTRY, MEDICINE, NATURE, COMPUTER, ASTRONOMIA, OTHER
	};

	Theme from_wchars(const wchar_t* theme);
	const wchar_t* to_wchars(Theme theme);
	const wchar_t* get_description();
}


