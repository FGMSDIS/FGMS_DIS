/**
 * @file main.cxx
 * @author Oliver Schroeder
 * @brief Main Program
 *
 */

//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, U$
//
// Copyright (C) 2006  Oliver Schroeder
//

//////////////////////////////////////////////////////////////////////
//
// main program
//
//////////////////////////////////////////////////////////////////////
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>
#ifndef _MSC_VER
#include <sys/wait.h>
#endif
#include <signal.h>
#include "fg_server.hxx"
#include "fg_config.hxx"
#include "daemon.hxx"
#include "fg_util.hxx"

using namespace std;

/** @brief The running  ::FG_SERVER server process */
FG_SERVER       Servant;

/** @brief Flag whether instance is a Daemon  */
extern  bool    RunAsDaemon;
#ifdef _MSC_VER
#define M_IS_DIR _S_IFDIR
#else // !_MSC_VER
#define M_IS_DIR S_IFDIR
/** @brief An instance of ::cDaemon */
extern  cDaemon Myself;
#endif

/** @brief Must have a config file, with server name */
static bool     bHadConfig = false;

/** @def DEF_CONF_FILE
 *  @brief The default config file to load unless overriden on \ref command_line
 */
#ifndef DEF_CONF_FILE
#define DEF_CONF_FILE "fgms.conf"
#endif

/** @def SYSCONFDIR
 *  @brief The default config directory
 */
#ifndef SYSCONFDIR
#define SYSCONFDIR "/usr/etc"
#endif

//////////////////////////////////////////////////////////////////////
/**
 * @brief Print a help screen for command line parameters, see \ref command_line
 */
void
PrintHelp ()
{
	cout << "fgms: version " << VERSION << ", compiled on " << __DATE__ << ", at " << __TIME__ << endl;
	cout << "\n"
	     "options are:\n"
	     "-h            print this help screen\n"
	     "-a PORT       listen to PORT for telnet\n"
	     "-c config     read 'config' as configuration file\n"
	     "-p PORT       listen to PORT\n"
	     "-t TTL        Time a client is active while not sending packets\n"
	     "-o OOR        nautical miles two players must be apart to be out of reach\n"
	     "-l LOGFILE    Log to LOGFILE\n"
	     "-v LEVEL      verbosity (loglevel) in range 1 (few) and 5 (much)\n"
	     "-d            do _not_ run as a daemon (stay in foreground)\n"
	     "-D            do run as a daemon\n"
	     "\n"
	     "the default is to run as a daemon, which can be overridden in the\n"
	     "config file.\n"
	     "\n";
	exit ( 0 );
} // PrintHelp ()
//////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
// kludge for getopt() for WIN32
static char* optarg;
static int curr_arg = 0;
int getopt ( int argcount, char* argvars[], char* args )
{
	size_t len = strlen ( args );
	size_t i;
	int c = 0;
	if ( curr_arg == 0 )
	{
		curr_arg = 1;
	}
	if ( curr_arg < argcount )
	{
		char* arg = argvars[curr_arg];
		if ( *arg == '-' )
		{
			arg++;
			c = *arg; // get first char
			for ( i = 0; i < len; i++ )
			{
				if ( c == args[i] )
				{
					// found
					if ( args[i+1] == ':' )
					{
						// fill in following
						curr_arg++;
						optarg = argvars[curr_arg];
					}
					break;
				}
			}
			curr_arg++;
			return c;
		}
		else
		{
			return '-';
		}
	}
	return -1;
}
#endif // _MSC_VER

//////////////////////////////////////////////////////////////////////
/**
 * @brief Read a config file and set internal variables accordingly
 * @param ConfigName Path of config file to load
 * @retval int  -- todo--
 */
