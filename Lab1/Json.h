#pragma once
#include <iostream>
#include <string>

namespace Json
{
	// добавляет значение в json объект
	void SetJsonValue(wchar_t* buf, const wchar_t* name, const wchar_t* value)
	{
		wcscat(buf, name);
		wcscat(buf, L":");
		wcscat(buf, value);
		wcscat(buf, L",");
	}

	// устанавливает метку для определения объекта и его начала
	void SetJsonBeginTag(wchar_t* buf, const wchar_t* tag)
	{
		wcscat(buf, tag);
		wcscat(buf, L":");
		wcscat(buf, L"{");
	}

	// устанавливает метку конца объекта
	void SetJsonEndTag(wchar_t* buf)
	{
		if (buf[wcslen(buf) - 1] == L',')
		{
			buf[wcslen(buf) - 1] = L'\0';
		}

		wcscat(buf, L"}\n");
	}

	// выдает значение указанной переменной из json объекта
	std::wstring GetJsonValue(std::wstring buf_json, const wchar_t* field_name_)
	{
		wchar_t field_name[200];
		wcscpy(field_name, field_name_);
		wcscat(field_name, L":");

		int field_pos = buf_json.find(field_name);
		int value_pos = buf_json.find(L",", field_pos);
		if(value_pos == -1)
		{
			value_pos = buf_json.find(L"}", field_pos);
		}

		return buf_json.substr(field_pos + wcslen(field_name),
			value_pos - (field_pos + wcslen(field_name)));
	}

	// Выдает массив отдельных json объектов из списка
	std::wstring* GetJsonEntitys(std::wstring buf, int& count_ent)
	{
		int count_entitys = 0, open_symbol = 0, close_symbol = 0;

		for (int i = 0; i < buf.length(); i++)
		{
			if (buf[i] == L'{')
			{
				open_symbol++;
			}
			else if (buf[i] == L'}')
			{
				close_symbol++;
			}
		}
		if (open_symbol != close_symbol)
		{
			std::wcout << "Error: Json parsing";
		}
		count_entitys = open_symbol;

		std::wstring* entitys = new std::wstring[count_entitys];

		for (int i = 0; i < count_entitys; i++) {
			int end_pos = buf.find(L"}");
			entitys[i] = buf.substr(0, end_pos + 1);
			buf = buf.substr(end_pos + 2, buf.length() - end_pos);
		}

		count_ent = count_entitys;
		return entitys;
	}

	// получает метку класса json объекта
	std::wstring GetTag(std::wstring buf)
	{
		int end_pos = buf.find(L"{");
		return buf.substr(0, end_pos - 1);
	}

	//	проверяет имеется ли json объект в буфере
	bool isJson(std::wstring buf)
	{
		if (buf.find(L"{") != std::wstring::npos &&
			buf.find(L"}") != std::wstring::npos)
		{
			return 1;
		}
		return 0;
	}
}
