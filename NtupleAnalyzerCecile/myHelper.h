#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TMath.h" //M_PI is in TMath
#include "TRandom3.h"
#include <TLorentzVector.h>

float GetMuRecoSF(std::string year, float eta){
    float sf=1.0;
    if (year=="2016pre"){
	if (fabs(eta)<0.9) sf=0.9998229551300333;
	else if (fabs(eta)<1.2) sf=1.0001593416915515;
	else if (fabs(eta)<2.1) sf=0.9998936144006075;
	else if (fabs(eta)<2.4) sf=0.9990268820042745;
    }
    else if (year=="2016post"){
        if (fabs(eta)<0.9) sf=1.0000406419782646;
        else if (fabs(eta)<1.2) sf=0.9997959311146515;
        else if (fabs(eta)<2.1) sf=0.9994928400570587;
        else if (fabs(eta)<2.4) sf=0.9990728619505579;
    }
    else if (year=="2017"){
        if (fabs(eta)<0.9) sf=0.9996742562806361;
        else if (fabs(eta)<1.2) sf=0.9997813602035737;
        else if (fabs(eta)<2.1) sf=0.9994674742459532;
        else if (fabs(eta)<2.4) sf=0.9993566412630517;
    }
    else if (year=="2018"){
        if (fabs(eta)<0.9) sf=0.9998088006315689;
        else if (fabs(eta)<1.2) sf=0.999754701980269;
        else if (fabs(eta)<2.1) sf=0.9995842791862117;
        else if (fabs(eta)<2.4) sf=0.9990341741614288;
    }
    return sf;
}


float TMass_F(float pt3lep, float px3lep, float py3lep, float met, float metPhi) {
    return sqrt(pow(pt3lep + met, 2) - pow(px3lep + met * cos(metPhi), 2) - pow(py3lep + met * sin(metPhi), 2));
}


void WriteHistToFileETau(TFile* myfile, std::vector<TH1F*> hist, std::string name, TString dir_name, TString uncertainties[55], TString fake_uncertainties[42], bool isMC, int nbhist, int nbhist_offset, bool write_uncertainties){
    TString postfix="";
    TDirectory *dir =myfile->mkdir(dir_name);
    dir->cd();
    if (!write_uncertainties) nbhist=1;
    for (int k=0; k<nbhist; ++k){
       for (int j=0; j<hist[k]->GetSize()-1; ++j){
         if (hist[k]->GetBinContent(j)<0) hist[k]->SetBinContent(j,0);
       }
       //include overflow in last bin
       hist[k]->SetBinContent(hist[k]->GetSize()-2,hist[k]->GetBinContent(hist[k]->GetSize()-2)+hist[k]->GetBinContent(hist[k]->GetSize()-1));
       hist[k]->SetBinError(hist[k]->GetSize()-2,pow(hist[k]->GetBinError(hist[k]->GetSize()-2)*hist[k]->GetBinError(hist[k]->GetSize()-2)+hist[k]->GetBinError(hist[k]->GetSize()-1)*hist[k]->GetBinError(hist[k]->GetSize()-1),0.5));
       hist[k]->SetBinContent(hist[k]->GetSize()-1,0);
       hist[k]->SetBinError(hist[k]->GetSize()-1,0);

       if (k<(55-nbhist_offset)) postfix=uncertainties[k];
       else postfix=fake_uncertainties[k-(55-nbhist_offset)];
       hist[k]->SetName(name.c_str()+postfix);
       hist[k]->Write();
    }
}

void WriteHistToFileTauTau(TFile* myfile, std::vector<TH1F*> hist, std::string name, TString dir_name, TString uncertainties[49], TString fake_uncertainties[1], bool isMC, int nbhist, int nbhist_offset, bool write_uncertainties){
    TString postfix="";
    TDirectory *dir =myfile->mkdir(dir_name);
    dir->cd();
    if (!write_uncertainties) nbhist=1;
    for (int k=0; k<nbhist; ++k){
       for (int j=0; j<hist[k]->GetSize()-1; ++j){
         if (hist[k]->GetBinContent(j)<0) hist[k]->SetBinContent(j,0);
       }
       if (k<(49-nbhist_offset)) postfix=uncertainties[k];
       else postfix=fake_uncertainties[k-(49-nbhist_offset)];
       hist[k]->SetName(name.c_str()+postfix);
       hist[k]->Write();
    }
}

void WriteHistToFileMuTau(TFile* myfile, std::vector<TH1F*> hist, std::string name, TString dir_name, TString uncertainties[27], TString fake_uncertainties[1], bool isMC, int nbhist, int nbhist_offset, bool write_uncertainties){
    TString postfix="";
    TDirectory *dir =myfile->mkdir(dir_name);
    dir->cd();
    if (!write_uncertainties) nbhist=1;
    for (int k=0; k<nbhist; ++k){
       for (int j=0; j<hist[k]->GetSize()-1; ++j){
         if (hist[k]->GetBinContent(j)<0) hist[k]->SetBinContent(j,0);
       }
       if (k<(27-nbhist_offset)) postfix=uncertainties[k];
       else postfix=fake_uncertainties[k-(27-nbhist_offset)];
       hist[k]->SetName(name.c_str()+postfix);
       hist[k]->Write();
    }
}

void WriteHistToFileEMu(TFile* myfile, std::vector<TH1F*> hist, std::string name, TString dir_name, TString uncertainties[23], TString fake_uncertainties[30], bool isMC, int nbhist, int nbhist_offset, bool write_uncertainties){
    TString postfix="";
    TDirectory *dir =myfile->mkdir(dir_name);
    dir->cd();
    if (!write_uncertainties) nbhist=1;
    bool do_write=true;
    bool is_iso = (dir_name=="em_0" or dir_name=="em_1" or dir_name=="em_2" or dir_name=="em_3" or dir_name=="em_4" or dir_name=="em_5" or dir_name=="em_6" or dir_name=="em_7" or dir_name=="em_8" or dir_name=="em_9" or dir_name=="em_10");
    for (int k=0; k<nbhist; ++k){
       do_write=true;
       for (int j=0; j<hist[k]->GetSize()-1; ++j){
         if (hist[k]->GetBinContent(j)<0) hist[k]->SetBinContent(j,0);
       }
       //include overflow in last bin
       hist[k]->SetBinContent(hist[k]->GetSize()-2,hist[k]->GetBinContent(hist[k]->GetSize()-2)+hist[k]->GetBinContent(hist[k]->GetSize()-1)); 
       hist[k]->SetBinError(hist[k]->GetSize()-2,pow(hist[k]->GetBinError(hist[k]->GetSize()-2)*hist[k]->GetBinError(hist[k]->GetSize()-2)+hist[k]->GetBinError(hist[k]->GetSize()-1)*hist[k]->GetBinError(hist[k]->GetSize()-1),0.5));
       hist[k]->SetBinContent(hist[k]->GetSize()-1,0);
       hist[k]->SetBinError(hist[k]->GetSize()-1,0);

       if (k<(23-nbhist_offset)) postfix=uncertainties[k];
       else{ 
	   postfix=fake_uncertainties[k-(23-nbhist_offset)];
	   if (is_iso) do_write=false;
       }
       hist[k]->SetName(name.c_str()+postfix);
       if (do_write) hist[k]->Write();
    }
}
