#ifndef NTUPLIZER_H
#define NTUPLIZER_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <TNtuple.h>
#include <TString.h>
#include <bitset>


#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Utilities/interface/InputTag.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/Tau.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/BTauReco/interface/JetTag.h"

#include "DataFormats/Common/interface/TriggerResults.h"

#include "tParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"



//Set this variable to decide the number of triggers that you want to check simultaneously
#define NUMBER_OF_MAXIMUM_TRIGGERS 64


/*
██████  ███████  ██████ ██       █████  ██████   █████  ████████ ██  ██████  ███    ██
██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ████   ██
██   ██ █████   ██      ██      ███████ ██████  ███████    ██    ██ ██    ██ ██ ██  ██
██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ██  ██ ██
██████  ███████  ██████ ███████ ██   ██ ██   ██ ██   ██    ██    ██  ██████  ██   ████
*/

class Ntuplizer : public edm::EDAnalyzer {
    public:
        /// Constructor
        explicit Ntuplizer(const edm::ParameterSet&);
        /// Destructor
        virtual ~Ntuplizer();

    private:
        //----edm control---
        virtual void beginJob() ;
        virtual void beginRun(edm::Run const&, edm::EventSetup const&);
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob();
        virtual void endRun(edm::Run const&, edm::EventSetup const&);
        void Initialize();
        bool hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor);

        TTree *_tree;
        TTree *_triggerNamesTree;
        std::string _treeName;
        // -------------------------------------
        // variables to be filled in output tree
        ULong64_t       _indexevents;
        Int_t           _runNumber;
        Int_t           _lumi;
        unsigned long _tauTriggerBits;
        float _tauPt;
        float _tauEta;
        float _tauPhi;
  
        bool _byLooseCombinedIsolationDeltaBetaCorr3Hits;
        bool _byMediumCombinedIsolationDeltaBetaCorr3Hits;
        bool _byTightCombinedIsolationDeltaBetaCorr3Hits;
        bool _byVLooseIsolationMVArun2v1DBoldDMwLT;
        bool _byLooseIsolationMVArun2v1DBoldDMwLT;
        bool _byMediumIsolationMVArun2v1DBoldDMwLT;
        bool _byTightIsolationMVArun2v1DBoldDMwLT;
        bool _byVTightIsolationMVArun2v1DBoldDMwLT;
        bool _byVLooseIsolationMVArun2v1DBnewDMwLT;
        bool _byLooseIsolationMVArun2v1DBnewDMwLT;
        bool _byMediumIsolationMVArun2v1DBnewDMwLT;
        bool _byTightIsolationMVArun2v1DBnewDMwLT;
        bool _byVTightIsolationMVArun2v1DBnewDMwLT;       
        bool _byLooseIsolationMVArun2v1DBdR03oldDMwLT;
        bool _byMediumIsolationMVArun2v1DBdR03oldDMwLT;
        bool _byTightIsolationMVArun2v1DBdR03oldDMwLT;
        bool _byVTightIsolationMVArun2v1DBdR03oldDMwLT;
          
        float _hltPt;
        float _hltEta;
        float _hltPhi;
        float _hltL2CaloJetPt;
        float _hltL2CaloJetEta;
        float _hltL2CaloJetPhi;
        float _hltL2CaloJetIso;

        int _l1tQual;
        float _l1tPt;
        float _l1tEta;
        float _l1tPhi;
        int _l1tIso;
        int _l1tEmuQual;
        float _l1tEmuPt;
        float _l1tEmuEta;
        float _l1tEmuPhi;
        int _l1tEmuIso;
        int _l1tEmuNTT;
        int _l1tEmuHasEM;
        int _l1tEmuIsMerged;
        int _l1tEmuTowerIEta;
        int _l1tEmuTowerIPhi;
        int _l1tEmuRawEt;
        int _l1tEmuIsoEt;
        Bool_t _hasTriggerMuonType;
        Bool_t _hasTriggerTauType;
        Bool_t _isMatched;
        Bool_t _isOS;
        int _foundJet;
        float _muonPt;
        float _muonEta;
        float _muonPhi;
        int _Nvtx;

        edm::EDGetTokenT<pat::MuonRefVector>  _muonsTag;
        edm::EDGetTokenT<pat::TauRefVector>   _tauTag;
        edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> _triggerObjects;
        edm::EDGetTokenT<edm::TriggerResults> _triggerBits;
        edm::EDGetTokenT<l1t::TauBxCollection> _L1TauTag  ;
        edm::EDGetTokenT<l1t::TauBxCollection> _L1EmuTauTag  ;
        edm::EDGetTokenT<std::vector<reco::Vertex>> _VtxTag;
        edm::EDGetTokenT<reco::CaloJetCollection> _hltL2CaloJet_ForIsoPix_Tag;
        edm::EDGetTokenT<reco::JetTagCollection> _hltL2CaloJet_ForIsoPix_IsoTag;

        //!Contains the parameters
        tVParameterSet _parameters;

        edm::InputTag _processName;
        //! Maximum
        std::bitset<NUMBER_OF_MAXIMUM_TRIGGERS> _tauTriggerBitSet;



        HLTConfigProvider _hltConfig;


};

