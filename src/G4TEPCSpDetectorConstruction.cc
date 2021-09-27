// User Defined Classes
#include "G4TEPCSpDetectorConstruction.hh"
#include "G4TEPCSensitiveDetector.hh"

// Geometry Related Libraries
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

// CGS Geometry Classes
#include "G4Box.hh"
#include "G4Sphere.hh"

// Visualization Libraries
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4TEPCSpDetectorConstruction::G4TEPCSpDetectorConstruction()
: G4VUserDetectorConstruction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4TEPCSpDetectorConstruction::~G4TEPCSpDetectorConstruction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4VPhysicalVolume* G4TEPCSpDetectorConstruction::Construct()
{

  /////////////////////////////////////////////////////////////////////////////
  // Materials Definition
  /////////////////////////////////////////////////////////////////////////////
  G4NistManager * nist = G4NistManager::Instance();

  G4Material * materialAir          = nist->FindOrBuildMaterial("G4_AIR");
  G4Material * materialAluminum     = nist->FindOrBuildMaterial("G4_Al");
  G4Material * materialA150_plastic = nist->FindOrBuildMaterial("G4_A-150_TISSUE");

  // Temporary material --> only for testing
  G4Material * materialTEGas        = nist->FindOrBuildMaterial("G4_PROPANE");


  /////////////////////////////////////////////////////////////////////////////
  // World Volume
  /////////////////////////////////////////////////////////////////////////////

  G4double world_half_Z  = 10*cm;
  G4double world_half_XY = 5*cm;

  G4Box * solidWorld = new G4Box("solidWorld", world_half_XY, world_half_XY, world_half_Z);
  G4LogicalVolume* logicalWorld = new G4LogicalVolume(solidWorld, materialAir, "logicalWorld", 0, 0, 0, true);

  G4VPhysicalVolume * physicalWorld = new G4PVPlacement(0,
                                                        G4ThreeVector(),
                                                        logicalWorld,
                                                        "physicalWorld",
                                                        0,
                                                        false,
                                                        0,
                                                        true);

  /////////////////////////////////////////////////////////////////////////////
  // TEPC - Spherical Geometry
  /////////////////////////////////////////////////////////////////////////////

  G4double spanning_angle = 360;

  // Aluminum Enclosure

  G4double TEPC_radius = 10*mm;

  G4Sphere * solidAluminumEnclosure = new G4Sphere("solidAluminumEnclosure",0, TEPC_radius, 0, spanning_angle*deg, 0, 180*deg);
  G4LogicalVolume * logicalAluminumEnclosure = new G4LogicalVolume(solidAluminumEnclosure, materialAluminum, "logicalAluminumEnclosure", 0, 0, 0, true);

  new G4PVPlacement(0,
                    G4ThreeVector(),
                    logicalAluminumEnclosure,
                    "physicalAluminumEnclosure",
                    logicalWorld,
                    false,
                    0,
                    true);

  // Outer Tissue Equivalent Gas

  G4double OuterTEG_radius = 19.82/2.0*mm;

  G4Sphere * solidOuterTEG = new G4Sphere("solidOuterTEG",0, OuterTEG_radius, 0, spanning_angle*deg, 0, 180*deg);
  G4LogicalVolume * logicalOuterTEG = new G4LogicalVolume(solidOuterTEG, materialTEGas, "logicalOuterTEG", 0, 0, 0, true);

  new G4PVPlacement(0,
                    G4ThreeVector(),
                    logicalOuterTEG,
                    "physicalOuterTEG",
                    logicalAluminumEnclosure,
                    false,
                    0,
                    true);

  // A-150 Plastic

  G4double A150Plastic_radius = 15.24/2.0*mm;

  G4Sphere * solidA150Plastic = new G4Sphere("solidA150Plastic",0, A150Plastic_radius, 0, spanning_angle*deg, 0, 180*deg);
  G4LogicalVolume * logicalA150Plastic = new G4LogicalVolume(solidA150Plastic, materialA150_plastic, "logicalA150Plastic", 0, 0, 0, true);

  new G4PVPlacement(0,
                    G4ThreeVector(),
                    logicalA150Plastic,
                    "physicalA150Plastic",
                    logicalOuterTEG,
                    false,
                    0,
                    true);


  // Inner Tissue Equivalent Gas

  G4double SensitiveVolume_radius = 12.7/2.0*mm;

  G4Sphere * solidSensitiveVolume = new G4Sphere("solidOuterTEG",0, SensitiveVolume_radius, 0, spanning_angle*deg, 0, 180*deg);
  G4LogicalVolume * logicalSensitiveVolume = new G4LogicalVolume(solidSensitiveVolume, materialTEGas, "logicalSensitiveVolume", 0, 0, 0, true);

  new G4PVPlacement(0,
                    G4ThreeVector(),
                    logicalSensitiveVolume,
                    "physicalSensitiveVolume",
                    logicalA150Plastic,
                    false,
                    0,
                    true);


  /////////////////////////////////////////////////////////////////////////////
  // Visualization Attributes
  /////////////////////////////////////////////////////////////////////////////

  logicalWorld->SetVisAttributes(G4VisAttributes::Invisible);
  logicalAluminumEnclosure->SetVisAttributes(new G4VisAttributes(G4Colour(102.0/255, 103.0/255, 105.0/255, 0.4)));
  logicalOuterTEG->SetVisAttributes(new G4VisAttributes(G4Colour(236.0/255, 255.0/255, 191.0/255, 0.4)));
  logicalA150Plastic->SetVisAttributes(new G4VisAttributes(G4Colour(130.0/255, 255.0/255, 222.0/255, 0.4)));
  logicalSensitiveVolume->SetVisAttributes(new G4VisAttributes(G4Colour(236.0/255, 255.0/255, 191.0/255, 0.4)));

  return physicalWorld;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4TEPCSpDetectorConstruction::ConstructSDandField()
{
  G4TEPCSensitiveDetector * sd = new G4TEPCSensitiveDetector("TEPC SD","TEPCHitsCollection");

  G4SDManager::GetSDMpointer()->AddNewDetector(sd);
  SetSensitiveDetector("logicalSensitiveVolume", sd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
