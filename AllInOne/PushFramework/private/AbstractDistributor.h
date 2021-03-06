/********************************************************************
	File :			AbstractDistributor.h
	Creation date :	2012/01/29

	License :			Copyright 2010 Ahmed Charfeddine, http://www.pushframework.com

				   Licensed under the Apache License, Version 2.0 (the "License");
				   you may not use this file except in compliance with the License.
				   You may obtain a copy of the License at

					   http://www.apache.org/licenses/LICENSE-2.0

				   Unless required by applicable law or agreed to in writing, software
				   distributed under the License is distributed on an "AS IS" BASIS,
				   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
				   See the License for the specific language governing permissions and
				   limitations under the License.


*********************************************************************/
#ifndef AbstractDistributor__INCLUDED
#define AbstractDistributor__INCLUDED

#pragma once

namespace PushFramework
{

typedef void* ItemPtr;
enum ProcessResult {DeleteItem, PauseProcessing, ContinueProcessing};
class AbstractDistributor
{
public:
    AbstractDistributor(void);

    ~AbstractDistributor(void);

    //thread 1
    void Reshuffle();

    virtual void AddItem(ItemPtr pItem);

    int GetItemsCount();

    void Start();
    void Stop();

protected:
    virtual ProcessResult ProcessItem(ItemPtr pItem) = 0;
private:
    int itemsCount;
    typedef std::vector<ItemPtr> itemListT;

    itemListT activeList;
    itemListT inactiveList;
    itemListT insertedItemsList;

    time_t lastQueueChange;
    time_t lastListChange;
    time_t lastAddedItemTime;
    time_t lastAddedItemsSyncTime;

    bool stop;
    ThreadHandleType hThread;

    CRITICAL_SECTION csInsertedItemsList;

    bool CheckMergeNewInsertedItems();
    bool CheckMergeInactiveItems();
    void ProcessActiveList();

    void DoWork();


#ifdef Plateform_Windows
    static DWORD WINAPI threadProc(LPVOID lpVoid);
#else
#ifdef Plateform_Linux
    static void* threadProc(void* lpVoid);
#endif
#endif

};
}


#endif // AbstractDistributor__INCLUDED
