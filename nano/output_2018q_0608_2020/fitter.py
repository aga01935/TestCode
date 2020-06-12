#!/usr/bin/python
import code
import math
#import histograms as h1
import cuts as ct
import ROOT as rt

from ROOT import TFile, TTree , TCanvas, TH1F, TList , TH2F ,TH3F ,TMath ,TF1, TStyle ,gStyle , TRefArray, TClonesArray, TObjArray, gPad, TPaveText, TLegend ,TString, TObject,gROOT,TFormula, TEllipse
from ROOT import TMath as mt
#Opening the file>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#file = TFile.Open("Incohernt_Phi_PID1.root")
#list = TList()
#list = file.Get("UPCPhiTaskTest/UPCPhiWithTrigger")
#tree = list.FindObject("scatterplot")
#tree2 = file.Get("tree2")
#tree.SetMarkerStyle(3)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

##Defining crystalball function>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
def cball(x,par):
  A = x[0]-par[0]
  B = 1/(math.sqrt(2)*math.pi*par[1])
  C= math.exp(-(A*A)/(2*par[1]*par[1]))
  D = -par[2]
  E = par[3]
  
  if abs(par[2])<100 and abs(A)<100 and abs(E)<100: #this if statement is due to the limitation of the 
                                      #python as it can not calculate higher math.exponential 
                                      #hence we limited the math.exponential to avoid error of being out of limit
    if x[0]<(par[0]-(par[1]*par[2])) and A>0:
          
     # try:
      #  A**(-E)
   #   except:
     #   print ("A: ",  A , ", E: " , E)
      cb = A**(-E)
     
    else:
      cb =  B*C
  else: # this is for the situation when the math.exponential goes out of limit of python 
   cb = 0   
  return cb
  
  
#bakground function
def tail(x,par):
  A = par[0]*x[0]
  B = 4
  C = (x[0]-B)
  if abs(A)<100:
    if x[0]<B:
      pol = math.exp(A)*(1+ par[1]*C*C +par[2]*C*C*C+par[3]*C*C*C*C)
    else:
      pol = math.exp(A)
        
  else:
    pol =0
  return pol
    
#combined function with both signal and background

def sig_bkg(x,par):
  A = x[0]-par[0]
  B = 1/(math.sqrt(2)*math.pi*par[1])
  C= math.exp(-(A*A)/(2*par[1]*par[1]))
  D = -par[2]
  E = par[3]
  F = par[4]*x[0]
  G = 4
  H = (x[0]-G)
  if abs(A)<100 and abs(F)<100 and abs((par[2])<100) and abs(E)<100 and A>0:
    if x[0]<(par[0]-par[1]*par[2]):
      if x[0]<B:
       
        combined = A**(-E)+ math.exp(F)*(1+ par[5]*H*H +par[6]*H*H*H+par[7]*H*H*H*H)
      else:
        
        combined = A**(-E)+ math.exp(F)
    else:
      if  x[0]<B:
        combined =  B*C +math.exp(F)*(1+ par[5]*H*H +par[6]*H*H*H+par[7]*H*H*H*H)
      else:
        combined = B*C +math.exp(F)
  else: 
    combined = 0
  
  

  return combined
  
tail_func = TF1("tail_func",tail,4,10,4)
sig_func =  TF1("sig_func",cball,2.9,3.2,4) 
comb_func = TF1("comb_func",sig_bkg,0,10,9)




 


sig_func.SetParameters(1,3,2,2)
tail_func.SetParameters(1,3,2,2)
#comb_func.SetParameters(3,1,1,1,1,1,1,1,2)
#comb_func.SetParameter(0,3)
#comb_func.Draw()





#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