/*
██ ███    ███ ██████  ██      ███████ ███    ███ ███████ ███    ██ ████████  █████  ████████ ██  ██████  ███    ██
██ ████  ████ ██   ██ ██      ██      ████  ████ ██      ████   ██    ██    ██   ██    ██    ██ ██    ██ ████   ██
██ ██ ████ ██ ██████  ██      █████   ██ ████ ██ █████   ██ ██  ██    ██    ███████    ██    ██ ██    ██ ██ ██  ██
██ ██  ██  ██ ██      ██      ██      ██  ██  ██ ██      ██  ██ ██    ██    ██   ██    ██    ██ ██    ██ ██  ██ ██
██ ██      ██ ██      ███████ ███████ ██      ██ ███████ ██   ████    ██    ██   ██    ██    ██  ██████  ██   ████
*/

// ----Constructor and Destructor -----
Ntuplizer::Ntuplizer(const edm::ParameterSet& iConfig) :
_muonsTag       (consumes<pat::MuonRefVector>                     (iConfig.getParameter<edm::InputTag>("muons"))),
_tauTag         (consumes<pat::TauRefVector>                      (iConfig.getParameter<edm::InputTag>("taus"))),
_triggerObjects (consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getParameter<edm::InputTag>("triggerSet"))),
_triggerBits    (consumes<edm::TriggerResults>                    (iConfig.getParameter<edm::InputTag>("triggerResultsLabel"))),
_L1TauTag       (consumes<l1t::TauBxCollection>                   (iConfig.getParameter<edm::InputTag>("L1Tau"))),
_L1EmuTauTag    (consumes<l1t::TauBxCollection>                   (iConfig.getParameter<edm::InputTag>("L1EmuTau"))),
_VtxTag         (consumes<std::vector<reco::Vertex>>              (iConfig.getParameter<edm::InputTag>("Vertexes"))),
_hltL2CaloJet_ForIsoPix_Tag(consumes<reco::CaloJetCollection>     (iConfig.getParameter<edm::InputTag>("L2CaloJet_ForIsoPix_Collection"))),
_hltL2CaloJet_ForIsoPix_IsoTag(consumes<reco::JetTagCollection>   (iConfig.getParameter<edm::InputTag>("L2CaloJet_ForIsoPix_IsoCollection")))
{
    this -> _treeName = iConfig.getParameter<std::string>("treeName");
    this -> _processName = iConfig.getParameter<edm::InputTag>("triggerResultsLabel");

    TString triggerName;
    edm::Service<TFileService> fs;
    this -> _triggerNamesTree = fs -> make<TTree>("triggerNames", "triggerNames");
    this -> _triggerNamesTree -> Branch("triggerNames",&triggerName);

    //Building the trigger arrays
    const std::vector<edm::ParameterSet>& HLTList = iConfig.getParameter <std::vector<edm::ParameterSet> > ("triggerList");
    for (const edm::ParameterSet& parameterSet : HLTList) {
        tParameterSet pSet;
        pSet.hltPath = parameterSet.getParameter<std::string>("HLT");
        triggerName = pSet.hltPath;
        pSet.hltFilters1 = parameterSet.getParameter<std::vector<std::string> >("path1");
        pSet.hltFilters2 = parameterSet.getParameter<std::vector<std::string> >("path2");
        pSet.leg1 = parameterSet.getParameter<int>("leg1");
        pSet.leg2 = parameterSet.getParameter<int>("leg2");
        this -> _parameters.push_back(pSet);

        this -> _triggerNamesTree -> Fill();
    }


    this -> Initialize();
    return;
}

