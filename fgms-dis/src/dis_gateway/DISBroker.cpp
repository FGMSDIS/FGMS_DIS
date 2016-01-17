
#include "DISBroker.h"
#include <math.h>
#include <string.h>
#include "fg_server.hxx"

DISBroker::DISBroker(void)
	{
	}

DISBroker::~DISBroker(void)
	{
	}

DIS::EntityStatePdu DISBroker::createESPDU(T_MsgHdr* MsgHdr, T_PositionMsg* PosMsg )
	{
	//get time
	unsigned int now;
	computeMilliSecHour( &now );

	DIS::EntityStatePdu esPDU;
		//set ProtocolVersion
	esPDU.setProtocolVersion(6);

	//set Exercise ID ToDo value from config File
	esPDU.setExerciseID(1);

	//set Force ID
	esPDU.setForceId(1);

	//set Marking (==name)
	char name[11] = {"          "};
	string fgCallsign = MsgHdr->Name;
	for ( int i = 0; i<fgCallsign.size(); i++)
		{
			name[i] = fgCallsign[i];
		}
	esPDU.getMarking().setCharacters( name );
	//set CharacterSet to ASCI (1)
	esPDU.getMarking().setCharacterSet(1);

	//set DeadReckoning
	esPDU.getDeadReckoningParameters().setDeadReckoningAlgorithm( 5 );

	//set Entity Position
	esPDU.getEntityLocation().setX( XDR_decode64<double> ( PosMsg->position[X] ) );
	esPDU.getEntityLocation().setY( XDR_decode64<double> ( PosMsg->position[Y] ) );
	esPDU.getEntityLocation().setZ( XDR_decode64<double> ( PosMsg->position[Z] ) );

	//extract orientation in angle-axis representation
	Point3D angleaxis ( XDR_decode<float> ( PosMsg->orientation[X] ), XDR_decode<float> ( PosMsg->orientation[Y] ), XDR_decode<float> ( PosMsg->orientation[Z] ) );


	//generate Quaternion from angleaxis
	Quat q = Quat::fromAngleAxis ( angleaxis );
	//rotate quaternion from FG local to DIS local
	Quat hundreteighty(sin(M_PI_2), 0.0, 0.0, cos(M_PI_2) );
	//q = Quat::hamiltonProd( q, hundreteighty );

	//compute euler angles
	float phi,theta,psi;
	q.getEulerRad( psi, theta, phi );

	//set Entity Orientation
	esPDU.getEntityOrientation().setPhi( phi );
	esPDU.getEntityOrientation().setTheta( theta );
	esPDU.getEntityOrientation().setPsi( psi );
	 /*
	Quat test = Quat::fromEulerRad ( phi, theta, psi );
	printf ( "Q[X]: %E test[X] %E \n", q.getX(), test.getX() );
	printf ( "Q[Y]: %E test[Y] %E \n", q.getY(), test.getY() );
	printf ( "Q[Z]: %E test[Z] %E \n", q.getZ(), test.getZ() );
	printf ( "Q[W]: %E test[Z] %E \n \n", q.getW(), test.getW() );
	*/
	/*	linear Velocity is reported by FG in body-frame
		has to be rotated in world frame for DIS!		*/

	//4-dimensional velocity vector for rotation
	double fgLinVel [] = {0,0,0,0};//4-dimensional velocity vector for rotation
	//extract linVelocity from FG mpMessage
	for (int i=0; i<3; i++)
		{ fgLinVel[i] = XDR_decode<float> ( PosMsg->linearVel[i] ); }
	Quat linVel( fgLinVel[0], fgLinVel[1], fgLinVel[2], fgLinVel[3] );

	//conjugate quaternion for rotation
	Quat qConj = Quat::conjugate( q );
	//multiply conjugate Quat with LinVel
	Quat tmpQuat = Quat::hamiltonProd(q, linVel);
	//2nd multiplication
	tmpQuat = Quat::hamiltonProd(tmpQuat, qConj);

	//set Linear Velocity
	esPDU.getEntityLinearVelocity().setX( tmpQuat.getX() );
	esPDU.getEntityLinearVelocity().setY( tmpQuat.getY() );
	esPDU.getEntityLinearVelocity().setZ( tmpQuat.getZ() );
	/*
	printf ( "FG-V[X]: %E DIS-V[X] %E \n", fgLinVel[0], esPDU.getEntityLinearVelocity().getX() );
	printf ( "FG-V[Y]: %E DIS-V[Y] %E \n", fgLinVel[1], esPDU.getEntityLinearVelocity().getY() );
	printf ( "FG-V[Z]: %E DIS-V[Z] %E \n", fgLinVel[2], esPDU.getEntityLinearVelocity().getZ() );
	printf ( "DIS-V[W] %E \n \n", tmpQuat.getW() );
	*/

	//validate computation (just for testing)

	/*
	Quat tmpQuat2 = Quat::hamiltonProd(q, tmpQuat);
	//2nd multiplication
	tmpQuat2 = Quat::hamiltonProd(tmpQuat2, qConj);
	printf ( "DIS2-V[X]: %E FG-V[X] %E \n", -tmpQuat2.getX(), fgLinVel[0] );
	printf ( "DIS2-V[Y]: %E FG-V[Y] %E \n", -tmpQuat2.getY(), fgLinVel[1] );
	printf ( "DIS2-V[Z]: %E FG-V[Z] %E \n", tmpQuat2.getZ(), fgLinVel[2] );
	printf ( "DIS2-V[W] %E \n \n", tmpQuat2.getW() );
	  */


	//set linear accdeleration
	esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().setX ( XDR_decode<float> ( PosMsg->linearAccel[X] ) );
	esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().setY ( XDR_decode<float> ( PosMsg->linearAccel[Y] ) );
	esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().setZ ( XDR_decode<float> ( PosMsg->linearAccel[Z] ) );
	//set angualar velocity
	esPDU.getDeadReckoningParameters().getEntityAngularVelocity().setX ( XDR_decode<float> ( PosMsg->angularVel[X] ) );
	esPDU.getDeadReckoningParameters().getEntityAngularVelocity().setY ( XDR_decode<float> ( -PosMsg->angularVel[Y] ) );
	esPDU.getDeadReckoningParameters().getEntityAngularVelocity().setZ ( XDR_decode<float> ( -PosMsg->angularVel[Z] ) );
	//set Time Stamp

	esPDU.setTimestamp( now );

	//set Length of PDU
	esPDU.setLength( esPDU.getMarshalledSize() );
	//return ESPDU
	return esPDU;
	}

