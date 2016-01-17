#
# single CMakeLists.txt for fgms-0-x - hand crafted - commenced 2012/07/03
# 20130411 - Change to use external version file
# 20121130 - Add link_directories ( ${PostgreSQL_LIBRARY_DIR} ) at least for WIN32 - AGE 26
# 20121025 - Add a windows 'perror' macro PERROR, and minor changes in crossfeed code - age 25
# 20121018 - Try to get the unix install to /usr/sbin right, and bump age to 24
# 20120815 - In Unix, install to /usr/sbin if CMAKE_INSTALL_PREFIX not given - default is /usr/local/sbin
#            Bump AGE to 20, since a number of other commits done.
# 20120808 - Change the IPCKEY value if building mp_server2 - bumped AGE to 19
# 20120723 - Add ENABLE_DEBUG_OUTPUT, which defines DEF_DEBUG_OUTPUT in fg_tracker.cxx
# and add USE_PTHREAD_IN_TRACKER server, replacing fork()

cmake_minimum_required( VERSION 2.8.8 )

project( fgms )

##################################################
#####       the version of the program
#####
#####       Increment AGE if source code
#####       has changed at all (e.g. bugfix)
#####
#####       If fgms has new features but is still
#####       protocol compatible increment MINOR
#####       and set AGE to 0
#####
#####       If fgms gets incompatible with older
#####       version increment MAJOR and set MINOR
#####       and AGE to 0
#####
#####       See the 'version' file
##################################################
# read 'version' file into a variable (stripping any newlines or spaces)
file(READ version versionFile)
if (NOT versionFile)
    message(FATAL_ERROR "Unable to determine FGMS version. 'version' file is missing.")
endif()
string(STRIP "${versionFile}" FGMS_VERSION)


# change names if build server and tracker #2
set( EXE_NAME fgms )
set( TRK_NAME fgt_server )

# directories
IF(NOT DEFINED USER_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr")
  message(STATUS "*** Set CMAKE_INSTALL_PREFIX to ${CMAKE_INSTALL_PREFIX}")
ELSE(NOT DEFINED USER_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX ${USER_INSTALL_PREFIX})
  message(STATUS "*** Set CMAKE_INSTALL_PREFIX to user ${CMAKE_INSTALL_PREFIX}")
ENDIF(NOT DEFINED USER_INSTALL_PREFIX)
if (NOT DEFINED SYSCONFDIR)
    set ( SYSCONFDIR "${CMAKE_INSTALL_PREFIX}/etc" )
endif (NOT DEFINED SYSCONFDIR)
if (NOT DEFINED SBINDIR)
    set ( SBINDIR "${CMAKE_INSTALL_PREFIX}/sbin" )
endif (NOT DEFINED SBINDIR)
add_definitions( -DSYSCONFDIR="${SYSCONFDIR}" )

# Allow developer to select is Dynamic or static library built
set( LIB_TYPE STATIC )  # set default static
option( BUILD_SHARED_LIB "Build Shared Library" OFF )
option( BUILD_TRACKER "Build 'tracker' server and client" OFF )
option( BUILD_SERVER2 "Build a server with different defaults" OFF )
option( ENABLE_TRACKER_LOG "Enable a tracker message log." OFF )
option( USE_POSTGRESQL "Use a PostgreSQL database in the tracking server." ON )
if(UNIX)
    option( ENABLE_DEBUG_SYMBOLS "Add debug symbols into the binary." OFF )
endif(UNIX)
option( ENABLE_DEBUG_OUTPUT "Enable some extra debug output in fg_tracker.cxx." OFF )
# this should not be confused with the fact that pthread is used in fgms by default. This is in the fgt_server server.c
# and of course need to be building the 'tracker' for this to have any effect.
option( USE_PTHREAD_IN_TRACKER "Use pthread in the tracker server, replacing fork()." OFF )

if(CMAKE_COMPILER_IS_GNUCXX)
    set( WARNING_FLAGS -Wall )
endif(CMAKE_COMPILER_IS_GNUCXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") 
   set( WARNING_FLAGS "-Wall -Wno-overloaded-virtual" )
endif() 

if(WIN32)
    if(MSVC)
        # turn off various warnings
        set(WARNING_FLAGS "${WARNING_FLAGS} /wd4996")
        # C4146: unary minus operator applied to unsigned type, result still unsigned
        # C4267: '=' : conversion from 'size_t' to 'int', possible loss of data
        # foreach(warning 4244 4251 4267 4275 4290 4786 4305)
        foreach(warning 4146 4267)
            set(WARNING_FLAGS "${WARNING_FLAGS} /wd${warning}")
        endforeach()

        set( EXTRA_FLAGS "-DNOMINMAX -D_USE_MATH_DEFINES -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D__CRT_NONSTDC_NO_WARNINGS" )
        # if (${MSVC_VERSION} EQUAL 1600)
        #    list(APPEND EXTRA_LD_FLAGS "/FORCE:MULTIPLE" )
        # endif (${MSVC_VERSION} EQUAL 1600)
    endif(MSVC)
    set( NOMINMAX 1 )
    add_definitions( -DUL_MSVC -DOPENALSDK -DHAVE_CONFIG_H -DFREEGLUT_LIB_PRAGMAS -DUL_WIN32 -D_CRT_SECURE_NO_DEPRECATE -DFREEGLUT_STATIC )
    configure_file( "${CMAKE_SOURCE_DIR}/config.h.msvc" "${CMAKE_BINARY_DIR}/config.h" COPY_ONLY)
    file(WRITE "${CMAKE_BINARY_DIR}/unistd.h" "/* dummy unistd.h for windows */") 
else(WIN32)
    if(ENABLE_DEBUG_SYMBOLS)
        list(APPEND EXTRA_FLAGS "-g")
    endif(ENABLE_DEBUG_SYMBOLS)
    list(APPEND EXTRA_LD_FLAGS -L.)
    set( WARNING_FLAGS "${WARNING_FLAGS} -Wno-unused-local-typedefs -Wno-unused-but-set-variable" )
endif(WIN32)

if(ENABLE_TRACKER_LOG)
    add_definitions( -DENABLE_TRACKER_LOG )
endif(ENABLE_TRACKER_LOG)

if(BUILD_SERVER2)
    set( EXE_NAME mp_server2 )
    set( TRK_NAME mpt_server2 )
    add_definitions( -DDEF_SERVER_LOG="fg_server2.log" -DDEF_EXIT_FILE="fgms_exit2"
        -DDEF_RESET_FILE="fgms_reset2" -DDEF_STAT_FILE="fgms_stat2" -DDEF_CONF_FILE="fgms2.conf"
        -DIPCKEY=0xf9f6 )
    message(STATUS "*** Building server 2. File fg_server2.log fgms_exit2 fgms_reset2 fgms_stat2 fgms2.conf")
endif(BUILD_SERVER2)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS} ${EXTRA_FLAGS} -D_REENTRANT" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} ${EXTRA_FLAGS} -D_REENTRANT" )
set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_LD_FLAGS}" )
message(STATUS "*** set CXX FLAGS [${CMAKE_CXX_FLAGS}] C FLAGS [${CMAKE_C_FLAGS}]")

