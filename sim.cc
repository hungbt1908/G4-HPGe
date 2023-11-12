#include <iostream>
#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4ParallelWorldPhysics.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

#include "G4ScoringManager.hh"

int main(int argc, char** argv)
{	
	// Choose the Random engine
	G4int seed =  time(NULL);
	G4Random::setTheSeed(seed);

	//construct the default run manager
	G4MTRunManager* runManager = new G4MTRunManager;
	G4int nThreads = G4Threading::G4GetNumberOfCores();
	runManager->SetNumberOfThreads(nThreads-1);

	// Activate UI-command base scorer
	G4ScoringManager* scManager = G4ScoringManager::GetScoringManager();
	scManager->SetVerboseLevel(1);

	auto detConstruction = new DetectorConstruction();
	runManager->SetUserInitialization(detConstruction);

	auto physicsList = new PhysicsList();
	runManager->SetUserInitialization(physicsList);

	auto actionInitialization = new ActionInitialization();
	runManager->SetUserInitialization(actionInitialization);
	//runManager->Initialize();
		
	
	// Detect interactive mode (if no macro provided) and define UI session
	//
	G4UIExecutive* ui = 0;

	// Process macro or start UI session
	//
	if (argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}

	// Initialize visualization
	//
	G4VisManager* visManager = new G4VisExecutive();
	visManager->Initialize();

	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();


	//
	//
	if (ui)
	{
		// interactive mode : define UI session
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	else
	{
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}
	delete visManager;
	delete runManager;

	return 0;
}