Ntuplizer::~Ntuplizer()
{}

void Ntuplizer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
    Bool_t changedConfig = false;

    if(!this -> _hltConfig.init(iRun, iSetup, this -> _processName.process(), changedConfig)){
        edm::LogError("HLTMatchingFilter") << "Initialization of HLTConfigProvider failed!!";
        return;
    }

    const edm::TriggerNames::Strings& triggerNames = this -> _hltConfig.triggerNames();
    std::cout << " ===== LOOKING FOR THE PATH INDEXES =====" << std::endl;
    for (tParameterSet& parameter : this -> _parameters){
        const std::string& hltPath = parameter.hltPath;
        bool found = false;
        for(unsigned int j=0; j < triggerNames.size(); j++)
        {
	  std::cout << triggerNames[j] << std::endl;
            if (triggerNames[j].find(hltPath) != std::string::npos) {
                found = true;
                parameter.hltPathIndex = j;

                std::cout << "### FOUND AT INDEX #" << j << " --> " << triggerNames[j] << std::endl;
            }
        }
        if (!found) parameter.hltPathIndex = -1;
    }

}

void Ntuplizer::Initialize() {
    this -> _indexevents = 0;
    this -> _runNumber = 0;
    this -> _lumi = 0;
    this -> _tauPt = -1.;
    this -> _tauEta = -1.;
    this -> _tauPhi = -1.;

    this -> _byLooseCombinedIsolationDeltaBetaCorr3Hits = 0;
    this -> _byMediumCombinedIsolationDeltaBetaCorr3Hits = 0;
    this -> _byTightCombinedIsolationDeltaBetaCorr3Hits = 0;
    this -> _byVLooseIsolationMVArun2v1DBoldDMwLT = 0;
    this -> _byLooseIsolationMVArun2v1DBoldDMwLT = 0;
    this -> _byMediumIsolationMVArun2v1DBoldDMwLT = 0;
    this -> _byTightIsolationMVArun2v1DBoldDMwLT = 0;
    this -> _byVTightIsolationMVArun2v1DBoldDMwLT = 0;
    this -> _byVLooseIsolationMVArun2v1DBnewDMwLT = 0;
    this -> _byLooseIsolationMVArun2v1DBnewDMwLT = 0;
    this -> _byMediumIsolationMVArun2v1DBnewDMwLT = 0;
    this -> _byTightIsolationMVArun2v1DBnewDMwLT = 0;
    this -> _byVTightIsolationMVArun2v1DBnewDMwLT = 0;    
    this -> _byLooseIsolationMVArun2v1DBdR03oldDMwLT = 0;
    this -> _byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
    this -> _byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
    this -> _byVTightIsolationMVArun2v1DBdR03oldDMwLT = 0;

    this -> _muonPt = -1.;
    this -> _muonEta = -1.;
    this -> _muonPhi = -1.;
    this -> _isMatched = false;

    this -> _hltPt = -1;
    this -> _hltEta = 666;
    this -> _hltPhi = 666;
    this -> _hltL2CaloJetPt = -1;
    this -> _hltL2CaloJetEta = 666;
    this -> _hltL2CaloJetPhi = 666;
    this -> _hltL2CaloJetIso = -1;

    this -> _l1tPt = -1;
    this -> _l1tEta = 666;
    this -> _l1tPhi = 666;
    this -> _l1tQual = -1;
    this -> _l1tIso = -1;
    this -> _l1tEmuPt = -1;
    this -> _l1tEmuEta = 666;
    this -> _l1tEmuPhi = 666;
    this -> _l1tEmuQual = -1;
    this -> _l1tEmuIso = -1;
    this -> _l1tEmuNTT = -1;
    this -> _l1tEmuHasEM = -1;
    this -> _l1tEmuIsMerged = -1;
    this -> _l1tEmuTowerIEta = -1;
    this -> _l1tEmuTowerIPhi = -1;
    this -> _l1tEmuRawEt = -1;
    this -> _l1tEmuIsoEt = -1;
    this -> _foundJet = 0;
}


