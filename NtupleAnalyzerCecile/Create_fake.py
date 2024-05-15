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

    postfixName=["","_CMS_jetfake_w_invertMTDown","_CMS_jetfake_w_invertMTUp","_CMS_jetfake_qcd_invertOSDown","_CMS_jetfake_qcd_invertOSUp","_CMS_jetfake_tauptextrap_w_et_dm0_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm0_"+year4+"Up","_CMS_jetfake_tauptextrap_w_et_dm1_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm1_"+year4+"Up","_CMS_jetfake_tauptextrap_w_et_dm10_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm10_"+year4+"Up","_CMS_jetfake_tauptextrap_w_et_dm11_"+year4+"Down","_CMS_jetfake_tauptextrap_w_et_dm11_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm0_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm0_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm1_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm1_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm10_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm10_"+year4+"Up","_CMS_jetfake_tauptextrap_qcd_et_dm11_"+year4+"Down","_CMS_jetfake_tauptextrap_qcd_et_dm11_"+year4+"Up","_CMS_jetfake_wfractionDown","_CMS_jetfake_wfractionUp","_CMS_jetfake_ntracksextrap_w_et_dm0Down","_CMS_jetfake_ntracksextrap_w_et_dm0Up","_CMS_jetfake_ntracksextrap_w_et_dm1Down","_CMS_jetfake_ntracksextrap_w_et_dm1Up","_CMS_jetfake_ntracksextrap_w_et_dm10Down","_CMS_jetfake_ntracksextrap_w_et_dm10Up","_CMS_jetfake_ntracksextrap_w_et_dm11Down","_CMS_jetfake_ntracksextrap_w_et_dm11Up","_CMS_jetfake_ntracksextrap_qcd_et_dm0Down","_CMS_jetfake_ntracksextrap_qcd_et_dm0Up","_CMS_jetfake_ntracksextrap_qcd_et_dm1Down","_CMS_jetfake_ntracksextrap_qcd_et_dm1Up","_CMS_jetfake_ntracksextrap_qcd_et_dm10Down","_CMS_jetfake_ntracksextrap_qcd_et_dm10Up","_CMS_jetfake_ntracksextrap_qcd_et_dm11Down","_CMS_jetfake_ntracksextrap_qcd_et_dm11Up","_CMS_jetfake_ntracksextrap_w_etDown","_CMS_jetfake_ntracksextrap_w_etUp","_CMS_jetfake_ntracksextrap_qcd_etDown","_CMS_jetfake_ntracksextrap_qcd_etUp"]

    nbhist=1
    if is_control==0: nbhist=1+42 

    fVV=ROOT.TFile("output_etau_"+options.year+"/VV.root","r")
    fTop=ROOT.TFile("output_etau_"+options.year+"/top.root","r")
    fGGEE=ROOT.TFile("output_etau_"+options.year+"/GGEE.root","r")
    fDY=ROOT.TFile("output_etau_"+options.year+"/DYrescaled.root","r")
    fData=ROOT.TFile("output_etau_2018/EGamma.root","r")
    if options.year=="2017" or options.year=="2016pre" or options.year=="2016post": fData=ROOT.TFile("output_etau_"+options.year+"/SingleElectron.root","r")
    fout=ROOT.TFile("output_etau_"+options.year+"/Fake.root","recreate")

    ncat=9
    if is_control==0: ncat=6

    for j in range(0,ncat):

       dir0=fout.mkdir("et_"+str(j))

       for k in range(0,nbhist):
	  print k,postfixName[k]
          postfix=postfixName[k]
          h0=fData.Get("et_"+str(j)+"_anti/data_obs"+postfix).Clone()
	  hinitial=fData.Get("et_"+str(j)+"_anti/data_obs"+postfix).Clone()
	  for i in range(1,h0.GetSize()-1):
	     if h0.GetBinContent(i)<0.01:
		h0.SetBinError(i,1.8*0.15*2) # error on 0 count times average FR
             elif h0.GetBinContent(i)==h0.GetBinError(i): # 1 count
                h0.SetBinError(i,2.3*h0.GetBinContent(i)) # error on 0 count times average FR
             elif h0.GetBinContent(i)<0.8 and h0.GetBinContent(i)>h0.GetBinError(i): # 2 count
                h0.SetBinError(i,1.35*h0.GetBinContent(i))
          h0.Add(fVV.Get("et_"+str(j)+"_anti/VV"),-1)
	  print("et_"+str(j)+"_anti/ZLL")
	  print(fDY.Get("et_"+str(j)+"_anti/ZLL").Integral())
          h0.Add(fDY.Get("et_"+str(j)+"_anti/ZLL"),-1)
          h0.Add(fDY.Get("et_"+str(j)+"_anti/ZTT"),-1)
          h0.Add(fTop.Get("et_"+str(j)+"_anti/top"),-1)
          h0.Add(fGGEE.Get("et_"+str(j)+"_anti/GGEE"),-1)
          for i in range(1,h0.GetSize()-1):
              if h0.GetBinContent(i)<0:
	          #h0.SetBinError(i,h0.GetBinContent(i)+h0.GetBinError(i))
                  h0.SetBinContent(i,0)

          fout.cd()
          dir0.cd()
          h0.SetName("Fake"+postfix)
          h0.Write()

