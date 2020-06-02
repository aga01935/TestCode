/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

// c++ headers
#include <iostream>
#include <fstream>
#include <map>

// root headers
#include <TMath.h>
#include <TH1I.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TF2.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TTree.h>
#include <TGraph2D.h>
#include <TStopwatch.h>
#include <TMatrixDSym.h>
#include <TFitResult.h>
#include <TLatex.h>
#include <TClonesArray.h>
#include <TDatabasePDG.h>
#include <TLorentzVector.h>
#include <TParticle.h>
#include <TObjString.h>
#include <TList.h>
#include <TChain.h>

// aliroot headers
#include <AliAnalysisTask.h>
#include <AliAnalysisManager.h>
#include <AliAODEvent.h>
#include <AliMCEvent.h>
#include <AliMCParticle.h>
#include <AliAODInputHandler.h> 
#include <AliMuonTrackCuts.h>
#include <AliAODMCParticle.h>

// my headers
#include "AliAnalysisTaskPolarizationTestJP.h"
// ----------------------------------------------------------------------------------------------------------------------------------
class AliAnalysisTaskPolarizationTestJP;    // your analysis class

using namespace std;            // std namespace: so you can do things like 'cout'

ClassImp(AliAnalysisTaskPolarizationTestJP) // classimp: necessary for root

// ----------------------------------------------------------------------------------------------------------------------------------
AliAnalysisTaskPolarizationTestJP::AliAnalysisTaskPolarizationTestJP() : AliAnalysisTaskSE(), 
  fMuonTrackCuts(0x0), fPeriod(0), fTrigger(0), fIsMC(0), fIsScalingOn(0), fAOD(0), fMC(0),
  fOutputList(0),
  fCounterH(0),
  // fNumberMuonsH(0), fNumberMCMuonsH(0),  
  fMapRunAndLumi(), fMapAnalysedMC(),//  fBBAFlags(0), fBBAFlagsAD(0),fBBCFlags(0), fBBCFlagsAD(0),
  // fRAbsMuonH(0), fMuMuMassPtH(0),  
  // fZNAEnergyTimingH(0), fZNCEnergyTimingH(0), fZNATDCTimingH(0), fZNCTDCTimingH(0),
  // fZNAEnergyTimingAllH(0), fZNCEnergyTimingAllH(0), fZNATDCTimingAllH(0), fZNCTDCTimingAllH(0),
  // fZNAEnergy0NH(0), fZNCEnergy0NH(0)
  fRecTree(0), fRunNum(0), fL0inputs(0),
  // fTracklets(0),
  fZNCEnergy(-999), fZNAEnergy(-999), 
  // fZPCEnergy(0), fZPAEnergy(0),
  fV0ADecision(-10), fV0CDecision(-10),  fV0AFiredCells(-10), fV0CFiredCells(-10), fADADecision(-10), fADCDecision(-10), fIsZNAFired(-10), fIsZNCFired(-10),
  // fIR1Map(0), fIR2Map(0), 
 // fMuMuPt(0), 
  // fMuMuPhi(0), 
  //fMuMuY(0),
   fMuMuM(0), fMCMuMuM(0),
  // fMuPt1(0), fMuPt2(0), fMuEta1(0), fMuEta2(0), fMuPhi1(0), fMuPhi2(0), fMuQ1(0), fMuQ2(0),
  fCMUPDecision(-10),fCMUP6Decision(-10), fCMUP10Decision(-10), fCMUP11Decision(-10),fCMUP13Decision(-10),fCMUP26Decision(-10),
  fGenPart(0), fGenTree(0), fMCRunNum(0),
  // fMCMuMuPt(0),
  // fMCMuMuPhi(0), 
  //fMCMuMuY(0), fMCMuMuM(0),
  // fMCMuPt1(0), fMCMuPt2(0), fMCMuEta1(0), fMCMuEta2(0), fMCMuPhi1(0), fMCMuPhi2(0), fMCMuPDG1(0), fMCMuPDG2(0),
  fTrgTree(0), fTrgRunNum(0) 
  ,fCMUP(-10),fCMUP6(-10), fCMUP10(-10), fCMUP11(-10),fCMUP13(-10),fCMUP26(-10)
 //,fHelicityTheta(0),fCollinTheta(0),fCollinTildePhi(0),fHelicityPhi(0),fCollinPhi(0),fHelicityTildePhi(0)
 , fHistRunCounter(0),fRunNumber(0),fHistTriggers(0),fHistCMUPTriggers(0),fHistCMUP6Triggers(0),fHistCMUP10Triggers(0),fHistCMUP11Triggers(0),fHistCMUP13Triggers(0),fHistCMUP26Triggers(0)
 
 ,fMCHelicityTheta(0),fMCCollinTheta(0),fMCCollinTildePhi(0),fMCHelicityPhi(0),fMCCollinPhi(0),fMCHelicityTildePhi(0)
 ,fRecHelicityTheta(0),fRecCollinTheta(0),fRecCollinTildePhi(0),fRecHelicityPhi(0),fRecCollinPhi(0),fRecHelicityTildePhi(0)
 , fMCdaughter1(0.,0.,0.,0.), fMCdaughter2(0.,0.,0.,0.) , fMCparent(0.,0.,0.,0.), fRecdaughter1(0.,0.,0.,0.), fRecdaughter2(0.,0.,0.,0.) , fRecparent(0.,0.,0.,0.)


,fSimulated_Reconstructed_Posdaughter(0.,0.,0.,0.),fSimulated_Reconstructed_Negdaughter(0.,0.,0.,0.),fSimulated_Reconstructed_MuMuPair(0.,0.,0.,0.),fSimulated_Reconstructed_MuMuMass(0) 

,fSimulated_Reconstructed_HelicityTheta(0),fSimulated_Reconstructed_CollinTheta(0),fSimulated_Reconstructed_HelicityPhi(0), fSimulated_Reconstructed_CollinPhi(0),fSimulated_Reconstructed_CollinTildePhi(0),fSimulated_Reconstructed_HelicityTildePhi(0)
 
{
  // default constructor, don't allocate memory here!
  // this is used by root for IO purposes, it needs to remain empty
}
// ----------------------------------------------------------------------------------------------------------------------------------
AliAnalysisTaskPolarizationTestJP::AliAnalysisTaskPolarizationTestJP(const char* name) : AliAnalysisTaskSE(name),
  fMuonTrackCuts(0x0), fPeriod(0), fTrigger(0), fIsMC(0), fIsScalingOn(0), fAOD(0), fMC(0), 
  fOutputList(0),
  fCounterH(0), 
  //fNumberMuonsH(0), fNumberMCMuonsH(0), 
  fMapRunAndLumi(), fMapAnalysedMC(),// fBBAFlags(0), fBBAFlagsAD(0), fBBCFlags(0), fBBCFlagsAD(0),
  // fRAbsMuonH(0), fMuMuMassPtH(0),  
  // fZNAEnergyTimingH(0), fZNCEnergyTimingH(0), fZNATDCTimingH(0), fZNCTDCTimingH(0),
  // fZNAEnergyTimingAllH(0), fZNCEnergyTimingAllH(0), fZNATDCTimingAllH(0), fZNCTDCTimingAllH(0),
  // fZNAEnergy0NH(0), fZNCEnergy0NH(0)
  fRecTree(0), fRunNum(0), fL0inputs(0),
  // fTracklets(0),
  fZNCEnergy(-999), fZNAEnergy(-999), 
  // fZPCEnergy(0), fZPAEnergy(0),
  fV0ADecision(-10), fV0CDecision(-10),  fV0AFiredCells(-10), fV0CFiredCells(-10), fADADecision(-10), fADCDecision(-10), fIsZNAFired(-10), fIsZNCFired(-10),
  // fIR1Map(0), fIR2Map(0), 
 // fMuMuPt(0), 
  // fMuMuPhi(0), 
 // fMuMuY(0), 
 fMuMuM(0), fMCMuMuM(0),
  // fMuPt1(0), fMuPt2(0), fMuEta1(0), fMuEta2(0), fMuPhi1(0), fMuPhi2(0), fMuQ1(0), fMuQ2(0),
  fCMUPDecision(-10),fCMUP6Decision(-10), fCMUP10Decision(-10), fCMUP11Decision(-10),fCMUP13Decision(-10),fCMUP26Decision(-10),
  fGenPart(0), fGenTree(0), fMCRunNum(0), //fMCMuMuPt(0),
  // fMCMuMuPhi(0), 
 // fMCMuMuY(0), fMCMuMuM(0),
  // fMCMuPt1(0), fMCMuPt2(0), fMCMuEta1(0), fMCMuEta2(0), fMCMuPhi1(0), fMCMuPhi2(0), fMCMuPDG1(0), fMCMuPDG2(0),
  fTrgTree(0), fTrgRunNum(0) 
  ,fCMUP(-10),fCMUP6(-10), fCMUP10(-10), fCMUP11(-10), fCMUP13(-10),fCMUP26(-10)
 //,fHelicityTheta(0),fCollinTheta(0),fCollinTildePhi(0),fHelicityPhi(0),fCollinPhi(0),fHelicityTildePhi(0)


 , fHistRunCounter(0),fRunNumber(0),fHistTriggers(0),fHistCMUPTriggers(0),fHistCMUP6Triggers(0),fHistCMUP10Triggers(0),fHistCMUP11Triggers(0),fHistCMUP13Triggers(0),fHistCMUP26Triggers(0)
 
 ,fMCHelicityTheta(0),fMCCollinTheta(0),fMCCollinTildePhi(0),fMCHelicityPhi(0),fMCCollinPhi(0),fMCHelicityTildePhi(0)
 ,fRecHelicityTheta(0),fRecCollinTheta(0),fRecCollinTildePhi(0),fRecHelicityPhi(0),fRecCollinPhi(0),fRecHelicityTildePhi(0)
 
 
 , fMCdaughter1(0.,0.,0.,0.), fMCdaughter2(0.,0.,0.,0.) , fMCparent(0.,0.,0.,0.), fRecdaughter1(0.,0.,0.,0.), fRecdaughter2(0.,0.,0.,0.) , fRecparent(0.,0.,0.,0.)
 
