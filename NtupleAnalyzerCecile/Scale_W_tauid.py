if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2018")

    options = parser.parse_args()
    postfixName=[""]

    nbhist=1 

    fVV=ROOT.TFile("output_tauid_"+options.year+"/VV.root","r")
    fTT=ROOT.TFile("output_tauid_"+options.year+"/TT.root","r")
    fST=ROOT.TFile("output_tauid_"+options.year+"/ST.root","r")
    fZTT=ROOT.TFile("output_tauid_"+options.year+"/ZTT.root","r")
    fZLL=ROOT.TFile("output_tauid_"+options.year+"/ZLL.root","r")
    fW=ROOT.TFile("output_tauid_"+options.year+"/W.root","r")
    fQCD=ROOT.TFile("output_tauid_"+options.year+"/QCD.root","r")
    fData=ROOT.TFile("output_tauid_"+options.year+"/SingleMuon.root","r")
    fout=ROOT.TFile("output_tauid_"+options.year+"/Wrescaled.root","recreate")

    ncat=8
    for j in range(0,ncat):
       print "tauid_"+str(j)
       dir0=fout.mkdir("tauid_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]
          hW=fW.Get("tauid_"+str(j)+"/W"+postfix).Clone()

	  if j==0 or j==2:
	     wnorm=fW.Get("tauid_2/W"+postfix).Integral(1,8)
	     diff=fData.Get("tauid_2/data_obs"+postfix).Integral(1,8)-(fVV.Get("tauid_2/VV"+postfix).Integral(1,8)+fZLL.Get("tauid_2/ZLL"+postfix).Integral(1,8)+fZTT.Get("tauid_2/ZTT"+postfix).Integral(1,8)+fTT.Get("tauid_2/TT"+postfix).Integral(1,8)+fST.Get("tauid_2/ST"+postfix).Integral(1,8)+fQCD.Get("tauid_2/QCD"+postfix).Integral(1,8))
	     sf=diff/wnorm
	     print sf
	     hW.Scale(sf)

          if j==1 or j==3:
             wnorm=fW.Get("tauid_3/W"+postfix).Integral(1,8)
             diff=fData.Get("tauid_3/data_obs"+postfix).Integral(1,8)-(fVV.Get("tauid_3/VV"+postfix).Integral(1,8)+fZLL.Get("tauid_3/ZLL"+postfix).Integral(1,8)+fZTT.Get("tauid_3/ZTT"+postfix).Integral(1,8)+fTT.Get("tauid_3/TT"+postfix).Integral(1,8)+fST.Get("tauid_3/ST"+postfix).Integral(1,8)+fQCD.Get("tauid_3/QCD"+postfix).Integral(1,8))
             sf=diff/wnorm
             print sf
             hW.Scale(sf)

          if j==4 or j==5:
             wnorm=fW.Get("tauid_5/W"+postfix).Integral(1,8)
             diff=fData.Get("tauid_5/data_obs"+postfix).Integral(1,8)-(fVV.Get("tauid_5/VV"+postfix).Integral(1,8)+fZLL.Get("tauid_5/ZLL"+postfix).Integral(1,8)+fZTT.Get("tauid_5/ZTT"+postfix).Integral(1,8)+fTT.Get("tauid_5/TT"+postfix).Integral(1,8)+fST.Get("tauid_5/ST"+postfix).Integral(1,8)+fQCD.Get("tauid_5/QCD"+postfix).Integral(1,8))
             sf=diff/wnorm
             print sf
             hW.Scale(sf)

          if j==6 or j==7:
             wnorm=fW.Get("tauid_7/W"+postfix).Integral(1,8)
             diff=fData.Get("tauid_7/data_obs"+postfix).Integral(1,8)-(fVV.Get("tauid_7/VV"+postfix).Integral(1,8)+fZLL.Get("tauid_7/ZLL"+postfix).Integral(1,8)+fZTT.Get("tauid_7/ZTT"+postfix).Integral(1,8)+fTT.Get("tauid_7/TT"+postfix).Integral(1,8)+fST.Get("tauid_7/ST"+postfix).Integral(1,8)+fQCD.Get("tauid_7/QCD"+postfix).Integral(1,8))
             sf=diff/wnorm
             print sf
             hW.Scale(sf)

          fout.cd()
          dir0.cd()
          hW.SetName("Wrescaled"+postfix)
          hW.Write()

