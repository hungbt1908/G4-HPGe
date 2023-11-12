Double_t fun_unfold_gause(Double_t energy)
{
        Double_t par[3];
        Double_t ene_tmp=energy*1000.0 ;
        
        par[0] = 0.54; par[1] = 0.022; par[2] = 0.00158;
        return 0.001*(ene_tmp + fun_FWHM(&ene_tmp, par) * gRandom->Gaus()/2.355);
} 

Double_t fun_FWHM( Double_t *energy,Double_t *par)
{
	Double_t x0 = energy[0];
    return (par[0]+par[1]*TMath::Sqrt(x0 +par[2]* x0 * x0));
}

void readNTuple()
{
    gROOT->Reset();
	gROOT->SetStyle("Plain");

	TFile* f = new TFile("defaultFilename.root", "READ");

	// list all Tree and Historgram
	f->ls();

    TTree* tree = (TTree*)f->Get("HPGe;1");

    tree->Print();

    double eDep;
    tree->SetBranchAddress("fEdep", &eDep);

    int entries;
    entries = tree->GetEntries();
    cout << "Number of entries: " << entries << endl;

    TH1D* eDepHist = new TH1D("HPGe Histogram", "Deposition Energies", 200, 0., 2.);
    TH1D* eDepFittedHist = new TH1D("HPGe Histogram", "Deposition Energies", 200, 0., 2.);

    double Ei;
    double sigma;

    for(int i=0; i<entries; ++i)
    {
        tree->GetEntry(i);

        Ei = (eDep + gRandom->Rndm());
        sigma = (0.5/100)*Ei; // 0.5%

        eDepHist->Fill(eDep);
        eDepFittedHist->Fill(gRandom->Gaus(Ei,sigma));
    }

    // Draw
    TCanvas* c1 = new TCanvas("c1", " ", 20, 20, 800, 1000);
    c1->Divide(1, 2);

    // Draw pad 1
	c1->cd(1);
	// gPad->SetLogy(1);
	eDepHist->SetTitle("HPGe Spectrum ");
	eDepHist->GetXaxis()->CenterTitle(true);
	eDepHist->GetYaxis()->CenterTitle(true);
	eDepHist->GetXaxis()->SetTitle("MeV");
	eDepHist->GetYaxis()->SetTitle("Counts");
	eDepHist->Draw("HIST");

    // Draw pad 2
	c1->cd(2);
    eDepFittedHist->SetTitle("HPGe Fitted Spectrum");
	eDepFittedHist->GetXaxis()->CenterTitle(true);
	eDepFittedHist->GetYaxis()->CenterTitle(true);
	eDepFittedHist->GetXaxis()->SetTitle("MeV");
	eDepFittedHist->GetYaxis()->SetTitle("Counts");
	eDepFittedHist->Draw("HIST");

}