#pragma once

#define  SOME_MACRO(x) #x

class Interface
{
public:
	virtual void Input() = 0;
	virtual void Output() = 0;
	virtual bool operator>(const Interface& i2) = 0;
	virtual bool operator<(const Interface& i2) = 0;
	virtual void Serialize(wchar_t* buf) = 0;
	virtual void Deserialize(const wchar_t* buf) = 0;
};