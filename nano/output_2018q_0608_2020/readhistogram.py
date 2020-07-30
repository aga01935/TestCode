#!/usr/bin/python
#include<stdio.h>
import code
import math
import cuts as ct
import ROOT as rt
import fitter as ft
from ROOT import TFile, TTree, TCanvas, TH1F, TList, TH2F,TH3F ,TMath, TF1, TStyle, gStyle, TRefArray, TClonesArray, TObjArray, gPad, TPaveText, TLegend ,TString, TObject,gROOT,TFormula, TEllipse, TDirectory,TLorentzVector
from ROOT import TMath as mt
from datetime import date
# this code creates the histograms from the analysis results and also applies some additional cuts
# however I am still new to the pyroot so I might be defining histogram more than I needed
# my goal was to create just one set of histogram and clear it after every time I store them in root file for different level of cuts
# Different directory are created to store all the histogram at different level of cuts


#Opening the file>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
filename = "AnalysisResults"

infilename =filename+".root"




mcfilename_psi = "AnalysisResults_MC_Psi_MuMu_Incomplete"
mcfilename_jpsi = "AnalysisResults_MC_Jpsi_Incomplete"
mcfilename_gammagamma = "AnalysisResults_MC_gammagamma"
inmc_psi_filename = mcfilename_psi+".root"
inmc_jpsi_filename = mcfilename_jpsi+".root"

inmc_gammagamma = mcfilename_gammagamma+".root"
file = TFile.Open(infilename)
mcfile_psi = TFile.Open(inmc_psi_filename)
mcfile_jpsi = TFile.Open(inmc_jpsi_filename)
##this line below will be used after obtaining gamma gamma mc analysis result

#mcfile_gammagamma = TFile.Open(inmc_gammagamma)


#file = TFile.Open("AnalysisResults.root")
#list = TList()
#list = file.Get("Polar")
tree = TTree()
#mcrectree_psi = TTree()
#mcgentree_psi = TTree()
#mcrectree_jpsi = TTree()
#mcgentree_jpsi = TTree()
#mcgentree_gammagamma = TTree()

tree = file.Get("PolarizationJP/fRecTree")
#mcgentree_psi = mcfile_psi.Get("PolarizationJP/fGenTree")

#mcrectree_jpsi = mcfile_jpsi.Get("PolarizationJP/fRecTree")
#mcgentree_psi = mcfile_jpsi.Get("PolarizationJP/fGenTree")


#mcgentree_gammagamma = mcfile_gammagamma.Get("PolarizationJP/fGenTree")
#entries = tree.GetEntries()

#entries = mcrectree_psi.GetEntries()
#entries = mcgentree_psi.GetEntries()

#entries = mcgentree_jpsi.GetEntries()
#entries = mcrectree_jpsi.GetEntries()

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
#legend = TLegend(x1,y1,x2,y2)
legend = TLegend(0.6,0.6,0.9,0.93)
#this is to use to run in batch mode  to avoid printing all the plots
gROOT.SetBatch(rt.kTRUE)
#this create the master canvas color and the entries to print
#gStyle.SetCanvasColor(22)
gStyle.SetOptStat("e")


#########################################################################
filenamelist= ["AnalysisResults_MC_Psi_MuMu_Incomplete.root","AnalysisResults_MC_Jpsi_Incomplete.root","AnalysisResults_MC_gammagamma"]

histo_canvas_names = ["_mcrectree_psi","_mcrectree_jpsi"] #,"_mcrectree_gammagamma","_mcgentree_gammagamma","_mcgentree_jpsi","_mcgentree_jpsi"]

#defining the canvas for the reconstructed and grenerated mc events to fit them
nmchistogram=0
mcxmin=0.0
mcxmax=6.0
mcn_bin = 80
mcbin_width = (mcxmax-mcxmin)/mcn_bin

signal_func_psi_parameters= [0,0,0,0]
signal_func_jpsi_parameters= [0,0,0,0]
tail_func_parammeters = [0,0,0,0]

