if __name__ == "__main__":

    import ROOT
    import argparse
    import ctypes

    is_control=0

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')

    options = parser.parse_args()

    year4=options.year
    if options.year=="2016pre": year4="2016preVFP"
    if options.year=="2016post": year4="2016postVFP"

    postfixName=[
"","_CMS_tauid_stat1_dm0_"+year4+"Down","_CMS_tauid_stat1_dm0_"+year4+"Up","_CMS_tauid_stat1_dm1_"+year4+"Down","_CMS_tauid_stat1_dm1_"+year4+"Up","_CMS_tauid_stat1_dm10_"+year4+"Down","_CMS_tauid_stat1_dm10_"+year4+"Up","_CMS_tauid_stat1_dm11_"+year4+"Down","_CMS_tauid_stat1_dm11_"+year4+"Up","_CMS_tauid_stat2_dm0_"+year4+"Down","_CMS_tauid_stat2_dm0_"+year4+"Up","_CMS_tauid_stat2_dm1_"+year4+"Down","_CMS_tauid_stat2_dm1_"+year4+"Up","_CMS_tauid_stat2_dm10_"+year4+"Down","_CMS_tauid_stat2_dm10_"+year4+"Up","_CMS_tauid_stat2_dm11_"+year4+"Down","_CMS_tauid_stat2_dm11_"+year4+"Up","_CMS_tauid_syst_allerasDown","_CMS_tauid_syst_allerasUp","_CMS_tauid_syst_"+year4+"Down","_CMS_tauid_syst_"+year4+"Up","_CMS_tauid_syst_dm0_"+year4+"Down","_CMS_tauid_syst_dm0_"+year4+"Up","_CMS_tauid_syst_dm1_"+year4+"Down","_CMS_tauid_syst_dm1_"+year4+"Up","_CMS_tauid_syst_dm10_"+year4+"Down","_CMS_tauid_syst_dm10_"+year4+"Up","_CMS_tauid_syst_dm11_"+year4+"Down","_CMS_tauid_syst_dm11_"+year4+"Up","_CMS_taues_dm0_"+year4+"Down","_CMS_taues_dm0_"+year4+"Up","_CMS_taues_dm1_"+year4+"Down","_CMS_taues_dm1_"+year4+"Up","_CMS_taues_3prong_"+year4+"Down","_CMS_taues_3prong_"+year4+"Up","_CMS_etauFR_barrel_"+year4+"Down","_CMS_etauFR_barrel_"+year4+"Up","_CMS_etauFR_endcap_"+year4+"Down","_CMS_etauFR_endcap_"+year4+"Up","_CMS_etauFES_dm0_"+year4+"Down","_CMS_etauFES_dm0_"+year4+"Up","_CMS_etauFES_dm1_"+year4+"Down","_CMS_etauFES_dm1_"+year4+"Up","_CMS_pileup_"+year4+"Down","_CMS_pileup_"+year4+"Up","_CMS_etautrg_"+year4+"Down","_CMS_etautrg_"+year4+"Up","_CMS_etrg_"+year4+"Down","_CMS_etrg_"+year4+"Up","_CMS_elasticRescalingDown","_CMS_elasticRescalingUp","_CMS_L1PrefiringDown","_CMS_L1PrefiringUp","_CMS_elId_systDown","_CMS_elId_systUp",
"_CMS_ISRDown","_CMS_ISRUp","_CMS_FSRDown","_CMS_FSRUp","_CMS_PDFDown","_CMS_PDFUp","_CMS_muR0p5_muF0p5","_CMS_muRDown","_CMS_muFDown","_CMS_muFUp","_CMS_muRUp","_CMS_muR2p0_muF2p0",
"_CMS_jetfake_w_invertMTDown","_CMS_jetfake_w_invertMTUp","_CMS_jetfake_qcd_invertOSDown","_CMS_jetfake_qcd_invertOSUp","_CMS_jetfake_tauptextrap_w_et_dm0_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm0_"+year4+"Up","_CMS_jetfake_tauptextrap_w_et_dm1_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm1_"+year4+"Up","_CMS_jetfake_tauptextrap_w_et_dm10_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm10_"+year4+"Up","_CMS_jetfake_tauptextrap_w_et_dm11_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm11_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm0_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm0_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm1_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm1_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm10_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm10_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm11_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm11_"+year4+"Up","_CMS_jetfake_wfractionDown","_CMS_jetfake_wfractionUp","_CMS_jetfake_ntracksextrap_w_et_dm0_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_dm0_"+year4+"Up","_CMS_jetfake_ntracksextrap_w_et_dm1_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_dm1_"+year4+"Up","_CMS_jetfake_ntracksextrap_w_et_dm10_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_dm10_"+year4+"Up","_CMS_jetfake_ntracksextrap_w_et_dm11_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_dm11_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_dm0_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_dm0_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_dm1_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_dm1_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_dm10_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_dm10_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_dm11_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_dm11_"+year4+"Up","_CMS_jetfake_ntracksextrap_w_et_"+year4+"Down","_CMS_jetfake_ntracksextrap_w_et_"+year4+"Up","_CMS_jetfake_ntracksextrap_qcd_et_"+year4+"Down","_CMS_jetfake_ntracksextrap_qcd_et_"+year4+"Up"]

    nbhist=1 
    nbhist_anti=1
    if is_control==0:
      nbhist=1+54+12
      nbhist_anti=1+54+42+12

    fDY=ROOT.TFile("output_etau_"+options.year+"/DY.root","r")
    fout=ROOT.TFile("output_etau_"+options.year+"/DYrescaled.root","recreate")

    ncat=9
    if is_control==0: ncat=6

    for j in range(0,ncat):
       print j

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

       if (is_control==0 and j==2):
          SF_ZLL=0.194
          SF_ZLLA=0.194
          SF_ZTT=0.194
          SF_ZTTA=0.194

       if (is_control==0 and j==3):
          SF_ZLL=0.0501+0.0242
          SF_ZLLA=0.0501+0.0242
          SF_ZTT=0.0501+0.0242
          SF_ZTTA=0.0501+0.0242

       if (is_control==0 and (j==4 or j==5)):
          SF_ZLL=1.0
          SF_ZLLA=1.0
          SF_ZTT=1.0
          SF_ZTTA=1.0

       print SF_ZLL, SF_ZLLA, SF_ZTT, SF_ZTTA

       for k in range(0,nbhist):
	  #print k,postfixName[k]
          postfix=postfixName[k]
          hZLL1=fDY.Get("etR_"+str(j)+"/ZLL"+postfix).Clone()
	  hZLL1.Scale(SF_ZLL)
          if (is_control==0 and (j==4 or j==5)):
            error = ROOT.Double(1.)
            total = hZLL1.IntegralAndError(0, hZLL1.GetNbinsX() + 1, error)
	    hZLL1.SetBinContent(1,0.0242*total)
            hZLL1.SetBinError(1,0.0242*error) 
            hZLL1.SetBinContent(2,0.0501*total)
            hZLL1.SetBinError(2,0.0501*error) 
            hZLL1.SetBinContent(3,0.072*total)
            hZLL1.SetBinError(3,0.072*error)
            hZLL1.SetBinContent(4,0.091*total)
            hZLL1.SetBinError(4,0.091*error)
            hZLL1.SetBinContent(5,0.101*total)
            hZLL1.SetBinError(5,0.101*error)
            hZLL1.SetBinContent(6,0.120*total)
            hZLL1.SetBinError(6,0.120*error)
            hZLL1.SetBinContent(7,0.130*total)
            hZLL1.SetBinError(7,0.130*error)
            hZLL1.SetBinContent(8,0.133*total)
            hZLL1.SetBinError(8,0.133*error)
            hZLL1.SetBinContent(9,0.140*total)
            hZLL1.SetBinError(9,0.140*error)
            hZLL1.SetBinContent(10,0.141*total)
            hZLL1.SetBinError(10,0.141*error)

          hZTT1=fDY.Get("etR_"+str(j)+"/ZTT"+postfix).Clone()
          hZTT1.Scale(SF_ZTT)
          if (is_control==0 and (j==4 or j==5)):
            error = ROOT.Double(1.)
            total = hZTT1.IntegralAndError(0, hZTT1.GetNbinsX() + 1, error)
            hZTT1.SetBinContent(1,0.0242*total)
            hZTT1.SetBinError(1,0.0242*error) 
            hZTT1.SetBinContent(2,0.0501*total)
            hZTT1.SetBinError(2,0.0501*error) 
            hZTT1.SetBinContent(3,0.072*total)
            hZTT1.SetBinError(3,0.072*error)
            hZTT1.SetBinContent(4,0.091*total)
            hZTT1.SetBinError(4,0.091*error)
            hZTT1.SetBinContent(5,0.101*total)
            hZTT1.SetBinError(5,0.101*error)
            hZTT1.SetBinContent(6,0.120*total)
            hZTT1.SetBinError(6,0.120*error)
            hZTT1.SetBinContent(7,0.130*total)
            hZTT1.SetBinError(7,0.130*error)
            hZTT1.SetBinContent(8,0.133*total)
            hZTT1.SetBinError(8,0.133*error)
            hZTT1.SetBinContent(9,0.140*total)
            hZTT1.SetBinError(9,0.140*error)
            hZTT1.SetBinContent(10,0.141*total)
            hZTT1.SetBinError(10,0.141*error)

          fout.cd()
          dir0.cd()
          hZLL1.SetName("ZLL"+postfix)
          hZLL2.SetName("ZLL"+postfix)
          if (j==3): 
             hZLL2.Write()
	  else: 
             hZLL1.Write()
          hZTT1.SetName("ZTT"+postfix)
          hZTT2.SetName("ZTT"+postfix)
          if (j!=3): hZTT1.Write()
          else: hZTT2.Write()

       for k in range(0,nbhist_anti):
          postfix=postfixName[k]

          hZLL1A=fDY.Get("etR_"+str(j)+"_anti/ZLL"+postfix).Clone()
          hZLL1A.Scale(SF_ZLLA)
          if (is_control==0 and (j==4 or j==5)):
            error = ROOT.Double(1.)
            total = hZLL1A.IntegralAndError(0, hZLL1A.GetNbinsX() + 1, error)
            hZLL1A.SetBinContent(1,0.0242*total)
            hZLL1A.SetBinError(1,0.0242*error)
            hZLL1A.SetBinContent(2,0.0501*total)
            hZLL1A.SetBinError(2,0.0501*error)
            hZLL1A.SetBinContent(3,0.072*total)
            hZLL1A.SetBinError(3,0.072*error)
            hZLL1A.SetBinContent(4,0.091*total)
            hZLL1A.SetBinError(4,0.091*error)
            hZLL1A.SetBinContent(5,0.101*total)
            hZLL1A.SetBinError(5,0.101*error)
            hZLL1A.SetBinContent(6,0.120*total)
            hZLL1A.SetBinError(6,0.120*error)
            hZLL1A.SetBinContent(7,0.130*total)
            hZLL1A.SetBinError(7,0.130*error)
            hZLL1A.SetBinContent(8,0.133*total)
            hZLL1A.SetBinError(8,0.133*error)
            hZLL1A.SetBinContent(9,0.140*total)
            hZLL1A.SetBinError(9,0.140*error)
            hZLL1A.SetBinContent(10,0.141*total)
            hZLL1A.SetBinError(10,0.141*error)

          hZTT1A=fDY.Get("etR_"+str(j)+"_anti/ZTT"+postfix).Clone()
          hZTT1A.Scale(SF_ZTTA)
          if (is_control==0 and (j==4 or j==5)):
            error = ROOT.Double(1.)
            total = hZTT1A.IntegralAndError(0, hZTT1A.GetNbinsX() + 1, error)
            hZTT1A.SetBinContent(1,0.0242*total)
            hZTT1A.SetBinError(1,0.0242*error)
            hZTT1A.SetBinContent(2,0.0501*total)
            hZTT1A.SetBinError(2,0.0501*error)
            hZTT1A.SetBinContent(3,0.072*total)
            hZTT1A.SetBinError(3,0.072*error)
            hZTT1A.SetBinContent(4,0.091*total)
            hZTT1A.SetBinError(4,0.091*error)
            hZTT1A.SetBinContent(5,0.101*total)
            hZTT1A.SetBinError(5,0.101*error)
            hZTT1A.SetBinContent(6,0.120*total)
            hZTT1A.SetBinError(6,0.120*error)
            hZTT1A.SetBinContent(7,0.130*total)
            hZTT1A.SetBinError(7,0.130*error)
            hZTT1A.SetBinContent(8,0.133*total)
            hZTT1A.SetBinError(8,0.133*error)
            hZTT1A.SetBinContent(9,0.140*total)
            hZTT1A.SetBinError(9,0.140*error)
            hZTT1A.SetBinContent(10,0.141*total)
            hZTT1A.SetBinError(10,0.141*error)


          fout.cd()
          dir0A.cd()
          hZLL1A.SetName("ZLL"+postfix)
          hZLL2A.SetName("ZLL"+postfix)
          if (j!=3): hZLL1A.Write()
          else: hZLL2A.Write()
          hZTT1A.SetName("ZTT"+postfix)
          hZTT2A.SetName("ZTT"+postfix)
          if (j!=3): hZTT1A.Write()
          else: hZTT2A.Write()