add_definitions( -DVERSION="${FGMS_VERSION}" )

if(ENABLE_DEBUG_OUTPUT)
   add_definitions( -DDEF_DEBUG_OUTPUT=true )
endif(ENABLE_DEBUG_OUTPUT)

# to distinguish between debug and release lib
if (WIN32)
set( CMAKE_DEBUG_POSTFIX "d" )
endif (WIN32)

if(BUILD_SHARED_LIB)
   set(LIB_TYPE SHARED)
   message(STATUS "*** Building DLL library ${LIB_TYPE}")
else(BUILD_SHARED_LIB)
   message(STATUS "*** Building static library ${LIB_TYPE}")
endif(BUILD_SHARED_LIB)

include_directories( SYSTEM "${PROJECT_BINARY_DIR}" src src/flightgear/MultiPlayer src/plib src/simgear/debug src/server
src/libcli src/pugixml src/openDIS src/openDIS/DIS src/dis_gateway )

### add_subdirectory( src/server )
# Project [fg_server] [Static Library] [noinst_LIBRARIES], with 6 sources. 12 hdrs.
set( fg_server_SRCS 
    src/server/fg_server.cxx 
    src/server/fg_tracker.cxx 
    src/server/fg_config.cxx 
    src/server/fg_list.cxx 
    src/server/fg_cli.cxx 
    src/server/fg_util.cxx 
    src/server/daemon.cxx 
    src/server/fg_geometry.cxx )
set( fg_server_HDRS  src/server/fg_server.hxx src/server/fg_tracker.hxx 
    src/server/fg_config.hxx src/server/fg_list.hxx 
    src/server/fg_cli.hxx
    src/server/daemon.hxx src/server/fg_util.hxx 
    src/server/fg_common.hxx )
add_library( fg_server ${LIB_TYPE} ${fg_server_SRCS} ${fg_server_HDRS} )
# NO INSTALL [noinst_LIBRARIES]
if(WIN32)
    list( APPEND add_LIBS fg_server )
else(WIN32)
    list(APPEND add_LIBS -lfg_server)
endif(WIN32)

#### add_subdirectory( src/flightgear/MultiPlayer )
# Project [MultiPlayer] [Static Library] [noinst_LIBRARIES], with 1 sources. 7 hdrs.
set( MultiPlayer_SRCS src/flightgear/MultiPlayer/tiny_xdr.cxx )
set( MultiPlayer_HDRS src/flightgear/MultiPlayer/tiny_xdr.hxx 
    src/flightgear/MultiPlayer/mpmessages.hxx )
