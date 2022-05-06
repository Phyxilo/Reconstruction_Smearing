//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May  6 18:31:00 2022 by ROOT version 6.22/02
// from TTree MicroTrackTree/Hits in emulsion layers info
// found on file: hadronsg4_r86_FTFP_BERT_8.root
//////////////////////////////////////////////////////////

#ifndef MicroTrackTree_h
#define MicroTrackTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class MicroTrackTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nevhep;
   Int_t           nhep;
   Int_t           isthep[89748];   //[nhep]
   Int_t           idhep[89748];   //[nhep]
   Int_t           jmohep[89748][2];   //[nhep]
   Int_t           jdahep[89748][4];   //[nhep]
   Double_t        phep[89748][5];   //[nhep]
   Double_t        vhep[89748][4];   //[nhep]
   Int_t           RunNumber;

   // List of branches
   TBranch        *b_nevhep;   //!
   TBranch        *b_nhep;   //!
   TBranch        *b_isthep;   //!
   TBranch        *b_idhep;   //!
   TBranch        *b_jmohep;   //!
   TBranch        *b_jdahep;   //!
   TBranch        *b_phep;   //!
   TBranch        *b_vhep;   //!
   TBranch        *b_RunNumber;   //!

   MicroTrackTree(TTree *tree=0);
   virtual ~MicroTrackTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MicroTrackTree_cxx
MicroTrackTree::MicroTrackTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("hadronsg4_r86_FTFP_BERT_8.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("hadronsg4_r86_FTFP_BERT_8.root");
      }
      f->GetObject("MicroTrackTree",tree);

   }
   Init(tree);
}

MicroTrackTree::~MicroTrackTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MicroTrackTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MicroTrackTree::LoadTree(Long64_t entry)
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

void MicroTrackTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("nevhep", &nevhep, &b_nevhep);
   fChain->SetBranchAddress("nhep", &nhep, &b_nhep);
   fChain->SetBranchAddress("isthep", isthep, &b_isthep);
   fChain->SetBranchAddress("idhep", idhep, &b_idhep);
   fChain->SetBranchAddress("jmohep", jmohep, &b_jmohep);
   fChain->SetBranchAddress("jdahep", jdahep, &b_jdahep);
   fChain->SetBranchAddress("phep", phep, &b_phep);
   fChain->SetBranchAddress("vhep", vhep, &b_vhep);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   Notify();
}

Bool_t MicroTrackTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MicroTrackTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MicroTrackTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MicroTrackTree_cxx
