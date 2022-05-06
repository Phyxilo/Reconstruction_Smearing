//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May  6 18:31:19 2022 by ROOT version 6.22/02
// from TTree DecayTree/info about all interaction/decay vertexes
// found on file: hadronsg4_r86_FTFP_BERT_8.root
//////////////////////////////////////////////////////////

#ifndef DecayTree_h
#define DecayTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class DecayTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Event;
   Int_t           Flag;
   Int_t           ICode;
   Int_t           ParId;
   Int_t           Region;
   Double_t        IntInfo[5];
   Double_t        IntVtx[3];
   Int_t           Multip;
   Int_t           Tracks[3];
   Int_t           SecondaryId[180];   //[Multip]
   Double_t        SecondaryInfo[180][4];   //[Multip]
   Int_t           VertexId;
   Int_t           RunNumber;

   // List of branches
   TBranch        *b_Event;   //!
   TBranch        *b_Flag;   //!
   TBranch        *b_ICode;   //!
   TBranch        *b_ParId;   //!
   TBranch        *b_Region;   //!
   TBranch        *b_IntInfo;   //!
   TBranch        *b_IntVtx;   //!
   TBranch        *b_Multip;   //!
   TBranch        *b_Tracks;   //!
   TBranch        *b_SecondaryId;   //!
   TBranch        *b_SecondaryInfo;   //!
   TBranch        *b_VertexId;   //!
   TBranch        *b_RunNumber;   //!

   DecayTree(TTree *tree=0);
   virtual ~DecayTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DecayTree_cxx
DecayTree::DecayTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("hadronsg4_r86_FTFP_BERT_8.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("hadronsg4_r86_FTFP_BERT_8.root");
      }
      f->GetObject("DecayTree",tree);

   }
   Init(tree);
}

DecayTree::~DecayTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DecayTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DecayTree::LoadTree(Long64_t entry)
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

void DecayTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("Flag", &Flag, &b_Flag);
   fChain->SetBranchAddress("ICode", &ICode, &b_ICode);
   fChain->SetBranchAddress("ParId", &ParId, &b_ParId);
   fChain->SetBranchAddress("Region", &Region, &b_Region);
   fChain->SetBranchAddress("IntInfo", IntInfo, &b_IntInfo);
   fChain->SetBranchAddress("IntVtx", IntVtx, &b_IntVtx);
   fChain->SetBranchAddress("Multip", &Multip, &b_Multip);
   fChain->SetBranchAddress("Tracks", Tracks, &b_Tracks);
   fChain->SetBranchAddress("SecondaryId", SecondaryId, &b_SecondaryId);
   fChain->SetBranchAddress("SecondaryInfo", SecondaryInfo, &b_SecondaryInfo);
   fChain->SetBranchAddress("VertexId", &VertexId, &b_VertexId);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   Notify();
}

Bool_t DecayTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DecayTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DecayTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DecayTree_cxx