,fSimulated_Reconstructed_Posdaughter(0.,0.,0.,0.),fSimulated_Reconstructed_Negdaughter(0.,0.,0.,0.),fSimulated_Reconstructed_MuMuPair(0.,0.,0.,0.),fSimulated_Reconstructed_MuMuMass(0) 


,fSimulated_Reconstructed_HelicityTheta(0),fSimulated_Reconstructed_CollinTheta(0),fSimulated_Reconstructed_HelicityPhi(0), fSimulated_Reconstructed_CollinPhi(0),fSimulated_Reconstructed_CollinTildePhi(0),fSimulated_Reconstructed_HelicityTildePhi(0) 
 
{
  // constructor
  DefineInput(0, TChain::Class());   
  DefineOutput(1, TTree::Class());
  DefineOutput(2, TList::Class());   
  DefineOutput(3, TTree::Class());
  DefineOutput(4, TTree::Class()); 
}
// ----------------------------------------------------------------------------------------------------------------------------------
AliAnalysisTaskPolarizationTestJP::~AliAnalysisTaskPolarizationTestJP()
{
  // destructor
  // liberate all allocated memory
  if(fOutputList) {delete fOutputList;}     	
  if(fMuonTrackCuts) {delete fMuonTrackCuts;}
  if(fRecTree) {delete fRecTree;}
  if(fGenTree) {delete fGenTree;}
  if(fTrgTree) {delete fTrgTree;}
  if(fCounterH) {delete fCounterH;}
  if(fHistRunCounter) {delete fHistRunCounter;}
  if(fHistTriggers) {delete fHistTriggers;}
  if(fHistCMUPTriggers) {delete fHistCMUPTriggers;}
  if(fHistCMUP6Triggers) {delete fHistCMUP6Triggers;}
  if(fHistCMUP10Triggers) {delete fHistCMUP10Triggers;}
  if(fHistCMUP11Triggers) {delete fHistCMUP11Triggers;}
  if(fHistCMUP13Triggers) {delete fHistCMUP13Triggers;}
  if(fHistCMUP26Triggers) {delete fHistCMUP26Triggers;}
  if(fHistCounter) {delete fHistCounter;}
  
  //if(fNumberMuonsH) {delete fNumberMuonsH;}
  //if(fNumberMCMuonsH) {delete fNumberMCMuonsH;}
  // if(fRAbsMuonH) {delete fRAbsMuonH;}
  // if(fMuMuMassPtH) {delete fMuMuMassPtH;}
}
// ----------------------------------------------------------------------------------------------------------------------------------
void AliAnalysisTaskPolarizationTestJP::UserCreateOutputObjects()
{
  // create output objects
  // this function is called ONCE at the start of your analysis (RUNTIME)

  ////////////////////////////////////////
  //Muon track cuts
  ////////////////////////////////////////
  fMuonTrackCuts = new AliMuonTrackCuts("StdMuonCuts", "StdMuonCuts");
  fMuonTrackCuts->SetFilterMask(AliMuonTrackCuts::kMuEta | AliMuonTrackCuts::kMuPdca | AliMuonTrackCuts::kMuMatchLpt);	
  fMuonTrackCuts->SetAllowDefaultParams(kTRUE);
  fMuonTrackCuts->Print("mask");

  
    
  
  
  
  ////////////////////////////////////////
  //Analysed output tree
  ////////////////////////////////////////
  
  
  
  
  
  
  
  
  
  fRecTree = new TTree("fRecTree", "fRecTree");
 // fRecTree ->Branch("fRunNum", &fRunNum, "fRunNum/I");
  //fRecTree ->Branch("fL0inputs", &fL0inputs, "fL0inputs/i");
  // fRecTree ->Branch("fTracklets", &fTracklets, "fTracklets/I");	
//  fRecTree ->Branch("fZNCEnergy", &fZNCEnergy, "fZNCEnergy/F");  
 // fRecTree ->Branch("fZNAEnergy", &fZNAEnergy, "fZNAEnergy/F");
  // fRecTree ->Branch("fZPCEnergy", &fZPCEnergy, "fZPCEnergy/D");
  // fRecTree ->Branch("fZPAEnergy", &fZPAEnergy, "fZPAEnergy/D");  
  //fRecTree ->Branch("fZNATDC", &fZNATDC[0], "fZNATDC[4]/F");
  //fRecTree ->Branch("fZNCTDC", &fZNCTDC[0], "fZNCTDC[4]/F");  
  // fRecTree ->Branch("fZPATDC", &fZPATDC[0], "fZPATDC[4]/D");
  // fRecTree ->Branch("fZPCTDC", &fZPCTDC[0], "fZPCTDC[4]/D"); 
  //fRecTree ->Branch("fV0ADecision", &fV0ADecision, "fV0ADecision/I");
  //fRecTree ->Branch("fV0CDecision", &fV0CDecision, "fV0CDecision/I");
  //fRecTree ->Branch("fV0AFiredCells", &fV0AFiredCells, "fV0AFiredCells/I");
  //fRecTree ->Branch("fV0CFiredCells", &fV0CFiredCells, "fV0CFiredCells/I");
  //fRecTree ->Branch("fADADecision", &fADADecision, "fADADecision/I");
  //fRecTree ->Branch("fADCDecision", &fADCDecision, "fADCDecision/I");
  //fRecTree ->Branch("fIsZNAFired", &fIsZNAFired, "fIsZNAFired/I");
  //fRecTree ->Branch("fIsZNCFired", &fIsZNCFired, "fIsZNCFired/I");
  // fRecTree ->Branch("fIR1Map", &fIR1Map);
  // fRecTree ->Branch("fIR2Map", &fIR2Map);  
  //fRecTree ->Branch("fMuMuPt", &fMuMuPt, "fMuMuPt/F");
  // fRecTree ->Branch("fMuMuPhi", &fMuMuPhi, "fMuMuPhi/D");
  //fRecTree ->Branch("fMuMuY", &fMuMuY, "fMuMuY/F");
  fRecTree ->Branch("fMuMuM", &fMuMuM, "fMuMuM/F");
  
  
  
  // fRecTree ->Branch("fMuPt1", &fMuPt1, "fMuPt1/D");
  // fRecTree ->Branch("fMuPt2", &fMuPt2, "fMuPt2/D");
  // fRecTree ->Branch("fMuEta1", &fMuEta1, "fMuEta1/D");
  // fRecTree ->Branch("fMuEta2", &fMuEta2, "fMuEta2/D");
  // fRecTree ->Branch("fMuPhi1", &fMuPhi1, "fMuPhi1/D");
  // fRecTree ->Branch("fMuPhi2", &fMuPhi2, "fMuPhi2/D");
  // fRecTree ->Branch("fMuQ1", &fMuQ1, "fMuQ1/D");
  // fRecTree ->Branch("fMuQ2", &fMuQ2, "fMuQ2/D");
  
  fRecTree ->Branch("fCMUPDecision", &fCMUPDecision, "fCMUPDecision/I");
  fRecTree ->Branch("fCMUP6Decision", &fCMUP6Decision, "fCMUP6Decision/I");
  fRecTree ->Branch("fCMUP10Decision", &fCMUP10Decision, "fCMUP10Decision/I");
  fRecTree ->Branch("fCMUP11Decision", &fCMUP11Decision, "fCMUP11Decision/I");
  
  //my additional branches
  fRecTree ->Branch("fCMUP13Decision", &fCMUP13Decision, "fCMUP13Decision/I");
  fRecTree ->Branch("fCMUP26Decision", &fCMUP26Decision, "fCMUP26Decision/I");
  
  
  fRecTree ->Branch("fRecCollinTildePhi", &fRecCollinTildePhi, "fRecCollinTildePhi/F");
  fRecTree ->Branch("fRecHelicityTildePhi", &fRecHelicityTildePhi, "fRecHelicityTildePhi/F");
  
  fRecTree ->Branch("fRecHelicityTheta", &fRecHelicityTheta, "fRecHelicityTheta/F");
  fRecTree ->Branch("fRecHelicityPhi", &fRecHelicityPhi, "fRecHelicityPhi/F");
  
  fRecTree ->Branch("fRecCollinTheta", &fRecCollinTheta, "fRecCollinTheta/F");
  fRecTree ->Branch("fRecCollinPhi", &fRecCollinPhi, "fRecCollinPhi/F");
  
  
  
  
  fRecTree->Branch("fRecdaughter1","TLorentzVector",&fRecdaughter1);
  fRecTree->Branch("fRecdaughter2","TLorentzVector",&fRecdaughter2);
  fRecTree->Branch("fRecparent","TLorentzVector",&fRecparent);
  
  if(fIsMC){
  fRecTree->Branch("fSimulated_Reconstructed_Posdaughter","TLorentzVector",&fSimulated_Reconstructed_Posdaughter);
  fRecTree->Branch("fSimulated_Reconstructed_Negdaughter","TLorentzVector",&fSimulated_Reconstructed_Negdaughter);
  fRecTree->Branch("fSimulated_Reconstructed_MuMuPair","TLorentzVector",&fSimulated_Reconstructed_MuMuPair);
  fRecTree ->Branch("fSimulated_Reconstructed_MuMuMass", &fSimulated_Reconstructed_MuMuMass, "fSimulated_Reconstructed_MuMuMass/F");
  
  
  
  
  
  fRecTree ->Branch("fSimulated_Reconstructed_CollinTildePhi", &fSimulated_Reconstructed_CollinTildePhi, "fSimulated_Reconstructed_CollinTildePhi/F");
  
  fRecTree ->Branch("fSimulated_Reconstructed_HelicityTildePhi", &fSimulated_Reconstructed_HelicityTildePhi, "fSimulated_Reconstructed_HelicityTildePhi/F");
  
  fRecTree ->Branch("fSimulated_Reconstructed_HelicityTheta", &fSimulated_Reconstructed_HelicityTheta, "fSimulated_Reconstructed_HelicityTheta/F");
  fRecTree ->Branch("fSimulated_Reconstructed_HelicityPhi", &fSimulated_Reconstructed_HelicityPhi, "fSimulated_Reconstructed_HelicityPhi/F");
  
  fRecTree ->Branch("fSimulated_Reconstructed_CollinTheta", &fSimulated_Reconstructed_CollinTheta, "fSimulated_Reconstructed_CollinTheta/F");
  fRecTree ->Branch("fSimulated_Reconstructed_CollinPhi", &fSimulated_Reconstructed_CollinPhi, "fSimulated_Reconstructed_CollinPhi/F");
  
  }
  
  
  
  
  
  
  
  
  // post data
  PostData(1, fRecTree);

  ////////////////////////////////////////
  //MC generated output tree
  ////////////////////////////////////////
  fGenTree = new TTree("fGenTree", "fGenTree");
  if(fIsMC){
    fGenPart = new TClonesArray("TParticle", 1000);
   // fGenTree ->Branch("fMCRunNum", &fMCRunNum, "fMCRunNum/I");
   // fGenTree ->Branch("fMCMuMuPt", &fMCMuMuPt, "fMCMuMuPt/F");
    // fGenTree ->Branch("fMCMuMuPhi", &fMCMuMuPhi, "fMCMuMuPhi/D");
   // fGenTree ->Branch("fMCMuMuY", &fMCMuMuY, "fMCMuMuY/F");
    //fGenTree ->Branch("fMCMuMuM", &fMCMuMuM, "fMCMuMuM/F");
    
    
    
    fGenTree->Branch("fMCdaughter1","TLorentzVector",&fMCdaughter1);
    fGenTree->Branch("fMCdaughter2","TLorentzVector",&fMCdaughter2);
    fGenTree->Branch("fMCparent","TLorentzVector",&fMCparent);
    
    
    fGenTree ->Branch("fMCMuMuM", &fMCMuMuM, "fMCMuMuM/F");
   
    fGenTree ->Branch("fMCHelicityTildePhi", &fMCHelicityTildePhi, "fMCHelicityTildePhi/F");
    fGenTree ->Branch("fMCCollinTildePhi", &fMCCollinTildePhi, "fMCCollinTildePhi/F");
    fGenTree ->Branch("fMCHelicityTheta", &fMCHelicityTheta, "fMCHelicityTheta/F");
    fGenTree ->Branch("fMCHelicityPhi", &fMCHelicityPhi, "fMCHelicityPhi/F");
    
    fGenTree ->Branch("fMCCollinTheta", &fMCCollinTheta, "fMCCollinTheta/F");
    fGenTree ->Branch("fMCCollinPhi", &fMCCollinPhi, "fMCCollinPhi/F");
    
    
    // fGenTree ->Branch("fMCMuPt1", &fMCMuPt1, "fMCMuPt1/D");
    // fGenTree ->Branch("fMCMuPt2", &fMCMuPt2, "fMCMuPt2/D");
    // fGenTree ->Branch("fMCMuEta1", &fMCMuEta1, "fMCMuEta1/D");
    // fGenTree ->Branch("fMCMuEta2", &fMCMuEta2, "fMCMuEta2/D");
    // fGenTree ->Branch("fMCMuPhi1", &fMCMuPhi1, "fMCMuPhi1/D");
    // fGenTree ->Branch("fMCMuPhi2", &fMCMuPhi2, "fMCMuPhi2/D");
    // fGenTree ->Branch("fMCMuPDG1", &fMCMuPDG1, "fMCMuPDG1/D");
    // fGenTree ->Branch("fMCMuPDG2", &fMCMuPDG2, "fMCMuPDG2/D");
    // post data
  }  
  PostData(3, fGenTree);

  ////////////////////////////////////////
  //Trigger information tree
  ////////////////////////////////////////
  fTrgTree = new TTree("fTrgTree", "fTrgTree");
  if(!fIsMC){
    
    fTrgTree ->Branch("fTrgRunNum", &fTrgRunNum, "fTrgRunNum/I");
    fTrgTree ->Branch("fCMUP", &fCMUP, "fCMUP/I");
    fTrgTree ->Branch("fCMUP6", &fCMUP6, "fCMUP6/I");
    fTrgTree ->Branch("fCMUP10", &fCMUP10, "fCMUP10/I");
    fTrgTree ->Branch("fCMUP11", &fCMUP11, "fCMUP11/I");
    fTrgTree ->Branch("fCMUP13", &fCMUP13, "fCMUP13/I");
    fTrgTree ->Branch("fCMUP26", &fCMUP26, "fCMUP26/I");
    
    
    // post data
  
  
  
  }  
  PostData(4, fTrgTree);

  ////////////////////////////////////////
  //output histograms
  ////////////////////////////////////////
  fOutputList = new TList();          // this is a list which will contain all  histograms
  fOutputList->SetOwner(kTRUE);       // memory stuff: the list is owner of all objects it contains and will delete them
  //  counter for events passing each cut    
  fCounterH = new TH1F("fCounterH", "fCounterH", 25, 0., 25.);
  fOutputList->Add(fCounterH);
  
  
  
  
  
  
  
  
  
  
  
  
  // number of positive and negative muons passing the muon selection
 // fNumberMuonsH = new TH2F("fNumberMuonsH", "fNumberMuonsH", 12, 0., 12.,12, 0., 12.); 
 // fOutputList->Add(fNumberMuonsH);        // don't forget to add it to the list!
  
  
  fHistRunCounter = new TH1D("fHistRunCounter","Counter", 70000, 240000.5, 310000.5);
  fOutputList->Add(fHistRunCounter);
   
    fHistTriggers= (TH1D*)fHistRunCounter->Clone("fHistTriggers");
    fHistCMUPTriggers= (TH1D*)fHistRunCounter->Clone("fHistCMUPTriggers");
    fHistCMUP6Triggers= (TH1D*)fHistRunCounter->Clone("fHistCMUP6Triggers");
    fHistCMUP10Triggers= (TH1D*)fHistRunCounter->Clone("fHistCMUP10Triggers");
    fHistCMUP11Triggers= (TH1D*)fHistRunCounter->Clone("fHistCMUP11Triggers");
    fHistCMUP13Triggers= (TH1D*)fHistRunCounter->Clone("fHistCMUP13Triggers");
    fHistCMUP26Triggers= (TH1D*)fHistRunCounter->Clone("fHistCMUP26Triggers");
    fOutputList->Add(fHistTriggers);
    fOutputList->Add(fHistCMUPTriggers); 
    fOutputList->Add(fHistCMUP6Triggers);
    fOutputList->Add(fHistCMUP10Triggers);
    fOutputList->Add(fHistCMUP11Triggers);
    fOutputList->Add(fHistCMUP13Triggers);
    fOutputList->Add(fHistCMUP26Triggers);
  
  
  
  // number of positive and negative MC muons passing the muon selection
  if(fIsMC){
   // fNumberMCMuonsH = new TH2F("fNumberMCMuonsH", "fNumberMCMuonsH", 12, 0., 12.,12, 0., 12.); 
    //fOutputList->Add(fNumberMCMuonsH); 
    
  }
  // // Rabs of positive and negative muons passing the muon selection
  // fRAbsMuonH = new TH2F("fRAbsMuonH", "fRAbsMuonH", 100, 0, 100, 100, 0, 100);
  // fOutputList->Add(fRAbsMuonH);
  // // kinematics of dimouns	
  // fMuMuMassPtH = new TH2F("fMuMuMassPtH", "fMuMuMassPtH", 1500, 0, 150, 150, 0, 15);
  // fOutputList->Add(fMuMuMassPtH);

  // post data
  
  
  
  
  PostData(2, fOutputList);           
}
// ----------------------------------------------------------------------------------------------------------------------------------
void AliAnalysisTaskPolarizationTestJP::NotifyRun()
{
  /// Set run number for cuts
  fMuonTrackCuts->SetRun(fInputHandler);
}
// ----------------------------------------------------------------------------------------------------------------------------------
void AliAnalysisTaskPolarizationTestJP::PostAllData()
{
  // Post data
  PostData(1, fRecTree);
  PostData(2, fOutputList);
  PostData(3, fGenTree);
  PostData(4, fTrgTree);
}
// ----------------------------------------------------------------------------------------------------------------------------------
void AliAnalysisTaskPolarizationTestJP::TwoMuonAna(Int_t *idxPosMuons, Int_t *idxNegMuons)
{
  // Get muon masss fromn PDG
  TDatabasePDG *pdgdat = TDatabasePDG::Instance();
  TParticlePDG *partMuon = pdgdat->GetParticle(13);
  Double_t MuonMass = partMuon->Mass();
  
  
  
  // create all four vectors
  // --  positive muon
  TLorentzVector PosMuon1;
  AliAODTrack *PosTrack = static_cast<AliAODTrack*>(fAOD->GetTrack(idxPosMuons[0]));
  //PosMuon1.SetPtEtaPhiM(PosTrack->Pt(), PosTrack->Eta(), PosTrack->Phi(), MuonMass);
  fRecdaughter1.SetPtEtaPhiM(PosTrack->Pt(), PosTrack->Eta(), PosTrack->Phi(), MuonMass);
  // --  negative muon
 

  TLorentzVector NegMuon1;
  AliAODTrack *NegTrack = static_cast<AliAODTrack*>(fAOD->GetTrack(idxNegMuons[0]));
  // NegMuon1.SetPtEtaPhiM(NegTrack->Pt(), NegTrack->Eta(), NegTrack->Phi(), MuonMass);
  fRecdaughter2.SetPtEtaPhiM(NegTrack->Pt(), NegTrack->Eta(), NegTrack->Phi(), MuonMass);
  // fill Rabs histo
  // fRAbsMuonH->Fill(PosTrack->GetRAtAbsorberEnd(),NegTrack->GetRAtAbsorberEnd());
  
  // fill in dimuon kinematics 
  
  
  //TLorentzVector MuMu = NegMuon1+PosMuon1;
  
 // fRecdaughter1 = PosMuon1;
  //fRecdaughter2 = NegMuon1;
  //TLorentzVector MuMu = fRecdaughter1 + fRecdaughter2;
   fRecparent = fRecdaughter1 + fRecdaughter2;
  
   fRecHelicityTheta= CosThetaHelicityFrame(fRecdaughter1,fRecdaughter2,fRecparent);
   fRecCollinTheta= CosThetaCollinsSoper(fRecdaughter1,fRecdaughter2,fRecparent);
      
   fRecHelicityPhi= CosPhiHelicityFrame(fRecdaughter1,fRecdaughter2,fRecparent);
   fRecCollinPhi=  CosPhiCollinsSoper(fRecdaughter1,fRecdaughter2,fRecparent);
   fRecCollinTildePhi = TildePhiCalulator(fRecCollinPhi , fRecCollinTheta);
   fRecHelicityTildePhi = TildePhiCalulator(fRecHelicityPhi , fRecHelicityTheta);
   
   
   fMuMuM = fRecparent.M();
  // fMuMuPt = MuMu.Pt(); 
  // fMuMuPhi = MuMu.Phi();
  //fMuMuY = MuMu.Rapidity(); 
   
  if (fMuMuM ==0) cout<<"reconstruction of parent is not working"<< endl;
  if(fIsMC) {
  
  TClonesArray *mcarray = (TClonesArray*) fAOD->GetList()->FindObject(AliAODMCParticle::StdBranchName());
  if(!mcarray) cout<<"no mc array found on mc data "<< endl;
  
  AliAODMCParticle *mctrack1 = (AliAODMCParticle*) mcarray->At(PosTrack->GetLabel());
  AliAODMCParticle *mctrack2 = (AliAODMCParticle*) mcarray->At(NegTrack->GetLabel());
  
  
  
  fSimulated_Reconstructed_Posdaughter.SetPtEtaPhiM(mctrack1->Pt(), mctrack1->Eta(), mctrack1->Phi(), MuonMass);
  fSimulated_Reconstructed_Negdaughter.SetPtEtaPhiM(mctrack2->Pt(), mctrack2->Eta(), mctrack2->Phi(), MuonMass);
  fSimulated_Reconstructed_MuMuPair = fSimulated_Reconstructed_Posdaughter + fSimulated_Reconstructed_Negdaughter;
  fSimulated_Reconstructed_MuMuMass = fSimulated_Reconstructed_MuMuPair.M();
  
  
  
  
  fSimulated_Reconstructed_HelicityTheta= CosThetaHelicityFrame(fSimulated_Reconstructed_Posdaughter,fSimulated_Reconstructed_Negdaughter,fSimulated_Reconstructed_MuMuPair);
 //cout<<"no problamo"<<endl;
  
  
  fSimulated_Reconstructed_CollinTheta= CosThetaCollinsSoper(fSimulated_Reconstructed_Posdaughter,fSimulated_Reconstructed_Negdaughter,fSimulated_Reconstructed_MuMuPair);
 //cout<<"yes problamo"<<endl;     
  
  
  fSimulated_Reconstructed_HelicityPhi= CosPhiHelicityFrame(fSimulated_Reconstructed_Posdaughter,fSimulated_Reconstructed_Negdaughter,fSimulated_Reconstructed_MuMuPair);
  
  
  fSimulated_Reconstructed_CollinPhi=  CosPhiCollinsSoper(fSimulated_Reconstructed_Posdaughter,fSimulated_Reconstructed_Negdaughter,fSimulated_Reconstructed_MuMuPair);
  
  fSimulated_Reconstructed_CollinTildePhi = TildePhiCalulator(fSimulated_Reconstructed_CollinPhi , fSimulated_Reconstructed_CollinTheta);
  fSimulated_Reconstructed_HelicityTildePhi = TildePhiCalulator(fSimulated_Reconstructed_HelicityPhi , fSimulated_Reconstructed_HelicityTheta);

  
  
  }
 
 
  
  
  
  
  
  // fMuMuMassPtH->Fill(MuMu.M(),MuMu.Pt());

  // set tree variables
  
    
    
   //cout<<fMuMuM<<endl;
  // fMuPt1 = PosTrack->Pt(); 
  // fMuEta1 = PosTrack->Eta(); 
  // fMuPhi1 = PosTrack->Phi();
  // fMuQ1 = PosTrack->Charge(); 

  // fMuPhi2 = NegTrack->Phi();
  // fMuEta2 = NegTrack->Eta();
  // fMuPt2 = NegTrack->Pt();
  // fMuQ2 = NegTrack->Charge();
}
// ----------------------------------------------------------------------------------------------------------------------------------
void AliAnalysisTaskPolarizationTestJP::TwoMCMuonAna(Int_t *idxMCPosMuons, Int_t *idxMCNegMuons)
{
  // get tracks  
  AliMCParticle *PosMCPart = static_cast<AliMCParticle*>(fMC->GetTrack(idxMCPosMuons[0])); 
  AliMCParticle *NegMCPart = static_cast<AliMCParticle*>(fMC->GetTrack(idxMCNegMuons[0]));

  // create lorentz vectors   
  TLorentzVector PosMCMuon,NegMCMuon,MCMuMu;

  //fill fourvectors
  PosMCMuon.SetPxPyPzE(PosMCPart->Px(), PosMCPart->Py(), PosMCPart->Pz(), PosMCPart->E());
  NegMCMuon.SetPxPyPzE(NegMCPart->Px(), NegMCPart->Py(), NegMCPart->Pz(), NegMCPart->E());
  MCMuMu = PosMCMuon+NegMCMuon;

  //connect variables
  fMCRunNum = fAOD->GetRunNumber();
 // fMCMuMuM = MCMuMu.M();
 // fMCMuMuPt = MCMuMu.Pt();
 // fMCMuMuY = MCMuMu.Rapidity();
  // fMCMuMuPhi = MCMuMu.Phi();
  
 // fMCparent = MCMuMu;
  fMCdaughter1 = PosMCMuon;
  fMCdaughter2 = NegMCMuon;
  fMCparent = fMCdaughter1+fMCdaughter2; 
  fMCMuMuM = fMCparent.M();
  fMCHelicityTheta= CosThetaHelicityFrame(fMCdaughter1,fMCdaughter2,fMCparent);
 //cout<<"no problamo"<<endl;
  fMCCollinTheta= CosThetaCollinsSoper(fMCdaughter1,fMCdaughter2,fMCparent);
 //cout<<"yes problamo"<<endl;     
  fMCHelicityPhi= CosPhiHelicityFrame(fMCdaughter1,fMCdaughter2,fMCparent);
  fMCCollinPhi=  CosPhiCollinsSoper(fMCdaughter1,fMCdaughter2,fMCparent);
   fMCCollinTildePhi = TildePhiCalulator(fMCCollinPhi , fMCCollinTheta);
   fMCHelicityTildePhi = TildePhiCalulator(fMCHelicityPhi , fMCHelicityTheta);
  
   

  // fMCMuPt1 = PosMCPart->Pt(); 
  // fMCMuEta1 = PosMCPart->Eta(); 
  // fMCMuPhi1 = PosMCPart->Phi();
  // fMCMuPDG1 = PosMCPart->PdgCode();

  // fMCMuPhi2 = NegMCPart->Phi();
  // fMCMuEta2 = NegMCPart->Eta();
  // fMCMuPt2 = NegMCPart->Pt(); 
  // fMCMuPDG2 = NegMCPart->PdgCode();
}
// ----------------------------------------------------------------------------------------------------------------------------------
void AliAnalysisTaskPolarizationTestJP::UserExec(Option_t *)
{
  Int_t iSelectionCounter = 0; // no selection applied yet 
  fCounterH->Fill(iSelectionCounter); // entering UserExec 1/1 (data/MC)
  iSelectionCounter++;
  fCounterH->GetXaxis()->SetBinLabel(iSelectionCounter,"Data");

  ////////////////////////////////////////////
  // Geting the AOD event
  ////////////////////////////////////////////
   // get AOD event
  
  
  fAOD = dynamic_cast<AliAODEvent*>(InputEvent());    

  if(!fAOD) {
  cout<< "no aod files found"<<endl; 
    PostAllData();
    return;
  }                                  
 // fIsMC = kTRUE;
 
  fCounterH->Fill(iSelectionCounter); // AOD event found 2/2
  iSelectionCounter++;
  fCounterH->GetXaxis()->SetBinLabel(iSelectionCounter,"Events");
  
  // Selecting good runs
  ////////////////////////////////////////////
  Bool_t IsGoodRun = kFALSE;

  fRunNumber = fAOD->GetRunNumber();
  
  
  fHistRunCounter->Fill(fRunNumber);
  
  
// this was causing for histogram not to fill up and if I am specifiying the run number then there is no point in finding good run number here, right?
 /* for(auto i : fMapRunAndLumi){
    if( fAOD->GetRunNumber() == i.first ) IsGoodRun = kTRUE;
    
  }
  
  if(!IsGoodRun) {
    PostAllData();
  
    return;
  }   */          
  //cout<<"here is working"<<endl;                    
  fCounterH->Fill(iSelectionCounter); // Good run selected 3/3
  iSelectionCounter++; 
  fCounterH->GetXaxis()->SetBinLabel(iSelectionCounter,"fMapRunAndLumi");
  ////////////////////////////////////////////
  //  MC Luminosity scaling
  ////////////////////////////////////////////
  const char *InputName = ((TTree*) GetInputData(0))->GetCurrentFile()->GetName();
  Int_t scaling = 20000;

  if( strstr(InputName,"/kCohJpsiToMu/") ){
    scaling = 40000;
  } 

  /*if(fIsMC && fIsScalingOn && (fMapAnalysedMC[fAOD->GetRunNumber()] > Int_t(fMapRunAndLumi[fAOD->GetRunNumber()]*scaling) ) )  {
    cout<<"no mc data"<<endl;
    PostAllData();
    return;
  }  */               
  fMapAnalysedMC[fAOD->GetRunNumber()]++;
 // cout<<"here is working 2"<<endl;
  ////////////////////////////////////////////
  //  MC generated particles analysis
  ////////////////////////////////////////////
  if(fIsMC){
    fGenPart->Clear("C");
    fMC = dynamic_cast<AliMCEvent*>(MCEvent()); 
   // cout<<"found some mc events"<< endl;
    if(!fMC){
      PostAllData();
    //  cout<<" mc events "<< endl;
      return;
      
    }  
    fCounterH->Fill(iSelectionCounter); // MC generated event found -/4
    iSelectionCounter++;
    fCounterH->GetXaxis()->SetBinLabel(iSelectionCounter,"MCEvents");

    //are there particles at all?
    Int_t nMCParticles(fMC->GetNumberOfTracks()); 
    if(nMCParticles<1) {
      PostAllData();
      return;
    } 
   // cout<<"here is working 3"<<endl;
    fCounterH->Fill(iSelectionCounter); // At least one MC generated particle -/5
    iSelectionCounter++;

    // loop over MC tracks and select muons
    Int_t nGoodMCPosMuons = 0;
    Int_t nGoodMCNegMuons = 0;  
    Int_t *idxMCPosMuons = new Int_t[nMCParticles];
    Int_t *idxMCNegMuons = new Int_t[nMCParticles];  
    for(Int_t iMCParticle = 0; iMCParticle < nMCParticles; iMCParticle++) {
      // get track
      AliMCParticle *MCPart = static_cast<AliMCParticle*>(fMC->GetTrack(iMCParticle)); 
      if(!MCPart) return;
      // Particle is primary (for LHC16b2) or is not primary and it is coming from J/Psi or Psi' decay (for LHC18l7)
      if(MCPart->GetMother() == -1){
        // if muons increase counter and store indices
        if(MCPart->PdgCode() == 13){
          idxMCPosMuons[nGoodMCPosMuons] = iMCParticle;
          nGoodMCPosMuons++;
        } else  if(MCPart->PdgCode() == -13){
          idxMCNegMuons[nGoodMCNegMuons] = iMCParticle;
          nGoodMCNegMuons++;
        }
      } else {
        AliMCParticle *MCMother = static_cast<AliMCParticle*>(fMC->GetTrack(MCPart->GetMother()));
        if(MCMother->PdgCode() != 443 && MCMother->PdgCode() != 100443) continue;
        // if muons increase counter and store indices
        if(MCPart->PdgCode() == 13){
          idxMCPosMuons[nGoodMCPosMuons] = iMCParticle;
          nGoodMCPosMuons++;
        } else  if(MCPart->PdgCode() == -13){
          idxMCNegMuons[nGoodMCNegMuons] = iMCParticle;
          nGoodMCNegMuons++;
        }
      } 
    }
    // store number of muons
  //  fNumberMCMuonsH->Fill(nGoodMCPosMuons,nGoodMCNegMuons);

    ////////////////////////////////////////////
    // two MC muon analysis
    ////////////////////////////////////////////
    if (!(nGoodMCPosMuons == 1 && nGoodMCNegMuons == 1)) {
      PostAllData();
      return;
    } 
    fCounterH->Fill(iSelectionCounter); // exactly one positive and one negative MC generated muons -/6
    iSelectionCounter++;
    TwoMCMuonAna(idxMCPosMuons,idxMCNegMuons);
    // FIll the MC generated tree
    fGenTree->Fill();
    }
   // end of MC generated particles

  ////////////////////////////////////////////
  //  Trigger information
  ////////////////////////////////////////////
  // in 2018 q,r : CMUP6-B-NOPF-MUFAST = *0VBA 0MUL ,  
  // in 2018 q,r and 2015 o:  CMUP11-B-NOPF-MUFAST = *0VBA *0UBA *0UBC 0MUL,
  // in 2015 o : CMUP10-B-NOPF-MUFAST = = *0VBA *0UBA *0UBC 0MSL , 
  TString trigger = fAOD->GetFiredTriggerClasses();
  
  Bool_t isTriggered = kFALSE;

  if (fIsMC) {
    if(IsTriggered()){
    cout<< "mc trigger is satisfied"<<endl;
    isTriggered = kTRUE; // Defined the trigger conditions
    fHistTriggers->Fill(fRunNumber);
    }
  } else {
      
      if (trigger.Contains("CMUP")) {
        isTriggered = kTRUE;
        fCMUPDecision = 1;
        fHistCMUPTriggers->Fill(fRunNumber);
        fCMUP = 1;
      } else {
        fCMUPDecision = 0;
        fCMUP = 0;
      }      
      
      
      
      if (trigger.Contains("CMUP11-B-NOPF-MUFAST")) {
        isTriggered = kTRUE;
        fCMUP11Decision = 1;
        fHistCMUP11Triggers->Fill(fRunNumber);
        fCMUP11 = 1;
      } else {
        fCMUP11Decision = 0;
        fCMUP11 = 0;
      }
      
      

      if (trigger.Contains("CMUP10-B-NOPF-MUFAST")) {
        isTriggered = kTRUE;
        fCMUP10Decision = 1;
        fHistCMUP10Triggers->Fill(fRunNumber);
        fCMUP10 = 1;
      } else {
        fCMUP10Decision = 0;
        fCMUP10 = 0;
      }
    
    // ###### CMUP6 trigger  
    if (fTrigger.Contains("CMUP6")){
      if (trigger.Contains("CMUP6-B-NOPF-MUFAST")) {
        isTriggered = kTRUE;
        fCMUP6Decision = 1;
        fHistCMUP6Triggers->Fill(fRunNumber);
        fCMUP6 = 1;
      } else {
        fCMUP6Decision = 0;
        fCMUP6 = 0;
      }
    }
   if (fTrigger.Contains("CMUP13")){
      if (trigger.Contains("CMUP13-B-NOPF-MUFAST")) {
        isTriggered = kTRUE;
        fCMUP13Decision = 1;
        fHistCMUP13Triggers->Fill(fRunNumber);
        fCMUP13 = 1;
      } else {
        fCMUP13Decision = 0;
        fCMUP13 = 0;
      }
    } 
    
    
    
  if (fTrigger.Contains("CMUP26")){
      if (trigger.Contains("CMUP26-B-NOPF-MUFAST")) {
        isTriggered = kTRUE;
        fCMUP26Decision = 1;
        fHistCMUP26Triggers->Fill(fRunNumber);
        fCMUP26 = 1;
      } else {
        fCMUP26Decision = 0;
        fCMUP26 = 0;
      }
    }  
    
    
  }

  if (!isTriggered) {
    PostAllData();
    return;
  }

  if (!fIsMC) {
    fTrgRunNum = fAOD->GetRunNumber();
    // Fill the trigger tree
    fTrgTree->Fill();
  }

  fCounterH->Fill(iSelectionCounter); // right trigger found 4/7
  iSelectionCounter++;

  // get the run number and trigger inputs
  fRunNum = fAOD->GetRunNumber();
  fL0inputs = fAOD->GetHeader()->GetL0TriggerInputs();
  
  ////////////////////////////////////////////
  //  find muons
  ////////////////////////////////////////////
  //are there tracks at all?
  Int_t nTracks(fAOD->GetNumberOfTracks()); 
  if(nTracks<1) {
    PostAllData();
    return;
  } 
  fCounterH->Fill(iSelectionCounter); // At least one track 5/8
  iSelectionCounter++;

  // loop over tracks and select good muons
  Int_t nGoodPosMuons = 0;
  Int_t nGoodNegMuons = 0;  
  Int_t *idxPosMuons = new Int_t[nTracks];
  Int_t *idxNegMuons = new Int_t[nTracks];  
  for(Int_t iTrack = 0; iTrack < nTracks; iTrack++) {
    // get track
    AliAODTrack* track = static_cast<AliAODTrack*>(fAOD->GetTrack(iTrack)); 
    if(!track) return;

    // is it a good muon track?
    if(!track->IsMuonTrack()) continue;
    if(!fMuonTrackCuts->IsSelected(track)) continue;
    if( (track->GetRAtAbsorberEnd() < 17.5) || (track->GetRAtAbsorberEnd() > 89.5) ) continue;

    // increase counter and store indices
    if (track->Charge() > 0) {
      idxPosMuons[nGoodPosMuons] = iTrack;
      nGoodPosMuons++;
    } else  if (track->Charge() < 0) {
      idxNegMuons[nGoodNegMuons] = iTrack;
      nGoodNegMuons++;
    } 
  }
  // store number of muons
 // fNumberMuonsH->Fill(nGoodPosMuons,nGoodNegMuons);

  ////////////////////////////////////////////
  // two muon analysis
  ////////////////////////////////////////////
  if (!(nGoodPosMuons == 1 && nGoodNegMuons == 1)) {
    PostAllData();
    return;
  } 
  fCounterH->Fill(iSelectionCounter); // exactly one positive and one negative muons 6/9
  iSelectionCounter++;
  TwoMuonAna(idxPosMuons,idxNegMuons);

  ////////////////////////////////////////////
  // info to determine exclusivity
  ////////////////////////////////////////////
  // ---SPD
  // fTracklets = fAOD->GetTracklets()->GetNumberOfTracklets();

  // ---ZDC 
  AliAODZDC *dataZDC = dynamic_cast<AliAODZDC*>(fAOD->GetZDCData());
  if(!dataZDC) {
    PostAllData();
    return;
  } 
  fCounterH->Fill(iSelectionCounter); // ZDC info is present 7/10
  iSelectionCounter++;

  fZNAEnergy = dataZDC->GetZNATowerEnergy()[0];
  fZNCEnergy = dataZDC->GetZNCTowerEnergy()[0];
  // fZPAEnergy = dataZDC->GetZPATowerEnergy()[0];
  // fZPCEnergy = dataZDC->GetZPCTowerEnergy()[0];
  for (Int_t i=0;i<4;i++) fZNATDC[i] = dataZDC->GetZNATDCm(i);
  for (Int_t i=0;i<4;i++) fZNCTDC[i] = dataZDC->GetZNCTDCm(i);
  // for (Int_t i=0;i<4;i++) fZPATDC[i] = dataZDC->GetZPATDCm(i);
  // for (Int_t i=0;i<4;i++) fZPCTDC[i] = dataZDC->GetZPCTDCm(i);

  // at least one ZDC hit in the timing window
  fIsZNAFired = 0;
  fIsZNCFired = 0;
  for (Int_t i=0;i<4;i++){
    if ( (fZNATDC[i]>-2.) && (fZNATDC[i]<2.) ) fIsZNAFired = 1;
    if ( (fZNCTDC[i]>-2.) && (fZNCTDC[i]<2.) ) fIsZNCFired = 1;  
  }

  // ---Checks for ZDC informations
  // all ZDC hits in the timing window
  //   if (fZNATDC[iZDC] > -999.){
  //     if ((fZNATDC[iZDC]<-2.) || (fZNATDC[iZDC]>2.)) isZNAfiredAll = kFALSE;
  //   }
  //   if (fZNCTDC[iZDC] > -999.){
  //     if ((fZNCTDC[iZDC]<-2.) || (fZNCTDC[iZDC]>2.)) isZNCfiredAll = kFALSE;
  //   }    
  // }
  // // events with no hits in the ZDC
  // if ( (fZNATDC[0]<-998.5)  && (fZNATDC[1]<-998.5) && (fZNATDC[2]<-998.5) && (fZNATDC[3]<-998.5) ){
  //   isZNAfiredAll = kFALSE;
  //   fZNAEnergy0NH->Fill(fZNAEnergy);
  // }
  // if ( (fZNCTDC[0]<-998.5)  && (fZNCTDC[1]<-998.5) && (fZNCTDC[2]<-998.5) && (fZNCTDC[3]<-998.5) ){
  //   isZNCfiredAll = kFALSE;
  //  fZNCEnergy0NH->Fill(fZNCEnergy);
  // }

  // if(isZNAfired) fZNAEnergyTimingH->Fill(fZNAEnergy);  
  // if(isZNCfired) fZNCEnergyTimingH->Fill(fZNCEnergy);

  // if(isZNAfiredAll) fZNAEnergyTimingAllH->Fill(fZNAEnergy);  
  // if(isZNCfiredAll) fZNCEnergyTimingAllH->Fill(fZNCEnergy);

  // // check for timing of all hits in the triggered events
  // for(Int_t iZDC = 0; iZDC < 4 ; iZDC++) {
  //   if(isZNAfired) fZNATDCTimingH->Fill(fZNATDC[iZDC]);
  //   if(isZNCfired) fZNCTDCTimingH->Fill(fZNATDC[iZDC]);

  //   if(isZNAfiredAll) fZNATDCTimingAllH->Fill(fZNATDC[iZDC]);
  //   if(isZNCfiredAll) fZNCTDCTimingAllH->Fill(fZNATDC[iZDC]);
  // }

  // ---V0
  AliVVZERO *dataVZERO = dynamic_cast<AliVVZERO*>(fAOD->GetVZEROData());
  if(!dataVZERO) {
    PostAllData();
    return;
  } 
  fCounterH->Fill(iSelectionCounter); //  V0 info 8/11
  iSelectionCounter++;

  fV0ADecision = dataVZERO->GetV0ADecision();
  fV0CDecision = dataVZERO->GetV0CDecision();

  Int_t nV0CFiredCells = 0;
  Int_t nV0AFiredCells = 0;

  for(Int_t i = 0; i < 64; i++) {
    if(dataVZERO->GetBBFlag(i) == kTRUE) {
      if(i < 32) {
        nV0CFiredCells += 1;
      } else {
        nV0AFiredCells += 1;
      }
    }
  }

  fV0CFiredCells = nV0CFiredCells;
  fV0AFiredCells = nV0AFiredCells;

  // ---AD
  AliVAD *dataAD = dynamic_cast<AliVAD*>(fAOD->GetADData());
  if(!dataAD){
    PostAllData();
    return;
  } 
  fCounterH->Fill(iSelectionCounter); //  AD info 9/12
  iSelectionCounter++;

  fADADecision = dataAD->GetADADecision();
  fADCDecision = dataAD->GetADCDecision();

  // //Past-future protection maps
  // fIR1Map = fAOD->GetHeader()->GetIRInt1InteractionMap();
  // fIR2Map = fAOD->GetHeader()->GetIRInt2InteractionMap();

  // Fill the reconstruction tree
  fRecTree->Fill();

  // post the data
  PostAllData();

  // clean up
  delete [] idxPosMuons;
  delete [] idxNegMuons;

}

