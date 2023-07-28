#!/usr/bin/env python
import ROOT
import argparse
import re

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Create a copy of the specified data card with duplicated shape histograms for correllating/decorrelating uncertainties")
    parser.add_argument('--inputFile')
    parser.add_argument('--outputFile')

    args = parser.parse_args()        

    inputDatacard = ROOT.TFile(args.inputFile)
    outputDatacard = ROOT.TFile(args.outputFile,"RECREATE")

    for mydir in inputDatacard.GetListOfKeys():
     if mydir.GetName()=="em_0" or mydir.GetName()=="em_1" or mydir.GetName()=="et_0" or mydir.GetName()=="et_1" or mydir.GetName()=="mt_0" or mydir.GetName()=="mt_1" or mydir.GetName()=="tt_0" or mydir.GetName()=="tt_1":
        directory = inputDatacard.Get(mydir.GetName())
        newDirectory = outputDatacard.mkdir(mydir.GetName())
        newDirectory.cd()
        for hist in directory.GetListOfKeys():
	  if (not ("201" in hist.GetName())) or "_0p0" in hist.GetName():
            directory.Get(hist.GetName()).Write()
	    if re.search("2018",hist.GetName()) and "data_obs" not in hist.GetName():
		print hist.GetName(),hist.GetName().split("_")
                copyHisto1 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
		copyHisto1.SetName(hist.GetName().replace("2018","2017"))
		copyHisto1.Write()
                copyHisto2 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto2.SetName(hist.GetName().replace("2018","2016postVFP"))
                copyHisto2.Write()
                copyHisto3 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto3.SetName(hist.GetName().replace("2018","2016preVFP"))
                copyHisto3.Write()
            elif re.search("2017",hist.GetName()) and "data_obs" not in hist.GetName():
                copyHisto1 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto1.SetName(hist.GetName().replace("2017","2018"))
                copyHisto1.Write()
                copyHisto2 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto2.SetName(hist.GetName().replace("2017","2016postVFP"))
                copyHisto2.Write()
                copyHisto3 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto3.SetName(hist.GetName().replace("2017","2016preVFP"))
                copyHisto3.Write()
            elif re.search("2016postVFP",hist.GetName()) and "data_obs" not in hist.GetName():
                copyHisto1 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto1.SetName(hist.GetName().replace("2016postVFP","2018"))
                copyHisto1.Write()
                copyHisto2 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto2.SetName(hist.GetName().replace("2016postVFP","2017"))
                copyHisto2.Write()
                copyHisto3 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto3.SetName(hist.GetName().replace("2016postVFP","2016preVFP"))
                copyHisto3.Write()
            elif re.search("2016preVFP",hist.GetName()) and "data_obs" not in hist.GetName():
                copyHisto1 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto1.SetName(hist.GetName().replace("2016preVFP","2018"))
                copyHisto1.Write()
                copyHisto2 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto2.SetName(hist.GetName().replace("2016preVFP","2017"))
                copyHisto2.Write()
                copyHisto3 = directory.Get(hist.GetName().split("_CMS")[0]).Clone()
                copyHisto3.SetName(hist.GetName().replace("2016preVFP","2016postVFP"))
                copyHisto3.Write()

    outputDatacard.Write()
    outputDatacard.Close()
    inputDatacard.Close()
