// to run:
//   alien-token-init
//   source /tmp/gclient_env_501
//   aliroot runAnalysis.C\(opt\)

//#include <iostream>
// include the header of your analysis task here! for classes already compiled by aliBuild,
// precompiled header files (with extension pcm) are available, so that you do not need to
// specify includes for those. for your own task however, you (probably) have not generated a
// pcm file, so we need to include it explicitly
#include "AliAnalysisTaskUPCforwardMC.h"
//#include "global.C"
//void runAnalysis(Int_t year_data, std::string ana_type )
void runAnalysis()



// year_data = 2015; 2018 q
// year_data = 201511; 2015 mc
// year_data = 20181; 2018 q
// year_data = 201811; 2018 q mc


// year_data = 20182; 2018r
// year_data = 201821; 2018r mc

/*
ana_type = "local" for local
ana_type = "grid" for grid
ana_type = "grid_test" for test in grid
ana_type = "grid_merge" to merge in grid
ana_type = "grid_download" to download data

*/

{
//std::string ana_type = "local";
//  cout<< ana_type << endl;


//int opt =1 ;
    // set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
    // Bool_t local = kFALSE;
    // Bool_t local = kTRUE;
    // if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
    // Bool_t gridTest = kFALSE;
    // Bool_t gridTest = kTRUE;

    /**
     * RUN ON LOCAL:
     */
    // Bool_t local    = kTRUE;
    // Bool_t gridTest = kFALSE;

    /**
     * RUN ON GRIDTEST:
     */
    // Bool_t local    = kFALSE;
    // Bool_t gridTest = kTRUE;


    /**
     * FULL GRID MOD:
     */


//test();

Int_t year_data;

std::string  ana_type;
std::string  channel;


cout<<"input the type of analysis you want to perform"<<endl;
cout<<"local ---->if you want to run it locally \n grid_test ---> if you want to run it on grid \n grid -->if you want to run full analysis \n grid_merge---> To merge the analysis in Grid \n grid_download ---> to download the final analysis"<<endl;

cin>> ana_type;


if(ana_type.compare("grid")==0|| ana_type.compare("grid_test")==0|| ana_type.compare("grid_merge")==0|| ana_type.compare("grid_download")==0){

  cout<< "input the year/data you want to run"<< endl;
  cout <<"2015       for  2015   data" <<endl;

  cout <<"201511     for  2015   montecarlo data " <<endl;

  cout <<"20181      for  2018q  data "<<endl;

  cout <<"20182      for  2018r  data "<<endl;

  cout <<"201811     for  2018q  montecarlo data "<<endl;

  cout <<"201811     for  2018q  montecarlo data "<<endl;

  cout <<"201821     for  2018r  montecarlo data "<<endl;

  cin>> year_data;

  }


Bool_t download = kFALSE;
Bool_t merge    = kFALSE;
Bool_t local;
Bool_t gridTest;

// str1.compare(str2) != 0)
 if(ana_type.compare("local")==0){
   cout<< "running the analysis locally"<<endl;
    local    = kTRUE;
    gridTest = kTRUE;

 }
  else if(ana_type.compare("grid_test")==0){
    local    = kFALSE;
    gridTest = kTRUE;


 }

 else if(ana_type.compare("grid")==0){
 //if(ana_type == "grid"){
    local    = kFALSE;
    gridTest = kFALSE;


 }
 else if(ana_type.compare("grid_merge")==0){
// if(ana_type == "grid_merge"){
    local    = kFALSE;
    gridTest = kFALSE;
   merge = kTRUE;




 }

 else if(ana_type.compare("grid_download")==0){
// if(ana_type == "grid_download"){
    local    = kFALSE;
    gridTest = kFALSE;
   download = kTRUE;
   merge = kTRUE;

 }
 else{
 cout<<"criteria is not defined "<<endl;
 cout<<"running it locally"<<endl;
    local    = kTRUE;
    gridTest = kTRUE;
 }

    // since we will compile a class, tell root where to look for headers
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->ProcessLine(".include $ROOTSYS/include");
    gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
#else
    gROOT->ProcessLine(".include $ROOTSYS/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
#endif

    // create the analysis manager
    AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskExample");
    AliAODInputHandler *aodH = new AliAODInputHandler();
    mgr->SetInputEventHandler(aodH);

    // compile the class and load the add task macro
    // here we have to differentiate between using the just-in-time compiler
    // from root6, or the interpreter of root5
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->LoadMacro("AliAnalysisTaskUPCforwardMC.cxx++g");
    AliAnalysisTaskUPCforwardMC *task = reinterpret_cast<AliAnalysisTaskUPCforwardMC*>(gInterpreter->ExecuteMacro("AddTaskUPCforwardMC.C"));
#else
    gROOT->LoadMacro("AliAnalysisTaskUPCforwardMC.cxx+++g");
    gROOT->LoadMacro("AddTaskUPCforwardMC.C");
    AliAnalysisTaskUPCforwardMC *task = AddTaskUPCforwardMC();
#endif


    if(!mgr->InitAnalysis()) return;
     mgr->SetDebugLevel(1);
     mgr->PrintStatus();
     mgr->SetUseProgressBar(1, 25);



    if(local) {
    cout<< "acutally running it on grid"<< endl;

        // if you want to run locally, we need to define some input
        /* TChain* chain = new TChain("aodTree");
        // add a few files to the chain (change this so that your local files are added)
          // chain->Add("/home/amrit/Analysis/TestCode/AliAOD_100JP.root");

        // FILE *f = fopen("list2015Full.txt","r");
        FILE *f = fopen("list.txt","r");
        // FILE *f = fopen("listLHC18qrAndLHC15o.txt","r");
        // FILE *f = fopen("listPROVA.txt","r");
        char fileadd[300];
        Int_t flaggingValue = 0;
        while(fscanf(f,"%s",fileadd)==1){
            // chain->AddFile(fileadd);
            flaggingValue = chain->Add(fileadd);
            if(flaggingValue == 0) std::cout << fileadd << std::endl;
            flaggingValue = 0;*/


        TChain* chain = new TChain("aodTree");
        // add a few files to the chain (change this so that your local files are added)
       // chain->Add("/home/amrit/Analysis/TestCode/Histogram/AliAOD.root");
        chain->Add("/home/amrit/Analysis/TestCode/AliAOD_100JP.root");
	// start the analysis locally, reading the events from the tchain
       // mgr->StartAnalysis("local", chain);

      //  }
        // start the analysis locally, reading the events from the tchain
        mgr->StartAnalysis("local", chain);
    } else {
        cout<<"running it on grid"<< endl;
        // if we want to run on grid, we create and configure the plugin
        AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
        // also specify the include (header) paths on grid
        alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
        // make sure your source files get copied to grid
        alienHandler->SetAdditionalLibs("AliAnalysisTaskUPCforwardMC.cxx AliAnalysisTaskUPCforwardMC.h");
        alienHandler->SetAnalysisSource("AliAnalysisTaskUPCforwardMC.cxx");
        // select the aliphysics version. all other packages
        // are LOADED AUTOMATICALLY!
        alienHandler->SetAliPhysicsVersion("vAN-20181028_ROOT6-1");
        // set the Alien API version
        alienHandler->SetAPIVersion("V1.1x");



        // select the input data for 2018 q
      	if (year_data == 20181) {
      	  alienHandler->SetGridDataDir("/alice/data/2018/LHC18q");
          // alienHandler->SetGridDataDir("/alice/data/2018/LHC18q/muon_calo_pass3/AOD225/PWGUD/UD_PbPb_AOD/501_20190723-1440/015");
      	  alienHandler->SetDataPattern("*muon_calo_pass3/AOD225/PWGUD/UD_PbPb_AOD/501_20190723-1440/*AliAOD.UPCNano.root");
	  //  alienHandler->SetDataPattern("*AliAOD.UPCNano.root");
	//alienHandler->SetDataPattern("*muon_calo_pass3/AOD225/PWGUD/UD_PbPb_AOD/501_20190723-1440/068/AliAOD.UPCNano.root");
        // alienHandler->SetDataPattern("*muon_calo_pass3/AOD225/PWGUD/UD_PbPb_AOD/501_20190723-1440/0015/AliAOD.UPCNano.root");

      	  // MC has no prefix, data has prefix 000
      	  alienHandler->SetRunPrefix("000");
      	  // runnumber
      	  alienHandler->AddRunNumber(296510);
          // for( Int_t iRunLHC18q = 0; iRunLHC18q < 128; iRunLHC18q++){
          //   alienHandler->AddRunNumber( listOfGoodRunNumbersLHC18q[iRunLHC18q] );
          // }

      	 } else if (year_data==20182) {
      	  alienHandler->SetGridDataDir("/alice/data/2018/LHC18r");
      	  alienHandler->SetDataPattern("*muon_calo_pass3/AOD225/PWGUD/UD_PbPb_AOD/502_20190723-1441/*AliAOD.UPCNano.root");
      	  // MC has no prefix, data has prefix 000
      	  alienHandler->SetRunPrefix("000");
      	  // runnumber
      	  alienHandler->AddRunNumber(297481);
          // for( Int_t iRunLHC18r = 0; iRunLHC18r <  97; iRunLHC18r++){
          //   alienHandler->AddRunNumber( listOfGoodRunNumbersLHC18r[iRunLHC18r] );
          // }

        } else if (year_data==2015) {
      	  alienHandler->SetGridDataDir("/alice/data/2015/LHC15o");
      	  alienHandler->SetDataPattern("*muon_calo_pass1/AOD229/PWGUD/UD_PbPb_AOD/522_20190828-1630/*AliAOD.UPCNano.root");
	  // MC has no prefix, data has prefix 000
      	  alienHandler->SetRunPrefix("000");
      	  // runnumber  /alice/data/2015/LHC15o/000246087/muon_calo_pass1/AOD229/PWGUD/UD_PbPb_AOD/522_20190828-1630
      	  alienHandler->AddRunNumber(246087);
          // for( Int_t iRunLHC18r = 0; iRunLHC18r <  97; iRunLHC18r++){
          //   alienHandler->AddRunNumber( listOfGoodRunNumbersLHC18r[iRunLHC18r] );
          // }

         }else if (year_data==201511) {

         //which channel
         //lhc16b2a or b  is for the jpsi to muons
         //lhc16b2c is for psi2s to muons  the channel can be found in the sim.log file inside the run number folder in grid dir location

      	  //alienHandler->SetGridDataDir("/alice/sim/2015/LHC15o");

          cout<<"enter the mc channel you need"<<endl;
             cout<<"psi for CohPsi2sToMuPi /n jpsi for CohJpsiToMu /n gamma for gammagammatoMu"<<endl;
             cin>>channel;

             if(channel.compare("psi")==0){
             //this is for coherent jpsi to mumu LHC16b2b is for incoherent
      	      alienHandler->SetGridDataDir("/alice/sim/2016/LHC16b2c");

      	      }
             else if(channel.compare("jpsi")==0){
               alienHandler->SetGridDataDir("/alice/sim/2016/LHC16b2a");
              }
             else if(channel.compare("gamma")==0){
                 alienHandler->SetGridDataDir("/alice/sim/2016/LHC16b2g");

               }
             else{ cout<<"you need to add new channel"<<endl; return;  }

          //alice/sim/2018/LHC18l7/kCohPsi2sToMuPi/296849
            //alienHandler->SetDataPattern("*AliAOD.root");
      	  // MC has no prefix, data has prefix 000
      	   //alienHandler->SetRunPrefix("");



         ///alice/sim/2018/LHC18l7/kCohPsi2sToMuPi/296849
          alienHandler->SetDataPattern("*AliAOD.root");
      	  // MC has no prefix, data has prefix 000
      	  alienHandler->SetRunPrefix("");
      	  // runnumber  /alice/data/2015/LHC15o/000246087/muon_calo_pass1/AOD229/PWGUD/UD_PbPb_AOD/522_20190828-1630

          alienHandler->AddRunNumber("244980 244982 244983 245064 245066 245068 245145 245146 245151 245152 245231 245232 245233 245253 245259 245343 245345 245346 245347 245353 245401 245407 245409 245410 245446 245450 245496 245501 245504 245505 245507 245535 245540 245542 245543 245554 245683 245692 245700 245705 245729 245731 245738 245752 245759 245766 245775 245785 245793 245829 245831 245833 245949 245952 245954 245963 245996 246001 246003 246012 246036 246037 246042 246048 246049 246053 246087 246089 246113 246115 246148 246151 246152 246153 246178 246181 246182 246217 246220 246222 246225 246272 246275 246276 246390 246391 246392 246424 246428 246431 246433 246434 246487 246488 246493 246495 246675 246676 246750 246751 246755 246757 246758 246759 246760 246763 246765 246804 246805 246806 246807 246808 246809 246844 246845 246846 246847 246851 246855 246859 246864 246865 246867 246871 246930 246937 246942 246945 246948 246949 246980 246982 246984 246989 246991 246994");
          // for( Int_t iRunLHC18r = 0; iRunLHC18r <  97; iRunLHC18r++){
          //   alienHandler->AddRunNumber( listOfGoodRunNumbersLHC18r[iRunLHC18r] );
          // }

          }else if (year_data==201811||year_data==201821) {
              alienHandler->SetDataPattern("*AliAOD.root");
    	        // MC has no prefix, data has prefix 000
      	      alienHandler->SetRunPrefix("");

             cout<<"enter the mc channel you need"<<endl;
             cout<<"psi for CohPsi2sToMuPi /n jpsi for CohJpsiToMu /n gamma for gammagammatoMu "<<endl;
             cin>>channel;

             if(channel.compare("psi")==0){
      	      alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kCohPsi2sToMu");
      	      }
             else if(channel.compare("jpsi")==0){
               alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kCohJpsiToMu");
               }
            else if (channel.compare("gamma")==0){
              alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kTwoGammaToMuMedium");
              }
             else {cout<<"you need to add new channel"<<endl; return;  }

          //alice/sim/2018/LHC18l7/kCohPsi2sToMuPi/296849



              if(year_data==201811){
              // alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kCohJpsiToMu");
              // alienHandler->SetDataPattern("*AliAOD.root");
              //  alienHandler->SetRunPrefix("");
              alienHandler->AddRunNumber("295585 295586 295587 295588 295589 295612 295615 295665 295666 295667 295668 295671 295673 295675 295676 295677 295714 295716 295717 295718 295719 295723 295725 295753 295754 295755 295758 295759 295762 295763 295786 295788 295791 295816 295818 295819 295822 295825 295826 295829 295831 295854 295855 295856 295859 295860 295861 295863 295881 295908 295909 295910 295913 295936 295937 295941 295942 295943 295945 295947 296061 296062 296063 296065 296066 296068 296123 296128 296132 296133 296134 296135 296142 296143 296191 296192 296194 296195 296196 296197 296198 296241 296242 296243 296244 296246 296247 296269 296270 296273 296279 296280 296303 296304 296307 296309 296312 296377 296378 296379 296380 296381 296383 296414 296419 296420 296423 296424 296433 296472 296509 296510 296511 296514 296516 296547 296548 296549 296550 296551 296552 296553 296615 296616 296618 296619 296622 296623");
                                               }

            else if(year_data==201821){
            //  alienHandler->SetGridDataDir(""/alice/sim/2018/LHC18l7/kCohJpsiToMu"");
             //  alienHandler->SetDataPattern("*AliAOD.root");
              //  alienHandler->SetRunPrefix("");

              alienHandler->AddRunNumber("296690 296691 296694 296749 296750 296781 296784 296785 296786 296787 296791 296793 296794 296799 296836 296838 296839 296848 296849 296850 296851 296852 296890 296894 296899 296900 296903 296930 296931 296932 296934 296935 296938 296941 296966 296967 296968 296969 296971 296975 296976 296979 297029 297031 297035 297085 297117 297118 297119 297123 297124 297128 297129 297132 297133 297193 297194 297196 297218 297219 297221 297222 297278 297310 297312 297315 297317 297363 297366 297367 297372 297379 297380 297405 297408 297413 297414 297415 297441 297442 297446 297450 297451 297452 297479 297481 297483 297512 297537 297540 297541 297542 297544 297558 297588 297590 297595");
                                               }

             else cout << "define new montecarlo data year"<<endl;



      	  // runnumber  /alice/data/2015/LHC15o/000246087/muon_calo_pass1/AOD229/PWGUD/UD_PbPb_AOD/522_20190828-1630

          // for( Int_t iRunLHC18r = 0; iRunLHC18r <  97; iRunLHC18r++){
          //   alienHandler->AddRunNumber( listOfGoodRunNumbersLHC18r[iRunLHC18r] );
          // }





        } else {
      	  cout << " not a valid option ... bye!" << endl;
          return;
      	 }
        // number of files per subjob
        alienHandler->SetSplitMaxInputFileNumber(40);
        alienHandler->SetExecutable("AD_XNXN.sh");
        // specify how many seconds your job may take
        alienHandler->SetTTL(10000);
        alienHandler->SetJDLName("AD_XNXN.jdl");

        alienHandler->SetOutputToRunNo(kTRUE);
        alienHandler->SetKeepLogs(kTRUE);
        // merging: run with "kTRUE" and "full" for normal run
        // to merge on grid run jobs in SetRunMode("terminate")
        // to collect final results set SetMergeViaJDL(kFALSE)


        if (download){
          alienHandler->SetMergeViaJDL(kFALSE);

          }
        else{
          alienHandler->SetMergeViaJDL(kTRUE);
          }
        /* - The setting to kFALSE is to download the output files
           -
         */

        alienHandler->SetMaxMergeStages(1);


        //TString LHC18q("LHC18q_histo");
        //TString LHC18q("LHC18q_histo");
        TString LHC18r("LHC18r_simone_code");
        TString LHC18q("LHC18q_simone_code");
       // TString LHC18q("LHC18q_compare");
        TString LHC15("LHC15_simone_code");
        TString LHC18qMCJP("LHC18qMCJP_histo");
        TString LHC18rMCJP("LHC18rMCJP_histo");
        TString LHC18qMCPsi2s("LHC18qMCPsi2s_histo");
        TString LHC18rMCPsi2s("LHC18rMCPsi2s_2_histo");
        //these are for gamma gamma high uncomment them and comment out other option to download gammga gamma high , I will add other channel in interactive option later so this might not be needed
        //TString LHC18qMCgamma("LHC18qMCgamma_histo");
        //TString LHC18rMCgamma("LHC18rMCgamma_histo");
        TString LHC18qMCgamma("LHC18qMCgamma_medium_histo");
        TString LHC18rMCgamma("LHC18rMCgamma_medium_histo");

        TString LHC16b2MCJp("LHC16b2MCJp_2_histo");
        TString LHC16b2MCPsi2s("LHC16b2MCPsi2s_2_histo");
        //TString LHC16b2gamma("LHC16b2MCgammagamma_histo");
        TString LHC16b2gamma("LHC16b2MC_histo");






        // define the output folders
        // alienHandler->SetGridWorkingDir("myWorkingDir");
        // alienHandler->SetGridWorkingDir("CheckAD_null");
        // alienHandler->SetGridWorkingDir("AD_HWandSW");
       // alienHandler->SetGridWorkingDir("PbPb18r_CoherentCheck_2");
        // alienHandler->SetGridOutputDir("myOutputDir");
        if (year_data == 20181){
          alienHandler->SetGridWorkingDir(LHC18q.Data());
          alienHandler->SetGridOutputDir(LHC18q.Data());


        }else if (year_data == 20182) {
          alienHandler->SetGridWorkingDir(LHC18r.Data());
          alienHandler->SetGridOutputDir(LHC18r.Data());



        }else if (year_data == 2015) {
          alienHandler->SetGridWorkingDir(LHC15.Data());
          alienHandler->SetGridOutputDir(LHC15.Data());

        }else if (year_data == 201511 && channel.compare("jpsi")==0){
           alienHandler->SetGridWorkingDir(LHC16b2MCJp.Data());
           alienHandler->SetGridOutputDir(LHC16b2MCJp.Data());

        }else if (year_data == 201511 && channel.compare("gamma")==0){
          alienHandler->SetGridWorkingDir(LHC16b2gamma.Data());
          alienHandler->SetGridOutputDir(LHC16b2gamma.Data());




        }else if (year_data == 201511 && channel.compare("psi")==0){
           alienHandler->SetGridWorkingDir(LHC16b2MCPsi2s.Data());
           alienHandler->SetGridOutputDir(LHC16b2MCPsi2s.Data());

        }else if (year_data == 201811 && channel.compare("jpsi")==0){
           alienHandler->SetGridWorkingDir(LHC18qMCJP.Data());
           alienHandler->SetGridOutputDir(LHC18qMCJP.Data());



        }else if (year_data == 201811 && channel.compare("psi")==0){
           alienHandler->SetGridWorkingDir(LHC18qMCPsi2s.Data());
           alienHandler->SetGridOutputDir(LHC18qMCPsi2s.Data());

        }else if (year_data == 201811 && channel.compare("gamma")==0){
            alienHandler->SetGridWorkingDir(LHC18qMCgamma.Data());
            alienHandler->SetGridOutputDir(LHC18qMCgamma.Data());

        }else if (year_data == 201821 && channel.compare("gamma")==0){
            alienHandler->SetGridWorkingDir(LHC18rMCgamma.Data());
            alienHandler->SetGridOutputDir(LHC18rMCgamma.Data());



        }else if (year_data == 201821 && channel.compare("jpsi")==0){
           alienHandler->SetGridWorkingDir(LHC18rMCJP.Data());
           alienHandler->SetGridOutputDir(LHC18rMCJP.Data());

        }else if (year_data == 201821 && channel.compare("jpsi")==0){
           alienHandler->SetGridWorkingDir(LHC18rMCPsi2s.Data());
           alienHandler->SetGridOutputDir(LHC18rMCPsi2s.Data());




        } else {
          alienHandler->SetGridWorkingDir("nodirset");
          alienHandler->SetGridOutputDir("nodirset");

        }

        // connect the alien plugin to the manager
        mgr->SetGridHandler(alienHandler);
        if(gridTest) {
            // speficy on how many files you want to run
            alienHandler->SetNtestFiles(1);
            // and launch the analysis
            alienHandler->SetRunMode("test");
            mgr->StartAnalysis("grid");
        } else {
            // else launch the full grid analysis

            /* - The option FULL is to send the full analysis.
               -
             */

              if  (merge) {
                alienHandler->SetRunMode("terminate");
               }
              else{
                 alienHandler->SetRunMode("full");
              }

            /* - This option TERMINATE is used for the merging of the files.
               -
             */

            mgr->StartAnalysis("grid");
        }
    }
}

/*
Welcome my dear ALICE user! To use ALICE software from CVMFS:
 * List all packages         --> alienv q
 * List AliPhysics packages  --> alienv q | grep -i aliphysics
 * Enable a specific package --> alienv enter VO_ALICE@AliPhysics::vAN-20190114_ROOT6-1
 * Enable multiple packages  --> alienv enter VO_ALICE@AliPhysics::vAN-20190114_ROOT6-1,VO_ALICE@fastjet::v3.2.1_1.024-alice3-7
 */
