from ROOT import RDataFrame, TChain


t_inclusive = TChain("Runs")
t_1Jets = TChain("Runs")
t_2Jets = TChain("Runs")
t_3Jets = TChain("Runs")
t_4Jets = TChain("Runs")

t_inclusive.Add("~/taug2data/AnalysisXuelong/ntuples_mutau_2018/W.root")
t_1Jets.Add("~/taug2data/AnalysisXuelong/ntuples_mutau_2018/W1.root")
t_2Jets.Add("~/taug2data/AnalysisXuelong/ntuples_mutau_2018/W2.root")
t_3Jets.Add("~/taug2data/AnalysisXuelong/ntuples_mutau_2018/W3.root")
t_4Jets.Add("~/taug2data/AnalysisXuelong/ntuples_mutau_2018/W4.root")


fr_inclusive = RDataFrame(t_inclusive)
fr_1Jets = RDataFrame(t_1Jets)
fr_2Jets = RDataFrame(t_2Jets)
fr_3Jets = RDataFrame(t_3Jets)
fr_4Jets = RDataFrame(t_4Jets)

print ("inclusive W: {}".format(fr_inclusive.Sum("genEventCount").GetValue()))
print ("1Jets W: {}".format(fr_1Jets.Sum("genEventCount").GetValue()))
print ("2Jets W: {}".format(fr_2Jets.Sum("genEventCount").GetValue()))
print ("3Jets W: {}".format(fr_3Jets.Sum("genEventCount").GetValue()))
print ("4Jets W: {}".format(fr_4Jets.Sum("genEventCount").GetValue()))