add_library( MultiPlayer ${LIB_TYPE} ${MultiPlayer_SRCS} ${MultiPlayer_HDRS} )
# NO INSTALL [noinst_LIBRARIES]
if(WIN32)
    list(APPEND add_LIBS MultiPlayer)
else(WIN32)
    list(APPEND add_LIBS -lMultiPlayer)
endif(WIN32)

#### add_subdirectory( src/plib )
# Project [plib] [Static Library] [noinst_LIBRARIES], with 1 sources. 1 hdrs.
set( plib_SRCS src/plib/netSocket.cxx )
set( plib_HDRS src/plib/netSocket.h )
add_library( Plib ${LIB_TYPE} ${plib_SRCS} ${plib_HDRS} )
# NO INSTALL [noinst_LIBRARIES]
if(WIN32)
    list(APPEND add_LIBS Plib)
else(WIN32)
    list(APPEND add_LIBS -lPlib)
endif(WIN32)

#### add_subdirectory( src/libcli )
# Project [plib] [Static Library] [noinst_LIBRARIES], with 1 sources. 1 hdrs.
set( libcli_SRCS
    src/libcli/debug.cxx
    src/libcli/filter.cxx
    src/libcli/cli_client.cxx
    src/libcli/libcli.cxx
    )
set( libcli_HDRS
    src/libcli/common.hxx
    src/libcli/command.hxx
    src/libcli/debug.hxx
    src/libcli/filter.hxx
    src/libcli/cli_client.hxx
    src/libcli/libcli.hxx
    )
if (WIN32)
    list(APPEND libcli_SRCS src/libcli/crypt-win.c)
endif ()
add_library( LibCLI ${LIB_TYPE} ${libcli_SRCS} ${libcli_HDRS} )
if(WIN32)
    list(APPEND add_LIBS LibCLI)
else(WIN32)
    list(APPEND add_LIBS -lLibCLI -lcrypt)
endif(WIN32)

### add_subdirectory( src/simgear/debug )
# Project [sgdebug] [Static Library] [noinst_LIBRARIES], with 1 sources. 2 hdrs.
set( sgdebug_SRCS src/simgear/debug/logstream.cxx )
set( sgdebug_HDRS src/simgear/debug/debug_types.h 
   src/simgear/debug/logstream.hxx )
add_library( SGdebug ${LIB_TYPE} ${sgdebug_SRCS} ${sgdebug_HDRS} )
# NO INSTALL [noinst_LIBRARIES]
if(WIN32)
    list(APPEND add_LIBS SGdebug)
else(WIN32)
    list(APPEND add_LIBS -lSGdebug)
endif(WIN32)

### add_subdirectory( src/pugixml )
# Project [pugixml] [Static Library] [noinst_LIBRARIES], with 1 sources. 2 hdrs.
set( pugixml_SRCS src/pugixml/pugixml.cpp )
set( pugixml_HDRS 
	src/pugixml/pugixml.hpp 
	src/pugixml/pugiconfig.hpp )
add_library( pugixml ${LIB_TYPE} ${pugixml_SRCS} ${pugixml_HDRS} )
# NO INSTALL [noinst_LIBRARIES]
if(WIN32)
    list(APPEND add_LIBS pugixml)
else(WIN32)
    list(APPEND add_LIBS -lpugixml)
endif(WIN32)

