#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

void HistDraw();
void HistFormat(TH1F *Hist0, TH1F *Hist1);
void HistFormatMulti(vector<TH1F*> HistArr);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *eTXDataHist = new TH1F("eTXDataHist","Slope X Histogram ",50,-0.5,0.5);
TH1F *eTYDataHist = new TH1F("eTYDataHist","Slope Y Histogram ",50,-0.5,0.5);

TH1F *eTXMC0Hist = new TH1F("eTXMCHist","Slope X Histogram ",50,-0.5,0.5);
TH1F *eTYMC0Hist = new TH1F("eTYMCHist","Slope Y Histogram ",50,-0.5,0.5);
TH1F *eTXMC1Hist = new TH1F("eTXMCHist","Slope X Histogram ",50,-0.5,0.5);
TH1F *eTYMC1Hist = new TH1F("eTYMCHist","Slope Y Histogram ",50,-0.5,0.5);
TH1F *eTXMC2Hist = new TH1F("eTXMCHist","Slope X Histogram ",50,-0.5,0.5);
TH1F *eTYMC2Hist = new TH1F("eTYMCHist","Slope Y Histogram ",50,-0.5,0.5);
TH1F *eTXMCTrueHist = new TH1F("eTYMCHist","Slope Y Histogram ",50,-0.5,0.5);
TH1F *eTYMCTrueHist = new TH1F("eTYMCHist","Slope Y Histogram ",50,-0.5,0.5);

TH1F *eT2DataHist = new TH1F("eT2DataHist","Space Angle Histogram ",50,0,1);
TH1F *eT2MC0Hist = new TH1F("eT2MCHist","Space Angle Histogram ",50,0,1);
TH1F *eT2MC1Hist = new TH1F("eT2MCHist","Space Angle Histogram ",50,0,1);
TH1F *eT2MC2Hist = new TH1F("eT2MCHist","Space Angle Histogram ",50,0,1);
TH1F *eT2MCTrueHist = new TH1F("eT2MCHist","Space Angle Histogram ",50,0,1);

TFile *data, *monteCarlo0, *monteCarlo1, *monteCarloTrue, *monteCarlo2;

vector<int> eIDListMC;
vector<int> eIDListTrueMC;
vector<int> eIDListData;

int eventSizeMC, eventSizeTrueMC, eventSizeData;

