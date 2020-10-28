# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: RECO --conditions 102X_dataRun2_v13 --customise Configuration/DataProcessing/Utils.addMonitoring --datatier NANOAOD --era Run2_2016,run2_nanoAOD_94X2016 --eventcontent NANOEDMAOD --filein _placeholder_.root --fileout file:ReReco-Run2016B-SingleMuon-02Apr2020_ver1-00001.root --nThreads 2 --no_exec --python_filename ReReco-Run2016B-SingleMuon-02Apr2020_ver1-00001_0_cfg.py --scenario pp --step NANO --data
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('NANO',eras.Run2_2016,eras.run2_nanoAOD_94X2016)

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
            fileNames = cms.untracked.vstring('/store/data/Run2016B/SingleMuon/MINIAOD/17Jul2018_ver1-v1/80000/306DAB6C-068C-E811-9E30-0242AC1C0501.root'),
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

#process.NANOEDMAODoutput = cms.OutputModule("PoolOutputModule",
process.NANOAODoutput = cms.OutputModule("NanoAODOutputModule",
            compressionAlgorithm = cms.untracked.string('LZMA'),
                compressionLevel = cms.untracked.int32(9),
                dataset = cms.untracked.PSet(
                            dataTier = cms.untracked.string('NANOAOD'),
                                    filterName = cms.untracked.string('')
                                        
                    ),
                   # fileName = cms.untracked.string('file:ReReco-Run2016B-SingleMuon-02Apr2020_ver1-00001.root'),
                    fileName = cms.untracked.string('file:test_nanoaod.root'),
                        outputCommands = process.NANOAODSIMEventContent.outputCommands
                        )

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_v13', '')

# Path and EndPath definitions
process.nanoAOD_step = cms.Path(process.nanoSequence)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.NANOEDMAODoutput_step = cms.EndPath(process.NANOAODoutput)

# Schedule definition
process.schedule = cms.Schedule(process.nanoAOD_step,process.endjob_step,process.NANOEDMAODoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(1)
process.options.numberOfStreams=cms.untracked.uint32(0)

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
