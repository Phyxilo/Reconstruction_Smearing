#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

#include "TPaveStats.h"
#include "TPaveText.h"
#include "TText.h"
#include "TPavesText.h"

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *SlpTXHist1 = new TH1F("SlpTXHist1","X Slope",50,-0.4,0.4);
TH1F *SlpTXHist2 = new TH1F("SlpTXHist2","X Slope",50,-0.4,0.4);
TH1F *SlpTXHist3 = new TH1F("SlpTXHist3","X Slope",50,-0.4,0.4);

TH1F *SlpTYHist1 = new TH1F("SlpTYHist1","Y Slope",50,-0.4,0.4);
TH1F *SlpTYHist2 = new TH1F("SlpTYHist2","Y Slope",50,-0.4,0.4);
TH1F *SlpTYHist3 = new TH1F("SlpTYHist3","Y Slope",50,-0.4,0.4);

TH1F *SlpT2Hist1 = new TH1F("SlpT2Hist1","Space Angle",50,0,0.5);
TH1F *SlpT2Hist2 = new TH1F("SlpT2Hist2","Space Angle",50,0,0.5);
TH1F *SlpT2Hist3 = new TH1F("SlpT2Hist3","Space Angle",50,0,0.5);

TH1F *IPData1 = new TH1F("IPData1","Impact Parameter",50,0,30);
TH1F *IPData2 = new TH1F("IPData2","Impact Parameter",50,0,30);
TH1F *IPData3 = new TH1F("IPData3","Impact Parameter",50,0,30);

TH1F *Mult1 = new TH1F("Mult1","Multiplicity",50,0,50);
TH1F *Mult2 = new TH1F("Mult2","Multiplicity",50,0,50);
TH1F *Mult3 = new TH1F("Mult3","Multiplicity",50,0,50);

TH1F *VX1 = new TH1F("VX1","Vertex X",100,10000,140000);
TH1F *VX2 = new TH1F("VX2","Vertex X",100,10000,140000);
TH1F *VX3 = new TH1F("VX3","Vertex X",100,10000,140000);

TH1F *VY1 = new TH1F("VY1","Vertex Y",100,10000,110000);
TH1F *VY2 = new TH1F("VY2","Vertex Y",100,10000,110000);
TH1F *VY3 = new TH1F("VY3","Vertex Y",100,10000,110000);

TH1F *VZ1 = new TH1F("VZ1","Vertex Z",100,1000,6500);
TH1F *VZ2 = new TH1F("VZ2","Vertex Z",100,1000,6500);
TH1F *VZ3 = new TH1F("VZ3","Vertex Z",100,1000,6500);