while nmchistogram<len(histo_canvas_names):
    mcrecfile = TFile.Open(filenamelist[nmchistogram])
    mcrectree = mcrecfile.Get("PolarizationJP/fRecTree")
    canvasname = "canvas"+histo_canvas_names[nmchistogram]
    mccanvas = TCanvas(canvasname,"",600,300)
    histoname = "hisogram"+histo_canvas_names[nmchistogram]
    histotitle = "Massplots"+ histo_canvas_names[nmchistogram]
    mchistogram = TH1F(histoname,histotitle,mcn_bin,mcxmin,mcxmax)
    bin_width = (mcxmax-mcxmin)/mcn_bin
    mcytitle = "Number of Events/{}GeV/C #rightarrow".format(mcbin_width)

    mchistogram.SetXTitle("Invariant mass of #mu^+mu^- pair(GeV/C^2)#rightarrow")

    mchistogram.SetYTitle(mcytitle)
    mchistogram.GetYaxis().SetTitleOffset(1.4)
    mchistogram.GetYaxis().CenterTitle()
    mchistogram.GetXaxis().CenterTitle()
    mccanvas.cd()


    mcrectree.Draw("fRecPair_ParentMass>>mchistogram","","e")  #need to define the cut parameter which will be on cos theta

    mchistogram.SetDirectory(0)

    if(filenamelist[nmchistogram]=="AnalysisResults_MC_Psi_MuMu_Incomplete.root"):

        mchistogram.Fit(ft.sig_func_mc_psi,"NQR")

        int1=0
        while int1<4:
            signal_func_psi_parameters.append(ft.sig_func_mc_psi.GetParameter(int1))
            int1= int1+1

    elif (filenamelist[nmchistogram]== "AnalysisResults_MC_JPsi_MuMu_Incomplete.root"):
        mchistogram.Fit(ft.sig_func_mc_jpsi,"NQR")
        int2=0
        while int2<4:
            signal_func_jpsi_parameters.append(ft.sig_func_mc_jpsi.GetParameter(int2))
            #print signal_func_jpsi_parameters[int2]
            int2= int2+1

    elif (filenamelist[nmchistogram]== "AnalysisResults_MC_gammagamma_MuMu.root"):
        mchistogram.Fit(ft.tail_func_mc,"NQR")
        int3=0
        while int3<4:
            tail_func_parammeters.append(ft.tail_func_mc.GetParameter(int3))
            int3= int3+1

    else:
        print "there is osme error in the code with fitting mc data"

    #histogram.Fit(ft.sig_func,"NQR+")
    #ft.comb_func.SetParameters(ft.sig_func.GetParameter(0),ft.sig_func.GetParameter(1),ft.sig_func.GetParameter(2),ft.sig_func.GetParameter(3),ft.tail_func.GetParameter(0),ft.tail_func.GetParameter(1),ft.tail_func.GetParameter(6),ft.tail_func.GetParameter(3))
    #histogram.Fit(ft.comb_func,"NQR+")
    #tailclone = ft.tail_func.Clone("tailclone")
    #sigclone  = ft.sig_func.Clone("sigclone")
    #combclone = ft.comb_func.Clone("comb_func")

    #tailclone.FixParameter(0,ft.tail_func.GetParameter(0))
    #tailclone.FixParameter(1,ft.tail_func.GetParameter(1))
    #tailclone.FixParameter(2,ft.tail_func.GetParameter(2))
    #tailclone.FixParameter(3,ft.tail_func.GetParameter(3))


    #sigclone.FixParameter(0,ft.sig_func.GetParameter(0))
    #sigclone.FixParameter(1,ft.sig_func.GetParameter(1))
    #sigclone.FixParameter(2,ft.sig_func.GetParameter(2))
    #sigclone.FixParameter(3,ft.sig_func.GetParameter(3))

    #combclone.FixParameter(0,ft.comb_func.GetParameter(0))
    #combclone.FixParameter(1,ft.comb_func.GetParameter(1))
    #combclone.FixParameter(2,ft.comb_func.GetParameter(2))
    #combclone.FixParameter(3,ft.comb_func.GetParameter(3))
    #combclone.FixParameter(4,ft.comb_func.GetParameter(4))
    #combclone.FixParameter(5,ft.comb_func.GetParameter(5))
    #combclone.FixParameter(6,ft.comb_func.GetParameter(6))
    #combclone.FixParameter(7,ft.comb_func.GetParameter(7))

    #tailclone.SetLineColor(rt.kRed)
    #sigclone.SetLineColor(rt.kGreen)
    #combclone.SetLineColor(rt.kBlue)
    #tailclone.Draw("SAME")
    #sigclone.Draw("SAME")
    #combclone.Draw("SAME")







    nmchistogram= nmchistogram + 1
