#pragma once
#include "AuthService.h"
#include "Dek.h"

static AuthService authService;

class ServiceManager
{
private:
	Dek<Service> service_dek;
public:
	void ServiceBoot()
	{
		service_dek.PushFirst(&authService);

		for (int i = 0; i < service_dek.GetCnt(); i++)
		{
			service_dek.GetNext()->Boot();
			
		}
	}
};