#include <iostream>
#include <fstream>
#include <windows.h>
#include <locale>
#include "Serde.h"

#include "limited_journal.h"
#include  "psu_journal.h"
#include "special_journal.h"
#include "dek.h"

#define SAVING_FILE L"save.txt"
#define BUFSIZE 1000
static SerDe Serde;

using namespace std;

void StartInfo();
Dek<Interface>* Boot();
void ViewDB(Dek<Interface>* dek);
Interface* CreateJournal();
Dek<Interface>* LoadJournal(const wchar_t file_name[]);
bool WriteBufToFile(const wchar_t file_name[], const wchar_t buf[]);

template <typename TYPE>
bool comp_more(TYPE a, TYPE b);

template <typename TYPE>
bool comp_less(TYPE a, TYPE b);


int wmain() {
	setlocale(LC_ALL, "");

	StartInfo();
	Dek<Interface>* dek = Boot();
	ViewDB(dek);

	wchar_t command[STDBUF_SIZE] = L" ";
	bool is_succes = true;	// флаг успеха выполнения команды

	wcout << L"\t \t \t Command line: \n";

	// цикл ввода-исполнения команд пользователя
	while (true)
	{
		is_succes = true;	// предполагаем успешное выполнение команды

		wcout << L"\n>> ";
		wcin >> command;
		wcout << endl;

		// определение введенной команды
		if (wcscmp(command, L"push") == 0)
		{
			Interface* new_jrl = CreateJournal();
			if (new_jrl != NULL) dek->PushFirst(new_jrl);
			else is_succes = false;
		}

		else if (wcscmp(command, L"pop") == 0)
		{
			dek->PopLast();
		}

		else if (wcscmp(command, L"view") == 0)
		{
			ViewDB(dek);
		}

		else if (wcscmp(command, L"cnt") == 0)
		{
			wcout << dek->GetCnt() << endl;
		}

		else if (wcscmp(command, L"save") == 0)
		{
			wchar_t buf[1000] = L"";
			Serde.SerializeFromDek(buf, dek);
			is_succes = WriteBufToFile(SAVING_FILE, buf);
		}

		else if (wcscmp(command, L"load") == 0)
		{
			wcout << L"All current data will be deleted! Are you sure? (y/n) \n";
			wcin >> command;
			if (wcscmp(command, L"y") == 0)
			{
				delete dek;
				dek = LoadJournal(SAVING_FILE);
			}
		}

		else if (wcscmp(command, L"help") == 0)
		{
			StartInfo();
		}

		else if (wcscmp(command, L"more") == 0)
		{
			int i;
			cout << "Enter the number of first journal:";
			cin >> i;
			Journal* left = (Journal*)dek->GetEl(i);
			cout << "Enter the number of first journal:";
			cin >> i;
			Journal* right = (Journal*)dek->GetEl(i);

			if (comp_more(left, right))
			{
				cout << "Circulation first journal more" << endl;
			}
			cout << "Circulation first journal less" << endl;
		}

		else if (wcscmp(command, L"less") == 0)
		{
			int i;
			cout << "Enter the number of first journal:";
			cin >> i;
			Journal* left = (Journal*)dek->GetEl(i);
			cout << "Enter the number of second journal:";
			cin >> i;
			Journal* right = (Journal*)dek->GetEl(i);
			if (comp_less(left, right))
			{
				cout << "Circulation first journal less" << endl;
			}
			cout << "Circulation first journal more" << endl;
		}

		else if (wcscmp(command, L"exit") == 0 || wcscmp(command, L"e") == 0)
		{
			wcout << L"All current data will be deleted! Are you sure? (y/n) \n";
			wcin >> command;
			if (wcscmp(command, L"y") == 0)
			{
				break;
			}
		}

		else
		{
			is_succes = false;
		}

		if (is_succes) wcout << L"\n Completed successfully \n";
		else wcout << L"Command error \n";
	}

	delete dek;

	system("pause");
	return 0;
}

