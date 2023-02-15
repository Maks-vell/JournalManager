#pragma once

#include <string>
#include "windows.h"
#include "Service.h"

#include "Json.h"
#include "SerDe.h"
#include "Dek.h"


#define BUFSIZE 1000
#define AUTH_FILE L"Auth.txt"

class AuthService : public Service
{
private:
	Dek<User> auth_dek;
	SerDe<User> serde;

public:
	void Boot() override
	{
		wchar_t buf[BUFSIZE] = L"";

		HANDLE file = CreateFile(AUTH_FILE,
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

		serde.UserDeserializeToDek(buf, &auth_dek);
		CloseHandle(file);
	}

	void UnBoot() override
	{
		
	}

	bool LogIn(const wchar_t* name, const wchar_t* pass)
	{
		if (auth_dek.GetCnt() > 0)
		{
			for (int i = 0; i < auth_dek.GetCnt(); i++)
			{
				User* user = (User*)auth_dek.GetNext();
				if (wcscmp(user->name, name) == 0 && wcscmp(user->pass, pass) == 0)
				{
					//user_service->SetCurrentUser(user);
					return true;
				}
			}
		}

		return false;
	}

	bool SignIn(const wchar_t* name, const wchar_t* pass)
	{
		if (auth_dek.GetCnt() > 0)
		{
			for (int i = 0; i < auth_dek.GetCnt(); i++)
			{
				User* user = auth_dek.GetNext();
				if (wcscmp(user->name, name) == 0)
				{
					return false;
				}
			}
		}

		auth_dek.PushFirst(new User(name, pass));
		wchar_t* buf = new wchar_t[BUFSIZE];
		wcscpy(buf, L" ");
		serde.SerializeFromDek(buf, &auth_dek);
		Json::WriteBufToFile(AUTH_FILE, buf);

		delete[] buf;
		return true;
	}

};
