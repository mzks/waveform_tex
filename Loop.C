// Loop.C -- root macro
// Author : Mizukoshi Keita
// 2017 Jan. 26

void Loop(){
	//Init
	TString header = "./data/aho2_";
	TString footer = "_ch1.root";
	stringstream ss;
	Int_t fileNumber=0;
	ss << header << fileNumber << footer;

	TH1D* histCharge = new TH1D("charge","charge",10000,-1.0e-3,1.0e-3);

	// Loop
	while(TFile* f1 = TFile::Open(ss.str().c_str())){
		TGraph* g1 = dynamic_cast<TGraph*>(f1->Get("graph"));

		Double_t* x = g1->GetX();
		Double_t* y = g1->GetY();

		Double_t integral = 0;
		for(int i=0;i<10000;++i){
			integral += y[i];
		}
		histCharge->Fill(integral *= 4.0e-10);

		ss.str("");
		ss.clear(stringstream::goodbit);
		++fileNumber;
		ss << header << fileNumber << footer;
	}
	histCharge->Draw();

}
