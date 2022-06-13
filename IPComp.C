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

TH1F *IPData = new TH1F("IPData","Impact Parameter Histogram",25,0,1500);
TH1F *IPMC = new TH1F("IPMC","Impact Parameter Histogram",25,0,1500);

TFile *data, *monteCarlo;

vector<float> dataList, MCList;

void IPComp()
{
  Canvas->SetWindowSize(1920, 1080);
  Canvas->SetCanvasSize(192*6, 108*6);

  data = TFile::Open("Vertexing/ImpactParameter/vertexingIPData.root");
  monteCarlo = TFile::Open("Vertexing/ImpactParameter/vertexingIPMC.root");

  TTree *treeData = (TTree*)data->Get("TRK");
  TTree *treeMC = (TTree*)monteCarlo->Get("TRK");

  TLeaf *dataIP = treeData->GetLeaf("ImpactPar");
  TLeaf *MCIP = treeMC->GetLeaf("ImpactPar");

  float ipDt, ipMC;

  for (int i = 0; i < treeData->GetEntriesFast(); i++)
  {
    treeData->GetEntry(i);

    ipDt = dataIP->GetValue();
    IPData->Fill(ipDt);
    dataList.push_back(ipDt);
  }
  for (int i = 0; i < treeMC->GetEntriesFast(); i++)
  {
    treeMC->GetEntry(i);

    ipMC = MCIP->GetValue();
    IPMC->Fill(ipMC);
    MCList.push_back(ipMC);
  }

  sort(dataList.begin(), dataList.end());
  dataList.erase(unique(dataList.begin(), dataList.end()), dataList.end());

  sort(MCList.begin(), MCList.end());
  MCList.erase(unique(MCList.begin(), MCList.end()), MCList.end());

  IPMC->Scale(dataList.size()/MCList.size());

  IPData->Draw("HIST E1"); IPData->SetLineColor(kRed);
  IPMC->Draw("SAME HIST"); IPMC->SetLineColor(kBlue);

  IPData->GetYaxis()->SetRangeUser(0, 500000);

  auto legendTX = new TLegend(0.1, 0.8, 0.32, 0.9);
  legendTX->SetHeader("Histogram Legend","C");
  legendTX->AddEntry(IPData,"Data","f");
  legendTX->AddEntry(IPMC,"MonteCarlo","f");
  legendTX->Draw();

  Canvas->Print( "IPCompHist.pdf", "pdf");
}