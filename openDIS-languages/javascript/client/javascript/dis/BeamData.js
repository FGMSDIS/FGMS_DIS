/**
 * Section 5.2.39. Specification of the data necessary to  describe the scan volume of an emitter.
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.BeamData = function()
{
   /** Specifies the beam azimuth an elevation centers and corresponding half-angles     to describe the scan volume */
  this.beamAzimuthCenter = 0;

   /** Specifies the beam azimuth sweep to determine scan volume */
  this.beamAzimuthSweep = 0;

   /** Specifies the beam elevation center to determine scan volume */
  this.beamElevationCenter = 0;

   /** Specifies the beam elevation sweep to determine scan volume */
  this.beamElevationSweep = 0;

   /** allows receiver to synchronize its regenerated scan pattern to     that of the emmitter. Specifies the percentage of time a scan is through its pattern from its origion. */
  this.beamSweepSync = 0;

} // end of class
