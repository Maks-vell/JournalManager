#include <string>
#include "windows.h"
#include "Service.h"

#include "Json.h"
#include "Serde.h"
#include "dek.h"


#define BUFSIZE 1000

class AuthService : Service
{
private:
	Dek<User> db;
	SerDe<User> serde;

public:
	void Boot() override
	{
		wchar_t buf[BUFSIZE] = L"";

		HANDLE file = CreateFile(L"Users.txt",
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

		serde.UserDeserializeToDek(buf, &db);

	}

	bool LogIn(const wchar_t* name, const wchar_t* pass)
	{
		if (db.GetCnt() > 0)
		{
			for (int i = 0; i < db.GetCnt(); i++)
			{
				User* user = (User*)db.GetNext();
				if (wcscmp(user->name, name) == 0 && wcscmp(user->pass, pass) ==0)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool SignIn(const wchar_t* name, const wchar_t* pass)
	{
		if (db.GetCnt() > 0)
		{
			for (int i = 0; i < db.GetCnt(); i++)
			{
				User* user = db.GetNext();
				if (wcscmp(user->name, name) == 0)
				{
					return false;
				}
			}
		}

		db.PushFirst(new User(name, pass));
		wchar_t* buf = new wchar_t[BUFSIZE];
		wcscpy(buf, L" ");
		serde.SerializeFromDek(buf, &db);
		Json::WriteBufToFile(L"Users.txt", buf);

		delete[] buf;
		return true;
	}

};
