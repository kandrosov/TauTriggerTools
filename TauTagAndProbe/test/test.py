import FWCore.ParameterSet.Config as cms
process = cms.Process("TagAndProbe")

isMC = True

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

if not isMC: # will use 80X
    from Configuration.AlCa.autoCond import autoCond
    process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v8'
    process.load('TauTagAndProbe.TauTagAndProbe.tagAndProbe_cff')
    process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/082EC2A0-4C28-E611-BC61-02163E014412.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/1014078C-4C28-E611-85FB-02163E0141C1.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/203E5176-4C28-E611-B4F8-02163E014743.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/32508866-4C28-E611-A38D-02163E011BAF.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/44AF1068-4C28-E611-80D0-02163E01367B.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/5AF4B08A-4C28-E611-AEC9-02163E01342C.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/6E3FD070-4C28-E611-9A1E-02163E011DC7.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/7005DB70-4C28-E611-8628-02163E0144DD.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/7C2CB76B-4C28-E611-8D90-02163E01467F.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/274/199/00000/86B68469-4C28-E611-92A6-02163E01419C.root',
            # '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/275/125/00000/24FC42B2-8036-E611-B42D-02163E012BD1.root'
        )
    )
else:
    process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_RunIIFall15DR76_v1' #MC 25 ns miniAODv2
    # process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0'
    process.load('TauTagAndProbe.TauTagAndProbe.MCanalysis_cff')
    process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            #'/store/mc/RunIIFall15MiniAODv2/GluGluToRadionToHHTo2B2Tau_M-700_narrow_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/60000/2CD9692A-9EB8-E511-A944-FACADE0000C9.root'
            '/store/mc/RunIIFall15MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/02A85EE9-70BA-E511-A0A2-0CC47A4D7678.root',
            '/store/mc/RunIIFall15MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/08C274E5-70BA-E511-920F-0CC47A78A458.root',
            '/store/mc/RunIIFall15MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/06E9C8D6-79BA-E511-9EB0-0CC47A4D7600.root',
            '/store/mc/RunIIFall15MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/08B579D9-C7B8-E511-861F-00259021A526.root'

        )
    )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100000)
)

process.p = cms.Path(
    process.TAndPseq
)

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# Adding ntuplizer
process.TFileService=cms.Service('TFileService',fileName=cms.string('NTuple.root'))
