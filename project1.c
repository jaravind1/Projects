
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void word_count(char *);            //declaration for the method word_count

//method for printing the usage menu

void usage_menu()
{

printf("\nUsage Menu\n");
printf("0. copy\n");
printf("1. interleave\n");
printf("2. more\n");
printf("3. grep\n");
printf("4. word count\n\n");

}


int main(int argc, char *argv[])
{
if(argc>5)
{exit(0);
}
else if(strcmp(argv[1],"0")==0)
{
if(argv[4])
{
usage_menu();
exit(1);
}
else
{goto g;}

}





else if ((strcmp(argv[1],"2")==0)||(strcmp(argv[1],"3")==0)||(strcmp(argv[1],"4")==0))
   {
   if(argv[3])
    {
     usage_menu();
     exit(1);}
   else
   {goto g;}
   }

else
{
  //initializing the variables,counters, file pointers etc.

g:  int a,counter=0;
  FILE *file1,*file2,*file3;
  char k,*ptr,line[1000],line1[1000],line2[1000],c[1000],d[1000],n[20],i=0;

  //putting the users choice in a switch case

switch(argv[1][0])
{

case '0':    //for option 0 perform the copy operation

      file1=fopen(argv[2],"r");     /*opening the file pointer for the file to e read*/
      file2=fopen(argv[3],"w");     /*opening the file pointer for the file to be written*/
      if(file1!=NULL)
       {
      while (fgets(line,sizeof(line),file1)!= NULL) /*if fgets returns null end of file reached*/
      {
         fputs(line,file2);        //writing the file contents line by line
      }
       fclose(file1);              //closing the file pointer1
       fclose(file2);              //closing the file pointer2
      }
     else
      {
      printf("\nFile %s cannot open\n\n",argv[2]);   //if file pointer retuns null, file cannot be opened
       }
      break;


case '1':    //for option 1 perform the interleave operation

   file1 = fopen(argv[2],"r");           //opening file1 for reading
   file2 = fopen(argv[3],"r");           //opening file2 for reading
   file3 = fopen(argv[4],"w");           //opening file3 for writing
   char line1[1000],line2[1000];

 if((file1!=NULL)&&(file2!=NULL))
 { while(!feof(file1)||!feof(file2))      //while loop ends if both file ends
    {
     if (i%2==0)
    {
     ptr=fgets(line1,sizeof(line1),file1); //writing one line of file1
     }
    else
      {
     ptr=fgets(line1,sizeof(line1),file2); //writing one line of file2
      }
     if(ptr!=NULL)
       {
       fputs(line1,file3);               //writing one line to file3
       }
        i++;
     }
 }
   else if(file1==NULL)
   { printf("\nFile %s cannot open\n\n",argv[2]);
       }
  else
{  printf("\nFile %s cannot open\n\n",argv[3]);}//if file pointer returns null, file cannot be opened
//closing all the file pointers

     fclose(file1);
     fclose(file2);
     fclose(file3);
     exit(0);

case '2':

  file1 = fopen(argv[2],"r");
if(file1!=NULL)
{
  for(i=0;i<10;i++)
  {
    fgets(line,sizeof(line),file1);   //displaying the first 10 lines in the file
    printf(line,"\n");
  }

 while(!feof(file1))
  {
   printf("\nEnter Input (n/p/q): "); // asking the input from the user if he wants to display the next line,next 10 lines or quit
   scanf(" %c",&k);
   if(k=='n')
    {
    fgets(line,sizeof(line),file1);
    printf(line,"\n");               //if the user inputs n print the next line
    }
   else if(k=='p')
  {
   for(i=0;i<10;i++)
  {
   fgets(line,sizeof(line),file1);   //if the user inputs p print the next 10 lines
   if(feof(file1))
   exit(0);
  else
   printf(line,"\n");
 }
 }
 else if(k=='q')                    //if the user inputs q quit the program
{exit(0);}

}
}

     else
      {
      printf("\nFile %s cannot open\n\n",argv[2]);   //if the file doesnt exist display error message
       }


break;


case '3':

   printf("\nEnter input search string : ");  //prompting the usr to enter a string
   gets(n);
   static const char filename[] = "file.txt";
   file1 = fopen(argv[2],"r");               //open file pointer file1 for reading a file
if(file1!=NULL)
{
    while (fgets(line,sizeof(line),file1)!= NULL)
      {
          if(strstr(line,n))
                {printf(line);              //printing out line that contains the input character string
        }
      }
  fclose(file1);                           //closing the file pointer file1
 }


else

      {
      printf("\nFile %s cannot open\n\n",argv[2]);
       }
break;

case '4':



       word_count(argv[2]);                //calling the method word count
       break;

}
}
}


