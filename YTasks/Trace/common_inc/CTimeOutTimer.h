/* 	
	Copyright (c) 2001 - 2007, 
	J.P. Silvennoinen.
	All rights reserved 
*/

#ifndef __CTIMEOUTTIMER_H__
#define __CTIMEOUTTIMER_H__

#include <E32BASE.H>

	class MTimeOutNotify
	{
	public:
		virtual void TimerExpired() = 0;
		};

	class CTimeOutTimer: public CTimer
		{
	public:
		static CTimeOutTimer* NewL(const TInt aPriority, MTimeOutNotify& aTimeOutNotify);
		~CTimeOutTimer();
	protected:
		CTimeOutTimer(const TInt aPriority);
		void ConstructL(MTimeOutNotify& aTimeOutNotify);
		virtual void RunL();
	private:
		MTimeOutNotify* iNotify;
		};

#endif // __CTIMEOUTTIMER_H__
