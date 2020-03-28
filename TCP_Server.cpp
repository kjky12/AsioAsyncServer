#pragma once


#include "pch.h"
#include "TCP_Server.h"



CTCP_Server::CTCP_Server(boost::asio::io_service& io) : m_Acceptor(io, tcp::endpoint(tcp::v4(), dfSERVER_PORT_NUMBER)), m_nAcceptCnt(0)
{
	// 		m_WorkerThread.create_thread(boost::bind(&CWorker::Worker, &g_Worker));
	// 		m_WorkerThread.add_thread(new boost::thread(boost::bind(&CWorker::Worker, &g_Worker)));

			//  [3/25/2020 kjky12] 리시브를 별도의 스레드에서 처리한다면 매우 빠를것 같음..(버그 발생 확률이 높아질듯..
			//for (int i = 0; i < dfSERVER_RECV_SEND_THREAD; i++)
			//{
			//	io_SessionThread.create_thread(boost::bind(&boost::asio::io_service::run, &io));
			//}

	WaitAccept();
}

CTCP_Server::~CTCP_Server()
{
	//io_SessionThread.join_all();
	//m_WorkerThread.join_all();
}


void CTCP_Server::WaitAccept()
{
	//boost::asio::io_service io = (boost::asio::io_context&)m_Acceptor.get_executor().context();

	++m_nAcceptCnt;
	CSession::pointer new_connection = CSession::create((boost::asio::io_context&)m_Acceptor.get_executor().context(), (CTCP_Server*)this);

	m_Acceptor.async_accept(new_connection->socket(),
		boost::bind(&CTCP_Server::handle_Accept, this, new_connection,
			boost::asio::placeholders::error));


}

void CTCP_Server::handle_Accept(CSession::pointer new_connection, const boost::system::error_code& error)
{
	if (!error)
	{
		//!임시로... 접속 성공시 세션 정보를 관리한다. -> 추후에는 m_Acceptor에 정보가 있을것으로 보임..
		m_mapSessionInfo.insert(std::make_pair(m_nAcceptCnt, new_connection));

		new_connection->start(m_nAcceptCnt);
		WaitAccept();
	}
	else
	{
		std::ostringstream stream;
		stream << "error No: " << error.value() << " error Message: " << error.message() << std::endl;
		g_BoostLog.DumpLog(stream.str());
	}
}



//! ID를 통해 세션을 삭제한다.
void CTCP_Server::DisconnectSoket(int nID)
{
	std::map<int, CSession::pointer>::iterator iterSessionInfo = m_mapSessionInfo.find(nID);
	if (iterSessionInfo != m_mapSessionInfo.end())
	{
		//! Shared_ptr의 주소를 확인한다.
		if (iterSessionInfo->second)
		{
			//! 1. 소켓이 오픈되어 있는경우 소켓을 닫아준다.
			if (iterSessionInfo->second->socket().is_open())
				iterSessionInfo->second->socket().close();

			//! 2. Shared_ptr 삭제
			iterSessionInfo->second.reset();
		}

		//! 3. 관리 변수 삭제
		m_mapSessionInfo.erase(nID);
	}
}




//! 임시 - 메모리 주소 또는 소켓이 닫힌 데이터는 삭제해준다. -> 주기적으로 확인하여 삭제해주어도 좋을듯(개선 필요)
// 	void RefreshDisconnectSyncSoket()
// 	{
// 		std::vector<int>	vecTem;
// 		std::map<int, CSession::pointer>::iterator iterSessionInfo;
// 		for (iterSessionInfo = m_mapSessionInfo.begin(); iterSessionInfo != m_mapSessionInfo.end(); iterSessionInfo++)
// 		{
// 			if (iterSessionInfo->second)
// 			{
// 				//! 공유메모리 참조 카운트!!
// 				//iterSessionInfo->second.use_count();
// 
// 				if (iterSessionInfo->second.get())
// 				{
// 					if (iterSessionInfo->second.get()->socket().is_open())
// 					{
// 					}
// 					else
// 					{
// 						iterSessionInfo->second.reset();
// 						vecTem.push_back(iterSessionInfo->first);
// 					}
// 				}
// 				else
// 				{
// 					iterSessionInfo->second.reset();
// 					vecTem.push_back(iterSessionInfo->first);
// 				}
// 			}
// 			else
// 			{
// 				iterSessionInfo->second.reset();
// 				vecTem.push_back(iterSessionInfo->first);
// 			}
// 		}
// 
// 		for (int v = 0;v < vecTem.size();v++)
// 		{
// 			m_mapSessionInfo.erase(vecTem[v]);
// 		}
// 
// 
// 
// 	}