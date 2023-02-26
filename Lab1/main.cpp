#include <iostream>
#include <fstream>
#include <windows.h>
#include <locale>

#include "SerDe.h"
#include "ServiceManager.h"

#include "LimitedJournal.h"
#include  "PsuJournal.h"
#include "SpecialJournal.h"

using namespace std;

#define SAVING_FILE L"save.txt"
#define BUFSIZE 1000

void StartInfo();
Dek<Entity>* CreateDek();
void ViewDB(Dek<Entity>* dek);
Entity* CreateJournal();
Dek<Entity>* LoadJournal(const wchar_t file_name[]);
void Auth();
template <typename TYPE>
bool comp_more(TYPE a, TYPE b);
template <typename TYPE>
bool comp_less(TYPE a, TYPE b);

static ServiceManager service_manager;


SerDe<Entity> serde;


int wmain() {
	setlocale(LC_ALL, "");

	// TEST
	wcout << L"DEK TEST \n";
	Dek<int> dekInt;
	int a = 1, b = 2, c = 3;
	dekInt.PushFirst(&a);
	dekInt.PushFirst(&b);
	dekInt.PushFirst(&c);
	for(int i = 0;i< 3; i++)
	{
		wcout << *dekInt.GetNext();
	}

	Dek<int*> dekInt1;
	int* a1 = new int(1);
	int* b1 = new int(2);
	int* c1 = new int(3);
	dekInt1.PushFirst(&a1);
	dekInt1.PushFirst(&b1);
	dekInt1.PushFirst(&c1);
	for (int i = 0; i < 3; i++)
	{
		wcout << **dekInt1.GetNext();
	}
	wcout << endl;
	// TEST



	service_manager.ServiceBoot();
	wcout << L"Last modification by " << user_service.GetLastUser().name << endl;
	Auth();
	StartInfo();
	Dek<Entity>* dek = CreateDek();
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
			Entity* new_jrl = CreateJournal();
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
			serde.SerializeFromDek(buf, dek);
			is_succes = Json::WriteBufToFile(SAVING_FILE, buf);
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
			wcout << L"Enter the number of first journal:";
			cin >> i;
			Journal* left = (Journal*)dek->GetEl(i);
			wcout << L"Enter the number of second journal:";
			wcin >> i;
			Journal* right = (Journal*)dek->GetEl(i);

			if (comp_more(left, right))
			{
				wcout << L"Circulation first journal more" << endl;
			}
			else
			{
				wcout << L"Circulation first journal less" << endl;
			}
		}

		else if (wcscmp(command, L"less") == 0)
		{
			int i;
			wcout << L"Enter the number of first journal:";
			wcin >> i;
			Journal* left = (Journal*)dek->GetEl(i);
			wcout << L"Enter the number of second journal:";
			wcin >> i;
			Journal* right = (Journal*)dek->GetEl(i);
			if (comp_less(left, right))
			{
				wcout << L"Circulation first journal less" << endl;
			}
			else
			{
				wcout << L"Circulation first journal more" << endl;
			}
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

void Auth()
{
	wcout << L"\t \t \t ***Authorization***\n\n";

	wchar_t answer[STDBUF_SIZE] = L" ";
	while (true)
	{
		wcout << L"Have you an account? (y/n) \n";
		wcin >> answer;

		wchar_t name[STDBUF_SIZE] = L" " ;
		wchar_t pass[STDBUF_SIZE] = L" " ;
		if (answer != std::wstring(L"y"))
		{
			wcout << L"Registration \n";
			wcout << L"Enter the name \n";
			wcin >> name;
			wcout << L"Enter the password \n";
			wcin >> pass;
			if (!auth_service.SignIn(name, pass))
			{
				wcout << L"Alredy exists \n";
			}
		}

		wcout << L"Log in \n";
		wcout << L"Enter the name \n";
		wcin >> name;
		wcout << L"Enter the password \n";
		wcin >> pass;
		if(!auth_service.LogIn(name, pass))
		{
			wcout << L"Invalid login or password \n";
		}
		else
		{
			break;
		}
	}

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
		<< L"less, more - compare 2 journal \n"
		<< L"e , exit - exit, data will be deleted \n \n";
}

Dek<Entity>* LoadJournal(const wchar_t file_name[])
{
	Dek<Entity>* dek = new Dek<Entity>;	// новый список журналов
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

	serde.JournalDeserializeToDek(buf, dek);

	CloseHandle(file);
	return dek;
}

Dek<Entity>* CreateDek()
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

	Dek<Entity>* dek = new Dek<Entity>;
	wchar_t jrl_type = L' ';
	Entity* new_jrl = NULL;

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

void ViewDB(Dek<Entity>* dek)
{
	wcout << L"\n \t \t \t List of journals \n";
	for (int i = 0; i < dek->GetCnt(); i++)
	{
		dek->GetNext()->Output();
		wcout << endl;
	}
}

Entity* CreateJournal()
{
	wchar_t jrl_type[STDBUF_SIZE] = L" ";
	wcout << L"\n Enter the type of journal: ";
	wcin >> jrl_type;
	Entity* new_jrl = 0;

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
