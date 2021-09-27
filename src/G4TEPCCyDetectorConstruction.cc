// User Defined Classes
#include "G4TEPCCyDetectorConstruction.hh"
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
#include "G4Tubs.hh"

// Visualization Libraries
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4TEPCCyDetectorConstruction::G4TEPCCyDetectorConstruction()
: G4VUserDetectorConstruction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4TEPCCyDetectorConstruction::~G4TEPCCyDetectorConstruction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4VPhysicalVolume* G4TEPCCyDetectorConstruction::Construct()
{

  /////////////////////////////////////////////////////////////////////////////
  // Materials Definition
  /////////////////////////////////////////////////////////////////////////////
  G4NistManager * nist = G4NistManager::Instance();

  G4Material * material_Air          = nist->FindOrBuildMaterial("G4_AIR");
  G4Material * material_Aluminum     = nist->FindOrBuildMaterial("G4_Al");
  G4Material * material_Water        = nist->FindOrBuildMaterial("G4_WATER");
  G4Material * material_A150_plastic = nist->FindOrBuildMaterial("G4_A-150_TISSUE");

  G4Element * element_C = new G4Element("Carbon","C",6,12.011*g/mole);
  G4Element * element_H = new G4Element("Hydrogen","H",1,1.008*g/mole);
  G4Element * element_N = new G4Element("Nitrogen","N",7,14.007*g/mole);
  G4Element * element_O = new G4Element("Oxygen","O",8,15.999*g/mole);

  G4int natoms;
  G4int ncomponents = 2;
  G4double density = 1.05*g/cm3;
  G4Material *material_Rexolite = new G4Material("Rexolite",density, ncomponents);
  material_Rexolite->AddElement(element_C,natoms=8);
  material_Rexolite->AddElement(element_H,natoms=8);

  density = 1.06409e-3*g/cm3;
  ncomponents = 2;
  G4Material * material_TEGas = new G4Material("TEGas",density, ncomponents);
  material_TEGas->AddElement(element_H,natoms=8);
  material_TEGas->AddElement(element_C,natoms=3);
  // material_TEGas->AddElement(element_N,0.035172);
  // material_TEGas->AddElement(element_O,0.406780);

  /////////////////////////////////////////////////////////////////////////////
  // World Volume
  /////////////////////////////////////////////////////////////////////////////

  G4double world_half_Z  = 50*cm;
  G4double world_half_XY = 50*cm;

  G4Box * solid_World = new G4Box("solid_World", world_half_XY, world_half_XY, world_half_Z);

  G4LogicalVolume* logical_World = new G4LogicalVolume(solid_World,
                                                       material_Air,
                                                       "logical_World",
                                                       0,
                                                       0,
                                                       0,
                                                       true);

  G4VPhysicalVolume * physical_World = new G4PVPlacement(0,
                                                        G4ThreeVector(),
                                                        logical_World,
                                                        "physicalWorld",
                                                        0,
                                                        false,
                                                        0,
                                                        true);

  /////////////////////////////////////////////////////////////////////////////
  // Water Phantom
  /////////////////////////////////////////////////////////////////////////////

  G4double phantom_half_side_length = 150*mm;

  G4Box * solid_WaterPhantom = new G4Box("solid_WaterPhantom", phantom_half_side_length, phantom_half_side_length, phantom_half_side_length);

  G4LogicalVolume * logical_WaterPhantom
    = new G4LogicalVolume(solid_WaterPhantom, material_Water, "logical_WaterPhantom",0,0,0,true);

  new G4PVPlacement(0,
                    G4ThreeVector(),
                    logical_WaterPhantom,
                    "physical_WaterPhantom",
                    logical_World,
                    false,
                    0,
                    true);

  /////////////////////////////////////////////////////////////////////////////
  // Aluminum Enclosure
  /////////////////////////////////////////////////////////////////////////////

  G4double spanning_angle = 360;

  G4double pRmin = 0*mm;
  G4double pRmax = 2.7/2.0*mm;
  G4double halfZ = 1.31/2.0*mm;

  G4Tubs * solid_AluminumEnclosure = new G4Tubs("solid_AluminumEnclosure",
                                               pRmin,
                                               pRmax,
                                               halfZ,
                                               0*deg,
                                               spanning_angle);

  G4LogicalVolume * logical_AluminumEnclosure =
    new G4LogicalVolume(solid_AluminumEnclosure,
                        material_Aluminum,
                        "logical_AluminumEnclosure",
                        0,
                        0,
                        0,
                        true);


  new G4PVPlacement(0,
                    G4ThreeVector(0,109.8*mm,0),
                    logical_AluminumEnclosure,
                    "physical_AluminumEnclosure",
                    logical_WaterPhantom,
                    false,
                    0,
                    true);

  /////////////////////////////////////////////////////////////////////////////
  // Rexolite Insulator
  /////////////////////////////////////////////////////////////////////////////

  pRmin = 0*mm;
  pRmax = 2.3/2.0*mm;
  halfZ = 1.31/2.0*mm;

  G4Tubs * solid_RexoliteInsulator = new G4Tubs("solid_RexoliteInsulator",
                                                pRmin,
                                                pRmax,
                                                halfZ,
                                                0*deg,
                                                spanning_angle);

  G4LogicalVolume * logical_RexoliteInsulator =
    new G4LogicalVolume(solid_RexoliteInsulator,
                        material_Rexolite,
                        "logical_RexoliteInsulator",
                        0,
                        0,
                        0,
                        true);


  new G4PVPlacement(0,
                    G4ThreeVector(),
                    logical_RexoliteInsulator,
                    "physical_RexoliteInsulator",
                    logical_AluminumEnclosure,
                    false,
                    0,
                    true);


  /////////////////////////////////////////////////////////////////////////////
  // A-150 Tissue-Equivalent Plastic
  /////////////////////////////////////////////////////////////////////////////

  pRmin = 0*mm;
  pRmax = 1.6/2.0*mm;
  halfZ = 1.31/2.0*mm;

  G4Tubs * solid_A150Plastic = new G4Tubs("solid_A150Plastic",
                                          pRmin,
                                          pRmax,
                                          halfZ,
                                          0*deg,
                                          spanning_angle);

  G4LogicalVolume * logical_A150Plastic =
    new G4LogicalVolume(solid_A150Plastic,
                        material_A150_plastic,
                        "logical_A150Plastic",
                        0,
                        0,
                        0,
                        true);

  new G4PVPlacement(0,
                    G4ThreeVector(),
                    logical_A150Plastic,
                    "physical_A150Plastic",
                    logical_RexoliteInsulator,
                    false,
                    0,
                    true);


  /////////////////////////////////////////////////////////////////////////////
  // Rexolite Disks
  /////////////////////////////////////////////////////////////////////////////

  pRmin = 0*mm;
  pRmax = 0.9/2.0*mm;
  halfZ = 0.1025*mm;

  G4Tubs * solid_RexoliteDisk = new G4Tubs("solid_RexoliteDisk",
                                           pRmin,
                                           pRmax,
                                           halfZ,
                                           0*deg,
                                           spanning_angle);

  G4LogicalVolume * logical_RexoliteDisk =
    new G4LogicalVolume(solid_RexoliteDisk,
                        material_Rexolite,
                        "logical_RexoliteDisk",
                        0,
                        0,
                        0,
                        true);


  new G4PVPlacement(0,
                    G4ThreeVector(0,0,0.5525),
                    logical_RexoliteDisk,
                    "physical_RexoliteDisk_front",
                    logical_A150Plastic,
                    false,
                    0,
                    true);

  new G4PVPlacement(0,
                    G4ThreeVector(0,0,-0.5525),
                    logical_RexoliteDisk,
                    "physical_RexoliteDisk_back",
                    logical_A150Plastic,
                    false,
                    0,
                    true);

  /////////////////////////////////////////////////////////////////////////////
  // Tissue-Equivalent Gas
  /////////////////////////////////////////////////////////////////////////////

  pRmin = 0*mm;
  pRmax = 0.9/2.0*mm;
  halfZ = 0.9/2.0*mm;

  G4Tubs* solid_TEGas = new G4Tubs("solid_TEGas",
                                   pRmin,
                                   pRmax,
                                   halfZ,
                                   0*deg,
                                   spanning_angle);

  G4LogicalVolume * logical_TEGas =
    new G4LogicalVolume(solid_TEGas,
                        material_TEGas,
                        "logical_TEGas",
                        0,
                        0,
                        0,
                        true);

  new G4PVPlacement(0,
                   G4ThreeVector(),
                   logical_TEGas,
                   "physical_TEGas",
                   logical_A150Plastic,
                   false,
                   0,
                   true);

  /////////////////////////////////////////////////////////////////////////////
  // Visualization Attributes
  /////////////////////////////////////////////////////////////////////////////

  logical_World->SetVisAttributes(G4VisAttributes::Invisible);
  logical_WaterPhantom->SetVisAttributes(new G4VisAttributes(G4Colour(135.0/255, 255.0/255, 243.0/255, 0.4)));
  logical_AluminumEnclosure->SetVisAttributes(new G4VisAttributes(G4Colour(102.0/255, 103.0/255, 105.0/255, 0.4)));
  logical_RexoliteInsulator->SetVisAttributes(new G4VisAttributes(G4Colour(236.0/255, 255.0/255, 191.0/255, 0.4)));
  logical_RexoliteDisk->SetVisAttributes(new G4VisAttributes(G4Colour(236.0/255, 255.0/255, 191.0/255, 0.4)));
  logical_A150Plastic->SetVisAttributes(new G4VisAttributes(G4Colour(130.0/255, 255.0/255, 222.0/255, 0.4)));
  logical_TEGas->SetVisAttributes(new G4VisAttributes(G4Colour(59.0/255, 59.0/255, 59.0/255, 0.4)));

  return physical_World;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4TEPCCyDetectorConstruction::ConstructSDandField()
{
  G4TEPCSensitiveDetector * sd = new G4TEPCSensitiveDetector("TEPC SD","TEPCHitsCollection");

  G4SDManager::GetSDMpointer()->AddNewDetector(sd);
  SetSensitiveDetector("logical_TEGas", sd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
