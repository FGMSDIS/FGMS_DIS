/**
 * @file fg_tracker.cxx
 * @author (c) 2006 Julien Pierru
 * @author (c) 2012 Rob Dosogne ( FreeBSD friendly )
 *
 * @todo Pete To make a links here to the config and explain a bit
 *
 */

//////////////////////////////////////////////////////////////////////
//
//  server tracker for FlightGear
//  (c) 2006 Julien Pierru
//  (c) 2012 Rob Dosogne ( FreeBSD friendly )
//
//  Licenced under GPL
//
//////////////////////////////////////////////////////////////////////
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <string.h>
#include <sstream>
#ifndef _MSC_VER
#include <errno.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#endif
#include <unistd.h>
#include <stdio.h>
#include "fg_common.hxx"
#include "fg_tracker.hxx"
#include "fg_util.hxx"
#include <simgear/debug/logstream.hxx>
#include "daemon.hxx"
#include <libcli/debug.hxx>

#if defined(_MSC_VER) || defined(__MINGW32__)
/* windows work around for gettimeofday() */
int gettimeofday(struct timeval* tp, void* tzp) 
{
    LARGE_INTEGER t;

    if(QueryPerformanceCounter(&t)) {
        /* hardware supports a performance counter */
        static int been_here = 0;
        static LARGE_INTEGER f;
        if( !been_here ) {
            been_here = 1;
            QueryPerformanceFrequency(&f);
        }
        tp->tv_sec = t.QuadPart/f.QuadPart;
        tp->tv_usec = ((float)t.QuadPart/f.QuadPart*1000*1000)
                  - (tp->tv_sec*1000*1000);
    } else {
        /* hardware doesn't support a performance counter, so get the
               time in a more traditional way. */
        DWORD t;
        t = timeGetTime();
        tp->tv_sec = t / 1000;
        tp->tv_usec = t % 1000;
    }

    /* 0 indicates that the call succeeded. */
    return 0;
}
#endif /* #if defined(_MSC_VER) || defined(__MINGW32__) */

//////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize to standard values
 * @param port
 * @param server ip or domain
 * @param id  what is id? -- todo --
 */
FG_TRACKER::FG_TRACKER ( int port, string server, int id )
{
	m_TrackerPort	= port;
	m_TrackerServer = server;
	m_TrackerSocket = 0;
	SG_LOG ( SG_FGTRACKER, SG_DEBUG, "# FG_TRACKER::FG_TRACKER:"
	            << m_TrackerServer << ", Port: " << m_TrackerPort
	          );
	LastSeen	= 0;
	LastSent	= 0;
	BytesSent	= 0;
	BytesRcvd	= 0;
	PktsSent	= 0;
	PktsRcvd	= 0;
	LostConnections = 0;
	LastConnected	= 0;
	WantExit	= false;
} // FG_TRACKER()

//////////////////////////////////////////////////////////////////////
/**
 * @brief xTerminate the tracker
 */
