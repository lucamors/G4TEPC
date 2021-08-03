#ifndef G4TEPC_DETECTOR_CONSTRUCTION_H
#define G4TEPC_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4TEPCDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    G4TEPCDetectorConstruction();
    virtual ~G4TEPCDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

};

#endif
