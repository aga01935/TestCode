#!/usr/bin/python
#include<stdio.h>
import code
import math
import cuts as ct
import ROOT as rt
import fitter as ft
from ROOT import TFile, TTree , TCanvas, TH1F, TList , TH2F ,TH3F ,TMath ,TF1, TStyle ,gStyle , TRefArray, TClonesArray, TObjArray, gPad, TPaveText, TLegend ,TString, TObject,gROOT,TFormula, TEllipse, TDirectory,TLorentzVector
from ROOT import TMath as mt
from datetime import date
# this code creates the histograms from the analysis results and also applies some additional cuts 
# however I am still new to the pyroot so I might be defining histogram more than I needed 
# my goal was to create just one set of histogram and clear it after every time I store them in root file for different level of cuts
# Different directory are created to store all the histogram at different level of cuts


#Opening the file>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
filename = "AnalysisResults"
infilename =filename+".root"
file = TFile.Open(infilename)
#file = TFile.Open("AnalysisResults.root")
#list = TList()
#list = file.Get("Polar")
tree = TTree()

tree = file.Get("PolarizationJP/fRecTree")

entries = tree.GetEntries()

#print list.first()
#daughter1 = TLorentzVector()
#daughter2 = TLorentzVector()
#parent  =   TLorentzVector()
#parent = tree.parent()
#daughter = 
#tree2 = file.Get("tree2")

#tree2.AddFriend(tree)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
text = TPaveText(.05,.1,.95,.8)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
legend = TLegend(0.5,0.6,0.9,0.93)
#this is to use to run in batch mode  to avoid printing all the plots
gROOT.SetBatch(rt.kTRUE)
#this create the master canvas color and the entries to print
#gStyle.SetCanvasColor(22)
gStyle.SetOptStat("e")


#master canvas






Date = date.today()
date_today = filename+str(Date)+".root"
#print date_today

#list of theta bins in helicity
#helicitytheta = ["-0.6<fRecHelicityTheta&&fRecHelicityTheta<-0.520","-0.520<fRecHelicityTheta<-0.440","-0.440<fRecHelicityTheta<-0.360","-0.360<fRecHelicityTheta<-0.280","-0.280<fRecHelicityTheta<-0.200","-0.200<fRecHelicityTheta<-0.120","-0.120<fRecHelicityTheta<-0.040","-0.040<fRecHelicityTheta<0.040","0.040<fRecHelicityTheta<0.120","0.120<fRecHelicityTheta<0.200","0.200<fRecHelicityTheta<0.280","280<fRecHelicityTheta<0.360","0.360<fRecHelicityTheta<0.440","0.440<fRecHelicityTheta<0.520","0.520<fRecHelicityTheta<0.600"]


helicitytheta = ["-0.6<fRecHelicityTheta && fRecHelicityTheta<-0.520","-0.520<fRecHelicityTheta && fRecHelicityTheta<-0.440","-0.440<fRecHelicityTheta && fRecHelicityTheta<-0.360","-0.360<fRecHelicityTheta && fRecHelicityTheta<-0.280","-0.280<fRecHelicityTheta && fRecHelicityTheta<-0.200","-0.200<fRecHelicityTheta && fRecHelicityTheta<-0.120","-0.120<fRecHelicityTheta && fRecHelicityTheta<-0.040","-0.040<fRecHelicityTheta && fRecHelicityTheta<0.040","0.040<fRecHelicityTheta && fRecHelicityTheta<0.120","0.120<fRecHelicityTheta && fRecHelicityTheta<0.200","0.200<fRecHelicityTheta && fRecHelicityTheta<0.280","280<fRecHelicityTheta && fRecHelicityTheta<0.360","0.360<fRecHelicityTheta && fRecHelicityTheta<0.440","0.440<fRecHelicityTheta && fRecHelicityTheta<0.520","0.520<fRecHelicityTheta && fRecHelicityTheta<0.600"]






