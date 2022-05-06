#define DecayTree_cxx
#include "DecayTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void DecayTree::Loop()
{
//   In a ROOT session, you can do:
//      root> .L DecayTree.C
//      root> DecayTree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   TH1F *eTXHist = new TH1F("eTXDataHist","Slope X Histogram ",50,-0.5,0.5);
   TH1F *eTYHist = new TH1F("eTXDataHist","Slope X Histogram ",50,-0.5,0.5);
   TH1F *eT2Hist = new TH1F("eT2MCHist","Space Angle Histogram ",50,0,1);

   float tX, tY, t2;

   TFile MCFile("trueMC.root","recreate");

   TTree *SlpTree = new TTree("Slp","Slope");

   TBranch *eTXBr = SlpTree->Branch("SlpTX", &tX, "SlpTX/F");
   TBranch *eTYBr = SlpTree->Branch("SlpTY", &tY, "SlpTY/F");
   TBranch *eT2Br = SlpTree->Branch("SlpT2", &t2, "SlpT2/F");

   float eTX, eTY, eT2;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      cout << jentry << "/" << nentries << endl;

      eTX = IntInfo[0]/IntInfo[2];
      eTY = IntInfo[1]/IntInfo[2];
      eT2 = sqrt(eTX*eTX+eTY*eTY);

      if (eTX < 0.4 && eTX > -0.4) {eTXHist->Fill(eTX); tX = eTX; SlpTree->Fill();}

      if (eTY < 0.4 && eTY > -0.4) {eTYHist->Fill(eTY); tY = eTY; SlpTree->Fill();}
      
      if ((eTX < 0.4 && eTX > -0.4) && (eTY < 0.4 && eTY > -0.4)) {eT2Hist->Fill(eT2); t2 = eT2; SlpTree->Fill();}

   }
   SlpTree->Write();

   //eT2Hist->Draw();

   MCFile.Close();
}
