#include "G4TEPCPhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

G4TEPCPhysicsList::G4TEPCPhysicsList() : G4VModularPhysicsList()
{
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  RegisterPhysics(new G4EmLivermorePhysics());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4TEPCPhysicsList::~G4TEPCPhysicsList(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4TEPCPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();

  return ;
}
