#ifndef MYDETECTORCONSTRUCTION_HH
#define	MYDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Orb.hh"

#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"

#include "G4MultiUnion.hh"
#include "G4SubtractionSolid.hh"

#include "G4RunManager.hh"
#include "globals.hh"

#include "MyDetectorMessenger.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();

private:
	//virtual void ConstructSDandField();

private:
	// methods
	//
	void DefineMaterials();
	G4VPhysicalVolume* DefineVolumes();

	G4bool check_overlap = true;
	static G4ThreadLocal G4GlobalMagFieldMessenger* fMagFieldMessenger;

public:
	// Solid volume
	G4Box* solidWorld;
	G4Tubs* solid_Endcap_Outer, * solid_Endcap_Inner, * solid_Ge, * solid_Electrode_Hole,
		* solid_Window_Electrode, * solid_Outer_Electrode_P1, * solid_Outer_Electrode_P2,
		* solid_Crystal_Holder_P1, * solid_Crystal_Holder_P2, * solid_Crystal_Holder_P3,
		* solid_Crystal_Holder_P4, * solid_Crystal_Holder_P5, * solid_Crystal_Holder_P6,
		* solid_Crystal_Holder_P7, * solid_Crystal_Holder_P8, * solid_Crystal_Holder_P9,
		* solid_Teflon_Insulator_P1, * solid_Teflon_Insulator_P2, * solid_Signal_Core;

	// Logical volume
	G4LogicalVolume* logicWorld, * logic_Endcap, * logic_Vacuum_Volume, * logic_Ge_Crystal,
		* logic_Window_Electrode, * logic_Outer_Electrode, * logic_Crystal_Holder,
		* logic_Teflon_Insulator, * logic_Signal_Core;

	// Physical volume
	G4VPhysicalVolume* physWorld;

	// Material
	G4Material* Air, * Al, * Ge, * SiO2, * Li, * Cu, * Mylar, * Kapton, * Vacuum;

	G4VisAttributes* Steel_Color, * Vacuum_Color, * Tungsten_Color;

	
	MyDetectorMessenger* detectorMessenger;

public:
	// get methods
	//
	G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

private:
	G4LogicalVolume* fScoringVolume;
};


#endif