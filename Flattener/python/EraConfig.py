import os
""" Year dependent configurations / files """

def getEraConfiguration(era,isData):

    """ defines global tags, depending on the era """

    globalTags = {
        'era2022':('150X_mcRun3_2022_realistic_v2',                 '150X_dataRun3_v2'),
        'era2023':('150X_mcRun3_2023_realistic_v2',                 '150X_dataRun3_v2'),
        'era2024':('150X_mcRun3_2024_realistic_v2',                 '150X_dataRun3_v2'),
        'era2025':('150X_mcRun3_2024_realistic_v2',                 '150X_dataRun3_Prompt_v1')
        }

    globalTag = globalTags[era][isData]

    return globalTag
    
ANALYSISTRIGGERMC = {
    '2022': {'e':'(HLT_Ele30_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele30_WPTight_Gsf||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'},
    '2023': {'e':'(HLT_Ele30_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele30_WPTight_Gsf||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'},
    '2024': {'e':'(HLT_Ele30_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele30_WPTight_Gsf||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'},
    '2025': {'e':'(HLT_Ele30_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele30_WPTight_Gsf||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'}
}

ANALYSISTRIGGERDATA = {
    '2022': {'e':'(HLT_Ele30_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele30_WPTight_Gsf||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'},
    '2023': {'e':'(HLT_Ele30_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele30_WPTight_Gsf||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'},
    '2024': {'e':'(HLT_Ele30_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele30_WPTight_Gsf||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'},
    '2025': {'e':'(HLT_Ele30_WPTight_Gsf)','mu':'(HLT_IsoMu24)','ee':'(HLT_Ele30_WPTight_Gsf||HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)','emu':'(1)','mumu':'(HLT_IsoMu24||HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)'}
}


ANALYSISCHANNELCUT = {
    'e':'(nElectron>0&&nJet>0)',
    'mu':'(nMuon>0&&nJet>0)',
    'emu':'(nMuon>0&&nElectron>0&&nJet>0)',
    'ee':'(nElectron>1&&nJet>0)',
    'mumu':'(nMuon>1&&nJet>0)'
}

ANALYSISGRL = {
    '2022': 'Cert_Collisions2022_355100_362760_Golden.json',
    '2023': 'Cert_Collisions2023_366442_370790_Golden.json',
    '2024': 'Cert_Collisions2024_378981_386951_Golden.json',
    '2025': 'Cert_Collisions2025_391658_398595_Golden.json',

}

cmssw=os.environ['CMSSW_BASE']
ANALYSISCUT={'': {'e' : '-c "%s"'%ANALYSISCHANNELCUT['e'], 'mu' : '-c "%s"'%ANALYSISCHANNELCUT['mu'], 'ee' : '-c "%s"'%ANALYSISCHANNELCUT['ee'], 'emu' : '-c "%s"'%ANALYSISCHANNELCUT['emu'], 'mumu' : '-c "%s"'%ANALYSISCHANNELCUT['mumu']}}

## Uncomment the following lines if running on data, comment if running on MC
for y in ANALYSISTRIGGERDATA:
    print(y)
    ANALYSISCUT[y]={}
    for c in ANALYSISTRIGGERDATA[y]:
        ANALYSISCUT[y][c]='--cut %s&&%s --json %s'%(ANALYSISTRIGGERDATA[y][c],ANALYSISCHANNELCUT[c],cmssw+'/src/BsTauTauAnalyzer/Flattener/data/'+ANALYSISGRL[y]) # for data (json applied)
    
## Comment the following lines if running on data, uncomment if running on MC
#for y in ANALYSISTRIGGERMC:
#    ANALYSISCUT[y]={}
#    for c in ANALYSISTRIGGERMC[y]:
#        ANALYSISCUT[y][c]='--cut %s&&%s'%(ANALYSISTRIGGERMC[y][c],ANALYSISCHANNELCUT[c]) # for MC (no json applied)
