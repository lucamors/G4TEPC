#include "G4TEPCDetectorConstruction.hh"
#include "G4TEPCSensitiveDetector.hh"

#include "G4SystemOfUnits.hh"


#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
// CGS Geometry Includes
#include "G4Box.hh"

G4TEPCDetectorConstruction::G4TEPCDetectorConstruction()
: G4VUserDetectorConstruction() {}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4TEPCDetectorConstruction::~G4TEPCDetectorConstruction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4VPhysicalVolume* G4TEPCDetectorConstruction::Construct()
{
   // Construct Geometry
   
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4TEPCDetectorConstruction::ConstructSDandField()
{
  G4TEPCSensitiveDetector * sd = new G4TEPCSensitiveDetector("TEPC SD","TEPCHitsCollection");

  G4SDManager::GetSDMpointer()->AddNewDetector(sd);
  SetSensitiveDetector("Envelope", sd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
