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

DIS::EntityStatePdu DISBroker::createESPDU(T_MsgHdr* MsgHdr, T_PositionMsg* PosMsg, int forceID )
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
	esPDU.setForceId(forceID);

	//set Marking (==name)
	char name[11] = {"          "};
	string fgCallsign = MsgHdr->Name;
	for ( unsigned int i = 0; i<fgCallsign.size(); i++)
		{
			name[i] = fgCallsign[i];
		}
	esPDU.getMarking().setCharacters( name );
	//set CharacterSet to ASCI (1)
	esPDU.getMarking().setCharacterSet( unsigned char(1) );

	//set DeadReckoning
	esPDU.getDeadReckoningParameters().setDeadReckoningAlgorithm( 4 );

	//set Entity Position
	esPDU.getEntityLocation().setX( XDR_decode64<double> ( PosMsg->position[X] ) );
	esPDU.getEntityLocation().setY( XDR_decode64<double> ( PosMsg->position[Y] ) );
	esPDU.getEntityLocation().setZ( XDR_decode64<double> ( PosMsg->position[Z] ) );

	//extract orientation in angle-axis representation
	Point3D angleaxis ( XDR_decode<float> ( PosMsg->orientation[X] ), XDR_decode<float> ( PosMsg->orientation[Y] ), XDR_decode<float> ( PosMsg->orientation[Z] ) );
	//std::cout << "FG X: " << XDR_decode<float> ( PosMsg->orientation[X] ) << " Y: " << XDR_decode<float> ( PosMsg->orientation[Y] ) << " Z: " << XDR_decode<float> ( PosMsg->orientation[Z] ) << "\n";

	//generate Quaternion from angleaxis
	Quat q = Quat::fromAngleAxis ( angleaxis );

	//compute euler angles
	double psi, theta, phi;
	q.getEulerRad( psi, theta, phi );
	//std::cout << "DIS phi: " << phi << " theta: " << theta << " psi: " << psi << "\n";

	//set Entity Orientation
	esPDU.getEntityOrientation().setPsi( psi );
	esPDU.getEntityOrientation().setTheta( theta );
	esPDU.getEntityOrientation().setPhi( phi );

	/*	linear Velocity is reported by FG in body-frame
		has to be rotated in world frame for DIS!		*/

	//4-dimensional velocity vector for rotation
	Quat linVel( XDR_decode<float> (PosMsg->linearVel[0]), XDR_decode<float> (PosMsg->linearVel[1]), XDR_decode<float> (PosMsg->linearVel[2]), 0 );
	//conjugate quaternion for rotation
	Quat qConj = Quat::conjugate( q );
	//multiply first with conjugate Quat for reverse rotation
	Quat tmpQuat = Quat::hamiltonProd(q, linVel);
	//2nd multiplication
	tmpQuat = Quat::hamiltonProd(tmpQuat, qConj);

	//set Linear Velocity
	esPDU.getEntityLinearVelocity().setX( tmpQuat.getX() );
	esPDU.getEntityLinearVelocity().setY( tmpQuat.getY() );
	esPDU.getEntityLinearVelocity().setZ( tmpQuat.getZ() );

	//set linear acceleration
	esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().setX ( XDR_decode<float> ( PosMsg->linearAccel[X] ) );
	esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().setY ( XDR_decode<float> ( PosMsg->linearAccel[Y] ) );
	esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().setZ ( XDR_decode<float> ( PosMsg->linearAccel[Z] ) );
	//set angualar velocity to zero 
	//because most FG-Aircrafts report garbish as angular velocity
	esPDU.getDeadReckoningParameters().getEntityAngularVelocity().setX ( XDR_decode<float> ( PosMsg->angularVel[X] ) );
	esPDU.getDeadReckoningParameters().getEntityAngularVelocity().setY ( XDR_decode<float> ( PosMsg->angularVel[Y] ) ); 
	esPDU.getDeadReckoningParameters().getEntityAngularVelocity().setZ ( XDR_decode<float> ( PosMsg->angularVel[Z] ) );

	//set Time Stamp
	esPDU.setTimestamp( now );

	//set Length of PDU
	esPDU.setLength( esPDU.getMarshalledSize() );
	//return ESPDU
	return esPDU;
	}