### add_subdirectory( src/opendis/DIS )
# Project [openDIS] [Static Library] [noinst_LIBRARIES], with 147 sources. 148 hdrs.
set( openDIS_SRCS
	src/openDIS/DIS/AcknowledgePdu.cpp
	src/openDIS/DIS/AcknowledgeReliablePdu.cpp
	src/openDIS/DIS/AcousticBeamData.cpp
	src/openDIS/DIS/AcousticBeamFundamentalParameter.cpp
	src/openDIS/DIS/AcousticEmitter.cpp
	src/openDIS/DIS/AcousticEmitterSystem.cpp
	src/openDIS/DIS/AcousticEmitterSystemData.cpp
	src/openDIS/DIS/ActionRequestPdu.cpp
	src/openDIS/DIS/ActionRequestReliablePdu.cpp
	src/openDIS/DIS/ActionResponsePdu.cpp
	src/openDIS/DIS/ActionResponseReliablePdu.cpp
	src/openDIS/DIS/AggregateID.cpp
	src/openDIS/DIS/AggregateMarking.cpp
	src/openDIS/DIS/AggregateStatePdu.cpp
	src/openDIS/DIS/AggregateType.cpp
	src/openDIS/DIS/AngularVelocityVector.cpp
	src/openDIS/DIS/AntennaLocation.cpp
	src/openDIS/DIS/ApaData.cpp
	src/openDIS/DIS/ArealObjectStatePdu.cpp
	src/openDIS/DIS/ArticulationParameter.cpp
	src/openDIS/DIS/BeamAntennaPattern.cpp
	src/openDIS/DIS/BeamData.cpp
	src/openDIS/DIS/BurstDescriptor.cpp
	src/openDIS/DIS/ClockTime.cpp
	src/openDIS/DIS/CollisionElasticPdu.cpp
	src/openDIS/DIS/CollisionPdu.cpp
	src/openDIS/DIS/CommentPdu.cpp
	src/openDIS/DIS/CommentReliablePdu.cpp
	src/openDIS/DIS/Conversion.cpp
	src/openDIS/DIS/CreateEntityPdu.cpp
	src/openDIS/DIS/CreateEntityReliablePdu.cpp
	src/openDIS/DIS/DataPdu.cpp
	src/openDIS/DIS/DataQueryPdu.cpp
	src/openDIS/DIS/DataQueryReliablePdu.cpp
	src/openDIS/DIS/DataReliablePdu.cpp	
	src/openDIS/DIS/DataStream.cpp
	src/openDIS/DIS/DeadReckoningParameter.cpp
	src/openDIS/DIS/DesignatorPdu.cpp
	src/openDIS/DIS/DetonationPdu.cpp
	src/openDIS/DIS/DistributedEmissionsFamilyPdu.cpp
	src/openDIS/DIS/EightByteChunk.cpp
	src/openDIS/DIS/ElectronicEmissionBeamData.cpp
	src/openDIS/DIS/ElectronicEmissionsPdu.cpp
	src/openDIS/DIS/ElectronicEmissionSystemData.cpp
	src/openDIS/DIS/EmitterSystem.cpp
	src/openDIS/DIS/EntityID.cpp
	src/openDIS/DIS/EntityInformationFamilyPdu.cpp
	src/openDIS/DIS/EntityManagementFamilyPdu.cpp
	src/openDIS/DIS/EntityStatePdu.cpp
	src/openDIS/DIS/EntityStateUpdatePdu.cpp
	src/openDIS/DIS/EntityType.cpp
	src/openDIS/DIS/Environment.cpp
	src/openDIS/DIS/EnvironmentalProcessPdu.cpp
	src/openDIS/DIS/EventID.cpp
	src/openDIS/DIS/EventReportPdu.cpp
	src/openDIS/DIS/EventReportReliablePdu.cpp
	src/openDIS/DIS/FastEntityStatePdu.cpp
	src/openDIS/DIS/FirePdu.cpp
	src/openDIS/DIS/FixedDatum.cpp
	src/openDIS/DIS/FourByteChunk.cpp
	src/openDIS/DIS/FundamentalParameterData.cpp
	src/openDIS/DIS/FundamentalParameterDataIff.cpp
	src/openDIS/DIS/GridAxisRecord.cpp
	src/openDIS/DIS/GridAxisRecordRepresentation0.cpp
	src/openDIS/DIS/GridAxisRecordRepresentation1.cpp
	src/openDIS/DIS/GridAxisRecordRepresentation2.cpp
	src/openDIS/DIS/GriddedDataPdu.cpp
	src/openDIS/DIS/IffAtcNavAidsLayer1Pdu.cpp
	src/openDIS/DIS/IffAtcNavAidsLayer2Pdu.cpp
	src/openDIS/DIS/IffFundamentalData.cpp
	src/openDIS/DIS/IncomingMessage.cpp
	src/openDIS/DIS/IntercomCommunicationsParameters.cpp
	src/openDIS/DIS/IntercomControlPdu.cpp
	src/openDIS/DIS/IntercomSignalPdu.cpp
	src/openDIS/DIS/IsGroupOfPdu.cpp
	src/openDIS/DIS/IsPartOfPdu.cpp
	src/openDIS/DIS/LayerHeader.cpp
	src/openDIS/DIS/LinearObjectStatePdu.cpp
	src/openDIS/DIS/LinearSegmentParameter.cpp
	src/openDIS/DIS/LogisticsFamilyPdu.cpp
	src/openDIS/DIS/LogisticsPdu.cpp
	src/openDIS/DIS/Marking.cpp
	src/openDIS/DIS/MinefieldDataPdu.cpp
	src/openDIS/DIS/MinefieldFamilyPdu.cpp
	src/openDIS/DIS/MinefieldPduFamily.cpp
	src/openDIS/DIS/MinefieldQueryPdu.cpp
	src/openDIS/DIS/MinefieldResponseNackPdu.cpp
	src/openDIS/DIS/MinefieldStatePdu.cpp
	src/openDIS/DIS/ModulationType.cpp
	src/openDIS/DIS/NamedLocation.cpp
	src/openDIS/DIS/ObjectType.cpp
	src/openDIS/DIS/OneByteChunk.cpp
	src/openDIS/DIS/Orientation.cpp
	src/openDIS/DIS/PacketFactory.cpp
	src/openDIS/DIS/Pdu.cpp
	src/openDIS/DIS/PDUBank.cpp
	src/openDIS/DIS/PduContainer.cpp
	src/openDIS/DIS/PduFactory.cpp
	src/openDIS/DIS/Point.cpp
	src/openDIS/DIS/PointObjectStatePdu.cpp
	src/openDIS/DIS/PropulsionSystemData.cpp
	src/openDIS/DIS/RadioCommunicationsFamilyPdu.cpp
	src/openDIS/DIS/RadioEntityType.cpp
	src/openDIS/DIS/ReceiverPdu.cpp
	src/openDIS/DIS/RecordQueryReliablePdu.cpp
	src/openDIS/DIS/RecordSet.cpp
	src/openDIS/DIS/Relationship.cpp
	src/openDIS/DIS/RemoveEntityPdu.cpp
	src/openDIS/DIS/RemoveEntityReliablePdu.cpp
	src/openDIS/DIS/RepairCompletePdu.cpp
	src/openDIS/DIS/RepairResponsePdu.cpp
	src/openDIS/DIS/ResupplyCancelPdu.cpp
	src/openDIS/DIS/ResupplyOfferPdu.cpp
	src/openDIS/DIS/ResupplyReceivedPdu.cpp
	src/openDIS/DIS/SeesPdu.cpp
	src/openDIS/DIS/ServiceRequestPdu.cpp
	src/openDIS/DIS/SetDataPdu.cpp
	src/openDIS/DIS/SetDataReliablePdu.cpp
	src/openDIS/DIS/SetRecordReliablePdu.cpp
	src/openDIS/DIS/ShaftRPMs.cpp
	src/openDIS/DIS/SignalPdu.cpp
	src/openDIS/DIS/SimulationAddress.cpp
	src/openDIS/DIS/SimulationManagementFamilyPdu.cpp
	src/openDIS/DIS/SimulationManagementWithReliabilityFamilyPdu.cpp
	src/openDIS/DIS/SixByteChunk.cpp
	src/openDIS/DIS/SphericalHarmonicAntennaPattern.cpp
	src/openDIS/DIS/StartResumePdu.cpp
	src/openDIS/DIS/StartResumeReliablePdu.cpp
	src/openDIS/DIS/StopFreezePdu.cpp
	src/openDIS/DIS/StopFreezeReliablePdu.cpp
	src/openDIS/DIS/StreamUtils.cpp
	src/openDIS/DIS/SupplyQuantity.cpp
	src/openDIS/DIS/SyntheticEnvironmentFamilyPdu.cpp
	src/openDIS/DIS/SystemID.cpp
	src/openDIS/DIS/TrackJamTarget.cpp
	src/openDIS/DIS/TransferControlRequestPdu.cpp
	src/openDIS/DIS/TransmitterPdu.cpp
	src/openDIS/DIS/TwoByteChunk.cpp 
	src/openDIS/DIS/UaPdu.cpp 
	src/openDIS/DIS/VariableDatum.cpp 
	src/openDIS/DIS/Vector3Double.cpp 
	src/openDIS/DIS/Vector3Float.cpp 
	src/openDIS/DIS/VectoringNozzleSystemData.cpp 
	src/openDIS/DIS/WarfareFamilyPdu.cpp )
