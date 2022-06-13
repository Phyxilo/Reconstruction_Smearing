TFile *dataread(Int_t getFile=0, Int_t print=1) {

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
   FILE *fp = fopen("DAT/MCVertexing2022.dat","r");

   FILE *fp1;
   fp1 = fopen("DAT/vertexing2022.dat", "w+");

   char line[190];
   while (fgets(line,190,fp)) {
      sscanf(&line[0],"%s ",type);
      if(strcmp(type,"1ry_vtx")==0){
      sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %d %d %f",&area1,&area2,&txpeak,&typeak,&i,&vx,&vy,&vz,&n_1ry_pl,&flagw,&n_1ry_trk,&n_1ry_parent_cut0,&n_1ry_parent_dmin_cut,&n_1ry_parent_dmin_cut_dt_cut,&dt);
      fprintf(fp1, "1ry_vtx   %d %d %.5f  %.5f  %d %.1f  %.1f  %.1f  %d %d %d %d %d %d %.5f  \n",area1,area2,txpeak,typeak,i,vx,vy,vz,n_1ry_pl,flagw,n_1ry_trk,n_1ry_parent_cut0,n_1ry_parent_dmin_cut,n_1ry_parent_dmin_cut_dt_cut,dt);
      //vtx->Fill();
      }
      if(strcmp(type,"1ry_trk")==0){
      sscanf(&line[8],"%d %d %f %f %d %f %f %f %d %d %d %d %f %d %d %d %f %f %f %f %d %f %f %f %f",&area1,&area2,&txpeak,&typeak,&i,&vx,&vy,&vz,&flagw,&n_1ry_trk,&n_1ry_parent_cut0,&n_1ry_parent_dmin_cut,&dz,&trk_id,&plt_of_1seg,&seg_id_of_1seg,&seg_x,&seg_y,&tx,&ty,&nseg,&ip_to_1ry_using_1stseg,&ip_to_1ry_using_2ndseg,&ph_mean,&dtrms1_trk);
      fprintf(fp1, "1ry_trk   %d %d %.5f  %.5f  %d %.1f  %.1f  %.1f  %d %d %d %d %.1f  %d %d %d %.1f  %.1f  %.3f  %.3f  %d %.2f  %.2f  %.2f  %.5f  \n",area1,area2,txpeak,typeak,i,vx,vy,vz,flagw,n_1ry_trk,n_1ry_parent_cut0,n_1ry_parent_dmin_cut,dz,trk_id,plt_of_1seg,seg_id_of_1seg,seg_x,seg_y,tx,ty,nseg,ip_to_1ry_using_1stseg,ip_to_1ry_using_2ndseg,ph_mean,dtrms1_trk);
      //trk->Fill();
      }
      
   }
   fclose(fp1);
   fclose(fp);
   return(0);
}