DIS::FirePdu DISBroker::createFPDU(DIS::EntityStatePdu MyEntity, DIS::EntityStatePdu Target, DIS::EntityType& type, int shoot_counter, unsigned int currentTime)
{
	unsigned int oldTimeStamp = Target.getTimestamp()/2/pow(2.0, 31)*3600000;
	unsigned int elapsedTime = currentTime - oldTimeStamp;
	//std::cout << "Delta T: " << elapsedTime << " ms\n";
	double elapsedTimeDBL =  (double)(elapsedTime)/1000;
	dr::calcDR( &Target, elapsedTimeDBL );

	DIS::FirePdu fPDU;
	// a) FirePDU Header - Represented by the PDU Header record
	//		a.a) Protocol Version -> automatically initialized
	//		a.b) Exercise Identifier
	fPDU.setExerciseID(1);
	//		a.c) PDU Type -> automatically initialized
	//		a.d) Protocol Family -> automatically initialized
	//		a.e) Timestamp
	fPDU.setTimestamp(MyEntity.getTimestamp());
	//		a.f) Length -> automatically initialized
	//		a.g) PDU Status -> field not provided by OPEN DIS
	//		a.h) Padding -> field not provided by OPEN DIS
	// b) Firing Entity ID - Represented by an Entity Identifier record
	fPDU.setFiringEntityID(MyEntity.getEntityID());
	// c) Target Entity ID - Represented by an Entity Identifier record
	fPDU.setTargetEntityID(Target.getEntityID());
	// d) Munition/Expendable Entity ID - Represented by an Entity Identifier record
	fPDU.getMunitionID().setSite(MyEntity.getEntityID().getSite());
	fPDU.getMunitionID().setApplication(MyEntity.getEntityID().getApplication());
	fPDU.getMunitionID().setEntity(shoot_counter+1);
	// e) Event ID - Represented by an Event Identifier record
	fPDU.getEventID().setSite(MyEntity.getEntityID().getSite());
	fPDU.getEventID().setApplication(MyEntity.getEntityID().getApplication());
	fPDU.getEventID().setEventNumber(shoot_counter+3);
	// f) Fire Mission Index - 0 by default
	// g) Location in World Coordinates - Represented by a World Coordinates record
	fPDU.setLocationInWorldCoordinates(MyEntity.getEntityLocation());
	// h) Descriptor - Represented by an Munition or Expendable Descriptor record
	fPDU.getBurstDescriptor().setMunition(type);
	// i) Linear Velocity
	fPDU.setVelocity(MyEntity.getEntityLinearVelocity());	
	// j) Range					
	double devX = (MyEntity.getEntityLocation().getX() - Target.getEntityLocation().getX());
	double devY = (MyEntity.getEntityLocation().getY() - Target.getEntityLocation().getY());
	double devZ = (MyEntity.getEntityLocation().getZ() - Target.getEntityLocation().getZ());
	fPDU.setRange(pow(devX*devX + devY*devY + devZ*devZ, 0.5));
	return fPDU;
}

