#pragma once


#include "pch.h"
#include "Session.h"


class CTCP_Server
{
private:
	tcp::acceptor m_Acceptor;
	int m_nAcceptCnt;

	std::map<int, CSession::pointer> m_mapSessionInfo;

	//boost::thread_group io_SessionThread;

	void WaitAccept();

	void handle_Accept(CSession::pointer new_connection, const boost::system::error_code& error);

public:
	//boost::thread_group m_WorkerThread;
	CTCP_Server(boost::asio::io_service& io);
	~CTCP_Server();


	//! ID를 통해 세션을 삭제한다.
	void DisconnectSoket(int nID);

};
