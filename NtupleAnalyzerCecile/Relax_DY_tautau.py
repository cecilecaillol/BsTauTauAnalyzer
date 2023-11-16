if __name__ == "__main__":

    import ROOT
    import argparse

    is_control=0 
    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Which TES?")

    options = parser.parse_args()
    postfixName=["","_CMS_tauid_pt30to35_2018Down","_CMS_tauid_pt30to35_2018Up","_CMS_tauid_pt35to40_2018Down","_CMS_tauid_pt35to40_2018Up","_CMS_tauid_ptgt40_2018Down","_CMS_tauid_ptgt40_2018Up","_CMS_taues_dm0_2018Down","_CMS_taues_dm0_2018Up","_CMS_taues_dm1_2018Down","_CMS_taues_dm1_2018Up","_CMS_taues_3prong_2018Down","_CMS_taues_3prong_2018Up","_CMS_tautauFR_barrel_2018Down","_CMS_tautauFR_barrel_2018Up","_CMS_tautauFR_endcap_2018Down","_CMS_tautauFR_endcap_2018Up","_CMS_tautauFES_dm0_2018Down","_CMS_tautauFES_dm0_2018Up","_CMS_tautauFES_dm1_2018Down","_CMS_tautauFES_dm1_2018Up","_CMS_pileup_2018Down","_CMS_pileup_2018Up","_CMS_tautautrg_2018Down","_CMS_tautautrg_2018Up","_CMS_etrg_2018Down","_CMS_etrg_2018Up"]

    nbhist=1#+26 

    fDY=ROOT.TFile("output_tautau_"+options.year+"/DY.root","r")
    fout=ROOT.TFile("output_tautau_"+options.year+"/DYrescaled.root","recreate")

    ncat=9
    for j in range(0,ncat):

       dir0=fout.mkdir("tt_"+str(j))
       dir0A=fout.mkdir("tt_"+str(j)+"_anti")

       hZTT2=fDY.Get("tt_"+str(j)+"/ZTT")
       hZTT1=fDY.Get("ttR_"+str(j)+"/ZTT").Clone()
       SF_ZTT=hZTT2.Integral()/hZTT1.Integral()

       hZTT2A=fDY.Get("tt_"+str(j)+"_anti/ZTT")
       hZTT1A=fDY.Get("ttR_"+str(j)+"_anti/ZTT").Clone()
       SF_ZTTA=hZTT2A.Integral()/hZTT1A.Integral()

       print(SF_ZTT,SF_ZTTA)

       if (is_control==0 and j==0):
          SF_ZTT=0.0242
          SF_ZTTA=0.0242

       if (is_control==0 and j==1):
          SF_ZTT=0.0501
          SF_ZTTA=0.0501

       for k in range(0,nbhist):
          postfix=postfixName[k]

          hZTT1=fDY.Get("ttR_"+str(j)+"/ZTT"+postfix).Clone()
          hZTT1.Scale(SF_ZTT)

          hZTT1A=fDY.Get("ttR_"+str(j)+"_anti/ZTT"+postfix).Clone()
          hZTT1A.Scale(SF_ZTTA)

          fout.cd()
          dir0.cd()
          hZTT1.SetName("ZTT"+postfix)
          hZTT1.Write()

          dir0A.cd()
          hZTT1A.SetName("ZTT"+postfix)
          hZTT1A.Write()

