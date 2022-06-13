TFile *data(Int_t getFile=0, Int_t print=1) {

   Char_t          type[8];
   Int_t           area1;
   Int_t           area2;
   Float_t         txpeak;
   Float_t         typeak;
   Int_t           i;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Int_t           n_1ry_pl;
   Int_t           flagw;
   Int_t           n_1ry_trk;
   Int_t           n_1ry_parent_cut0;
   Int_t           n_1ry_parent_dmin_cut;

   Int_t           n_1ry_parent_dmin_cut_dt_cut;
   Float_t         dt;

   Float_t         dz;
   Int_t           trk_id;
   Int_t           plt_of_1seg;
   Int_t           seg_id_of_1seg;
   Int_t           vIDTr;
   Int_t           vID;
   Float_t         seg_x;
   Float_t         seg_y;
   Float_t         tx;
   Float_t         ty;
   Int_t           nseg;
   Float_t         ip_to_1ry_using_1stseg;
   Float_t         ip_to_1ry_using_2ndseg;
   Float_t         ph_mean;
   Float_t         dtrms1_trk;

   TString filename = "vertexing2022.root";
   FILE *fp = fopen("DAT/vertexing2022.dat","r");

   TFile *hfile = 0;
   if (getFile) {
      if (!gSystem->AccessPathName("vertexing2022.root",kFileExists)) {
         hfile = TFile::Open("vertexing2022.root"); //in current dir
         if (hfile) return hfile;
      }
   }

   hfile = TFile::Open(filename,"RECREATE");
   TTree *vtx = new TTree("VTX","VTXinfo");

   vtx->Branch("type",type,"type/C");
   vtx->Branch("area1",&area1,"area1/I");
   vtx->Branch("area2",&area2,"area2/I");
   vtx->Branch("txpeak",&txpeak,"txpeak/F");
   vtx->Branch("typeak",&typeak,"typeak/F");
   vtx->Branch("i",&i,"i/I");
   vtx->Branch("vx",&vx,"vx/F");
   vtx->Branch("vy",&vy,"vy/F");
   vtx->Branch("vz",&vz,"vz/F");
   vtx->Branch("n_1ry_pl",&n_1ry_pl,"n_1ry_pl/I");
   vtx->Branch("flagw",&flagw,"flagw/I");
   vtx->Branch("vID",&vID,"vID/I");
   vtx->Branch("n_1ry_trk",&n_1ry_trk,"n_1ry_trk/I");
   vtx->Branch("n_1ry_parent_cut0",&n_1ry_parent_cut0,"n_1ry_parent_cut0/I");
   vtx->Branch("n_1ry_parent_dmin_cut",&n_1ry_parent_dmin_cut,"n_1ry_parent_dmin_cut/I");

   vtx->Branch("n_1ry_parent_dmin_cut_dt_cut",&n_1ry_parent_dmin_cut_dt_cut,"n_1ry_parent_dmin_cut_dt_cut/I");
   vtx->Branch("dt",&dt,"dt/F");

   TTree *trk = new TTree("TRK","TRKinfo");

   trk->Branch("type",type,"type/C");
   trk->Branch("area1",&area1,"area1/I");
   trk->Branch("area2",&area2,"area2/I");
   trk->Branch("txpeak",&txpeak,"txpeak/F");
   trk->Branch("typeak",&typeak,"typeak/F");
   trk->Branch("i",&i,"i/I");
   trk->Branch("vx",&vx,"vx/F");
   trk->Branch("vy",&vy,"vy/F");
   trk->Branch("vz",&vz,"vz/F");
   trk->Branch("flagw",&flagw,"flagw/I");
   trk->Branch("n_1ry_trk",&n_1ry_trk,"n_1ry_trk/I");
   trk->Branch("n_1ry_parent_cut0",&n_1ry_parent_cut0,"n_1ry_parent_cut0/I");
   trk->Branch("n_1ry_parent_dmin_cut",&n_1ry_parent_dmin_cut,"n_1ry_parent_dmin_cut/I");

   trk->Branch("dz",&dz,"dz/F");
   trk->Branch("trk_id",&trk_id,"trk_id/I");
   trk->Branch("plt_of_1seg",&plt_of_1seg,"plt_of_1seg/I");
   trk->Branch("seg_id_of_1seg",&seg_id_of_1seg,"seg_id_of_1seg/I");
   trk->Branch("seg_x",&seg_x,"seg_x/F");
   trk->Branch("seg_y",&seg_y,"seg_y/F");
   trk->Branch("tx",&tx,"tx/F");
   trk->Branch("ty",&ty,"ty/F");
   trk->Branch("nseg",&nseg,"nseg/I");
   trk->Branch("vID",&vIDTr,"vID/I");
   trk->Branch("ip_to_1ry_using_1stseg",&ip_to_1ry_using_1stseg,"ip_to_1ry_using_1stseg/F");
   trk->Branch("ip_to_1ry_using_2ndseg",&ip_to_1ry_using_2ndseg,"ip_to_1ry_using_2ndseg/F");
   trk->Branch("ph_mean",&ph_mean,"ph_mean/F");
   trk->Branch("dtrms1_trk",&dtrms1_trk,"dtrms1_trk/F");

   int VtxId = 0;
   char line[185];
   while (fgets(line,185,fp)) {
      sscanf(&line[0],"%s ",type);
      if(strcmp(type,"1ry_vtx")==0){
      sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %d %d %f",&area1,&area2,&txpeak,&typeak,&i,&vx,&vy,&vz,&n_1ry_pl,&flagw,&n_1ry_trk,&n_1ry_parent_cut0,&n_1ry_parent_dmin_cut,&n_1ry_parent_dmin_cut_dt_cut,&dt);
      VtxId++;
      vID = VtxId;
      vtx->Fill();
      }
      if(strcmp(type,"1ry_trk")==0){
      sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %f %d %d %d %f %f %f %f %d %f %f %f %f",&area1,&area2,&txpeak,&typeak,&i,&vx,&vy,&vz,&flagw,&n_1ry_trk,&n_1ry_parent_cut0,&n_1ry_parent_dmin_cut,&dz,&trk_id,&plt_of_1seg,&seg_id_of_1seg,&seg_x,&seg_y,&tx,&ty,&nseg,&ip_to_1ry_using_1stseg,&ip_to_1ry_using_2ndseg,&ph_mean,&dtrms1_trk);
      vIDTr = VtxId;
      trk->Fill();
      }
      
   }
   if (print) vtx->Print();
   if (print) trk->Print();
   vtx->Write();
   trk->Write();

   fclose(fp);
   delete hfile;
   if (getFile) {
      hfile = TFile::Open(filename);
      return hfile;
   }
   return 0;
}