##########################################################################



#defining histograms to find the fit parameters for dataset





#print hist





#ytitle = "Number of Events/"+ str(bin_width) + " GeV/C #rightarrow"








Date = date.today()
date_today = filename+str(Date)+".root"
#print date_today

#list of theta bins in helicity
#helicitytheta = ["-0.6<fRecHelicityTheta&&fRecHelicityTheta<-0.520","-0.520<fRecHelicityTheta<-0.440","-0.440<fRecHelicityTheta<-0.360","-0.360<fRecHelicityTheta<-0.280","-0.280<fRecHelicityTheta<-0.200","-0.200<fRecHelicityTheta<-0.120","-0.120<fRecHelicityTheta<-0.040","-0.040<fRecHelicityTheta<0.040","0.040<fRecHelicityTheta<0.120","0.120<fRecHelicityTheta<0.200","0.200<fRecHelicityTheta<0.280","280<fRecHelicityTheta<0.360","0.360<fRecHelicityTheta<0.440","0.440<fRecHelicityTheta<0.520","0.520<fRecHelicityTheta<0.600"]


helicitytheta = ["-0.6<fRecHelicityTheta && fRecHelicityTheta<-0.520","-0.520<fRecHelicityTheta && fRecHelicityTheta<-0.440","-0.440<fRecHelicityTheta && fRecHelicityTheta<-0.360","-0.360<fRecHelicityTheta && fRecHelicityTheta<-0.280","-0.280<fRecHelicityTheta && fRecHelicityTheta<-0.200","-0.200<fRecHelicityTheta && fRecHelicityTheta<-0.120","-0.120<fRecHelicityTheta && fRecHelicityTheta<-0.040","-0.040<fRecHelicityTheta && fRecHelicityTheta<0.040","0.040<fRecHelicityTheta && fRecHelicityTheta<0.120","0.120<fRecHelicityTheta && fRecHelicityTheta<0.200","0.200<fRecHelicityTheta && fRecHelicityTheta<0.280","280<fRecHelicityTheta && fRecHelicityTheta<0.360","0.360<fRecHelicityTheta && fRecHelicityTheta<0.440","0.440<fRecHelicityTheta && fRecHelicityTheta<0.520","0.520<fRecHelicityTheta && fRecHelicityTheta<0.600"]






#list of phi bins in helicity

#helicityphi = ["-3.14<fRecHelicityPhi<-2.889","-2.889<fRecHelicityPhi<-2.638","-2.638<fRecHelicityPhi<-2.386","-2.386<fRecHelicityPhi<-2.135","-2.135<fRecHelicityPhi<-1.884","-1.884<fRecHelicityPhi<-1.633","-1.633<fRecHelicityPhi<-1.382","-1.382<fRecHelicityPhi<-1.130","-1.130<fRecHelicityPhi<-0.879","-0.879<fRecHelicityPhi<-0.628","-0.628<fRecHelicityPhi<-0.377","-0.377<fRecHelicityPhi<-0.126","-0.126<fRecHelicityPhi<0.126","0.126<fRecHelicityPhi<0.377","0.377<fRecHelicityPhi<0.628","0.628<fRecHelicityPhi<0.879","0.879<fRecHelicityPhi<1.130","1.130<fRecHelicityPhi<1.382","1.382<fRecHelicityPhi<1.633","1.633<fRecHelicityPhi<1.884","1.884<fRecHelicityPhi<2.135","2.135<fRecHelicityPhi<2.386","2.386<fRecHelicityPhi<2.638","2.638<fRecHelicityPhi<2.889","2.889<fRecHelicityPhi<3.14"]


