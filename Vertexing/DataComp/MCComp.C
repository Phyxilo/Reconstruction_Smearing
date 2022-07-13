#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *SlpTXHist1 = new TH1F("SlpTXHist1","X Slope Histogram",50,-0.4,0.4);
TH1F *SlpTXHist2 = new TH1F("SlpTXHist2","X Slope Histogram",50,-0.4,0.4);
TH1F *SlpTXHist3 = new TH1F("SlpTXHist3","X Slope Histogram",50,-0.4,0.4);

TH1F *SlpTYHist1 = new TH1F("SlpTYHist1","Y Slope Histogram",50,-0.4,0.4);
TH1F *SlpTYHist2 = new TH1F("SlpTYHist2","Y Slope Histogram",50,-0.4,0.4);
TH1F *SlpTYHist3 = new TH1F("SlpTYHist3","Y Slope Histogram",50,-0.4,0.4);

TH1F *SlpT2Hist1 = new TH1F("SlpT2Hist1","Space Angle Histogram",50,0,0.5);
TH1F *SlpT2Hist2 = new TH1F("SlpT2Hist2","Space Angle Histogram",50,0,0.5);
TH1F *SlpT2Hist3 = new TH1F("SlpT2Hist3","Space Angle Histogram",50,0,0.5);

TH1F *IPMC1 = new TH1F("IPMC","Impact Parameter Histogram",50,0,30);
TH1F *IPMC2 = new TH1F("IPMC","Impact Parameter Histogram",50,0,30);
TH1F *IPMC3 = new TH1F("IPMC","Impact Parameter Histogram",50,0,30);

TH1F *Mult1 = new TH1F("Mult1","Multiplicity Histogram",50,0,50);
TH1F *Mult2 = new TH1F("Mult2","Multiplicity Histogram",50,0,50);
TH1F *Mult3 = new TH1F("Mult3","Multiplicity Histogram",50,0,50);

TFile *monteCarlo1, *monteCarlo2, *monteCarlo3;

int MC1VtxSize, MC2VtxSize, MC3VtxSize;

