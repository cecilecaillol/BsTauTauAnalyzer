#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "THStack.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TMath.h"
#include "TLine.h"
#include "tr_Tree.h"



using namespace std;

//this code only plot data/MC comparison with cross section reweighting

int main(int argc, char** argv) {
    gStyle->SetOptStat(0);
    gStyle->SetFrameLineWidth(1);
    gStyle->SetLineWidth(1);
    gStyle->SetOptStat(0);

    
    std::string variable = *(argv + 1);
    double plotmin = atof(*(argv+2));
    double plotmax = atof(*(argv+3));
    int log = atoi(*(argv+4));

    cout << "Try to compare data/MC of variable " << variable << endl;
    cout << "Plot minimum is " << plotmin << endl;
    cout << "Plot maximum is " << plotmax << endl;
    cout << "log scale " << log << endl;



    vector<string> allsamplename = {"DYJetsToLL_M-50","WJetsToLNu","TTTo2L2Nu","TTToHadronic","TTToSemiLeptonic","WW","WZ","ZZTo2L2Nu",
        "ZZTo2Q2L_mllmin4p0","ZZTo4L","ST_t-channel_antitop_5f_InclusiveDecays","ST_t-channel_top_4f_InclusiveDecays","ST_tW_top_5f_inclusiveDecays",
        "ST_tW_antitop_5f_inclusiveDecays"};

    //vector<string> cate = {"DY","WJets","TT","Others"};
    //int catenumber[4][2] = {{0,0},{1,1},{2,4},{5,13}};
    vector<string> cate = {"Others","TT","WJets","DY"};
    int catenumber[4][2] = {{5,13},{2,4},{1,1},{0,0}};
    vector<Color_t> color = {kRed,kBlue,kGreen,kCyan+2};

    TChain *datantuple = new TChain("Events","datatuple");
    datantuple->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/nanoplots/mutau/data*.root");
    TH1F *hdata = new TH1F("hdata","",40,plotmin,plotmax);
    datantuple->Draw(Form("%s>>hdata",variable.c_str()),"","goff");
    int DataEntries = datantuple->GetEntries();
    cout << "Entry of data is " << DataEntries << endl; 
    vector<TChain> bkgMCntuple;
    vector<TH1F*> bkgMChis(cate.size());
    cout << "bkgMChis.size " << bkgMChis.size() << endl;
    THStack *hsMC = new THStack("hsMC","");

    /*double bkgMCentries=0;
    for (unsigned int i=0; i < allsamplename.size(); i++){
        double xsweight;
        TChain t("Events");
        t.Add(("/afs/cern.ch/user/x/xuqin/eos/taug-2/nanoplots/mutau/" + allsamplename[i] + ".root").c_str());
        t.SetBranchAddress("xsweight",&xsweight);
        t.GetEntry(i);
        cout << "sample is " << allsamplename[i] << " Entries is " << xsweight*t.GetEntries() << endl;
        bkgMCentries += xsweight*t.GetEntries();
        TH1F *hMC = new TH1F(Form("h%s",allsamplename[i].c_str()),"",40,plotmin,plotmax);
        t.Draw(Form("%s>>h%s",variable.c_str(),allsamplename[i].c_str()),"xsweight","goff");
        bkgMChis.push_back(hMC);
        hsMC->Add(hMC);
    }
    cout << "Total entries of MC " << bkgMCentries << endl;
    */

    //return 0;
    TH1F *hratio = new TH1F("hratio","",40,plotmin,plotmax);

    for (unsigned int i=0; i < cate.size(); i++){
        TChain t("Events");
        for (int j = catenumber[i][0];j <= catenumber[i][1]; j++){
            cout << "j= " << j << endl;
            t.Add(("/afs/cern.ch/user/x/xuqin/eos/taug-2/nanoplots/mutau/" + allsamplename[j] + ".root").c_str());
        }
        cout << "xixi" << endl;
        bkgMChis[i]=new TH1F(Form("h%s",cate[i].c_str()),"",40,plotmin,plotmax);
        //bkgMChis[i]->SetName(Form("h%s",cate[i].c_str()));
        //bkgMChis[i]->SetBins(40,plotmin,plotmax);
        cout<< "xixi" << endl;   

        //TH1F *hMC = new TH1F(Form("h%s",cate[i].c_str()),"",40,plotmin,plotmax);
        t.Draw(Form("%s>>h%s",variable.c_str(),cate[i].c_str()),"xsweight","goff");  
        cout<< "xixi" << endl;   
        //bkgMChis.push_back(hMC);
        bkgMChis[i]->SetFillColor(color[i]);
        hsMC->Add(bkgMChis[i]);       
    }
    cout << "xuxu" << endl;
    for (unsigned int i=1; i <= 40; i++){
        double valuedata = hdata->GetBinContent(i);
        double valueMC = 0.;
        for (unsigned int j=0; j < cate.size(); j++){
            valueMC+=bkgMChis[j]->GetBinContent(i);
        }
        double ratio=0;
        if (valueMC!=0){
        ratio = valuedata/valueMC;
        }
        hratio->SetBinContent(i,ratio);
        hratio->SetBinError(i,0);
        cout<< "value of " << i << " is " << hratio->GetBinContent(i) << endl;
    }
    cout << "xuxu" << endl;
    TCanvas *c = new TCanvas("c","",800,600);
    TPad* pad1 = new TPad("pad1","pad1",0,0.30,1,1);
    pad1->Draw();
    pad1->cd();
    pad1->SetFillColor(0);
    pad1->SetBorderMode(0);
    pad1->SetBorderSize(10);
    pad1->SetTickx(1);
    pad1->SetTicky(1);
    pad1->SetLeftMargin(0.10);
    pad1->SetRightMargin(0.05);
    pad1->SetTopMargin(0.122);
    pad1->SetBottomMargin(0.026);
    pad1->SetFrameFillStyle(0);
    pad1->SetFrameLineStyle(0);
    pad1->SetFrameLineWidth(2);
    pad1->SetFrameBorderMode(0);
    pad1->SetFrameBorderSize(10);
    if (log==1){
        pad1->SetLogy();
    }
    //gPad->SetLeftMargin(0.12);
    hdata->GetXaxis()->SetLabelSize(0);
    hdata->GetXaxis()->SetTitle(variable.c_str());
    hdata->GetXaxis()->SetNdivisions(505);
    hdata->GetYaxis()->SetLabelFont(42);
    hdata->GetYaxis()->SetLabelOffset(0.01);
    hdata->GetYaxis()->SetLabelSize(0.06);
    hdata->GetYaxis()->SetTitleSize(0.07);
    hdata->GetYaxis()->SetTitleOffset(0.7);
    hdata->GetYaxis()->SetTickLength(0.012);
    hdata->SetTitle(variable.c_str());
    hdata->GetYaxis()->SetTitle("Events");
    hdata->SetMarkerStyle(20);
    hdata->SetMarkerSize(1);
    hdata->SetLineWidth(1);
    hdata->Draw("e0p");
    hsMC->Draw("histsame");
    hdata->Draw("e0psame");


    if (variable=="taumudelphi"){
        TLegend *leg = new TLegend(0.4,0.55,0.6,0.85);
        leg->AddEntry(hdata, "data", "epl");
        for (int i=cate.size()-1; i>= 0; i--){
            leg->AddEntry(bkgMChis[i], cate[i].c_str(), "f");
        }
        leg->Draw();
    }
    else {
        TLegend *leg = new TLegend(0.7,0.55,0.9,0.85);
        leg->AddEntry(hdata, "data", "epl");
        for (int i=cate.size()-1; i>= 0; i--){
            leg->AddEntry(bkgMChis[i], cate[i].c_str(), "f");
        }
        leg->Draw();
    }

    c->cd();
    TPad* pad2 = new TPad("pad2","pad2",0,0.0,1,0.3);
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.15);
    pad2->SetLeftMargin(0.10);
    pad2->SetRightMargin(0.05);
    pad2->SetTickx(1);
    pad2->SetTicky(1);
    pad2->SetFrameLineWidth(2);
    //pad2.SetGridx()
    pad2->SetGridy();
    pad2->Draw();
    pad2->cd();


    hratio->SetMaximum(1.6);
    hratio->SetMinimum(0.6);

    hratio->GetXaxis()->SetLabelSize(0.07);
    hratio->GetYaxis()->SetLabelSize(0.08);
    hratio->GetYaxis()->SetTickLength(0.012);
    //hratio->GetYaxis()->SetTitle("#frac{(Obs.-Bkg.)}{#sqrt{Bkg.}}")
    hratio->GetYaxis()->SetTitle("#frac{Obs.}{Exp.}");
    hratio->GetYaxis()->SetNdivisions(5);
    
    hratio->GetXaxis()->SetTitleSize(0.15);
    hratio->GetYaxis()->SetTitleSize(0.10);
    hratio->GetYaxis()->SetTitleOffset(0.4);
    hratio->GetXaxis()->SetTitleOffset(1.65);
    hratio->GetXaxis()->SetLabelSize(0.09);
    hratio->GetXaxis()->SetTitle(variable.c_str());
    hratio->SetMarkerSize(1);
    hratio->SetMarkerStyle(20);
    hratio->SetLineWidth(1);
    hratio->Draw("e0p");
    //hratio->LabelsOption("v","X");

    TLine *line = new TLine(hratio->GetXaxis()->GetXmin(),1,hratio->GetXaxis()->GetXmax(), 1);
    line->SetLineStyle(3);
    line->Draw();

    c->SaveAs(Form("Plotsmutau/%s_log%d.png",variable.c_str(),log));
    //TChain *DYtuple = new TChain("Events");
    //cout << "Entry of MC is " << bkgMCentries << endl;




}

