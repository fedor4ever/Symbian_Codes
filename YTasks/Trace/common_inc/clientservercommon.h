/* 
	Copyright (c) 2006, 
	Jukka Silvennoinen. 
	All rights reserved 
*/


#ifndef __CLIENTSERVERCOMMON_H__
#define __CLIENTSERVERCOMMON_H__

#include <e32base.h>
#include "Common.h"


//the server version. A version must be specified when 
//creating a session with the server
const TUint SServMajorVersionNumber=0;
const TUint SServMinorVersionNumber=1;
const TUint SServBuildVersionNumber=1;

const TInt KMaxSoneClientMessage=512;


//opcodes used in message passing between client and server
enum TSoneClientMessages
	{
	EExamplePServGetCount,
	EExamplePServGetItem,
	EExamplePServShutDown,
	EExamplePServClearList,
	EExamplePServStop,
	EExamplePServStart,
	EExamplePServGetCPUMax,
	EExampleReReadSett
    };
 
 #ifdef __SERIES60_3X__

#else
	//opcodes used by server to indicate which asynchronous service
	// 2nd edition only
	enum TSProtServRqstComplete
		{
		EExamplePServGetCountComplete = 1,
		EExamplePServGetItemComplete,
		EExamplePServShutDownComplete,
		EExamplePServClearListComplete,
		EExamplePServStopComplete,
		EExamplePServStartComplete,
		EExamplePServGetCPUMaxComplete
	};
#endif

    
/*
----------------------------- TExampleItem ----------------------------------
*/  
class TExampleItem
    {
    public:
        TExampleItem(): iIndex(-1){};
    public:
    	TInt 		iIndex;
    	TInt 		iCpuLoad;
    	TInt		iMemory;
        TTime		iTime;
    };

    
/*
----------------------------- etxra stuff ----------------------------------
*/

    
#endif // __CLIENTSERVERCOMMON_H__

