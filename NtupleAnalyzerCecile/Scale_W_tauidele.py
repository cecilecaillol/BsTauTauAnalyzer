if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2018")

    options = parser.parse_args()
    postfixName=[""]

    nbhist=1 

    fVV=ROOT.TFile("output_tauidele_"+options.year+"/VV.root","r")
    fTT=ROOT.TFile("output_tauidele_"+options.year+"/TT.root","r")
    fST=ROOT.TFile("output_tauidele_"+options.year+"/ST.root","r")
    fZTT=ROOT.TFile("output_tauidele_"+options.year+"/ZTT.root","r")
    fZLL=ROOT.TFile("output_tauidele_"+options.year+"/ZLL.root","r")
    fW=ROOT.TFile("output_tauidele_"+options.year+"/W.root","r")
    fQCD=ROOT.TFile("output_tauidele_"+options.year+"/QCD.root","r")
    fData=ROOT.TFile("output_tauidele_"+options.year+"/EGamma.root","r")
    fout=ROOT.TFile("output_tauidele_"+options.year+"/Wrescaled.root","recreate")

    ncat=4
    for j in range(0,ncat):
       print "tauidele_"+str(j)
       dir0=fout.mkdir("tauidele_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]
          hW=fW.Get("tauidele_"+str(j)+"/W"+postfix).Clone()
	  for z in range(2,hW.GetSize()):
	     if hW.GetBinContent(z)==0:
		hW.SetBinContent(z,hW.GetBinContent(z-1))
                hW.SetBinError(z,hW.GetBinError(z-1))

	  if j==0 or j==2:
	     wnorm=fW.Get("tauidele_2/W"+postfix).Integral(1,2)
	     diff=fData.Get("tauidele_2/data_obs"+postfix).Integral(1,2)-(fVV.Get("tauidele_2/VV"+postfix).Integral(1,2)+fZLL.Get("tauidele_2/ZLL"+postfix).Integral(1,2)+fZTT.Get("tauidele_2/ZTT"+postfix).Integral(1,2)+fTT.Get("tauidele_2/TT"+postfix).Integral(1,2)+fST.Get("tauidele_2/ST"+postfix).Integral(1,2)+fQCD.Get("tauidele_2/QCD"+postfix).Integral(1,2))
	     sf=diff/wnorm
	     print sf
	     hW.Scale(sf)

          if j==1 or j==3:
             wnorm=fW.Get("tauidele_3/W"+postfix).Integral(1,4)
             diff=fData.Get("tauidele_3/data_obs"+postfix).Integral(1,4)-(fVV.Get("tauidele_3/VV"+postfix).Integral(1,4)+fZLL.Get("tauidele_3/ZLL"+postfix).Integral(1,4)+fZTT.Get("tauidele_3/ZTT"+postfix).Integral(1,4)+fTT.Get("tauidele_3/TT"+postfix).Integral(1,4)+fST.Get("tauidele_3/ST"+postfix).Integral(1,4)+fQCD.Get("tauidele_3/QCD"+postfix).Integral(1,4))
             sf=diff/wnorm
             print sf
             hW.Scale(sf)

          fout.cd()
          dir0.cd()
          hW.SetName("Wrescaled"+postfix)
          hW.Write()