bool
ProcessConfig ( const string& ConfigName )
{
	FG_CONFIG   Config;
	string      Val;
	int         E;
	if ( bHadConfig )	// we already have a config, so ignore
	{
		return ( true );
	}
	if ( Config.Read ( ConfigName ) )
	{
		bHadConfig = true;
		SG_LOG ( SG_SYSTEMS, SG_ALERT,
		  "Could not read config file '" << ConfigName
		  << "' => using defaults");
		return ( false );
	}
	cout << "processing " << ConfigName << endl;
	Servant.ConfigFile =  ConfigName;
	Val = Config.Get ( "server.name" );
	if ( Val != "" )
	{
		Servant.SetServerName ( Val );
		Servant.SetMyCallsign ( Val );
		bHadConfig = true; // got a serve name - minimum
	}
	Val = Config.Get ( "server.address" );
	if ( Val != "" )
	{
		Servant.SetBindAddress ( Val );
		cout << "server.address " << Val << endl;
	}
	Val = Config.Get ( "server.port" );
	if ( Val != "" )
	{
		cout << "server.port " << Val << endl;
		Servant.SetFromFGPort ( StrToNum<int> ( Val.c_str (), E ) );
		if ( E )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "invalid value for DataPort: '" << optarg << "'" );
			exit ( 1 );
		}
	}
	Val = Config.Get ( "server.DIS_address" );
	if ( Val != "" )
	{
		Servant.SetDISAddress ( Val );
		cout << "server.DIS_address " << Val << endl;
	}
	Val = Config.Get ( "server.DIS_port" );
	if ( Val != "" )
	{
		cout << "server.DIS_port " << Val << endl;
		Servant.SetDISPort ( StrToNum<int> ( Val.c_str (), E ) );
		if ( E )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "invalid value for DISPort: '" << optarg << "'" );
			exit ( 1 );
		}
	}

	Val = Config.Get ( "server.DIS_Site" );
	if ( Val != "" )
	{
		cout << "server.DIS_Site " << Val << endl;
		Servant.SetDISSite ( StrToNum<int> ( Val.c_str (), E ) );
		if ( E )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "invalid value for DIS-Site: '" << optarg << "'" );
			exit ( 1 );
		}
	}

	Val = Config.Get ( "server.DIS_Application" );
	if ( Val != "" )
	{
		cout << "server.DIS_Application " << Val << endl;
		Servant.SetDISAppl ( StrToNum<int> ( Val.c_str (), E ) );
		if ( E )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "invalid value for DIS-Application: '" << optarg << "'" );
			exit ( 1 );
		}
	}

	Val = Config.Get ( "server.forceID" );
	if ( Val != "" )
	{
		cout << "server.forceID " << Val << endl;
		Servant.SetForceID ( StrToNum<int> ( Val.c_str (), E ) );
		if ( E )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "invalid value for forceID: '" << optarg << "'" );
			exit ( 1 );
		}
	}

	Val = Config.Get ( "server.DIS_FGUpdaterate" );
	if ( Val != "" )
	{		
		cout << "server.DIS_FGUpdaterate " << Val << endl;
		Servant.SetDIS2FGUpdaterate ( StrToNum<double> ( Val.c_str (), E ) );
		if ( E )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "invalid value for DIS-FGUpdaterate: '" << optarg << "'" );
			exit ( 1 );
		}
	}
	Val = Config.Get ( "server.out_of_reach" );
	if ( Val != "" )
	{
		cout << "server.out_of_reach " << Val << endl;
		Servant.SetOutOfReach ( StrToNum<int> ( Val.c_str (), E ) );
		if ( E )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "invalid value for OutOfReach: '" << optarg << "'" );
			exit ( 1 );
		}
	}
	Val = Config.Get ( "server.radarActive" );
	if ( Val != "" )
	{
		cout << "radarActive " << Val << endl;
		if ( ( Val == "on" ) || ( Val == "true" ) )
		{
			Servant.SetRadarActive( true );
		}
		else if ( ( Val == "off" ) || ( Val == "false" ) )
		{
			Servant.SetRadarActive( false );
		}
		else
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "unknown value for 'server.radarActive'!" << " in file " << ConfigName );
		}
	}
	Val = Config.Get ( "server.playerexpires" );
	if ( Val != "" )
	{
		cout << "server.playerexpires " << Val << endl;
		Servant.SetPlayerExpires ( StrToNum<int> ( Val.c_str (), E ) );
		if ( E )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "invalid value for Expire: '" << optarg << "'" );
			exit ( 1 );
		}
	}
	Val = Config.Get ( "server.daemon" );
	if ( Val != "" )
	{
		if ( ( Val == "on" ) || ( Val == "true" ) )
		{
			RunAsDaemon = true;
		}
		else if ( ( Val == "off" ) || ( Val == "false" ) )
		{
			RunAsDaemon = false;
		}
		else
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "unknown value for 'server.daemon'!" << " in file " << ConfigName );
		}
	}

	//////////////////////////////////////////////////
	return ( true );
} // ProcessConfig ( const string& ConfigName )

//////////////////////////////////////////////////////////////////////
/**
 * @brief Parse commandline parameters
 * @param argcount
 * @param argvars
 * @retval int 1 on success
 */
