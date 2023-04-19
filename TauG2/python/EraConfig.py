import os
""" Year dependent configurations / files """

def getEraConfiguration(era,isData):

    """ defines global tags, depending on the era """

    globalTags = {
        'era2016preVFP':('106X_mcRun2_asymptotic_preVFP_v11',    '106X_dataRun2_v35'),
        'era2016':('106X_mcRun2_asymptotic_v17',                 '106X_dataRun2_v35'),
        'era2017':('auto:phase1_2017_realistic',                 '106X_dataRun2_v35'),
        'era2018':('auto:phase1_2018_realistic',                 '106X_dataRun2_v35')
        }

    globalTag = globalTags[era][isData]

    return globalTag
    
ANALYSISTRIGGERMC = {
    '2016': {'ee':'(HLT_Ele27_WPTight_Gsf||HLT_Ele25_eta2p1_WPTight_Gsf)','emu':'(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL||HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)','etau':'(HLT_Ele27_WPTight_Gsf||HLT_Ele25_eta2p1_WPTight_Gsf||HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1||HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20||HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30)','mumu':'(HLT_IsoTkMu24||HLT_IsoMu24)','mutau':'(HLT_IsoMu24||HLT_IsoTkMu24||HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1)','tautau':'(HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg||HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg)'},
    '2017': {'ee':'(HLT_Ele32_WPTight_Gsf_L1DoubleEG||HLT_Ele35_WPTight_Gsf)','emu':'(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ)','etau':'(HLT_Ele32_WPTight_Gsf_L1DoubleEG||HLT_Ele35_WPTight_Gsf||HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1)','mumu':'(HLT_IsoMu27)','mutau':'(HLT_IsoMu27||HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1)','tautau':'(HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg||HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg||HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg)'},
    '2018': {'ee':'(HLT_Ele32_WPTight_Gsf)','emu':'(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ)','etau':'(HLT_Ele32_WPTight_Gsf||HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1)','mumu':'(HLT_IsoMu24)','mutau':'(HLT_IsoMu24||HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1)','tautau':'(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg)'}
}

# Some tau triggers are enabled only during part of the data taking in 2018, apply the triggers at analysis level rather than here
ANALYSISTRIGGERDATA = {
    '2016': {'ee':'(HLT_Ele27_WPTight_Gsf||HLT_Ele25_eta2p1_WPTight_Gsf)','emu':'(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL||HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)','etau':'(1)','mumu':'(HLT_IsoMu24||HLT_IsoTkMu24)','mutau':'(1)','tautau':'(1)'},
    '2017': {'ee':'(HLT_Ele32_WPTight_Gsf_L1DoubleEG||HLT_Ele35_WPTight_Gsf)','emu':'(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ)','etau':'(1)','mumu':'(HLT_IsoMu27)','mutau':'(1)','tautau':'(1)'},
    '2018': {'ee':'(HLT_Ele32_WPTight_Gsf)','emu':'(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ)','etau':'(1)','mumu':'(HLT_IsoMu24)','mutau':'(1)','tautau':'(1)'}
}


ANALYSISCHANNELCUT = {
    'emu':'(nMuon>0&&nElectron>0)',
    'etau':'(nElectron>0&&nTau>0)',
    'mutau':'(nMuon>0&&nTau>0)',
    'ee':'nElectron>1',
    'mumu':'nMuon>1',
    'tautau':'nTau>1'
}

ANALYSISGRL = {
    '2016': 'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt', #35.93
    '2017': 'Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt', #41.48
    '2018': 'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt' # 

}

cmssw=os.environ['CMSSW_BASE']
ANALYSISCUT={'': {'ee' : '-c "%s"'%ANALYSISCHANNELCUT['ee'], 'emu' : '-c "%s"'%ANALYSISCHANNELCUT['emu'], 'etau' : '-c "%s"'%ANALYSISCHANNELCUT['etau'], 'mumu' : '-c "%s"'%ANALYSISCHANNELCUT['mumu'], 'mutau' : '-c "%s"'%ANALYSISCHANNELCUT['mutau'], 'tautau' : '-c "%s"'%ANALYSISCHANNELCUT['tautau']}}

for y in ANALYSISTRIGGERDATA:
    print y
    ANALYSISCUT[y]={}
    for c in ANALYSISTRIGGERDATA[y]:
        ANALYSISCUT[y][c]='--cut %s&&%s --json %s'%(ANALYSISTRIGGERDATA[y][c],ANALYSISCHANNELCUT[c],cmssw+'/src/MyNanoAnalyzer/TauG2/data/'+ANALYSISGRL[y]) # for data (json applied)
    
#for y in ANALYSISTRIGGERMC:
#    ANALYSISCUT[y]={}
#    for c in ANALYSISTRIGGERMC[y]:
#        ANALYSISCUT[y][c]='--cut %s&&%s'%(ANALYSISTRIGGERMC[y][c],ANALYSISCHANNELCUT[c]) # for MC (no json applied)
