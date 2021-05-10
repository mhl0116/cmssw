# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: RECO --conditions 106X_dataRun2_v32 --customise Configuration/DataProcessing/Utils.addMonitoring --datatier NANOAOD --era Run2_2018,run2_nanoAOD_106Xv1 --eventcontent NANOEDMAOD --filein _placeholder_.root --fileout file:ReReco-Run2018D-EGamma-UL2018_MiniAODv1_NanoAODv2-00001.root --nThreads 2 --no_exec --python_filename ReReco-Run2018D-EGamma-UL2018_MiniAODv1_NanoAODv2-00001_0_cfg.py --scenario pp --step NANO --data
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run2_2018_cff import Run2_2018
from Configuration.Eras.Modifier_run2_nanoAOD_106Xv1_cff import run2_nanoAOD_106Xv1

process = cms.Process('NANO',Run2_2018,run2_nanoAOD_106Xv1)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('PhysicsTools.NanoAOD.nano_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(1000)
            
        )

# Input source
process.source = cms.Source("PoolSource",
            fileNames = cms.untracked.vstring('/store/data/Run2018B/EGamma/MINIAOD/UL2018_MiniAODv2-v1/260000/00FAE4A8-E0E7-A941-AB7E-0DD0383C9CB5.root'),
                secondaryFileNames = cms.untracked.vstring()
                )

process.options = cms.untracked.PSet(

        
        )

# Production Info
process.configurationMetadata = cms.untracked.PSet(
            annotation = cms.untracked.string('RECO nevts:1'),
                name = cms.untracked.string('Applications'),
                    version = cms.untracked.string('$Revision: 1.19 $')
                    
        )

# Output definition

process.NANOEDMAODoutput = cms.OutputModule("NanoAODOutputModule",
            compressionAlgorithm = cms.untracked.string('LZMA'),
                compressionLevel = cms.untracked.int32(9),
                dataset = cms.untracked.PSet(
                            dataTier = cms.untracked.string('NANOAOD'),
                                    filterName = cms.untracked.string('')
                                        
                    ),
                    #fileName = cms.untracked.string('file:ReReco-Run2018D-EGamma-UL2018_MiniAODv1_NanoAODv2-00001.root'),
                    fileName = cms.untracked.string('file:test_nanoaod.root'),
                        outputCommands = process.NANOAODEventContent.outputCommands
                        )

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_dataRun2_v32', '')

# Path and EndPath definitions
process.nanoAOD_step = cms.Path(process.nanoSequence)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.NANOEDMAODoutput_step = cms.EndPath(process.NANOEDMAODoutput)

# Schedule definition
process.schedule = cms.Schedule(process.nanoAOD_step,process.endjob_step,process.NANOEDMAODoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(2)
process.options.numberOfStreams=cms.untracked.uint32(0)
process.options.numberOfConcurrentLuminosityBlocks=cms.untracked.uint32(1)

# customisation of the process.

# Automatic addition of the customisation function from PhysicsTools.NanoAOD.nano_cff
from PhysicsTools.NanoAOD.nano_cff import nanoAOD_customizeData 

#call to customisation function nanoAOD_customizeData imported from PhysicsTools.NanoAOD.nano_cff
process = nanoAOD_customizeData(process)

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