void DISBroker::createMPmessage(char* msg, DIS::EntityStatePdu &esPDU, string model, string CallSign, int Bytes, double *updateRate){


	//variables
	T_MsgHdr* MsgHdr = new T_MsgHdr;
	T_PositionMsg* PosMsg = new T_PositionMsg;
	double now;
	const char* c_model = model.c_str();

	//set Marking
	//char* Marking = esPDU.getMarking().getCharacters();
	//strncpy(MsgHdr->Name,Marking,8);
	strncpy( MsgHdr->Name, CallSign.c_str(), 8 );
	MsgHdr->Name[7] = '\0';

	//setting header
	MsgHdr->Magic = XDR_encode<uint32_t>(MSG_MAGIC);
	MsgHdr->Version  = XDR_encode<uint32_t>(PROTO_VER);
	MsgHdr->MsgId = XDR_encode<uint32_t>(POS_DATA_ID);
	MsgHdr->ReplyAddress = 9;
	MsgHdr->ReplyPort =0;
	MsgHdr->MsgLen = XDR_encode<uint32_t>(Bytes);

	//setting timestamp
	computeMilliSecDay( &now );
	PosMsg->time = XDR_encode64<double>(now);
	PosMsg->lag = XDR_encode64<double>( *updateRate / 1000);

	strncpy(PosMsg->Model,c_model,MAX_MODEL_NAME_LEN);
	PosMsg->Model[MAX_MODEL_NAME_LEN - 1] = '\0';


	//set Entity Position
	//PosMsg = ( T_PositionMsg* ) ( Msg + sizeof ( T_MsgHdr ) );
	PosMsg->position[X] = XDR_encode64<double>( esPDU.getEntityLocation().getX());
	PosMsg->position[Y] = XDR_encode64<double>( esPDU.getEntityLocation().getY());
	PosMsg->position[Z] = XDR_encode64<double>( esPDU.getEntityLocation().getZ());

	//set Entity Orientation
	float phi, theta, psi;
	phi = esPDU.getEntityOrientation().getPhi();
	theta = esPDU.getEntityOrientation().getTheta();
	psi = (esPDU.getEntityOrientation().getPsi());
	Quat q = q.fromDISglobToFGlocByEulerRad(phi, theta, psi);
	Point3D point = Quat::getAngleAxis(q);
	PosMsg->orientation[X] = XDR_encode<float>(point.GetX());
	PosMsg->orientation[Y] = XDR_encode<float>(point.GetY());
	PosMsg->orientation[Z] = XDR_encode<float>(point.GetZ());


	//extract linVelocity from ES-PDU
	Quat disLinVel(esPDU.getEntityLinearVelocity().getX(), esPDU.getEntityLinearVelocity().getY(), esPDU.getEntityLinearVelocity().getZ(), 0);//4-dimensional velocity vector for rotation

	//4-dimensional velocity vector for rotation
	Quat rotation = Quat::fromDISglobToDISlocByEulerRad(psi, theta, phi);
	Quat conjRotation = Quat::conjugate( rotation );

	//transform linear velocity from DIS global to Dis local
	disLinVel = Quat::hamiltonProd( conjRotation, disLinVel);
	disLinVel = Quat::hamiltonProd( disLinVel, rotation);

	//set Linear Velocity
	PosMsg->linearVel[X] = XDR_encode<float> ( disLinVel.getX() ) ;
	PosMsg->linearVel[Y] = XDR_encode<float> ( -disLinVel.getY() ) ;
	PosMsg->linearVel[Z] = XDR_encode<float> ( -disLinVel.getZ() ) ;
	/*
	printf ( "DIS-V[X]: %E \n", disLinVel.getX() );
	printf ( "DIS-V[Y]: %E \n", disLinVel.getY() );
	printf ( "DIS-V[Z]: %E \n \n", disLinVel.getZ() );
	*/

	PosMsg->angularAccel[X] = XDR_encode<float> (0);
	PosMsg->angularAccel[Y] = XDR_encode<float> (0);
	PosMsg->angularAccel[Z] = XDR_encode<float> (0);

	PosMsg->angularVel[X] = XDR_encode<float> (0);//XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityAngularVelocity().getX());
	PosMsg->angularVel[Y] = XDR_encode<float> (0);//XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityAngularVelocity().getY());
	PosMsg->angularVel[Z] = XDR_encode<float> (0);//XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityAngularVelocity().getZ());

	PosMsg->linearAccel[X] = XDR_encode<float> (0);//XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().getX());
	PosMsg->linearAccel[Y] = XDR_encode<float> (0);//XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().getY());
	PosMsg->linearAccel[Z] = XDR_encode<float> (0);//XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().getZ());

	//create Msg
	memcpy (msg, MsgHdr, sizeof(T_MsgHdr));
	memcpy (msg + sizeof(T_MsgHdr), PosMsg, sizeof(T_PositionMsg));
	}