FG_TRACKER::~FG_TRACKER ()
{
	pthread_mutex_unlock ( &msg_mutex ); // give up the lock
	WriteQueue ();
	msg_queue.clear ();
	if ( m_TrackerSocket )
	{
		m_TrackerSocket->close ();
		delete m_TrackerSocket;
		m_TrackerSocket = 0;
	}
} // ~FG_TRACKER()
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
pthread_t
FG_TRACKER::GetThreadID
()
{
	return MyThreadID;
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
void
FG_TRACKER::WriteQueue ()
{
	VI CurrentMessage;
	ofstream queue_file;
	pthread_mutex_lock ( &msg_mutex ); // set the lock
	if ( msg_queue.size() == 0 )
	{
		pthread_mutex_unlock ( &msg_mutex ); // give up the lock
		return;
	}
	queue_file.open ( "queue_file", ios::out|ios::app );
	if ( ! queue_file )
	{
		SG_LOG ( SG_FGTRACKER, SG_ALERT, "# FG_TRACKER::WriteQueue: "
		            << "could not open queuefile!" );
		pthread_mutex_unlock ( &msg_mutex ); // give up the lock
		return;
	}
	CurrentMessage = msg_queue.begin(); // get first message
	while ( CurrentMessage != msg_queue.end() )
	{
		queue_file << ( *CurrentMessage ) << endl;
		CurrentMessage++;
	}
	pthread_mutex_unlock ( &msg_mutex ); // set the lock
	queue_file.close ();
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
void
FG_TRACKER::AddMessage
(
        const string& message
)
{
	pthread_mutex_lock ( &msg_mutex ); // acquire the lock
#if 0
	if ( msg_queue.size () > 512 )
	{
		SG_LOG ( SG_FGTRACKER, SG_ALERT, "# FG_TRACKER queue full, writeing backlog..." );
		pthread_mutex_unlock ( &msg_mutex ); // give up the lock
		WriteQueue ();
		msg_queue.clear();
	}
#endif
	msg_queue.push_back ( message.c_str() ); // queue the message
	pthread_cond_signal ( &condition_var );  // wake up the worker
	pthread_mutex_unlock ( &msg_mutex );	 // give up the lock
} // FG_TRACKER::AddMessage()
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
int
FG_TRACKER::TrackerWrite ( const string& str )
{
	size_t l   = str.size() + 1;
	LastSent   = time ( 0 );
	errno      = 0;
	int s   = -1;
	while ( s < 0 )
	{
		s = m_TrackerSocket->send ( str.c_str(), l, MSG_NOSIGNAL );
		if ( s < 0 )
		{
			if ( errno == EAGAIN ) /*|| ( errno == EWOULDBLOCK ) ) //EWOULDBLOCK not under windows available*/
			{
				continue;
			}
			m_connected = false;
			LostConnections++;
			SG_LOG ( SG_FGTRACKER, SG_ALERT, "# FG_TRACKER::TrackerWrite: "
			            << "lost connection to server"
			          );
			return -1;
		}
	}
	BytesSent += s;
	PktsSent++;
	return s;
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
void
FG_TRACKER::ReplyToServer ( const string& str )
{
	string reply;
	if ( str == "OK" )
	{
		// set timeout time to 0
		return;
	}
	else if ( str == "PING" )
	{
		reply = "PONG STATUS OK";
		if ( TrackerWrite ( reply ) < 0 )
		{
			return;
		}
		SG_LOG ( SG_FGTRACKER, SG_DEBUG, "# FG_TRACKER::ReplyToServer: "
		            << "PING from server received"
		          );
		return;
	}
	SG_LOG ( SG_FGTRACKER, SG_ALERT, "# FG_TRACKER::ReplyToServer: "
	            << "Responce not recognized. Msg: '" << str
	          );
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
void
FG_TRACKER::ReadQueue ()
{
//////////////////////////////////////////////////
// FIXME: this needs a better mechanism.
// This is fire and forget, and forgets
// messages if the server is not reachable
//////////////////////////////////////////////////
	ifstream queue_file;
	queue_file.open ( "queue_file" );
	if ( ! queue_file )
	{
		return;
	}
	string line;
	int    line_number = 0;
	while ( getline ( queue_file, line, '\n' ) )
	{
		line_number++;
		pthread_mutex_lock ( &msg_mutex );	 // set the lock
		msg_queue.push_back ( line ); // queue the message
		pthread_mutex_unlock ( &msg_mutex );	 // give up the lock
#if 0
		if ( TrackerWrite ( line ) < 0 )
		{
			SG_LOG ( SG_FGTRACKER, SG_ALERT, "# FG_TRACKER::FG_TRACKER: "
			            << "lost connection while sending queue after " << line_number
			            << " entries"
			          );
			m_connected = false;
			queue_file.close();
			return;
		}
		TrackerRead ();
#endif
	}
	queue_file.close();
	remove ( "queue_file" );
}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
void
FG_TRACKER::TrackerRead ()
{
	char	res[MSGMAXLINE];	/*Msg from/to server*/
	errno = 0;
	int i = m_TrackerSocket->recv ( res, MSGMAXLINE, MSG_NOSIGNAL );
	if ( i <= 0 )
	{
		// error
		if ( ( errno != EAGAIN ) /*&& ( errno != EWOULDBLOCK )*/ && ( errno != EINTR ) )
		{
			m_connected = false;
			LostConnections++;
			SG_LOG ( SG_FGTRACKER, SG_ALERT, "# FG_TRACKER::TrackerRead: "
			            << "lost connection to server"
			          );
		}
	}
	else
	{
		// something received from tracker server
		res[i]='\0';
		LastSeen = time ( 0 );
		PktsRcvd++;
		BytesRcvd += i;
		ReplyToServer ( res );
	}
}
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/**
 * @brief Signal handling
 * @param s int with the signal
 */
void
signal_handler ( int s )
{
#ifndef _MSC_VER
	switch ( s )
	{
	case  1:
		printf ( "SIGHUP received, exiting...\n" );
		exit ( 0 );
		break;
	case  2:
		printf ( "SIGINT received, exiting...\n" );
		exit ( 0 );
		break;
	case  3:
		printf ( "SIGQUIT received, exiting...\n" );
		break;
	case  4:
		printf ( "SIGILL received\n" );
		break;
	case  5:
		printf ( "SIGTRAP received\n" );
		break;
	case  6:
		printf ( "SIGABRT received\n" );
		break;
	case  7:
		printf ( "SIGBUS received\n" );
		break;
	case  8:
		printf ( "SIGFPE received\n" );
		break;
	case  9:
		printf ( "SIGKILL received\n" );
		exit ( 0 );
		break;
	case 10:
		printf ( "SIGUSR1 received\n" );
		break;
	case 11:
		printf ( "SIGSEGV received. Exiting...\n" );
		exit ( 1 );
		break;
	case 12:
		printf ( "SIGUSR2 received\n" );
		break;
	case 13:
		printf ( "SIGPIPE received. Connection Error.\n" );
		break;
	case 14:
		printf ( "SIGALRM received\n" );
		break;
	case 15:
		printf ( "SIGTERM received\n" );
		exit ( 0 );
		break;
	case 16:
		printf ( "SIGSTKFLT received\n" );
		break;
	case 17:
		printf ( "SIGCHLD received\n" );
		break;
	case 18:
		printf ( "SIGCONT received\n" );
		break;
	case 19:
		printf ( "SIGSTOP received\n" );
		break;
	case 20:
		printf ( "SIGTSTP received\n" );
		break;
	case 21:
		printf ( "SIGTTIN received\n" );
		break;
	case 22:
		printf ( "SIGTTOU received\n" );
		break;
	case 23:
		printf ( "SIGURG received\n" );
		break;
	case 24:
		printf ( "SIGXCPU received\n" );
		break;
	case 25:
		printf ( "SIGXFSZ received\n" );
		break;
	case 26:
		printf ( "SIGVTALRM received\n" );
		break;
	case 27:
		printf ( "SIGPROF received\n" );
		break;
	case 28:
		printf ( "SIGWINCH received\n" );
		break;
	case 29:
		printf ( "SIGIO received\n" );
		break;
	case 30:
		printf ( "SIGPWR received\n" );
		break;
	default:
		printf ( "signal %d received\n",s );
	}
#endif
}

// eof - fg_tracker.cxx
//////////////////////////////////////////////////////////////////////
