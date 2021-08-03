#ifndef G4TEPC_PRIMARY_GENERATOR_ACTION_H
#define G4TEPC_PRIMARY_GENERATOR_ACTION_H 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class G4TEPCPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:

    G4TEPCPrimaryGeneratorAction();
    ~G4TEPCPrimaryGeneratorAction();
    void GeneratePrimaries(G4Event* anEvent);

private:
    G4GeneralParticleSource* fParticleGPS;
};

#endif
