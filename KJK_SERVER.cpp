#include "pch.h"

#include "TCP_Server.h"



int main()
{
	try
	{
		boost::asio::io_service io;

		CTCP_Server server(io);

		boost::thread_group WorkerThread;
		WorkerThread.create_thread(boost::bind(&CWorker::Worker, &g_Worker));
		for (int v=  0; v < dfSERVER_RECV_SEND_THREAD; v++)
		{
			WorkerThread.add_thread(new boost::thread(boost::bind(&CWorker::Worker, &g_Worker)));
		}

		io.run();

		io.stop();
		io.reset();


		WorkerThread.join_all();
	}
	catch (std::exception & e)
	{
		std::string strError = e.what();
		//std::cerr << strError << std::endl;
		g_BoostLog.DumpLog(strError);
	}

	return 0;
}


