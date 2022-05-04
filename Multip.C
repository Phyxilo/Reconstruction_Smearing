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

  //sprintf(MCName, "/home/phyxilo/FedraPro/linked_tracks.root");
  sprintf(MC0Name, "/home/phyxilo/Downloads/pl001_030/linked_tracks.root");
  sprintf(MC1Name, "/home/phyxilo/Downloads/fedraOut/Out/finalCut.root");
  //sprintf(MCName, "/home/phyxilo/Downloads/pl001_030/linked_tracks.root");
  sprintf(dataName, "/home/phyxilo/Downloads/dataFile/data.root");

  TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  TFile *monteCarlo = TFile::Open(MC1Name);
  TFile *data = TFile::Open(dataName);

  TH1F *MCMultHist = new TH1F("MCMultiplicity","Multiplicity Histogram ",80,0,80);
  TH1F *DataMultHist = new TH1F("DataMultiplicity","Multiplicity Histogram ",80,0,80);

  TTree *MCTree = (TTree*)monteCarlo->Get("tracks");
  TTree *dataTree = (TTree*)data->Get("VTX");

  TLeaf *MCPlateID = MCTree->GetLeaf("t.ePID");
  TLeaf *MCMult = MCTree->GetLeaf("t.eMCTrack");
  TLeaf *MCeID = MCTree->GetLeaf("t.eMCEvt");

  TLeaf *DataeID = dataTree->GetLeaf("n_1ry_trk");

  int currentEID = 0;
  int secondEID = 0;
  int multNum = 0;
  int eSize = MCTree->GetEntriesFast();

  int currentDataEID = 0;

  for (int i = 0; i < dataTree->GetEntriesFast(); i++)
  {
    dataTree->GetEntry(i);

    currentDataEID = DataeID->GetValue();
    DataMultHist->Fill(currentDataEID);
  }

  for (int i = 0; i < eSize; i++)
  {
    MCTree->GetEntry(i);
    currentEID = MCeID->GetValue();
    eIDListFull.push_back(currentEID);

    if (MCPlateID->GetValue() >= 1 && find(eIDList.begin(), eIDList.end(), currentEID) == eIDList.end())
    {
      //MCMultHist->Fill(MCMult->GetValue());
      /*
      for (int j = 0; j < eSize; j++)
      {
        MCTree->GetEntry(j);
        secondEID = MCeID->GetValue();

        if (currentEID == secondEID) { multNum++; }
      }
      */
      //cout << "EventID: " << currentEID << endl;

      //cout << "EventID: " << currentEID << " = " << multNum << endl;
      //MCMultHist->Fill(multNum);
      //multNum = -1;
      eIDList.push_back(currentEID);
    }
    
    //cout << eIDListFull.size() << "-" << eIDList.size() << endl;
  }

  int eIDSize = eIDList.size();
  for (int i = 0; i < eIDSize; i++)
  {
    multNum = count(eIDListFull.begin(), eIDListFull.end(), eIDList[i]);

    if (multNum > 1)
    {
      MCMultHist->Fill(multNum-1);
      cout << "Event: " << i << "/" << eIDSize << endl;
    }

    multNum = 0;
  }

  MCMultHist->Scale(DataMultHist->Integral()/MCMultHist->Integral());

  MCMultHist->Draw("HIST");
  DataMultHist->Draw("SAME");
  DataMultHist->SetLineColor(kRed);

  auto legendTX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTX->SetHeader("Histogram Legend","C");
  legendTX->AddEntry(DataMultHist,"Data","f");
  legendTX->AddEntry(MCMultHist,"MonteCarlo","f");
  legendTX->Draw();
  
  Canvas->Print ("multHist.pdf", "pdf");
}