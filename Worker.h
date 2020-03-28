#pragma once

//#include "pch.h"

#include "IncludeBoost.h"


typedef boost::function<void(BYTE*)> TYPE_SEND_CB;

typedef struct ST_WORKER_DATA
{
	int nID;
	//DWORD dwSize;
	PBYTE pData;
}ST_WORKER_DATA;


class CWorker
{
private:
	boost::pool<> m_Pool;
	boost::lockfree::queue<ST_WORKER_DATA> m_WorkList;
	std::map<int, TYPE_SEND_CB> m_mapSessionAdress;

public:

	void InsertAdr(int nID, TYPE_SEND_CB cb);

	void DeleteAdr(int nID);

	// 보낸 id, 데이터 크기, 보낼 data
	bool ProcessRecv(int nID, int nSize, PBYTE pData);     

	void AddWork(int nID, DWORD dwSize, PBYTE pData);

	bool GetWork(ST_WORKER_DATA& stWorkerData);

	void Worker();

	CWorker(): m_Pool(sizeof(eBufSize)), m_WorkList(100)
	{
		
	};


	virtual ~CWorker(void)
	{

	};

};