Double_t AliAnalysisTaskPolarizationTestJP::CosPhiHelicityFrame(  TLorentzVector muonPositive,
                                                          TLorentzVector muonNegative,
                                                          TLorentzVector possibleJPsi )
{
  /* - This function computes the helicity phi for the
     - helicity of the J/Psi.
     - The idea should be to get back to a reference frame where it
     - is easier to compute and to define the proper z-axis.
     -
   */

  /* - Half of the energy per pair of the colliding nucleons.
     -
  */
  Double_t HalfSqrtSnn   = 2510.;
  Double_t MassOfLead208 = 193.6823;
  Double_t MomentumBeam  = TMath::Sqrt( HalfSqrtSnn*HalfSqrtSnn*208*208 - MassOfLead208*MassOfLead208 );
  /* - Fill the Lorentz vector for projectile and target.
     - For the moment we do not consider the crossing angle.
     - Projectile runs towards the MUON arm.
     -
   */
  TLorentzVector pProjCM(0.,0., -MomentumBeam, HalfSqrtSnn*208); // projectile
  TLorentzVector pTargCM(0.,0.,  MomentumBeam, HalfSqrtSnn*208); // target
  /* - Translate the dimuon parameters in the dimuon rest frame
     -
   */
  TVector3       beta      = ( -1./possibleJPsi.E() ) * possibleJPsi.Vect();
  TLorentzVector pMu1Dimu  = muonPositive;
  TLorentzVector pMu2Dimu  = muonNegative;
  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);
  //
  // --- Determine the z axis for the calculation of the AliAnalysisTaskPolarizationTestJP angle
  // (i.e. the direction of the dimuon in the CM system)
  //
  TVector3 zaxis = (possibleJPsi.Vect()).Unit();
  TVector3 yaxis = ((pProjDimu.Vect()).Cross(pTargDimu.Vect())).Unit();
  TVector3 xaxis = (yaxis.Cross(zaxis)).Unit();
  //
  // --- Calculation of the azimuthal angle (Helicity)
  //
  Double_t phi = TMath::ATan2((pMu1Dimu.Vect()).Dot(yaxis),(pMu1Dimu.Vect()).Dot(xaxis));
  return   phi;
}      
      


