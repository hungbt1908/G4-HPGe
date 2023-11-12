#include "RunAction.hh"
#include "RunActionMessenger.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
{
    fRunActionMessenger = new RunActionMessenger(this);

    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);

    // Create analysis manager
    // The choice of the output format is done via the specified
    // file extension.
    auto analysisManager = G4AnalysisManager::Instance();

    // Create directories
    //analysisManager->SetHistoDirectoryName("histograms");
    //analysisManager->SetNtupleDirectoryName("ntuple");
    //analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);
      // Note: merging ntuples is available only with Root output

    // Creating histograms
    analysisManager->CreateH1("H1", "Edep in absorber, Energy[MeV]", 2000, 0., 2.0*MeV);

    // Creating ntuple
    //
    analysisManager->CreateNtuple("HPGe", "Edep");
    analysisManager->CreateNtupleDColumn("fEdep");
    analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{
  delete fRunActionMessenger;
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  if(fFileName.size()) // or whatever check is necessesary :)
    analysisManager->OpenFile(fFileName);
  else
    analysisManager->OpenFile("defaultFilename.root");

  // G4cout << "Using " << analysisManager->GetType() << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

void RunAction::SetFilename(G4String fileName) 
{
  fFileName = G4String(fileName);
}