helicityphi = ["-3.14<fRecHelicityPhi && fRecHelicityPhi<-2.889","-2.889<fRecHelicityPhi && fRecHelicityPhi<-2.638","-2.638<fRecHelicityPhi && fRecHelicityPhi<-2.386","-2.386<fRecHelicityPhi && fRecHelicityPhi<-2.135","-2.135<fRecHelicityPhi && fRecHelicityPhi<-1.884","-1.884<fRecHelicityPhi && fRecHelicityPhi<-1.633","-1.633<fRecHelicityPhi && fRecHelicityPhi<-1.382","-1.382<fRecHelicityPhi && fRecHelicityPhi<-1.130","-1.130<fRecHelicityPhi && fRecHelicityPhi<-0.879","-0.879<fRecHelicityPhi && fRecHelicityPhi<-0.628","-0.628<fRecHelicityPhi && fRecHelicityPhi<-0.377","-0.377<fRecHelicityPhi && fRecHelicityPhi<-0.126","-0.126<fRecHelicityPhi && fRecHelicityPhi<0.126","0.126<fRecHelicityPhi && fRecHelicityPhi<0.377","0.377<fRecHelicityPhi && fRecHelicityPhi<0.628","0.628<fRecHelicityPhi && fRecHelicityPhi<0.879","0.879<fRecHelicityPhi && fRecHelicityPhi<1.130","1.130<fRecHelicityPhi && fRecHelicityPhi<1.382","1.382<fRecHelicityPhi && fRecHelicityPhi<1.633","1.633<fRecHelicityPhi && fRecHelicityPhi<1.884","1.884<fRecHelicityPhi && fRecHelicityPhi<2.135","2.135<fRecHelicityPhi && fRecHelicityPhi<2.386","2.386<fRecHelicityPhi && fRecHelicityPhi<2.638","2.638<fRecHelicityPhi && fRecHelicityPhi<2.889","2.889<fRecHelicityPhi && fRecHelicityPhi<3.14"]

helicitytildephi = ["-3.14<fRecHelicityPhi && fRecHelicityPhi<-2.889","-2.889<fRecHelicityPhi && fRecHelicityPhi<-2.638","-2.638<fRecHelicityPhi && fRecHelicityPhi<-2.386","-2.386<fRecHelicityPhi && fRecHelicityPhi<-2.135","-2.135<fRecHelicityPhi && fRecHelicityPhi<-1.884","-1.884<fRecHelicityPhi && fRecHelicityPhi<-1.633","-1.633<fRecHelicityPhi && fRecHelicityPhi<-1.382","-1.382<fRecHelicityPhi && fRecHelicityPhi<-1.130","-1.130<fRecHelicityPhi && fRecHelicityPhi<-0.879","-0.879<fRecHelicityPhi && fRecHelicityPhi<-0.628","-0.628<fRecHelicityPhi && fRecHelicityPhi<-0.377","-0.377<fRecHelicityPhi && fRecHelicityPhi<-0.126","-0.126<fRecHelicityPhi && fRecHelicityPhi<0.126","0.126<fRecHelicityPhi && fRecHelicityPhi<0.377","0.377<fRecHelicityPhi && fRecHelicityPhi<0.628","0.628<fRecHelicityPhi && fRecHelicityPhi<0.879","0.879<fRecHelicityPhi && fRecHelicityPhi<1.130","1.130<fRecHelicityPhi && fRecHelicityPhi<1.382","1.382<fRecHelicityPhi && fRecHelicityPhi<1.633","1.633<fRecHelicityPhi && fRecHelicityPhi<1.884","1.884<fRecHelicityPhi && fRecHelicityPhi<2.135","2.135<fRecHelicityPhi && fRecHelicityPhi<2.386","2.386<fRecHelicityPhi && fRecHelicityPhi<2.638","2.638<fRecHelicityPhi && fRecHelicityPhi<2.889","2.889<fRecHelicityPhi && fRecHelicityPhi<3.14"]

#tildephi = [0.251]

colinsopertheta =["-0.6<fRecCollinTheta && fRecCollinTheta<-0.520","-0.520<fRecCollinTheta && fRecCollinTheta<-0.440","-0.440<fRecCollinTheta && fRecCollinTheta<-0.360","-0.360<fRecCollinTheta && fRecCollinTheta<-0.280","-0.280<fRecCollinTheta && fRecCollinTheta<-0.200","-0.200<fRecCollinTheta && fRecCollinTheta<-0.120","-0.120<fRecCollinTheta && fRecCollinTheta<-0.040","-0.040<fRecCollinTheta && fRecCollinTheta<0.040","0.040<fRecCollinTheta && fRecCollinTheta<0.120","0.120<fRecCollinTheta && fRecCollinTheta<0.200","0.200<fRecCollinTheta && fRecCollinTheta<0.280","280<fRecCollinTheta && fRecCollinTheta<0.360","0.360<fRecCollinTheta && fRecCollinTheta<0.440","0.440<fRecCollinTheta && fRecCollinTheta<0.520","0.520<fRecCollinTheta && fRecCollinTheta<0.600"]