Double_t AliAnalysisTaskPolarizationTestJP::CosPhiCollinsSoper( TLorentzVector muonPositive,
                                                        TLorentzVector muonNegative,
                                                        TLorentzVector possibleJPsi )
{
  /* - This function computes the Collins-Soper PHI for the
     - helicity of the J/Psi.
     - The idea should be to get back to a reference frame where it
     - is easier to compute and to define the proper z-axis.
     -
   */

  /* - Half of the energy per pair of the colliding nucleons.
     -
   */
  Double_t HalfSqrtSnn   = 2510.;
  Double_t MassOfLead208 = 193.6823;
  Double_t MomentumBeam  = TMath::Sqrt( HalfSqrtSnn*HalfSqrtSnn*208*208 - MassOfLead208*MassOfLead208 );
  /* - Fill the Lorentz vector for projectile and target.
     - For the moment we do not consider the crossing angle.
     - Projectile runs towards the MUON arm.
     -
   */
  TLorentzVector pProjCM(0.,0., -MomentumBeam, HalfSqrtSnn*208); // projectile
  TLorentzVector pTargCM(0.,0.,  MomentumBeam, HalfSqrtSnn*208); // target
  /* - Translate the dimuon parameters in the dimuon rest frame
     -
   */
  TVector3       beta      = ( -1./possibleJPsi.E() ) * possibleJPsi.Vect();
  TLorentzVector pMu1Dimu  = muonPositive;
  TLorentzVector pMu2Dimu  = muonNegative;
  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);
  /* - Determine the z axis for the CS angle.
     -
   */
  TVector3 zaxisCS=(((pProjDimu.Vect()).Unit())-((pTargDimu.Vect()).Unit())).Unit();
  //
  // --- Determine the CS angle (angle between mu+ and the z axis defined above)
  //
  TVector3 yaxisCS=(((pProjDimu.Vect()).Unit()).Cross((pTargDimu.Vect()).Unit())).Unit();
  TVector3 xaxisCS=(yaxisCS.Cross(zaxisCS)).Unit();

  Double_t phi = TMath::ATan2((pMu1Dimu.Vect()).Dot(yaxisCS),((pMu1Dimu.Vect()).Dot(xaxisCS)));
  return   phi;
}



