#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

void HistDrawMC(TFile *file, TH1F *TXHist, TH1F *TYHist, TH1F *T2Hist);
void HistDrawData(TFile *file, TH1F *TXHist, TH1F *TYHist, TH1F *T2Hist);
void HistFormat(TH1F *Hist0, TH1F *Hist1);
void HistFormatMulti(TH1F *Hist0, TH1F *Hist1, TH1F *Hist2);

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *eTXDataHist = new TH1F("eTXDataHist","Slope X Histogram ",50,-0.5,0.5);
TH1F *eTYDataHist = new TH1F("eTYDataHist","Slope Y Histogram ",50,-0.5,0.5);

TH1F *eTXMC0Hist = new TH1F("eTXMCHist","Slope X Histogram ",50,-0.5,0.5);
TH1F *eTYMC0Hist = new TH1F("eTYMCHist","Slope Y Histogram ",50,-0.5,0.5);
TH1F *eTXMC1Hist = new TH1F("eTXMCHist","Slope X Histogram ",50,-0.5,0.5);
TH1F *eTYMC1Hist = new TH1F("eTYMCHist","Slope Y Histogram ",50,-0.5,0.5);

TH1F *eT2DataHist = new TH1F("eTXDataHist","Space Angle Histogram ",50,0,1);
TH1F *eT2MC0Hist = new TH1F("eTXDataHist","Space Angle Histogram ",50,0,1);
TH1F *eT2MC1Hist = new TH1F("eTXDataHist","Space Angle Histogram ",50,0,1);

void GComp()
{
  char dataName[64], MC0Name[64], MC1Name[64];
  char outName[64], outNameBegin[64], outNameEnd[64];

  sprintf(MC0Name, "/home/phyxilo/Downloads/pl001_030/linked_tracks.root");
  sprintf(MC1Name, "/home/phyxilo/Downloads/fedraOut/Out/finalCut.root");
  sprintf(dataName, "/home/phyxilo/Downloads/dataFile/data.root");

  sprintf(outName, "histogram.pdf");
  sprintf(outNameBegin, "%s[", outName);
  sprintf(outNameEnd, "%s]", outName);

  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  TFile *data = TFile::Open(dataName);
  //TFile *monteCarlo0 = TFile::Open(MC0Name);
  TFile *monteCarlo1 = TFile::Open(MC1Name);

  TTree *dataTree = (TTree*)data->Get("TRK");
  //TTree *MC0Tree = (TTree*)monteCarlo0->Get("tracks");
  TTree *MC1Tree = (TTree*)monteCarlo1->Get("tracks");

  //HistDrawMC(monteCarlo0, eTXMC0Hist, eTYMC0Hist, eT2MC0Hist);
  HistDrawMC(monteCarlo1, eTXMC1Hist, eTYMC1Hist, eT2MC1Hist);
  HistDrawData(data, eTXDataHist, eTYDataHist, eT2DataHist);

  Canvas->Print( outNameBegin,"pdf");
  
  HistFormat(eTXDataHist, eTXMC1Hist); Canvas->Print( outName,"pdf");
  HistFormat(eTYDataHist, eTYMC1Hist); Canvas->Print( outName,"pdf");
  HistFormat(eT2DataHist, eT2MC1Hist); Canvas->Print( outName,"pdf");
  
  /*
  HistFormatMulti(eTXDataHist, eTXMC0Hist, eTXMC1Hist); Canvas->Print( outName,"pdf");
  HistFormatMulti(eTYDataHist, eTYMC0Hist, eTYMC1Hist); Canvas->Print( outName,"pdf");
  HistFormatMulti(eT2DataHist, eT2MC0Hist, eT2MC1Hist); Canvas->Print( outName,"pdf");
  */
  Canvas->Print( outNameEnd,"pdf");
}

void HistDrawMC(TFile *file, TH1F *TXHist, TH1F *TYHist, TH1F *T2Hist)
{
  TTree *tree = (TTree*)file->Get("tracks");

  TLeaf *eTX = tree->GetLeaf("t.eTX");
  TLeaf *eTY = tree->GetLeaf("t.eTY");

  TLeaf *PlateID = tree->GetLeaf("t.ePID");

  double dataBfX = 0;
  double dataBfY = 0;

  for (int i = 0; i < tree->GetEntriesFast(); i++)
  {
    tree->GetEntry(i);

    if (PlateID->GetValue() >= 1)
    {
      //eXMCHist->Fill(eXMC->GetValue());
      //eYMCHist->Fill(eYMC->GetValue());

      dataBfX = eTX->GetValue();
      dataBfY = eTY->GetValue();

      TXHist->Fill(dataBfX);
      TYHist->Fill(dataBfY);
      T2Hist->Fill(sqrt(dataBfX*dataBfX + dataBfY*dataBfY));
    }
  }
}

void HistDrawData(TFile *file, TH1F *TXHist, TH1F *TYHist, TH1F *T2Hist)
{
  TTree *tree = (TTree*)file->Get("TRK");

  TLeaf *eTX = tree->GetLeaf("tx");
  TLeaf *eTY = tree->GetLeaf("ty");

  TLeaf *beamAngleX = tree->GetLeaf("txpeak");
  TLeaf *beamAngleY = tree->GetLeaf("typeak");

  double dataBfX = 0;
  double dataBfY = 0;

  for (int i = 0; i < tree->GetEntriesFast(); i++)
  {
    tree->GetEntry(i);

    //eXDataHist->Fill(eXData->GetValue());
    //eYDataHist->Fill(eYData->GetValue());

    double dataBfX = eTX->GetValue() - beamAngleX->GetValue();
    double dataBfY = eTY->GetValue() - beamAngleY->GetValue();

    TXHist->Fill(dataBfX);
    TYHist->Fill(dataBfY);
    T2Hist->Fill(sqrt(dataBfX*dataBfX + dataBfY*dataBfY));
  }
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

void HistFormatMulti(TH1F *Hist0, TH1F *Hist1, TH1F *Hist2)
{

  Hist1->Scale(Hist0->Integral()/Hist1->Integral());
  Hist2->Scale(Hist0->Integral()/Hist2->Integral() + 0.2);

  //Hist0->Scale(1./Hist0->Integral());
  //Hist1->Scale(1./Hist1->Integral());

  Hist0->GetYaxis()->SetRangeUser(0, 180000);

  Hist0->Draw("HIST"); Hist0->SetLineColor(kBlue);
  Hist1->Draw("SAMESE1"); Hist1->SetLineColor(kRed);
  Hist2->Draw("SAMESE1"); Hist2->SetLineColor(kGreen);
  /*
  gStyle->SetOptFit();
  Canvas->Update();
  TPaveStats *peTX = (TPaveStats*)Hist0->FindObject("stats");
  peTX->SetY1NDC(0.05);
  peTX->SetY2NDC(0.25);
  Canvas->Modified();
  */
  auto legendTX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTX->SetHeader("Histogram Legend","C");
  legendTX->AddEntry(Hist2,"Data","f");
  legendTX->AddEntry(Hist1,"Data","f");
  legendTX->AddEntry(Hist0,"MonteCarlo","f");
  legendTX->Draw();
}