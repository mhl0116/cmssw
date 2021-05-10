# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: --python_filename TRK-RunIISummer19UL18NanoAODv2-00006_1_cfg.py --eventcontent NANOEDMAODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier NANOAODSIM --fileout file:TRK-RunIISummer19UL18NanoAODv2-00006.root --conditions 106X_upgrade2018_realistic_v15_L1v1 --step NANO --filein dbs:/TTbar_13TeV_TuneCP5_Pythia8/RunIISummer19UL18MiniAOD-106X_upgrade2018_realistic_v11_L1v1-v2/MINIAODSIM --era Run2_2018,run2_nanoAOD_106Xv1 --no_exec --mc -n 6697
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run2_2018_cff import Run2_2018
from Configuration.Eras.Modifier_run2_nanoAOD_106Xv1_cff import run2_nanoAOD_106Xv1

process = cms.Process('NANO',Run2_2018,run2_nanoAOD_106Xv1)

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
        #'/store/mc/RunIISummer19UL18MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/230000/591914C1-4BCC-6140-B7E8-394A0DD692D7.root', 
        #'/store/mc/RunIISummer19UL18MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/240000/29E00E77-B064-6F47-87C0-BB330CEE24FA.root', 
        #'/store/mc/RunIISummer19UL18MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/240000/4DA9822B-73A9-EC46-ADCD-21D229E481C1.root', 
        #'/store/mc/RunIISummer19UL18MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/240000/591D7F02-B0AA-5F46-BF6F-B611B4B68EFF.root', 
        #'/store/mc/RunIISummer19UL18MiniAOD/TTbar_13TeV_TuneCP5_Pythia8/MINIAODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/240000/7F18F173-4CEC-5A40-BF02-EAC1A5CC2391.root',
        '/store/mc/RunIISummer19UL18MiniAODv2/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v1/230000/773DE56C-BEF3-C241-8FD6-18F6CA90D26D.root'
    ),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('--python_filename nevts:6697'),
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
    #fileName = cms.untracked.string('file:TRK-RunIISummer19UL18NanoAODv2-00006.root'),
    fileName = cms.untracked.string('file:test_nanoaod.root'),
    outputCommands = process.NANOAODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_upgrade2018_realistic_v15_L1v1', '')

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
