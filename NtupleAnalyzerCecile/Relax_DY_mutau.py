if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Which TES?")

    options = parser.parse_args()
    postfixName=["","_CMS_tauid_pt30to35_2018Down","_CMS_tauid_pt30to35_2018Up","_CMS_tauid_pt35to40_2018Down","_CMS_tauid_pt35to40_2018Up","_CMS_tauid_ptgt40_2018Down","_CMS_tauid_ptgt40_2018Up","_CMS_taues_dm0_2018Down","_CMS_taues_dm0_2018Up","_CMS_taues_dm1_2018Down","_CMS_taues_dm1_2018Up","_CMS_taues_3prong_2018Down","_CMS_taues_3prong_2018Up","_CMS_mutauFR_barrel_2018Down","_CMS_mutauFR_barrel_2018Up","_CMS_mutauFR_endcap_2018Down","_CMS_mutauFR_endcap_2018Up","_CMS_mutauFES_dm0_2018Down","_CMS_mutauFES_dm0_2018Up","_CMS_mutauFES_dm1_2018Down","_CMS_mutauFES_dm1_2018Up","_CMS_pileup_2018Down","_CMS_pileup_2018Up","_CMS_mutautrg_2018Down","_CMS_mutautrg_2018Up","_CMS_etrg_2018Down","_CMS_etrg_2018Up"]

    nbhist=1#+26 

    fDY=ROOT.TFile("output_mutau_"+options.year+"/DY.root","r")
    fout=ROOT.TFile("output_mutau_"+options.year+"/DYrescaled.root","recreate")

    ncat=9
    for j in range(0,ncat):

       dir0=fout.mkdir("mt_"+str(j))
       dir0A=fout.mkdir("mt_"+str(j)+"_anti")

       hZLL2=fDY.Get("mt_"+str(j)+"/ZLL")
       hZLL1=fDY.Get("mtR_"+str(j)+"/ZLL").Clone()
       if hZLL1.Integral()>0: SF_ZLL=hZLL2.Integral()/hZLL1.Integral()

       hZLL2A=fDY.Get("mt_"+str(j)+"_anti/ZLL")
       hZLL1A=fDY.Get("mtR_"+str(j)+"_anti/ZLL").Clone()
       if hZLL1A.Integral()>0 : SF_ZLLA=hZLL2A.Integral()/hZLL1A.Integral()

       hZTT2=fDY.Get("mt_"+str(j)+"/ZTT")
       hZTT1=fDY.Get("mtR_"+str(j)+"/ZTT").Clone()
       SF_ZTT=hZTT2.Integral()/hZTT1.Integral()

       hZTT2A=fDY.Get("mt_"+str(j)+"_anti/ZTT")
       hZTT1A=fDY.Get("mtR_"+str(j)+"_anti/ZTT").Clone()
       SF_ZTTA=hZTT2A.Integral()/hZTT1A.Integral()

       for k in range(0,nbhist):
          postfix=postfixName[k]
          hZLL1=fDY.Get("mtR_"+str(j)+"/ZLL"+postfix).Clone()
	  hZLL1.Scale(SF_ZLL)

          hZLL1A=fDY.Get("mtR_"+str(j)+"_anti/ZLL"+postfix).Clone()
          hZLL1A.Scale(SF_ZLLA)

          hZTT1=fDY.Get("mtR_"+str(j)+"/ZTT"+postfix).Clone()
          hZTT1.Scale(SF_ZTT)

          hZTT1A=fDY.Get("mtR_"+str(j)+"_anti/ZTT"+postfix).Clone()
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

