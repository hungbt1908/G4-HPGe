#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class RunActionMessenger;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction();

    void BeginOfRunAction(const G4Run*) override;
    void   EndOfRunAction(const G4Run*) override;

    void SetFilename(G4String fileName);

  private:
    G4String fFileName;

    RunActionMessenger* fRunActionMessenger;
};

#endif

