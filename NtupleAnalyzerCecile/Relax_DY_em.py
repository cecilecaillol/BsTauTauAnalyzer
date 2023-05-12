if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')

    options = parser.parse_args()
    postfixName=[""]

    nbhist=1 

    fDY=ROOT.TFile("output_emu_"+options.year+"/DY.root","r")
    fout=ROOT.TFile("output_emu_"+options.year+"/DYrescaled.root","recreate")

    ncat=9
    for j in range(0,ncat):

       dir0=fout.mkdir("em_"+str(j))
       dir0A=fout.mkdir("em_"+str(j)+"_anti")

       for k in range(0,nbhist):
          postfix=postfixName[k]
          hZTT2=fDY.Get("em_"+str(j)+"/ZTT"+postfix)
          hZTT1=fDY.Get("emR_"+str(j)+"/ZTT"+postfix).Clone()
          hZTT1.Scale(hZTT2.Integral()/hZTT1.Integral())

          hZTT2A=fDY.Get("em_"+str(j)+"_anti/ZTT"+postfix)
          hZTT1A=fDY.Get("emR_"+str(j)+"_anti/ZTT"+postfix).Clone()
          hZTT1A.Scale(hZTT2A.Integral()/hZTT1A.Integral())

          fout.cd()
          dir0.cd()
          hZTT1.SetName("ZTT"+postfix)
          hZTT1.Write()

          dir0A.cd()
          hZTT1A.SetName("ZTT"+postfix)
          hZTT1A.Write()

