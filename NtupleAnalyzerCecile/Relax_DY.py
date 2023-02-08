if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Which TES?")

    options = parser.parse_args()
    postfixName=[""]

    nbhist=1 

    fDY=ROOT.TFile("output_etau_"+options.year+"/DY.root","r")
    fout=ROOT.TFile("output_etau_"+options.year+"/DYrescaled.root","recreate")

    ncat=9
    for j in range(0,ncat):

       dir0=fout.mkdir("et_"+str(j))
       dir0A=fout.mkdir("et_"+str(j)+"_anti")

       for k in range(0,nbhist):
          postfix=postfixName[k]
          hZLL2=fDY.Get("et_"+str(j)+"/ZLL"+postfix)
          hZLL1=fDY.Get("etR_"+str(j)+"/ZLL"+postfix).Clone()
	  hZLL1.Scale(hZLL2.Integral()/hZLL1.Integral())

          hZLL2A=fDY.Get("et_"+str(j)+"_anti/ZLL"+postfix)
          hZLL1A=fDY.Get("etR_"+str(j)+"_anti/ZLL"+postfix).Clone()
          hZLL1A.Scale(hZLL2A.Integral()/hZLL1A.Integral())

          hZTT2=fDY.Get("et_"+str(j)+"/ZTT"+postfix)
          hZTT1=fDY.Get("etR_"+str(j)+"/ZTT"+postfix).Clone()
          hZTT1.Scale(hZTT2.Integral()/hZTT1.Integral())

          hZTT2A=fDY.Get("et_"+str(j)+"_anti/ZTT"+postfix)
          hZTT1A=fDY.Get("etR_"+str(j)+"_anti/ZTT"+postfix).Clone()
          hZTT1A.Scale(hZTT2A.Integral()/hZTT1A.Integral())

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