void GComp()
{
  char dataName[64], MC0Name[64], MC1Name[64], TrueMCName[64], MC2Name[64];
  char outName[64], outNameBegin[64], outNameEnd[64];

  //sprintf(MC0Name, "/home/phyxilo/Downloads/pl001_030/linked_tracks.root");
  sprintf(MC1Name, "/home/phyxilo/Downloads/fedraOut/Out/finalCut.root");
  //sprintf(MC2Name, "/home/phyxilo/Downloads/fedraOut/OutTrack/finalCut.root");
  //sprintf(TrueMCName, "/home/phyxilo/root/macros/Smearing/MultCut.root");
  sprintf(TrueMCName, "/home/phyxilo/root/macros/Smearing/MultCut.root");
  //sprintf(TrueMCName, "TrueMC/trueMC.root");
  sprintf(dataName, "/home/phyxilo/Downloads/dataFile/data.root");

  sprintf(outName, "histogram.pdf");
  sprintf(outNameBegin, "%s[", outName);
  sprintf(outNameEnd, "%s]", outName);

  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  data = TFile::Open(dataName);
  //monteCarlo0 = TFile::Open(MC0Name);
  monteCarlo1 = TFile::Open(MC1Name);
  //monteCarlo2 = TFile::Open(MC2Name);
  monteCarloTrue = TFile::Open(TrueMCName);

  HistDraw();

  vector<TH1F*> histListTX, histListTY, histListT2;
  histListTX.push_back(eTXDataHist); histListTX.push_back(eTXMC1Hist); histListTX.push_back(eTXMCTrueHist);
  histListTY.push_back(eTYDataHist); histListTY.push_back(eTYMC1Hist); histListTY.push_back(eTYMCTrueHist);
  histListT2.push_back(eT2DataHist); histListT2.push_back(eT2MC1Hist); histListT2.push_back(eT2MCTrueHist);

  Canvas->Print( outNameBegin,"pdf");

  
  HistFormatMulti(histListTX); Canvas->Print( outName,"pdf");
  HistFormatMulti(histListTY); Canvas->Print( outName,"pdf");
  HistFormatMulti(histListT2); Canvas->Print( outName,"pdf"); 

  /*
  HistFormat(eTXDataHist, eTXMC1Hist); Canvas->Print( outName,"pdf");
  HistFormat(eTYDataHist, eTYMC1Hist); Canvas->Print( outName,"pdf");
  HistFormat(eT2DataHist, eT2MC1Hist); Canvas->Print( outName,"pdf");
  */

  Canvas->Print( outNameEnd,"pdf");
}
void HistDraw()
{
  TTree *treeData = (TTree*)data->Get("TRK");
  TTree *treeDataVtx = (TTree*)data->Get("VTX");
  //TTree *treeMC0 = (TTree*)monteCarlo0->Get("tracks");
  TTree *treeMC1 = (TTree*)monteCarlo1->Get("tracks");
  //TTree *treeMC2 = (TTree*)monteCarlo2->Get("tracks");
  TTree *treeMCTrue = (TTree*)monteCarloTrue->Get("Slp");

  TLeaf *eTXData = treeData->GetLeaf("tx"); TLeaf *eTYData = treeData->GetLeaf("ty");
  //TLeaf *eTXMC0 = treeMC0->GetLeaf("t.eTX"); TLeaf *eTYMC0 = treeMC0->GetLeaf("t.eTY");
  TLeaf *eTXMC1 = treeMC1->GetLeaf("t.eTX"); TLeaf *eTYMC1 = treeMC1->GetLeaf("t.eTY"); TLeaf *eIDMC1 = treeMC1->GetLeaf("t.eMCEvt");
  //TLeaf *eTXMC2 = treeMC2->GetLeaf("t.eTX"); TLeaf *eTYMC2 = treeMC2->GetLeaf("t.eTY"); 
  TLeaf *eTXMCTrue = treeMCTrue->GetLeaf("SlpTX"); TLeaf *eTYMCTrue = treeMCTrue->GetLeaf("SlpTY");
  TLeaf *eT2MCTrue = treeMCTrue->GetLeaf("SlpT2");
 
  /*TLeaf *PlateIDMC0 = treeMC0->GetLeaf("t.ePID");*/ TLeaf *PlateIDMC1 = treeMC1->GetLeaf("t.ePID"); /*TLeaf *PlateIDMC2 = treeMC2->GetLeaf("t.ePID");*/

  TLeaf *beamAngleX = treeData->GetLeaf("txpeak"); TLeaf *beamAngleY = treeData->GetLeaf("typeak");

  double bfXMC0 = 0, bfYMC0 = 0, bfXMC1 = 0, bfYMC1 = 0, bfXMC2 = 0, bfYMC2 = 0, bfXMCTrue = 0, bfYMCTrue = 0;
  double bfDataX = 0, bfDataY = 0;

  for (int i = 0; i < treeData->GetEntriesFast(); i++)
  {
    treeData->GetEntry(i);

    bfDataX = eTXData->GetValue() - beamAngleX->GetValue();
    bfDataY = eTYData->GetValue() - beamAngleY->GetValue();

    eTXDataHist->Fill(bfDataX);
    eTYDataHist->Fill(bfDataY);
    eT2DataHist->Fill(sqrt(bfDataX*bfDataX + bfDataY*bfDataY));
  }
  /*
  for (int i = 0; i < treeMC0->GetEntriesFast(); i++)
  {
    treeMC0->GetEntry(i);

    if (PlateIDMC0->GetValue() >= 1)
    {
      dataBfXMC0 = eTXMC0->GetValue();
      dataBfXMC0 = eTYMC0->GetValue();

      eTXMC0Hist->Fill(bfXMC0);
      eTYMC0Hist->Fill(bfYMC0);
      eT2MC0Hist->Fill(sqrt(bfXMC0*bfXMC0 + bfYMC0*bfYMC0));
    }
  }
  */
  for (int i = 0; i < treeMC1->GetEntriesFast(); i++)
  {
    treeMC1->GetEntry(i);

    if (PlateIDMC1->GetValue() >= 1)
    {
      bfXMC1 = eTXMC1->GetValue();
      bfYMC1 = eTYMC1->GetValue();

      eTXMC1Hist->Fill(bfXMC1);
      eTYMC1Hist->Fill(bfYMC1);
      eT2MC1Hist->Fill(sqrt(bfXMC1*bfXMC1 + bfYMC1*bfYMC1));

      eIDListMC.push_back(eIDMC1->GetValue());
    }
  }
  /*
  for (int i = 0; i < treeMC2->GetEntriesFast(); i++)
  {
    treeMC2->GetEntry(i);

    if (PlateIDMC2->GetValue() >= 1)
    {
      bfXMC2 = eTXMC2->GetValue();
      bfYMC2 = eTYMC2->GetValue();

      eTXMC2Hist->Fill(bfXMC2);
      eTYMC2Hist->Fill(bfYMC2);
      eT2MC2Hist->Fill(sqrt(bfXMC2*bfXMC2 + bfYMC2*bfYMC2));
    }
  }
  */

  for (int i = 0; i < treeMCTrue->GetEntriesFast(); i++)
  {
    treeMCTrue->GetEntry(i);

    bfXMCTrue = eTXMCTrue->GetValue();
    bfYMCTrue = eTYMCTrue->GetValue();

    eTXMCTrueHist->Fill(bfXMCTrue);
    eTYMCTrueHist->Fill(bfYMCTrue);
    eT2MCTrueHist->Fill(sqrt(bfXMCTrue*bfXMCTrue + bfYMCTrue*bfYMCTrue));

    //eIDListTrueMC.push_back()
  }


  sort(eIDListMC.begin(), eIDListMC.end());
  eIDListMC.erase(unique(eIDListMC.begin(), eIDListMC.end()), eIDListMC.end());

  eventSizeMC = eIDListMC.size();
  eventSizeTrueMC = 1148;
  //eventSizeTrueMC = 10000;
  eventSizeData = treeDataVtx->GetEntriesFast();

}