DIS::ElectronicEmissionsPdu DISBroker::createEEPDU(DIS::EntityStatePdu MyEntity, int emittingEventID, unsigned int currentTime)
{
	unsigned int oldTimeStamp = MyEntity.getTimestamp()/2/pow(2.0, 31)*3600000;
	unsigned int elapsedTime = currentTime - oldTimeStamp;
	//std::cout << "Delta T: " << elapsedTime << " ms\n";
	double elapsedTimeDBL =  (double)(elapsedTime)/1000;
	dr::calcDR( &MyEntity, elapsedTimeDBL );

	DIS::ElectronicEmissionsPdu eePDU;

	// Initalize EEPDU
	// a.) Electronic Emissions PDU Header - Represented by a PDU Header record
	//		a.a.) Protocol Version -> automatically initialized
	//		a.b.) Exercise Identifier
	eePDU.setExerciseID(1);
	//		a.c.) PDU Type -> automatically initialized
	//		a.d.) Protocol Family -> automatically initialized
	//		a.e.) Timestamp
	eePDU.setTimestamp(MyEntity.getTimestamp());
	//		a.f.) Length
	//		a.g.) PDU Status -> field not provided by OPEN DIS
	//		a.h.) Padding -> field not provided by OPEN DIS
	// b.) Emitting Entity ID - Represented by a Entity identifier record
	eePDU.setEmittingEntityID(MyEntity.getEntityID());
	// c.) Event ID - Represented by a Event Identifier record
	eePDU.getEventID().setSite(MyEntity.getEntityID().getSite());
	eePDU.getEventID().setApplication(MyEntity.getEntityID().getApplication());
	eePDU.getEventID().setEventNumber(emittingEventID);
	// d.) State Update Indicator - Represented by an 8 Bit Enumeration (Value = 0 || 1)
	eePDU.setStateUpdateIndicator(0);
	// e.) Number of Systems
	// f.) "Information provided for each Emitter System"
	std::vector<DIS::ElectronicEmissionSystemData> eeSystems;
	DIS::ElectronicEmissionSystemData system;
	//		f.1.) System Data Length
	//		f.2.) Number of Beams 1
	//		f.3.) Emitter Systems - Represented by an emitter System record -> EmitterSystemsTable would be most dynamic solution 
	//				f.3.i.) Emitter Name 45300 Schuk-M
	system.getEmitterSystem().setEmitterName(45300);
	//				f.3.ii.) Function 6 Tracker
	system.getEmitterSystem().setFunction(6);
	//				f.3.ii.) Emitter Id Number 1
	system.getEmitterSystem().setEmitterIdNumber(1);
	//		f.4.) Location - Represented by an Entity Coordinate Vector record
	//				f.4.i.) Entity Coordinate Vector
	system.getLocation().setX(MyEntity.getEntityLocation().getX());
	system.getLocation().setY(MyEntity.getEntityLocation().getY());
	system.getLocation().setZ(MyEntity.getEntityLocation().getZ());
	//				f.4.ii.) Linear Acceleration Vector -> field not contained in Object Library
	//				f.4.iii.) Linear Velocity Vector -> field not contained in Object Library
	//		f.5.) "Information provided for each active beam"
	std::vector<DIS::ElectronicEmissionBeamData> eeBeams;
	DIS::ElectronicEmissionBeamData beam;
	//				f.5.i) Beam Data Length
	//				f.5.ii.) Beam number
	beam.setBeamIDNumber(0);
	//				f.5.iii.) Beam Parameter Index
	beam.setBeamParameterIndex(0);
	//				f.5.iv.) Fundamental Parameter Data - Represented by an EE Fundamental Parameter Data record
	DIS::FundamentalParameterData eeBeamfundamental;
	//						f.5.iv.1.) Frequency 10 GHz
	eeBeamfundamental.setFrequency(1000000000.0);
	//						f.5.iv.2.) Frequency Range 10 MHz
	eeBeamfundamental.setFrequencyRange(1000000);
	//						f.5.iv.3.) Effective Radiated Power 10*log10(5kW/1mW)
	eeBeamfundamental.setEffectiveRadiatedPower(70);
	//						f.5.iv.4.) Pulse Repetition Frequency 15 kHz
	eeBeamfundamental.setPulseRepetitionFrequency(15000);
	//						f.5.iv.5.) Pulse Width 7 µs
	eeBeamfundamental.setPulseWidth(7);
	//				f.5.v.) Beam Data - Represented by a Beam Data record
	//						f.5.v.1.) Beam Azimuth Center 0
	eeBeamfundamental.setBeamAzimuthCenter(0);
	//						f.5.v.2.) Beam Azimuth Sweep pi/6
	eeBeamfundamental.setBeamAzimuthSweep(3.141/6);
	//						f.5.v.3.) Beam Elevation Center 0
	eeBeamfundamental.setBeamElevationCenter(0);
	//						f.5.v.4.) Beam Elevation Sweep pi/6
	eeBeamfundamental.setBeamElevationSweep(3.141/6);
	//						f.5.v.5.) Beam Sweep Sync 0
	eeBeamfundamental.setBeamSweepSync(0);
	//				f.5.vi.) Beam Function 4 (Tracker)
	beam.setBeamFunction(4);
	//				f.5.vii.) Number of Targets 0
	/*beam.setTrackJamTargets(0);*/
	//				f.5.viii.) High Density Track/Jam 0
	beam.setHighDensityTrackJam(0);
	//				f.5.ix.) Beam Status - Represented by a Beam Status record
	//						f.5.ix.1) Beam State 0
	//						f.5.ix.1) Padding
	//				f.5.x.) Jamming Technique - Represented by a Jamming Technique record -> kein Jamming
	//						f.5.x.1.) Kind 
	//						f.5.x.2.) Category
	//						f.5.x.3.) Subcategory
	//						f.5.x.4.) Specific
	//				f.5.xi.) Track/Jam Data - Represented by a series of Track/Jam Data records -> kein Jamming
	//						f.5.xi.1.) Entity ID
	//						f.5.xi.2.) Emitter Number
	//						f.5.xi.3.) Beam Number
											

	// Complete Electronic Emitter PDU Data					
	beam.setFundamentalParameterData(eeBeamfundamental);
	eeBeams.push_back(beam);
	system.setBeamDataRecords(eeBeams);
	eeSystems.push_back(system);
	eePDU.setSystems(eeSystems);	
	eePDU.setLength(eePDU.getMarshalledSize());
	return eePDU;
}

			
		