set( openDIS_HDRS 
	src/openDIS/DIS/AcknowledgePdu.h
	src/openDIS/DIS/AcknowledgeReliablePdu.h
	src/openDIS/DIS/AcousticBeamData.h
	src/openDIS/DIS/AcousticBeamFundamentalParameter.h
	src/openDIS/DIS/AcousticEmitter.h
	src/openDIS/DIS/AcousticEmitterSystem.h
	src/openDIS/DIS/AcousticEmitterSystemData.h
	src/openDIS/DIS/ActionRequestPdu.h
	src/openDIS/DIS/ActionRequestReliablePdu.h
	src/openDIS/DIS/ActionResponsePdu.h
	src/openDIS/DIS/ActionResponseReliablePdu.h
	src/openDIS/DIS/AggregateID.h
	src/openDIS/DIS/AggregateMarking.h
	src/openDIS/DIS/AggregateStatePdu.h
	src/openDIS/DIS/AggregateType.h
	src/openDIS/DIS/AngularVelocityVector.h
	src/openDIS/DIS/AntennaLocation.h
	src/openDIS/DIS/ApaData.h
	src/openDIS/DIS/ArealObjectStatePdu.h
	src/openDIS/DIS/ArticulationParameter.h
	src/openDIS/DIS/BeamAntennaPattern.h
	src/openDIS/DIS/BeamData.h
	src/openDIS/DIS/BurstDescriptor.h
	src/openDIS/DIS/ClockTime.h
	src/openDIS/DIS/CollisionElasticPdu.h
	src/openDIS/DIS/CollisionPdu.h
	src/openDIS/DIS/CommentPdu.h
	src/openDIS/DIS/CommentReliablePdu.h
	src/openDIS/DIS/Conversion.h
	src/openDIS/DIS/CreateEntityPdu.h
	src/openDIS/DIS/CreateEntityReliablePdu.h
	src/openDIS/DIS/DataPdu.h
	src/openDIS/DIS/DataQueryPdu.h
	src/openDIS/DIS/DataQueryReliablePdu.h
	src/openDIS/DIS/DataReliablePdu.h	
	src/openDIS/DIS/DataStream.h
	src/openDIS/DIS/DeadReckoningParameter.h
	src/openDIS/DIS/DesignatorPdu.h
	src/openDIS/DIS/DetonationPdu.h
	src/openDIS/DIS/DistributedEmissionsFamilyPdu.h
	src/openDIS/DIS/EightByteChunk.h
	src/openDIS/DIS/ElectronicEmissionBeamData.h
	src/openDIS/DIS/ElectronicEmissionsPdu.h
	src/openDIS/DIS/ElectronicEmissionSystemData.h
	src/openDIS/DIS/EmitterSystem.h
	src/openDIS/DIS/EntityID.h
	src/openDIS/DIS/EntityInformationFamilyPdu.h
	src/openDIS/DIS/EntityManagementFamilyPdu.h
	src/openDIS/DIS/EntityStatePdu.h
	src/openDIS/DIS/EntityStateUpdatePdu.h
	src/openDIS/DIS/EntityType.h
	src/openDIS/DIS/Environment.h
	src/openDIS/DIS/EnvironmentalProcessPdu.h
	src/openDIS/DIS/EventID.h
	src/openDIS/DIS/EventReportPdu.h
	src/openDIS/DIS/EventReportReliablePdu.h
	src/openDIS/DIS/FastEntityStatePdu.h
	src/openDIS/DIS/FirePdu.h
	src/openDIS/DIS/FixedDatum.h
	src/openDIS/DIS/FourByteChunk.h
	src/openDIS/DIS/FundamentalParameterData.h
	src/openDIS/DIS/FundamentalParameterDataIff.h
	src/openDIS/DIS/GridAxisRecord.h
	src/openDIS/DIS/GridAxisRecordRepresentation0.h
	src/openDIS/DIS/GridAxisRecordRepresentation1.h
	src/openDIS/DIS/GridAxisRecordRepresentation2.h
	src/openDIS/DIS/GriddedDataPdu.h
	src/openDIS/DIS/IffAtcNavAidsLayer1Pdu.h
	src/openDIS/DIS/IffAtcNavAidsLayer2Pdu.h
	src/openDIS/DIS/IffFundamentalData.h
	src/openDIS/DIS/IncomingMessage.h
	src/openDIS/DIS/IntercomCommunicationsParameters.h
	src/openDIS/DIS/IntercomControlPdu.h
	src/openDIS/DIS/IntercomSignalPdu.h
	src/openDIS/DIS/IsGroupOfPdu.h
	src/openDIS/DIS/IsPartOfPdu.h
	src/openDIS/DIS/LayerHeader.h
	src/openDIS/DIS/LinearObjectStatePdu.h
	src/openDIS/DIS/LinearSegmentParameter.h
	src/openDIS/DIS/LogisticsFamilyPdu.h
	src/openDIS/DIS/LogisticsPdu.h
	src/openDIS/DIS/Marking.h
	src/openDIS/DIS/MinefieldDataPdu.h
	src/openDIS/DIS/MinefieldFamilyPdu.h
	src/openDIS/DIS/MinefieldPduFamily.h
	src/openDIS/DIS/MinefieldQueryPdu.h
	src/openDIS/DIS/MinefieldResponseNackPdu.h
	src/openDIS/DIS/MinefieldStatePdu.h
	src/openDIS/DIS/ModulationType.h
	src/openDIS/DIS/NamedLocation.h
	src/openDIS/DIS/ObjectType.h
	src/openDIS/DIS/OneByteChunk.h
	src/openDIS/DIS/Orientation.h
	src/openDIS/DIS/PacketFactory.h
	src/openDIS/DIS/Pdu.h
	src/openDIS/DIS/PDUBank.h
	src/openDIS/DIS/PduContainer.h
	src/openDIS/DIS/PduFactory.h
	src/openDIS/DIS/Point.h
	src/openDIS/DIS/PointObjectStatePdu.h
	src/openDIS/DIS/PropulsionSystemData.h
	src/openDIS/DIS/RadioCommunicationsFamilyPdu.h
	src/openDIS/DIS/RadioEntityType.h
	src/openDIS/DIS/ReceiverPdu.h
	src/openDIS/DIS/RecordQueryReliablePdu.h
	src/openDIS/DIS/RecordSet.h
	src/openDIS/DIS/Relationship.h
	src/openDIS/DIS/RemoveEntityPdu.h
	src/openDIS/DIS/RemoveEntityReliablePdu.h
	src/openDIS/DIS/RepairCompletePdu.h
	src/openDIS/DIS/RepairResponsePdu.h
	src/openDIS/DIS/ResupplyCancelPdu.h
	src/openDIS/DIS/ResupplyOfferPdu.h
	src/openDIS/DIS/ResupplyReceivedPdu.h
	src/openDIS/DIS/SeesPdu.h
	src/openDIS/DIS/ServiceRequestPdu.h
	src/openDIS/DIS/SetDataPdu.h
	src/openDIS/DIS/SetDataReliablePdu.h
	src/openDIS/DIS/SetRecordReliablePdu.h
	src/openDIS/DIS/ShaftRPMs.h
	src/openDIS/DIS/SignalPdu.h
	src/openDIS/DIS/SimulationAddress.h
	src/openDIS/DIS/SimulationManagementFamilyPdu.h
	src/openDIS/DIS/SimulationManagementWithReliabilityFamilyPdu.h
	src/openDIS/DIS/SixByteChunk.h
	src/openDIS/DIS/SphericalHarmonicAntennaPattern.h
	src/openDIS/DIS/StartResumePdu.h
	src/openDIS/DIS/StartResumeReliablePdu.h
	src/openDIS/DIS/StopFreezePdu.h
	src/openDIS/DIS/StopFreezeReliablePdu.h
	src/openDIS/DIS/StreamUtils.h
	src/openDIS/DIS/SupplyQuantity.h
	src/openDIS/DIS/SyntheticEnvironmentFamilyPdu.h
	src/openDIS/DIS/SystemID.h
	src/openDIS/DIS/TrackJamTarget.h
	src/openDIS/DIS/TransferControlRequestPdu.h
	src/openDIS/DIS/TransmitterPdu.h
	src/openDIS/DIS/TwoByteChunk.h 
	src/openDIS/DIS/UaPdu.h 
	src/openDIS/DIS/VariableDatum.h 
	src/openDIS/DIS/Vector3Double.h
	src/openDIS/DIS/Vector3Float.h 
	src/openDIS/DIS/VectoringNozzleSystemData.h 
	src/openDIS/DIS/WarfareFamilyPdu.h
	src/openDIS/DIS/msLibMacro.h)
