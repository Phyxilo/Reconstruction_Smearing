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

void OTCount()
{
  char MCName[64];

  sprintf(MCName, "PD04_p036.root");
  TFile *monteCarlo = TFile::Open(MCName);

  TTree *MCTree = (TTree*)monteCarlo->Get("TRK");

  TLeaf *MCeID = MCTree->GetLeaf("vID");
  TLeaf *MCTX = MCTree->GetLeaf("tx");
  TLeaf *MCTY = MCTree->GetLeaf("ty");

  int currentDataEID = 0;
  int minTX, minTY = 100;

  Float_t refTrTX, refTrTY, refTrT2, secTrTX, secTrTY;
  Float_t dTrTX; Float_t dTrTY;

  int refIDEvent = 0, refFlag = 0, refParID = 0, currentEID = 0;

  for (int i = 0; i < MCTree->GetEntriesFast(); i++)
  {
    MCTree->GetEntry(i);
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
    if(i%1 == 0) {cout << i << "/" << eSize << endl; cout << "TX min: " << minTX << ", TY min: " << minTY << endl;}

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
          MCTree->GetEntry(index);

          refTrTX = MCTX->GetValue(); refTrTY = MCTY->GetValue(); /*refTrT2 = MCT2->GetValue();*/
          refIDEvent = MCeID->GetValue(); /*refParID = MCParID->GetValue(); refFlag = MCFlag->GetValue();*/

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
                MCTree->GetEntry(secIndex);

                //cout << "Secondary: " << "Event: " << eIDListFull[secIndex] << ", Track Num: " << secIndex << endl;

                secTrTX = MCTX->GetValue();
                secTrTY = MCTY->GetValue();

                dTrTX = refTrTX - secTrTX;
                dTrTY = refTrTY - secTrTY;

                if (index != secIndex &&)
                {
                  if (minTX > dTrTX){minTX = dTrTX;}
                  if (minTY > dTrTY){minTY = dTrTY;}
                }

              }
            }
          }
        }
      }
    }
  }
  monteCarlo->Close();

}
