if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Which TES?")

    options = parser.parse_args()
    postfixName=[""]

    nbhist=1 

    fVV=ROOT.TFile("output_emu_"+options.year+"/VV.root","r")
    fTT=ROOT.TFile("output_emu_"+options.year+"/TT.root","r")
    fST=ROOT.TFile("output_emu_"+options.year+"/ST.root","r")
    fDY=ROOT.TFile("output_emu_"+options.year+"/DY.root","r")
    fData=ROOT.TFile("output_emu_"+options.year+"/MuonEG.root","r")
    fout=ROOT.TFile("output_emu_"+options.year+"/Fake.root","recreate")

    ncat=9
    for j in range(0,ncat):

       dir0=fout.mkdir("em_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]
          h0=fData.Get("em_"+str(j)+"_anti/data_obs"+postfix)
          h0.Add(fVV.Get("em_"+str(j)+"_anti/VV"+postfix),-1)
          h0.Add(fDY.Get("em_"+str(j)+"_anti/ZTT"+postfix),-1)
          h0.Add(fTT.Get("em_"+str(j)+"_anti/TT"+postfix),-1)
          h0.Add(fST.Get("em_"+str(j)+"_anti/ST"+postfix),-1)
          for i in range(0,h0.GetSize()-2):
              if h0.GetBinContent(i)<0:
                  h0.SetBinError(i,max(0,h0.GetBinError(i)+h0.GetBinError(i)))
                  h0.SetBinContent(i,0)

          fout.cd()
          dir0.cd()
          h0.SetName("Fake"+postfix)
          h0.Write()

    for j in range(0,ncat):

       dir0=fout.mkdir("em_"+str(j)+"_lNlA")

       for k in range(0,nbhist):
          postfix=postfixName[k]
          h0=fData.Get("em_"+str(j)+"_lNlA_anti/data_obs"+postfix)
          h0.Add(fVV.Get("em_"+str(j)+"_lNlA_anti/VV"+postfix),-1)
          h0.Add(fDY.Get("em_"+str(j)+"_lNlA_anti/ZTT"+postfix),-1)
          h0.Add(fTT.Get("em_"+str(j)+"_lNlA_anti/TT"+postfix),-1)
          h0.Add(fST.Get("em_"+str(j)+"_lNlA_anti/ST"+postfix),-1)
          for i in range(0,h0.GetSize()-2):
              if h0.GetBinContent(i)<0:
                  h0.SetBinError(i,max(0,h0.GetBinError(i)+h0.GetBinError(i)))
                  h0.SetBinContent(i,0)

          fout.cd()
          dir0.cd()
          h0.SetName("Fake"+postfix)
          h0.Write()