add_library( openDIS ${LIB_TYPE} ${openDIS_SRCS} ${openDIS_HDRS} )
# NO INSTALL [noinst_LIBRARIES]
if(WIN32)
    list(APPEND add_LIBS openDIS)
else(WIN32)
    list(APPEND add_LIBS -lopenDIS)
endif(WIN32)

### add_subdirectory( src/dis_gateway )
# Project [dis_gateway] [Static Library] [noinst_LIBRARIES], with 6 sources. 12 hdrs.
set( dis_gateway_SRCS 
	src/dis_gateway/CallSignManager.cpp
	src/dis_gateway/DISBroker.cpp
	src/dis_gateway/dr.cpp
	src/dis_gateway/EntityTable.cpp
	src/dis_gateway/Quat.cpp )
set( dis_gateway_HDRS
	src/dis_gateway/CallSignManager.h
	src/dis_gateway/DISBroker.h
	src/dis_gateway/dr.h
	src/dis_gateway/EntityTable.h
	src/dis_gateway/Quat.h)
add_library( dis_gateway ${LIB_TYPE} ${dis_gateway_SRCS} ${dis_gateway_HDRS} )
# NO INSTALL [noinst_LIBRARIES]
if(WIN32)
    list( APPEND add_LIBS dis_gateway )
