
#include "pch.h"
#include "BoostLog.h"

// We define our own severity levels
#include <direct.h>


CBoostLog::CBoostLog()
{
	m_strLogRootDirectory = gf_GetModulePathA() + "LOG\\";

	m_bAutoRefreshDirectory = true;


	//////////////////////////////////////////////////////////////////////////
	std::wstring strT1 = gf_GetModulePathW();
	std::string  strT2 = gf_GetModulePathA();



	m_sinkSingleTone = NULL;
// 	m_sinkSingleTone = init_logging();
// 
// 
// 	{
// 		sink_t::locked_backend_ptr p = m_sinkSingleTone->locked_backend();
// 		//p->add_stream(boost::make_shared< std::ofstream >("Sample.log"));
// 		//p->add_stream(boost::shared_ptr< std::ostream >(vT));
// 
// 		boost::shared_ptr<std::ofstream> vt = open_file(m_strLogRootDirectory + "Server.log", 4);
// 		p->add_stream(vt);
// 
// 		src::severity_channel_logger< severity_level > lg(keywords::channel = "net");
// 		BOOST_LOG_SEV(lg, warning) << "KJK Server Version.1";
// 
// 		//Finsh_logging(m_sinkSingleTone);
// 
// 	}


// 	src::severity_channel_logger< severity_level > lg(keywords::channel = "net");
// 	BOOST_LOG_SEV(lg, warning) << "Hello world!TT";
// 	BOOST_LOG_SEV(lg, warning) << "Hello world!TT";
// 	BOOST_LOG_SEV(lg, warning) << "Hello world!TT";
// 
// 
// 	stop_logging(m_sinkSingleTone);
// 
// 	//m_sinkSingleTone = init_logging();
// 
// 	BOOST_LOG_SEV(lg, warning) << "Hello world!TT1";
// 	BOOST_LOG_SEV(lg, warning) << "Hello world!TT2";
// 	BOOST_LOG_SEV(lg, warning) << "Hello world!TT3";
// 
// 
// 	stop_logging(m_sinkSingleTone);

	
}


CBoostLog::~CBoostLog()
{
	if(m_sinkSingleTone)
		stop_logging(m_sinkSingleTone);
	m_sinkSingleTone = NULL;
}


bool CBoostLog::SetLogDirectoryPath(std::string strDirectory)
{
	m_strLogRootDirectory = strDirectory;

	return false;
}

//! 로그 경로가 루트에서 일자별로 자동으로 나뉘게한다.
bool CBoostLog::SetAutoDateRefreshDirectory(bool bAutoRefreshDirectory)
{
	m_bAutoRefreshDirectory = bAutoRefreshDirectory;
	return true;
}

//! 파일 유무 판단


bool CBoostLog::DumpLog(std::string strLog, bool bFlush)
{

	SYSTEMTIME st;
	GetLocalTime(&st);

	std::string strPathFile;
	//std::string strPathFile = strPath + strLogFileName;

	if (m_bAutoRefreshDirectory == true)
	{
		std::string strPath = m_strLogRootDirectory + format_string("%04d%02d\\", st.wYear, st.wMonth);
		std::string strLogFileName = format_string("%04d%02d%02d.log", st.wYear, st.wMonth, st.wDay);

		strPathFile = strPath + strLogFileName;


		//////////////////////////////////////////////////////////////////////////
		//일자로 파일 만드는 영역!!

		//! 경로가 잇는경우 만들어줌!
// 		if (m_strLogRootDirectory.empty()) //! 문자열이 비었을때
// 		{
// 			//! 기본 디렉토리에 파일을 만든다!!
// 			std::string strTmp = format_string("log%d%02d%02d_%02d%02d%02d,log", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
// 			p->add_stream(boost::make_shared< std::ofstream >(strTmp));
// 		}
// 		else //! 문자열 정보가 있음!
// 		{
			//format_string("%d_%02d_%02d_%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond)

		gf_MakeFullDirectoryA(strPath);

		
		//! 파일이 존재하지 않는 경우 싱크를 없애줌..
// 		if (gf_IsExistsFile(strPathFile) == false)
// 		{
// 			Finsh_logging(m_sinkSingleTone);
// 		}
	}
	else
	{
		std::string strPath = m_strLogRootDirectory;
		std::string strLogFileName = "Server.log";

		strPathFile = strPath + strLogFileName;


// 		if (!m_sinkSingleTone)
// 		{
// 			sink_t::locked_backend_ptr p = m_sinkSingleTone->locked_backend();
// 			//p->add_stream(boost::make_shared< std::ofstream >("Sample.log"));
// 			//p->add_stream(boost::shared_ptr< std::ostream >(vT));
// 
// 			boost::shared_ptr<std::ofstream> vt = open_file(strPathFile, 4);
// 			p->add_stream(vt);
// 
// 			p->flush();
// 		}
	}


	if (!m_sinkSingleTone)
	{
		//Finsh_logging(m_sinkSingleTone);
		m_sinkSingleTone = init_logging();


		sink_t::locked_backend_ptr p = m_sinkSingleTone->locked_backend();
		boost::shared_ptr<std::ofstream> vt = open_file(strPathFile, 4);
		p->add_stream(vt);
	}


	

	src::severity_channel_logger< severity_level > lg(keywords::channel = "net");
	BOOST_LOG_SEV(lg, warning) << strLog;

	
	m_sinkSingleTone->flush();
// 	if (bFlush)
// 		stop_logging(m_sinkSingleTone);


	return true;
}