#list of phi bins in helicity

#helicityphi = ["-3.14<fRecHelicityPhi<-2.889","-2.889<fRecHelicityPhi<-2.638","-2.638<fRecHelicityPhi<-2.386","-2.386<fRecHelicityPhi<-2.135","-2.135<fRecHelicityPhi<-1.884","-1.884<fRecHelicityPhi<-1.633","-1.633<fRecHelicityPhi<-1.382","-1.382<fRecHelicityPhi<-1.130","-1.130<fRecHelicityPhi<-0.879","-0.879<fRecHelicityPhi<-0.628","-0.628<fRecHelicityPhi<-0.377","-0.377<fRecHelicityPhi<-0.126","-0.126<fRecHelicityPhi<0.126","0.126<fRecHelicityPhi<0.377","0.377<fRecHelicityPhi<0.628","0.628<fRecHelicityPhi<0.879","0.879<fRecHelicityPhi<1.130","1.130<fRecHelicityPhi<1.382","1.382<fRecHelicityPhi<1.633","1.633<fRecHelicityPhi<1.884","1.884<fRecHelicityPhi<2.135","2.135<fRecHelicityPhi<2.386","2.386<fRecHelicityPhi<2.638","2.638<fRecHelicityPhi<2.889","2.889<fRecHelicityPhi<3.14"]


helicityphi = ["-3.14<fRecHelicityPhi && fRecHelicityPhi<-2.889","-2.889<fRecHelicityPhi && fRecHelicityPhi<-2.638","-2.638<fRecHelicityPhi && fRecHelicityPhi<-2.386","-2.386<fRecHelicityPhi && fRecHelicityPhi<-2.135","-2.135<fRecHelicityPhi && fRecHelicityPhi<-1.884","-1.884<fRecHelicityPhi && fRecHelicityPhi<-1.633","-1.633<fRecHelicityPhi && fRecHelicityPhi<-1.382","-1.382<fRecHelicityPhi && fRecHelicityPhi<-1.130","-1.130<fRecHelicityPhi && fRecHelicityPhi<-0.879","-0.879<fRecHelicityPhi && fRecHelicityPhi<-0.628","-0.628<fRecHelicityPhi && fRecHelicityPhi<-0.377","-0.377<fRecHelicityPhi && fRecHelicityPhi<-0.126","-0.126<fRecHelicityPhi && fRecHelicityPhi<0.126","0.126<fRecHelicityPhi && fRecHelicityPhi<0.377","0.377<fRecHelicityPhi && fRecHelicityPhi<0.628","0.628<fRecHelicityPhi && fRecHelicityPhi<0.879","0.879<fRecHelicityPhi && fRecHelicityPhi<1.130","1.130<fRecHelicityPhi && fRecHelicityPhi<1.382","1.382<fRecHelicityPhi && fRecHelicityPhi<1.633","1.633<fRecHelicityPhi && fRecHelicityPhi<1.884","1.884<fRecHelicityPhi && fRecHelicityPhi<2.135","2.135<fRecHelicityPhi && fRecHelicityPhi<2.386","2.386<fRecHelicityPhi && fRecHelicityPhi<2.638","2.638<fRecHelicityPhi && fRecHelicityPhi<2.889","2.889<fRecHelicityPhi && fRecHelicityPhi<3.14"]



#tildephi = [0.251]

colinsopertheta =["-0.6<fRecCollinTheta && fRecCollinTheta<-0.520","-0.520<fRecCollinTheta && fRecCollinTheta<-0.440","-0.440<fRecCollinTheta && fRecCollinTheta<-0.360","-0.360<fRecCollinTheta && fRecCollinTheta<-0.280","-0.280<fRecCollinTheta && fRecCollinTheta<-0.200","-0.200<fRecCollinTheta && fRecCollinTheta<-0.120","-0.120<fRecCollinTheta && fRecCollinTheta<-0.040","-0.040<fRecCollinTheta && fRecCollinTheta<0.040","0.040<fRecCollinTheta && fRecCollinTheta<0.120","0.120<fRecCollinTheta && fRecCollinTheta<0.200","0.200<fRecCollinTheta && fRecCollinTheta<0.280","280<fRecCollinTheta && fRecCollinTheta<0.360","0.360<fRecCollinTheta && fRecCollinTheta<0.440","0.440<fRecCollinTheta && fRecCollinTheta<0.520","0.520<fRecCollinTheta && fRecCollinTheta<0.600"]



