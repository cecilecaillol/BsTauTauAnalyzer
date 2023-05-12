#ifndef ApplyFR_H
#define ApplyFR_H
#include <ROOT/RDataFrame.hxx>
#include "TLorentzVector.h"

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"
#include <cmath>
#include "ROOT/RVec.hxx"
#include "ROOT/RDF/RInterface.hxx"
using namespace std;
using namespace ROOT;
using namespace ROOT::VecOps;
using Vec_t = const ROOT::RVec<float>&;

float GetFR_mutau(int taudecaymode, float mvis, float mtrans, float taupt, int nTrk, bool isMuonTauTrigger);
float GetFR_tautau(int taudecaymode,float taupt, int nTrk);


#endif