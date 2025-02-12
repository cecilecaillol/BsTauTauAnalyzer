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
    '2016': {'e':'(HLT_Ele27_WPTight_Gsf)','mu':'(HLT_IsoTkMu24||HLT_IsoMu24)','ee':'(HLT_Ele27_WPTight_Gsf)','emu':'(1)','mumu':'(HLT_IsoTkMu24||HLT_IsoMu24)'},
    '2017': {'e':'(HLT_Ele27_WPTight_Gsf||HLT_Ele32_WPTight_Gsf||HLT_Ele32_WPTight_Gsf_L1DoubleEG||HLT_Ele35_WPTight_Gsf)','mu':'(HLT_IsoMu27)','ee':'(HLT_Ele27_WPTight_Gsf||HLT_Ele32_WPTight_Gsf||HLT_Ele32_WPTight_Gsf_L1DoubleEG||HLT_Ele35_WPTight_Gsf)','emu':'(1)','mumu':'(HLT_IsoMu27)'},
    '2018': {'e':'(HLT_Ele32_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele32_WPTight_Gsf||HLT_DoubleEle25_CaloIdL_MW||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'}
}

# Some tau triggers are enabled only during part of the data taking in 2018, apply the triggers at analysis level rather than here
ANALYSISTRIGGERDATA = {
    '2016': {'e':'(HLT_Ele27_WPTight_Gsf)','mu':'(HLT_IsoMu24||HLT_IsoTkMu24)','ee':'(HLT_Ele27_WPTight_Gsf)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_IsoTkMu24)'},
    '2017': {'e':'(HLT_Ele27_WPTight_Gsf||HLT_Ele32_WPTight_Gsf||HLT_Ele32_WPTight_Gsf_L1DoubleEG||HLT_Ele35_WPTight_Gsf)','mu':'(HLT_IsoMu27)','ee':'(HLT_Ele27_WPTight_Gsf||HLT_Ele32_WPTight_Gsf||HLT_Ele32_WPTight_Gsf_L1DoubleEG||HLT_Ele35_WPTight_Gsf)','emu':'(1)','mumu':'(HLT_IsoMu27)'},
    '2018': {'e':'(HLT_Ele32_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele32_WPTight_Gsf||HLT_DoubleEle25_CaloIdL_MW||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'}
}


ANALYSISCHANNELCUT = {
    'e':'(nElectron>0)',
    'mu':'(nMuon>0)',
    'emu':'(nMuon>0&&nElectron>0)',
    'ee':'nElectron>1',
    'mumu':'nMuon>1'
}

ANALYSISGRL = {
    '2016': 'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt', #35.93
    '2017': 'Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt', #41.48
    '2018': 'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt' # 

}

cmssw=os.environ['CMSSW_BASE']
ANALYSISCUT={'': {'e' : '-c "%s"'%ANALYSISCHANNELCUT['e'], 'mu' : '-c "%s"'%ANALYSISCHANNELCUT['mu'], 'ee' : '-c "%s"'%ANALYSISCHANNELCUT['ee'], 'emu' : '-c "%s"'%ANALYSISCHANNELCUT['emu'], 'mumu' : '-c "%s"'%ANALYSISCHANNELCUT['mumu']}}

## Uncomment the following lines if running on data, comment if running on MC
for y in ANALYSISTRIGGERDATA:
    print y
    ANALYSISCUT[y]={}
    for c in ANALYSISTRIGGERDATA[y]:
        ANALYSISCUT[y][c]='--cut %s&&%s --json %s'%(ANALYSISTRIGGERDATA[y][c],ANALYSISCHANNELCUT[c],cmssw+'/src/BsTauTauAnalyzer/Flattener/data/'+ANALYSISGRL[y]) # for data (json applied)
    
## Comment the following lines if running on data, uncomment if running on MC
#for y in ANALYSISTRIGGERMC:
#    ANALYSISCUT[y]={}
#    for c in ANALYSISTRIGGERMC[y]:
#        ANALYSISCUT[y][c]='--cut %s&&%s'%(ANALYSISTRIGGERMC[y][c],ANALYSISCHANNELCUT[c]) # for MC (no json applied)