colinsoperphi =["-3.14<fRecCollinPhi && fRecCollinPhi<-2.889","-2.889<fRecCollinPhi && fRecCollinPhi<-2.638","-2.638<fRecCollinPhi && fRecCollinPhi<-2.386","-2.386<fRecCollinPhi && fRecCollinPhi<-2.135","-2.135<fRecCollinPhi && fRecCollinPhi<-1.884","-1.884<fRecCollinPhi && fRecCollinPhi<-1.633","-1.633<fRecCollinPhi && fRecCollinPhi<-1.382","-1.382<fRecCollinPhi && fRecCollinPhi<-1.130","-1.130<fRecCollinPhi && fRecCollinPhi<-0.879","-0.879<fRecCollinPhi && fRecCollinPhi<-0.628","-0.628<fRecCollinPhi && fRecCollinPhi<-0.377","-0.377<fRecCollinPhi && fRecCollinPhi<-0.126","-0.126<fRecCollinPhi && fRecCollinPhi<0.126","0.126<fRecCollinPhi && fRecCollinPhi<0.377","0.377<fRecCollinPhi && fRecCollinPhi<0.628","0.628<fRecCollinPhi && fRecCollinPhi<0.879","0.879<fRecCollinPhi && fRecCollinPhi<1.130","1.130<fRecCollinPhi && fRecCollinPhi<1.382","1.382<fRecCollinPhi && fRecCollinPhi<1.633","1.633<fRecCollinPhi && fRecCollinPhi<1.884","1.884<fRecCollinPhi && fRecCollinPhi<2.135","2.135<fRecCollinPhi && fRecCollinPhi<2.386","2.386<fRecCollinPhi && fRecCollinPhi<2.638","2.638<fRecCollinPhi && fRecCollinPhi<2.889","2.889<fRecCollinPhi && fRecCollinPhi<3.14"]











file2 = TFile(date_today,"Recreate")
# directory is created to fill histograms without cuts
# way to create a string as a variable

reference_frame = ["colinsoper_phi","collinsoper_theta","helicity_phi","helicity_theta"]

master_canvas = []
 # print vars()
  
  
  
histograms = [] 

nframe = 0
print "reference frame length must be 4 and it is : " , len(reference_frame) 