colinsoperphi =["-3.14<fRecCollinPhi && fRecCollinPhi<-2.889","-2.889<fRecCollinPhi && fRecCollinPhi<-2.638","-2.638<fRecCollinPhi && fRecCollinPhi<-2.386","-2.386<fRecCollinPhi && fRecCollinPhi<-2.135","-2.135<fRecCollinPhi && fRecCollinPhi<-1.884","-1.884<fRecCollinPhi && fRecCollinPhi<-1.633","-1.633<fRecCollinPhi && fRecCollinPhi<-1.382","-1.382<fRecCollinPhi && fRecCollinPhi<-1.130","-1.130<fRecCollinPhi && fRecCollinPhi<-0.879","-0.879<fRecCollinPhi && fRecCollinPhi<-0.628","-0.628<fRecCollinPhi && fRecCollinPhi<-0.377","-0.377<fRecCollinPhi && fRecCollinPhi<-0.126","-0.126<fRecCollinPhi && fRecCollinPhi<0.126","0.126<fRecCollinPhi && fRecCollinPhi<0.377","0.377<fRecCollinPhi && fRecCollinPhi<0.628","0.628<fRecCollinPhi && fRecCollinPhi<0.879","0.879<fRecCollinPhi && fRecCollinPhi<1.130","1.130<fRecCollinPhi && fRecCollinPhi<1.382","1.382<fRecCollinPhi && fRecCollinPhi<1.633","1.633<fRecCollinPhi && fRecCollinPhi<1.884","1.884<fRecCollinPhi && fRecCollinPhi<2.135","2.135<fRecCollinPhi && fRecCollinPhi<2.386","2.386<fRecCollinPhi && fRecCollinPhi<2.638","2.638<fRecCollinPhi && fRecCollinPhi<2.889","2.889<fRecCollinPhi && fRecCollinPhi<3.14"]




