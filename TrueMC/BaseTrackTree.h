//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May  6 18:31:36 2022 by ROOT version 6.22/02
// from TTree BaseTrackTree/basetrack info
// found on file: hadronsg4_r86_FTFP_BERT_8.root
//////////////////////////////////////////////////////////

#ifndef BaseTrackTree_h
#define BaseTrackTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class BaseTrackTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           event;
   Int_t           nhits;
   Int_t           plate[14507];   //[nhits]
   Int_t           trkid[14507];   //[nhits]
   Int_t           flkid[14507];   //[nhits]
   Int_t           parent[14507];   //[nhits]
   Double_t        posX[14507];   //[nhits]
   Double_t        posY[14507];   //[nhits]
   Double_t        posZ[14507];   //[nhits]
   Double_t        thX[14507];   //[nhits]
   Double_t        thY[14507];   //[nhits]
   Double_t        Mom[14507];   //[nhits]
   Int_t           vtxid[14507];   //[nhits]
   Int_t           vtxid2nd[14507];   //[nhits]
   Int_t           RunNumber;
   Double_t        Ene[14507];   //[nhits]
   Double_t        dZ[14507][2];   //[nhits]
   Int_t           ICode[14507];   //[nhits]

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_nhits;   //!
   TBranch        *b_plate;   //!
   TBranch        *b_trkid;   //!
   TBranch        *b_flkid;   //!
   TBranch        *b_parent;   //!
   TBranch        *b_posX;   //!
   TBranch        *b_posY;   //!
   TBranch        *b_posZ;   //!
   TBranch        *b_thX;   //!
   TBranch        *b_thY;   //!
   TBranch        *b_Mom;   //!
   TBranch        *b_vtxid;   //!
   TBranch        *b_vtxid2nd;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_Ene;   //!
   TBranch        *b_dZ;   //!
   TBranch        *b_ICode;   //!

   BaseTrackTree(TTree *tree=0);
   virtual ~BaseTrackTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef BaseTrackTree_cxx
BaseTrackTree::BaseTrackTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("hadronsg4_r86_FTFP_BERT_8.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("hadronsg4_r86_FTFP_BERT_8.root");
      }
      f->GetObject("BaseTrackTree",tree);

   }
   Init(tree);
}

BaseTrackTree::~BaseTrackTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t BaseTrackTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t BaseTrackTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void BaseTrackTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nhits", &nhits, &b_nhits);
   fChain->SetBranchAddress("plate", plate, &b_plate);
   fChain->SetBranchAddress("trkid", trkid, &b_trkid);
   fChain->SetBranchAddress("flkid", flkid, &b_flkid);
   fChain->SetBranchAddress("parent", parent, &b_parent);
   fChain->SetBranchAddress("posX", posX, &b_posX);
   fChain->SetBranchAddress("posY", posY, &b_posY);
   fChain->SetBranchAddress("posZ", posZ, &b_posZ);
   fChain->SetBranchAddress("thX", thX, &b_thX);
   fChain->SetBranchAddress("thY", thY, &b_thY);
   fChain->SetBranchAddress("Mom", Mom, &b_Mom);
   fChain->SetBranchAddress("vtxid", vtxid, &b_vtxid);
   fChain->SetBranchAddress("vtxid2nd", vtxid2nd, &b_vtxid2nd);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("Ene", Ene, &b_Ene);
   fChain->SetBranchAddress("dZ", dZ, &b_dZ);
   fChain->SetBranchAddress("ICode", ICode, &b_ICode);
   Notify();
}

Bool_t BaseTrackTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void BaseTrackTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t BaseTrackTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef BaseTrackTree_cxx
