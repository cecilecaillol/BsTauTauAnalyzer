float mupt_,taupt_,mueta_,taueta_,muphi_,tauphi_,GenVtx_z_,recoDitau_z_,mudz_,taudz_,weight_;
float tau1pt_,tau2pt_,tau1eta_,tau2eta_,tau1phi_,tau2phi_,tau1dz_,tau2dz_;
int taudm_,tau1dm_,tau2dm_;

void fillTreeDz(TTree* BG_Tree,float MUPT, float TAUPT, float MUETA, float TAUETA, float MUPHI, float TAUPHI, int TAUDM, float GENVTX_Z, float RECODITAU_Z, float MUDZ, float TAUDZ, float WEIGHT){
   mupt_=MUPT;
   taupt_=TAUPT;
   mueta_=MUETA;
   taueta_=TAUETA;
   muphi_=MUPHI;
   tauphi_=TAUPHI;
   taudm_=TAUDM;
   GenVtx_z_=GENVTX_Z;
   recoDitau_z_=RECODITAU_Z;
   mudz_=MUDZ;
   taudz_=TAUDZ;
   weight_=WEIGHT;
   BG_Tree->Fill();
}

void fillTreeDzTautau(TTree* BG_Tree,float TAU1PT, float TAU2PT, float TAU1ETA, float TAU2ETA, float TAU1PHI, float TAU2PHI, int TAU1DM, int TAU2DM, float GENVTX_Z, float RECODITAU_Z, float TAU1DZ, float TAU2DZ, float WEIGHT){
   tau1pt_=TAU1PT;
   tau2pt_=TAU2PT;
   tau1eta_=TAU1ETA;
   tau2eta_=TAU2ETA;
   tau1phi_=TAU1PHI;
   tau2phi_=TAU2PHI;
   tau1dm_=TAU1DM;
   tau2dm_=TAU2DM;
   GenVtx_z_=GENVTX_Z;
   recoDitau_z_=RECODITAU_Z;
   tau1dz_=TAU1DZ;
   tau2dz_=TAU2DZ;
   weight_=WEIGHT;
   BG_Tree->Fill();
}

