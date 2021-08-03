#include "G4TEPCHit.hh"

G4ThreadLocal G4Allocator<G4TEPCHit>* G4TEPCHitAllocator = 0;

G4TEPCHit::G4TEPCHit() : G4VHit()
{
  fEdep = 0.0;
}

G4TEPCHit::~G4TEPCHit(){}

G4TEPCHit::G4TEPCHit(const G4TEPCHit& right) : G4VHit()
{
	fEdep = right.fEdep;
}

const G4TEPCHit& G4TEPCHit::operator=(const G4TEPCHit& right)
{
	fEdep = right.fEdep;
	return *this;
}

G4int G4TEPCHit::operator==(const G4TEPCHit& right) const
{
	return (this == &right ) ? 1 : 0;
}
