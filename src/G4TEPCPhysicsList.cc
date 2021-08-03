#include "G4TEPCPhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"

G4TEPCPhysicsList::G4TEPCPhysicsList() : G4VModularPhysicsList()
{
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  RegisterPhysics(new G4EmLivermorePhysics());
  // check this
  RegisterPhysics(new G4HadronPhysicsFTFP_BERT());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4TEPCPhysicsList::~G4TEPCPhysicsList(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4TEPCPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();

  return ;
}
