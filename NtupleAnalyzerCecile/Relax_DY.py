if __name__ == "__main__":

    import ROOT
    import argparse

    is_control=0

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')

    options = parser.parse_args()

    year4=options.year
    if options.year=="2016pre": year4="2016preVFP"
    if options.year=="2016post": year4="2016postVFP"

    postfixName=[
"","_CMS_tauid_stat1_dm0_"+year4+"Down","_CMS_tauid_stat1_dm0_"+year4+"Up","_CMS_tauid_stat1_dm1_"+year4+"Down","_CMS_tauid_stat1_dm1_"+year4+"Up","_CMS_tauid_stat1_dm10_"+year4+"Down","_CMS_tauid_stat1_dm10_"+year4+"Up","_CMS_tauid_stat1_dm11_"+year4+"Down","_CMS_tauid_stat1_dm11_"+year4+"Up","_CMS_tauid_stat2_dm0_"+year4+"Down","_CMS_tauid_stat2_dm0_"+year4+"Up","_CMS_tauid_stat2_dm1_"+year4+"Down","_CMS_tauid_stat2_dm1_"+year4+"Up","_CMS_tauid_stat2_dm10_"+year4+"Down","_CMS_tauid_stat2_dm10_"+year4+"Up","_CMS_tauid_stat2_dm11_"+year4+"Down","_CMS_tauid_stat2_dm11_"+year4+"Up","_CMS_tauid_syst_allerasDown","_CMS_tauid_syst_allerasUp","_CMS_tauid_syst_"+year4+"Down","_CMS_tauid_syst_"+year4+"Up","_CMS_tauid_syst_dm0_"+year4+"Down","_CMS_tauid_syst_dm0_"+year4+"Up","_CMS_tauid_syst_dm1_"+year4+"Down","_CMS_tauid_syst_dm1_"+year4+"Up","_CMS_tauid_syst_dm10_"+year4+"Down","_CMS_tauid_syst_dm10_"+year4+"Up","_CMS_tauid_syst_dm11_"+year4+"Down","_CMS_tauid_syst_dm11_"+year4+"Up","_CMS_taues_dm0_"+year4+"Down","_CMS_taues_dm0_"+year4+"Up","_CMS_taues_dm1_"+year4+"Down","_CMS_taues_dm1_"+year4+"Up","_CMS_taues_3prong_"+year4+"Down","_CMS_taues_3prong_"+year4+"Up","_CMS_etauFR_barrel_"+year4+"Down","_CMS_etauFR_barrel_"+year4+"Up","_CMS_etauFR_endcap_"+year4+"Down","_CMS_etauFR_endcap_"+year4+"Up","_CMS_etauFES_dm0_"+year4+"Down","_CMS_etauFES_dm0_"+year4+"Up","_CMS_etauFES_dm1_"+year4+"Down","_CMS_etauFES_dm1_"+year4+"Up","_CMS_pileup_"+year4+"Down","_CMS_pileup_"+year4+"Up","_CMS_etautrg_"+year4+"Down","_CMS_etautrg_"+year4+"Up","_CMS_etrg_"+year4+"Down","_CMS_etrg_"+year4+"Up","_CMS_elasticRescalingDown","_CMS_elasticRescalingUp","_CMS_L1PrefiringDown","_CMS_L1PrefiringUp","_CMS_elId_systDown","_CMS_elId_systUp",
"_CMS_jetfake_w_invertMTDown","_CMS_jetfake_w_invertMTUp","_CMS_jetfake_qcd_invertOSDown","_CMS_jetfake_qcd_invertOSUp","_CMS_jetfake_tauptextrap_w_et_dm0_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm0_"+year4+"Up","_CMS_jetfake_tauptextrap_w_et_dm1_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm1_"+year4+"Up","_CMS_jetfake_tauptextrap_w_et_dm10_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm10_"+year4+"Up","_CMS_jetfake_tauptextrap_w_et_dm11_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm11_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm0_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm0_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm1_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm1_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm10_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm10_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm11_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm11_"+year4+"Up","_CMS_jetfake_wfractionDown","_CMS_jetfake_wfractionUp","_CMS_jetfake_ntracksextrap_w_et_dm0_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_dm0_"+year4+"Up","_CMS_jetfake_ntracksextrap_w_et_dm1_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_dm1_"+year4+"Up","_CMS_jetfake_ntracksextrap_w_et_dm10_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_dm10_"+year4+"Up","_CMS_jetfake_ntracksextrap_w_et_dm11_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_dm11_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_dm0_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_dm0_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_dm1_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_dm1_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_dm10_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_dm10_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_dm11_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_dm11_"+year4+"Up","_CMS_jetfake_ntracksextrap_w_et_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_"+year4+"Up"]

    nbhist=1 
    nbhist_anti=1
    if is_control==0:
      nbhist=1+54
      nbhist_anti=1+54+42

    fDY=ROOT.TFile("output_etau_"+options.year+"/DY.root","r")
    fout=ROOT.TFile("output_etau_"+options.year+"/DYrescaled.root","recreate")

    ncat=9
    if is_control==0: ncat=2

    for j in range(0,ncat):

       dir0=fout.mkdir("et_"+str(j))
       dir0A=fout.mkdir("et_"+str(j)+"_anti")

       hZLL2=fDY.Get("et_"+str(j)+"/ZLL")
       hZLL1=fDY.Get("etR_"+str(j)+"/ZLL").Clone()
       SF_ZLL=hZLL2.Integral()/(hZLL1.Integral()+0.001)

       hZLL2A=fDY.Get("et_"+str(j)+"_anti/ZLL")
       hZLL1A=fDY.Get("etR_"+str(j)+"_anti/ZLL").Clone()
       SF_ZLLA=hZLL2A.Integral()/(hZLL1A.Integral()+0.001)

       hZTT2=fDY.Get("et_"+str(j)+"/ZTT")
       hZTT1=fDY.Get("etR_"+str(j)+"/ZTT").Clone()
       SF_ZTT=hZTT2.Integral()/(hZTT1.Integral()+0.001)

       hZTT2A=fDY.Get("et_"+str(j)+"_anti/ZTT")
       hZTT1A=fDY.Get("etR_"+str(j)+"_anti/ZTT").Clone()
       SF_ZTTA=hZTT2A.Integral()/(hZTT1A.Integral()+0.001)

       if (is_control==0 and j==0):
	  SF_ZLL=0.0242
          SF_ZLLA=0.0242
          SF_ZTT=0.0242
          SF_ZTTA=0.0242

       if (is_control==0 and j==1):
          SF_ZLL=0.0501
          SF_ZLLA=0.0501
          SF_ZTT=0.0501
          SF_ZTTA=0.0501

       print SF_ZLL, SF_ZLLA, SF_ZTT, SF_ZTTA

       for k in range(0,nbhist):
	  print k,postfixName[k]
          postfix=postfixName[k]
          hZLL1=fDY.Get("etR_"+str(j)+"/ZLL"+postfix).Clone()
	  hZLL1.Scale(SF_ZLL)

          hZTT1=fDY.Get("etR_"+str(j)+"/ZTT"+postfix).Clone()
          hZTT1.Scale(SF_ZTT)

          fout.cd()
          dir0.cd()
          hZLL1.SetName("ZLL"+postfix)
          hZLL1.Write()
          hZTT1.SetName("ZTT"+postfix)
          hZTT1.Write()

       for k in range(0,nbhist_anti):
          postfix=postfixName[k]

          hZLL1A=fDY.Get("etR_"+str(j)+"_anti/ZLL"+postfix).Clone()
          hZLL1A.Scale(SF_ZLLA)
          hZTT1A=fDY.Get("etR_"+str(j)+"_anti/ZTT"+postfix).Clone()
          hZTT1A.Scale(SF_ZTTA)

          fout.cd()
          dir0A.cd()
          hZLL1A.SetName("ZLL"+postfix)
          hZLL1A.Write()
          hZTT1A.SetName("ZTT"+postfix)
          hZTT1A.Write()

