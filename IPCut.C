#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

using namespace std;

vector<int> eIDList;
vector<int> eIDListFull;

void IPCut()
{
  TFile *monteCarlo = TFile::Open("Vertexing/vertexing2022.root");
  TTree *MCTrkTree = (TTree*)monteCarlo->Get("TRK");
  TTree *MCVtxTree = (TTree*)monteCarlo->Get("VTX");
  
  TLeaf *trId = MCTrkTree->GetLeaf("trk_id");
  TLeaf *MCTX = MCTrkTree->GetLeaf("tx");
  TLeaf *MCTY = MCTrkTree->GetLeaf("ty");
  TLeaf *vtxIdTr = MCTrkTree->GetLeaf("vID");
  TLeaf *MCTrkVX = MCTrkTree->GetLeaf("seg_x");
  TLeaf *MCTrkVY = MCTrkTree->GetLeaf("seg_y");
  TLeaf *MCTrkDZ = MCTrkTree->GetLeaf("dz");

  TLeaf *vtxIdVt = MCVtxTree->GetLeaf("vID");
  TLeaf *MCVtxVX = MCVtxTree->GetLeaf("vx");
  TLeaf *MCVtxVY = MCVtxTree->GetLeaf("vy");
  TLeaf *MCVtxVZ = MCVtxTree->GetLeaf("vz");

  TFile MCFile("vertexingIPCutApplied.root","recreate");

  TTree *TrkTree = new TTree("TRK","Track");
  /*
  TLeaf *MCTX = MCTrkTree->GetLeaf("SlpTX");
  TLeaf *MCTY = MCTrkTree->GetLeaf("SlpTY");
  TLeaf *MCT2 = MCTrkTree->GetLeaf("SlpT2");
  TLeaf *trId = MCTrkTree->GetLeaf("TrackID");
  TLeaf *vtxId = MCTrkTree->GetLeaf("VertexID");
  */
  float tX, tY, t2, ip;
  int tId, vId;
  
  TBranch *eTXBr = TrkTree->Branch("SlpTX", &tX, "SlpTX/F");
  TBranch *eTYBr = TrkTree->Branch("SlpTY", &tY, "SlpTY/F");
  TBranch *eT2Br = TrkTree->Branch("SlpT2", &t2, "SlpT2/F");
  TBranch *vtxIDBr = TrkTree->Branch("VertexID", &vId, "VertexID/I");
  TBranch *eIDBr = TrkTree->Branch("TrackID", &tId, "TrackID/I");
  TBranch *IPBr = TrkTree->Branch("ImpactPar", &ip, "ImpactPar/F");
  
  for (int i = 0; i < MCVtxTree->GetEntriesFast(); i++)
  {
    MCVtxTree->GetEntry(i);
    eIDList.push_back(vtxIdVt->GetValue());
  }
  for (int i = 0; i < MCTrkTree->GetEntriesFast(); i++)
  {
    MCTrkTree->GetEntry(i);
    eIDListFull.push_back(vtxIdTr->GetValue());
  }
  
  int eVtxID = 0, mult = 0, index = 0;
  float VtxX, VtxY, VtxZ;
  float dx, dy, dz;

  cout << eIDList.size() << endl;

  int vtxTreeSize = MCVtxTree->GetEntriesFast();

  for (int i = 0; i < vtxTreeSize; i++)
  {
    MCVtxTree->GetEntry(i);
    eVtxID = vtxIdVt->GetValue();
    mult = count(eIDListFull.begin(), eIDListFull.end(), eVtxID);

    VtxX = MCVtxVX->GetValue(); VtxY = MCVtxVY->GetValue(); VtxZ = MCVtxVZ->GetValue();

    //cout << "VertexEventID: " << eVtxID << ", Multiplicity: " << mult << endl;
    
    for (int j = 0; j < mult; j++)
    {
      auto it = find(eIDListFull.begin() + index + 1, eIDListFull.end(), eVtxID);
      if (it != eIDListFull.end())
      {
        index = it - eIDListFull.begin();
        MCTrkTree->GetEntry(index);

        dz = MCTrkDZ->GetValue();
        dx = VtxX - (MCTrkVX->GetValue() + MCTX->GetValue()*dz);
        dy = VtxY - (MCTrkVY->GetValue() + MCTY->GetValue()*dz);

        float Ip = sqrt(dx*dx + dy*dy);

        if (Ip < 500)
        {
          ip = sqrt(dx*dx + dy*dy);
          tX = MCTX->GetValue(); tY = MCTY->GetValue();
          t2 = sqrt(tX*tX + tY*tY);
          tId = trId->GetValue(); vId = vtxIdTr->GetValue();

          TrkTree->Fill();
        }

        //cout << "TrackID: " << trId->GetValue() << endl;
        //cout << dz << endl;
        //cout << sqrt(dx*dx + dy*dy) << endl;
      }
    }

    if(i%1000 == 0) {cout << i << "/" << vtxTreeSize << endl;}
  }
  monteCarlo->Close();
  
  //cout << "Full Size: " << trIDListFull.size() << ", Reduced Size: " << trIDList.size() << endl;
  
  TrkTree->Write();
  MCFile.Close();
}