TH2F *VXY1 = new TH2F("VXY1","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY2 = new TH2F("VXY2","Vertex X vs Y",100,10000,90000,100,10000,90000);
TH2F *VXY3 = new TH2F("VXY3","Vertex X vs Y",100,10000,90000,100,10000,90000);

TFile *Data1, *Data2, *Data3, *DataRaw1, *DataRaw2, *DataRaw3;

int Data1VtxSize, Data2VtxSize, Data3VtxSize;

void MCComp()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  Data1 = TFile::Open("Multip/20210616_PD04.root");
  Data2 = TFile::Open("Multip/20220610_PD04.root");
  Data3 = TFile::Open("Multip/20220622_PD04.root");

  DataRaw1 = TFile::Open("Raw/20210616_PD04.root");
  DataRaw2 = TFile::Open("Raw/20220610_PD04.root");
  DataRaw3 = TFile::Open("Raw/20220622_PD04.root");

  TTree *treeDataTrk1 = (TTree*)Data1->Get("TRK");
  TTree *treeDataTrk2 = (TTree*)Data2->Get("TRK");
  TTree *treeDataTrk3 = (TTree*)Data3->Get("TRK");

  TTree *treeDataVtx1 = (TTree*)Data1->Get("VTX");
  TTree *treeDataVtx2 = (TTree*)Data2->Get("VTX");
  TTree *treeDataVtx3 = (TTree*)Data3->Get("VTX");

  TTree *treeDataVtxRaw1 = (TTree*)DataRaw1->Get("VTX");
  TTree *treeDataVtxRaw2 = (TTree*)DataRaw2->Get("VTX");
  TTree *treeDataVtxRaw3 = (TTree*)DataRaw3->Get("VTX");

  Data1VtxSize = treeDataVtx1->GetEntriesFast();
  Data2VtxSize = treeDataVtx2->GetEntriesFast();
  Data3VtxSize = treeDataVtx3->GetEntriesFast();

  for (int i = 0; i < treeDataTrk1->GetEntriesFast(); i++)
  {
    treeDataTrk1->GetEntry(i);
    
    TLeaf *slpTX = treeDataTrk1->GetLeaf("SlpTX");
    TLeaf *slpTY = treeDataTrk1->GetLeaf("SlpTY");
    //TLeaf *slpT2 = treeDataTrk1->GetLeaf("SlpT2");
    TLeaf *beamTX = treeDataTrk1->GetLeaf("BeamTX");
    TLeaf *beamTY = treeDataTrk1->GetLeaf("BeamTY");
    TLeaf *IP = treeDataTrk1->GetLeaf("ImpactPar");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();
    
    SlpTXHist1->Fill(TX);
    SlpTYHist1->Fill(TY);
    //SlpT2Hist1->Fill(slpT2->GetValue());
    SlpT2Hist1->Fill(sqrt(TX*TX+TY*TY));
    IPData1->Fill(IP->GetValue());
  }

  for (int i = 0; i < treeDataTrk2->GetEntriesFast(); i++)
  {
    treeDataTrk2->GetEntry(i);

    TLeaf *slpTX = treeDataTrk2->GetLeaf("SlpTX");
    TLeaf *slpTY = treeDataTrk2->GetLeaf("SlpTY");
    //TLeaf *slpT2 = treeDataTrk2->GetLeaf("SlpT2");
    TLeaf *beamTX = treeDataTrk2->GetLeaf("BeamTX");
    TLeaf *beamTY = treeDataTrk2->GetLeaf("BeamTY");
    TLeaf *IP = treeDataTrk2->GetLeaf("ImpactPar");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    SlpTXHist2->Fill(TX);
    SlpTYHist2->Fill(TY);
    //SlpT2Hist2->Fill(slpT2->GetValue());
    SlpT2Hist2->Fill(sqrt(TX*TX+TY*TY));
    IPData2->Fill(IP->GetValue());
  }

  for (int i = 0; i < treeDataTrk3->GetEntriesFast(); i++)
  {
    treeDataTrk3->GetEntry(i);

    TLeaf *slpTX = treeDataTrk3->GetLeaf("SlpTX");
    TLeaf *slpTY = treeDataTrk3->GetLeaf("SlpTY");
    TLeaf *slpT2 = treeDataTrk3->GetLeaf("SlpT2");
    TLeaf *beamTX = treeDataTrk3->GetLeaf("BeamTX");
    TLeaf *beamTY = treeDataTrk3->GetLeaf("BeamTY");
    TLeaf *IP = treeDataTrk3->GetLeaf("ImpactPar");

    double TX = slpTX->GetValue() - beamTX->GetValue();
    double TY = slpTY->GetValue() - beamTY->GetValue();

    SlpTXHist3->Fill(TX);
    SlpTYHist3->Fill(TY);
    //SlpT2Hist3->Fill(slpT2->GetValue());
    SlpT2Hist3->Fill(sqrt(TX*TX+TY*TY));
    IPData3->Fill(IP->GetValue());
  }

  for (int i = 0; i < Data1VtxSize; i++)
  {
    treeDataVtx1->GetEntry(i);
    treeDataVtxRaw1->GetEntry(i);

    TLeaf *mult = treeDataVtx1->GetLeaf("Multip");
    TLeaf *VX = treeDataVtxRaw1->GetLeaf("vx");
    TLeaf *VY = treeDataVtxRaw1->GetLeaf("vy");
    TLeaf *VZ = treeDataVtxRaw1->GetLeaf("vz");

    Mult1->Fill(mult->GetValue());
    VX1->Fill(VX->GetValue());
    VY1->Fill(VY->GetValue());
    VZ1->Fill(VZ->GetValue());

    //VXY1->Fill(VX->GetValue(), VY->GetValue());
  }

  for (int i = 0; i < Data2VtxSize; i++)
  {
    treeDataVtx2->GetEntry(i);
    treeDataVtxRaw2->GetEntry(i);

    TLeaf *mult = treeDataVtx2->GetLeaf("Multip");
    TLeaf *VX = treeDataVtxRaw2->GetLeaf("vx");
    TLeaf *VY = treeDataVtxRaw2->GetLeaf("vy");
    TLeaf *VZ = treeDataVtxRaw2->GetLeaf("vz");

    Mult2->Fill(mult->GetValue());
    VX2->Fill(VX->GetValue());
    VY2->Fill(VY->GetValue());
    VZ2->Fill(VZ->GetValue());

    //VXY2->Fill(VX->GetValue(), VY->GetValue());
    
  }

  for (int i = 0; i < Data3VtxSize; i++)
  {
    treeDataVtx3->GetEntry(i);
    treeDataVtxRaw3->GetEntry(i);

    TLeaf *mult = treeDataVtx3->GetLeaf("Multip");
    TLeaf *VX = treeDataVtxRaw3->GetLeaf("vx");
    TLeaf *VY = treeDataVtxRaw3->GetLeaf("vy");
    TLeaf *VZ = treeDataVtxRaw3->GetLeaf("vz");

    Mult3->Fill(mult->GetValue());
    VX3->Fill(VX->GetValue());
    VY3->Fill(VY->GetValue());
    VZ3->Fill(VZ->GetValue());
    
    //VXY3->Fill(VX->GetValue(), VY->GetValue());
  }

  
  SlpTXHist2->Scale(Data1VtxSize/Data2VtxSize);
  SlpTXHist3->Scale(Data1VtxSize/Data3VtxSize);

  SlpTYHist2->Scale(Data1VtxSize/Data2VtxSize);
  SlpTYHist3->Scale(Data1VtxSize/Data3VtxSize);

  SlpT2Hist2->Scale(Data1VtxSize/Data2VtxSize);
  SlpT2Hist3->Scale(Data1VtxSize/Data3VtxSize);

  IPData2->Scale(Data1VtxSize/Data2VtxSize);
  IPData3->Scale(Data1VtxSize/Data3VtxSize);

  Mult2->Scale(Data1VtxSize/Data2VtxSize);
  Mult3->Scale(Data1VtxSize/Data3VtxSize);

  VX2->Scale(Data1VtxSize/Data2VtxSize);
  VX3->Scale(Data1VtxSize/Data3VtxSize);

  VY2->Scale(Data1VtxSize/Data2VtxSize);
  VY3->Scale(Data1VtxSize/Data3VtxSize);

  VZ2->Scale(Data1VtxSize/Data2VtxSize);
  VZ3->Scale(Data1VtxSize/Data3VtxSize);

  SlpTXHist1->GetYaxis()->SetRangeUser(0, 200000); 
  
  SlpTXHist1->Draw("HIST"); SlpTXHist1->SetLineColor(kBlue); SlpTXHist1->SetLineStyle(1); SlpTXHist1->SetLineWidth(2);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *statBoxSlpTX1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxSlpTX1->SetName("SlpTXHist1");
  statBoxSlpTX1->SetY1NDC(0.9);
  statBoxSlpTX1->SetY2NDC(0.7);
  statBoxSlpTX1->SetTextColor(kBlue);
  statBoxSlpTX1->Draw();

  SlpTXHist2->Draw("SAMES HIST"); SlpTXHist2->SetLineColor(kRed); SlpTXHist2->SetLineStyle(2); SlpTXHist2->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxSlpTX2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxSlpTX2->SetName("SlpTXHist2");
  statBoxSlpTX2->SetY1NDC(0.6);
  statBoxSlpTX2->SetY2NDC(0.4);
  statBoxSlpTX2->SetTextColor(kRed);
  statBoxSlpTX2->Draw();

  SlpTXHist3->Draw("SAMES HIST"); SlpTXHist3->SetLineColor(kBlack); SlpTXHist3->SetLineStyle(kDotted); SlpTXHist3->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxSlpTX3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxSlpTX3->SetName("SlpTXHist3");
  statBoxSlpTX3->SetY1NDC(0.3);
  statBoxSlpTX3->SetY2NDC(0.1);
  statBoxSlpTX3->SetTextColor(kBlack);
  statBoxSlpTX3->Draw();

  TLegend *legendTX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTX->SetHeader("Histogram Legend","C");
  legendTX->AddEntry(SlpTXHist1,"Data1","f");
  legendTX->AddEntry(SlpTXHist2,"Data2","f");
  legendTX->AddEntry(SlpTXHist3,"Data3","f");
  legendTX->Draw();

  Canvas->Print( "DataCompHist.pdf(", "pdf");

  SlpTYHist1->GetYaxis()->SetRangeUser(0, 200000);

  SlpTYHist1->Draw("HIST"); SlpTYHist1->SetLineColor(kBlue); SlpTYHist1->SetLineStyle(1); SlpTYHist1->SetLineWidth(2);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *statBoxSlpTY1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxSlpTY1->SetName("SlpTYHist1");
  statBoxSlpTY1->SetY1NDC(0.9);
  statBoxSlpTY1->SetY2NDC(0.7);
  statBoxSlpTY1->SetTextColor(kBlue);
  statBoxSlpTY1->Draw();

  SlpTYHist2->Draw("SAMES HIST"); SlpTYHist2->SetLineColor(kRed); SlpTYHist2->SetLineStyle(2); SlpTYHist2->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxSlpTY2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxSlpTY2->SetName("SlpTYHist2");
  statBoxSlpTY2->SetY1NDC(0.6);
  statBoxSlpTY2->SetY2NDC(0.4);
  statBoxSlpTY2->SetTextColor(kRed);
  statBoxSlpTY2->Draw();

  SlpTYHist3->Draw("SAMES HIST"); SlpTYHist3->SetLineColor(kBlack); SlpTYHist3->SetLineStyle(kDotted); SlpTYHist3->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxSlpTY3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxSlpTY3->SetName("SlpTYHist3");
  statBoxSlpTY3->SetY1NDC(0.3);
  statBoxSlpTY3->SetY2NDC(0.1);
  statBoxSlpTY3->SetTextColor(kBlack);
  statBoxSlpTY3->Draw();
  
  TLegend *legendTY = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTY->SetHeader("Histogram Legend","C");
  legendTY->AddEntry(SlpTYHist1,"Data1","f");
  legendTY->AddEntry(SlpTYHist2,"Data2","f");
  legendTY->AddEntry(SlpTYHist3,"Data3","f");
  legendTY->Draw();

  Canvas->Print( "DataCompHist.pdf", "pdf");

  SlpT2Hist1->GetYaxis()->SetRangeUser(0, 150000);
  
  SlpT2Hist1->Draw("HIST"); SlpT2Hist1->SetLineColor(kBlue); SlpT2Hist1->SetLineStyle(1); SlpT2Hist1->SetLineWidth(2);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *statBoxSlpT21 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxSlpT21->SetName("SlpT2Hist1");
  statBoxSlpT21->SetY1NDC(0.9);
  statBoxSlpT21->SetY2NDC(0.7);
  statBoxSlpT21->SetTextColor(kBlue);
  statBoxSlpT21->Draw();

  SlpT2Hist2->Draw("SAMES HIST"); SlpT2Hist2->SetLineColor(kRed); SlpT2Hist2->SetLineStyle(2); SlpT2Hist2->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxSlpT22 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxSlpT22->SetName("SlpT2Hist2");
  statBoxSlpT22->SetY1NDC(0.6);
  statBoxSlpT22->SetY2NDC(0.4);
  statBoxSlpT22->SetTextColor(kRed);
  statBoxSlpT22->Draw();

  SlpT2Hist3->Draw("SAMES HIST"); SlpT2Hist3->SetLineColor(kBlack); SlpT2Hist3->SetLineStyle(kDotted); SlpT2Hist3->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxSlpT23 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxSlpT23->SetName("SlpT2Hist3");
  statBoxSlpT23->SetY1NDC(0.3);
  statBoxSlpT23->SetY2NDC(0.1);
  statBoxSlpT23->SetTextColor(kBlack);
  statBoxSlpT23->Draw();

  TLegend *legendT2 = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendT2->SetHeader("Histogram Legend","C");
  legendT2->AddEntry(SlpT2Hist1,"Data1","f");
  legendT2->AddEntry(SlpT2Hist2,"Data2","f");
  legendT2->AddEntry(SlpT2Hist3,"Data3","f");
  legendT2->Draw();

  Canvas->Print( "DataCompHist.pdf", "pdf");

  IPData1->GetYaxis()->SetRangeUser(0, 450000);

  IPData1->Draw("HIST"); IPData1->SetLineColor(kBlue); IPData1->SetLineStyle(1); IPData1->SetLineWidth(2);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *statBoxIP1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxIP1->SetName("IPData1");
  statBoxIP1->SetY1NDC(0.9);
  statBoxIP1->SetY2NDC(0.7);
  statBoxIP1->SetTextColor(kBlue);
  statBoxIP1->Draw();

  IPData2->Draw("SAMES HIST"); IPData2->SetLineColor(kRed); IPData2->SetLineStyle(2); IPData2->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxIP2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxIP2->SetName("IPData2");
  statBoxIP2->SetY1NDC(0.6);
  statBoxIP2->SetY2NDC(0.4);
  statBoxIP2->SetTextColor(kRed);
  statBoxIP2->Draw();

  IPData3->Draw("SAMES HIST"); IPData3->SetLineColor(kBlack); IPData3->SetLineStyle(kDotted); IPData3->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxIP3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxIP3->SetName("IPData3");
  statBoxIP3->SetY1NDC(0.3);
  statBoxIP3->SetY2NDC(0.1);
  statBoxIP3->SetTextColor(kBlack);
  statBoxIP3->Draw();
  
  TLegend *legendIP = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendIP->SetHeader("Histogram Legend","C");
  legendIP->AddEntry(IPData1,"Data1","f");
  legendIP->AddEntry(IPData2,"Data2","f");
  legendIP->AddEntry(IPData3,"Data3","f");
  legendIP->Draw();

  Canvas->Print( "DataCompHist.pdf", "pdf");

  Mult1->GetYaxis()->SetRangeUser(0, 5000);

  Mult1->Draw("HIST"); Mult1->SetLineColor(kBlue); Mult1->SetLineStyle(1); Mult1->SetLineWidth(2);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *statBoxMult1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxMult1->SetName("Mult1");
  statBoxMult1->SetY1NDC(0.9);
  statBoxMult1->SetY2NDC(0.7);
  statBoxMult1->SetTextColor(kBlue);
  statBoxMult1->Draw();

  Mult2->Draw("SAMES HIST"); Mult2->SetLineColor(kRed); Mult2->SetLineStyle(2); Mult2->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxMult2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxMult2->SetName("Mult2");
  statBoxMult2->SetY1NDC(0.6);
  statBoxMult2->SetY2NDC(0.4);
  statBoxMult2->SetTextColor(kRed);
  statBoxMult2->Draw();

  Mult3->Draw("SAMES HIST"); Mult3->SetLineColor(kBlack); Mult3->SetLineStyle(kDotted); Mult3->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxMult3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxMult3->SetName("Mult3");
  statBoxMult3->SetY1NDC(0.3);
  statBoxMult3->SetY2NDC(0.1);
  statBoxMult3->SetTextColor(kBlack);
  statBoxMult3->Draw();
  
  TLegend *legendMl = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendMl->SetHeader("Histogram Legend","C");
  legendMl->AddEntry(Mult1,"Data1","f");
  legendMl->AddEntry(Mult2,"Data2","f");
  legendMl->AddEntry(Mult3,"Data3","f");
  legendMl->Draw();

  Canvas->Print( "DataCompHist.pdf", "pdf");

  VX1->GetYaxis()->SetRangeUser(0, 900);

  VX1->Draw("HIST"); VX1->SetLineColor(kBlue); VX1->SetLineStyle(1); VX1->SetLineWidth(2);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *statBoxVX1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxVX1->SetName("VX1");
  statBoxVX1->SetY1NDC(0.9);
  statBoxVX1->SetY2NDC(0.7);
  statBoxVX1->SetTextColor(kBlue);
  statBoxVX1->Draw();

  VX2->Draw("SAMES HIST"); VX2->SetLineColor(kRed); VX2->SetLineStyle(2); VX2->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxVX2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxVX2->SetName("VX2");
  statBoxVX2->SetY1NDC(0.6);
  statBoxVX2->SetY2NDC(0.4);
  statBoxVX2->SetTextColor(kRed);
  statBoxVX2->Draw();

  VX3->Draw("SAMES HIST"); VX3->SetLineColor(kBlack); VX3->SetLineStyle(kDotted); VX3->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxVX3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxVX3->SetName("VX3");
  statBoxVX3->SetY1NDC(0.3);
  statBoxVX3->SetY2NDC(0.1);
  statBoxVX3->SetTextColor(kBlack);
  statBoxVX3->Draw();
  
  TLegend *legendVX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendVX->SetHeader("Histogram Legend","C");
  legendVX->AddEntry(VX1,"Data1","f");
  legendVX->AddEntry(VX2,"Data2","f");
  legendVX->AddEntry(VX3,"Data3","f");
  legendVX->Draw();

  Canvas->Print( "DataCompHist.pdf", "pdf");

  VY1->GetYaxis()->SetRangeUser(0, 900);

  VY1->Draw("HIST"); VY1->SetLineColor(kBlue); VY1->SetLineStyle(1); VY1->SetLineWidth(2);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *statBoxVY1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxVY1->SetName("VY1");
  statBoxVY1->SetY1NDC(0.9);
  statBoxVY1->SetY2NDC(0.7);
  statBoxVY1->SetTextColor(kBlue);
  statBoxVY1->Draw();

  VY2->Draw("SAMES HIST"); VY2->SetLineColor(kRed); VY2->SetLineStyle(2); VY2->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxVY2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxVY2->SetName("VY2");
  statBoxVY2->SetY1NDC(0.6);
  statBoxVY2->SetY2NDC(0.4);
  statBoxVY2->SetTextColor(kRed);
  statBoxVY2->Draw();

  VY3->Draw("SAMES HIST"); VY3->SetLineColor(kBlack); VY3->SetLineStyle(kDotted); VY3->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxVY3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxVY3->SetName("VY3");
  statBoxVY3->SetY1NDC(0.3);
  statBoxVY3->SetY2NDC(0.1);
  statBoxVY3->SetTextColor(kBlack);
  statBoxVY3->Draw();
  
  TLegend *legendVY = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendVY->SetHeader("Histogram Legend","C");
  legendVY->AddEntry(VY1,"Data1","f");
  legendVY->AddEntry(VY2,"Data2","f");
  legendVY->AddEntry(VY3,"Data3","f");
  legendVY->Draw();

  Canvas->Print( "DataCompHist.pdf", "pdf");

  VZ1->GetYaxis()->SetRangeUser(0, 5000);

  VZ1->Draw("HIST"); VZ1->SetLineColor(kBlue); VZ1->SetLineStyle(1); VZ1->SetLineWidth(2);

  Canvas->Modified(); Canvas->Update();
  TPaveStats *statBoxVZ1 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxVZ1->SetName("VZ1");
  statBoxVZ1->SetY1NDC(0.9);
  statBoxVZ1->SetY2NDC(0.7);
  statBoxVZ1->SetTextColor(kBlue);
  statBoxVZ1->Draw();

  VZ2->Draw("SAMES HIST"); VZ2->SetLineColor(kRed); VZ2->SetLineStyle(2); VZ2->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxVZ2 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxVZ2->SetName("VZ2");
  statBoxVZ2->SetY1NDC(0.6);
  statBoxVZ2->SetY2NDC(0.4);
  statBoxVZ2->SetTextColor(kRed);
  statBoxVZ2->Draw();

  VZ3->Draw("SAMES HIST"); VZ3->SetLineColor(kBlack); VZ3->SetLineStyle(kDotted); VZ3->SetLineWidth(2);

  Canvas->Update();
  TPaveStats *statBoxVZ3 = (TPaveStats*)Canvas->GetPrimitive("stats");
  statBoxVZ3->SetName("VZ3");
  statBoxVZ3->SetY1NDC(0.3);
  statBoxVZ3->SetY2NDC(0.1);
  statBoxVZ3->SetTextColor(kBlack);
  statBoxVZ3->Draw();
  
  TLegend *legendVZ = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendVZ->SetHeader("Histogram Legend","C");
  legendVZ->AddEntry(VZ1,"Data1","f");
  legendVZ->AddEntry(VZ2,"Data2","f");
  legendVZ->AddEntry(VZ3,"Data3","f");
  legendVZ->Draw();

  /*
  Canvas->Print( "DataCompHist.pdf", "pdf");

  VXY1->SetXTitle("vx");
  VXY1->SetYTitle("vy");
  VXY1->SetFillColor(5);
  VXY1->Draw("coltz");

  Canvas->Print( "DataCompHist.pdf", "pdf");

  VXY2->SetXTitle("vx");
  VXY2->SetYTitle("vy");
  VXY2->SetFillColor(5);
  VXY2->Draw("coltz");

  Canvas->Print( "DataCompHist.pdf", "pdf");

  VXY3->SetXTitle("vx");
  VXY3->SetYTitle("vy");
  VXY3->SetFillColor(5);
  VXY3->Draw("coltz");
  */
  Canvas->Print( "DataCompHist.pdf)", "pdf");
}