colinsopertildephi =["-3.14<fRecCollinPhi && fRecCollinPhi<-2.889","-2.889<fRecCollinPhi && fRecCollinPhi<-2.638","-2.638<fRecCollinPhi && fRecCollinPhi<-2.386","-2.386<fRecCollinPhi && fRecCollinPhi<-2.135","-2.135<fRecCollinPhi && fRecCollinPhi<-1.884","-1.884<fRecCollinPhi && fRecCollinPhi<-1.633","-1.633<fRecCollinPhi && fRecCollinPhi<-1.382","-1.382<fRecCollinPhi && fRecCollinPhi<-1.130","-1.130<fRecCollinPhi && fRecCollinPhi<-0.879","-0.879<fRecCollinPhi && fRecCollinPhi<-0.628","-0.628<fRecCollinPhi && fRecCollinPhi<-0.377","-0.377<fRecCollinPhi && fRecCollinPhi<-0.126","-0.126<fRecCollinPhi && fRecCollinPhi<0.126","0.126<fRecCollinPhi && fRecCollinPhi<0.377","0.377<fRecCollinPhi && fRecCollinPhi<0.628","0.628<fRecCollinPhi && fRecCollinPhi<0.879","0.879<fRecCollinPhi && fRecCollinPhi<1.130","1.130<fRecCollinPhi && fRecCollinPhi<1.382","1.382<fRecCollinPhi && fRecCollinPhi<1.633","1.633<fRecCollinPhi && fRecCollinPhi<1.884","1.884<fRecCollinPhi && fRecCollinPhi<2.135","2.135<fRecCollinPhi && fRecCollinPhi<2.386","2.386<fRecCollinPhi && fRecCollinPhi<2.638","2.638<fRecCollinPhi && fRecCollinPhi<2.889","2.889<fRecCollinPhi && fRecCollinPhi<3.14"]










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
    histograms = TString()
  #  hist = hist_name + "_"+ str(i)
    histograms = "{}_{}".format(hist_name,i)
    #print i
    #print hist

   # i=i+1
    canvas = TCanvas(histograms,"Canvas of Mass",600,300)
    histogram = TH1F(histograms,"Mass Plots",n_bin,xmin,xmax)
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


    #tail_func.FixParameter(1,tail_func_parammeters[1])
    #tail_func.FixParameter(2,tail_func_parammeters[2])
    #tail_func.FixParameter(3,tail_func_parammeters[3])
    #par 3 = jpsi n  and par 9 = psin
    #par
    #sig_func.FixParameter()

    #histogram.Fit(ft.tail_func,"NQR")
    #histogram.Fit(ft.sig_func,"NQR+")
    #ft.comb_func.SetParameters(ft.sig_func.GetParameter(0),ft.sig_func.GetParameter(1),ft.sig_func.GetParameter(2),ft.sig_func.GetParameter(3),ft.tail_func.GetParameter(0),ft.tail_func.GetParameter(1),ft.tail_func.GetParameter(6),ft.tail_func.GetParameter(3))
    # for comb function n1 = par3 +n2 = par9 a1 = par 2 a2 = par 10
                                    # for sig func par n = par3 a = par 2
                                    #tail = and sig par5--->1 par6--->2 par7----3

    #signal_func_psi_parameters= []
    #signal_func_jpsi_parameters= []
    #tail_func_parammeters = []
    ft.comb_func.FixParameter(3,signal_func_psi_parameters[3])
    ft.comb_func.FixParameter(2,signal_func_psi_parameters[2])
    ft.comb_func.FixParameter(9,signal_func_jpsi_parameters[3])
    ft.comb_func.FixParameter(10,signal_func_jpsi_parameters[2])
    ft.comb_func.FixParameter(5,tail_func_parammeters[1])
    ft.comb_func.FixParameter(6,tail_func_parammeters[2])
    ft.comb_func.FixParameter(7,tail_func_parammeters[3])



    histogram.Fit(ft.tail_func,"NQ")
    tailclone = ft.tail_func.Clone("tailclone")
    sigclone_psi  = ft.sig_func.Clone("sigclone_psi")
    sigclone_jpsi  = ft.sig_func.Clone("sigclone_jpsi")



    combclone = ft.comb_func.Clone("combclone")



    tailclone.FixParameter(0,tail_func_parammeters[0])
    tailclone.FixParameter(1,tail_func_parammeters[1])
    tailclone.FixParameter(2,tail_func_parammeters[2])
    tailclone.FixParameter(3,tail_func_parammeters[3])


    sigclone_psi.FixParameter(0,ft.comb_func.GetParameter(0))
    sigclone_psi.FixParameter(1,ft.sig_func.GetParameter(1))
    sigclone_psi.FixParameter(2,ft.sig_func.GetParameter(2))
    sigclone_psi.FixParameter(3,ft.sig_func.GetParameter(3))

    combclone.FixParameter(0,ft.comb_func.GetParameter(0))
    combclone.FixParameter(1,ft.comb_func.GetParameter(1))
    combclone.FixParameter(2,ft.comb_func.GetParameter(2))
    combclone.FixParameter(3,ft.comb_func.GetParameter(3))
    combclone.FixParameter(4,ft.comb_func.GetParameter(4))
    combclone.FixParameter(5,ft.comb_func.GetParameter(5))
    combclone.FixParameter(6,ft.comb_func.GetParameter(6))
    combclone.FixParameter(7,ft.comb_func.GetParameter(7))

    tailclone.SetLineColor(rt.kRed)
    sigclone_psi.SetLineColor(rt.kGreen)
    combclone.SetLineColor(rt.kBlue)
    tailclone.Draw("SAME")
    sigclone_psi.Draw("SAME")
    combclone.Draw("SAME")










    legend.SetHeader("UPC Run2 Dataset","C") # option "C" allows to center the header
    legend.AddEntry(0,cut[i],"")
    legend.AddEntry(0,"#N_{j/\Psi}","")
    legend.AddEntry(0,"#N_{\Psi(2s)}=","")
    legend.AddEntry(0,"#N_{\gamma \gamma}=","")
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
