
#include "pch.h"
#include "Worker.h"


void CWorker::InsertAdr(int nID, TYPE_SEND_CB cb)
{
	m_mapSessionAdress.insert(std::map<int, TYPE_SEND_CB>::value_type(nID, cb));
}

void CWorker::DeleteAdr(int nID)
{
// 	std::map<int, TYPE_SEND_CB>::iterator iterAdress = m_mapSessionAdress.find(nID);
// 
// 	if (iterAdress != m_mapSessionAdress.end())
// 	{
// 		//m_mapSessionAdress.insert(std::map<int, TYPE_SEND_CB>::value_type(nID, cb));
// 
// 	}


	m_mapSessionAdress.erase(nID);

}


bool CWorker::ProcessRecv(int nID, int nSize, PBYTE pData)     // 받을 id, 보낼 data
{
	std::map<int, TYPE_SEND_CB>::const_iterator it = m_mapSessionAdress.find(nID);
	if (it != m_mapSessionAdress.end())
	{
		(it->second)(pData);


	}
	else
		return false;

	return true;
}

void CWorker::AddWork(int nID, DWORD dwSize, PBYTE pData)
{
	P_HEADER* pHeader = (P_HEADER*)pData;

	ST_WORKER_DATA stWorkerData;
	stWorkerData.nID = nID;
	//stWorkerData.dwSize = ;
	stWorkerData.pData = (PBYTE)m_Pool.ordered_malloc(pHeader->PacketSize);
	//stWorkerData.pData = new BYTE[pHeader->PacketSize];
	std::copy(pData, pData + pHeader->PacketSize, stWorkerData.pData);


	m_WorkList.push(stWorkerData);


	int a = 0;


// 	P_PACKET_DEFAULT pPacketDefault;
// 	int nHeaderSize = sizeof(P_HEADER);
// 	memcpy(&pPacketDefault, pData, sizeof(nHeaderSize));
// 
// 	//  [3/23/2020 kjky12] 입력 크기와 헤더의 크기가 다른 경우를 처리해주어야함!!
// 	pPacketDefault.pData = (BYTE*)m_Pool.ordered_malloc(nSize - nHeaderSize);
// 	std::copy(pData + nHeaderSize, pData + nHeaderSize + nSize, pPacketDefault.pData);
// 
// 	//m_WorkList.enqueue(temp);
// 	m_WorkList.push(pPacketDefault);
}

bool CWorker::GetWork(ST_WORKER_DATA& stWorkerData)
{
	//m_WorkList.pop(wd);

	bool bFlag = m_WorkList.pop(stWorkerData);

	return bFlag;
}


void CWorker::Worker()
{
	while (true)
	{
		ST_WORKER_DATA stWorkerData;
		if (GetWork(stWorkerData))
		{
			P_HEADER* pHeader = (P_HEADER*)stWorkerData.pData;

			if (!pHeader)
				continue;

			//! 데이터 사이즈가 0이면 일단 패스
			if(pHeader->PacketSize <= 0)
				continue;


			std::map<int, TYPE_SEND_CB>::iterator iterAdress;
			std::ostringstream stream;


			switch (pHeader->PacketID)
			{
			default:
			{
				if (stWorkerData.pData != NULL)
				{
					stream << "Thread No : " << GetCurrentThreadId() << "\t" << "Worker_Dequeue " << stWorkerData.nID << "'s : " /*<< (*(char*)(stWorkerData.pData)) */<< std::endl;
					g_BoostLog.DumpLog(stream.str());

					for (iterAdress = m_mapSessionAdress.begin(); iterAdress != m_mapSessionAdress.end(); iterAdress++)
					{
						ProcessRecv(iterAdress->first, 0, stWorkerData.pData);
					}

					m_Pool.ordered_free(stWorkerData.pData);
				}
			}

			break;
			}


		}

		//boost::this_thread::sleep_for(boost::chrono::milliseconds(1));

	}
}