void DISBroker::createMPmessage(char* msg, DIS::EntityStatePdu &esPDU, string model, string CallSign, int Bytes, double* updateRate, EntityTable et, int forceID)
{
	//variables
	T_MsgHdr* MsgHdr = (T_MsgHdr*)msg;
	T_PositionMsg* PosMsg = (T_PositionMsg*)(msg+sizeof(T_MsgHdr));
	double now;
	const char* c_model = model.c_str();

	//set Callsign
	strncpy( MsgHdr->Name, CallSign.c_str(), 8 );
	//set zero termination for Callsign
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
	//time = time in seconds
	PosMsg->time = XDR_encode64<double>( now/1000 );
	//lag = time since last packet in seconds
	PosMsg->lag = XDR_encode64<double>( *updateRate / 1000 );
	//cout << "lagDIS: " <<  *updateRate / 1000 << endl;
	//set the model
	strncpy( PosMsg->Model, c_model, MAX_MODEL_NAME_LEN );
	//zero termination for model
	PosMsg->Model[MAX_MODEL_NAME_LEN - 1] = '\0';


	//set Entity Position
	PosMsg->position[X] = XDR_encode64<double>( esPDU.getEntityLocation().getX());
	PosMsg->position[Y] = XDR_encode64<double>( esPDU.getEntityLocation().getY());
	PosMsg->position[Z] = XDR_encode64<double>( esPDU.getEntityLocation().getZ());

	//get Entity Orientation
	double phi, theta, psi;
	phi = esPDU.getEntityOrientation().getPhi();
	theta = esPDU.getEntityOrientation().getTheta();
	psi = (esPDU.getEntityOrientation().getPsi());
	//rotate orientation in FG-cordinate system with quaternion
	Quat q = q.fromEulerRad(psi, theta, phi);
	//set orientaion as angel-axis representation (required by FG)
	Point3D point = Quat::getAngleAxis(q); 
	PosMsg->orientation[X] = XDR_encode<float> ( point.GetX() );
	PosMsg->orientation[Y] = XDR_encode<float> ( point.GetY() );
	PosMsg->orientation[Z] = XDR_encode<float> ( point.GetZ() );

	//extract linVelocity from ES-PDU
	//4-dimensional velocity vector for rotation
	Quat disLinVel(esPDU.getEntityLinearVelocity().getX(), esPDU.getEntityLinearVelocity().getY(), esPDU.getEntityLinearVelocity().getZ(), 0);
	//conjugate quaternion for rotation
	Quat conjq = Quat::conjugate( q );
	//transform linear velocity from world frame to body frame
	Quat tmpQuat = Quat::hamiltonProd( conjq, disLinVel);
	tmpQuat = Quat::hamiltonProd( tmpQuat, q);

	//set Linear Velocity
	PosMsg->linearVel[X] = XDR_encode<float> ( tmpQuat.getX() ) ;
	PosMsg->linearVel[Y] = XDR_encode<float> ( tmpQuat.getY() ) ;
	PosMsg->linearVel[Z] = XDR_encode<float> ( tmpQuat.getZ() ) ;

	//set angular acceleration to zero
	PosMsg->angularAccel[X] = XDR_encode<float> (0);
	PosMsg->angularAccel[Y] = XDR_encode<float> (0);
	PosMsg->angularAccel[Z] = XDR_encode<float> (0);
	//set angular velocity to zero
	PosMsg->angularVel[X] = XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityAngularVelocity().getX());
	PosMsg->angularVel[Y] = XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityAngularVelocity().getY());
	PosMsg->angularVel[Z] = XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityAngularVelocity().getZ());
	//set linear acceleration to zero
	PosMsg->linearAccel[X] = XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().getX());
	PosMsg->linearAccel[Y] = XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().getY());
	PosMsg->linearAccel[Z] = XDR_encode<float> (esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().getZ());
	
	// Prepare Array to write ForceID, Type and Name into FGMP-Message fields 
	// field 10100 generic string[0] -> "friendly", "opposing", "neutral"
	// field 10101 generic string[1] -> "surface", "air"
	// field 10102 generic string[2] -> <name> from entitytable.xml
	int id [3] = {10100,10101,10102};
	string* value[3]; 
	for(int s=0; s<3; s++) { value[s] = new string(""); }
	char* cp = (msg+sizeof(T_MsgHdr)+sizeof(T_PositionMsg));

	// get force id
	if(esPDU.getForceId() >= 0 && esPDU.getForceId() <= 30)
	{
		// in IEEE1278.1 30 force IDs possible
		// 3*x -> neutral or other
		// 3*x+1 -> side A (good guys)
		// 3*x+2 -> side B (bad guys)
		int modFID = esPDU.getForceId()%3;
		if(forceID%3 == modFID) //same side
		{
			value[0] = new string("friendly");
		}
		else
		{
			if(modFID == 0)
			{
				value[0] =  new string("neutral");
			}
			else
			{
				value[0] =  new string("opposing");
			}
		}
	}
	//else
	//{
	//	cout << esPDU.getEntityID().getSite() << ":" << esPDU.getEntityID().getApplication() << ":" << esPDU.getEntityID().getEntity() << " contains invalid Force ID." << endl;
	//}

	//get Type
	// KindDomain represents Entity Kind and Domain in a single Variable
	// with last 2 digits being the Kind specific Domain according to IEEE 1278.1
	// and all leading digits being the Kind according to IEEE 1278.1
	int KindDomain = esPDU.getEntityType().getEntityKind()*100 + esPDU.getEntityType().getDomain();
	// 102=Platform Air, 103=Platform Surface, 201..206=Missiles
	if(KindDomain == 102 || KindDomain == 103 || (KindDomain > 200 && KindDomain < 207))
	{
		if(KindDomain == 103)// ships
		{
			value[1] =  new string("surface");
		}
		else// Airplatforms and Missiles
		{
			value[1] =  new string("air");
		}
	}
	//else
	//{
	//	cout << esPDU.getEntityID().getSite() << ":" << esPDU.getEntityID().getApplication() << ":" << esPDU.getEntityID().getEntity() << " is not translated to FlightGear."<< endl;
	//}
	
	// get platform name
	if(et.getName(esPDU.getEntityType()) != "")
	{
		value[2] =  new string(et.getName(esPDU.getEntityType()));
	}
	//else
	//{
	//	cout << (int)(esPDU.getEntityType().getEntityKind()) << ":" 
	//		<< (int)(esPDU.getEntityType().getDomain()) <<":" 
	//		<< esPDU.getEntityType().getCountry() <<":" 
	//		<< (int)(esPDU.getEntityType().getCategory()) <<":" 
	//		<< (int)(esPDU.getEntityType().getSubcategory()) <<":" 
	//		<< (int)(esPDU.getEntityType().getSpecific()) <<":" 
	//		<< (int)(esPDU.getEntityType().getExtra()) <<":" 
	//		<< " is not defined in entitytable.xml."<< endl;
	//}

	// write Properties into Multiplayer Message
	for(int j=0 ; j<3 ; j++)
	{
		// set Property ID
		*(int*)cp = XDR_encode<int> (id[j]);
		cp += sizeof(int);
		// set Property Size
		int size = (*(value[j])).length();
		*(int*)cp = XDR_encode<int> (size);
		cp += sizeof(int);
		// set Property Value
		for(int i=0;i<size;i++)
		{
			*(int*)cp = XDR_encode<int>((int)((*(value[j]))[i]));
			cp += sizeof(int);
		}
		//		set Property Padding
		cp += (4-(size%4))*4;
	}
}


