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

vector<int> eParIDList;
vector<int> eParIDCountList;
vector<int> eParIDListFull;

vector<int> eParIDDiscardedList;
vector<int> eParIDDiscardedCountList;
vector<int> eParIDDiscardedListFull;

void Test()
{
  char dataName[64], MCName[64];

  sprintf(MCName, "/home/phyxilo/Downloads/fedraOut/Out/finalCut.root");
  
  TFile *monteCarlo = TFile::Open(MCName);

  TTree *MCTree = (TTree*)monteCarlo->Get("tracks");

  TLeaf *MCPlateID = MCTree->GetLeaf("t.ePID");
  TLeaf *MCParID = MCTree->GetLeaf("t.eMCTrack");
  TLeaf *MCeID = MCTree->GetLeaf("t.eMCEvt");

  int currentEParID = 0;
  int currentEParIDCount = 0;
  int eSize = MCTree->GetEntriesFast();

  int currentDataEID = 0;

  for (int i = 0; i < eSize; i++)
  {
    MCTree->GetEntry(i);
    currentEParID = MCParID->GetValue();

    if (MCPlateID->GetValue() > 0 || MCParID->GetValue() != 1)
    {
      eParIDListFull.push_back(currentEParID);

      if (find(eParIDList.begin(), eParIDList.end(), currentEParID) == eParIDList.end())
      {
        eParIDList.push_back(currentEParID);
      }
    }
    else 
    {
      eParIDDiscardedListFull.push_back(currentEParID);

      if (find(eParIDDiscardedList.begin(), eParIDDiscardedList.end(), currentEParID) == eParIDDiscardedList.end())
      {
        eParIDDiscardedList.push_back(currentEParID);
      }
    }

    if (i%1000 == 0) cout << i << "/" << eSize << endl;
  }

  cout << "\n------------------ Selected Particle FLUKA ID List ------------------" << endl;

  for (int i = 0; i < eParIDList.size(); i++)
  {
    currentEParIDCount = count(eParIDListFull.begin(), eParIDListFull.end(), eParIDList[i]);
    eParIDCountList.push_back(currentEParIDCount);

    cout << "Particle " << i+1 << " = " << eParIDList[i] << ", Particle Count =  " << currentEParIDCount << endl;
  }

  cout << "\n------------------ Discarded Particle FLUKA ID List ------------------" << endl;

  for (int i = 0; i < eParIDDiscardedList.size(); i++)
  {
    currentEParIDCount = count(eParIDDiscardedListFull.begin(), eParIDDiscardedListFull.end(), eParIDDiscardedList[i]);
    eParIDDiscardedCountList.push_back(currentEParIDCount);

    cout << "Particle " << i+1 << " = " << eParIDDiscardedList[i] << ", Particle Count =  " << currentEParIDCount << endl;
  }
}