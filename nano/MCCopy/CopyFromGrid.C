void CopyFromGrid(TString OutputDir="./")
{
  TGrid::Connect("alien:",0,0,"t");


  //const char *cpcmd = Form("gbbox find   /alice/cern.ch/user/a/agautam/simulation/freshstart/ 244918/Mu4.root > bbb.txt");
  const char *cpcmd = Form("gbbox find   /alice/cern.ch/user/a/agautam/LHC18qMCJP/LHC18qMCJP/ */AnalysisResults.root > bbb.txt");

  TString list = "bbb.txt";
  gSystem->Exec(cpcmd);

  // return;



  TString line;
  ifstream in;
  in.open(list.Data());
  Int_t ic = 0;

  while (in.good()) {
    in >> line;
    if (line.Length() == 0) continue;
    Printf("%d adding %s",ic,line.Data());


    Long_t id, size, flags, modtime;
    const char *name = Form("alien://%s",line.Data());
    if (gSystem->GetPathInfo(name, &id, &size, &flags, &modtime))
      {
	printf("%s not found.\n", name);
	continue;
      }

    //  if(size < 24977) continue;
    printf("size = %d\n",Int_t(size));


    //    GetName(line.Data());

    TString OutputDir1 = Form("%s/%d",OutputDir.Data(),ic);


    //    printf("****   %s\n", OutputDir1.Data());
      gSystem->Exec(Form("mkdir -p %s", OutputDir1.Data()));


     TString cmd=Form("alien_cp alien:%s  file:%s",line.Data(),OutputDir1.Data());
      gSystem->Exec(cmd.Data());

      //  if(ic>2) break;

    ic++;

  }




}







void GetName(const char* name)
{
   TString j = name;
   TObjString *os;
   TObjArray *arr = j.Tokenize("/");

   TObjString *os7 = (TObjString *)arr->At(7);
   TObjString *os8 = (TObjString *)arr->At(8);

   printf("%s   %s\n",os7->GetString().Data(), os8->GetString().Data());
   TIter next(arr);
   while ((os=(TObjString*)next())){

     printf("%s\n", os->GetString().Data());
     //       if (fJetBranchName.Length()) fJetBranchName += " ";
     //       fJetBranchName += os->GetString().Data();
   }
   delete arr;
}   
