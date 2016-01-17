/**
 * Section 5.2.22. Contains electromagnetic emmision regineratin parameters that are        variable throughout a scenario dependent on the actions of the participants in the simulation. Also provides basic parametric data that may be used to support low-fidelity simulations.
 *
 * Copyright (c) 2008-2013, MOVES Institute, Naval Postgraduate School. All rights reserved.
 * This work is licensed under the BSD open source license, available at https://www.movesinstitute.org/licenses/bsd.html
 *
 * @author DMcG
 */
if (typeof dis === "undefined")
 dis = {};

 dis.FundamentalParameterData = function()
{
   /** center frequency of the emission in hertz. */
  this.frequency = 0;

   /** Bandwidth of the frequencies corresponding to the fequency field. */
  this.frequencyRange = 0;

   /** Effective radiated power for the emission in DdBm. For a      radar noise jammer, indicates the peak of the transmitted power. */
  this.effectiveRadiatedPower = 0;

   /** Average repetition frequency of the emission in hertz. */
  this.pulseRepetitionFrequency = 0;

   /** Average pulse width  of the emission in microseconds. */
  this.pulseWidth = 0;

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
