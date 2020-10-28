# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step1 --filein dbs:/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM --fileout file:HIG-RunIIAutumn18NanoAODv7-01134.root --mc --eventcontent NANOEDMAODSIM --datatier NANOAODSIM --conditions 102X_upgrade2018_realistic_v21 --step NANO --nThreads 2 --era Run2_2018,run2_nanoAOD_102Xv1 --python_filename HIG-RunIIAutumn18NanoAODv7-01134_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 10000
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('NANO',eras.Run2_2018,eras.run2_nanoAOD_102Xv1)

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
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/27891EA5-F05F-5648-AD45-1D47EC8BE543.root' 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/E2F7214D-EA53-F340-8597-A6520EF58FCA.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/E1BD797C-2720-3E46-8DBB-44429008DEED.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/4C9ED7EB-87FA-D84A-A922-9835BC45B69B.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/2D09D8C4-D38E-684D-8383-5A81B0FAC6CA.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/3CC56300-1BB0-2B4F-A17E-6FC4645854AC.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/61EEF79B-208C-FC4D-A82B-C5B0C0C6692F.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/0AD6B042-89BB-7843-A91D-2986D4B0261A.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/016B9FB8-9D18-2C4E-9D4C-79E73526CC54.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/014F0EEF-3EE7-954B-9F1D-C7472B2492B0.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/4264F053-1261-B34B-9BF7-551EAC62D060.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/18C65219-2498-C241-A45E-43B4FE3B6F05.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/753C4DD3-7F7E-7949-8989-523D6ECB31A9.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/0F40D1EA-0F48-624D-B5D9-991D7B07A31E.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/DF643901-7352-2147-BF72-2033667EA535.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/7E57A5BE-BAA4-914A-94B9-5136511543AA.root', 
#        '/store/mc/RunIIAutumn18MiniAOD/ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/260000/30844E66-D98F-C24C-9A23-7E3467C799EF.root'
    ),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step1 nevts:10000'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

#process.NANOEDMAODSIMoutput = cms.OutputModule("PoolOutputModule",
process.NANOAODSIMoutput = cms.OutputModule("NanoAODOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(9),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('NANOAODSIM'),
        filterName = cms.untracked.string('')
    ),
    #fileName = cms.untracked.string('file:HIG-RunIIAutumn18NanoAODv7-01134.root'),
    fileName = cms.untracked.string('file:test_nanoaod.root'),
    outputCommands = process.NANOAODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v21', '')

# Path and EndPath definitions
process.nanoAOD_step = cms.Path(process.nanoSequenceMC)
process.endjob_step = cms.EndPath(process.endOfProcess)
#process.NANOEDMAODSIMoutput_step = cms.EndPath(process.NANOEDMAODSIMoutput)
process.NANOAODSIMoutput_step = cms.EndPath(process.NANOAODSIMoutput)

# Schedule definition
#process.schedule = cms.Schedule(process.nanoAOD_step,process.endjob_step,process.NANOEDMAODSIMoutput_step)
process.schedule = cms.Schedule(process.nanoAOD_step,process.endjob_step,process.NANOAODSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(2)
process.options.numberOfStreams=cms.untracked.uint32(0)

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
