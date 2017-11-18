#pragma once

#include <QException>

class Exception :public QException
{
public:
	Exception()
	{

	}
	virtual ~Exception()
	{

	}
public:
	virtual Exception * clone() const
	{
		return new Exception(*this);
	}
	void raise() const
	{
		throw *this;
	}
};

class ExceptionBadAlloc :public Exception
{
public:
	ExceptionBadAlloc()
	{

	}
	virtual ~ExceptionBadAlloc()
	{

	}
public:
	virtual ExceptionBadAlloc * clone() const
	{
		return new ExceptionBadAlloc(*this);
	}
	void raise() const
	{
		throw *this;
	}
};