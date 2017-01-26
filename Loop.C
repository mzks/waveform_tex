// Loop.C -- root macro
// Author : Mizukoshi Keita
// 2017 Jan. 26

void Loop(){

	const Double_t THRESHOLD = -1.0e-3; //Volt


	//Init
	TString header = "./data/coin_";
	TString footer = "_ch1.root";
	stringstream ss;
	Int_t fileNumber=0;
	ss << header << fileNumber << footer;

	TH1D* histCharge = new TH1D("charge","charge",1000,-0.2e-9,0.1e-9);

	// Loop
	while(TFile* f1 = TFile::Open(ss.str().c_str())){
		TGraph* g1 = dynamic_cast<TGraph*>(f1->Get("graph"));

		Double_t* x = g1->GetX();
		Double_t* y = g1->GetY();


		//define baseline
		Double_t baseline;
		for(int i=0;i<1000;++i){
			baseline += y[i];
		}
		baseline /= 1000.0;
		
		Double_t integral = 0;
		for(int i=0;i<10000;++i){
			if((y[i]-baseline)<THRESHOLD) integral += y[i]-baseline;
		}

		histCharge->Fill(integral *= (4.0e-10/50.0) ); //50.0 Ohm

		// prepare for next loop
		ss.str("");
		ss.clear(stringstream::goodbit);
		++fileNumber;
		ss << header << fileNumber << footer;
	}
	histCharge->SetTitle("Charge;C;count");
	histCharge->Draw();

}
