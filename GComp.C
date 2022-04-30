#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

void dataRead();

void GComp()
{
  dataRead();
}

void dataRead()
{
  char dataName[64], MCName[64], MCLeafName[64];
  //sprintf( dataName, "~/Downloads/data_finealign/%02d_001.cp.root", index);
  //sprintf( MCName, "~/Downloads/cp_data_pl001_105/%02d_001.cp.root", index);
  //sprintf( MCLeafName, "couples%d", index);

  sprintf(MCName, "/home/phyxilo/Downloads/pl001_030/linked_tracks.root");
  sprintf(dataName, "/home/phyxilo/Downloads/dataFile/data.root");

  TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
	Canvas->SetWindowSize(1920, 1080);
	Canvas->SetCanvasSize(192*6, 108*6);

  TFile *data = TFile::Open(dataName);
  TFile *monteCarlo = TFile::Open(MCName);

  TH1F *eXDataHist = new TH1F("eXDataHist","Data Histogram ",100,-15000,15000);
  TH1F *eYDataHist = new TH1F("eYDataHist","Data Histogram ",100,-15000,15000);
  TH1F *eTXDataHist = new TH1F("eTXDataHist","Slope X Histogram ",100,-0.5,0.5);
  TH1F *eTYDataHist = new TH1F("eTYDataHist","Slope Y Histogram ",100,-0.5,0.5);

  TH1F *eXMCHist = new TH1F("eXMCHist","MonteCarlo Histogram ",100,-15000,15000);
  TH1F *eYMCHist = new TH1F("eYMCHist","MonteCarlo Histogram ",100,-15000,15000);
  TH1F *eTXMCHist = new TH1F("eTXMCHist","Slope X Histogram ",100,-0.5,0.5);
  TH1F *eTYMCHist = new TH1F("eTYMCHist","Slope Y Histogram ",100,-0.5,0.5);

  TH1F *eT2DataHist = new TH1F("eTXDataHist","Space Angle Histogram ",100,0,1);
  TH1F *eT2MCHist = new TH1F("eTXDataHist","Space Angle Histogram ",100,0,1);

  //TTree *dataTree = (TTree*)data->Get("couples");
  //TTree *MCTree = (TTree*)monteCarlo->Get(MCLeafName);
  TTree *dataTree = (TTree*)data->Get("TRK");
  TTree *MCTree = (TTree*)monteCarlo->Get("tracks");

  //TLeaf *eXData = dataTree->GetLeaf("t.eX");
  //TLeaf *eYData = dataTree->GetLeaf("t.eY");
  TLeaf *eTXData = dataTree->GetLeaf("tx");
  TLeaf *eTYData = dataTree->GetLeaf("ty");

  TLeaf *beamAngleX = dataTree->GetLeaf("txpeak");
  TLeaf *beamAngleY = dataTree->GetLeaf("typeak");

  //TLeaf *eXMC = MCTree->GetLeaf("t.eX");
  //TLeaf *eYMC = MCTree->GetLeaf("t.eY");
  TLeaf *eTXMC = MCTree->GetLeaf("t.eTX");
  TLeaf *eTYMC = MCTree->GetLeaf("t.eTY");

  TLeaf *MCPlateID = MCTree->GetLeaf("t.ePID");

  Canvas->Print( "histogram.pdf[","pdf");

  double dataBfDataX = 0;
  double dataBfDataY = 0;

  for (int i = 0; i < dataTree->GetEntriesFast(); i++)
  {
    dataTree->GetEntry(i);

    //eXDataHist->Fill(eXData->GetValue());
    //eYDataHist->Fill(eYData->GetValue());

    double dataBfX = eTXData->GetValue() - beamAngleX->GetValue();
    double dataBfY = eTYData->GetValue() - beamAngleY->GetValue();

    eTXDataHist->Fill(dataBfX);
    eTYDataHist->Fill(dataBfY);
    eT2DataHist->Fill(sqrt(dataBfX*dataBfX + dataBfY*dataBfY));
  }

  double dataBfMCX = 0;
  double dataBfMCY = 0;

  for (int i = 0; i < MCTree->GetEntriesFast(); i++)
  {
    MCTree->GetEntry(i);

    if (MCPlateID->GetValue() >= 1)
    {
      //eXMCHist->Fill(eXMC->GetValue());
      //eYMCHist->Fill(eYMC->GetValue());

      dataBfMCX = eTXMC->GetValue();
      dataBfMCY = eTYMC->GetValue();

      eTXMCHist->Fill(dataBfMCX);
      eTYMCHist->Fill(dataBfMCY);
      eT2MCHist->Fill(sqrt(dataBfMCX*dataBfMCX + dataBfMCY*dataBfMCY));
    }
  }

  //eTYMCHist->SetDefaultBufferSize();

  /*
  eXMCHist->Draw(); eXMCHist->SetLineColor(kBlue);
  eXDataHist->Draw("SAMESE1"); eXDataHist->SetLineColor(kRed);

  gStyle->SetOptFit();
  Canvas->Update();
  TPaveStats *peX = (TPaveStats*)eXMCHist->FindObject("stats");
  peX->SetY1NDC(0.05);
  peX->SetY2NDC(0.25);
  Canvas->Modified();

  auto legendX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendX->SetHeader("Histogram Legend","C");
  legendX->AddEntry(eXDataHist,"Data","f");
  legendX->AddEntry(eXMCHist,"MonteCarlo","f");
  legendX->Draw();

  Canvas->Print( "histogram.pdf","pdf");

  eYMCHist->Draw(); eYMCHist->SetLineColor(kBlue);
  eYDataHist->Draw("SAMESE1"); eYDataHist->SetLineColor(kRed);

  gStyle->SetOptFit();
  Canvas->Update();
  TPaveStats *peY = (TPaveStats*)eYMCHist->FindObject("stats");
  peY->SetY1NDC(0.05);
  peY->SetY2NDC(0.25);
  Canvas->Modified();

  auto legendY = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendY->SetHeader("Histogram Legend","C");
  legendY->AddEntry(eYDataHist,"Data","f");
  legendY->AddEntry(eYMCHist,"MonteCarlo","f");
  legendY->Draw();

  Canvas->Print( "histogram.pdf","pdf");
  */

  eTXMCHist->Scale(eTXDataHist->Integral()/eTXMCHist->Integral());

  //eTXMCHist->Scale(1./eTYMCHist->Integral());
  //eTXDataHist->Scale(1./eTYDataHist->Integral());

  eTXMCHist->Draw("HIST"); eTXDataHist->SetLineColor(kRed);
  eTXDataHist->Draw("SAMESE1"); eTXMCHist->SetLineColor(kBlue);

  gStyle->SetOptFit();
  Canvas->Update();
  TPaveStats *peTX = (TPaveStats*)eTXMCHist->FindObject("stats");
  peTX->SetY1NDC(0.05);
  peTX->SetY2NDC(0.25);
  Canvas->Modified();

  auto legendTX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTX->SetHeader("Histogram Legend","C");
  legendTX->AddEntry(eTXDataHist,"Data","f");
  legendTX->AddEntry(eTXMCHist,"MonteCarlo","f");
  legendTX->Draw();

  Canvas->Print( "histogram.pdf","pdf");

  eTYMCHist->Scale(eTYDataHist->Integral()/eTYMCHist->Integral());

  //eTYMCHist->Scale(1./eTYMCHist->Integral());
  //eTYDataHist->Scale(1./eTYDataHist->Integral());

  eTYMCHist->Draw("HIST"); eTYDataHist->SetLineColor(kRed);
  eTYDataHist->Draw("SAMESE1"); eTYMCHist->SetLineColor(kBlue);

  gStyle->SetOptFit();
  Canvas->Update();
  TPaveStats *peTY = (TPaveStats*)eTYMCHist->FindObject("stats");
  peTY->SetY1NDC(0.05);
  peTY->SetY2NDC(0.25);
  Canvas->Modified();

  auto legendTY = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTY->SetHeader("Histogram Legend","C");
  legendTY->AddEntry(eTYDataHist,"Data","f");
  legendTY->AddEntry(eTYMCHist,"MonteCarlo","f");
  legendTY->Draw();

  Canvas->Print( "histogram.pdf","pdf");

  eT2MCHist->Scale(eT2DataHist->Integral()/eT2MCHist->Integral());

  eT2MCHist->Draw("HIST"); eT2DataHist->SetLineColor(kRed);
  eT2DataHist->Draw("SAMESE1"); eT2MCHist->SetLineColor(kBlue);

  gStyle->SetOptFit();
  Canvas->Update();
  TPaveStats *peT2 = (TPaveStats*)eT2MCHist->FindObject("stats");
  peT2->SetY1NDC(0.05);
  peT2->SetY2NDC(0.25);
  Canvas->Modified();

  auto legendT2 = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendT2->SetHeader("Histogram Legend","C");
  legendT2->AddEntry(eT2DataHist,"Data","f");
  legendT2->AddEntry(eT2MCHist,"MonteCarlo","f");
  legendT2->Draw();

  Canvas->Print( "histogram.pdf","pdf");

  Canvas->Print( "histogram.pdf]","pdf");

}
