if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Which TES?")

    options = parser.parse_args()
    postfixName=[""]


    fVV=ROOT.TFile("output_emu_"+options.year+"/VV.root","r")
    fTT=ROOT.TFile("output_emu_"+options.year+"/TT.root","r")
    fST=ROOT.TFile("output_emu_"+options.year+"/ST.root","r")
    fDY=ROOT.TFile("output_emu_"+options.year+"/DY.root","r")
    fData=ROOT.TFile("output_emu_"+options.year+"/MuonEG.root","r")
    fout=ROOT.TFile("emu_fr_2018.root","recreate")

    h0iso=fData.Get("h_fr_iso")
    h0iso.Add(fVV.Get("h_fr_iso"),-1)
    h0iso.Add(fDY.Get("h_fr_iso"),-1)
    h0iso.Add(fTT.Get("h_fr_iso"),-1)
    h0iso.Add(fST.Get("h_fr_iso"),-1)

    h0anti=fData.Get("h_fr_anti")
    h0anti.Add(fVV.Get("h_fr_anti"),-1)
    h0anti.Add(fDY.Get("h_fr_anti"),-1)
    h0anti.Add(fTT.Get("h_fr_anti"),-1)
    h0anti.Add(fST.Get("h_fr_anti"),-1)

    h0iso.Divide(h0anti)
    fout.cd()
    h0iso.SetName("FR")
    h0iso.Write()

