#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

using namespace std;

vector<int> trIDList;
vector<int> trIDListFull;

void TrackRejection()
{
  //TFile *monteCarlo = TFile::Open("/home/phyxilo/Downloads/dataFile/PD04.root");
  TFile *monteCarlo = TFile::Open("/home/phyxilo/root/macros/Smearing/Vertexing/ImpactParameter/vertexingIPCutApplied_10.root");
  TTree *MCTree = (TTree*)monteCarlo->Get("TRK");
  /*
  TLeaf *trId = MCTree->GetLeaf("trk_id");
  TLeaf *MCTX = MCTree->GetLeaf("tx");
  TLeaf *MCTY = MCTree->GetLeaf("ty");
  TLeaf *vtxId = MCTree->GetLeaf("vID");
  */

  TLeaf *MCTX = MCTree->GetLeaf("SlpTX");
  TLeaf *MCTY = MCTree->GetLeaf("SlpTY");
  TLeaf *MCT2 = MCTree->GetLeaf("SlpT2");
  TLeaf *trId = MCTree->GetLeaf("TrackID");
  TLeaf *vtxId = MCTree->GetLeaf("VertexID");
  TLeaf *imPar = MCTree->GetLeaf("ImpactPar");

  TFile MCFile("vertexingTrReducedMC_10.root","recreate");

  TTree *TrkTree = new TTree("TRK","Track");

  float tX, tY, t2, ip;
  int tId, vId;

  TBranch *eTXBr = TrkTree->Branch("SlpTX", &tX, "SlpTX/F");
  TBranch *eTYBr = TrkTree->Branch("SlpTY", &tY, "SlpTY/F");
  TBranch *eT2Br = TrkTree->Branch("SlpT2", &t2, "SlpT2/F");
  TBranch *vtxIDBr = TrkTree->Branch("VertexID", &vId, "VertexID/I");
  TBranch *eIDBr = TrkTree->Branch("TrackID", &tId, "TrackID/I");
  TBranch *eIpBr = TrkTree->Branch("ImpacPar", &ip, "ImpactPar/F");

  //int mlt;
  //TBranch *eIDBr = VtxTree->Branch("Muliplicity", &mlt, "Muliplicity/I");

  //MCTree->SetAutoFlush(100);
  //TrkTree->SetAutoFlush(100);

  int currentTrID = 0;
  int eSize = MCTree->GetEntriesFast();
  
  for (int i = 0; i < eSize; i++)
  {
    MCTree->GetEntry(i);
    currentTrID = trId->GetValue();
    trIDListFull.push_back(currentTrID);
    
    if (find(trIDList.begin(), trIDList.end(), currentTrID) == trIDList.end())
    {
      trIDList.push_back(currentTrID);
      tId = currentTrID;
      vId = vtxId->GetValue();
       
      tX = MCTX->GetValue();
      tY = MCTY->GetValue();
      //t2 = MCT2->GetValue();
      t2 = sqrt(tX*tX+tY*tY);
      ip = imPar->GetValue();

      //TrkTree = MCTree->CloneTree(i);

      TrkTree->Fill();
    }
    
    if (i%1000 == 0) 
    {
      cout << i << "/" << eSize << endl; 
      //TrkTree->AutoSave(); TrkTree->FlushBaskets();
      //MCTree->FlushBaskets();
      //TrkTree->AutoSave(); TrkTree->Write(); free(TrkTree);
    }
    
  }
  monteCarlo->Close();

  cout << "Full Size: " << trIDListFull.size() << ", Reduced Size: " << trIDList.size() << endl;
  
  TrkTree->Write();
  MCFile.Close();
}