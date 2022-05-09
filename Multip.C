#include <iostream>
#include <vector>
#include <cmath>
#include <list>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

vector<int> eIDList;
vector<int> eIDListFull;

void Multip()
{
  char dataName[64], MC0Name[64], MC1Name[64];

  //sprintf(MC1Name, "/home/phyxilo/FedraPro/linked_tracks.root");
  //sprintf(MC0Name, "/home/phyxilo/Downloads/pl001_030/linked_tracks.root");
  //sprintf(MC1Name, "/home/phyxilo/Downloads/fedraOut/OutTrack/finalCut.root");
  sprintf(MC1Name, "/home/phyxilo/Downloads/fedraOut/Out/finalCut.root");
  //sprintf(MCName, "/home/phyxilo/Downloads/pl001_030/linked_tracks.root");
  //sprintf(dataName, "/home/phyxilo/Downloads/dataFile/data.root");
  /*
  TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);
  */
  TFile *monteCarlo = TFile::Open(MC1Name);
  //TFile *data = TFile::Open(dataName);

  TFile MCFile("MultCut.root","recreate");

  TTree *SlpTree = new TTree("Slp","Slope");
  TTree *MltTree = new TTree("Mlt","Multiplicity");

  float tX, tY, t2;
  int mlt;

  TBranch *eTXBr = SlpTree->Branch("SlpTX", &tX, "SlpTX/F");
  TBranch *eTYBr = SlpTree->Branch("SlpTY", &tY, "SlpTY/F");
  TBranch *eT2Br = SlpTree->Branch("SlpT2", &t2, "SlpT2/F");
  TBranch *eMult = MltTree->Branch("Mult", &mlt, "Mult/I");

  //TH1F *MCMultHist = new TH1F("MCMultiplicity","Multiplicity Histogram ",80,0,80);
  //TH1F *DataMultHist = new TH1F("DataMultiplicity","Multiplicity Histogram ",80,0,80);
  //TH1F *TXHist = new TH1F("TX","Multiplicity Histogram ",50,-0.5,0.5);

  TTree *MCTree = (TTree*)monteCarlo->Get("tracks");
  //TTree *dataTree = (TTree*)data->Get("VTX");

  TLeaf *MCPlateID = MCTree->GetLeaf("t.ePID");
  TLeaf *MCParentID = MCTree->GetLeaf("t.eMCTrack");
  TLeaf *MCeID = MCTree->GetLeaf("t.eMCEvt");
  TLeaf *MCTX = MCTree->GetLeaf("t.eTX");
  TLeaf *MCTY = MCTree->GetLeaf("t.eTY");

  //TLeaf *DataeID = dataTree->GetLeaf("n_1ry_trk");

  int currentEID = 0;
  int secondEID = 0;
  int multNum = 0;
  int eSize = MCTree->GetEntriesFast();

  int currentDataEID = 0;
  /*
  for (int i = 0; i < dataTree->GetEntriesFast(); i++)
  {
    dataTree->GetEntry(i);

    currentDataEID = DataeID->GetValue();
    //DataMultHist->Fill(currentDataEID);
  }
  */
  for (int i = 0; i < eSize; i++)
  {
    MCTree->GetEntry(i);
    currentEID = MCeID->GetValue();
    eIDListFull.push_back(currentEID);

    if (find(eIDList.begin(), eIDList.end(), currentEID) == eIDList.end())
    {
      eIDList.push_back(currentEID);
    }
    
    if (i%1000 == 0) cout << i << "/" << eSize << endl;
    //cout << eIDListFull.size() << "-" << eIDList.size() << endl;
  }

  int eIDSize = eIDList.size();
  int MCSize = MCTree->GetEntriesFast();
  int index = 0;

  for (int i = 0; i < eIDSize; i++)
  {
    multNum = count(eIDListFull.begin(), eIDListFull.end(), eIDList[i]);
    MCTree->GetEntry(i);

    if (/*multNum > 2 &&*/MCParentID->GetValue() == 1 && MCPlateID->GetValue() >= 1)
    {
      //MCMultHist->Fill(multNum-1);
      mlt = multNum-1; MltTree->Fill();
      
      for (int j = 0; j < multNum; j++)
      {
        auto it = find(eIDListFull.begin() + index + 1, eIDListFull.end(), eIDList[i]);
        if (it != eIDListFull.end())
        {
          index = it - eIDListFull.begin();
          MCTree->GetEntry(index);
          //cout << MCTX->GetValue() << endl;

          tX = MCTX->GetValue();
          tY = MCTY->GetValue();
          t2 = sqrt(tX*tX+tY*tY);
          SlpTree->Fill();

          //TXHist->Fill(MCTX->GetValue());
        }
        
      }
      index = 0;

      /*
      for (int j = 0; j < MCSize; j++)
      {
        MCTree->GetEntry(j);
        
        if (eIDList[i] == MCeID->GetValue()) TXHist->Fill(MCTX->GetValue());
      }
      */
      //TXHist->Fill(MCTX->GetValue());
    }

    cout << "Event: " << i << "/" << eIDSize << endl;

    multNum = 0;
  }
  monteCarlo->Close();

  SlpTree->Write();
  MltTree->Write();

  MCFile.Close();

  /*
  MCMultHist->Scale(DataMultHist->Integral()/MCMultHist->Integral());

  MCMultHist->GetYaxis()->SetRangeUser(0, 4500);
  MCMultHist->Draw("HIST");
  DataMultHist->Draw("SAME");
  DataMultHist->SetLineColor(kRed);

  auto legendTX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTX->SetHeader("Histogram Legend","C");
  legendTX->AddEntry(DataMultHist,"Data","f");
  legendTX->AddEntry(MCMultHist,"MonteCarlo","f");
  legendTX->Draw();
  
  Canvas->Print ("multHist.pdf", "pdf");

  TXHist->Draw();
  Canvas->Print ("TX.pdf", "pdf");
  */
}