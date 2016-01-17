# C++ Console Executable Makefile autogenerated by premake
# Don't edit this file! Instead edit `premake.lua` then rerun `make`

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := ../../bin
  LIBDIR := ../../lib
  OBJDIR := obj_gnu_DIS_debug
  OUTDIR := ../../bin
  CPPFLAGS := -MMD -D "WIN32" -D "_DEBUG" -D "EXPORT_LIBRARY" -I "../../cpp" -I "../../CppUtils"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -shared -Wl,--out-implib="../../lib/libDIS_debug.a"
  LDDEPS :=
  RESFLAGS := -D "WIN32" -D "_DEBUG" -D "EXPORT_LIBRARY" -I "../../cpp" -I "../../CppUtils"
  TARGET := DIS_debug.dll
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := ../../bin
  LIBDIR := ../../lib
  OBJDIR := obj_gnu_DIS
  OUTDIR := ../../bin
  CPPFLAGS := -MMD -D "WIN32" -D "EXPORT_LIBRARY" -I "../../cpp" -I "../../CppUtils"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O2
  CXXFLAGS := $(CFLAGS)
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -shared -Wl,--out-implib="../../lib/libDIS.a" -s
  LDDEPS :=
  RESFLAGS := -D "WIN32" -D "EXPORT_LIBRARY" -I "../../cpp" -I "../../CppUtils"
  TARGET := DIS.dll
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
	$(OBJDIR)/AcknowledgePdu.o \
	$(OBJDIR)/AcknowledgeReliablePdu.o \
	$(OBJDIR)/AcousticBeamData.o \
	$(OBJDIR)/AcousticBeamFundamentalParameter.o \
	$(OBJDIR)/AcousticEmitter.o \
	$(OBJDIR)/AcousticEmitterSystem.o \
	$(OBJDIR)/AcousticEmitterSystemData.o \
	$(OBJDIR)/ActionRequestPdu.o \
	$(OBJDIR)/ActionRequestReliablePdu.o \
	$(OBJDIR)/ActionResponsePdu.o \
	$(OBJDIR)/ActionResponseReliablePdu.o \
	$(OBJDIR)/AggregateID.o \
	$(OBJDIR)/AggregateMarking.o \
	$(OBJDIR)/AggregateStatePdu.o \
	$(OBJDIR)/AggregateType.o \
	$(OBJDIR)/AngularVelocityVector.o \
	$(OBJDIR)/AntennaLocation.o \
	$(OBJDIR)/ApaData.o \
	$(OBJDIR)/ArealObjectStatePdu.o \
	$(OBJDIR)/ArticulationParameter.o \
	$(OBJDIR)/BeamAntennaPattern.o \
	$(OBJDIR)/BeamData.o \
	$(OBJDIR)/BurstDescriptor.o \
	$(OBJDIR)/ClockTime.o \
	$(OBJDIR)/CollisionElasticPdu.o \
	$(OBJDIR)/CollisionPdu.o \
	$(OBJDIR)/CommentPdu.o \
	$(OBJDIR)/CommentReliablePdu.o \
	$(OBJDIR)/CreateEntityPdu.o \
	$(OBJDIR)/CreateEntityReliablePdu.o \
	$(OBJDIR)/DataPdu.o \
	$(OBJDIR)/DataQueryPdu.o \
	$(OBJDIR)/DataQueryReliablePdu.o \
	$(OBJDIR)/DataReliablePdu.o \
	$(OBJDIR)/DeadReckoningParameter.o \
	$(OBJDIR)/DesignatorPdu.o \
	$(OBJDIR)/DetonationPdu.o \
	$(OBJDIR)/DistributedEmissionsFamilyPdu.o \
	$(OBJDIR)/EightByteChunk.o \
	$(OBJDIR)/ElectronicEmissionBeamData.o \
	$(OBJDIR)/ElectronicEmissionsPdu.o \
	$(OBJDIR)/ElectronicEmissionSystemData.o \
	$(OBJDIR)/EmitterSystem.o \
	$(OBJDIR)/EntityID.o \
	$(OBJDIR)/EntityInformationFamilyPdu.o \
	$(OBJDIR)/EntityManagementFamilyPdu.o \
	$(OBJDIR)/EntityStatePdu.o \
	$(OBJDIR)/EntityStateUpdatePdu.o \
	$(OBJDIR)/EntityType.o \
	$(OBJDIR)/Environment.o \
	$(OBJDIR)/EnvironmentalProcessPdu.o \
	$(OBJDIR)/EventID.o \
	$(OBJDIR)/EventReportPdu.o \
	$(OBJDIR)/EventReportReliablePdu.o \
	$(OBJDIR)/FastEntityStatePdu.o \
	$(OBJDIR)/FirePdu.o \
	$(OBJDIR)/FixedDatum.o \
	$(OBJDIR)/FourByteChunk.o \
	$(OBJDIR)/FundamentalParameterData.o \
	$(OBJDIR)/FundamentalParameterDataIff.o \
	$(OBJDIR)/GridAxisRecord.o \
	$(OBJDIR)/GridAxisRecordRepresentation0.o \
	$(OBJDIR)/GridAxisRecordRepresentation1.o \
	$(OBJDIR)/GridAxisRecordRepresentation2.o \
	$(OBJDIR)/GriddedDataPdu.o \
	$(OBJDIR)/IffAtcNavAidsLayer1Pdu.o \
	$(OBJDIR)/IffAtcNavAidsLayer2Pdu.o \
	$(OBJDIR)/IffFundamentalData.o \
	$(OBJDIR)/IntercomCommunicationsParameters.o \
	$(OBJDIR)/IntercomControlPdu.o \
	$(OBJDIR)/IntercomSignalPdu.o \
	$(OBJDIR)/IsGroupOfPdu.o \
	$(OBJDIR)/IsPartOfPdu.o \
	$(OBJDIR)/LayerHeader.o \
	$(OBJDIR)/LinearObjectStatePdu.o \
	$(OBJDIR)/LinearSegmentParameter.o \
	$(OBJDIR)/LogisticsFamilyPdu.o \
	$(OBJDIR)/LogisticsPdu.o \
	$(OBJDIR)/Marking.o \
	$(OBJDIR)/MinefieldDataPdu.o \
	$(OBJDIR)/MinefieldFamilyPdu.o \
	$(OBJDIR)/MinefieldPduFamily.o \
	$(OBJDIR)/MinefieldQueryPdu.o \
	$(OBJDIR)/MinefieldResponseNackPdu.o \
	$(OBJDIR)/MinefieldStatePdu.o \
	$(OBJDIR)/ModulationType.o \
	$(OBJDIR)/NamedLocation.o \
	$(OBJDIR)/ObjectType.o \
	$(OBJDIR)/OneByteChunk.o \
	$(OBJDIR)/Orientation.o \
	$(OBJDIR)/Pdu.o \
	$(OBJDIR)/Point.o \
	$(OBJDIR)/PointObjectStatePdu.o \
	$(OBJDIR)/PropulsionSystemData.o \
	$(OBJDIR)/RadioCommunicationsFamilyPdu.o \
	$(OBJDIR)/RadioEntityType.o \
	$(OBJDIR)/ReceiverPdu.o \
	$(OBJDIR)/RecordQueryReliablePdu.o \
	$(OBJDIR)/RecordSet.o \
	$(OBJDIR)/Relationship.o \
	$(OBJDIR)/RemoveEntityPdu.o \
	$(OBJDIR)/RemoveEntityReliablePdu.o \
	$(OBJDIR)/RepairCompletePdu.o \
	$(OBJDIR)/RepairResponsePdu.o \
	$(OBJDIR)/ResupplyCancelPdu.o \
	$(OBJDIR)/ResupplyOfferPdu.o \
	$(OBJDIR)/ResupplyReceivedPdu.o \
	$(OBJDIR)/SeesPdu.o \
	$(OBJDIR)/ServiceRequestPdu.o \
	$(OBJDIR)/SetDataPdu.o \
	$(OBJDIR)/SetDataReliablePdu.o \
	$(OBJDIR)/SetRecordReliablePdu.o \
	$(OBJDIR)/ShaftRPMs.o \
	$(OBJDIR)/SignalPdu.o \
	$(OBJDIR)/SimulationAddress.o \
	$(OBJDIR)/SimulationManagementFamilyPdu.o \
	$(OBJDIR)/SimulationManagementWithReliabilityFamilyPdu.o \
	$(OBJDIR)/SixByteChunk.o \
	$(OBJDIR)/SphericalHarmonicAntennaPattern.o \
	$(OBJDIR)/StartResumePdu.o \
	$(OBJDIR)/StartResumeReliablePdu.o \
	$(OBJDIR)/StopFreezePdu.o \
	$(OBJDIR)/StopFreezeReliablePdu.o \
	$(OBJDIR)/SupplyQuantity.o \
	$(OBJDIR)/SyntheticEnvironmentFamilyPdu.o \
	$(OBJDIR)/SystemID.o \
	$(OBJDIR)/TrackJamTarget.o \
	$(OBJDIR)/TransferControlRequestPdu.o \
	$(OBJDIR)/TransmitterPdu.o \
	$(OBJDIR)/TwoByteChunk.o \
	$(OBJDIR)/UaPdu.o \
	$(OBJDIR)/VariableDatum.o \
	$(OBJDIR)/Vector3Double.o \
	$(OBJDIR)/Vector3Float.o \
	$(OBJDIR)/VectoringNozzleSystemData.o \
	$(OBJDIR)/WarfareFamilyPdu.o \
	$(OBJDIR)/Conversion.o \
	$(OBJDIR)/DataStream.o \
	$(OBJDIR)/IncomingMessage.o \
	$(OBJDIR)/PacketFactory.o \
	$(OBJDIR)/PDUBank.o \
	$(OBJDIR)/StreamUtils.o \

