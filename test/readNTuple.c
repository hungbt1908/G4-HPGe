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

    for(int i=0; i<entries; ++i)
    {
        tree->GetEntry(i);

        //cout << eSum << endl;
        eDepHist->Fill(eDep);
    }

    // Draw
    TCanvas* c1 = new TCanvas("c1", " ", 20, 20, 800, 1000);

	// gPad->SetLogy(1);
	eDepHist->SetTitle("HPGe Spectrum ");
	eDepHist->GetXaxis()->CenterTitle(true);
	eDepHist->GetYaxis()->CenterTitle(true);
	eDepHist->GetXaxis()->SetTitle("MeV");
	eDepHist->GetYaxis()->SetTitle("Counts");
	eDepHist->Draw("HIST");

}