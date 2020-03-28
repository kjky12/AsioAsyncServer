#pragma once


#include "pch.h"
#include "TCP_Server.h"



CTCP_Server::CTCP_Server(boost::asio::io_service& io) : m_Acceptor(io, tcp::endpoint(tcp::v4(), dfSERVER_PORT_NUMBER)), m_nAcceptCnt(0)
{
	// 		m_WorkerThread.create_thread(boost::bind(&CWorker::Worker, &g_Worker));
	// 		m_WorkerThread.add_thread(new boost::thread(boost::bind(&CWorker::Worker, &g_Worker)));

			//  [3/25/2020 kjky12] ���ú긦 ������ �����忡�� ó���Ѵٸ� �ſ� ������ ����..(���� �߻� Ȯ���� ��������..
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
		//!�ӽ÷�... ���� ������ ���� ������ �����Ѵ�. -> ���Ŀ��� m_Acceptor�� ������ ���������� ����..
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



//! ID�� ���� ������ �����Ѵ�.
void CTCP_Server::DisconnectSoket(int nID)
{
	std::map<int, CSession::pointer>::iterator iterSessionInfo = m_mapSessionInfo.find(nID);
	if (iterSessionInfo != m_mapSessionInfo.end())
	{
		//! Shared_ptr�� �ּҸ� Ȯ���Ѵ�.
		if (iterSessionInfo->second)
		{
			//! 1. ������ ���µǾ� �ִ°�� ������ �ݾ��ش�.
			if (iterSessionInfo->second->socket().is_open())
				iterSessionInfo->second->socket().close();

			//! 2. Shared_ptr ����
			iterSessionInfo->second.reset();
		}

		//! 3. ���� ���� ����
		m_mapSessionInfo.erase(nID);
	}
}




//! �ӽ� - �޸� �ּ� �Ǵ� ������ ���� �����ʹ� �������ش�. -> �ֱ������� Ȯ���Ͽ� �������־ ������(���� �ʿ�)
// 	void RefreshDisconnectSyncSoket()
// 	{
// 		std::vector<int>	vecTem;
// 		std::map<int, CSession::pointer>::iterator iterSessionInfo;
// 		for (iterSessionInfo = m_mapSessionInfo.begin(); iterSessionInfo != m_mapSessionInfo.end(); iterSessionInfo++)
// 		{
// 			if (iterSessionInfo->second)
// 			{
// 				//! �����޸� ���� ī��Ʈ!!
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