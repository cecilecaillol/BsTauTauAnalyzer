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
    '2018': {'ee':'(HLT_Ele32_WPTight_Gsf||HLT_Ele35_WPTight_Gsf||HLT_Photon200||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ)','etau':'(HLT_Ele32_WPTight_Gsf||HLT_Ele35_WPTight_Gsf||HLT_Photon200||HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1)','mumu':'(HLT_IsoMu24||HLT_IsoMu27||HLT_Mu50||HLT_OldMu100||HLT_TkMu100||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)','mutau':'(HLT_IsoMu24||HLT_IsoMu27||HLT_Mu50||HLT_OldMu100||HLT_TkMu100||HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1)','tautau':'(HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg||HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1)'}
}

# Some tau triggers are enabled only during part of the data taking in 2018, apply the triggers at analysis level rather than here
ANALYSISTRIGGERDATA = {
    '2018': {'ee':'(HLT_Ele32_WPTight_Gsf||HLT_Ele35_WPTight_Gsf||HLT_Photon200||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ)','etau':'(1)','mumu':'(HLT_IsoMu24||HLT_IsoMu27||HLT_Mu50||HLT_OldMu100||HLT_TkMu100||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)','mutau':'(1)','tautau':'(1)'}
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
    '2018': 'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt' 
}

cmssw=os.environ['CMSSW_BASE']
ANALYSISCUT={'': {'ee' : '-c "%s"'%ANALYSISCHANNELCUT['ee'], 'emu' : '-c "%s"'%ANALYSISCHANNELCUT['emu'], 'etau' : '-c "%s"'%ANALYSISCHANNELCUT['etau'], 'mumu' : '-c "%s"'%ANALYSISCHANNELCUT['mumu'], 'mutau' : '-c "%s"'%ANALYSISCHANNELCUT['mutau'], 'tautau' : '-c "%s"'%ANALYSISCHANNELCUT['tautau']}}

#for y in ANALYSISTRIGGER:
#  ANALYSISCUT[y]={}
#  for c in ANALYSISTRIGGER[y]:
#    ANALYSISCUT[y][c]='--cut %s&&%s --json %s'%(ANALYSISTRIGGERDATA[y][c],ANALYSISCHANNELCUT[c],cmssw+'/src/MyNanoAnalyzer/TauG2/data/'+ANALYSISGRL[y]) # for data (json applied)
    #ANALYSISCUT[y][c]='--cut %s&&%s'%(ANALYSISTRIGGERMC[y][c],ANALYSISCHANNELCUT[c]) # for MC (no json applied)
