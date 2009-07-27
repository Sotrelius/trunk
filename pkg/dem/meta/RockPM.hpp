/*************************************************************************
*    Copyright (C) 2009 Anton Gladkyy gladky.anton@gmail.com             *
*                                                                        *
*    This program is free software: you can redistribute it and/or modify*
*    it under the terms of the GNU General Public License as published by*
*    the Free Software Foundation, either version 3 of the License, or   *
*    (at your option) any later version.                                 *
*                                                                        *
*    This program is distributed in the hope that it will be useful,     *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of      *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       *
*    GNU General Public License for more details.                        *
*                                                                        *
*    You should have received a copy of the GNU General Public License   *
*    along with this program.  If not, see <http://www.gnu.org/licenses/>*
**************************************************************************/
/*

=== HIGH LEVEL OVERVIEW OF RockPM ===

Rock Particle Model (RockPM) is a set of classes for modelling
mechanical behavior of mining rocks.
*/

#pragma once

#include<yade/pkg-common/RigidBodyParameters.hpp>
#include<yade/pkg-dem/BodyMacroParameters.hpp>
#include<yade/pkg-common/InteractionPhysicsEngineUnit.hpp>
#include<yade/pkg-dem/SpheresContactGeometry.hpp>
#include<yade/pkg-common/PeriodicEngines.hpp>
#include<yade/pkg-common/NormalShearInteractions.hpp>
#include<yade/pkg-common/ConstitutiveLaw.hpp>


class Law2_Dem3DofGeom_RockPMPhys_Rpm: public ConstitutiveLaw{
	public:
		virtual void go(shared_ptr<InteractionGeometry>& _geom, shared_ptr<InteractionPhysics>& _phys, Interaction* I, MetaBody* rootBody);
		FUNCTOR2D(Dem3DofGeom,RpmPhys);
		REGISTER_CLASS_AND_BASE(Law2_Dem3DofGeom_RockPMPhys_Rpm,ConstitutiveLaw);
		REGISTER_ATTRIBUTES(ConstitutiveLaw,/*nothing here*/);
		DECLARE_LOGGER;	
};
REGISTER_SERIALIZABLE(Law2_Dem3DofGeom_RockPMPhys_Rpm);

/* This class holds information associated with each body */
class RpmMat: public BodyMacroParameters {
	public:
		int exampleNumber; //Number of "stone"
		bool initCohesive, isDamaged;
		Real stressCompressMax, stressTensionMax; //Parameters for damaging

		RpmMat(): exampleNumber(0.), initCohesive(false), isDamaged(false), stressCompressMax(0), stressTensionMax(0) {createIndex();};
		REGISTER_ATTRIBUTES(BodyMacroParameters, 
			(exampleNumber)
			(initCohesive)
			(isDamaged)
			(stressCompressMax)
			(stressTensionMax));
		REGISTER_CLASS_AND_BASE(RpmMat,BodyMacroParameters);
};
REGISTER_SERIALIZABLE(RpmMat);


class Ip2_RpmMat_RpmMat_RpmPhys: public InteractionPhysicsEngineUnit{
	private:
	public:
		Real sigmaT, initDistance;

		Ip2_RpmMat_RpmMat_RpmPhys(){
			initDistance = 0;
		}

		virtual void go(const shared_ptr<PhysicalParameters>& pp1, const shared_ptr<PhysicalParameters>& pp2, const shared_ptr<Interaction>& interaction);
		REGISTER_ATTRIBUTES(InteractionPhysicsEngineUnit,
			(sigmaT)
			(initDistance)
		);

		FUNCTOR2D(RpmMat,RpmMat);
		REGISTER_CLASS_AND_BASE(Ip2_RpmMat_RpmMat_RpmPhys,InteractionPhysicsEngineUnit);
		DECLARE_LOGGER;
};
REGISTER_SERIALIZABLE(Ip2_RpmMat_RpmMat_RpmPhys);


class RpmPhys: public NormalShearInteraction {
	private:
	public:
		Real crossSection,E,G,tanFrictionAngle,lengthMaxCompression,lengthMaxTension;
		bool isCohesive;

		RpmPhys(): NormalShearInteraction(),crossSection(0),E(0),G(0), tanFrictionAngle(0), lengthMaxCompression(0), lengthMaxTension(0), isCohesive(false) { createIndex();}
		virtual ~RpmPhys();

		REGISTER_ATTRIBUTES(NormalShearInteraction,
			(E)
			(G)
			(tanFrictionAngle)
			(isCohesive)
			(lengthMaxCompression)
			(lengthMaxTension)
		);
	REGISTER_CLASS_AND_BASE(RpmPhys,NormalShearInteraction);
};
REGISTER_SERIALIZABLE(RpmPhys);