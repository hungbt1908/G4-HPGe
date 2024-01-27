Double_t fun_FWHM(Double_t* energy, Double_t* par)
{
	Double_t e = energy[0];
    	return (par[0] + par[1]*TMath::Sqrt(e + par[2]*e*e)); // in keV
}

Double_t fun_gauss(Double_t energy)
{
	Double_t ene_tmp = energy*1000.0; // convert to keV
	Double_t a, b, c;
	a = 1.56762; // for keV
	b = 0.0154; // for keV
	c = 0.000337181; // for keV
	
	Double_t par[3];
	par[0] = a;
	par[1] = b;
	par[2] = c;
	
	return 0.001*(ene_tmp + fun_FWHM(&ene_tmp, par)*gRandom->Gaus()/2.355); // in MeV
}

Double_t addGauss(Double_t energy)
{	
	Double_t ene_tmp = energy; // convert to keV

	Double_t r1, r2, x1, x2, edepstdgaus;
	r1 = r2 = 0.;
	x1 = x2 = 0.;
	edepstdgaus = 0.;

	TRandom2* rand = new TRandom2(0);
	r1 = rand->Rndm();
	r2 = rand->Rndm();

	//cout << "Initialize r1 value = " << r1 << "; r2 = " << r2 << endl;

	x1 = TMath::Sqrt(-2.*TMath::Log(r1));
	x2 = TMath::Sin(2.*TMath::Pi()*r2);
	edepstdgaus = x1 * x2;

	Double_t a, b, c;
	a = 0.000727;
	b = 0.0006587;
	c = 0.7411766;

	Double_t deltaedep, edepresolution;
	deltaedep = 0.; edepresolution = 0.;
	deltaedep = ((a + b*TMath::Sqrt(ene_tmp + c*ene_tmp*ene_tmp))/2.35482)*edepstdgaus;
	edepresolution = ene_tmp + deltaedep;

	return edepresolution;
}

void plotReso()
{
	gROOT->Reset();
	gROOT->SetStyle("Plain");
	
	// read root file
	TFile* f = new TFile("defaultFilename.root", "READ");
	f->ls(); // list all Tree and Historgram
	
	double eDep; // in MeV
	
	// create a new tree
	TTree* tree = (TTree*)f->Get("HPGe;1");
	tree->Print(); // print all branches
	tree->SetBranchAddress("fEdep", &eDep); // set branch "fEdep" as a object to read
	int entries = tree->GetEntries(); // get entries
	cout << "Number of entries: " << entries << endl;
	
	// create a new fited histogram
	TH1D* eDepHist = new TH1D("Original Histogram", "Deposition Energies", 2000, 0., 2);
	TH1D* correctedHist = new TH1D("Corrected Histogram", "Deposition Energies", 2000, 0., 2);
	
	// read ntuples from the root file to above histogram
	for(int i=0; i<entries; ++i)
    {
        tree->GetEntry(i);

        //cout << eSum << endl;
	eDepHist->Fill(eDep);
        //correctedHist->Fill(fun_gauss(eDep));
	correctedHist->Fill(addGauss(eDep));
    }
	
	// create a canvas to plot graph
	//
	Double_t w = 1920;
   	Double_t h = 1080;
	// canvas 1
        TCanvas* c1 = new TCanvas("c1", "c1", w, h);
   	c1->SetWindowSize(w + (w - c1->GetWw()), h + (h - c1->GetWh()));
	// cavans 2
	TCanvas* c2 = new TCanvas("c2", "c2", w, h);
   	c2->SetWindowSize(w + (w - c2->GetWw()), h + (h - c2->GetWh()));

	// plotting
	//
	// canvas 1
	c1->cd();
	// gPad->SetLogy(1);
	eDepHist->SetTitle("HPGe-Original Spectrum ");
	eDepHist->GetXaxis()->CenterTitle(true);
	eDepHist->GetYaxis()->CenterTitle(true);
	eDepHist->GetXaxis()->SetTitle("Energy in MeV");
	eDepHist->GetYaxis()->SetTitle("Counts");
	eDepHist->Draw();
	c1->Print("originSpectrum.pdf)","Title:Total Deposition Energies");

	// canvas 2
	c2->cd();
	correctedHist->SetTitle("HPGe-Corrected Spectrum ");
	correctedHist->GetXaxis()->CenterTitle(true);
	correctedHist->GetYaxis()->CenterTitle(true);
	correctedHist->GetXaxis()->SetTitle("Energy in MeV");
	correctedHist->GetYaxis()->SetTitle("Counts");
	correctedHist->Draw();
	c2->Print("correctedSpectrum.pdf)","Title:Total Deposition Energies");
}