
Or = "||"
n = "&&"

PtCut = "fPt>0.5"
#KSigmaTPC_Cut ="(fKaonSigma0*fKaonSigma0 + fKaonSigma1*fKaonSigma1)<4"
KSigmaTPC_Cut ="((fKaonSigma0+0.4)*(fKaonSigma0+0.4) + (fKaonSigma1+0.4)*(fKaonSigma1+0.4))<4"
KSigmaTOF_Cut ="(fKaonSigmaTOF0*fKaonSigmaTOF0 + fKaonSigmaTOF1*fKaonSigmaTOF1)<9"
KSigmaTOF_Cut3 ="(fKaonSigmaTOF0*fKaonSigmaTOF0 + fKaonSigmaTOF1*fKaonSigmaTOF1)<9"
KSigmaTPC_Cut3 ="(fKaonSigma0*fKaonSigma0 + fKaonSigma1*fKaonSigma1)<9"
KSigmaTPC_Cut4 = "(fKaonSigma0>-2 || fKaonSigma1>-2)"
PiSigmaTPC_Cut = " (fPiSigma0>2 && fPiSigma1>3)"
PiSigmaTPC_Cut3 = " (fPiSigma0>3 && fPiSigma1>3)"
PiSigmaTOF_Cut ="(fPiSigmaTOF0>2 && fPiSigmaTOF1>2) "
PiSigmaTOF_Cut3= "(fPiSigmaTOF0>3 && fPiSigmaTOF1>3) "
PiSigmaTpc_Cut4 = "(fPiSigma0*fPiSigma0+fPiSigma1*fPiSigma1)>25"
DaughterPcut = "fPd0<0.8&& fPd1<0.8"
DaughterPcuthigh ="(fPd0>0.4 || fPd0<1.5)&&(fPd1>0.4 || fPd1<1.5)"
DaughterPcut2 = "fPd0<1 && fPd1<1"
DaughterPcuthigh2 ="fPd0>0.4 &&fPd0<1 &&fPd1>0.4 &&fPd1<1"
DCAxyCut = "(TMath::Abs(fDCAxy1) < 2) && (TMath::Abs(fDCAxy2) < 2)"
DCAzCut ="(TMath::Abs(fDCAz1) > 0.05) && (TMath::Abs(fDCAz2) > 0.05)"
TriggerCut="fTriggerClass==31"
KSigmaTPC_TOF = "fKaonSigma0>0 && fKaonSigma0 "
#ElSigmaTPC_Cut =  " (fElSigma0*fElSigma0 + fElSigma1*fElSigma1)>4" 
ElSigmaTPC_Cut =  " (abs(fElSigma0)>3 && abs(fElSigma1>3))"
MuSigmaTPC_Cut = " (fMuSigma0*fMuSigma0 + fMuSigma1*fMuSigma1)<2"
ElSigmaTOF_Cut =  " (fElSigmaTOF0>2 && fElSigmaTOF1>2)"
Charge_Cut = " (fCharge0 * fCharge1) >= 0 "
#PhiCut = "fCCUP8Trigger != 0 && fCCUP8Trigger !=1 && fCCUP8Trigger !=2 && fCCUP8Trigger !=3"
TOFCut ="fCCUP8Trigger!=8"
PhiCut ="(TMath::Abs(fPhi1-fPhi2)<1 || TMath::Abs(fPhi1-fPhi2)>3.14 )"
#Defining the combination of cuts here>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#CombinedCut  = "("+TriggerCut+n+PiSigmaTPC_Cut+n+ElSigmaTPC_Cut+n+KSigmaTPC_Cut+n+"fPt>0.2"+")"+Or+"("+"fPt>0.2"+n+PiSigmaTOF_Cut+n+TriggerCut+n+ElSigmaTOF_Cut+n+KSigmaTOF_Cut+")"
CombinedCut  = "("+TriggerCut+n+PiSigmaTPC_Cut+n+ElSigmaTPC_Cut+n+KSigmaTPC_Cut+n+PtCut+n+DCAxyCut+n+Charge_Cut+")"+Or+"("+PtCut+n+PiSigmaTOF_Cut+n+TriggerCut+n+ElSigmaTOF_Cut+n+KSigmaTOF_Cut+n+DCAxyCut+n+Charge_Cut+")"
#CombinedCut = "("+TriggerCut+n+"fPt>0.7"+")"
#CombinedCut2 = "("+TriggerCut+n+PiSigmaTOF_Cut+n+KSigmaTOF_Cut+n+ElSigmaTOF_Cut+")"
#CombinedCut2  = "("+PiSigmaTPC_Cut+n+ElSigmaTPC_Cut+n+KSigmaTPC_Cut+n+"fPt>0.2"+")"+Or+"("+PiSigmaTOF_Cut+n+ElSigmaTOF_Cut+n+KSigmaTOF_Cut+n+"fPt>0.2"+")"
CombinedCut2 ="("+TriggerCut+n+PiSigmaTPC_Cut+")"+Or+"("+PiSigmaTOF_Cut+n+TriggerCut+")"


