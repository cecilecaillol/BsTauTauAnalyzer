float mu1pt_,mu1eta_,mu1phi_,mu2pt_,mu2eta_,mu2phi_,acoplanarity_,aweight_,weight_,npvs_weight_,ntpu_weight_,nths_weight_,aco_weight_;
int os_,ntracksAll_,sum_ntracks_;

void fillTreeRescaling(TTree* BG_Tree,float MU1PT, float MU1ETA, float MU1PHI, float MU2PT, float MU2ETA, float MU2PHI, int OS, float ACOPLANARITY, int SUM_NTRACKS, int NTRACKSALL, float AWEIGHT, float WEIGHT, float NPVS_WEIGHT, float NTPU_WEIGHT, float NTHS_WEIGHT, float ACO_WEIGHT){
   mu1pt_=MU1PT;
   mu1eta_=MU1ETA;
   mu1phi_=MU1PHI;
   mu2pt_=MU2PT;
   mu2eta_=MU2ETA;
   mu2phi_=MU2PHI;
   os_=OS;
   acoplanarity_=ACOPLANARITY;
   sum_ntracks_=SUM_NTRACKS;
   ntracksAll_=NTRACKSALL;
   aweight_=AWEIGHT;
   weight_=WEIGHT;
   npvs_weight_=NPVS_WEIGHT;
   ntpu_weight_=NTPU_WEIGHT;
   nths_weight_=NTHS_WEIGHT;
   aco_weight_=ACO_WEIGHT;
   BG_Tree->Fill();
}