else(WIN32)
    list(APPEND add_LIBS -ldis_gateway)
endif(WIN32)

# Project [fgms] [Console Application] [sbin_PROGRAMS], with 1 sources. deps [sgdebug MultiPlayer plib fg_server]4
set( fgms_SRCS src/server/main.cxx )
add_executable( ${EXE_NAME} ${fgms_SRCS} )

# find the threads library
find_package(Threads REQUIRED)
if(Threads_FOUND)
  if(WIN32)
    list(APPEND add_LIBS winmm.lib ws2_32.lib)
	###message( STATUS "*** ENV INCLUDE $ENV{INCLUDE}")
	message( STATUS "*** Finding pthread.h HINTS [${CMAKE_PREFIX_PATH}] PATHS [${CMAKE_INCLUDE_PATH}] PATH_SUFFIXES include" )
	###find_file( thread_INC pthread.h
	find_path( thread_INC pthread.h
		HINTS ${CMAKE_PREFIX_PATH} $ENV{INCLUDE}
		PATHS ${CMAKE_INCLUDE_PATH} $ENV{INCLUDE}
		PATH_SUFFIXES include )
	if(thread_INC)
		include_directories( SYSTEM ${thread_INC} )
		message(STATUS "*** thread_INC: ${thread_INC}")
	else(thread_INC)
		message(FATAL_ERROR "*** thread_INC: ${thread_INC} pthread.h NOT FOUND!")
	endif(thread_INC)
	find_library( thread_LIB pthreadVC2.lib
		HINTS ${CMAKE_PREFIX_PATH} $ENV{LIB}
		PATHS ${CMAKE_INCLUDE_PATH} $ENV{LIB}
		PATH_SUFFIXES lib )
	if(thread_LIB)
		list(APPEND add_LIBS ${thread_LIB})
		message(STATUS "*** Found ${thread_LIB})" )
	else(thread_LIB)
		message( FATAL_ERROR "*** NOT FOUND target_link_libraries(pthread1 ${thread_LIB})" )
	endif(thread_LIB)
  else(WIN32)
     list(APPEND add_LIBS ${CMAKE_THREAD_LIBS_INIT})
  endif(WIN32)
