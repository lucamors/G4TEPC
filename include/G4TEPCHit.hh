#ifndef G4TEPC_HIT_H
#define G4TEPC_HIT_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class G4TEPCHit : public G4VHit
{
  public:

    // Constructors
    G4TEPCHit();
    G4TEPCHit(const G4TEPCHit&);
    // Destructor
    ~G4TEPCHit();

    // Operators
    const G4TEPCHit& operator=(const G4TEPCHit&);
    G4int operator==(const G4TEPCHit&) const;

    inline void * operator new(size_t);
    inline void   operator delete(void*);

    // User Defined Hit Interface

  private:


};

using G4TEPCHitsCollection = G4THitsCollection<G4TEPCHit>;
extern G4ThreadLocal G4Allocator<G4TEPCHit>* G4TEPCHitAllocator;

inline void* G4TEPCHit::operator new(size_t)
{
  if(!G4TEPCHitAllocator) G4TEPCHitAllocator = new G4Allocator<G4TEPCHit>;

  void * hit;
  hit = (void*) G4TEPCHitAllocator->MallocSingle();

  return hit;
}

inline void G4TEPCHit::operator delete(void *hit)
{
  if(!G4TEPCHitAllocator) G4TEPCHitAllocator = new G4Allocator<G4TEPCHit>;

  G4TEPCHitAllocator->FreeSingle((G4TEPCHit*)hit);

  return ;
}

#endif