"""text = TPaveText(.05,.1,.95,.8)


#Defining histograms>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#gROOT.SetBatch(rt.kTRUE)
#MassPlot for Incoherent Candidates
HighPt_Mass = TH1F("HighPt_Mass","Mass Dist of Inco #Phi Candidates TPC+TOF",100, 0.8,1.8)
#HighPt_Mass.SetFillStyle(4050)
HighPt_Mass.SetYTitle("Number of Events")
HighPt_Mass.SetXTitle("#Phi Mass (GeV/C^2)")
HighPt_Mass.SetTitleOffset(1.5, "Y")
HighPt_Mass.SetTitleOffset(1.3, "X")
HighPt_Mass.SetLineColor(rt.kRed)
HighPt_Mass.SetMarkerStyle(rt.kCircle)
HighPt_Mass.SetLineWidth(4)
HighPt_Mass.SetOption("E1")

#These will define that color of the canvas and the information to show in histogram
#gStyle.SetCanvasColor(22)
gStyle.SetOptStat("e")

# Fit Functions

gau = TF1("gau","gaus",1.006,1.032)
gau2 = TF1("gau2","gaus",1,1.03)
gau3 = TF1("gau3","gaus",1.05,1.25)
gau2.SetLineColor(5)
cryst = TF1("cryst","crystalball",1.002,1.028)
cryst2 = TF1("cryst2","crystalball",0.98,1.032)
cryst2.SetLineColor(rt.kBlack)
#gau = TF1("gau","[0]*math.exp(-0.5*((x-[1])/[2])^2)",0.95,1.05) 
ep = TF1("ep","math.expo",2,3)
ep.SetLineColor(rt.kGreen)
ep2 = TF1("ep2","math.expo(0)+math.expo(2)",1.01,1.1)
ep2.SetLineColor(rt.kYellow)
poly = TF1("poly","pol2",1.05,1.3)
poly1 = TF1("poly1","pol1",1.05,1.2)
poly1.SetLineColor(rt.kGreen)
poly.SetLineColor(rt.kGreen)
tp = TF1("tp","gaus(0)",0,1.2)
#Combined = TF1("Combined","[0]* math.exp(-0.5*((x-[1])/[2])^2)+[3]*math.exp(-[4]*x)",0.9,1.2) 
Combined = TF1("Combined","gaus(0)+ math.expo(3)",0.98,1.8) 
Combined2 = TF1("Combined2","gaus(0)+pol2(3)",0.98,1.8)
Combined3 =  TF1("Combined3","crystalball(0)+math.expo(5)",0.98,1.8)
Combined4 = TF1("Combined4","gaus(0)+gaus(3)+math.expo(6)",0.98,1.8)
Combined5 = TF1("Combined5","gaus(0)+ math.expo(3)",0.98,3) 


Mass_Fit = TCanvas("Mass_Fit","Mass_Fit",600,300,700,527)
gPad.SetTopMargin(0.02)
gPad.SetRightMargin(0.02)
gPad.SetBottomMargin(0.1)
gPad.SetLeftMargin(0.11)
Mass_Fit.Divide(2,1)
Mass_Fit.cd(1)
FinalCut = ct.CombinedCut #combinecut
tree.Draw("fM >>HighPt_Mass",FinalCut,"e")
HighPt_Mass.SetDirectory(0)


gau.SetLineColor(rt.kGreen)

HighPt_Mass.Fit("gau","NQR+")
HighPt_Mass.Fit("poly", "NQR+")
HighPt_Mass.Fit("poly1", "R+")

con = gau.GetParameter(0)
mean = gau.GetParameter(1)
sigma = gau.GetParameter(2)

#con2 = ep.GetParameter(0)
#index3 = ep2.GetParameter(2)
deg0=poly.GetParameter(0)
deg1=poly.GetParameter(1)
deg2=poly.GetParameter(2)
#fit1.SetParameter(0,1)
fit1.SetParameter(1,mean)
fit1.SetParameter(2,sigma)

#fit1.SetParameter(3,2)
#fit1.SetParameter(4,2)
#print "historoot" , fit1.GetChisquare()/fit1.GetNDF() ,gau2.GetChisquare()/gau2.GetNDF()
fit1.SetParameter(3,.8)# last worked one
fit1.SetParameter(4,.8) #last worked one
#fit1.SetParameter(6,index)
#fit1.SetParameter(7,deg2)

HighPt_Mass.Fit("fit1", " R+")

fit2.SetLineColor(rt.kBlack)

#fit2.FixParameter(0,fit1.GetParameter(0))
fit2.SetParameter(1,fit1.GetParameter(1))
fit2.SetParameter(2,fit1.GetParameter(2))
fit2.FixParameter(3,fit1.GetParameter(3))
fit2.FixParameter(4,fit1.GetParameter(4))
#fit2.SetParameter(6,index)

#fit2.FixParameter(5,con)

fit3.FixParameter(1,fit1.GetParameter(1))
fit3.FixParameter(2,fit1.GetParameter(2))
fit3.FixParameter(3,fit1.GetParameter(3))
fit3.FixParameter(4,fit1.GetParameter(4))


HighPt_Mass.Fit("fit3", "R+")
#fit3.Draw("SAME")
alpha = cryst.GetParameter(3)
mean3 = cryst.GetParameter(1)
slope = cryst.GetParameter(4)
sigma3 = cryst.GetParameter(2)

print "chisquare of fit3 crystalball and polynomical " ,fit3.GetChisquare()/fit3.GetNDF()

legend = TLegend(0.4,0.7,0.9,0.9)
#legend.SetHeader("The Legend Title","C") # option "C" allows to center the header
#legend.AddEntry(None,{tp.GetChisquare},"f")
legend.AddEntry("tp","Gaussian with math.exponential and Polynomical background","l")
#legend.AddEntry("HighPt_Mass",MassCut[0:16],"e2p")
#cryst.SetParameter(0,const)

#Fitting with Combined Function
polyclone = TF1("polyclone","pol2",0.8,1.3)
polyclone.FixParameter(0,fit3.GetParameter(5))
polyclone.FixParameter(1,fit3.GetParameter(6))
polyclone.FixParameter(2,fit3.GetParameter(7))

polyclone.SetLineWidth(3)
polyclone.SetLineColor(rt.kGreen)

fit1clone = TF1("fit1clone",cball1,0.8,1.8,5)
fit1clone.FixParameter(0,fit3.GetParameter(0))
fit1clone.FixParameter(1,fit3.GetParameter(1))
fit1clone.FixParameter(2,fit3.GetParameter(2))
fit1clone.FixParameter(3,fit3.GetParameter(3))
fit1clone.FixParameter(4,fit3.GetParameter(4))
fit1clone.SetLineColor(rt.kBlue)
fit3clone =  TF1("fit3clone",cball3,0.8,1.3,8)
fit3clone.FixParameter(0,fit3.GetParameter(0))
fit3clone.FixParameter(1,fit3.GetParameter(1))
fit3clone.FixParameter(2,fit3.GetParameter(2))
fit3clone.FixParameter(3,fit3.GetParameter(3))
fit3clone.FixParameter(4,fit3.GetParameter(4))
fit3clone.FixParameter(5,fit3.GetParameter(5))
fit3clone.FixParameter(6,fit3.GetParameter(6))
fit3clone.FixParameter(7,fit3.GetParameter(7))
fit3clone.SetLineWidth(3)
fit3clone.SetLineColor(rt.kBlack)
#fit3clone.Draw("SAME")

#fit1clone.Draw("SAME")
polyclone.Draw("SAME")
#fit1.Draw("SAME")
#poly.Draw("SAME")
#legend.AddEntry(None,r,"ep")
#legend.AddEntry(None,{r},"f")
#LowPt_Mass.Draw()
poly2 =TF1("poly2","pol2",0.8,1.8)
poly2.SetLineColor(rt.kGreen)
poly2.FixParameter(0,poly.GetParameter(0))
poly2.FixParameter(1,poly.GetParameter(1))
poly2.FixParameter(2,poly.GetParameter(2))
#poly2.FixParameter(3,Combined2.GetParameter(6))
#poly2.FixParameter(4,Combined2.GetParameter(7))
#poly2.FixParameter(5,Combined2.GetParameter(8))
#poly2.FixParameter(6,Combined2.GetParameter(9))
#poly2.Draw("SAME") 

gau5 = TF1("gau5","gaus",1.002,1.035)
gau5.FixParameter(0,Combined2.GetParameter(0))
gau5.FixParameter(1,Combined2.GetParameter(1))
gau5.FixParameter(2,Combined2.GetParameter(2))
gau5.SetLineColor(rt.kBlue)

gau4 = TF1("gau4","gaus",1.006,1.032)
gau4.FixParameter(0,Combined.GetParameter(0))
gau4.FixParameter(1,Combined.GetParameter(1))
gau4.FixParameter(2,Combined.GetParameter(2))
gau4.SetLineColor(rt.kBlue)
m = Combined.GetParameter(1)
s = Combined.GetParameter(2)
m2 = Combined2.GetParameter(1)
s2 = Combined2.GetParameter(2)

a2 = m2 - 2*s2
b2 = m2 + 2*s2
#gau5.Draw("SAME")
a = m - 2*s
b = m + 2*s
a3 = fit1.GetParameter(1)-2*fit1.GetParameter(2)
b3 = fit1.GetParameter(1)+2*fit1.GetParameter(2)

ep4 = TF1("ep4","math.expo",1.006,1.032)
ep4.FixParameter(0,Combined.GetParameter(3))
ep4.FixParameter(1,Combined.GetParameter(4))
ep5 = TF1("ep5","math.expo",0,1.8)
ep5.FixParameter(0,ep.GetParameter(0))
ep5.FixParameter(1,ep.GetParameter(1))
ep5.SetLineColor(rt.kGreen)
#ep5.Draw("SAME")
#ep2.Draw("SAME")
#poly2.Draw("SAME")
#Combined2.Draw("SAME")
yeildfit = (fit3.Integral(a3,b3)-polyclone.Integral(a3,b3)) *100
backfit = polyclone.Integral(a3,b3)*100
ratiofit = yeildfit/backfit
yf = str(yeildfit)
bf = str(backfit)
rf = str (ratiofit)
chif = fit3.GetChisquare()/fit3.GetNDF()
cf = str(chif)
print "yeild" , yf, "background", bf, "ratio" ,rf




Mass_Fit.cd(2)
text.AddText("CCUP8")
text.AddText("Filterbit 1<<0")
text.AddText("Two Track")
text.AddText("Opposite Charge")

#text.AddText("Gaus + Polynomial Background")
#text.AddText ("Chisquare/Ndf = "+r2)
#text.AddText("yeild = "+y2)
#text.AddText("Background = "+ b2)
#text.AddText("Ratio = "+ rat2)
text.AddText("My function +Polynomial background")
text.AddText("yeild = "+ yf)
text.AddText("Background = "+bf)
text.AddText("Ratio = "+ rf)
text.AddText("Chisquare/Ndf = "+cf)
text.AddText("Cuts Applied Are")
text.AddText("CCUP8Trigger")
if FinalCut == ct.MassTpcTofCut522:

	text.AddText("Parent Pt > 0.5")
	text.AddText("Kaon #sqrt{n#sigma_{Track 1}^{2} + n#sigma_{Track 2}^{2}}<2")
	text.AddText("Pion n#sigma>2")
	text.AddText("Added Similar TOF PID Cuts Only Available")
if FinalCut == ct.MassTpcTofCut532:

	text.AddText("Parent Pt > 0.5")
	text.AddText("Kaon #sqrt{n#sigma_{Track 1}^{2} + n#sigma_{Track 2}^{2}}<3")
	text.AddText("Pion n#sigma>2")
	text.AddText("Added Similar TOF PID Cuts Only Available")
if FinalCut == ct.MassTpcTofCut533:

	text.AddText("Parent Pt > 0.5")
	text.AddText("Kaon #sqrt{n#sigma_{Track 1}^{2} + n#sigma_{Track 2}^{2}}<3")
	text.AddText("Pion n#sigma>3")
	text.AddText("Added Similar TOF PID Cuts Only Available")
if FinalCut == ct.MassTpcTofCut523:

	text.AddText("Parent Pt > 0.5")
	text.AddText("Kaon #sqrt{n#sigma_{Track 1}^{2} + n#sigma_{Track 2}^{2}}<2")
	text.AddText("Pion n#sigma>3")
	text.AddText("Added Similar TOF PID Cuts Only Available")

if FinalCut == ct.MassTpcTofCut222:

	text.AddText("Parent Pt > 0.2")
	text.AddText("Kaon #sqrt{n#sigma_{Track 1}^{2} + n#sigma_{Track 2}^{2}}<2")
	text.AddText("Pion n#sigma>2")
	text.AddText("Added Similar TOF PID Cuts Only Available")

if FinalCut == ct.MassTpcTofCut232:

	text.AddText("Parent Pt > 0.2")
	text.AddText("Kaon #sqrt{n#sigma_{Track 1}^{2} + n#sigma_{Track 2}^{2}}<3")
	text.AddText("Pion n#sigma>2")
	text.AddText("Added Similar TOF PID Cuts Only Available")
if FinalCut == ct.MassTpcTofCut233:

	text.AddText("Parent Pt > 0.2")
	text.AddText("Kaon #sqrt{n#sigma_{Track 1}^{2} + n#sigma_{Track 2}^{2}}<3")
	text.AddText("Pion n#sigma>3")
	text.AddText("Added Similar TOF PID Cuts Only Available")
if FinalCut == ct.MassTpcTofCut223:

	text.AddText("Parent Pt > 0.2")
	text.AddText("Kaon #sqrt{n#sigma_{Track 1}^{2} + n#sigma_{Track 2}^{2}}<2")
	text.AddText("Pion n#sigma>3")
	text.AddText("Added Similar TOF PID Cuts Only Available")
text.Draw()


#fit1.SetLineColor(rt.kBlue)
#fit1.Draw("SAME")

file = TFile("histogram_results.root","Recreate")

#Writing Canvas to the file so that can be finely edited later
#PhiMass.Write()


Mass_Fit.Write()

Mass_Fit.SaveAs("fit.pdf")"""

#The lines below are so that pyroot do not exit on completing the analysis

vars = globals()
vars.update(locals())
shell = code.InteractiveConsole(vars)
shell.interact()

