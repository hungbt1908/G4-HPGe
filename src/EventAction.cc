#define _USE_MATH_DEFINES

#include "EventAction.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PrimaryParticle.hh"
#include "G4ParticleDefinition.hh"

#include "G4AnalysisManager.hh"

#include "Randomize.hh"
#include <cmath>
#include<math.h>

EventAction::EventAction()
{
	fEdep = 0.;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
	// initialisation per event
	fEdep = 0.;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
	// G4cout << "Energy deposition: " << fEdep << G4endl;

	// get analysis manager
	G4AnalysisManager* man = G4AnalysisManager::Instance();

	G4double newfEdep = AddGaussEnergy(fEdep);

	if (newfEdep > 0)
	{
		fEdep = fEdep/MeV;

		// fill histograms
		man->FillH1(0, newfEdep);

		// fill ntuple
		man->FillNtupleDColumn(0, newfEdep);
		man->AddNtupleRow();
	}
	
}

G4double EventAction::AddGaussEnergy(G4double fEdep)
{
	G4double r1, r2, x1, x2, edepStdGaus;

	r1 = r2 = 0.;
	x1 = x2 = 0.;
	edepStdGaus = 0.;

	r1 = CLHEP::HepUniformRand();
	r2 = CLHEP::HepUniformRand();

	x1 = std::sqrt(-2.*std::log(r1));
	x2 = std::sqrt(2.*M_PI*r2);
	edepStdGaus = x1*x2;

  	// parameters
	G4double a = 1.56762;
	G4double b = 0.0154;
	G4double c = 3.3718E-04; 

	G4double deltaEdep, edepResolution;
	deltaEdep = 0.;
	edepResolution = 0.;

	deltaEdep = ((a + b*sqrt(fEdep + c*fEdep*fEdep))/2.35482)*edepStdGaus;
	edepResolution = fEdep + deltaEdep;

	return edepResolution;
}
