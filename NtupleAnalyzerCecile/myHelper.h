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
