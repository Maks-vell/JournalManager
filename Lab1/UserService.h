#pragma once
#include "Dek.h"
#include "SerDe.h"
#include "Service.h"

#define USER_FILE L"User.txt"

class UserService : public Service
{
private:
	Dek<User> history_user;
	User current_user;
	SerDe<User> serde;

public:
	void Boot() override
	{
		wchar_t buf[BUFSIZE] = L"";

		HANDLE file = CreateFile(USER_FILE,
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


		serde.UserDeserializeToDek(buf, &history_user);
		history_user.PushFirst(&current_user);

		CloseHandle(file);
	}

	void UnBoot() override
	{
		wchar_t buf[BUFSIZE] = L"";

		serde.SerializeFromDek(buf, &history_user);
		Json::WriteBufToFile(USER_FILE, buf);
	}

	void SetCurrentUser(const User& user)
	{
		current_user = user;
	}

	const User& GetLastUser()
	{
		return *history_user.GetFirst();
	}
};
