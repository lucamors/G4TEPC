#ifndef G4TEPC_PHYSICS_LIST
#define G4TEPC_PHYSICS_LIST 1

#include "G4VModularPhysicsList.hh"


class G4TEPCPhysicsList : public G4VModularPhysicsList
{
  public:

    G4TEPCPhysicsList();
    virtual ~G4TEPCPhysicsList();
    virtual void SetCuts();

};

#endif
