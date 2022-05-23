#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

vector<int> eIDList;
vector<int> eIDListFull;
vector<int> discardedTracks;

double dTLimit = 0.01;

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

  int refIDEvent = 0, refFlag = 0, refParID = 0, currentEID = 0;

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

    multNum = count(eIDListFull.begin(), eIDListFull.end(), eIDList[i]); /*cout << "Mult: " << multNum << endl;*/

    index = 0;
    for(int j = 0; j < multNum; j++)
    {
      auto it = find(eIDListFull.begin() + index + 1, eIDListFull.end(), eIDList[i]);
      if (it != eIDListFull.end())
      {
        index = it - eIDListFull.begin(); //cout << "Index: " << index << endl;
        if (find(discardedTracks.begin(), discardedTracks.end(), index) == discardedTracks.end())
        {
          TrueMCTree->GetEntry(index);

          refTrTX = MCTX->GetValue(); refTrTY = MCTY->GetValue(); refTrT2 = MCT2->GetValue();
          refIDEvent = MCeID->GetValue(); refParID = MCParID->GetValue(); refFlag = MCFlag->GetValue();

          //cout << "Primary: " << "Event: " << eIDListFull[index] << ", Track Num: " << index << endl;

          secIndex = 0;
          for(int k = 0; k < multNum; k++)
          {
            auto secIt = find(eIDListFull.begin() + secIndex + 1, eIDListFull.end(), eIDList[i]);
            if(secIt != eIDListFull.end())
            {
              secIndex = secIt - eIDListFull.begin();
              if (find(discardedTracks.begin(), discardedTracks.end(), secIndex) == discardedTracks.end())
              {
                TrueMCTree->GetEntry(secIndex);

                //cout << "Secondary: " << "Event: " << eIDListFull[secIndex] << ", Track Num: " << secIndex << endl;

                secTrTX = MCTX->GetValue();
                secTrTY = MCTY->GetValue();

                dTrTX = refTrTX - secTrTX;
                dTrTY = refTrTY - secTrTY;

                if (index != secIndex && (dTrTX < dTLimit && dTrTX > -dTLimit && dTrTY < dTLimit && dTrTY > -dTLimit))
                {
                  discardedTracks.push_back(secIndex);
                }
              }
            }
          }

          if (refFlag == 222 /*refParID == 1*/)
          {
            tX = refTrTX; tY = refTrTY; t2 = refTrT2;
            ev = refIDEvent; prID = refParID;
            TrkTree->Fill();
          }
        }
      }
    }
  }
  monteCarloTrue->Close();
  TrkTree->Write();
  MCFile.Close();

}