RESOURCES := \

MKDIR_TYPE := msdos
CMD := $(subst \,\\,$(ComSpec)$(COMSPEC))
ifeq (,$(CMD))
  MKDIR_TYPE := posix
endif
ifeq (/bin/sh.exe,$(SHELL))
  MKDIR_TYPE := posix
endif
ifeq ($(MKDIR_TYPE),posix)
  CMD_MKBINDIR := mkdir -p $(BINDIR)
  CMD_MKLIBDIR := mkdir -p $(LIBDIR)
  CMD_MKOUTDIR := mkdir -p $(OUTDIR)
  CMD_MKOBJDIR := mkdir -p $(OBJDIR)
else
  CMD_MKBINDIR := $(CMD) /c if not exist $(subst /,\\,$(BINDIR)) mkdir $(subst /,\\,$(BINDIR))
  CMD_MKLIBDIR := $(CMD) /c if not exist $(subst /,\\,$(LIBDIR)) mkdir $(subst /,\\,$(LIBDIR))
  CMD_MKOUTDIR := $(CMD) /c if not exist $(subst /,\\,$(OUTDIR)) mkdir $(subst /,\\,$(OUTDIR))
  CMD_MKOBJDIR := $(CMD) /c if not exist $(subst /,\\,$(OBJDIR)) mkdir $(subst /,\\,$(OBJDIR))