void word_count(char *fp)                 //definition for the method word_count

{
 FILE *fp1;                                     //declaring file pointer fp1
 char  smallest_line_c[100],smallest_line_w[100],d,a[100],b[100],c[100],longest_word[100],longest_word2[100],longest_word3[100]; //declaring character variables
 int l,len,len1=10000,max1=0,max2=0,max3=0,ctr1=0,ctr2=0,ctr3=0,ctr4=0,small=1000,max=-1,i=0,word_count,word_count1=10000,wc;     //declaring integer variables

 fp1=fopen(fp,"r");                                                                   //opening file pointer fp1
if(fp1!=NULL)

{

 while(fgets(a,sizeof(a),fp1)!=NULL)           //reading line by line till end of file is reacheD
 {
  len=0;
  word_count=0;

 for(i=0;a[i]!='\0';i++)
  {
      len++;
      if(((a[i]>=48)&&(a[i]<=57))||((a[i]>=65)&&(a[i]<=90))||((a[i]>=97)&&(a[i]<=122)))
          {
             word_count++;
          }

      wc=len-word_count;
  }

  if(wc<word_count1)
  {
    word_count1=wc;
    strcpy(smallest_line_w,a);               //smallest line in terms of number of words will be stored in the variable smallest_line_w
  }
 }

fclose(fp1);                                 //closing the file pointer fp1
fp1=fopen(fp,"r");                           //opening the file pointer fp1

while(fscanf(fp1,"%c",&d)!= EOF)
{
 ctr2++;
 if(((d>=65)&&(d<=90))||((d>=97)&&(d<=122))||((d>=48)&&(d<=57)))
 ctr3++;
}

  fclose(fp1);
  fp1=fopen(fp,"r");
  while(fgets(a,sizeof(a),fp1)!=NULL)
 {
    ctr1++;
    ctr4=0;
   for(i=0;a[i]!='\0';i++)
  {
    len++;
   if(((a[i]>=48)&&(a[i]<=57))||((a[i]>=65)&&(a[i]<=90))||((a[i]>=97)&&(a[i]<=122)))
      {word_count++;}
       wc=len-word_count;
       ctr4++;

}

 if(wc<word_count1)
{
word_count1=wc;
strcpy(smallest_line_w,a);
}
if(ctr4<small)
 {small=ctr4;
 strcpy(b,a);}
}
fclose(fp1);
fp1=fopen(fp,"r");

while(fscanf(fp1,"%s",&c)!=EOF)
{
l=0;
for(i=0;c[i]!='\0';i++)
l++;
if(l>max)
{
max=l;
strcpy(longest_word,c);                 //the longest word is stored in the variable longest_word
}
else if((l>max2)&&(l<=max))
{
max2=l;
strcpy(longest_word2,c);                 //the second longest word stored in variable longest_word2
}
else if((l>max3)&&(l<=max2))
{
max3=l;
strcpy(longest_word3,c);                //the third longest word stored in variable longest_word3
}
}fclose(fp1);                           //closing the file pointer fp1

//printing all what is required in case 4

printf("Number of lines = %d\n",ctr1);                                                             //printing the total number of lines
printf("Number of characters = %d\n",ctr2);                                                        // printing the total number of characters
printf("Number of words = %d\n",ctr2-ctr3);                                                        //printing the total number of words
printf("The shortest line (%d characters): %s\n",small-1,b);                                       //printing the shortest line in terms of number of characters
printf("The shortest line (%d words): %s\n",word_count1,smallest_line_w);                          //printing the shortest line in terms of number of words
printf("The top three longest words are: %s, %s, %s\n",longest_word,longest_word2,longest_word3);  //printing the longest 3 words
}
else
{
printf("\nFile %s cannot open\n\n",fp);
       }


}

