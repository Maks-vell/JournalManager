#pragma once
#include <string>
#include "Json.h"
#include "dek.h"

#include "journal.h"
#include "limited_journal.h"
#include "psu_journal.h"
#include "special_journal.h"


static class SerDe
{
public:
	void DeserializeToDek(wchar_t* buf, Dek* dek)
	{
		int count_ent = 0;
		std::wstring* entitys = Json::GetJsonEntitys(buf, count_ent);

		for (int i = 0; i < count_ent; i++)
		{
			std::wstring tag = Json::GetTag(entitys[i]);

			if (tag == std::wstring(L"Journal"))
			{
				Journal* journal = new Journal;
				journal->Deserialize(entitys[i].c_str());
				dek->PushFirst(journal);
			}
			else if (tag == std::wstring(L"LimitedJournal"))
			{
				LimitedJournal* journal = new LimitedJournal;
				journal->Deserialize(entitys[i].c_str());
				dek->PushFirst(journal);
			}
			else if (tag == std::wstring(L"SpecialJournal"))
			{
				SpecialJournal* journal = new SpecialJournal;
				journal->Deserialize(entitys[i].c_str());
				dek->PushFirst(journal);
			}
			else if (tag == std::wstring(L"PsuJournal"))
			{
				PsuJournal* journal = new PsuJournal;
				journal->Deserialize(entitys[i].c_str());
				dek->PushFirst(journal);
			}
		}

		delete[] entitys;
	}

	void SerializeFromDek(wchar_t* buf, Dek* dek)
	{
		for (int i = 0; i < dek->GetCnt(); i++)
		{
			dek->GetNext()->Serialize(buf);
		}
	}

};
