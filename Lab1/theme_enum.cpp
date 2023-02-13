#include "theme_enum.h"

theme_enum::Theme theme_enum::from_wchars(const wchar_t* theme)
{
	if (wcscmp(theme, L"physycs") == 0) return theme_enum::PHYSYCS;
	else if (wcscmp(theme, L"chemistry") == 0) return theme_enum::CHEMISTRY;
	else if (wcscmp(theme, L"medicine") == 0) return theme_enum::MEDICINE;
	else if (wcscmp(theme, L"nature") == 0) return theme_enum::NATURE;
	else if (wcscmp(theme, L"computer") == 0) return theme_enum::COMPUTER;
	else if (wcscmp(theme, L"astronomia") == 0) return theme_enum::ASTRONOMIA;
	else if (wcscmp(theme, L"other") == 0) return theme_enum::OTHER;
	else return theme_enum::OTHER;
}

const wchar_t* theme_enum::to_wchars(theme_enum::Theme theme)
{
	if (theme == theme_enum::PHYSYCS) return L"physycs";
	else if (theme == theme_enum::CHEMISTRY) return L"chemistry";
	else if (theme == theme_enum::MEDICINE) return L"medicine";
	else if (theme == theme_enum::NATURE) return L"nature";
	else if (theme == theme_enum::COMPUTER) return L"computer";
	else if (theme == theme_enum::ASTRONOMIA) return L"astronomia";
	else if (theme == theme_enum::OTHER) return L"other";
	else return L"other";
}

const wchar_t* theme_enum::get_description()
{
	return L" Themes: physycs, chemistry, medicine, nature, computer, astronomia, other \n";
}
