if __name__ == "__main__":

    is_control=0

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')
    options = parser.parse_args()

    year4=options.year
    if options.year=="2016pre": year4="2016preVFP"
    if options.year=="2016post": year4="2016postVFP"

    postfixName=["","_CMS_pileup_"+year4+"Down","_CMS_pileup_"+year4+"Up","_CMS_emutrg_lowmuhighe_systDown","_CMS_emutrg_lowmuhighe_systUp","_CMS_emutrg_highmulowe_systDown","_CMS_emutrg_highmulowe_systUp","_CMS_emutrg_highmuhighe_systDown","_CMS_emutrg_highmuhighe_systUp","_CMS_elasticRescalingDown","_CMS_elasticRescalingUp","_CMS_L1PrefiringDown","_CMS_L1PrefiringUp","_CMS_muId_systDown","_CMS_muId_systUp","_CMS_muId_stat_"+year4+"Down","_CMS_muId_stat_"+year4+"Up","_CMS_muIso_systDown","_CMS_muIso_systUp","_CMS_muIso_stat_"+year4+"Down","_CMS_muIso_stat_"+year4+"Up","_CMS_elId_systDown","_CMS_elId_systUp",
"_CMS_ISRDown","_CMS_ISRUp","_CMS_FSRDown","_CMS_FSRUp","_CMS_PDFDown","_CMS_PDFUp","_CMS_muR0p5_muF0p5","_CMS_muRDown","_CMS_muFDown","_CMS_muFUp","_CMS_muRUp","_CMS_muR2p0_muF2p0",
"_CMS_fakebkg_emu_stat_pte15to24_ptmu24to35_"+year4+"Down","_CMS_fakebkg_emu_stat_pte15to24_ptmu24to35_"+year4+"Up","_CMS_fakebkg_emu_stat_pte15to24_ptmu35to45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte15to24_ptmu35to45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte15to24_ptmugt45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte15to24_ptmugt45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte24to35_ptmu15to24_"+year4+"Down","_CMS_fakebkg_emu_stat_pte24to35_ptmu15to24_"+year4+"Up","_CMS_fakebkg_emu_stat_pte24to35_ptmu24to35_"+year4+"Down","_CMS_fakebkg_emu_stat_pte24to35_ptmu24to35_"+year4+"Up","_CMS_fakebkg_emu_stat_pte24to35_ptmu35to45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte24to35_ptmu35to45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte24to35_ptmugt45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte24to35_ptmugt45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte35to45_ptmu15to24_"+year4+"Down","_CMS_fakebkg_emu_stat_pte35to45_ptmu15to24_"+year4+"Up","_CMS_fakebkg_emu_stat_pte35to45_ptmu24to35_"+year4+"Down","_CMS_fakebkg_emu_stat_pte35to45_ptmu24to35_"+year4+"Up","_CMS_fakebkg_emu_stat_pte35to45_ptmu35to45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte35to45_ptmu35to45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte35to45_ptmugt45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte35to45_ptmugt45_"+year4+"Up","_CMS_fakebkg_emu_stat_ptegt45_ptmu15to24_"+year4+"Down","_CMS_fakebkg_emu_stat_ptegt45_ptmu15to24_"+year4+"Up","_CMS_fakebkg_emu_stat_ptegt45_ptmu24to35_"+year4+"Down","_CMS_fakebkg_emu_stat_ptegt45_ptmu24to35_"+year4+"Up","_CMS_fakebkg_emu_stat_ptegt45_ptmu35to45_"+year4+"Down","_CMS_fakebkg_emu_stat_ptegt45_ptmu35to45_"+year4+"Up","_CMS_fakebkg_emu_stat_ptegt45_ptmugt45_"+year4+"Down","_CMS_fakebkg_emu_stat_ptegt45_ptmugt45_"+year4+"Up"]

    nbhist=1 
    nbhist_anti=1

    fDY=ROOT.TFile("output_emu_"+options.year+"/DY.root","r")
    fout=ROOT.TFile("output_emu_"+options.year+"/DYrescaled.root","recreate")

    ncat=9
    if is_control==0: 
       ncat=6
       nbhist=1+22+12
       nbhist_anti=1+22+30+12

    for j in range(0,ncat):

       dir0=fout.mkdir("em_"+str(j))
       dir0A=fout.mkdir("em_"+str(j)+"_anti")

       for k in range(0,nbhist):
          postfix=postfixName[k]
          print "em_"+str(j)+"/ZTT"+postfix
          hZTT2=fDY.Get("em_"+str(j)+"/ZTT"+postfix)
          hZTT1=fDY.Get("emR_"+str(j)+"/ZTT"+postfix).Clone()
          hZTT1.Scale(hZTT2.Integral()/hZTT1.Integral())

          fout.cd()
          dir0.cd()
          hZTT1.SetName("ZTT"+postfix)
          hZTT1.Write()

       for k in range(0,nbhist_anti):
          postfix=postfixName[k]
          hZTT2A=fDY.Get("em_"+str(j)+"_anti/ZTT"+postfix)
	  print("emR_"+str(j)+"_anti/ZTT"+postfix)
          hZTT1A=fDY.Get("emR_"+str(j)+"_anti/ZTT"+postfix).Clone()
          if hZTT1A.Integral()>0: hZTT1A.Scale(hZTT2A.Integral()/hZTT1A.Integral())

          fout.cd()
          dir0A.cd()
          hZTT1A.SetName("ZTT"+postfix)
          hZTT1A.Write()