while  nframe<len(reference_frame):
  folder = reference_frame[nframe]
  
  vars()[folder] = TDirectory()
  
  #folder = TDirectory()

  folder = file2.mkdir(reference_frame[nframe])
  
  
  folder.cd()
  costheta_binmax= 0.6
  costheta_binmin=-0.6
  costheta_bin1 = 100
  costheta_bin2 = 17
  # histogram = TH1F(hist,"",n_bin,xmin,xmax)
  hist_costheta =  TH1F("hist_costheta","",costheta_bin1,costheta_binmax,costheta_binmin)
  
  hist_costheta2 =  TH1F("hist_costheta2", "purityHv3",costheta_bin2,costheta_binmax,costheta_binmin)
  ytitle_costheta = "cos(#theta_{gen && rec on same bin})/cos(#theta_{generated})"
  xtitle_costheta = " cos(#theta_{generated})"
    
  hist_costheta.SetXTitle(xtitle_costheta)
  hist_costheta.SetYTitle(ytitle_costheta)
  hist_costheta.GetYaxis().SetTitleOffset(1.4)
  hist_costheta.GetYaxis().CenterTitle()
  hist_costheta.GetXaxis().CenterTitle()
    
  hist_costheta2.SetXTitle(xtitle_costheta)
  hist_costheta2.SetYTitle(ytitle_costheta)
  hist_costheta2.GetYaxis().SetTitleOffset(1.4)
  hist_costheta2.GetYaxis().CenterTitle()
  hist_costheta2.GetXaxis().CenterTitle()
  
  hist_costheta3 =  TH2F("hist_costheta3", "fBinMigrationHelicityH",25,-1,1,25,-1,1)
  
  xtitle_costheta3 = " cos(#theta_{generated})"
  ytitle_costheta3 = "cos(#theta_{reconstructed}"
  
  hist_costheta3.SetXTitle(xtitle_costheta3)
  hist_costheta3.SetYTitle(ytitle_costheta3)
  hist_costheta3.GetYaxis().SetTitleOffset(1.4)
  hist_costheta3.GetYaxis().CenterTitle()
  hist_costheta3.GetXaxis().CenterTitle()
  
  
  #angular_canvas = "canvas_{}".format(reference_frame[nframe])
  canvasname = "canvas_{}".format(reference_frame[nframe])
  
  ang_canvas1 = TCanvas(canvasname+"1","",600,300)
  ang_canvas1.cd()
 # hist_costheta.Write()
  ang_canvas2 = TCanvas(canvasname+"2","",600,300)
  ang_canvas2.cd()
 # hist_costheta2.Write()
  ang_canvas3 = TCanvas(canvasname+"3","",600,300)
  ang_canvas3.cd()
 # hist_costheta3.Write()
  cutlist_name = "cutlist_{}".format(reference_frame[nframe])
  cut = []
  
  
 
 
 # canvas = TCanvas(hist,"",600,300)
  #tree.Draw("fcostheta>>")
  
  #cos theta
  #MuonPair_normal[15]
  
  #MuonPair_normal = TH1F()
  #Master_Canvas_normal= TCanvas()
  #histname_normal = []
 # cutlist_name = "cutlist_"+ reference_frame[nframe]
  
  
  #print cutlist_name
  
  #hist_name = "histname_"+reference_frame[nframe]
  hist_name = "histname_{}".format(reference_frame[nframe])
  #cutlist_name = [] #char[15]
  

  if (reference_frame[nframe] == "helicity_theta"):
    cut = list(helicitytheta)
    
  if (reference_frame[nframe] == "helicity_phi"):
    cut = list(helicityphi)
      
  if(reference_frame[nframe] == "colinsoper_phi"):
    cut = list(colinsoperphi)
  if(reference_frame[nframe] == "collinsoper_theta"):
    cut = list(colinsopertheta) 
  
  
  
  
  
  #nbins = 80 
  #nfiles = len(hist_name)
  nfiles = len(cut)
  xmin=2.0
  xmax=6.0
  n_bin = 80
  i =0
  
  print "length of the cut parameter list " , len(cut), reference_frame[nframe]
   
  
  
  #print vars()
  
  while i<nfiles:
   
   
   
    print "cut parameters" , cut[i]
    histogram = TString()
  #  hist = hist_name + "_"+ str(i)
    histogram = "{}_{}".format(hist_name,i)
    #print i
    #print hist 
    
   # i=i+1
    canvas = TCanvas(histogram,"Canvas of Mass",600,300)
    histogram = TH1F("histogram","Mass Plots",n_bin,xmin,xmax)
    #print hist
    
  
    bin_width = (xmax-xmin)/n_bin
  
  
  
    #ytitle = "Number of Events/"+ str(bin_width) + " GeV/C #rightarrow"
    ytitle = "Number of Events/{}GeV/C #rightarrow".format(bin_width)
    
    histogram.SetXTitle("Invariant mass of #mu^+mu^- pair(GeV/C^2)#rightarrow")
    
    histogram.SetYTitle(ytitle)
    histogram.GetYaxis().SetTitleOffset(1.4)
    histogram.GetYaxis().CenterTitle()
    histogram.GetXaxis().CenterTitle()
    
    
    
    

    
    
    
 
  
   # master_canvas.append(canvas)
    #histograms.append(histogram)
    
    
    #master_canvas[i].cd() 
    
    canvas.cd()  
    tree.Draw("fRecPair_ParentMass>>histogram",cut[i],"e")  #need to define the cut parameter which will be on cos theta  
    histogram.SetDirectory(0)
 
 
    histogram.Fit(ft.tail_func,"NQR") 
    histogram.Fit(ft.sig_func,"NQR+")
    ft.comb_func.SetParameters(ft.sig_func.GetParameter(0),ft.sig_func.GetParameter(1),ft.sig_func.GetParameter(2),ft.sig_func.GetParameter(3),ft.tail_func.GetParameter(0),ft.tail_func.GetParameter(1),ft.tail_func.GetParameter(6),ft.tail_func.GetParameter(3))
    histogram.Fit(ft.comb_func,"NQR+")
    tailclone = ft.tail_func.Clone("tailclone")
    sigclone  = ft.sig_func.Clone("sigclone")
    combclone = ft.comb_func.Clone("comb_func")
    
    tailclone.FixParameter(0,ft.tail_func.GetParameter(0))
    tailclone.FixParameter(1,ft.tail_func.GetParameter(1))
    tailclone.FixParameter(2,ft.tail_func.GetParameter(2))
    tailclone.FixParameter(3,ft.tail_func.GetParameter(3))
    
    
    sigclone.FixParameter(0,ft.sig_func.GetParameter(0))
    sigclone.FixParameter(1,ft.sig_func.GetParameter(1))
    sigclone.FixParameter(2,ft.sig_func.GetParameter(2))
    sigclone.FixParameter(3,ft.sig_func.GetParameter(3))
    
    combclone.FixParameter(0,ft.comb_func.GetParameter(0))
    combclone.FixParameter(1,ft.comb_func.GetParameter(1))
    combclone.FixParameter(2,ft.comb_func.GetParameter(2))
    combclone.FixParameter(3,ft.comb_func.GetParameter(3))
    combclone.FixParameter(4,ft.comb_func.GetParameter(4))
    combclone.FixParameter(5,ft.comb_func.GetParameter(5))
    combclone.FixParameter(6,ft.comb_func.GetParameter(6))
    combclone.FixParameter(7,ft.comb_func.GetParameter(7))
    
    tailclone.SetLineColor(rt.kRed)
    sigclone.SetLineColor(rt.kGreen)
    combclone.SetLineColor(rt.kBlue)
    tailclone.Draw("SAME")
    sigclone.Draw("SAME")
    combclone.Draw("SAME")
    
    
    
    
    
    
    
  
    
    
    legend.SetHeader("UPC Run2 Dataset","C") # option "C" allows to center the header
    legend.AddEntry(None,cut[i],"")
    legend.AddEntry(None,"#N_{j/\Psi}","")
    legend.AddEntry(None,"#N_{\Psi(2s)}=","")
    legend.AddEntry(None,"#N_{\gamma \gamma}=","")     
    legend.AddEntry("tp","Gaussian with math.exponential and Polynomical background","P")
    #legend.AddEntry("HighPt_Mass",MassCut[0:16],"e2p")
    #cryst.SetParameter(0,const)
    legend.Draw("SAME")
    canvas.Write()
    #histogram.Write()
    
    #histogram.clear()
    #canvas.clear()
    legend.Clear()
    i = i+1
  #  if (i == len(cut)-1):
   #   break
  folder.cd("../")
  
  nframe = nframe+1 
  
  
  #cos phi







file2.Write()
#tree.delete()

file2.Close()

# Mass

#The lines below are so that pyroot do not exit on completing the analysis
vars = globals()
vars.update(locals())
shell = code.InteractiveConsole(vars)
shell.interact()


