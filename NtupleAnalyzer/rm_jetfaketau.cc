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
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TMath.h"
#include "tr_Tree.h"


using namespace std;
//this code is used to rm jet fake tau MC in signal region
int main(int argc, char** argv) {
    std::string sample = *(argv + 1);

    TFile *fin = new TFile(Form("/afs/cern.ch/user/x/xuqin/eos/taug-2/nanoplots/mutau/after_sel/%s.root",sample.c_str()),"read");
    TTree *tin = (TTree*)fin->Get("Events");
    TFile *fout = new TFile(Form("/afs/cern.ch/user/x/xuqin/eos/taug-2/nanoplots/mutau/after_sel/sig_reg_rmjetfaketau/%s_rmjetfaketau.root",sample.c_str()),"recreate");
    TTree *tout = (TTree*)tin->CloneTree(0);

    double taugen;
    tin->SetBranchAddress("taugen",&taugen);
    int Entries = tin->GetEntries();

    for (int i=0;i<Entries;i++){
        tin->GetEntry(i);
        if (taugen>0){
            tout->Fill();
        }
    }
    fout->cd();
    tout->Write();

    fout->Close();

}