int
ParseParams ( int argcount, char* argvars[] )
{
	int     m;
	int     E;
	while ( ( m=getopt ( argcount,argvars,"a:b:c:dDhl:o:p:t:v:" ) ) != -1 )
	{
		switch ( m )
		{
		case 'h':
			cerr << endl;
			cerr << "syntax: " << argvars[0] << " options" << endl;
			PrintHelp ();
			break; // never reached
		case 'c':
			ProcessConfig ( optarg );
			break;
		case 'p':
			Servant.SetFromFGPort ( StrToNum<int>  ( optarg, E ) );
			if ( E )
			{
				cerr << "invalid value for DataPort: '"
				     << optarg << "'" << endl;
				exit ( 1 );
			}
			break;
		case 'o':
			Servant.SetOutOfReach ( StrToNum<int>  ( optarg, E ) );
			if ( E )
			{
				cerr << "invalid value for OutOfReach: '"
				     << optarg << "'" << endl;
				exit ( 1 );
			}
			break;
		case 't':
			Servant.SetPlayerExpires ( StrToNum<int>  ( optarg, E ) );
			if ( E )
			{
				cerr << "invalid value for expire: '"
				     << optarg << "'" << endl;
				exit ( 1 );
			}
			break;
		case 'd':
			RunAsDaemon = false;
			break;
		case 'D':
			RunAsDaemon = true;
			break;
		default:
			cerr << endl << endl;
			PrintHelp ();
			exit ( 1 );
		} // switch ()
	} // while ()
	return ( 1 ); // success
} // ParseParams()

//////////////////////////////////////////////////////////////////////
/**
 * @brief  (re)Read config files
 * @param ReInit True to reinitialize
 */
int
ReadConfigs ( bool ReInit = false )
{
	string Path;
#ifndef _MSC_VER
	Path = SYSCONFDIR;
	Path += "/" DEF_CONF_FILE; // fgms.conf
	if ( ProcessConfig ( Path ) == true )
	{
		return 1;
	}
	Path = getenv ( "HOME" );
#else
	char* cp = getenv ( "HOME" );
	if ( cp )
	{
		Path = cp;
	}
	else
	{
		cp = getenv ( "USERPROFILE" ); // XP=C:\Documents and Settings\<name>, Win7=C:\Users\<user>
		if ( cp )
		{
			Path = cp;
		}
	}
#endif
	if ( Path != "" )
	{
		Path += "/" DEF_CONF_FILE;
		if ( ProcessConfig ( Path ) )
		{
			return 1;
		}
	}
	if ( ProcessConfig ( DEF_CONF_FILE ) )
	{
		return 1;
	}
	return 0;
} // ReadConfigs ()



//////////////////////////////////////////////////////////////////////
/**
 * @brief If we receive a SIGHUP, reinit application
 * @param SigType int with signal type
 */
void SigHUPHandler ( int SigType )
{
	Servant.PrepareInit();
	bHadConfig = false;
	if (Servant.ConfigFile == "")
	{
		if ( !ReadConfigs ( true ) )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "received HUP signal, but read config file failed!" );
			exit ( 1 );
		}
	}
	else
	{
		if ( ProcessConfig ( Servant.ConfigFile ) == false )
		{
			SG_LOG ( SG_SYSTEMS, SG_ALERT, "received HUP signal, but read config file failed!" );
			exit ( 1 );
		}
	}
	if ( Servant.Init () != 0 )
	{
		SG_LOG ( SG_SYSTEMS, SG_ALERT, "received HUP signal, but reinit failed!" );
		exit ( 1 );
	}
#ifndef _MSC_VER
	signal ( SigType, SigHUPHandler );
#endif
} // SigHUPHandler ()
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/**
 * @brief MAIN routine
 * @param argc
 * @param argv*[]
 */
int
main ( int argc, char* argv[] )
{
	int     I;
#ifndef _MSC_VER
	signal ( SIGHUP, SigHUPHandler );
#endif
	ParseParams ( argc, argv );
	ReadConfigs ();
	if ( !bHadConfig )
	{
		SG_LOG ( SG_SYSTEMS, SG_ALERT, "No configuration file '" << DEF_CONF_FILE << "' found!" );
		exit ( 1 );
	}
#ifndef _MSC_VER
	if ( RunAsDaemon )
	{
		Myself.Daemonize ();
	}
#endif
	I = Servant.Init ();
	if ( I != 0 )
	{
		return ( I );
	}
	SG_CONSOLE ( SG_SYSTEMS, SG_ALERT, "Main server started!" );
	I = Servant.incomingMessageEvent_Loop();
	Servant.Done();
	return ( I );
} // main()
//////////////////////////////////////////////////////////////////////

