import ROOT

def add_lumi():
    lowX=0.63
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.07)
    lumi.SetTextFont (   42 )
    lumi.AddText("138 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.1
    lowY=0.84
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("SuperChic")
    return lumi

def add_Preliminary():
    lowX=0.2
    lowY=0.82
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    lumi.AddText("")
    return lumi

def add_Supplementary():
    lowX=0.2
    lowY=0.82
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("")
    return lumi

ROOT.gStyle.SetOptStat(0)

# Open ROOT file containing histograms
file_el = ROOT.TFile.Open("output_GGTT_Elastic_superchic.root")
file_tot = ROOT.TFile.Open("output_GGTT_superchic.root")

# Access histograms
hist_tot = file_tot.Get("h_mtt")
hist_el = file_el.Get("h_mtt")

# Create canvas
canvas = ROOT.TCanvas("canvas", "Two Panel Canvas", 800, 600)

# Create pads for top and bottom panels
pad1 = ROOT.TPad("pad1", "pad1", 0, 0.3, 1, 1)
pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.3)

# Set margins
pad1.SetBottomMargin(0.05)
pad2.SetTopMargin(0.05)
pad2.SetBottomMargin(0.3)

# Draw pads
pad1.Draw()
pad2.Draw()

# Top panel
pad1.cd()
pad1.SetTickx(1)
pad1.SetTicky(1)
hist_tot.SetLineColor(2)
hist_tot.SetTitle("")
hist_tot.GetYaxis().SetTitle("d#sigma^{fid}/m_{#tau#tau} (fb/ 10 GeV)")
hist_tot.GetYaxis().SetTitleOffset(0.5)
hist_tot.GetXaxis().SetTitle("m_{#tau#tau} (GeV)")
hist_tot.GetYaxis().SetTitleSize(0.08)
hist_tot.GetXaxis().SetTitleSize(0.00)
hist_tot.GetXaxis().SetLabelSize(0.00)
hist_tot.SetLineWidth(3)
hist_el.SetLineWidth(3)
hist_tot.Draw("hist")
hist_el.Draw("histsame")
legend = ROOT.TLegend(0.4, 0.6, 0.9, 0.8)
legend.SetLineWidth(0)
legend.SetLineStyle(0)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.SetMargin(0.1)
legend.AddEntry(hist_el, "Elastic", "l")
legend.AddEntry(hist_tot, "Elastic + (semi-)dissociative", "l")
legend.Draw()

l1=add_lumi()
#l1.Draw("same")
l2=add_CMS()
l2.Draw("same")
l4=add_Supplementary()
#l4.Draw("same")

# Bottom panel (Ratio)
pad2.cd()
pad2.SetTickx(1)
pad2.SetTicky(1)
ratio_hist = hist_tot.Clone("ratio_hist")
ratio_hist.Divide(hist_el)
ratio_hist.GetXaxis().SetLabelSize(0.10)
ratio_hist.GetXaxis().SetTitleSize(0.15)
ratio_hist.GetYaxis().SetLabelSize(0.10)
ratio_hist.GetYaxis().SetTitleSize(0.13)
ratio_hist.GetXaxis().SetTitleOffset(0.9)
ratio_hist.GetYaxis().SetTitleOffset(0.3)
ratio_hist.GetYaxis().SetTitle("Ratio to el.")
ratio_hist.GetYaxis().SetNdivisions(505)
ratio_hist.SetMinimum(2.0)
ratio_hist.Draw("e")

total2 = ROOT.TF1( 'total', 'pol1', 50, 500 )
total2.SetLineColor( 3 )
ratio_hist.Fit(total2,'R')
total2.Draw("lsame")

t = ROOT.TLatex();
t.SetTextAlign(2);
t.SetTextSize(0.1);
t.SetTextFont(62);
sf = total2.GetParameter(1)
text = f"Lin. SF = {total2.GetParameter(0):.3f}"
text += f" {sf:+.3g} #times #frac{{m_{{#mu#mu}}}}{{GeV}}"
t.DrawLatex(50, 3.5, text);


# Update canvas
canvas.Update()

canvas.SaveAs("superchic.png")
canvas.SaveAs("superchic.pdf")