Double_t AliAnalysisTaskPolarizationTestJP::CosThetaCollinsSoper( TLorentzVector muonPositive,
                                                          TLorentzVector muonNegative,
                                                          TLorentzVector possibleJPsi )
{
  /* - This function computes the Collins-Soper cos(theta) for the
     - helicity of the J/Psi.
     - The idea should be to get back to a reference frame where it
     - is easier to compute and to define the proper z-axis.
     -
   */

  /* - Half of the energy per pair of the colliding nucleons.
     -
   */
  Double_t HalfSqrtSnn   = 2510.;
  Double_t MassOfLead208 = 193.6823;
  Double_t MomentumBeam  = TMath::Sqrt( HalfSqrtSnn*HalfSqrtSnn*208*208 - MassOfLead208*MassOfLead208 );
  /* - Fill the Lorentz vector for projectile and target.
     - For the moment we do not consider the crossing angle.
     - Projectile runs towards the MUON arm.
     -
   */
  TLorentzVector pProjCM(0.,0., -MomentumBeam, HalfSqrtSnn*208); // projectile
  TLorentzVector pTargCM(0.,0.,  MomentumBeam, HalfSqrtSnn*208); // target
  /* - Translate the dimuon parameters in the dimuon rest frame
     -
   */
  TVector3       beta      = ( -1./possibleJPsi.E() ) * possibleJPsi.Vect();
  TLorentzVector pMu1Dimu  = muonPositive;
  TLorentzVector pMu2Dimu  = muonNegative;
  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);
  /* - Determine the z axis for the CS angle.
     -
   */
  TVector3 zaxisCS=(((pProjDimu.Vect()).Unit())-((pTargDimu.Vect()).Unit())).Unit();
  /* - Determine the CS angle (angle between mu+ and the z axis defined above)
     -
   */
  Double_t CosThetaCS = zaxisCS.Dot((pMu1Dimu.Vect()).Unit());
  return   CosThetaCS;
}


