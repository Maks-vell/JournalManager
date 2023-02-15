#pragma once

class Service
{
public:
	virtual void Boot() = 0;
	virtual void UnBoot() = 0;
};