MassTpcTofCut522 = "("+KSigmaTPC_Cut+n+TriggerCut+n+PiSigmaTPC_Cut+n+PtCut+")"+Or+"("+PtCut+n+PiSigmaTOF_Cut+n+TriggerCut+n+KSigmaTOF_Cut+")"

MassTpcTofCut532 = "("+KSigmaTPC_Cut3+n+TriggerCut+n+PiSigmaTPC_Cut+n+PtCut+")"+Or+"("+PtCut+n+PiSigmaTOF_Cut+n+TriggerCut+n+KSigmaTOF_Cut3+")"

MassTpcTofCut533 = "("+KSigmaTPC_Cut3+n+TriggerCut+n+PiSigmaTPC_Cut3+n+PtCut+")"+Or+"("+PtCut+n+PiSigmaTOF_Cut3+n+TriggerCut+n+KSigmaTOF_Cut3+")"

MassTpcTofCut523 = "("+KSigmaTPC_Cut+n+TriggerCut+n+PiSigmaTPC_Cut3+n+PtCut+")"+Or+"("+PtCut+n+PiSigmaTOF_Cut3+n+TriggerCut+n+KSigmaTOF_Cut+")"

MassTpcTofCut222 = "("+KSigmaTPC_Cut+n+TriggerCut+n+PiSigmaTPC_Cut+n+"fPt>0.2"+")"+Or+"("+"fPt>0.2"+n+PiSigmaTOF_Cut+n+TriggerCut+n+KSigmaTOF_Cut+")"

MassTpcTofCut232 = "("+KSigmaTPC_Cut3+n+TriggerCut+n+PiSigmaTPC_Cut+n+"fPt>0.2"+")"+Or+"("+"fPt>0.2"+n+PiSigmaTOF_Cut+n+TriggerCut+n+KSigmaTOF_Cut3+")"

MassTpcTofCut233 = "("+KSigmaTPC_Cut3+n+TriggerCut+n+PiSigmaTPC_Cut3+n+"fPt>0.2"+")"+Or+"("+"fPt>0.2"+n+PiSigmaTOF_Cut3+n+TriggerCut+n+KSigmaTOF_Cut3+")"

MassTpcTofCut223 = "("+KSigmaTPC_Cut+n+TriggerCut+n+PiSigmaTPC_Cut3+n+"fPt>0.2"+")"+Or+"("+"fPt>0.2"+n+PiSigmaTOF_Cut3+n+TriggerCut+n+KSigmaTOF_Cut+")"

MassTpcCut =KSigmaTPC_Cut+n+TriggerCut+n+PiSigmaTPC_Cut+n+DaughterPcut+n+DCAzCut+n+PtCut 


Mass3SigmaCut = "("+KSigmaTPC_Cut3+n+TriggerCut+n+PiSigmaTPC_Cut+n+DaughterPcut+n+DCAzCut+n+PtCut+")"+Or+"("+"fPt>1"+n+PiSigmaTOF_Cut+n+TriggerCut+n+KSigmaTOF_Cut3+n+DaughterPcuthigh+n+DCAzCut+")"


MassLowPtCut = "("+KSigmaTPC_Cut+n+TriggerCut+n+PiSigmaTPC_Cut+n+DaughterPcut+n+DCAzCut+n+"fPt>0.2"+")"+Or+"("+"fPt>0.2"+n+PiSigmaTOF_Cut+n+TriggerCut+n+KSigmaTOF_Cut+n+DaughterPcuthigh+n+DCAzCut+")"
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