Double_t AliAnalysisTaskPolarizationTestJP::CosThetaHelicityFrame( TLorentzVector muonPositive,
                                                           TLorentzVector muonNegative,
                                                           TLorentzVector possibleJPsi )
{
  /* - This function computes the Helicity cos(theta) for the
     - helicity of the J/Psi.
     - The idea should be to get back to a reference frame where it
     - is easier to compute and to define the proper z-axis.
     -
   */

  /* - Half of the energy per pair of the colliding nucleons.
     -
   */
  Double_t HalfSqrtSnn   = 2510.;
  Double_t MassOfLead208 = 193.6823;
  Double_t MomentumBeam  = TMath::Sqrt( HalfSqrtSnn*HalfSqrtSnn*208*208 - MassOfLead208*MassOfLead208 );
  /* - Fill the Lorentz vector for projectile and target.
     - For the moment we do not consider the crossing angle.
     - Projectile runs towards the MUON arm.
     -
   */
  TLorentzVector pProjCM(0.,0., -MomentumBeam, HalfSqrtSnn*208); // projectile
  TLorentzVector pTargCM(0.,0.,  MomentumBeam, HalfSqrtSnn*208); // target
  /* - Translate the dimuon parameters in the dimuon rest frame
     -
   */
  TVector3       beta      = ( -1./possibleJPsi.E() ) * possibleJPsi.Vect();
  TLorentzVector pMu1Dimu  = muonPositive;
  TLorentzVector pMu2Dimu  = muonNegative;
  TLorentzVector pProjDimu = pProjCM;
  TLorentzVector pTargDimu = pTargCM;
  pMu1Dimu.Boost(beta);
  pMu2Dimu.Boost(beta);
  pProjDimu.Boost(beta);
  pTargDimu.Boost(beta);
  //
  // --- Determine the z axis for the calculation of the AliAnalysisTaskPolarizationTestJP angle
  // (i.e. the direction of the dimuon in the CM system)
  //
  TVector3 zaxis = (possibleJPsi.Vect()).Unit();
  /* - Determine the He angle (angle between mu+ and the z axis defined above)
     -
   */
  Double_t CosThetaHE = zaxis.Dot((pMu1Dimu.Vect()).Unit());
  return   CosThetaHE;

}


