#ifndef G4TEPC_EVENT_ACTION_H
#define G4TEPC_EVENT_ACTION_H 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "G4TEPCHit.hh"

class G4TEPCEventAction : public G4UserEventAction
{
  public:

    G4TEPCEventAction();
    virtual ~G4TEPCEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

  private:

    G4TEPCHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;
    G4int fHCID;

};

#endif
