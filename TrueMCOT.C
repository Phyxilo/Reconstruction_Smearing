//g++-5 TrueMCOT.cpp -w `root-config --cflags` -I$FEDRA_ROOT/include -L$FEDRA_ROOT/lib -lEIO -lDataConversion -lEdb -lEbase -lEdr -lScan -lAlignment -lEmath -lEphys -lvt -lDataConversion `root-config --libs` -o MCOT
//./MCOT

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

void TrueMCOT()
{
  char TrueMCName[64];

  sprintf(TrueMCName, "/home/phyxilo/root/macros/Smearing/TrueMC/trueMC.root");
  TFile *monteCarloTrue = TFile::Open(TrueMCName);
  monteCarloTrue = TFile::Open(TrueMCName);

  TTree *TrueMCTree = (TTree*)monteCarloTrue->Get("TRK");

  TFile MCFile("SelectedTrueMC.root","recreate");

  TTree *TrkTree = new TTree("TRK","Track");
  //TTree *MltTree = new TTree("Mlt","Multiplicity");

  float tX, tY, t2, ev, prID;
  int mlt;

  TBranch *eTXBr = TrkTree->Branch("SlpTX", &tX, "SlpTX/F");
  TBranch *eTYBr = TrkTree->Branch("SlpTY", &tY, "SlpTY/F");
  TBranch *eT2Br = TrkTree->Branch("SlpT2", &t2, "SlpT2/F");
  TBranch *event = TrkTree->Branch("Event", &ev, "Event/F");
  TBranch *parID = TrkTree->Branch("ParID", &prID, "ParID/F");
  //TBranch *eMult = MltTree->Branch("Mult", &mlt, "Mult/I");

  //TLeaf *MCPlateID = MCTree->GetLeaf("t.ePID");
  //TLeaf *MCParentID = MCTree->GetLeaf("t.eMCTrack");
  TLeaf *MCeID = TrueMCTree->GetLeaf("Event");
  TLeaf *MCFlag = TrueMCTree->GetLeaf("Flag");
  TLeaf *MCParID = TrueMCTree->GetLeaf("ParID");
  TLeaf *MCTX = TrueMCTree->GetLeaf("SlpTX");
  TLeaf *MCTY = TrueMCTree->GetLeaf("SlpTY");
  TLeaf *MCT2 = TrueMCTree->GetLeaf("SlpT2");

  int currentDataEID = 0;

  Float_t refTrTX, refTrTY, refTrT2, secTrTX, secTrTY;
  Float_t dTrTX; Float_t dTrTY;

  int refIDEvent = 0, refFlag = 0, currentEID = 0;
  vector<int> eIDList;
  vector<int> eIDListFull;
  vector<int> discardedTracks;
  vector<int> selectedTracks;

  for (int i = 0; i < TrueMCTree->GetEntriesFast(); i++)
  {
    TrueMCTree->GetEntry(i);
    currentEID = MCeID->GetValue();
    eIDListFull.push_back(currentEID);

    if (find(eIDList.begin(), eIDList.end(), currentEID) == eIDList.end())
    {
      eIDList.push_back(currentEID);
    }
  }

  int eSize = eIDList.size();
  int index = 0, secIndex = 0, multNum = 0;

  for(int i = 0; i < eSize; i++)
  {
    if(i%10 == 0) {cout << i << "/" << eSize << endl;}

    multNum = count(eIDListFull.begin(), eIDListFull.end(), eIDList[i]);

    index = 0;
    for(int j = 0; j < multNum; j++)
    {
      auto it = find(eIDListFull.begin() + index + 1, eIDListFull.end(), eIDList[i]);
      if (it != eIDListFull.end() && !(find(discardedTracks.begin(), discardedTracks.end(), index) != discardedTracks.end()))
      {
        index = it - eIDListFull.begin();
        TrueMCTree->GetEntry(index);

        refTrTX = MCTX->GetValue(); refTrTY = MCTY->GetValue(); refTrT2 = MCT2->GetValue();
        refIDEvent = MCeID->GetValue();

        secIndex = 0;
        for(int k = 0; k < multNum; k++)
        {
          auto secIt = find(eIDListFull.begin() + secIndex + 1, eIDListFull.end(), eIDList[i]);
          if(secIt != eIDListFull.end() && index != secIndex)
          {
            if (!(find(discardedTracks.begin(), discardedTracks.end(), secIndex) != discardedTracks.end()))
            {
              secIndex = secIt - eIDListFull.begin();
              TrueMCTree->GetEntry(secIndex);

              secTrTX = MCTX->GetValue();
              secTrTY = MCTY->GetValue();
              refFlag = MCFlag->GetValue();

              dTrTX = refTrTX - secTrTX;
              dTrTY = refTrTY - secTrTY;

              if ((dTrTX < 0.02 && dTrTX > -0.02 && dTrTY < 0.02 && dTrTY > -0.02) && refFlag != 222)
              { 
                /*
                if (!(find(discardedTracks.begin(), discardedTracks.end(), secIndex) == discardedTracks.end()))
                {
                  discardedTracks.push_back(secIndex);
                }
                */
                //eIDListFull.erase(next(eIDListFull.begin()));
                discardedTracks.push_back(secIndex);
              }
              //else{eIDListFull.erase(next(eIDListFull.begin()));}
            }
          }
        }

        tX = refTrTX; tY = refTrTY; t2 = refTrT2;
        ev = refIDEvent; prID = MCParID->GetValue();
        TrkTree->Fill();
      }
    }
  }
  monteCarloTrue->Close();
  TrkTree->Write();
  MCFile.Close();
}