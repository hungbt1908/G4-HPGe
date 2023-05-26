#ifndef MYRUNACTION_HH
#define MYRUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "G4Run.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"

class G4Run;

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    virtual ~MyRunAction();
public:
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif // !MYRUNACTION_HH