void Ntuplizer::beginJob()
{
    edm::Service<TFileService> fs;
    this -> _tree = fs -> make<TTree>(this -> _treeName.c_str(), this -> _treeName.c_str());

    //Branches
    this -> _tree -> Branch("EventNumber",&_indexevents,"EventNumber/l");
    this -> _tree -> Branch("RunNumber",&_runNumber,"RunNumber/I");
    this -> _tree -> Branch("lumi",&_lumi,"lumi/I");
    this -> _tree -> Branch("tauTriggerBits", &_tauTriggerBits, "tauTriggerBits/l");
    this -> _tree -> Branch("tauPt",  &_tauPt,  "tauPt/F");
    this -> _tree -> Branch("tauEta", &_tauEta, "tauEta/F");
    this -> _tree -> Branch("tauPhi", &_tauPhi, "tauPhi/F");

    this -> _tree -> Branch("byLooseCombinedIsolationDeltaBetaCorr3Hits", &_byLooseCombinedIsolationDeltaBetaCorr3Hits, "byLooseCombinedIsolationDeltaBetaCorr3Hits/O");
    this -> _tree -> Branch("byMediumCombinedIsolationDeltaBetaCorr3Hits", &_byMediumCombinedIsolationDeltaBetaCorr3Hits, "byMediumCombinedIsolationDeltaBetaCorr3Hits/O");
    this -> _tree -> Branch("byTightCombinedIsolationDeltaBetaCorr3Hits", &_byTightCombinedIsolationDeltaBetaCorr3Hits, "byTightCombinedIsolationDeltaBetaCorr3Hits/O");
    this -> _tree -> Branch("byVLooseIsolationMVArun2v1DBoldDMwLT", &_byVLooseIsolationMVArun2v1DBoldDMwLT, "byVLooseIsolationMVArun2v1DBoldDMwLT/O");
    this -> _tree -> Branch("byLooseIsolationMVArun2v1DBoldDMwLT", &_byLooseIsolationMVArun2v1DBoldDMwLT, "byLooseIsolationMVArun2v1DBoldDMwLT/O");
    this -> _tree -> Branch("byMediumIsolationMVArun2v1DBoldDMwLT", &_byMediumIsolationMVArun2v1DBoldDMwLT, "byMediumIsolationMVArun2v1DBoldDMwLT/O");
    this -> _tree -> Branch("byTightIsolationMVArun2v1DBoldDMwLT", &_byTightIsolationMVArun2v1DBoldDMwLT, "byTightIsolationMVArun2v1DBoldDMwLT/O");
    this -> _tree -> Branch("byVTightIsolationMVArun2v1DBoldDMwLT", &_byVTightIsolationMVArun2v1DBoldDMwLT, "byVTightIsolationMVArun2v1DBoldDMwLT/O");
    this -> _tree -> Branch("byVLooseIsolationMVArun2v1DBnewDMwLT", &_byVLooseIsolationMVArun2v1DBnewDMwLT, "byVLooseIsolationMVArun2v1DBnewDMwLT/O");
    this -> _tree -> Branch("byLooseIsolationMVArun2v1DBnewDMwLT", &_byLooseIsolationMVArun2v1DBnewDMwLT, "byLooseIsolationMVArun2v1DBnewDMwLT/O");
    this -> _tree -> Branch("byMediumIsolationMVArun2v1DBnewDMwLT", &_byMediumIsolationMVArun2v1DBnewDMwLT, "byMediumIsolationMVArun2v1DBnewDMwLT/O");
    this -> _tree -> Branch("byTightIsolationMVArun2v1DBnewDMwLT", &_byTightIsolationMVArun2v1DBnewDMwLT, "byTightIsolationMVArun2v1DBnewDMwLT/O");
    this -> _tree -> Branch("byVTightIsolationMVArun2v1DBnewDMwLT", &_byVTightIsolationMVArun2v1DBnewDMwLT, "byVTightIsolationMVArun2v1DBnewDMwLT/O");    
    this -> _tree -> Branch("byLooseIsolationMVArun2v1DBdR03oldDMwLT", &_byLooseIsolationMVArun2v1DBdR03oldDMwLT, "byLooseIsolationMVArun2v1DBdR03oldDMwLT/O");
    this -> _tree -> Branch("byMediumIsolationMVArun2v1DBdR03oldDMwLT", &_byMediumIsolationMVArun2v1DBdR03oldDMwLT, "byMediumIsolationMVArun2v1DBdR03oldDMwLT/O");
    this -> _tree -> Branch("byTightIsolationMVArun2v1DBdR03oldDMwLT", &_byTightIsolationMVArun2v1DBdR03oldDMwLT, "byTightIsolationMVArun2v1DBdR03oldDMwLT/O");
    this -> _tree -> Branch("byVTightIsolationMVArun2v1DBdR03oldDMwLT", &_byVTightIsolationMVArun2v1DBdR03oldDMwLT, "byVTightIsolationMVArun2v1DBdR03oldDMwLT/O");


    this -> _tree -> Branch("muonPt",  &_muonPt,  "muonPt/F");
    this -> _tree -> Branch("muonEta", &_muonEta, "muonEta/F");
    this -> _tree -> Branch("muonPhi", &_muonPhi, "muonPhi/F");
    
    this -> _tree -> Branch("hltPt",  &_hltPt,  "hltPt/F");
    this -> _tree -> Branch("hltEta", &_hltEta, "hltEta/F");
    this -> _tree -> Branch("hltPhi", &_hltPhi, "hltPhi/F");

    this -> _tree -> Branch("hltL2CaloJetPt",  &_hltL2CaloJetPt,  "hltL2CaloJetPt/F");
    this -> _tree -> Branch("hltL2CaloJetEta", &_hltL2CaloJetEta, "hltL2CaloJetEta/F");
    this -> _tree -> Branch("hltL2CaloJetPhi", &_hltL2CaloJetPhi, "hltL2CaloJetPhi/F");
    this -> _tree -> Branch("hltL2CaloJetIso", &_hltL2CaloJetIso, "hltL2CaloJetIso/F");

    this -> _tree -> Branch("l1tPt",  &_l1tPt,  "l1tPt/F");
    this -> _tree -> Branch("l1tEta", &_l1tEta, "l1tEta/F");
    this -> _tree -> Branch("l1tPhi", &_l1tPhi, "l1tPhi/F");
    this -> _tree -> Branch("l1tQual", &_l1tQual, "l1tQual/I");
    this -> _tree -> Branch("l1tIso", &_l1tIso, "l1tIso/I");
    this -> _tree -> Branch("l1tEmuPt",  &_l1tEmuPt,  "l1tEmuPt/F");
    this -> _tree -> Branch("l1tEmuEta", &_l1tEmuEta, "l1tEmuEta/F");
    this -> _tree -> Branch("l1tEmuPhi", &_l1tEmuPhi, "l1tEmuPhi/F");
    this -> _tree -> Branch("l1tEmuQual", &_l1tEmuQual, "l1tEmuQual/I");
    this -> _tree -> Branch("l1tEmuIso", &_l1tEmuIso, "l1tEmuIso/I");
    this -> _tree -> Branch("l1tEmuNTT", &_l1tEmuNTT, "l1tEmuNTT/I");
    this -> _tree -> Branch("l1tEmuHasEM", &_l1tEmuHasEM, "l1tEmuHasEM/I");
    this -> _tree -> Branch("l1tEmuIsMerged", &_l1tEmuIsMerged, "l1tEmuIsMerged/I");
    this -> _tree -> Branch("l1tEmuTowerIEta", &_l1tEmuTowerIEta, "l1tEmuTowerIEta/I");
    this -> _tree -> Branch("l1tEmuTowerIPhi", &_l1tEmuTowerIPhi, "l1tEmuTowerIPhi/I");
    this -> _tree -> Branch("l1tEmuRawEt", &_l1tEmuRawEt, "l1tEmuRawEt/I");
    this -> _tree -> Branch("l1tEmuIsoEt", &_l1tEmuIsoEt, "l1tEmuIsoEt/I");


    this -> _tree -> Branch("hasTriggerMuonType", &_hasTriggerMuonType, "hasTriggerMuonType/O");
    this -> _tree -> Branch("hasTriggerTauType", &_hasTriggerTauType, "hasTriggerTauType/O");
    this -> _tree -> Branch("isMatched", &_isMatched, "isMatched/O");
    this -> _tree -> Branch("isOS", &_isOS, "isOS/O");
    this -> _tree -> Branch("foundJet", &_foundJet, "foundJet/I");
    this -> _tree -> Branch("Nvtx", &_Nvtx, "Nvtx/I");

    return;
}