boost::shared_ptr<std::ofstream> CBoostLog::open_file(const std::string file_name,uint8_t presition)
{
	boost::shared_ptr<std::ofstream> stream = boost::make_shared<std::ofstream>(file_name.c_str(), std::ios_base::out | std::ios_base::app);

	
// 	stream->precision(presition);
// 
// 	stream->setf(std::ios::fixed, std::ios::floatfield);

	return stream;
}




boost::shared_ptr< sink_t > CBoostLog::init_logging()
{
	boost::shared_ptr< logging::core > core = logging::core::get();

	// Create a backend and initialize it with a stream
	boost::shared_ptr< sinks::text_ostream_backend > backend =
		boost::make_shared< sinks::text_ostream_backend >();
	backend->add_stream(
		boost::shared_ptr< std::ostream >(&std::clog, boost::null_deleter()));

	// Wrap it into the frontend and register in the core
	boost::shared_ptr< sink_t > sink(new sink_t(backend));
	core->add_sink(sink);

	// You can manage filtering and formatting through the sink interface
	sink->set_filter(expr::attr< severity_level >("Severity") >= warning);
	sink->set_formatter
	(
		expr::stream
		<< expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y/%m/%d %H:%M:%S.%f")
		<< "[lv:" << expr::attr< severity_level >("Severity") << "]"
		<< " " << expr::message
	);

	logging::add_common_attributes();


// 	logging::add_file_log(
// // 		logging::keywords::file_name = "sample_%N.log",
// // 		logging::keywords::rotation_size = 10 * 1024 * 1024, //10mb마다 rotate 
// // 		logging::keywords::time_based_rotation = logging::sinks::file::rotation_at_time_point(0, 0, 0), //12시마다 rotate 
// // 		logging::keywords::format = "[%TimeStamp%]: %Message%"
// 
// 		logging::keywords::file_name = "sample_%N.log", // 파일의 이름 패턴 
// 		logging::keywords::rotation_size = 10 * 1024 * 1024, // 파일의 최대 크기, 즉 "파일의 로테이션를 10MB마다 해라" 라는 의미 
// 		logging::keywords::time_based_rotation = logging::sinks::file::rotation_at_time_point(0, 0, 0), // 파일의 로테이션 시간, "자정마다" 
// 		logging::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%" // 로그 레코드의 출력 형식
// 		//[%TimeStamp%] : 시간(소수점까지)
// 		//[% ThreadID%] : 스레드 ID
// 		//[% Severity%] : 로그 종류
// 		//[% ProcessID%] : 프로세스 ID? -> 순서인듯?
// 		//[% LineID%] : 프로세스의 위치?? -> 아마 다른 함수의 경우 다른 값이 출력되는듯..
// 
// 	); // text 파일로 저장 하는 sink
// 
// 
// // 	logging::add_file_log
// // 	(
// // 		keywords::file_name = "sample_%N.log",
// // 		keywords::rotation_size = 10 * 1024 * 1024,
// // 		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
// // 		keywords::format = "[%TimeStamp%]: %Message%"
// // 	);
// 
// 	logging::core::get()->set_filter
// 	(
// 		logging::trivial::severity >= logging::trivial::info
// 	);


// 	{
// 		sink_t::locked_backend_ptr p = sink->locked_backend();
//  		//p->add_stream(boost::make_shared< std::ofstream >("Sample.log"));
//  		//p->add_stream(boost::shared_ptr< std::ostream >(vT));
//  
//  		boost::shared_ptr<std::ofstream> vt = open_file(m_strLogRootDirectory + "Server.log", 4);
//  		p->add_stream(vt);
// 
// // 		SYSTEMTIME st;
// // 		GetLocalTime(&st);
// 
// 
// 		src::severity_channel_logger< severity_level > lg(keywords::channel = "net");
// 		BOOST_LOG_SEV(lg, warning) << "KJK Server Start";
// 
// 		//Finsh_logging(sink);
// 
// 	}

// 	// You can also manage backend in a thread-safe manner
// 	{
// // 		sink_t::locked_backend_ptr p = sink->locked_backend();
// // 		p->add_stream(boost::make_shared< std::ofstream >("Sample.log"));
// 
// 		//boost::make_shared< std::ofstream > vT = boost::make_shared< std::ofstream >("Sample.log").get();
// 
// 
// 		//open_file("Sample.log", 4);
// 		//std::ofstream	ofStreamFile("Sample.log");
// 
// 
// 		//boost::shared_ptr< std::ofstream > vT = open_file("Sample.log", 4);
// 
// 		//boost::shared_ptr< std::ofstream > vT = boost::make_shared< std::ofstream >(open_file("Sample.log", 4));
// 		//boost::shared_ptr< std::ofstream > vT = boost::make_shared< std::ofstream >("Sample.log");
// 
// 
// 
// 		//void* v = boost::make_shared< std::ofstream >("Sample.log").get();
// 
// 
// 		sink_t::locked_backend_ptr p = sink->locked_backend();
// 		//p->add_stream(boost::make_shared< std::ofstream >("Sample.log"));
// 		//p->add_stream(boost::shared_ptr< std::ostream >(vT));
// 
// 		boost::shared_ptr<std::ofstream> vt = open_file("Sample.log", 4);
// 
// 		int a = 0;
// 
// 		p->add_stream(vt);
// 
// 		//shared_ptr< stream_type > const& strm;
// 		//p->add_stream();
// 		//p->set_auto_newline_mode(0);
// 		
// 
// 		//////////////////////////////////////////////////////////////////////////
// 		//일자로 파일 만드는 영역!!
// // 		SYSTEMTIME st;
// // 		GetLocalTime(&st);
// // 
// // 		//! 경로가 잇는경우 만들어줌!
// // 		if (m_strLogRootDirectory.empty()) //! 문자열이 비었을때
// // 		{
// // 			//! 기본 디렉토리에 파일을 만든다!!
// // 			std::string strTmp = format_string("log%d%02d%02d_%02d%02d%02d,log", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
// // 			p->add_stream(boost::make_shared< std::ofstream >(strTmp));
// // 		}
// // 		else //! 문자열 정보가 있음!
// // 		{
// // 			//format_string("%d_%02d_%02d_%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond)
// // 
// // 			std::string strPath = gf_GetModulePathA() + "LOG\\" + format_string("%d02d", st.wYear, st.wMonth);
// // 			std::string strTmp = format_string("%d%02d%02d.log", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
// // 			p->add_stream(boost::make_shared< std::ofstream >(m_strLogRootDirectory));
// // 		}
// 
// 
// 	} // the backend gets released here

	return sink;
}
//]

//[ example_sinks_async_stop
void CBoostLog::stop_logging(boost::shared_ptr< sink_t >& sink)
{
	if (!sink)
		return;


	sink->flush();
}
//]


void CBoostLog::Finsh_logging(boost::shared_ptr< sink_t >& sink)
{
	if (!sink)
		return;

	boost::shared_ptr< logging::core > core = logging::core::get();

	// Remove the sink from the core, so that no records are passed to it
	core->remove_sink(sink);
	


	// Break the feeding loop
	sink->stop();

	// Flush all log records that may have left buffered
	sink->flush();

	sink.reset();

	sink = NULL;
}