else(Threads_FOUND)
  message( FATAL_ERROR "*** THREADS NOT FOUND!")
endif(Threads_FOUND)

target_link_libraries( ${EXE_NAME} ${add_LIBS} )
message(STATUS "*** target_link_libraries( ${EXE_NAME} ${add_LIBS} )" )
if(WIN32)
    set_target_properties( ${EXE_NAME} PROPERTIES DEBUG_POSTFIX "d" )
    install(TARGETS ${EXE_NAME} DESTINATION bin)
else(WIN32)
    message(STATUS "*** Will install binary to ${SBINDIR}")
    message(STATUS "*** Will read config from ${SYSCONFDIR}")
    install(TARGETS ${EXE_NAME} DESTINATION ${SBINDIR})
endif(WIN32)

if(BUILD_TRACKER)
    if(USE_POSTGRESQL)
        # find postgresql include and libraries
        # =====================================
        find_package(PostgreSQL REQUIRED)
        if(PostgreSQL_FOUND)
            list( APPEND add_LIBS ${PostgreSQL_LIBRARIES} )
            include_directories( "${PostgreSQL_INCLUDE_DIR}" )
            message(STATUS "*** Found PosgreSQL_INCLUDE_DIR=${PostgreSQL_INCLUDE_DIR}")
            message(STATUS "*** Found PostgreSQL_LIBRARY_DIR=${PostgreSQL_LIBRARY_DIR} LIBS ${PostgreSQL_LIBRARIES}")
            if (WIN32)
                link_directories( ${PostgreSQL_LIBRARY_DIR} )
            endif (WIN32)
        else(PostgreSQL_FOUND)
            message(FATAL_ERROR "*** PosgreSQL NOT FOUND! Run cmake with -DBUILD_TRACKER:BOOL=FALSE")
        endif(PostgreSQL_FOUND)
    else(USE_POSTGRESQL)
        add_definitions( -DNO_POSTGRESQL )
    endif(USE_POSTGRESQL)
    if(USE_PTHREAD_IN_TRACKER)
        add_definitions( -DUSE_PTHREAD )
    endif(USE_PTHREAD_IN_TRACKER)

    set( tracker_SRCS contrib/fgtracker/fgt_error.c contrib/fgtracker/wrappers.c )
    set( tracker_HDRS contrib/fgtracker/fgt_error.h contrib/fgtracker/wrappers.h contrib/fgtracker/fgt_config.h contrib/fgtracker/fgt_common.h )
    add_library( tracker ${LIB_TYPE} ${tracker_SRCS} ${tracker_HDRS} )
    list(APPEND add_LIBS tracker)

    set( server_SRCS contrib/fgtracker/server.c )
    add_executable( ${TRK_NAME} ${server_SRCS} )
    target_link_libraries( ${TRK_NAME} ${add_LIBS} )
    if (WIN32)
        set_target_properties( ${TRK_NAME} PROPERTIES DEBUG_POSTFIX "d" )
    endif (WIN32)

    set( client_SRCS contrib/fgtracker/client.c )
    add_executable( fgt_client ${client_SRCS} )
    target_link_libraries( fgt_client ${add_LIBS} )
    if (WIN32)
        set_target_properties( fgt_client PROPERTIES DEBUG_POSTFIX "d" )
    endif (WIN32)
    # deal with INSTALL
    install(TARGETS ${TRK_NAME} fgt_client DESTINATION bin)
else(BUILD_TRACKER)
    message( STATUS "*** Tracker NOT being built. Use -DBUILD_TRACKER:BOOL=TRUE to enable it." )
endif(BUILD_TRACKER)

# eof - CMakeLists.txt
