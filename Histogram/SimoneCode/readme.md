
AnalysisResults.root is produced using Simone's Code for MC particles

Have TDirectory named………. PolarizationJP
PolarizationJP have 
fRecTree- Tree for reconstructed branches and Lorentz vectors
	  fRecPosDaughter is Tlorentz vectors for positive muon tracks
	  fRecNegDaughter is TLorentz vectors for negative muon tracks
	  fRecPair_Parent = TLorentzvector for muon pair

    fRecCollinTildePhi = Reconstructed TildePhi in collinsoper frame
    fRecHelicityTildePhi = Reconstructed TildePhi in helicity frame
    fRecCollinPhi = Reconstructed Phi in collinsoper frame
    fRecHelicityPhi = Reconstructed Phi in helicity frame
    fRecCollinTheta = Reonstructed Costhea in Collinsoper frame 
    fRecHelicityTheta = Reconstructed Costheta in helicityframe
    fZNCEnergy and ZNAEnergy = energy recorded by ZDC
    fZNATDC and fZNCTDC is time recorded by ZDC
    TLorentzVectors with fRec_Connected… are simulated particle corresponding to the reconstructed particles

fOutPutList is TList with histograms 

most important is the fCounterH which records the events with each selection criteria. My issue is my numbers do not match with simone's result eventhough it I am using same input AOD and same selection. 