void StartInfo()
{
	wcout << L"\t \t \t ***Journal manager***\n\n"
		<< L"A type of journals: limited - limited journal, special - special, psu - psu journal \n"
		<< L"Commands: \n"
		<< L"push - add journal in the start \n"
		<< L"pop - delete journal in the end \n"
		<< L"view - view list of journals \n"
		<< L"cnt - count of journals \n"
		<< L"save - save journals \n"
		<< L"load - load saved journals (all current journals will be removed) \n"
		<< L"e , exit - exit, data will be deleted \n \n";
}

bool WriteBufToFile(const wchar_t file_name[], const wchar_t buf[])
{
	HANDLE file = CreateFile(file_name,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file == NULL)
	{
		wprintf(L"ERROR: Open file failed with %d.\n", GetLastError());
		return false;
	}
	else
	{
		DWORD written_bytes;
		BOOL is_write = WriteFile(file, buf,
			wcslen(buf) * sizeof(wchar_t), &written_bytes, NULL);
		if (!is_write)
		{
			wprintf(L"ERROR: Writing file failed with %d.\n", GetLastError());
			return false;
		}

		CloseHandle(file);
	}

	return true;
}

Dek<Interface>* LoadJournal(const wchar_t file_name[])
{
	Dek<Interface>* dek = new Dek<Interface>;	// новый список журналов
	wchar_t buf[BUFSIZE] = L"";

	HANDLE file = CreateFile(file_name,
		GENERIC_READ,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file == NULL)
	{
		wprintf(L"ERROR: Open file failed with %d.\n", GetLastError());
		system("pause");
		exit(-1);
	}

	DWORD bytes_read = 0;
	ReadFile(file,
		buf,
		BUFSIZE,
		&bytes_read,
		NULL);

	Serde.DeserializeToDek(buf, dek);

	CloseHandle(file);
	return dek;
}

Dek<Interface>* Boot()
{
	wcout << L"Load data? [y/n] \n";
	wchar_t answer[100] = L"";
	wcin >> answer;

	if (wcscmp(answer, L"y") == 0)
	{
		return LoadJournal(SAVING_FILE);
	}

	int cnt = 0;
	wcout << L"Enter the count of journals: ";
	wcin >> cnt;

	wcout << L"\n \t \t \t Creating new journals \n";

	Dek<Interface>* dek = new Dek<Interface>;
	wchar_t jrl_type = L' ';
	Interface* new_jrl = NULL;

	// создаем каждый журнал
	for (int i = 1; i < cnt + 1; i++)
	{
		new_jrl = CreateJournal();
		if (new_jrl != NULL) dek->PushFirst(new_jrl);
		else
		{
			i--;
			continue;
		}
	}

	return dek;
}

void ViewDB(Dek<Interface>* dek)
{
	wcout << L"\n \t \t \t List of journals \n";
	for (int i = 0; i < dek->GetCnt(); i++)
	{
		dek->GetNext()->Output();
		wcout << endl;
	}
}

Interface* CreateJournal()
{
	wchar_t jrl_type[STDBUF_SIZE] = L" ";
	wcout << L"\n Enter the type of journal: ";
	wcin >> jrl_type;
	Interface* new_jrl = 0;

	//создаем журнал согласно типу
	if (wcscmp(jrl_type, L"limited") == 0) new_jrl = new LimitedJournal;
	else if (wcscmp(jrl_type, L"special") == 0) new_jrl = new SpecialJournal;
	else if (wcscmp(jrl_type, L"psu") == 0) new_jrl = new PsuJournal;
	else wcout << L"ERROR: Unknown type \n";

	if (new_jrl != 0) new_jrl->Input();

	return new_jrl;
}

template <typename TYPE>
bool comp_more(TYPE a, TYPE b)
{
	return a > b;
}

template <typename TYPE>
bool comp_less(TYPE a, TYPE b)
{
	return a < b;
}
