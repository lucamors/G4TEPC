#include "G4TEPCSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"

G4TEPCSensitiveDetector::G4TEPCSensitiveDetector()
: G4VSensitiveDetector("det"), fHitsCollection(nullptr){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4TEPCSensitiveDetector::G4TEPCSensitiveDetector(const G4String& name, const G4String& HC_name)
: G4VSensitiveDetector(name), fHitsCollection(nullptr)
{
  collectionName.insert(HC_name);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4TEPCSensitiveDetector::~G4TEPCSensitiveDetector(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4TEPCSensitiveDetector::Initialize(G4HCofThisEvent* hitCollectionOfEvent)
{
  // Create a Hit Collection
  fHitsCollection = new G4TEPCHitsCollection(SensitiveDetectorName, collectionName[0]);

  auto HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

  hitCollectionOfEvent->AddHitsCollection(HCID, fHitsCollection);

  return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4bool G4TEPCSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
{

  // Create an hit object
  G4TEPCHit * hit = new G4TEPCHit();
  G4double edep = step->GetTotalEnergyDeposit()/CLHEP::keV;


  // The mean chord length is computed as <l> = 4 * <Tissue Equivalent Radius in um> / 3
#ifdef SPHERICAL_GEOMETRY
  edep /= ((4.0/3.0) * 1 );
#else
  edep /= ((4.0/3.0) * 1 );
#endif


  if(edep > 0)
  {
    // G4cout << edep << G4endl;
    hit->SetEdep(edep);
    fHitsCollection->insert(hit);
  }

  return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4TEPCSensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
  return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
