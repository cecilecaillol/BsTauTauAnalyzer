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
    lowY=0.83
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
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
    lumi.AddText("Supplementary")
    return lumi

ROOT.gStyle.SetOptStat(0)

# Open ROOT file containing histograms
file1 = ROOT.TFile.Open("suppl_etau_6p4.root")
file2 = ROOT.TFile.Open("suppl_etau_0p0.root")

# Access histograms
hist1 = file1.Get("h_suppl")
hist2 = file2.Get("h_suppl")

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
hist1.SetLineColor(2)
hist1.SetTitle("")
hist1.GetYaxis().SetTitle("Events")
hist1.GetYaxis().SetTitleOffset(0.5)
hist1.GetXaxis().SetTitle("m_{vis} (GeV)")
hist1.GetYaxis().SetTitleSize(0.08)
hist1.GetXaxis().SetTitleSize(0.00)
hist1.GetXaxis().SetLabelSize(0.00)
hist1.SetLineWidth(3)
hist2.SetLineWidth(3)
hist1.Draw("hist")
hist2.Draw("histsame")
legend = ROOT.TLegend(0.4, 0.6, 0.9, 0.8)
legend.SetLineWidth(0)
legend.SetLineStyle(0)
legend.SetFillStyle(0)
legend.SetBorderSize(0)
legend.SetTextFont(42)
legend.AddEntry(hist2, "#gamma#gamma #rightarrow #tau#tau, SM", "l")
legend.AddEntry(hist1, "#gamma#gamma #rightarrow #tau#tau, a_{#tau} = 0.007", "l")
legend.Draw()

l1=add_lumi()
l1.Draw("same")
l2=add_CMS()
l2.Draw("same")
l4=add_Supplementary()
l4.Draw("same")

lowX=0.55
lowY=0.335
lumi1  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
lumi1.SetBorderSize(   0 )
lumi1.SetFillStyle(    0 )
lumi1.SetTextAlign(   12 )
lumi1.SetTextColor(    1 )
lumi1.SetTextSize(0.09)
lumi1.SetTextFont (   42 )
lumi1.AddText("e#tau_{h}, N_{tracks} = 0")
lumi1.Draw("same")


# Bottom panel (Ratio)
pad2.cd()
pad2.SetTickx(1)
pad2.SetTicky(1)
ratio_hist = hist1.Clone("ratio_hist")
ratio_hist.Divide(hist2)
ratio_hist.GetXaxis().SetLabelSize(0.10)
ratio_hist.GetXaxis().SetTitleSize(0.15)
ratio_hist.GetYaxis().SetLabelSize(0.10)
ratio_hist.GetYaxis().SetTitleSize(0.13)
ratio_hist.GetXaxis().SetTitleOffset(0.9)
ratio_hist.GetYaxis().SetTitleOffset(0.3)
ratio_hist.GetYaxis().SetTitle("Ratio to SM")
ratio_hist.GetYaxis().SetNdivisions(505)
ratio_hist.Draw("hist")

# Update canvas
canvas.Update()

canvas.SaveAs("signal_etau.png")
