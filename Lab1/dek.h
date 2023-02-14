#pragma once

#include "Entity.h"
#include "Journal.h"
#include "LimitedJournal.h"
#include "SpecialJournal.h"
#include "PsuJournal.h"
#include "stdio.h"
#include "Json.h"


template <typename TYPE>
class Dek
{
private:
	class element
	{
	public:
		TYPE* obj;
		element* next;

		element(TYPE* obj_, element* next_) :
			obj(obj_),
			next(next_)
		{}
	};

private:
	element* first;
	element* last;
	element* current;	// ��� �������� ����� ����

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

		// ��������� ��������� ������ � ������� �������
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

	TYPE* GetFirst()
	{
		return first != NULL ? first->obj : NULL;
	}

	// ��� �������� � �����, ����� ����� �������� ��������� ������������ � 1 ��������
	TYPE* GetNext()
	{
		if (this->current != NULL) this->current = this->current->next;
		else this->current = this->first;

		return this->current->obj;
	}

	void PushFirst(TYPE* obj)
	{
		if (this->cnt != 0)
		{
			element* new_first = new element(obj, this->first);
			this->last->next = new_first;
			this->first = new_first;
		}
		else
		{
			element* new_first = new element(obj, NULL);
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

		//	���������� �������� ��� ��������� ��������������
		for (int i = 0; i < this->cnt - 1; i++)
		{
			GetNext();
		}
		current->next = first;
		delete last;
		last = current;
	}

	TYPE* GetEl(int index)
	{
		for (int i = 0; i < index; i++)
		{
			GetNext();
		}
		return this->current->obj;
	}

};