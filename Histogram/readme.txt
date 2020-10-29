Counter_Histogram_SideBySide.jpg have the histogram created by my code and Simone's Code
CompareTable_1.jpg has table with some selection and their respective number of events

AnalysisResults.root
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
