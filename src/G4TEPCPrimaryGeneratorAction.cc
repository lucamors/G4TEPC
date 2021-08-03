#include "G4TEPCPrimaryGeneratorAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4TEPCPrimaryGeneratorAction::G4TEPCPrimaryGeneratorAction()
{
    fParticleGPS = new G4GeneralParticleSource();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4TEPCPrimaryGeneratorAction::~G4TEPCPrimaryGeneratorAction()
{
    delete fParticleGPS;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4TEPCPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGPS->GeneratePrimaryVertex(anEvent);
}