void HistFormat(TH1F *Hist0, TH1F *Hist1)
{

  Hist1->Scale(Hist0->Integral()/Hist1->Integral());

  //Hist0->Scale(1./Hist0->Integral());
  //Hist1->Scale(1./Hist1->Integral());

  Hist1->GetYaxis()->SetRangeUser(0, 150000);

  Hist1->Draw("HIST"); Hist1->SetLineColor(kBlue);
  Hist0->Draw("SAMESE1"); Hist0->SetLineColor(kRed);

  gStyle->SetOptFit();
  Canvas->Update();
  TPaveStats *peTX = (TPaveStats*)Hist1->FindObject("stats");
  peTX->SetY1NDC(0.05);
  peTX->SetY2NDC(0.25);
  Canvas->Modified();

  auto legendTX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTX->SetHeader("Histogram Legend","C");
  legendTX->AddEntry(Hist0,"Data","f");
  legendTX->AddEntry(Hist1,"MonteCarlo","f");
  legendTX->Draw();
}

void HistFormatMulti(vector<TH1F*> HistArr)
{
  //HistArr[1]->Scale(HistArr[0]->Integral()/HistArr[1]->Integral());
  //HistArr[2]->Scale(HistArr[0]->Integral()/HistArr[2]->Integral());
  //HistArr[3]->Scale(HistArr[0]->Integral()/HistArr[3]->Integral());

  //Hist0->Scale(1./Hist0->Integral());
  //Hist1->Scale(1./Hist1->Integral());

  HistArr[1]->Scale(eventSizeData/eventSizeMC);
  HistArr[2]->Scale(eventSizeData/eventSizeTrueMC);

  HistArr[0]->GetYaxis()->SetRangeUser(0, 180000);

  HistArr[0]->SetLineColor(kRed); HistArr[0]->Draw("HIST E1"); 
  HistArr[1]->SetLineColor(kBlue); HistArr[1]->Draw("SAME HIST");
  HistArr[2]->SetLineColor(kGreen); HistArr[2]->Draw("SAME HIST");
  //HistArr[3]->SetLineColor(kBlack); HistArr[3]->SetLineStyle(kSolid); HistArr[3]->Draw("SAME HIST");

  auto legendTX = new TLegend(0.1, 0.8, 0.35, 0.95);
  legendTX->SetHeader("Histogram Legend","C");
  legendTX->AddEntry(HistArr[2],"Monte Carlo (Final Cut)","f");
  //legendTX->AddEntry(HistArr[2],"Monte Carlo 2","f");
  legendTX->AddEntry(HistArr[1],"Monte Carlo","f");
  legendTX->AddEntry(HistArr[0],"Data","f");
  legendTX->Draw();
}