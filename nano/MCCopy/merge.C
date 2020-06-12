{

TFileMerger m1 ;


const char *FileName = "Incohernt_Phi.root";


m1.OutputFile("Incoherent_Phi.root");

 for(Int_t i = 0; i< 200; i++)
   {
     //     if(i != 2094 && i != 2157 && i != 2228 && i != 4839 && i != 5779 && i != 5906 && i != 6494) {

 const char *name = Form("%d/%s", i,FileName);
 Long_t id, size, flags, modtime;
 if (gSystem->GetPathInfo(name, &id, &size, &flags, &modtime))
   {
     printf("%s not found.\n", name);
     continue;
   }

 m1.AddFile(name);
 printf("%d/%s\n",i,FileName);
 //     }
   }


 m1.Merge() ;


}
