if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Which TES?")

    options = parser.parse_args()
    postfixName=[""]

    nbhist=1 

    fDY=ROOT.TFile("output_mumu_"+options.year+"/DY.root","r")
    fData=ROOT.TFile("output_mumu_"+options.year+"/Data.root","r")
    fout=ROOT.TFile("output_mumu_"+options.year+"/Fake.root","recreate")

    ncat=4
    for j in range(0,ncat):

       dir0=fout.mkdir("mumu"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]
          h0=fData.Get("mumu"+str(j)+"_SS/data_obs"+postfix)
          h0.Add(fDY.Get("mumu"+str(j)+"_SS/DY"+postfix),-1)
          for i in range(0,h0.GetSize()-2):
              if h0.GetBinContent(i)<0:
                  h0.SetBinError(i,max(0,h0.GetBinError(i)+h0.GetBinError(i)))
                  h0.SetBinContent(i,0)

          fout.cd()
          dir0.cd()
          h0.SetName("Fake"+postfix)
          h0.Write()


