#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
struct DistributingCenter{
    int id;
    float x1;
	float y1;
	float x2;
	float y2;
};
struct Customer{
    int id;
    int type;
    float x1;
	float y1;
	float x2;
	float y2;
};
struct Line{
    int id;
    float x1;
	float y1;
	float x2;
	float y2;
};

int main(){
    FILE *file = fopen("Realistic_system.txt","r");
    if( file == NULL )
        printf("File could not be opened");
    else{
        struct DistributingCenter all_DC[2000];
        struct Customer all_C[2000];
        struct Line all_L[2000];

        int type1 = 0;
        int type2 = 0;
        int type3 = 0;

        char costumer[2000];
        char line[2000];
        char distributing[2000];

        int count1 = 0;

        while(!feof(file)){
            if(strcmp(fgets(distributing,2000,file),"INDIRICI_ID\tX1\tY1\tX2\tY2\t\n") == 0){
                fscanf(file,"%d%f%f%f%f",&all_DC[count1].id, &all_DC[count1].x1, &all_DC[count1].y1, &all_DC[count1].x2, &all_DC[count1].y2);
                ++count1;
            }
            if(strcmp(distributing,"END\t\t\t\t\t\n")==0)
                break;
        }

        int count2 = 0;

        while(!feof(file)){
            fgets(costumer,2000,file);
                fscanf(file,"%d%d%f%f%f%f",&all_C[count2].id, &all_C[count2].type, &all_C[count2].x1, &all_C[count2].y1, &all_C[count2].x2, &all_C[count2].y2);
                ++count2;

            if(strcmp(costumer,"END\t\t\t\t\t\n")==0)
                break;
        }

        int count3 = 0;

        while(!feof(file)){
            fgets(line,2000,file);
                fscanf(file,"%d%f%f%f%f",&all_L[count3].id, &all_L[count3].x1, &all_L[count3].y1, &all_L[count3].x2, &all_L[count3].y2);
                ++count3;

            if(strcmp(line,"END\t\t\t\t\t\n")==0)
                break;
        }

        fclose(file);

        /* All data in file is printed to console in this section. */
        // a, b and c are counter.

        // Distributing Center Data
        printf("Distributing:ID     X1     Y1     X2     Y2\n");
        int a = 0;
        for(a;a<count1;a++){
            printf("%d %f %f %f %f\n",all_DC[a].id,all_DC[a].x1,all_DC[a].y1,all_DC[a].x2,all_DC[a].y2);
        }
        printf("*************************************************************************************************\n\n");
        // Costumers' Data
        printf("Costumer: ID     TYPE     X1     Y1     X2     Y2\n");
        int b = 0;
	    for(b;b<count2;b++){
	    	printf("%d  %d  %f %f %f %f\n",all_C[b].id,all_C[b].type,all_C[b].x1,all_C[b].y1,all_C[b].x2,all_C[b].y2);
		}
		printf("*************************************************************************************************\n\n");
		// Lines' Data
		int c = 0;
		printf("Lines: ID    X1   Y1  X2   Y2\n ");
		for(c;c<count3;c++){
			printf("%d  %f  %f  %f  %f\n",all_L[c].id,all_L[c].x1,all_L[c].y1,all_L[c].x2,all_L[c].y2);
		}
        printf("*************************************************************************************************\n\n");

        printf("The number of Distributing Center : %d \n",a);

        printf("The number of Costumer : %d \n",b);
        // A distinction is made here according to customer types.
        for(int g =0;g<count2-2;g++){
	       if(all_C[g].type==1){
		     type1++;
	        }
	       if(all_C[g].type==2){
		      type2++;
	        }
	       if(all_C[g].type==3){
		     type3++;
	        }
        }
        printf("The number of Residence : %d \n",type1);
        printf("The number of Commercial : %d \n",type2);
        printf("The number of Industry : %d \n",type3);

        printf("The number of Line : %d \n",c);
        // Line length is calculated in this section.
        double line_length = 0;
        for(int f=0;f<count3-2;f++) {
	        line_length+= sqrt((pow(all_L[f].x2-all_L[f].x1,2)+pow(all_L[f].y2-all_L[f].y1,2)));
        }
        printf("Line length is  %.4lf (meter)\n",line_length);

        printf("*************************************************************************************************\n\n");

        /* In this part, bird flight measurement data is calculated and written to the file. */
        FILE *file1=fopen("bird flight.txt","w");
        double bird_flight[1000];
        if(file1==NULL){
	      printf("Could not write file\n");
        }
        else {
           int counter1 = 0;
	       printf(" Bird flight file has been created\n");
	       for(counter1;counter1<count2;counter1++) {
	           bird_flight[counter1]=sqrt((pow(all_DC[counter1].x1-all_C[counter1].x1,2)+pow(all_DC[counter1].y1-all_C[counter1].y1,2)));
	           fprintf(file1,"ID:%d\t\t %d\t\t Bird Flight Distance :%lf meter\n",all_C[counter1].id,all_C[counter1].type,bird_flight[counter1]);

	        }
		}

		printf("*************************************************************************************************\n\n");

        /* In this part, it is determined whether there is a line break and it is written to the file. */

        file = fopen("Realistic_system.txt","r");
        FILE *file2 = fopen("Line break","w+");
	    if(file2==NULL){
		  printf("Failed to create file for line break.\n");
        }
	    else {

		  printf("File created for line break.\n");
		  printf("A '+' sign was placed for connected lines and a '-' sign for disconnected lines.\n");
		  for(int counter2=0;counter2<count3;counter2++){
		  for(int h=0;h<count2;h++){
		      if((all_L[counter2].x1==all_L[counter2+1].x1 && all_L[counter2].y2==all_L[counter2+1].y1) || (all_L[counter2].x1==all_L[counter2+1].x2 && all_L[counter2].y1==all_L[counter2+1].y2) || (all_L[counter2].x2==all_L[counter2+1].x1 && all_L[counter2].y2==all_L[counter2+1].y1) || (all_L[counter2].x2==all_L[counter2+1].x2 && all_L[counter2].y2==all_L[counter2+1].y2)){
				  fprintf(file2,"\n%d +\n",all_L[counter2].id);
				}
			  else{
			 	fprintf(file2,"\n%d -\n",all_L[counter2].id);
			    }
			  if((all_L[h].x1==all_C[h].x1  && all_L[h].y1==all_C[h].y1 )|| (all_L[h].x1==all_C[h].x2 && all_L[h].y1==all_C[h].y2) || (all_L[h].x2==all_C[h].x1 && all_L[h].y2==all_C[h].y1 )|| (all_L[h].x2==all_C[h].x2 && all_L[h].y2==all_L[h].y2)){
				 fprintf(file2,"\n%d +\n",all_C[h].id);
			    }
			  else {
			    	fprintf(file2,"\n%d -\n",all_C[h].id);
			    }
		    }
		    }
	    }
	   printf("\n*************************************************************************************************\n\n");
	   // In this section, all the information of any part is found with the id information and printed to the console.

	   printf("Write the part you want to learn (EX: customer,line,distributing) : \n");
	   char wanted[20];
        scanf("%s",&wanted);

        if(strcmp(wanted,"distributing")==0) {
          printf("ID: %d  X1: %f  Y1: %f  X2: %f  Y2: %f\n",all_DC[count1].id,all_DC[count1].x1,all_DC[count1].y1,all_DC[count1].x2,all_DC[count1].y2);
        }
       int wanted_id = 0;
       if(strcmp(wanted,"costumer")==0){
            printf("Enter the ID number : \n");
            scanf("%d",&wanted_id);
            for(int t=0;t<count2;t++){
              if(all_C[t].id==wanted_id){
                 printf("ID: %d Type: %d X1: %f Y1: %f X2: %f Y2: %f\n",all_C[t].id,all_C[t].type,all_C[t].x1,all_C[t].y1,all_C[t].x2,all_C[t].y2);
                }
            }
        }
       if(strcmp(wanted,"line")==0){
          printf("Enter the ID number : \n");
          scanf("%d",&wanted_id);
          for(int s=0;s<count3;s++){
             if(all_L[s].id==wanted_id){
                 printf("ID: %d X1: %f Y1: %f X2: %f Y2: %f\n",all_L[s].id,all_L[s].x1,all_L[s].y1,all_L[s].x2,all_L[s].y2);
                }
            }
        }
	    fclose(file);
	    fclose(file2);
	    printf("\n*************************************************************************************************\n\n");
    }
}
