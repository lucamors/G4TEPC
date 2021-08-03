#include "G4TEPCRunAction.hh"
#include "Analysis.hh"
#include "G4Run.hh"

G4TEPCRunAction::G4TEPCRunAction() : G4UserRunAction()
{
  //

  fAnalysisManager = G4AnalysisManager::Instance();

  fAnalysisManager->SetVerboseLevel(1);

  fAnalysisManager->CreateNtuple("ht","TEPC Simulation");
  fAnalysisManager->CreateNtupleDColumn("edep");
  fAnalysisManager->FinishNtuple();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4TEPCRunAction::~G4TEPCRunAction()
{
  delete fAnalysisManager;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4TEPCRunAction::BeginOfRunAction(const G4Run * run)
{
  fAnalysisManager->OpenFile();
  return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4TEPCRunAction::EndOfRunAction(const G4Run * run)
{

  fAnalysisManager->Write();
  fAnalysisManager->CloseFile();
  return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
