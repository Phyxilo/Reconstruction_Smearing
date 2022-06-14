#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

using namespace std;

vector<int> eIDList;
vector<int> eIDListFull;

void MultipVTX()
{
  TFile *monteCarlo = TFile::Open("/home/phyxilo/root/macros/Smearing/Vertexing/ImpactParameter/vertexingIPCutAppliedData_10.root");

  float tX, tY, t2;
  int mlt;

  TTree *MCTree = (TTree*)monteCarlo->Get("TRK");
  TLeaf *MCeID = MCTree->GetLeaf("VertexID");

  TFile outFile("vertexingMultipData.root","recreate");
  TTree *TrkTree = new TTree("TRK","Track");
  TTree *VtxTree = new TTree("VTX","Vertex");
  TBranch *mltBr = VtxTree->Branch("Multip", &mlt, "Multip/I");

  TrkTree = MCTree->CloneTree();
  TrkTree->Write();

  int currentEID = 0;
  int multNum = 0;
  int eSize = MCTree->GetEntriesFast();
  
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
  }
  cout << "Full: " << eIDListFull.size() << ", Reduced: " << eIDList.size() << endl;
  int eIDSize = eIDList.size();
  
  for (int i = 0; i < eIDSize; i++)
  {
    multNum = count(eIDListFull.begin(), eIDListFull.end(), eIDList[i]);
    VtxTree->GetEntry(i);

    mlt = multNum-1;
    VtxTree->Fill();
    
    if (i%100 == 0) cout << "Event: " << i << "/" << eIDSize << endl;
    
    multNum = 0;
  }
  
  VtxTree->Write();

  outFile.Close();
  monteCarlo->Close();
}