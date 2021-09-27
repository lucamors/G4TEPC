#ifndef G4TEPC_DETECTOR_CONSTRUCTION_H
#define G4TEPC_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4TEPCCyDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    G4TEPCCyDetectorConstruction();
    virtual ~G4TEPCCyDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

};

#endif
