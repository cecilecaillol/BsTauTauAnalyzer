if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')

    options = parser.parse_args()
    postfixName=["","_CMS_tauid_stat1_dm0_2018Down","_CMS_tauid_stat1_dm0_2018Up","_CMS_tauid_stat1_dm1_2018Down","_CMS_tauid_stat1_dm1_2018Up","_CMS_tauid_stat1_dm10_2018Down","_CMS_tauid_stat1_dm10_2018Up","_CMS_tauid_stat1_dm11_2018Down","_CMS_tauid_stat1_dm11_2018Up","_CMS_tauid_stat2_dm0_2018Down","_CMS_tauid_stat2_dm0_2018Up","_CMS_tauid_stat2_dm1_2018Down","_CMS_tauid_stat2_dm1_2018Up","_CMS_tauid_stat2_dm10_2018Down","_CMS_tauid_stat2_dm10_2018Up","_CMS_tauid_stat2_dm11_2018Down","_CMS_tauid_stat2_dm11_2018Up","_CMS_tauid_syst_allerasDown","_CMS_tauid_syst_allerasUp","_CMS_tauid_syst_2018Down","_CMS_tauid_syst_2018Up","_CMS_tauid_syst_dm0_2018Down","_CMS_tauid_syst_dm0_2018Up","_CMS_tauid_syst_dm1_2018Down","_CMS_tauid_syst_dm1_2018Up","_CMS_tauid_syst_dm10_2018Down","_CMS_tauid_syst_dm10_2018Up","_CMS_tauid_syst_dm11_2018Down","_CMS_tauid_syst_dm11_2018Up","_CMS_taues_dm0_2018Down","_CMS_taues_dm0_2018Up","_CMS_taues_dm1_2018Down","_CMS_taues_dm1_2018Up","_CMS_taues_3prong_2018Down","_CMS_taues_3prong_2018Up","_CMS_etauFR_barrel_2018Down","_CMS_etauFR_barrel_2018Up","_CMS_etauFR_endcap_2018Down","_CMS_etauFR_endcap_2018Up","_CMS_etauFES_dm0_2018Down","_CMS_etauFES_dm0_2018Up","_CMS_etauFES_dm1_2018Down","_CMS_etauFES_dm1_2018Up","_CMS_pileup_2018Down","_CMS_pileup_2018Up","_CMS_etautrg_2018Down","_CMS_etautrg_2018Up","_CMS_etrg_2018Down","_CMS_etrg_2018Up"]
#"","_CMS_tauid_pt30to35_2018Down","_CMS_tauid_pt30to35_2018Up","_CMS_tauid_pt35to40_2018Down","_CMS_tauid_pt35to40_2018Up","_CMS_tauid_ptgt40_2018Down","_CMS_tauid_ptgt40_2018Up","_CMS_taues_dm0_2018Down","_CMS_taues_dm0_2018Up","_CMS_taues_dm1_2018Down","_CMS_taues_dm1_2018Up","_CMS_taues_3prong_2018Down","_CMS_taues_3prong_2018Up","_CMS_etauFR_barrel_2018Down","_CMS_etauFR_barrel_2018Up","_CMS_etauFR_endcap_2018Down","_CMS_etauFR_endcap_2018Up","_CMS_etauFES_dm0_2018Down","_CMS_etauFES_dm0_2018Up","_CMS_etauFES_dm1_2018Down","_CMS_etauFES_dm1_2018Up","_CMS_pileup_2018Down","_CMS_pileup_2018Up","_CMS_etautrg_2018Down","_CMS_etautrg_2018Up","_CMS_etrg_2018Down","_CMS_etrg_2018Up"]

    nbhist=1#+48 

    fDY=ROOT.TFile("output_etau_"+options.year+"/DY.root","r")
    fout=ROOT.TFile("output_etau_"+options.year+"/DYrescaled.root","recreate")

    ncat=9
    for j in range(0,ncat):

       dir0=fout.mkdir("et_"+str(j))
       dir0A=fout.mkdir("et_"+str(j)+"_anti")

       hZLL2=fDY.Get("et_"+str(j)+"/ZLL")
       hZLL1=fDY.Get("etR_"+str(j)+"/ZLL").Clone()
       SF_ZLL=hZLL2.Integral()/hZLL1.Integral()

       hZLL2A=fDY.Get("et_"+str(j)+"_anti/ZLL")
       hZLL1A=fDY.Get("etR_"+str(j)+"_anti/ZLL").Clone()
       SF_ZLLA=hZLL2A.Integral()/hZLL1A.Integral()

       hZTT2=fDY.Get("et_"+str(j)+"/ZTT")
       hZTT1=fDY.Get("etR_"+str(j)+"/ZTT").Clone()
       SF_ZTT=hZTT2.Integral()/hZTT1.Integral()

       hZTT2A=fDY.Get("et_"+str(j)+"_anti/ZTT")
       hZTT1A=fDY.Get("etR_"+str(j)+"_anti/ZTT").Clone()
       SF_ZTTA=hZTT2A.Integral()/hZTT1A.Integral()

       for k in range(0,nbhist):
          postfix=postfixName[k]
          hZLL1=fDY.Get("etR_"+str(j)+"/ZLL"+postfix).Clone()
	  hZLL1.Scale(SF_ZLL)

          hZLL1A=fDY.Get("etR_"+str(j)+"_anti/ZLL"+postfix).Clone()
          hZLL1A.Scale(SF_ZLLA)

          hZTT1=fDY.Get("etR_"+str(j)+"/ZTT"+postfix).Clone()
          hZTT1.Scale(SF_ZTT)

          hZTT1A=fDY.Get("etR_"+str(j)+"_anti/ZTT"+postfix).Clone()
          hZTT1A.Scale(SF_ZTTA)

          fout.cd()
          dir0.cd()
          hZLL1.SetName("ZLL"+postfix)
          hZLL1.Write()
          hZTT1.SetName("ZTT"+postfix)
          hZTT1.Write()

          dir0A.cd()
          hZLL1A.SetName("ZLL"+postfix)
          hZLL1A.Write()
          hZTT1A.SetName("ZTT"+postfix)
          hZTT1A.Write()

