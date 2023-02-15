#pragma once
#include "AuthService.h"
#include "Dek.h"
#include "Service.h"
#include "UserService.h"

static AuthService auth_service;
static UserService user_service;

class ServiceManager
{
private:
	Dek<Service> service_dek;
public:
	void ServiceBoot()
	{
		service_dek.PushFirst(&auth_service);
		service_dek.PushFirst(&user_service);

		for (int i = 0; i < service_dek.GetCnt(); i++)
		{
			service_dek.GetNext()->Boot();
		}
	}
};