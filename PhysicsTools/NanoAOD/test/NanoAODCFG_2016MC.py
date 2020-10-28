# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: --python_filename SMP-RunIISummer16NanoAODv7-00246_1_cfg.py --eventcontent NANOEDMAOD --customise Configuration/DataProcessing/Utils.addMonitoring --datatier NANOAODSIM --fileout file:SMP-RunIISummer16NanoAODv7-00246.root --conditions 102X_mcRun2_asymptotic_v8 --step NANO --filein dbs:/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM --era Run2_2016,run2_nanoAOD_94X2016 --no_exec --mc -n 10000
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('NANO',eras.Run2_2016,eras.run2_nanoAOD_94X2016)

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
    input = cms.untracked.int32(10000)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/110000/16E58813-6CBC-E811-A263-0CC47AFB7CE8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/110000/30395BDD-6BBC-E811-A14D-0025904C6508.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/110000/B46C7C5F-93BC-E811-BD77-0025905C5432.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/76DA464E-22BD-E811-97D4-0CC47AFB7CEC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/A848A1A4-26BD-E811-A2A0-0025905C42A4.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/72DC1ABA-2ABD-E811-8C8A-0025905C3DD6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/D0A002A1-2FBD-E811-AD6C-0025905C2CA6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/FE12ADDF-32BD-E811-BF68-0025905C54FE.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/BCF0CA69-35BD-E811-B1EA-0CC47AFB7DEC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/F62535BD-1CBD-E811-9F9F-0CC47AF9B302.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/6E0402D1-1CBD-E811-AF37-0CC47AF9B2C2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/1A8DE81E-1DBD-E811-925E-0CC47AFB7D60.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/5A8E1CCB-1EBD-E811-B6ED-0025904C68D8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/360BD18F-1FBD-E811-9D07-0025904CDDFA.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/3208266A-1FBD-E811-BE99-0025904C6624.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/10ACCDED-1CBD-E811-B69C-0025905C95F8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/50F40214-83BE-E811-95BD-0025905C3DF8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/BA37DC24-15C2-E811-B95F-0CC47AF9B2C2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/9494F83F-1AC2-E811-BCC1-0CC47AFB7D48.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/8A89B638-1EC2-E811-A0B8-0025905D1D02.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/BC24FA8C-1DC2-E811-BEDB-0025905C54B8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/22272A7B-23C2-E811-886B-0025905D1D50.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/20B16EED-2AC2-E811-B442-0CC47AFB80DC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/32F2E780-2FC2-E811-A450-0CC47AF9B2C6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/34CAB2B6-27C2-E811-8917-0025905C5438.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/D67A9227-2AC2-E811-A1EF-0025905C2D9A.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/54BABFCB-2CC2-E811-976C-0025905D1D60.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/F64AB6EC-2DC2-E811-8D0D-0025904B7C26.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/46A7883B-2EC2-E811-8084-0025904C67BA.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/802D1987-32C2-E811-A361-0025905D1D7A.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/6628296F-31C2-E811-9967-0025904C66EE.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/569612F4-37C2-E811-871A-0025905C54F4.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/787A9F41-3EC2-E811-949A-0025905C543A.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/62C1B3C4-3EC2-E811-8E43-0025905C53DC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/323EEB6A-41C2-E811-83C8-0025905D1CB0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/F0456FFF-49C2-E811-BB24-0CC47AF9B2C2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/7057497F-4AC2-E811-A0A1-0CC47AF9B2CA.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/22829E89-4AC2-E811-9D0E-0CC47AFB80DC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/326F2BBF-49C2-E811-9169-0025905C53F0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/48837ECE-49C2-E811-9352-0025905C3DD0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/BA8B71A1-4AC2-E811-A008-0025905C96E8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/D84F858D-4AC2-E811-AA8A-0025905C3D40.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/AA4C6D8B-4AC2-E811-92B7-0025905C42A2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/E0BDE7F1-49C2-E811-A027-0025904CDDF8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/A0867F85-4AC2-E811-BE45-0025905C543A.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/7ADF98A7-4AC2-E811-ADEA-0025904CF93E.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/4AAB8065-4AC2-E811-A07F-0025905C53DE.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/9C2CCBBA-4AC2-E811-91B7-0025904C4F52.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/4AE5E994-4AC2-E811-8FDE-0025904CDDEC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/72D26B9E-4AC2-E811-A23E-0025904C5DE0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/CE853DCD-53C2-E811-9F38-0025905C5432.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/5098133A-63C2-E811-A5F5-0025905C94D0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/4EAE42A3-70C2-E811-A216-0025905C5502.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/509E53E7-74C2-E811-8D77-0025905C2CBA.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/0E1FFF39-83C2-E811-A09F-0CC47AFB7D5C.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/2C7D975F-8AC2-E811-AFD8-0025904C63FA.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/9E3483AF-93C2-E811-BA4B-0025905C3D96.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/D0AF8E37-9EC2-E811-8AA1-0025905C94D0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/8CB050BD-B7C2-E811-84E2-0CC47AFB7D5C.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/A437F578-B8C2-E811-9AC3-0025904C51FE.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/FA64985D-BCC2-E811-AA6A-0025905C2CE6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/06E966DF-BDC2-E811-9854-0025905C2CA4.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/E493D29B-CBC2-E811-8F3B-0CC47AFB80DC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/9285BF54-CCC2-E811-B546-0025905C2CBA.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/4ADCD273-D1C2-E811-B7B5-0CC47AFB802C.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/9663A692-CAC2-E811-BA46-0025905C3D96.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/9ACDCFF5-CFC2-E811-A1B8-0025904C66F2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/A0553D1D-1ABF-E811-B07E-0025905C2C84.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/66400811-19BF-E811-A161-0025905C53D0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/6861A862-31BF-E811-B03E-0025905C54C6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/32518B0D-4EBF-E811-AD54-0025905C2CB8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/3E308611-55BF-E811-9185-0025905C53D0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/1C61CE7F-7BBF-E811-BF3A-0025904C66F2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/4C2EB47A-84BF-E811-A5EE-0CC47AFB80DC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/0CE9B9F9-7FBF-E811-9583-0025905C54C6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/5ECF80AF-84BF-E811-A9FD-0025905C2C84.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/D6F2F0E5-88BF-E811-96DD-0025905C2CB8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/EAE1DE28-91BF-E811-85E1-0025905C53D0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/0EBE471F-B9BF-E811-88CA-0025905C54C6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/98511967-BEBF-E811-98A8-0025905C2C84.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/36C1FA23-C2BF-E811-89E6-0025905C2CB8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/F4B71726-CBBF-E811-ABBA-0025904C66F2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/6289DCC6-D5BF-E811-BE65-0CC47AFB80DC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/826A9A55-D3BF-E811-B998-0025905C3DF6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/206C63E6-D9BF-E811-8E52-0025905C53D0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/62D94389-F2BF-E811-AD63-0025905C54C6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/B0F69461-F9BF-E811-A06D-0025905C2C84.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/A443B0D4-FCBF-E811-8A7B-0025905C2CB8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/BC848545-0DC0-E811-B2C7-0025905C3DF6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/A6D92AB9-0FC0-E811-A143-0025904C66F2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/6039876A-2EC0-E811-939D-0025905C54C6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/6A150BB0-33C0-E811-B06D-0025905C2C84.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/B0C78C76-39C0-E811-AF93-0025905C2CB8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/E0079A5A-3CC0-E811-A5A8-0025905C3DD8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/F225D831-47C0-E811-887E-0025905C3DF6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/C473F8B9-4CC0-E811-88E4-0025904C66F2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/AA5EED38-53C0-E811-9E9D-0025905C53D0.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/5A33D519-6AC0-E811-8671-0CC47AFB80DC.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/6A44CBE9-64C0-E811-AD1F-0025905C53D2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/7C485968-6AC0-E811-9D9B-0025905C54C6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/EEE54739-6EC0-E811-A4BB-0025905C2C84.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/C85DEB00-75C0-E811-B091-0025905C2CB8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/8EE56421-79C0-E811-98EF-0025905C3DD8.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/7C1B144D-89C0-E811-86F2-0025904C66F2.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/B2EEBAD0-82C0-E811-876B-0025905C3DF6.root', 
        '/store/mc/RunIISummer16MiniAODv3/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/100000/74815D3A-9FC0-E811-A459-0025905C2CD2.root'
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

process.NANOEDMAODoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(9),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('NANOAODSIM'),
        filterName = cms.untracked.string('')
    ),
    #fileName = cms.untracked.string('file:SMP-RunIISummer16NanoAODv7-00246.root'),
    fileName = cms.untracked.string('file:test_nanoaod.root'),
    outputCommands = process.NANOAODEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_mcRun2_asymptotic_v8', '')

# Path and EndPath definitions
process.nanoAOD_step = cms.Path(process.nanoSequenceMC)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.NANOEDMAODoutput_step = cms.EndPath(process.NANOEDMAODoutput)

# Schedule definition
process.schedule = cms.Schedule(process.nanoAOD_step,process.endjob_step,process.NANOEDMAODoutput_step)
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
