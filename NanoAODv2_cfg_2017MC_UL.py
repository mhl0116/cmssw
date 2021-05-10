# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: --python_filename TRK-RunIISummer19UL17NanoAODv2-00002_1_cfg.py --eventcontent NANOEDMAODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier NANOAODSIM --fileout file:TRK-RunIISummer19UL17NanoAODv2-00002.root --conditions 106X_mc2017_realistic_v8 --step NANO --filein dbs:/TTbar_13TeV_TuneCP5_Pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM --era Run2_2017,run2_nanoAOD_106Xv1 --no_exec --mc -n 10000
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run2_2017_cff import Run2_2017
from Configuration.Eras.Modifier_run2_nanoAOD_106Xv1_cff import run2_nanoAOD_106Xv1

process = cms.Process('NANO',Run2_2017,run2_nanoAOD_106Xv1)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('PhysicsTools.NanoAOD.nano_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#        '/store/mc/RunIISummer19UL17MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_mc2017_realistic_v6-v1/10000/2406CA6A-35B9-A142-A1E0-45ACCC3C55B4.root', 
#        '/store/mc/RunIISummer19UL17MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_mc2017_realistic_v6-v1/100000/047C0C2E-1533-FA44-9273-8CADFFC14220.root', 
#        '/store/mc/RunIISummer19UL17MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_mc2017_realistic_v6-v1/100000/5EC93828-FE9D-F848-B56D-A673B99DB792.root', 
#        '/store/mc/RunIISummer19UL17MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_mc2017_realistic_v6-v1/100000/892A580E-5A7B-9742-922D-6CC1D98FA71A.root', 
#        '/store/mc/RunIISummer19UL17MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_mc2017_realistic_v6-v1/100000/A1C25B06-10C4-7746-8D06-5D59EF9D06E5.root', 
        '/store/mc/RunIISummer19UL17MiniAODv2/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/106X_mc2017_realistic_v9-v1/270000/0A9420B7-9769-864E-82AB-6E1269413775.root'
    ),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('--python_filename nevts:10000'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.NANOEDMAODSIMoutput = cms.OutputModule("NanoAODOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(9),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('NANOAODSIM'),
        filterName = cms.untracked.string('')
    ),
    #fileName = cms.untracked.string('file:TRK-RunIISummer19UL17NanoAODv2-00002.root'),
    fileName = cms.untracked.string('file:test_nanoaod.root'),
    outputCommands = process.NANOAODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mc2017_realistic_v8', '')

# Path and EndPath definitions
process.nanoAOD_step = cms.Path(process.nanoSequenceMC)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.NANOEDMAODSIMoutput_step = cms.EndPath(process.NANOEDMAODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.nanoAOD_step,process.endjob_step,process.NANOEDMAODSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# customisation of the process.

# Automatic addition of the customisation function from PhysicsTools.NanoAOD.nano_cff
from PhysicsTools.NanoAOD.nano_cff import nanoAOD_customizeMC 

#call to customisation function nanoAOD_customizeMC imported from PhysicsTools.NanoAOD.nano_cff
process = nanoAOD_customizeMC(process)

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# End of customisation functions

# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
