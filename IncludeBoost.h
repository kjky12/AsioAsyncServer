#pragma once


//////////////////////////////////////////////////////////////////////////
//! INCLUDE BOOST CLASS
//////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <iostream>
#include <string>
#include <fstream>


//////////////////////////////////////////////////////////////////////////
//! includ : asio ¼­¹ö 
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>


#include <boost/pool/pool.hpp>
#include <boost/pool/singleton_pool.hpp>

#include <boost/function.hpp>
#include <boost/lockfree/queue.hpp>


using boost::asio::ip::tcp;

//////////////////////////////////////////////////////////////////////////
//! includ : log
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <boost/log/trivial.hpp>

#include <boost/log/expressions/formatters/date_time.hpp>
// Supporting headers
#include <boost/log/support/date_time.hpp>

#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