void MCComp()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  monteCarlo1 = TFile::Open("Multip/20210616_PD04.root");
  monteCarlo2 = TFile::Open("Multip/20220610_PD04.root");
  monteCarlo3 = TFile::Open("Multip/20220622_PD04.root");

  TTree *treeMCTrk1 = (TTree*)monteCarlo1->Get("TRK");
  TTree *treeMCTrk2 = (TTree*)monteCarlo2->Get("TRK");
  TTree *treeMCTrk3 = (TTree*)monteCarlo3->Get("TRK");

  TTree *treeMCVtx1 = (TTree*)monteCarlo1->Get("VTX");
  TTree *treeMCVtx2 = (TTree*)monteCarlo2->Get("VTX");
  TTree *treeMCVtx3 = (TTree*)monteCarlo3->Get("VTX");

  MC1VtxSize = treeMCVtx1->GetEntriesFast();
  MC2VtxSize = treeMCVtx2->GetEntriesFast();
  MC3VtxSize = treeMCVtx3->GetEntriesFast();

  for (int i = 0; i < treeMCTrk1->GetEntriesFast(); i++)
  {
    treeMCTrk1->GetEntry(i);
    
    TLeaf *slpTX = treeMCTrk1->GetLeaf("SlpTX");
    TLeaf *slpTY = treeMCTrk1->GetLeaf("SlpTY");
    TLeaf *slpT2 = treeMCTrk1->GetLeaf("SlpT2");
    TLeaf *IP = treeMCTrk1->GetLeaf("ImpactPar");
    
    SlpTXHist1->Fill(slpTX->GetValue());
    SlpTYHist1->Fill(slpTY->GetValue());
    SlpT2Hist1->Fill(slpT2->GetValue());
    IPMC1->Fill(IP->GetValue());
  }

  for (int i = 0; i < treeMCTrk2->GetEntriesFast(); i++)
  {
    treeMCTrk2->GetEntry(i);

    TLeaf *slpTX = treeMCTrk2->GetLeaf("SlpTX");
    TLeaf *slpTY = treeMCTrk2->GetLeaf("SlpTY");
    TLeaf *slpT2 = treeMCTrk2->GetLeaf("SlpT2");
    TLeaf *IP = treeMCTrk2->GetLeaf("ImpactPar");

    SlpTXHist2->Fill(slpTX->GetValue());
    SlpTYHist2->Fill(slpTY->GetValue());
    SlpT2Hist2->Fill(slpT2->GetValue());
    IPMC2->Fill(IP->GetValue());
  }

  for (int i = 0; i < treeMCTrk3->GetEntriesFast(); i++)
  {
    treeMCTrk3->GetEntry(i);

    TLeaf *slpTX = treeMCTrk3->GetLeaf("SlpTX");
    TLeaf *slpTY = treeMCTrk3->GetLeaf("SlpTY");
    TLeaf *slpT2 = treeMCTrk3->GetLeaf("SlpT2");
    TLeaf *IP = treeMCTrk3->GetLeaf("ImpactPar");

    SlpTXHist3->Fill(slpTX->GetValue());
    SlpTYHist3->Fill(slpTY->GetValue());
    SlpT2Hist3->Fill(slpT2->GetValue());
    IPMC3->Fill(IP->GetValue());
  }

  for (int i = 0; i < MC1VtxSize; i++)
  {
    treeMCVtx1->GetEntry(i);

    TLeaf *mult = treeMCVtx1->GetLeaf("Multip");

    Mult1->Fill(mult->GetValue());
  }

  for (int i = 0; i < MC2VtxSize; i++)
  {
    treeMCVtx2->GetEntry(i);

    TLeaf *mult = treeMCVtx2->GetLeaf("Multip");

    Mult2->Fill(mult->GetValue());
  }

  for (int i = 0; i < MC3VtxSize; i++)
  {
    treeMCVtx3->GetEntry(i);

    TLeaf *mult = treeMCVtx3->GetLeaf("Multip");

    Mult3->Fill(mult->GetValue());
  }

  
  SlpTXHist2->Scale(MC1VtxSize/MC2VtxSize);
  SlpTXHist3->Scale(MC1VtxSize/MC3VtxSize);

  SlpTYHist2->Scale(MC1VtxSize/MC2VtxSize);
  SlpTYHist3->Scale(MC1VtxSize/MC3VtxSize);

  SlpT2Hist2->Scale(MC1VtxSize/MC2VtxSize);
  SlpT2Hist3->Scale(MC1VtxSize/MC3VtxSize);

  IPMC2->Scale(MC1VtxSize/MC2VtxSize);
  IPMC3->Scale(MC1VtxSize/MC3VtxSize);

  Mult2->Scale(MC1VtxSize/MC2VtxSize);
  Mult3->Scale(MC1VtxSize/MC3VtxSize);

  SlpTXHist1->GetYaxis()->SetRangeUser(0, 200000);
  
  SlpTXHist1->Draw("HIST E1"); SlpTXHist1->SetLineColor(kRed);
  SlpTXHist2->Draw("SAME HIST"); SlpTXHist2->SetLineColor(kBlue);
  SlpTXHist3->Draw("SAME HIST"); SlpTXHist3->SetLineColor(kOrange);
  
  TLegend *legend; 

  legend = new TLegend(0.1, 0.8, 0.32, 0.9);
  legend->SetHeader("Histogram Legend","C");
  legend->AddEntry(SlpTXHist1,"MC1","f");
  legend->AddEntry(SlpTXHist2,"MC2","f");
  legend->AddEntry(SlpTXHist3,"MC3","f");
  legend->Draw();

  Canvas->Print( "MCCompHist.pdf(", "pdf");

  SlpTYHist1->GetYaxis()->SetRangeUser(0, 200000);

  SlpTYHist1->Draw("HIST E1"); SlpTYHist1->SetLineColor(kRed);
  SlpTYHist2->Draw("SAME HIST"); SlpTYHist2->SetLineColor(kBlue);
  SlpTYHist3->Draw("SAME HIST"); SlpTYHist3->SetLineColor(kOrange);
  
  legend = new TLegend(0.1, 0.8, 0.32, 0.9);
  legend->SetHeader("Histogram Legend","C");
  legend->AddEntry(SlpTYHist1,"MC1","f");
  legend->AddEntry(SlpTYHist2,"MC2","f");
  legend->AddEntry(SlpTYHist3,"MC3","f");
  legend->Draw();

  Canvas->Print( "MCCompHist.pdf", "pdf");

  SlpT2Hist1->GetYaxis()->SetRangeUser(0, 150000);

  SlpT2Hist1->Draw("HIST E1"); SlpT2Hist1->SetLineColor(kRed);
  SlpT2Hist2->Draw("SAME HIST"); SlpT2Hist2->SetLineColor(kBlue);
  SlpT2Hist3->Draw("SAME HIST"); SlpT2Hist3->SetLineColor(kOrange);
  
  legend = new TLegend(0.1, 0.8, 0.32, 0.9);
  legend->SetHeader("Histogram Legend","C");
  legend->AddEntry(SlpT2Hist1,"MC1","f");
  legend->AddEntry(SlpT2Hist2,"MC2","f");
  legend->AddEntry(SlpT2Hist3,"MC3","f");
  legend->Draw();

  Canvas->Print( "MCCompHist.pdf", "pdf");

  IPMC1->GetYaxis()->SetRangeUser(0, 450000);

  IPMC1->Draw("HIST E1"); IPMC1->SetLineColor(kRed);
  IPMC2->Draw("SAME HIST"); IPMC2->SetLineColor(kBlue);
  IPMC3->Draw("SAME HIST"); IPMC3->SetLineColor(kOrange);
  
  legend = new TLegend(0.1, 0.8, 0.32, 0.9);
  legend->SetHeader("Histogram Legend","C");
  legend->AddEntry(IPMC1,"MC1","f");
  legend->AddEntry(IPMC2,"MC2","f");
  legend->AddEntry(IPMC3,"MC3","f");
  legend->Draw();

  Canvas->Print( "MCCompHist.pdf", "pdf");

  Mult1->GetYaxis()->SetRangeUser(0, 5000);

  Mult1->Draw("HIST E1"); Mult1->SetLineColor(kRed);
  Mult2->Draw("SAME HIST"); Mult2->SetLineColor(kBlue);
  Mult3->Draw("SAME HIST"); Mult3->SetLineColor(kOrange);
  
  legend = new TLegend(0.1, 0.8, 0.32, 0.9);
  legend->SetHeader("Histogram Legend","C");
  legend->AddEntry(Mult1,"MC1","f");
  legend->AddEntry(Mult2,"MC2","f");
  legend->AddEntry(Mult3,"MC3","f");
  legend->Draw();

  Canvas->Print( "MCCompHist.pdf)", "pdf");
}