Bool_t AliAnalysisTaskPolarizationTestJP::IsTriggered()
{
  /* - This is implemented using Evgeny's Code to create VZero and AD triggers 
     - I am still trying to figure out properly implementing the CMUP triggers
   */
   
  
  UShort_t fTriggerAD = fAOD->GetADData()->GetTriggerBits();
  UShort_t fTriggerVZERO = fAOD->GetVZEROData()->GetTriggerBits();
  UInt_t fL0inputs = fAOD->GetHeader()->GetL0TriggerInputs();
  
  //fTriggerInputsMC[0] = fL0inputs & (1 << 9);   //0VBA VZERO A
  //fTriggerInputsMC[1] = fL0inputs & (1 << 10);   //0VBC VZERO C
  
  
  Bool_t is0VBAfired = fTriggerVZERO & (1 << 12); //0VBA VZERO A
  Bool_t is0VBCfired = fTriggerVZERO & (1 << 13); //0VBC VZERO C
  Bool_t is0UBAfired = fTriggerAD & (1 << 12);   //0UBA ADA
  Bool_t is0UBCfired = fTriggerAD & (1 << 13);   //0UBC ADC
  
  
  
  if (!is0VBAfired && !is0UBAfired && !is0UBCfired ) return kTRUE;
  else return kFALSE;

} 


// this is tilde phi calculator  


Double_t AliAnalysisTaskPolarizationTestJP::TildePhiCalulator(Double_t phi, Double_t costheta){

  Double_t TildePhi;
  if(costheta < 0){
  
  TildePhi = phi - (3/4) * TMath::Pi();  
  }
  else{
  TildePhi = phi- (1/4) * TMath::Pi();

  }


 return TildePhi;
}




















// ----------------------------------------------------------------------------------------------------------------------------------
void AliAnalysisTaskPolarizationTestJP::Terminate(Option_t *)
{
    cout << endl;
    // terminate
    // called at the END of the analysis (when all events are processed)
}
// ----------------------------------------------------------------------------------------------------------------------------------


