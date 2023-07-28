

def add_lumi(year):
    lowX=0.4
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.055)
    lumi.SetTextFont (   42 )
    if (year=="2018"): lumi.AddText("2018, 60 fb^{-1} (13 TeV)")
    if (year=="2017"): lumi.AddText("2017, 41 fb^{-1} (13 TeV)")
    if (year=="2016"): lumi.AddText("2016, 36 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.16
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.065)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi


if __name__ == "__main__":

    import ROOT
    import argparse
    from array import array
    import ctypes

    ROOT.gStyle.SetOptStat(0)

    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2016", choices=['Run2','2016', '2016pre', '2016post', '2017', '2018'], help="Which TES?")
    parser.add_argument('--channel', default="etau", choices=['etau', 'emu', 'mutau', 'tautau'], help="Which TES?")

    options = parser.parse_args()
    postfixName=[""]


    ceBR=[]
    at=[]
    for i in range(0,101):
      ceBR.append(-40.0+i*0.8)
      at.append((-40.0+i*0.8)*2*1.777*100/(0.3*3266.4*4)) #multiplied by 100 for numerical precision in Combine
      print ceBR[i],at[i]
    ceBRname=["m40p0","m39p2","m38p4","m37p6","m36p8","m36p0","m35p2","m34p4","m33p6","m32p8","m32p0","m31p2","m30p4","m29p6","m28p8","m28p0","m27p2","m26p4","m25p6","m24p8","m24p0","m23p2","m22p4","m21p6","m20p8","m20p0","m19p2","m18p4","m17p6","m16p8","m16p0","m15p2","m14p4","m13p6","m12p8","m12p0","m11p2","m10p4","m9p6","m8p8","m8p0","m7p2","m6p4","m5p6","m4p8","m4p0","m3p2","m2p4","m1p6","m0p8","0p0","0p8","1p6","2p4","3p2","4p0","4p8","5p6","6p4","7p2","8p0","8p8","9p6","10p4","11p2","12p0","12p8","13p6","14p4","15p2","16p0","16p8","17p6","18p4","19p2","20p0","20p8","21p6","22p4","23p2","24p0","24p8","25p6","26p4","27p2","28p0","28p8","29p6","30p4","31p2","32p0","32p8","33p6","34p4","35p2","36p0","36p8","37p6","38p4","39p2","40p0"]


    canv=ROOT.TCanvas("canvas","",0,0,900,600)
    canv.SetLeftMargin(0.15)
    canv.cd()
    #canv.SetLogy()

    fin=ROOT.TFile("output_"+options.channel+"_"+options.year+"/signal.root","r")
    fout=ROOT.TFile("output_"+options.channel+"_"+options.year+"/bsm.root","recreate")
    falt=ROOT.TFile("output_"+options.channel+"_"+options.year+"/signal.root","r")
    if (options.channel=="mutau"): falt=ROOT.TFile("/afs/cern.ch/work/c/ccaillol/Combine/CMSSW_10_2_13/src/auxiliaries/shapes/Taug2_mutau_2018.root","r")
    if (options.channel=="tautau"): falt=ROOT.TFile("/afs/cern.ch/work/c/ccaillol/Combine/CMSSW_10_2_13/src/auxiliaries/shapes/Taug2_tautau_2018.root","r")

    physics_model = open("physics_model_"+options.channel+"_"+options.year+".txt","w")

    short_channel="et"
    if options.channel=="emu": short_channel="em"
    if options.channel=="mutau": short_channel="mt"
    if options.channel=="tautau": short_channel="tt"
    categories=[short_channel+"_0",short_channel+"_1"]
    ncat=2

    shapes=[]
    year4=""
    if options.year=="2018": year4="2018"
    if options.year=="2017": year4="2017"
    if options.year=="2016pre": year4="2016preVFP"
    if options.year=="2016post": year4="2016postVFP"
    if "201" in options.year:
       if options.channel=="etau":
           shapes=["CMS_tauid_stat1_dm0_"+year4,"CMS_tauid_stat1_dm1_"+year4,"CMS_tauid_stat1_dm10_"+year4,"CMS_tauid_stat1_dm11_"+year4,"CMS_tauid_stat2_dm0_"+year4,"CMS_tauid_stat2_dm1_"+year4,"CMS_tauid_stat2_dm10_"+year4,"CMS_tauid_stat2_dm11_"+year4,"CMS_tauid_syst_alleras","CMS_tauid_syst_"+year4,"CMS_tauid_syst_dm0_"+year4,"CMS_tauid_syst_dm1_"+year4,"CMS_tauid_syst_dm10_"+year4,"CMS_tauid_syst_dm11_"+year4,"CMS_taues_dm0_"+year4,"CMS_taues_dm1_"+year4,"CMS_taues_3prong_"+year4,"CMS_etauFR_barrel_"+year4,"CMS_etauFR_endcap_"+year4,"CMS_etauFES_dm0_"+year4,"CMS_etauFES_dm1_"+year4,"CMS_pileup_"+year4,"CMS_etautrg_"+year4,"CMS_etrg_"+year4,"CMS_elId_syst","CMS_elasticRescaling"]
       elif options.channel=="mutau":
           shapes=["CMS_tauid_stat1_dm0_"+year4,"CMS_tauid_stat1_dm1_"+year4,"CMS_tauid_stat1_dm10_"+year4,"CMS_tauid_stat1_dm11_"+year4,"CMS_tauid_stat2_dm0_"+year4,"CMS_tauid_stat2_dm1_"+year4,"CMS_tauid_stat2_dm10_"+year4,"CMS_tauid_stat2_dm11_"+year4,"CMS_tauid_syst_alleras","CMS_tauid_syst_"+year4,"CMS_tauid_syst_dm0_"+year4,"CMS_tauid_syst_dm1_"+year4,"CMS_tauid_syst_dm10_"+year4,"CMS_tauid_syst_dm11_"+year4,"CMS_taues_dm0_"+year4,"CMS_taues_dm1_"+year4,"CMS_taues_3prong_"+year4,"CMS_mutauFR_barrel_"+year4,"CMS_mutauFR_endcap_"+year4,"CMS_pileup_"+year4,"CMS_mutautrg_"+year4,"CMS_mutrg_stat_"+year4,"CMS_muIso_stat_"+year4,"CMS_muId_stat_"+year4,"CMS_mutrg_syst","CMS_muIso_syst","CMS_muId_syst","CMS_elasticRescaling"]
       elif options.channel=="tautau":
           shapes=["CMS_tauid_stat1_dm0_"+year4,"CMS_tauid_stat1_dm1_"+year4,"CMS_tauid_stat1_dm10_"+year4,"CMS_tauid_stat1_dm11_"+year4,"CMS_tauid_stat2_dm0_"+year4,"CMS_tauid_stat2_dm1_"+year4,"CMS_tauid_stat2_dm10_"+year4,"CMS_tauid_stat2_dm11_"+year4,"CMS_tauid_syst_alleras","CMS_tauid_syst_"+year4,"CMS_tauid_syst_dm0_"+year4,"CMS_tauid_syst_dm1_"+year4,"CMS_tauid_syst_dm10_"+year4,"CMS_tauid_syst_dm11_"+year4,"CMS_taues_dm0_"+year4,"CMS_taues_dm1_"+year4,"CMS_taues_3prong_"+year4,"CMS_pileup_"+year4,"CMS_ditautrg_dm0_"+year4,"CMS_ditautrg_dm1_"+year4,"CMS_ditautrg_3prong_"+year4,"CMS_elasticRescaling"]
       elif options.channel=="emu":
	   shapes=["CMS_pileup_"+year4,"CMS_emutrg_lowmuhighe_syst","CMS_emutrg_highmulowe_syst","CMS_emutrg_highmuhighe_syst","CMS_elasticRescaling","CMS_muId_syst","CMS_muId_stat_"+year4,"CMS_muIso_syst","CMS_muIso_stat_"+year4,"CMS_elId_syst"]
    else:
       if options.channel=="etau":
           shapes=[
            "CMS_tauid_stat1_dm0_2016preVFP","CMS_tauid_stat1_dm1_2016preVFP","CMS_tauid_stat1_dm10_2016preVFP","CMS_tauid_stat1_dm11_2016preVFP","CMS_tauid_stat2_dm0_2016preVFP","CMS_tauid_stat2_dm1_2016preVFP","CMS_tauid_stat2_dm10_2016preVFP","CMS_tauid_stat2_dm11_2016preVFP","CMS_tauid_syst_2016preVFP","CMS_tauid_syst_dm0_2016preVFP","CMS_tauid_syst_dm1_2016preVFP","CMS_tauid_syst_dm10_2016preVFP","CMS_tauid_syst_dm11_2016preVFP","CMS_taues_dm0_2016preVFP","CMS_taues_dm1_2016preVFP","CMS_taues_3prong_2016preVFP","CMS_etauFR_barrel_2016preVFP","CMS_etauFR_endcap_2016preVFP","CMS_etauFES_dm0_2016preVFP","CMS_etauFES_dm1_2016preVFP","CMS_pileup_2016preVFP","CMS_etautrg_2016preVFP","CMS_etrg_2016preVFP",
            "CMS_tauid_stat1_dm0_2016postVFP","CMS_tauid_stat1_dm1_2016postVFP","CMS_tauid_stat1_dm10_2016postVFP","CMS_tauid_stat1_dm11_2016postVFP","CMS_tauid_stat2_dm0_2016postVFP","CMS_tauid_stat2_dm1_2016postVFP","CMS_tauid_stat2_dm10_2016postVFP","CMS_tauid_stat2_dm11_2016postVFP","CMS_tauid_syst_2016postVFP","CMS_tauid_syst_dm0_2016postVFP","CMS_tauid_syst_dm1_2016postVFP","CMS_tauid_syst_dm10_2016postVFP","CMS_tauid_syst_dm11_2016postVFP","CMS_taues_dm0_2016postVFP","CMS_taues_dm1_2016postVFP","CMS_taues_3prong_2016postVFP","CMS_etauFR_barrel_2016postVFP","CMS_etauFR_endcap_2016postVFP","CMS_etauFES_dm0_2016postVFP","CMS_etauFES_dm1_2016postVFP","CMS_pileup_2016postVFP","CMS_etautrg_2016postVFP","CMS_etrg_2016postVFP",
            "CMS_tauid_stat1_dm0_2017","CMS_tauid_stat1_dm1_2017","CMS_tauid_stat1_dm10_2017","CMS_tauid_stat1_dm11_2017","CMS_tauid_stat2_dm0_2017","CMS_tauid_stat2_dm1_2017","CMS_tauid_stat2_dm10_2017","CMS_tauid_stat2_dm11_2017","CMS_tauid_syst_2017","CMS_tauid_syst_dm0_2017","CMS_tauid_syst_dm1_2017","CMS_tauid_syst_dm10_2017","CMS_tauid_syst_dm11_2017","CMS_taues_dm0_2017","CMS_taues_dm1_2017","CMS_taues_3prong_2017","CMS_etauFR_barrel_2017","CMS_etauFR_endcap_2017","CMS_etauFES_dm0_2017","CMS_etauFES_dm1_2017","CMS_pileup_2017","CMS_etautrg_2017","CMS_etrg_2017",
            "CMS_tauid_stat1_dm0_2018","CMS_tauid_stat1_dm1_2018","CMS_tauid_stat1_dm10_2018","CMS_tauid_stat1_dm11_2018","CMS_tauid_stat2_dm0_2018","CMS_tauid_stat2_dm1_2018","CMS_tauid_stat2_dm10_2018","CMS_tauid_stat2_dm11_2018","CMS_tauid_syst_2018","CMS_tauid_syst_dm0_2018","CMS_tauid_syst_dm1_2018","CMS_tauid_syst_dm10_2018","CMS_tauid_syst_dm11_2018","CMS_taues_dm0_2018","CMS_taues_dm1_2018","CMS_taues_3prong_2018","CMS_etauFR_barrel_2018","CMS_etauFR_endcap_2018","CMS_etauFES_dm0_2018","CMS_etauFES_dm1_2018","CMS_pileup_2018","CMS_etautrg_2018","CMS_etrg_2018",
           "CMS_tauid_syst_alleras","CMS_elId_syst","CMS_elasticRescaling"]
       elif options.channel=="emu":
           shapes=[
              "CMS_pileup_2016preVFP","CMS_muId_stat_2016preVFP","CMS_muIso_stat_2016preVFP",
              "CMS_pileup_2016postVFP","CMS_muId_stat_2016postVFP","CMS_muIso_stat_2016postVFP",
              "CMS_pileup_2017","CMS_muId_stat_2017","CMS_muIso_stat_2017",
              "CMS_pileup_2018","CMS_muId_stat_2018","CMS_muIso_stat_2018",
              "CMS_emutrg_lowmuhighe_syst","CMS_emutrg_highmulowe_syst","CMS_emutrg_highmuhighe_syst","CMS_elasticRescaling","CMS_muId_syst","CMS_elId_syst","CMS_muIso_syst"]

       elif options.channel=="mutau":
           shapes=[
              "CMS_tauid_stat1_dm0_2016preVFP","CMS_tauid_stat1_dm1_2016preVFP","CMS_tauid_stat1_dm10_2016preVFP","CMS_tauid_stat1_dm11_2016preVFP","CMS_tauid_stat2_dm0_2016preVFP","CMS_tauid_stat2_dm1_2016preVFP","CMS_tauid_stat2_dm10_2016preVFP","CMS_tauid_stat2_dm11_2016preVFP","CMS_tauid_syst_2016preVFP","CMS_tauid_syst_dm0_2016preVFP","CMS_tauid_syst_dm1_2016preVFP","CMS_tauid_syst_dm10_2016preVFP","CMS_tauid_syst_dm11_2016preVFP","CMS_taues_dm0_2016preVFP","CMS_taues_dm1_2016preVFP","CMS_taues_3prong_2016preVFP","CMS_mutauFR_barrel_2016preVFP","CMS_mutauFR_endcap_2016preVFP","CMS_pileup_2016preVFP","CMS_mutautrg_2016preVFP","CMS_mutrg_stat_2016preVFP","CMS_muId_stat_2016preVFP","CMS_muIso_stat_2016preVFP",
              "CMS_tauid_stat1_dm0_2016postVFP","CMS_tauid_stat1_dm1_2016postVFP","CMS_tauid_stat1_dm10_2016postVFP","CMS_tauid_stat1_dm11_2016postVFP","CMS_tauid_stat2_dm0_2016postVFP","CMS_tauid_stat2_dm1_2016postVFP","CMS_tauid_stat2_dm10_2016postVFP","CMS_tauid_stat2_dm11_2016postVFP","CMS_tauid_syst_2016postVFP","CMS_tauid_syst_dm0_2016postVFP","CMS_tauid_syst_dm1_2016postVFP","CMS_tauid_syst_dm10_2016postVFP","CMS_tauid_syst_dm11_2016postVFP","CMS_taues_dm0_2016postVFP","CMS_taues_dm1_2016postVFP","CMS_taues_3prong_2016postVFP","CMS_mutauFR_barrel_2016postVFP","CMS_mutauFR_endcap_2016postVFP","CMS_pileup_2016postVFP","CMS_mutautrg_2016postVFP","CMS_mutrg_stat_2016postVFP","CMS_muId_stat_2016postVFP","CMS_muIso_stat_2016postVFP",
              "CMS_tauid_stat1_dm0_2017","CMS_tauid_stat1_dm1_2017","CMS_tauid_stat1_dm10_2017","CMS_tauid_stat1_dm11_2017","CMS_tauid_stat2_dm0_2017","CMS_tauid_stat2_dm1_2017","CMS_tauid_stat2_dm10_2017","CMS_tauid_stat2_dm11_2017","CMS_tauid_syst_2017","CMS_tauid_syst_dm0_2017","CMS_tauid_syst_dm1_2017","CMS_tauid_syst_dm10_2017","CMS_tauid_syst_dm11_2017","CMS_taues_dm0_2017","CMS_taues_dm1_2017","CMS_taues_3prong_2017","CMS_mutauFR_barrel_2017","CMS_mutauFR_endcap_2017","CMS_pileup_2017","CMS_mutautrg_2017","CMS_mutrg_stat_2017","CMS_muId_stat_2017","CMS_muIso_stat_2017",
              "CMS_tauid_stat1_dm0_2018","CMS_tauid_stat1_dm1_2018","CMS_tauid_stat1_dm10_2018","CMS_tauid_stat1_dm11_2018","CMS_tauid_stat2_dm0_2018","CMS_tauid_stat2_dm1_2018","CMS_tauid_stat2_dm10_2018","CMS_tauid_stat2_dm11_2018","CMS_tauid_syst_2018","CMS_tauid_syst_dm0_2018","CMS_tauid_syst_dm1_2018","CMS_tauid_syst_dm10_2018","CMS_tauid_syst_dm11_2018","CMS_taues_dm0_2018","CMS_taues_dm1_2018","CMS_taues_3prong_2018","CMS_mutauFR_barrel_2018","CMS_mutauFR_endcap_2018","CMS_pileup_2018","CMS_mutautrg_2018","CMS_mutrg_stat_2018","CMS_muId_stat_2018","CMS_muIso_stat_2018",
              "CMS_tauid_syst_alleras","CMS_elasticRescaling","CMS_mutrg_syst","CMS_muId_syst","CMS_muIso_syst"]
       elif options.channel=="tautau":
           shapes=[
              "CMS_tauid_stat1_dm0_2016preVFP","CMS_tauid_stat1_dm1_2016preVFP","CMS_tauid_stat1_dm10_2016preVFP","CMS_tauid_stat1_dm11_2016preVFP","CMS_tauid_stat2_dm0_2016preVFP","CMS_tauid_stat2_dm1_2016preVFP","CMS_tauid_stat2_dm10_2016preVFP","CMS_tauid_stat2_dm11_2016preVFP","CMS_tauid_syst_2016preVFP","CMS_tauid_syst_dm0_2016preVFP","CMS_tauid_syst_dm1_2016preVFP","CMS_tauid_syst_dm10_2016preVFP","CMS_tauid_syst_dm11_2016preVFP","CMS_taues_dm0_2016preVFP","CMS_taues_dm1_2016preVFP","CMS_taues_3prong_2016preVFP","CMS_pileup_2016preVFP","CMS_ditautrg_dm0_2016preVFP","CMS_ditautrg_dm1_2016preVFP","CMS_ditautrg_3prong_2016preVFP",
              "CMS_tauid_stat1_dm0_2016postVFP","CMS_tauid_stat1_dm1_2016postVFP","CMS_tauid_stat1_dm10_2016postVFP","CMS_tauid_stat1_dm11_2016postVFP","CMS_tauid_stat2_dm0_2016postVFP","CMS_tauid_stat2_dm1_2016postVFP","CMS_tauid_stat2_dm10_2016postVFP","CMS_tauid_stat2_dm11_2016postVFP","CMS_tauid_syst_2016postVFP","CMS_tauid_syst_dm0_2016postVFP","CMS_tauid_syst_dm1_2016postVFP","CMS_tauid_syst_dm10_2016postVFP","CMS_tauid_syst_dm11_2016postVFP","CMS_taues_dm0_2016postVFP","CMS_taues_dm1_2016postVFP","CMS_taues_3prong_2016postVFP","CMS_pileup_2016postVFP","CMS_ditautrg_dm0_2016postVFP","CMS_ditautrg_dm1_2016postVFP","CMS_ditautrg_3prong_2016postVFP",
              "CMS_tauid_stat1_dm0_2017","CMS_tauid_stat1_dm1_2017","CMS_tauid_stat1_dm10_2017","CMS_tauid_stat1_dm11_2017","CMS_tauid_stat2_dm0_2017","CMS_tauid_stat2_dm1_2017","CMS_tauid_stat2_dm10_2017","CMS_tauid_stat2_dm11_2017","CMS_tauid_syst_2017","CMS_tauid_syst_dm0_2017","CMS_tauid_syst_dm1_2017","CMS_tauid_syst_dm10_2017","CMS_tauid_syst_dm11_2017","CMS_taues_dm0_2017","CMS_taues_dm1_2017","CMS_taues_3prong_2017","CMS_pileup_2017","CMS_ditautrg_dm0_2017","CMS_ditautrg_dm1_2017","CMS_ditautrg_3prong_2017",
              "CMS_tauid_stat1_dm0_2018","CMS_tauid_stat1_dm1_2018","CMS_tauid_stat1_dm10_2018","CMS_tauid_stat1_dm11_2018","CMS_tauid_stat2_dm0_2018","CMS_tauid_stat2_dm1_2018","CMS_tauid_stat2_dm10_2018","CMS_tauid_stat2_dm11_2018","CMS_tauid_syst_2018","CMS_tauid_syst_dm0_2018","CMS_tauid_syst_dm1_2018","CMS_tauid_syst_dm10_2018","CMS_tauid_syst_dm11_2018","CMS_taues_dm0_2018","CMS_taues_dm1_2018","CMS_taues_3prong_2018","CMS_pileup_2018","CMS_ditautrg_dm0_2018","CMS_ditautrg_dm1_2018","CMS_ditautrg_3prong_2018",
              "CMS_tauid_syst_alleras","CMS_elasticRescaling"]

    for c in range(0,ncat):

       nominal=fin.Get(categories[c]).Get("GGTT_0p0")
       if options.channel=="mutau" or options.channel=="tautau": nominal=falt.Get(categories[c]).Get("GGTT")
       mydir=fout.mkdir(categories[c])
       mydir.cd()

       for jj in range(1,nominal.GetSize()-1):
	  myhist=nominal.Clone()
          for jjj in range(1,nominal.GetSize()-1):
	     if jjj!=jj:
	        myhist.SetBinContent(jjj,0.)
		myhist.SetBinError(jjj,0.)
	     else:
                myhist.SetBinContent(jjj,1.0)
                if nominal.GetBinContent(jj)>0: myhist.SetBinError(jjj,1.0*nominal.GetBinError(jj)/nominal.GetBinContent(jj))
	  myhist.SetName("TauG2_"+categories[c]+"_bin"+str(jj))
          myhist.Write()
	  for s in shapes:
	     myhist_up=myhist.Clone()
	     print "GGTT_0p0_"+s+"Up"
	     if nominal.GetBinContent(jj)>0:
	        if options.channel=="mutau" or options.channel=="tautau": myhist_up.Scale(falt.Get(categories[c]).Get("GGTT_"+s+"Up").GetBinContent(jj)/nominal.GetBinContent(jj))
	        else: myhist_up.Scale(fin.Get(categories[c]).Get("GGTT_0p0_"+s+"Up").GetBinContent(jj)/nominal.GetBinContent(jj))
  	     myhist_up.SetName("TauG2_"+categories[c]+"_bin"+str(jj)+"_"+s+"Up")
	     myhist_up.Write()
             myhist_down=myhist.Clone()
             if nominal.GetBinContent(jj)>0:
	        if options.channel=="mutau" or options.channel=="tautau": myhist_down.Scale(falt.Get(categories[c]).Get("GGTT_"+s+"Down").GetBinContent(jj)/nominal.GetBinContent(jj))
                else: myhist_down.Scale(fin.Get(categories[c]).Get("GGTT_0p0_"+s+"Down").GetBinContent(jj)/nominal.GetBinContent(jj))
             myhist_down.SetName("TauG2_"+categories[c]+"_bin"+str(jj)+"_"+s+"Down")
             myhist_down.Write()

          nom=nominal.GetBinContent(jj)
          n = len(ceBR)
          x, y, exl, exh, eyl, eyh = array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' )
          for k in range(0,len(ceBR)):
             hist=fin.Get(categories[c]+"/GGTT_"+ceBRname[k])
             #print "et_1/GGTT_"+ceBRname[k]
             exl.append(0.0)
             exh.append(0.0)
             x.append(at[k])
             y.append(hist.GetBinContent(jj))
             eyl.append(hist.GetBinError(jj))
             eyh.append(hist.GetBinError(jj))
             

          gr = ROOT.TGraphAsymmErrors( n, x, y,exl,exh,eyl,eyh )
          gr.SetLineColor( 2 )
          #gr.SetLineWidth( 4 )
          gr.SetMarkerColor( 4 )
          gr.SetMarkerStyle( 21 )
          gr.SetTitle( '' )
          gr.GetXaxis().SetTitle( 'a_{#tau} x 100' )
          gr.GetYaxis().SetTitle( 'Signal count' )
          gr.GetXaxis().SetTitleSize(0.06)
          gr.GetYaxis().SetTitleSize(0.06)
          gr.GetXaxis().SetTitleOffset(0.8)
          #gr.Draw( 'ACP' )

          total = ROOT.TF1( 'total', "pol5", -4, 4, 0)
          total.SetLineColor( ROOT.TColor.GetColor("#12cadd") )
          total.SetLineWidth(4)
          gr.Fit(total,"R")
          gr.Draw("AP")


          categ  = ROOT.TPaveText(0.35, 0.5+0.013, 0.83, 0.50+0.155, "NDC")
          categ.SetBorderSize(   0 )
          categ.SetFillStyle(    0 )
          categ.SetTextAlign(   12 )
          categ.SetTextSize ( 0.06 )
          categ.SetTextColor(    1 )
          categ.SetTextFont (   42 )
	  if options.channel=="emu": categ.AddText("e#mu "+str(options.year))
          elif options.channel=="etau": categ.AddText("e#tau_{h} "+str(options.year))
          elif options.channel=="mutau": categ.AddText("#mu#tau_{h} "+str(options.year))
          elif options.channel=="tautau": categ.AddText("#tau_{h}#tau_{h} "+str(options.year))
	  categ.AddText(str(nominal.GetBinLowEdge(jj))+" < m_{vis} < "+str(nominal.GetBinLowEdge(jj)+(nominal.GetBinWidth(jj)))+" GeV")
          categ.Draw("same")


	  #self.modelBuilder.factory_('expr::scale_et_0_bin1("@0*@1",mu_fid,rho_0_45)')
 	  physics_model.write("self.modelBuilder.factory_('expr::scale_")
          physics_model.write(categories[c])
          #physics_model.write("_")
          #physics_model.write(options.year)
          physics_model.write("_bin")
          physics_model.write(str(jj))
          physics_model.write('("(')
          physics_model.write(str(total.GetParameter(0))+"+"+str(total.GetParameter(1))+"*@0+"+str(total.GetParameter(2))+"*@0*@0+"+str(total.GetParameter(3))+"*@0*@0*@0+"+str(total.GetParameter(4))+"*@0*@0*@0*@0+"+str(total.GetParameter(5))+"*@0*@0*@0*@0*@0)*@1")
          physics_model.write('"')
          physics_model.write(",atau,mu)')\n")


          canv.cd()
          ROOT.gPad.Draw()
          ROOT.gPad.RedrawAxis()
          canv.Modified()
          canv.SaveAs("plots_"+short_channel+"_"+options.year+"/bsm_extrap_"+categories[c]+"_bin"+str(jj)+".png")
          canv.SaveAs("plots_"+short_channel+"_"+options.year+"/bsm_extrap_"+categories[c]+"_bin"+str(jj)+".pdf")

    physics_model.close()