endif

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking DIS
	-@$(CMD_MKBINDIR)
	-@$(CMD_MKLIBDIR)
	-@$(CMD_MKOUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning DIS
ifeq ($(MKDIR_TYPE),posix)
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)
else
	-@if exist $(subst /,\,$(OUTDIR)/$(TARGET)) del /q $(subst /,\,$(OUTDIR)/$(TARGET))
	-@if exist $(subst /,\,$(OBJDIR)) del /q $(subst /,\,$(OBJDIR))
	-@if exist $(subst /,\,$(OBJDIR)) rmdir /s /q $(subst /,\,$(OBJDIR))
endif

$(OBJDIR)/AcknowledgePdu.o: ../../cpp/DIS/AcknowledgePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AcknowledgeReliablePdu.o: ../../cpp/DIS/AcknowledgeReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AcousticBeamData.o: ../../cpp/DIS/AcousticBeamData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AcousticBeamFundamentalParameter.o: ../../cpp/DIS/AcousticBeamFundamentalParameter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AcousticEmitter.o: ../../cpp/DIS/AcousticEmitter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AcousticEmitterSystem.o: ../../cpp/DIS/AcousticEmitterSystem.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AcousticEmitterSystemData.o: ../../cpp/DIS/AcousticEmitterSystemData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ActionRequestPdu.o: ../../cpp/DIS/ActionRequestPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ActionRequestReliablePdu.o: ../../cpp/DIS/ActionRequestReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ActionResponsePdu.o: ../../cpp/DIS/ActionResponsePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ActionResponseReliablePdu.o: ../../cpp/DIS/ActionResponseReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AggregateID.o: ../../cpp/DIS/AggregateID.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AggregateMarking.o: ../../cpp/DIS/AggregateMarking.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AggregateStatePdu.o: ../../cpp/DIS/AggregateStatePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AggregateType.o: ../../cpp/DIS/AggregateType.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AngularVelocityVector.o: ../../cpp/DIS/AngularVelocityVector.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/AntennaLocation.o: ../../cpp/DIS/AntennaLocation.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ApaData.o: ../../cpp/DIS/ApaData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ArealObjectStatePdu.o: ../../cpp/DIS/ArealObjectStatePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ArticulationParameter.o: ../../cpp/DIS/ArticulationParameter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/BeamAntennaPattern.o: ../../cpp/DIS/BeamAntennaPattern.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/BeamData.o: ../../cpp/DIS/BeamData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/BurstDescriptor.o: ../../cpp/DIS/BurstDescriptor.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ClockTime.o: ../../cpp/DIS/ClockTime.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/CollisionElasticPdu.o: ../../cpp/DIS/CollisionElasticPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/CollisionPdu.o: ../../cpp/DIS/CollisionPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/CommentPdu.o: ../../cpp/DIS/CommentPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/CommentReliablePdu.o: ../../cpp/DIS/CommentReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/CreateEntityPdu.o: ../../cpp/DIS/CreateEntityPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/CreateEntityReliablePdu.o: ../../cpp/DIS/CreateEntityReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DataPdu.o: ../../cpp/DIS/DataPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DataQueryPdu.o: ../../cpp/DIS/DataQueryPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DataQueryReliablePdu.o: ../../cpp/DIS/DataQueryReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DataReliablePdu.o: ../../cpp/DIS/DataReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DeadReckoningParameter.o: ../../cpp/DIS/DeadReckoningParameter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DesignatorPdu.o: ../../cpp/DIS/DesignatorPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DetonationPdu.o: ../../cpp/DIS/DetonationPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DistributedEmissionsFamilyPdu.o: ../../cpp/DIS/DistributedEmissionsFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EightByteChunk.o: ../../cpp/DIS/EightByteChunk.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ElectronicEmissionBeamData.o: ../../cpp/DIS/ElectronicEmissionBeamData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ElectronicEmissionsPdu.o: ../../cpp/DIS/ElectronicEmissionsPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ElectronicEmissionSystemData.o: ../../cpp/DIS/ElectronicEmissionSystemData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EmitterSystem.o: ../../cpp/DIS/EmitterSystem.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EntityID.o: ../../cpp/DIS/EntityID.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EntityInformationFamilyPdu.o: ../../cpp/DIS/EntityInformationFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EntityManagementFamilyPdu.o: ../../cpp/DIS/EntityManagementFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EntityStatePdu.o: ../../cpp/DIS/EntityStatePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EntityStateUpdatePdu.o: ../../cpp/DIS/EntityStateUpdatePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EntityType.o: ../../cpp/DIS/EntityType.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Environment.o: ../../cpp/DIS/Environment.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EnvironmentalProcessPdu.o: ../../cpp/DIS/EnvironmentalProcessPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EventID.o: ../../cpp/DIS/EventID.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EventReportPdu.o: ../../cpp/DIS/EventReportPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/EventReportReliablePdu.o: ../../cpp/DIS/EventReportReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/FastEntityStatePdu.o: ../../cpp/DIS/FastEntityStatePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/FirePdu.o: ../../cpp/DIS/FirePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/FixedDatum.o: ../../cpp/DIS/FixedDatum.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/FourByteChunk.o: ../../cpp/DIS/FourByteChunk.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/FundamentalParameterData.o: ../../cpp/DIS/FundamentalParameterData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/FundamentalParameterDataIff.o: ../../cpp/DIS/FundamentalParameterDataIff.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/GridAxisRecord.o: ../../cpp/DIS/GridAxisRecord.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/GridAxisRecordRepresentation0.o: ../../cpp/DIS/GridAxisRecordRepresentation0.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/GridAxisRecordRepresentation1.o: ../../cpp/DIS/GridAxisRecordRepresentation1.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/GridAxisRecordRepresentation2.o: ../../cpp/DIS/GridAxisRecordRepresentation2.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/GriddedDataPdu.o: ../../cpp/DIS/GriddedDataPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/IffAtcNavAidsLayer1Pdu.o: ../../cpp/DIS/IffAtcNavAidsLayer1Pdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/IffAtcNavAidsLayer2Pdu.o: ../../cpp/DIS/IffAtcNavAidsLayer2Pdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/IffFundamentalData.o: ../../cpp/DIS/IffFundamentalData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/IntercomCommunicationsParameters.o: ../../cpp/DIS/IntercomCommunicationsParameters.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/IntercomControlPdu.o: ../../cpp/DIS/IntercomControlPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/IntercomSignalPdu.o: ../../cpp/DIS/IntercomSignalPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/IsGroupOfPdu.o: ../../cpp/DIS/IsGroupOfPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/IsPartOfPdu.o: ../../cpp/DIS/IsPartOfPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/LayerHeader.o: ../../cpp/DIS/LayerHeader.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/LinearObjectStatePdu.o: ../../cpp/DIS/LinearObjectStatePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/LinearSegmentParameter.o: ../../cpp/DIS/LinearSegmentParameter.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/LogisticsFamilyPdu.o: ../../cpp/DIS/LogisticsFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/LogisticsPdu.o: ../../cpp/DIS/LogisticsPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Marking.o: ../../cpp/DIS/Marking.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/MinefieldDataPdu.o: ../../cpp/DIS/MinefieldDataPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/MinefieldFamilyPdu.o: ../../cpp/DIS/MinefieldFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/MinefieldPduFamily.o: ../../cpp/DIS/MinefieldPduFamily.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/MinefieldQueryPdu.o: ../../cpp/DIS/MinefieldQueryPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/MinefieldResponseNackPdu.o: ../../cpp/DIS/MinefieldResponseNackPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/MinefieldStatePdu.o: ../../cpp/DIS/MinefieldStatePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ModulationType.o: ../../cpp/DIS/ModulationType.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/NamedLocation.o: ../../cpp/DIS/NamedLocation.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ObjectType.o: ../../cpp/DIS/ObjectType.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/OneByteChunk.o: ../../cpp/DIS/OneByteChunk.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Orientation.o: ../../cpp/DIS/Orientation.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Pdu.o: ../../cpp/DIS/Pdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Point.o: ../../cpp/DIS/Point.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/PointObjectStatePdu.o: ../../cpp/DIS/PointObjectStatePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/PropulsionSystemData.o: ../../cpp/DIS/PropulsionSystemData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/RadioCommunicationsFamilyPdu.o: ../../cpp/DIS/RadioCommunicationsFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/RadioEntityType.o: ../../cpp/DIS/RadioEntityType.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ReceiverPdu.o: ../../cpp/DIS/ReceiverPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/RecordQueryReliablePdu.o: ../../cpp/DIS/RecordQueryReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/RecordSet.o: ../../cpp/DIS/RecordSet.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Relationship.o: ../../cpp/DIS/Relationship.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/RemoveEntityPdu.o: ../../cpp/DIS/RemoveEntityPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/RemoveEntityReliablePdu.o: ../../cpp/DIS/RemoveEntityReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/RepairCompletePdu.o: ../../cpp/DIS/RepairCompletePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/RepairResponsePdu.o: ../../cpp/DIS/RepairResponsePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ResupplyCancelPdu.o: ../../cpp/DIS/ResupplyCancelPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ResupplyOfferPdu.o: ../../cpp/DIS/ResupplyOfferPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ResupplyReceivedPdu.o: ../../cpp/DIS/ResupplyReceivedPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SeesPdu.o: ../../cpp/DIS/SeesPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ServiceRequestPdu.o: ../../cpp/DIS/ServiceRequestPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SetDataPdu.o: ../../cpp/DIS/SetDataPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SetDataReliablePdu.o: ../../cpp/DIS/SetDataReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SetRecordReliablePdu.o: ../../cpp/DIS/SetRecordReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/ShaftRPMs.o: ../../cpp/DIS/ShaftRPMs.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SignalPdu.o: ../../cpp/DIS/SignalPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SimulationAddress.o: ../../cpp/DIS/SimulationAddress.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SimulationManagementFamilyPdu.o: ../../cpp/DIS/SimulationManagementFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SimulationManagementWithReliabilityFamilyPdu.o: ../../cpp/DIS/SimulationManagementWithReliabilityFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SixByteChunk.o: ../../cpp/DIS/SixByteChunk.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SphericalHarmonicAntennaPattern.o: ../../cpp/DIS/SphericalHarmonicAntennaPattern.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/StartResumePdu.o: ../../cpp/DIS/StartResumePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/StartResumeReliablePdu.o: ../../cpp/DIS/StartResumeReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/StopFreezePdu.o: ../../cpp/DIS/StopFreezePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/StopFreezeReliablePdu.o: ../../cpp/DIS/StopFreezeReliablePdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SupplyQuantity.o: ../../cpp/DIS/SupplyQuantity.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SyntheticEnvironmentFamilyPdu.o: ../../cpp/DIS/SyntheticEnvironmentFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/SystemID.o: ../../cpp/DIS/SystemID.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TrackJamTarget.o: ../../cpp/DIS/TrackJamTarget.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TransferControlRequestPdu.o: ../../cpp/DIS/TransferControlRequestPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TransmitterPdu.o: ../../cpp/DIS/TransmitterPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/TwoByteChunk.o: ../../cpp/DIS/TwoByteChunk.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/UaPdu.o: ../../cpp/DIS/UaPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/VariableDatum.o: ../../cpp/DIS/VariableDatum.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Vector3Double.o: ../../cpp/DIS/Vector3Double.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Vector3Float.o: ../../cpp/DIS/Vector3Float.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/VectoringNozzleSystemData.o: ../../cpp/DIS/VectoringNozzleSystemData.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/WarfareFamilyPdu.o: ../../cpp/DIS/WarfareFamilyPdu.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/Conversion.o: ../../CppUtils/DIS/Conversion.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/DataStream.o: ../../CppUtils/DIS/DataStream.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/IncomingMessage.o: ../../CppUtils/DIS/IncomingMessage.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/PacketFactory.o: ../../CppUtils/DIS/PacketFactory.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/PDUBank.o: ../../CppUtils/DIS/PDUBank.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR)/StreamUtils.o: ../../CppUtils/DIS/StreamUtils.cpp
	-@$(CMD_MKOBJDIR)
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(OBJECTS:%.o=%.d)
