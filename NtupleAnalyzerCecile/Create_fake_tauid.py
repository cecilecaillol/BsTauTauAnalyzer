if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2018")

    options = parser.parse_args()
    postfixName=["","_tauesDown","_tauesUp","_mesDown","_mesUp","_fesDown","_fesUp","_mvisresDown","_mvisresUp"]

    nbhist=1+8 

    fVV=ROOT.TFile("output_tauid_"+options.year+"/VV.root","r")
    fTT=ROOT.TFile("output_tauid_"+options.year+"/TT.root","r")
    fST=ROOT.TFile("output_tauid_"+options.year+"/ST.root","r")
    fZTT=ROOT.TFile("output_tauid_"+options.year+"/ZTT.root","r")
    fZLL=ROOT.TFile("output_tauid_"+options.year+"/ZLL.root","r")
    fW=ROOT.TFile("output_tauid_"+options.year+"/W.root","r")
    fData=ROOT.TFile("output_tauid_"+options.year+"/SingleMuon.root","r")
    fout=ROOT.TFile("output_tauid_"+options.year+"/QCD.root","recreate")

    ncat=8
    for j in range(0,ncat):
       print "tauid_"+str(j)
       dir0=fout.mkdir("tauid_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]
          h0=fData.Get("tauid_"+str(j)+"_SS/data_obs")
          h0.Add(fVV.Get("tauid_"+str(j)+"_SS/VV"+postfix),-1)
          h0.Add(fZLL.Get("tauid_"+str(j)+"_SS/ZLL"+postfix),-1)
          h0.Add(fZTT.Get("tauid_"+str(j)+"_SS/ZTT"+postfix),-1)
          h0.Add(fW.Get("tauid_"+str(j)+"_SS/W"+postfix),-1)
          h0.Add(fTT.Get("tauid_"+str(j)+"_SS/TT"+postfix),-1)
          h0.Add(fST.Get("tauid_"+str(j)+"_SS/ST"+postfix),-1)
          for i in range(0,h0.GetSize()-2):
              if h0.GetBinContent(i)<0:
                  h0.SetBinError(i,max(0,h0.GetBinError(i)+h0.GetBinError(i)))
                  h0.SetBinContent(i,0)

          fout.cd()
          dir0.cd()
          h0.SetName("QCD"+postfix)
          h0.Write()

