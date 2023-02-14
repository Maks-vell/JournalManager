#include <string>
#include "Json.h"

#define BUFSIZE 100

class User
{
public:
	wchar_t* name;
	wchar_t* pass;

	User(const wchar_t name_[BUFSIZE] = L"", const wchar_t pass_[BUFSIZE] = L"");
	~User();

	void Serialize(wchar_t* buf);
	void Deserialize(const wchar_t* buf);
};