void Ntuplizer::endJob()
{
    return;
}


void Ntuplizer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
    return;
}


void Ntuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{
    this -> Initialize();

    _indexevents = iEvent.id().event();
    _runNumber = iEvent.id().run();
    _lumi = iEvent.luminosityBlock();

    //cout<<"EventNumber = "<<_indexevents<<endl;

    // std::auto_ptr<pat::MuonRefVector> resultMuon(new pat::MuonRefVector);

    // search for the tag in the event
    edm::Handle<pat::MuonRefVector> muonHandle;
    edm::Handle<pat::TauRefVector>  tauHandle;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<std::vector<reco::Vertex> >  vertexes;
    edm::Handle< reco::CaloJetCollection > L2CaloJets_ForIsoPix_Handle;
    edm::Handle< reco::JetTagCollection > L2CaloJets_ForIsoPix_IsoHandle;


    iEvent.getByToken(this -> _muonsTag, muonHandle);
    iEvent.getByToken(this -> _tauTag,   tauHandle);
    iEvent.getByToken(this -> _triggerObjects, triggerObjects);
    iEvent.getByToken(this -> _triggerBits, triggerBits);
    iEvent.getByToken(this -> _VtxTag,vertexes);
    
    try {iEvent.getByToken(_hltL2CaloJet_ForIsoPix_Tag, L2CaloJets_ForIsoPix_Handle);}  catch (...) {;}
    try {iEvent.getByToken(_hltL2CaloJet_ForIsoPix_IsoTag, L2CaloJets_ForIsoPix_IsoHandle);}  catch (...) {;}



//! TagAndProbe on HLT taus
    const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
    const pat::TauRef tau = (*tauHandle)[0] ;
    const pat::MuonRef muon = (*muonHandle)[0] ;

    if(muonHandle.isValid()) this -> _isOS = (muon -> charge() / tau -> charge() < 0) ? true : false;


    this -> _tauTriggerBitSet.reset();


    for (pat::TriggerObjectStandAlone  obj : *triggerObjects)
    {

      obj.unpackPathNames(names);
      const edm::TriggerNames::Strings& triggerNames = names.triggerNames();

        const float dR = deltaR (*tau, obj);
        if ( dR < 0.5)
        {
            this -> _isMatched = true;
            this -> _hasTriggerTauType = obj.hasTriggerObjectType(trigger::TriggerTau);	   
            this -> _hasTriggerMuonType = obj.hasTriggerObjectType(trigger::TriggerMuon);

  	    /*cout<<"hasTriggerTauType="<<this -> _hasTriggerTauType<<endl;
	    cout<<"hasTriggerMuonType="<<this -> _hasTriggerMuonType<<endl;
            const std::vector<std::string>& eventLabels = obj.filterLabels();
	    for(unsigned int i=0; i<eventLabels.size();i++)	
	        cout<<eventLabels[i]<<endl;*/

            //obj.unpackPathNames(names);
            //const edm::TriggerNames::Strings& triggerNames = names.triggerNames();
            //Looking for the path
            unsigned int x = 0;
            bool foundTrigger = false;
            for (const tParameterSet& parameter : this -> _parameters)
            {
                if ((parameter.hltPathIndex >= 0)&&(obj.hasPathName(triggerNames[parameter.hltPathIndex], true, false)))
                {

                    foundTrigger = true;
                    //Path found, now looking for the label 1, if present in the parameter set
                    //std::cout << "==== FOUND PATH " << triggerNames[parameter.hltPathIndex] << " ====" << std::endl;

                    //Retrieving filter list for the event		    		   
                    const std::vector<std::string>& filters = (parameter.leg1 == 15)? (parameter.hltFilters1):(parameter.hltFilters2);
                    if (this -> hasFilters(obj, filters))
		    //if(this -> _hasTriggerTauType)
                    {
		      //std::cout << "#### FOUND TAU WITH HLT PATH " << x << " ####" << std::endl;
                        this -> _hltPt = obj.pt();
                        this -> _hltEta = obj.eta();
                        this -> _hltPhi = obj.phi();
                        this -> _tauTriggerBitSet[x] = true;
                        //std::cout << this -> _tauTriggerBitSet.to_string() << std::endl;
                    }
                }
                x++;
            }
            if (foundTrigger) this -> _foundJet++;
        }
    }


    if(L2CaloJets_ForIsoPix_Handle.isValid() && L2CaloJets_ForIsoPix_IsoHandle.isValid()){

      for (auto const &  jet : *L2CaloJets_ForIsoPix_IsoHandle){
	edm::Ref<reco::CaloJetCollection> jetRef = edm::Ref<reco::CaloJetCollection>(L2CaloJets_ForIsoPix_Handle,jet.first.key());
	
	const float dR = deltaR (*tau, *(jet.first));
	
	if ( dR < 0.5)
	  {
	    this -> _hltL2CaloJetPt = jet.first->pt();
	    this -> _hltL2CaloJetEta = jet.first->eta();
	    this -> _hltL2CaloJetPhi = jet.first->phi();
	    this -> _hltL2CaloJetIso = jet.second;
	  }

      }

    }




    //! TagAndProbe on L1T taus

    edm::Handle< BXVector<l1t::Tau> >  L1TauHandle;
    iEvent.getByToken(_L1TauTag, L1TauHandle);

    float minDR = 0.5; //Uncomment for new match algo

    //cout<<"ill try this: "<<endl;

    for (l1t::TauBxCollection::const_iterator bx0TauIt = L1TauHandle->begin(0); bx0TauIt != L1TauHandle->end(0) ; bx0TauIt++)
    {
        const float dR = deltaR(*tau, *bx0TauIt);
	const l1t::Tau& l1tTau = *bx0TauIt;

	//cout<<"FW Tau, pT = "<<l1tTau.pt()<<", eta = "<<l1tTau.eta()<<", phi = "<<l1tTau.phi()<<endl;

        if (dR < minDR) //Uncomment for new match algo
        //if (dR < 0.5) //Uncomment for old match algo
        {
            minDR = dR; //Uncomment for new match algo
            this -> _l1tPt = l1tTau.pt();
            this -> _l1tEta = l1tTau.eta();
            this -> _l1tPhi = l1tTau.phi();
            this -> _l1tIso = l1tTau.hwIso();
            this -> _l1tQual = l1tTau.hwQual();
        }
    }

    edm::Handle< BXVector<l1t::Tau> >  L1EmuTauHandle;
    try {iEvent.getByToken(_L1EmuTauTag, L1EmuTauHandle);} catch (...) {;}

    if (L1EmuTauHandle.isValid())
      {
	minDR = 0.5;
	
	for (l1t::TauBxCollection::const_iterator bx0EmuTauIt = L1EmuTauHandle->begin(0); bx0EmuTauIt != L1EmuTauHandle->end(0) ; bx0EmuTauIt++)
	  {
	    const float dR = deltaR(*tau, *bx0EmuTauIt);
	    const l1t::Tau& l1tEmuTau = *bx0EmuTauIt;
	    
	    //cout<<"Emul Tau, pT = "<<l1tEmuTau.pt()<<", eta = "<<l1tEmuTau.eta()<<", phi = "<<l1tEmuTau.phi()<<endl;
	    
	    if (dR < minDR) //Uncomment for new match algo
	      {
		minDR = dR; //Uncomment for new match algo
		this -> _l1tEmuPt        = l1tEmuTau.pt();
		this -> _l1tEmuEta       = l1tEmuTau.eta();
		this -> _l1tEmuPhi       = l1tEmuTau.phi();
		this -> _l1tEmuIso       = l1tEmuTau.hwIso();
		this -> _l1tEmuNTT       = l1tEmuTau.nTT();
		this -> _l1tEmuQual      = l1tEmuTau.hwQual();
		this -> _l1tEmuHasEM     = l1tEmuTau.hasEM();
		this -> _l1tEmuIsMerged  = l1tEmuTau.isMerged();
		this -> _l1tEmuTowerIEta = l1tEmuTau.towerIEta();
		this -> _l1tEmuTowerIPhi = l1tEmuTau.towerIPhi();
		this -> _l1tEmuRawEt     = l1tEmuTau.rawEt();
		this -> _l1tEmuIsoEt     = l1tEmuTau.isoEt();
		
	      }
	  }
      }

    this -> _tauPt = tau -> pt();
    this -> _tauEta = tau -> eta();
    this -> _tauPhi = tau -> phi();

    this -> _byLooseCombinedIsolationDeltaBetaCorr3Hits = tau->tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits");
    this -> _byMediumCombinedIsolationDeltaBetaCorr3Hits = tau->tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits");
    this -> _byTightCombinedIsolationDeltaBetaCorr3Hits = tau->tauID("byTightCombinedIsolationDeltaBetaCorr3Hits");
    this -> _byVLooseIsolationMVArun2v1DBoldDMwLT = tau->tauID("byVLooseIsolationMVArun2v1DBoldDMwLT");
    this -> _byLooseIsolationMVArun2v1DBoldDMwLT = tau->tauID("byLooseIsolationMVArun2v1DBoldDMwLT");
    this -> _byMediumIsolationMVArun2v1DBoldDMwLT = tau->tauID("byMediumIsolationMVArun2v1DBoldDMwLT");
    this -> _byTightIsolationMVArun2v1DBoldDMwLT = tau->tauID("byTightIsolationMVArun2v1DBoldDMwLT");
    this -> _byVTightIsolationMVArun2v1DBoldDMwLT = tau->tauID("byVTightIsolationMVArun2v1DBoldDMwLT");
    this -> _byVLooseIsolationMVArun2v1DBnewDMwLT = tau->tauID("byVLooseIsolationMVArun2v1DBnewDMwLT");
    this -> _byLooseIsolationMVArun2v1DBnewDMwLT = tau->tauID("byLooseIsolationMVArun2v1DBnewDMwLT");
    this -> _byMediumIsolationMVArun2v1DBnewDMwLT = tau->tauID("byMediumIsolationMVArun2v1DBnewDMwLT");
    this -> _byTightIsolationMVArun2v1DBnewDMwLT = tau->tauID("byTightIsolationMVArun2v1DBnewDMwLT");
    this -> _byVTightIsolationMVArun2v1DBnewDMwLT = tau->tauID("byVTightIsolationMVArun2v1DBnewDMwLT");
    this -> _byLooseIsolationMVArun2v1DBdR03oldDMwLT = tau->tauID("byLooseIsolationMVArun2v1DBdR03oldDMwLT");
    this -> _byMediumIsolationMVArun2v1DBdR03oldDMwLT = tau->tauID("byMediumIsolationMVArun2v1DBdR03oldDMwLT");
    this -> _byTightIsolationMVArun2v1DBdR03oldDMwLT = tau->tauID("byTightIsolationMVArun2v1DBdR03oldDMwLT");
    this -> _byVTightIsolationMVArun2v1DBdR03oldDMwLT = tau->tauID("byVTightIsolationMVArun2v1DBdR03oldDMwLT");

    if(muonHandle.isValid()) this -> _muonPt=muon->pt();
    if(muonHandle.isValid()) this -> _muonEta=muon->eta();
    if(muonHandle.isValid()) this -> _muonPhi=muon->phi();

    this -> _Nvtx = vertexes->size();

    //float deltaPt = this -> _hltPt - this -> _tauPt;
    //if (this -> _foundJet > 1 ) std::cout << "deltaPt: " << deltaPt << " con foundJet " << this -> _foundJet << " hltPt " << this -> _hltPt << endl;

    this -> _tauTriggerBits = this -> _tauTriggerBitSet.to_ulong();
    //std::cout << "++++++++++ FILL ++++++++++" << std::endl;
    this -> _tree -> Fill();

}

bool Ntuplizer::hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor) {

    const std::vector<std::string>& eventLabels = obj.filterLabels();
    for (const std::string& filter : filtersToLookFor)
    {
        //Looking for matching filters
        bool found = false;
        for (const std::string& label : eventLabels)
        {

	  //cout<<"label="<<label<<endl;
            //if (label == std::string("hltOverlapFilterIsoMu17MediumIsoPFTau40Reg"))
            if (label == filter)
            {

                //std::cout << "#### FOUND FILTER " << label << " == " << filter << " ####" << std::endl;
                found = true;
            }
        }
        if(!found) return false;
    }

    return true;
}


#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(Ntuplizer);

#endif //NTUPLIZER_H
