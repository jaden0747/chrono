// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All right reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Alessandro Tasora, Radu Serban
// =============================================================================

#include <algorithm>

#include "chrono/core/ChClassFactory.h"
#include "chrono/physics/ChMaterialSurfaceNSC.h"

namespace chrono {

// -----------------------------------------------------------------------------

// Register into the object factory, to enable run-time dynamic creation and persistence
CH_FACTORY_REGISTER(ChMaterialSurfaceNSC)

ChMaterialSurfaceNSC::ChMaterialSurfaceNSC()
    : static_friction(0.6f),
      sliding_friction(0.6f),
      rolling_friction(0),
      spinning_friction(0),
      restitution(0),
      cohesion(0),
      dampingf(0),
      compliance(0),
      complianceT(0),
      complianceRoll(0),
      complianceSpin(0) {}

ChMaterialSurfaceNSC::ChMaterialSurfaceNSC(const ChMaterialSurfaceNSC& other) {
    static_friction = other.static_friction;
    sliding_friction = other.sliding_friction;
    rolling_friction = other.rolling_friction;
    spinning_friction = other.spinning_friction;
    restitution = other.restitution;
    cohesion = other.cohesion;
    dampingf = other.dampingf;
    compliance = other.compliance;
    complianceT = other.complianceT;
    complianceRoll = other.complianceRoll;
    complianceSpin = other.complianceSpin;
}

void ChMaterialSurfaceNSC::SetFriction(float mval) {
    SetSfriction(mval);
    SetKfriction(mval);
}

void ChMaterialSurfaceNSC::ArchiveOUT(ChArchiveOut& marchive) {
    // version number
    marchive.VersionWrite<ChMaterialSurfaceNSC>();

    // serialize parent class
    ChMaterialSurface::ArchiveOUT(marchive);

    // serialize all member data:
    marchive << CHNVP(static_friction);
    marchive << CHNVP(sliding_friction);
    marchive << CHNVP(rolling_friction);
    marchive << CHNVP(spinning_friction);
    marchive << CHNVP(restitution);
    marchive << CHNVP(cohesion);
    marchive << CHNVP(dampingf);
    marchive << CHNVP(compliance);
    marchive << CHNVP(complianceT);
    marchive << CHNVP(complianceRoll);
    marchive << CHNVP(complianceSpin);
}

void ChMaterialSurfaceNSC::ArchiveIN(ChArchiveIn& marchive) {
    // version number
    int version = marchive.VersionRead<ChMaterialSurfaceNSC>();

    // deserialize parent class
    ChMaterialSurface::ArchiveIN(marchive);

    // stream in all member data:
    marchive >> CHNVP(static_friction);
    marchive >> CHNVP(sliding_friction);
    marchive >> CHNVP(rolling_friction);
    marchive >> CHNVP(spinning_friction);
    marchive >> CHNVP(restitution);
    marchive >> CHNVP(cohesion);
    marchive >> CHNVP(dampingf);
    marchive >> CHNVP(compliance);
    marchive >> CHNVP(complianceT);
    marchive >> CHNVP(complianceRoll);
    marchive >> CHNVP(complianceSpin);
}

// -----------------------------------------------------------------------------

ChMaterialCompositeNSC::ChMaterialCompositeNSC()
    : static_friction(0),
      sliding_friction(0),
      rolling_friction(0),
      spinning_friction(0),
      restitution(0),
      cohesion(0),
      dampingf(0),
      compliance(0),
      complianceT(0),
      complianceRoll(0),
      complianceSpin(0) {}

ChMaterialCompositeNSC::ChMaterialCompositeNSC(std::shared_ptr<ChMaterialSurfaceNSC> mat1,
                                               std::shared_ptr<ChMaterialSurfaceNSC> mat2) {
    static_friction = std::min<float>(mat1->static_friction, mat2->static_friction);
    sliding_friction = std::min<float>(mat1->sliding_friction, mat2->sliding_friction);
    restitution = std::min<float>(mat1->restitution, mat2->restitution);
    cohesion = std::min<float>(mat1->cohesion, mat2->cohesion);
    dampingf = std::min<float>(mat1->dampingf, mat2->dampingf);
    compliance = mat1->compliance + mat2->compliance;
    complianceT = mat1->complianceT + mat2->complianceT;

    rolling_friction = std::min<float>(mat1->rolling_friction, mat2->rolling_friction);
    spinning_friction = std::min<float>(mat1->spinning_friction, mat2->spinning_friction);
    complianceRoll = mat1->complianceRoll + mat2->complianceRoll;
    complianceSpin = mat1->complianceSpin + mat2->complianceSpin;
}

}  // end namespace chrono