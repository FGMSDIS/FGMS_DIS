import struct
import time
import warnings

# @author: Shawn Pollock
# @author: Tommy Getty
# @author: John Weaver

# @title: DIS Entity State PDU 
# @date: 17SEP2010

# @description: This library allows the user to simply create a DIS ESPDU, similar to OPEN-DIS.
#   At this version the data format still needs some massaging to be exactly DIS format, but 
#   does demonstrate the basic idea of creating, passing and decoding PDUs on a network.

def fxn():
    warnings.warn("deprecated", DeprecationWarning)

with warnings.catch_warnings():
    warnings.simplefilter("ignore")
    fxn()

    class ESPDU:
        ESPDU = ""
        # Header Report
        protocolVersion = 6         # Default is IEEE 1278.1-1995
        exerciseID = 0
        pduType = 1                 # Entity State PDU
        protocolFamily = 1          # Entity Information/Interaction
        timeStamp = 0
        pduLength = 144             # 144 Octets for default ESPDU 
        padding = 0

        # Entity Identification Report
        siteID = 0
        applicationID = 0
        entityID = 0

        # Force Identification Report
        forceID = 3                 # Default is 3 neutral

        # Number of Articulation Parameters Report
        numOfArticulationParameters = 0

        # Entity Type Record        Default is U.S. M1A2 tank
        kind = 1                    
        domain = 2                  
        country = 225               
        category = 1
        subCategory = 1
        specific = 3
        extra = 0

        # Alternate Entity Type Record        Default is U.S. M1A2 tank
        altKind = 1                    
        altDomain = 2                  
        altCountry = 225               
        altCategory = 1
        altSubCategory = 1
        altSpecific = 3
        altExtra = 0

        # Entity Linear Velocity Record
        v1 = 0.0
        v2 = 0.0
        v3 = 0.0

        # Entity Location Record
        x = 0.0
        y = 0.0
        z = 0.0

        # Entity Orientation Record
        psi = 0.0
        theta = 0.0
        phi = 0.0

        # Entity Appearance Record
        generalAppearance = 0
        specificAppearance = 0

        # Dead Reckoning Parameters Record
        algorithmDR = 1                     # Default is static entity
        paramsDR = 0
        aX = 0.0
        aY = 0.0
        aZ = 0.0
        wX = 0.0
        wY = 0.0
        wZ = 0.0

        # Entity Marking Record
        markingCharSet = 1                  # Default is ASCII
        markingChar01 = '0'
        markingChar02 = '0'
        markingChar03 = '0'
        markingChar04 = '0'
        markingChar05 = '0'
        markingChar06 = '0'
        markingChar07 = '0'
        markingChar08 = '0'
        markingChar09 = '0'
        markingChar10 = '0'
        markingChar11 = '0'

        # Entity Capabilities Record
        capabilities = 0

        # Articulation Parameters Record. The ESPDU contains zero or more of these, as specified 
        # by the numberOfArticulationParameters field. We'll leave the default at none for now.
        parameterTypeDesignator = 0
        parameterTypeChangeIndicator = 0
        attachmentID = 0
        attachedParts = 0
        articulatedPartsLow = 0
        articulatedPartsHi = 0
        articulationParameterValue = 0
        
        # Note that the "!" character at the start of the pack format string forces the packing to be in network byte order
        
        timeStamp = time.time()
        pduHeader = struct.pack('!BBBBIHH', protocolVersion, exerciseID, pduType, protocolFamily, timeStamp, pduLength, padding)  
                                    
        entityIdent =  struct.pack('!HHH', siteID, applicationID, entityID)

        entityType= struct.pack('!BBHBBBB',
                                    kind,
                                    domain,
                                    country,
                                    category,
                                    subCategory,
                                    specific,
                                    extra)

        altEntityType= struct.pack('!BBHBBBB',
                                    altKind,
                                    altDomain,
                                    altCountry,
                                    altCategory,
                                    altSubCategory,
                                    altSpecific,
                                    altExtra)
                                    
        linearVelocity = struct.pack('!fff',
                                    v1,
                                    v2,
                                    v3)
         
        location = struct.pack('!ddd',
                                    x,
                                    y,
                                    z)

        orientation = struct.pack('!fff',
                                    psi,
                                    theta,
                                    phi)
                                    
        appearance = struct.pack('!HH',
                                    generalAppearance,
                                    specificAppearance)
                                   
        deadReckoningParams = struct.pack('!Bffffff',
                                    algorithmDR,
                                    #paramsDR,
                                    aX,
                                    aY,
                                    aZ,
                                    wX,
                                    wY,
                                    wZ)
                                    
        marking = struct.pack('!Bccccccccccc',
                                    markingCharSet,
                                    markingChar01,
                                    markingChar02,
                                    markingChar03,
                                    markingChar04,
                                    markingChar05,
                                    markingChar06,
                                    markingChar07,
                                    markingChar08,
                                    markingChar09,
                                    markingChar10,
                                    markingChar11)
                                    
        capabilities = 0

        articulationParameters = struct.pack('!BBHLHHd',
                                    parameterTypeDesignator,
                                    parameterTypeChangeIndicator,
                                    attachmentID,
                                    attachedParts,
                                    articulatedPartsLow,
                                    articulatedPartsHi,
                                    articulationParameterValue)
                                    
        espdu = struct.pack('12s 6s BB 8s 8s 12s 24s 12s 4s 28s 12s I',
        #espdu = struct.pack('!BBBBIHH HHH B B BBHBBBB BBHBBBB fff ddd fff I Bffffff b11c I',
                                    pduHeader,
                                    entityIdent,
                                    forceID,
                                    numOfArticulationParameters,
                                    entityType,
                                    altEntityType,
                                    linearVelocity,
                                    location,
                                    orientation,
                                    appearance,
                                    deadReckoningParams,
                                    marking,
                                    capabilities)
                                    #articulationParameters)

        def marshall(self):
            # Sets the timestamp and packs all the data into binary format as a string
            timeStamp = time.time()
            print int(self.timeStamp)
            self.pduHeader = struct.pack('!BBBBIHH', self.protocolVersion, self.exerciseID, self.pduType, self.protocolFamily, self.timeStamp, self.pduLength, self.padding)  
                                        
            self.entityIdent =  struct.pack('HHH',
                                        self.siteID,
                                        self.applicationID,
                                        self.entityID)

            self.entityType= struct.pack('!BBHBBBB',
                                        self.kind,
                                        self.domain,
                                        self.country,
                                        self.category,
                                        self.subCategory,
                                        self.specific,
                                        self.extra)

            self.altEntityType= struct.pack('!BBHBBBB',
                                        self.altKind,
                                        self.altDomain,
                                        self.altCountry,
                                        self.altCategory,
                                        self.altSubCategory,
                                        self.altSpecific,
                                        self.altExtra)
                                        
            self.linearVelocity = struct.pack('!fff',
                                        self.v1,
                                        self.v2,
                                        self.v3)
             
            self.location = struct.pack('ddd',
                                        self.x,
                                        self.y,
                                        self.z)

            self.orientation = struct.pack('!fff',
                                        self.psi,
                                        self.theta,
                                        self.phi)
                                        
            self.appearance = struct.pack('!HH',
                                        self.generalAppearance,
                                        self.specificAppearance)
                                       
            self.deadReckoningParams = struct.pack('!Bffffff',
                                        self.algorithmDR,
                                        #self.paramsDR,
                                        self.aX,
                                        self.aY,
                                        self.aZ,
                                        self.wX,
                                        self.wY,
                                        self.wZ)
                                        
            self.marking = struct.pack('!Bccccccccccc',
                                        self.markingCharSet,
                                        self.markingChar01,
                                        self.markingChar02,
                                        self.markingChar03,
                                        self.markingChar04,
                                        self.markingChar05,
                                        self.markingChar06,
                                        self.markingChar07,
                                        self.markingChar08,
                                        self.markingChar09,
                                        self.markingChar10,
                                        self.markingChar11)

            self.articulationParameters = struct.pack('!BBHLHHd',
                                        self.parameterTypeDesignator,
                                        self.parameterTypeChangeIndicator,
                                        self.attachmentID,
                                        self.attachedParts,
                                        self.articulatedPartsLow,
                                        self.articulatedPartsHi,
                                        self.articulationParameterValue)
                                        
            self.espdu = struct.pack('!12s6sBB8s8s12s24s12s4s28s12sI',
                                        self.pduHeader,
                                        self.entityIdent,
                                        self.forceID,
                                        self.numOfArticulationParameters,
                                        self.entityType,
                                        self.altEntityType,
                                        self.linearVelocity,
                                        self.location,
                                        self.orientation,
                                        self.appearance,
                                        self.deadReckoningParams,
                                        self.marking,
                                        self.capabilities)
                                        #self.articulationParameters)
            
        def __init__(self, datagramIN): # UNMARHSALLING
            if datagramIN != 0:
            
                self.pduHeader, self.entityID, self.forceID, self.numOfArticulationParameters, theRest = struct.unpack('!12s 6s B B 124s', datagramIN)
                self.entityType, self.altEntityType, self.linearVelocity, theRest2 = struct.unpack('!8s 8s 12s 96s', theRest)
                self.location, self.orientation, self.appearance, self.deadReckoningParams, theRest3 = struct.unpack('!24s 12s 4s 28s 28s', theRest2)
                self.marking, self.capabilities, self.articulationParameters = struct.unpack('!12s I 12s', theRest3)
                

                self.protocolVersion, self.exerciseID, self.pduType, self.protocolFamily, theRest = struct.unpack('!BBBB8s', self.pduHeader)
                self.timeStamp, self.pduLength, self.padding = struct.unpack('LHH', theRest)
                                                                  
                self.siteID, self.applicationID, self.entityID =  struct.unpack('HHH', self.entityIdent)
                                            
                self.kind, self.domain, self.country, self.category, theRest = struct.unpack('BBHB3s', self.entityType)
                self.subCategory, self.specific, self.extra = struct.unpack('BBB', theRest)
                                            
                self.altKind, self.altDomain, self.altCountry, self.altCategory, theRest = struct.unpack('BBHB3s', self.altEntityType)
                self.altSubCategory, self.altSpecific, self.altExtra = struct.unpack('BBB', theRest)
                                                                   
                self.v1, self.v2, self.v3 = struct.unpack('fff', self.linearVelocity)
                 
                self.x, self.y, self.z = struct.unpack('ddd', self.location)

                self.psi, self.theta, self.phi = struct.unpack('fff', self.orientation)
                                            
                self.generalAppearance, self.specificAppearance = struct.unpack('HH', self.appearance)
                                                                  
                self.algorithmDR, self.aX, self.aY, self.aZ, theRest = struct.unpack('Bfff12s', self.deadReckoningParams)        #self.paramsDR
                self.wX, self.wY, self.wZ = struct.unpack('fff', theRest)
                                                                        
                self.markingCharSet, self.markingChar01, self.markingChar02, theRest = struct.unpack('Bcc9s', self.marking)
                self.markingChar03, self.markingChar04, self.markingChar05, theRest2 = struct.unpack('ccc6s', theRest)
                self.markingChar06, self.markingChar07, self.markingChar08, theRest3 = struct.unpack('ccc3s', theRest2)
                self.markingChar09, self.markingChar10, self.markingChar11 = struct.unpack('ccc', theRest3)
                self.capabilities = struct.unpack('!I', theRest4)
                
                #self.parameterTypeDesignator, self.parameterTypeChangeIndicator, self.attachmentID, theRest = struct.unpack('BBH12s', self.articulationParameters)
                #self.attachedParts, self.articulatedPartsLow, self.articulatedPartsHi, self.articulationParameterValue = struct.unpack('LHHf', theRest)  
            else:
                self.entityID = 0
                
        def printESPDU(self):          
            # Prints the most relevant data from the ESPDU
            print "Exercise: " + str(self.exerciseID)
            print "Time Stamp: " + str(self.timeStamp)
            print "Force: " + str(self.forceID)
            print "Entity: " + str(self.entityID)
            print "Entity Type: " + str(self.kind) + ", " + str(self.domain) + ", " + str(self.country) + ", " + str(self.category) + ", " + str(self.subCategory) + ", " + str(self.specific) + ", " + str(self.extra)
            print "Posit: (" + str(self.x) + ", " + str(self.y) + ", " + str(self.z) + ")"
            print "Velocity: (" + str(self.v1) + ", " + str(self.v2) + ", " + str(self.v3) + ")"
            print "Orienation: (" + str(self.psi) + ", " + str(self.theta) + ", " + str(self.phi) + ")"
            
