#include "ThemeEnum.h"

ThemeEnum::Theme ThemeEnum::from_wchars(const wchar_t* theme)
{
	if (wcscmp(theme, L"physycs") == 0) return ThemeEnum::PHYSYCS;
	else if (wcscmp(theme, L"chemistry") == 0) return ThemeEnum::CHEMISTRY;
	else if (wcscmp(theme, L"medicine") == 0) return ThemeEnum::MEDICINE;
	else if (wcscmp(theme, L"nature") == 0) return ThemeEnum::NATURE;
	else if (wcscmp(theme, L"computer") == 0) return ThemeEnum::COMPUTER;
	else if (wcscmp(theme, L"astronomia") == 0) return ThemeEnum::ASTRONOMIA;
	else if (wcscmp(theme, L"other") == 0) return ThemeEnum::OTHER;
	else return ThemeEnum::OTHER;
}

const wchar_t* ThemeEnum::to_wchars(ThemeEnum::Theme theme)
{
	if (theme == ThemeEnum::PHYSYCS) return L"physycs";
	else if (theme == ThemeEnum::CHEMISTRY) return L"chemistry";
	else if (theme == ThemeEnum::MEDICINE) return L"medicine";
	else if (theme == ThemeEnum::NATURE) return L"nature";
	else if (theme == ThemeEnum::COMPUTER) return L"computer";
	else if (theme == ThemeEnum::ASTRONOMIA) return L"astronomia";
	else if (theme == ThemeEnum::OTHER) return L"other";
	else return L"other";
}

const wchar_t* ThemeEnum::get_description()
{
	return L" Themes: physycs, chemistry, medicine, nature, computer, astronomia, other \n";
}
