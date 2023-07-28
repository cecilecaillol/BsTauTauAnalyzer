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

    postfixName=["","_CMS_fakebkg_emu_stat_pte15to24_ptmu24to35_"+year4+"Down","_CMS_fakebkg_emu_stat_pte15to24_ptmu24to35_"+year4+"Up","_CMS_fakebkg_emu_stat_pte15to24_ptmu35to45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte15to24_ptmu35to45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte15to24_ptmugt45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte15to24_ptmugt45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte24to35_ptmu15to24_"+year4+"Down","_CMS_fakebkg_emu_stat_pte24to35_ptmu15to24_"+year4+"Up","_CMS_fakebkg_emu_stat_pte24to35_ptmu24to35_"+year4+"Down","_CMS_fakebkg_emu_stat_pte24to35_ptmu24to35_"+year4+"Up","_CMS_fakebkg_emu_stat_pte24to35_ptmu35to45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte24to35_ptmu35to45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte24to35_ptmugt45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte24to35_ptmugt45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte35to45_ptmu15to24_"+year4+"Down","_CMS_fakebkg_emu_stat_pte35to45_ptmu15to24_"+year4+"Up","_CMS_fakebkg_emu_stat_pte35to45_ptmu24to35_"+year4+"Down","_CMS_fakebkg_emu_stat_pte35to45_ptmu24to35_"+year4+"Up","_CMS_fakebkg_emu_stat_pte35to45_ptmu35to45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte35to45_ptmu35to45_"+year4+"Up","_CMS_fakebkg_emu_stat_pte35to45_ptmugt45_"+year4+"Down","_CMS_fakebkg_emu_stat_pte35to45_ptmugt45_"+year4+"Up","_CMS_fakebkg_emu_stat_ptegt45_ptmu15to24_"+year4+"Down","_CMS_fakebkg_emu_stat_ptegt45_ptmu15to24_"+year4+"Up","_CMS_fakebkg_emu_stat_ptegt45_ptmu24to35_"+year4+"Down","_CMS_fakebkg_emu_stat_ptegt45_ptmu24to35_"+year4+"Up","_CMS_fakebkg_emu_stat_ptegt45_ptmu35to45_"+year4+"Down","_CMS_fakebkg_emu_stat_ptegt45_ptmu35to45_"+year4+"Up","_CMS_fakebkg_emu_stat_ptegt45_ptmugt45_"+year4+"Down","_CMS_fakebkg_emu_stat_ptegt45_ptmugt45_"+year4+"Up"]

    nbhist=1 

    fVV=ROOT.TFile("output_emu_"+options.year+"/VV.root","r")
    fTop=ROOT.TFile("output_emu_"+options.year+"/top.root","r")
    fDY=ROOT.TFile("output_emu_"+options.year+"/DY.root","r")
    fData=ROOT.TFile("output_emu_"+options.year+"/MuonEG.root","r")
    fout=ROOT.TFile("output_emu_"+options.year+"/Fake.root","recreate")

    ncat=9
    if is_control==0: 
	ncat=2
        nbhist=1+30

    for j in range(0,ncat):

       dir0=fout.mkdir("em_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]
          print postfix
          h0=fData.Get("em_"+str(j)+"_anti/data_obs"+postfix)
          h0.Add(fVV.Get("em_"+str(j)+"_anti/VV"+postfix),-1)
          h0.Add(fDY.Get("em_"+str(j)+"_anti/ZTT"+postfix),-1)
          h0.Add(fTop.Get("em_"+str(j)+"_anti/top"+postfix),-1)
          for i in range(0,h0.GetSize()-2):
              if h0.GetBinContent(i)<0:
                  h0.SetBinError(i,max(0,h0.GetBinError(i)+h0.GetBinError(i)))
                  h0.SetBinContent(i,0)

          h0R=fData.Get("emR_"+str(j)+"_anti/data_obs"+postfix)
          h0R.Add(fVV.Get("emR_"+str(j)+"_anti/VV"+postfix),-1)
          h0R.Add(fDY.Get("emR_"+str(j)+"_anti/ZTT"+postfix),-1)
          h0R.Add(fTop.Get("emR_"+str(j)+"_anti/top"+postfix),-1)
          for i in range(0,h0R.GetSize()-2):
              if h0R.GetBinContent(i)<0:
                  h0R.SetBinError(i,max(0,h0R.GetBinError(i)+h0R.GetBinError(i)))
                  h0R.SetBinContent(i,0)


          fout.cd()
          dir0.cd()
          h0.SetName("rawFake"+postfix)
          h0.Write()
	  print j, h0.Integral(), h0R.Integral()
  	  h0R.Scale(h0.Integral()/h0R.Integral())
          h0R.SetName("Fake"+postfix)
          h0R.Write()


