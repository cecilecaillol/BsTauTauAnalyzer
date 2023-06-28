def add_lumi(year):
    lowX=0.35
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.055)
    lumi.SetTextFont (   42 )
    if (year=="2018"): lumi.AddText("2018, 60 fb^{-1} (13 TeV)")
    if (year=="2017"): lumi.AddText("2017, 41 fb^{-1} (13 TeV)")
    if (year=="2016"): lumi.AddText("2016, 36 fb^{-1} (13 TeV)")
    if (year=="2016pre"): lumi.AddText("2016 preVFP, 20 fb^{-1} (13 TeV)")
    if (year=="2016post"): lumi.AddText("2016 postVFP, 16 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.16
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.065)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi


if __name__ == "__main__":

    import ROOT
    import argparse
    ROOT.gStyle.SetOptStat(0)
    ROOT.gStyle.SetPaintTextFormat("1.2f");

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')

    options = parser.parse_args()
    postfixName=[""]


    fVV=ROOT.TFile("output_emu_"+options.year+"/VV.root","r")
    fTop=ROOT.TFile("output_emu_"+options.year+"/top.root","r")
    fDY=ROOT.TFile("output_emu_"+options.year+"/DY.root","r")
    fData=ROOT.TFile("output_emu_"+options.year+"/MuonEG.root","r")
    fout=ROOT.TFile("emu_fr_"+options.year+".root","recreate")

    h0iso=fData.Get("h_fr_iso")
    h0iso.Add(fVV.Get("h_fr_iso"),-1)
    h0iso.Add(fDY.Get("h_fr_iso"),-1)
    h0iso.Add(fTop.Get("h_fr_iso"),-1)
    h0anti=fData.Get("h_fr_anti")
    h0anti.Add(fVV.Get("h_fr_anti"),-1)
    h0anti.Add(fDY.Get("h_fr_anti"),-1)
    h0anti.Add(fTop.Get("h_fr_anti"),-1)
    h0iso.Divide(h0anti)
    fout.cd()
    h0iso.SetName("FR")
    h0iso.Write()

    h0highiso=fData.Get("h_frhigh_iso")
    h0highiso.Add(fVV.Get("h_frhigh_iso"),-1)
    h0highiso.Add(fDY.Get("h_frhigh_iso"),-1)
    h0highiso.Add(fTop.Get("h_frhigh_iso"),-1)
    h0highanti=fData.Get("h_frhigh_anti")
    h0highanti.Add(fVV.Get("h_frhigh_anti"),-1)
    h0highanti.Add(fDY.Get("h_frhigh_anti"),-1)
    h0highanti.Add(fTop.Get("h_frhigh_anti"),-1)
    h0highiso.Divide(h0highanti)

    h0lowiso=fData.Get("h_frlow_iso")
    h0lowiso.Add(fVV.Get("h_frlow_iso"),-1)
    h0lowiso.Add(fDY.Get("h_frlow_iso"),-1)
    h0lowiso.Add(fTop.Get("h_frlow_iso"),-1)
    h0lowanti=fData.Get("h_frlow_anti")
    h0lowanti.Add(fVV.Get("h_frlow_anti"),-1)
    h0lowanti.Add(fDY.Get("h_frlow_anti"),-1)
    h0lowanti.Add(fTop.Get("h_frlow_anti"),-1)
    h0lowiso.Divide(h0lowanti)


    h1iso=fData.Get("h_frnt_iso")
    h1iso.Add(fVV.Get("h_frnt_iso"),-1)
    h1iso.Add(fDY.Get("h_frnt_iso"),-1)
    h1iso.Add(fTop.Get("h_frnt_iso"),-1)

    h1anti=fData.Get("h_frnt_anti")
    h1anti.Add(fVV.Get("h_frnt_anti"),-1)
    h1anti.Add(fDY.Get("h_frnt_anti"),-1)
    h1anti.Add(fTop.Get("h_frnt_anti"),-1)

    h1iso.Divide(h1anti)
    average=h1iso.GetBinContent(1)
    for k in range(1,h1iso.GetSize()):
       h1iso.SetBinContent(k,h1iso.GetBinContent(k)/average)
    fout.cd()
    h1iso.SetName("FRNT")
    h1iso.Write()

    c=ROOT.TCanvas("canvas","",0,0,800,800)
    c.SetRightMargin(0.15)
    c.cd()
    h1iso.SetTitle("")
    h1iso.SetMarkerStyle(20)
    h1iso.SetMarkerColor(1)
    h1iso.SetLineColor(1)
    h1iso.GetXaxis().SetTitle("N_{tracks}")
    h1iso.GetYaxis().SetTitle("OS-to-SS ratio / average")
    h1iso.Draw("e0p")
    h1iso.GetXaxis().SetRangeUser(0,100)
    h1iso.SetMinimum(0.5)
    lumi=add_lumi(options.year)
    lumi.Draw("same")
    cms=add_CMS()
    cms.Draw("same")
    total = ROOT.TF1( 'total', 'pol5', 0, 100 )
    total.SetLineColor( 2 )
    h1iso.Fit(total,'R')
    total.SetName("fit_frnt")

    hint = ROOT.TH1D("hint","Fitted Gaussian with .68 conf.band", 100, 0, 100);
    (ROOT.TVirtualFitter.GetFitter()).GetConfidenceIntervals(hint,0.68);
    hint.SetStats(False);
    hint.SetFillColor(ROOT.kCyan);
    hint.SetFillStyle(3001);
    hint.Draw("e3 same");
    print hint.GetBinError(1)/hint.GetBinContent(1);

    fout.cd()
    total.Write()
    c.cd()
    c.Modified()
    c.SaveAs("plots_emu_"+options.year+"/frnt.pdf")
    c.SaveAs("plots_emu_"+options.year+"/frnt.png")

    h0iso.SetTitle("")
    h0iso.SetMarkerStyle(20)
    h0iso.SetMarkerColor(1)
    h0iso.SetLineColor(1)
    h0iso.GetXaxis().SetTitle("p_{T}(e) (GeV)")
    h0iso.GetYaxis().SetTitle("p_{T}(#mu) (GeV)")
    h0iso.GetZaxis().SetTitle("OS/SS ratio")
    h0iso.GetZaxis().SetRangeUser(1.2,2.2)
    h0iso.Draw("COLZH ERROR TEXT45")
    lumi=add_lumi(options.year)
    lumi.Draw("same")
    cms=add_CMS()
    cms.Draw("same")
    c.cd()
    c.Modified()
    c.SaveAs("plots_emu_"+options.year+"/fr2D.pdf")
    c.SaveAs("plots_emu_"+options.year+"/fr2D.png")

    h0highiso.SetTitle("")
    h0highiso.SetMarkerStyle(20)
    h0highiso.SetMarkerColor(1)
    h0highiso.SetLineColor(1)
    h0highiso.GetXaxis().SetTitle("p_{T}(e) (GeV)")
    h0highiso.GetYaxis().SetTitle("p_{T}(#mu) (GeV)")
    h0highiso.GetZaxis().SetTitle("OS/SS ratio")
    h0highiso.GetZaxis().SetRangeUser(1.2,2.2)
    h0highiso.Draw("COLZH ERROR TEXT45")
    lumi=add_lumi(options.year)
    lumi.Draw("same")
    cms=add_CMS()
    cms.Draw("same")
    c.cd()
    c.Modified()
    c.SaveAs("plots_emu_"+options.year+"/frhigh2D.pdf")
    c.SaveAs("plots_emu_"+options.year+"/frhigh2D.png")

    h0lowiso.SetTitle("")
    h0lowiso.SetMarkerStyle(20)
    h0lowiso.SetMarkerColor(1)
    h0lowiso.SetLineColor(1)
    h0lowiso.GetXaxis().SetTitle("p_{T}(e) (GeV)")
    h0lowiso.GetYaxis().SetTitle("p_{T}(#mu) (GeV)")
    h0lowiso.GetZaxis().SetTitle("OS/SS ratio")
    h0lowiso.GetZaxis().SetRangeUser(1.2,2.2)
    h0lowiso.Draw("COLZH ERROR TEXT45")
    lumi=add_lumi(options.year)
    lumi.Draw("same")
    cms=add_CMS()
    cms.Draw("same")
    c.cd()
    c.Modified()
    c.SaveAs("plots_emu_"+options.year+"/frlow2D.pdf")
    c.SaveAs("plots_emu_"+options.year+"/frlow2D.png")


    h2iso=fData.Get("h_frFP_iso")
    h2iso.Add(fVV.Get("h_frFP_iso"),-1)
    h2iso.Add(fDY.Get("h_frFP_iso"),-1)
    h2iso.Add(fTop.Get("h_frFP_iso"),-1)
    h2anti=fData.Get("h_frFP_anti")
    h2anti.Add(fVV.Get("h_frFP_anti"),-1)
    h2anti.Add(fDY.Get("h_frFP_anti"),-1)
    h2anti.Add(fTop.Get("h_frFP_anti"),-1)
    h2iso.Divide(h2anti)

    h3iso=fData.Get("h_frFF_iso")
    h3iso.Add(fVV.Get("h_frFF_iso"),-1)
    h3iso.Add(fDY.Get("h_frFF_iso"),-1)
    h3iso.Add(fTop.Get("h_frFF_iso"),-1)
    h3anti=fData.Get("h_frFF_anti")
    h3anti.Add(fVV.Get("h_frFF_anti"),-1)
    h3anti.Add(fDY.Get("h_frFF_anti"),-1)
    h3anti.Add(fTop.Get("h_frFF_anti"),-1)
    h3iso.Divide(h3anti)

    h2iso.Divide(h3iso)
    fout.cd()
    h2iso.SetName("FRantimu")
    h2iso.Write()

    h2iso.SetTitle("")
    h2iso.SetMarkerStyle(20)
    h2iso.SetMarkerColor(1)
    h2iso.SetLineColor(1)
    h2iso.GetXaxis().SetTitle("p_{T}(e) (GeV)")
    h2iso.GetYaxis().SetTitle("p_{T}(#mu) (GeV)")
    h2iso.GetZaxis().SetTitle("anti-#mu correction")
    h2iso.GetZaxis().SetRangeUser(0.9,2.0)
    h2iso.Draw("COLZH ERROR TEXT45")
    lumi.Draw("same")
    cms.Draw("same")
    c.cd()
    c.Modified()
    c.SaveAs("plots_emu_"+options.year+"/frantimu.pdf")
    c.SaveAs("plots_emu_"+options.year+"/frantimu.png")


