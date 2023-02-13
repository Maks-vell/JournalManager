#pragma once

#include "interface.h"
#include "Journal.h"
#include "limited_journal.h"
#include "special_journal.h"
#include "psu_journal.h"
#include "stdio.h"
#include "Json.h"


class Dek
{
private:
	class element
	{
	public:
		Interface* journal;
		element* next;

		element(Interface* journal_, element* next_) :
			journal(journal_),
			next(next_)
		{}
	};

private:
	element* first;
	element* last;
	element* current;	// для перебора всего дека

	int cnt;
public:
	Dek() :
		first(NULL),
		last(NULL),
		current(NULL),
		cnt(0)
	{}

	~Dek()
	{
		element* current_ = NULL;
		element* next = first;

		// сохраняем следующий журнал и удаляем текущий
		for (int i = 0; i < this->cnt; i++)
		{
			current_ = next;
			next = current_->next;
			delete current_;
		}

		this->cnt = 0;
		this->current = NULL;
		this->first = NULL;
		this->last = NULL;
	}

	int GetCnt()
	{
		return this->cnt;
	}

	Interface* GetFirst()
	{
		return first != NULL ? first->journal : NULL;
	}

	// для перебора в цикле, после любых операций изменения сбрасывается к 1 элементу
	Interface* GetNext()
	{
		if (this->current != NULL) this->current = this->current->next;
		else this->current = this->first;

		return this->current->journal;
	}

	void PushFirst(Interface* journal)
	{
		if (this->cnt != 0)
		{
			element* new_first = new element(journal, this->first);
			this->last->next = new_first;
			this->first = new_first;
		}
		else
		{
			element* new_first = new element(journal, NULL);
			new_first->next = new_first;

			this->last = new_first;
			this->first = new_first;
		}

		this->current = this->last;
		this->cnt++;
	}

	void PopLast()
	{
		if (this->cnt == 0) return;

		if (this->cnt == 1)
		{
			delete this->first;
			this->first == NULL;
			this->last == NULL;
			this->cnt = 0;
			return;
		}

		//	перебираем элементы для получения предпоследнего
		for (int i = 0; i < this->cnt - 1; i++)
		{
			GetNext();
		}
		current->next = first;
		delete last;
		last = current;
	}

	Interface* GetEl(int index)
	{
		for (int i = 0; i < index; i++)
		{
			GetNext();
		}
		return this->current->journal;
	}

};