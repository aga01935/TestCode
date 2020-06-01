// to run:
//   alien-token-init
//   source /tmp/gclient_env_501
//   aliroot runAnalysis.C\(opt\)


// include the header of your analysis task here! for classes already compiled by aliBuild,
// precompiled header files (with extension pcm) are available, so that you do not need to
// specify includes for those. for your own task however, you (probably) have not generated a
// pcm file, so we need to include it explicitly
#include "AliAnalysisTaskPolarizationTestJP.h"

void runAnalysis()
// opt = 0; 2018 q
// opt = 1; 2018 r
{
  
int opt =1 ;
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
    Bool_t local    = kTRUE;
    Bool_t gridTest = kFALSE;


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
    gInterpreter->LoadMacro("AliAnalysisTaskPolarizationTestJP.cxx++g");
    AliAnalysisTaskPolarizationTestJP *task = reinterpret_cast<AliAnalysisTaskPolarizationTestJP*>(gInterpreter->ExecuteMacro("AddPolarizationJP.C"));
#else
    gROOT->LoadMacro("AliAnalysisTaskPolarizationTestJP.cxx++g");
    gROOT->LoadMacro("AddPolarizationJP.C");
    AliAnalysisTaskPolarizationTestJP *task = AddPolarizationJP();
#endif


    if(!mgr->InitAnalysis()) return;
     mgr->SetDebugLevel(2);
     mgr->PrintStatus();
     mgr->SetUseProgressBar(1, 25);
    
    

    if(local) {
        // if you want to run locally, we need to define some input
      /*  TChain* chain = new TChain("aodTree");
        // add a few files to the chain (change this so that your local files are added)

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
        chain->Add("/afs/cern.ch/user/a/agautam/Test/AliAOD_100JP.root");
        // start the analysis locally, reading the events from the tchain
       // mgr->StartAnalysis("local", chain);
        
      //  }
        // start the analysis locally, reading the events from the tchain
        mgr->StartAnalysis("local", chain);
    } else {
        // if we want to run on grid, we create and configure the plugin
        AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
        // also specify the include (header) paths on grid
        alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
        // make sure your source files get copied to grid
        alienHandler->SetAdditionalLibs("AliAnalysisTaskPolarizationTestJP.cxx AliAnalysisTaskPolarizationTestJP.h");
        alienHandler->SetAnalysisSource("AliAnalysisTaskPolarizationTestJP.cxx");
        // select the aliphysics version. all other packages
        // are LOADED AUTOMATICALLY!
        alienHandler->SetAliPhysicsVersion("vAN-20181028_ROOT6-1");
        // set the Alien API version
        alienHandler->SetAPIVersion("V1.1x");


        Int_t listOfGoodRunNumbersLHC18q[] = { 295585, 295586, 295587, 295588, 295589, 295612,
                                               295615, 295665, 295666, 295667, 295668, 295671,
                                               295673, 295675, 295676, 295677, 295714, 295716,
                                               295717, 295718, 295719, 295723, 295725, 295753,
                                               295754, 295755, 295758, 295759, 295762, 295763,
                                               295786, 295788, 295791, 295816, 295818, 295819,
                                               295822, 295825, 295826, 295829, 295831, 295854,
                                               295855, 295856, 295859, 295860, 295861, 295863,
                                               295881, 295908, 295909, 295910, 295913, 295936,
                                               295937, 295941, 295942, 295943, 295945, 295947,
                                               296061, 296062, 296063, 296065, 296066, 296068,
                                               296123, 296128, 296132, 296133, 296134, 296135,
                                               296142, 296143, 296191, 296192, 296194, 296195,
                                               296196, 296197, 296198, 296241, 296242, 296243,
                                               296244, 296246, 296247, 296269, 296270, 296273,
                                               296279, 296280, 296303, 296304, 296307, 296309,
                                               296312, /*296376,*/ 296377, 296378, 296379, 296380,
                                               296381, 296383, 296414, 296419, 296420, 296423,
                                               296424, 296433, 296472, 296509, 296510, 296511,
                                               296514, 296516, 296547, 296548, 296549, 296550,
                                               296551, 296552, 296553, 296615, 296616, 296618,
                                               296619, 296622, 296623 };
        Int_t listOfGoodRunNumbersLHC18r[] = { 296690, 296691, 296694, 296749, 296750, 296781,
                                               296784, 296785, 296786, 296787, 296791, 296793,
                                               296794, 296799, 296836, 296838, 296839, 296848,
                                               296849, 296850, 296851, 296852, 296890, 296894,
                                               296899, 296900, 296903, 296930, 296931, 296932,
                                               296934, 296935, 296938, 296941, 296966, 296967,
                                               296968, 296969, 296971, 296975, 296976, /*296977,*/
                                               296979, 297029, 297031, 297035, 297085, 297117,
                                               297118, 297119, 297123, 297124, 297128, 297129,
                                               297132, 297133, 297193, 297194, 297196, 297218,
                                               297219, 297221, 297222, 297278, 297310, 297312,
                                               297315, 297317, 297363, 297366, 297367, 297372,
                                               297379, 297380, 297405, 297408, 297413, 297414,
                                               297415, 297441, 297442, 297446, 297450, 297451,
                                               297452, 297479, 297481, 297483, 297512, 297537,
                                               297540, 297541, 297542, 297544, 297558, 297588,
                                               297590, 297595/*, 297623, 297624*/ };


        // select the input data for 2018 q
      	if (opt == 0) {
      	  alienHandler->SetGridDataDir("/alice/data/2018/LHC18q");
      	  alienHandler->SetDataPattern("*muon_calo_pass3/AOD225/PWGUD/UD_PbPb_AOD/501_20190723-1440/*AliAOD.UPCNano.root");
      	  // MC has no prefix, data has prefix 000
      	  alienHandler->SetRunPrefix("000");
      	  // runnumber
      	  alienHandler->AddRunNumber(296510);
          // for( Int_t iRunLHC18q = 0; iRunLHC18q < 128; iRunLHC18q++){
          //   alienHandler->AddRunNumber( listOfGoodRunNumbersLHC18q[iRunLHC18q] );
          // }

      	} else if (opt == 1) {
      	  alienHandler->SetGridDataDir("/alice/data/2018/LHC18r");
      	  alienHandler->SetDataPattern("*muon_calo_pass3/AOD225/PWGUD/UD_PbPb_AOD/502_20190723-1441/*AliAOD.UPCNano.root");
      	  // MC has no prefix, data has prefix 000
      	  alienHandler->SetRunPrefix("000");
      	  // runnumber
      	  alienHandler->AddRunNumber(297481);
          // for( Int_t iRunLHC18r = 0; iRunLHC18r <  97; iRunLHC18r++){
          //   alienHandler->AddRunNumber( listOfGoodRunNumbersLHC18r[iRunLHC18r] );
          // }

      	} else {
      	  cout << " not a valid option ... bye!" << endl;
      	}
        // number of files per subjob
        alienHandler->SetSplitMaxInputFileNumber(20);
        alienHandler->SetExecutable("AD_XNXN.sh");
        // specify how many seconds your job may take
        alienHandler->SetTTL(10000);
        alienHandler->SetJDLName("AD_XNXN.jdl");

        alienHandler->SetOutputToRunNo(kTRUE);
        alienHandler->SetKeepLogs(kTRUE);
        // merging: run with "kTRUE" and "full" for normal run
        // to merge on grid run jobs in SetRunMode("terminate")
        // to collect final results set SetMergeViaJDL(kFALSE)
        // alienHandler->SetMergeViaJDL(kTRUE);

        /* - The setting to kFALSE is to download the output files
           -
         */
        alienHandler->SetMergeViaJDL(kFALSE);
        alienHandler->SetMaxMergeStages(1);


        TString LHC18q("LHC18q");
        TString LHC18r("LHC18r");
        // define the output folders
        // alienHandler->SetGridWorkingDir("myWorkingDir");
        // alienHandler->SetGridWorkingDir("CheckAD_null");
        // alienHandler->SetGridWorkingDir("AD_HWandSW");
        alienHandler->SetGridWorkingDir("PbPb18r_CoherentCheck_2");
        // alienHandler->SetGridOutputDir("myOutputDir");
        if (opt == 0) alienHandler->SetGridOutputDir(LHC18q.Data());
        if (opt == 1) alienHandler->SetGridOutputDir(LHC18r.Data());



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
            // alienHandler->SetRunMode("full");

            /* - This option TERMINATE is used for the merging of the files.
               -
             */
            alienHandler->SetRunMode("terminate");
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
