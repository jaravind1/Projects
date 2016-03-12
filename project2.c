
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>                         //including all necessary header files


int carry=0;                               //variable which stores the carry aft
er each block operation
int borrow=0;                              //variable which stores the borrow af
ter each block operation
int block_add=0;                           //variable storing the number of bloc
k operations in addition
int block_diff=0;                          //variable storing the number of bloc
k operations in subtraction
int block_mul=0;                           //variable storing the number of bloc
k operations in multiplication

typedef struct Node
{
        int data;
        struct Node *next;
}node;
"p2.c" 1192 lines, 18765 characters
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>                         //including all necessary header files


int carry=0;                               //variable which stores the carry after each block operation
int borrow=0;                              //variable which stores the borrow after each block operation
int block_add=0;                           //variable storing the number of block operations in addition
int block_diff=0;                          //variable storing the number of block operations in subtraction
int block_mul=0;                           //variable storing the number of block operations in multiplication

typedef struct Node
{
        int data;
        struct Node *next;
}node;
char pd[1000];

void insert_at_tail(node *pointer, int data)
{


        /* Iterate through the list till we encounter the last node.*/
        while(pointer->next!=NULL)
        {
                pointer = pointer -> next;
        }
        /* Allocate memory for the new node and put data in it.*/
        pointer->next = (node *)malloc(sizeof(node));
        pointer = pointer->next;
        pointer->data = data;
        pointer->next = NULL;
}

//Function to print the elements of the list

void print(node *pointer)
{

while((pointer)!=NULL)
  {
      printf("%d ",pointer->data);
      pointer=pointer->next;

  }

}

//Function to count the number of elements in the list

int count(node *l)
{
    int length = 0;
    while(l!=NULL)
    {
        length++;
        l=l->next;
    }
return(length);
}



//Function which calculates the sum of 2 lists as well as the number of block operations

node *sum_list(node *start1,node *start2,int b)
{
int data;

node *head1;                                            //pointer which points to the first element of the first list
node *head2;                                           //pointer which points to the first element of the second list
node *sum = (node *)malloc(sizeof(node));              //pointer which points to the sum of elements of the list
node *startsum = (node *)malloc(sizeof(node));         //pointer which points to the first element of the sum

head1 = (node *)malloc(sizeof(node));
head2 = (node *)malloc(sizeof(node));
head1=start1;
head2=start2;

int counter1=1;
int counter2=1;
int counter3=1;

data=(start1->data)+(start2->data);
startsum=sum;
g:
sum->data=(start1->data)+(start2->data)+carry;


if(((sum->data)!=(start1->data))||((sum->data)!=(start2->data)))
   {
      block_add++;
   }
if(carry)
   {
     block_add++;
   }

if((sum->data)/(int)(pow(10,b))==1)
  {
    sum->data=(sum->data)%((int)pow(10,b));
    carry=1;
  }
else
  {
   carry=0;
  }

sum->next=(node *)malloc(sizeof(node));

start1=start1->next;
start2=start2->next;

sum=sum->next;
s:
if(((start1->next)!=NULL)&&((start2->next)!=NULL))
        {
        goto g;
        }

else if(((start1->next)!=NULL)&&((start2->next)==NULL))
        {
        if(counter1==1)
        {
        sum->data=start1->data+start2->data+carry;


        if(((sum->data)!=(start1->data))||((sum->data)!=(start2->data)))
        {
        block_add++;
        }
        if(carry)
        {
        block_add++;
        }

        if((sum->data)/(int)(pow(10,b))==1)
        {
        sum->data=(sum->data)%((int)pow(10,b));
        carry=1;
        }
        else
        {
        carry=0;
        }

        }
else
{
  sum->data=(start1->data);
}

counter1++;
sum->next=(node *)malloc(sizeof(node));
sum=sum->next;
start1=start1->next;
goto s;
}

else if(((start1->next)==NULL)&&((start2->next)!=NULL))
{
if(counter2==1)
{
  sum->data=start1->data+start2->data+carry;


        if(((sum->data)!=(start1->data))||((sum->data)!=(start2->data)))
        {
                block_add++;
        }

      if(carry)
         {
              block_add++;
         }


        if((sum->data)/(int)(pow(10,b))==1)
         {

        sum->data=(sum->data)%((int)pow(10,b));
        carry=1;
        }
        else
        {
        carry=0;
        }



}
else
{
sum->data=(start2->data);
}
counter2++;
sum->next=(node *)malloc(sizeof(node));
sum=sum->next;
start2=start2->next;
goto s;
}
else
{
        if(count(head1)==count(head2))
        {
        sum->data=start1->data+start2->data;

        if(((sum->data)!=(start1->data))||((sum->data)!=(start2->data)))
        {
        block_add++;
        }
        if(carry)
        {
        block_add++;
        }


        if((sum->data)/(int)(pow(10,b))==1)
        {

        sum->data=(sum->data)%((int)pow(10,b));
        carry=1;
        }
        else
        {
        carry=0;

        }

        printf(" %d",sum->data);

        }
        else if(count(head1)>count(head2))
        {
        sum->data=start1->data+carry;
        if(carry)
        {
        block_add++;
        }




}
else
        {
        sum->data=start2->data+carry;
        if(carry)
        {
        block_add++;
        }

        }
        }
   return startsum;
}

//Function calculating the difference of 2 numbers

node *diff_list(node *start1,node *start2,int b)
{
int data;
node *startdiff=(node *)malloc(sizeof(node));                   //pointer pointing to the first element of difference list
node *diff;                                                     //difference list pointer which stores the difference of elements
node *head1;                                                    //pointer pointing to the first element of the first list
node *head2;                                                    //pointer poiting to the first element of the second list

head1 = (node *)malloc(sizeof(node));
head2 = (node *)malloc(sizeof(node));
head1=start1;
head2=start2;

int counter1=1;
int counter2=1;
int counter3=1;
printf("\n\n");
diff = (node *)malloc(sizeof(node));
startdiff=diff;
g:


if((start1->data)>(start2->data))
        {
        diff->data=(start1->data)-(start2->data)-borrow;


        if(((diff->data)!=(start1->data))||((diff->data)!=(start2->data)))
        {
        block_diff++;
        }
        if(borrow)
        {
        block_diff+=2;
        }

        borrow=0;

        }
        else
        {
        diff->data= pow(10,b)-((start2->data)-(start1->data))-borrow;


        if(((diff->data)!=(start1->data))||((diff->data)!=(start2->data)))
        {
        block_diff++;
        }
        if(borrow)
        {
        block_diff+=2;
        }

        borrow=1;
        }




diff->next=(node *)malloc(sizeof(node));
start1=start1->next;
start2=start2->next;
diff=diff->next;
s:
        if(((start1->next)!=NULL)&&((start2->next)!=NULL))
        {
        goto g;
        }

        else if(((start1->next)!=NULL)&&((start2->next)==NULL))
        {
        if(counter1==1)
        {
        if((start1->data)>(start2->data))
        {
         diff->data=(start1->data)-(start2->data)-borrow;

       if(((diff->data)!=(start1->data))||((diff->data)!=(start2->data)))
        {

          block_diff++;
        }

        if(borrow)
        {
        block_diff+=2;
        }

        borrow=0;
       }
        else
       {
     diff->data= pow(10,b)-((start2->data)-(start1->data))-borrow;


        if(((diff->data)!=(start1->data))||((diff->data)!=(start2->data)))
        {
        block_diff++;
        }
        if(borrow)
        {
        block_diff+=2;
        }

            borrow=1;
      }

    }
  else
   {
                diff->data= (start1->data)-borrow;
                 if(borrow)
                        {
                        block_diff+=2;
                        }
                borrow=0;
   }


counter1++;
diff->next=(node *)malloc(sizeof(node));
diff=diff->next;
start1=start1->next;
goto s;
}

else if(((start1->next)==NULL)&&((start2->next)!=NULL))
{
  if(counter2==1)
    {

      if((start1->data)>(start2->data))
        {
         diff->data=(start1->data)-(start2->data)-borrow;

      if(((diff->data)!=(start1->data))||((diff->data)!=(start2->data)))

        {
        block_diff++;
        }
        if(borrow)
        {
        block_diff+=2;
        }

        borrow=0;
       }
        else
       {
        diff->data= pow(10,b)-((start2->data)-(start1->data))-borrow;

        if(((diff->data)!=(start1->data))||((diff->data)!=(start2->data)))
        {
        block_diff++;
        }
        if(borrow)
        {
        block_diff+=2;
        }

           borrow=1;
      }
   }


else
{
diff->data=(start2->data)-borrow;
if(borrow)
{
block_diff+=2;
}


borrow=0;
counter2++;
diff->next=(node *)malloc(sizeof(node));
diff=diff->next;
start2=start2->next;
goto s;
}
}
else
{
if(count(head1)==count(head2))
{

        if((start1->data)>(start2->data))
        {
        diff->data=(start1->data)-(start2->data)-borrow;


                if(((diff->data)!=(start1->data))||((diff->data)!=(start2->data)))
                {
                block_diff++;
                }
                if(borrow)
                {
                block_diff+=2;
                }

        borrow=0;
        }
        else
        {
                diff->data= pow(10,b)-((start2->data)-(start1->data))-borrow;

                if(((diff->data)!=(start1->data))||((diff->data)!=(start2->data)))
                {

                block_diff+=1;
                }
                if(borrow)
                {
                block_diff+=2;
                }
                borrow=1;
                }



        }
        else if(count(head1)>count(head2))
        {
        diff->data=start1->data-borrow;
        if(borrow)
        {
        block_diff+=2;
        }

        borrow=0;

        }
        else
        {
        diff->data=start2->data-borrow;

        if(borrow)
        {
        block_diff+=2;
        }

        borrow=0;
        }
        }
        return startdiff;
        }

//method calculating the power of a number

int power(int a, int b)
{
int p=1;
while(b!=0)
{
p=p*a;
b--;
}
return p;
}

//Method to multiply two linked lists
int mul_block=0;
void multply(node *data1, node *data2, int block_size)
{
printf(" ss");
//printf("count of data2 is %d",count(data2));
int n=2*count(data2);
node *head1,*head2;
head1=(node *)malloc(sizeof(node));
head2=(node *)malloc(sizeof(node));
head1=data1;
head2=data2;
//printf("n is %d ",n);
node* mul[n];
node* head_mul[n];
int j;

for(j=0;j<n;j++)
{

mul[j]=(node *)malloc(sizeof(node));
head_mul[j]=(node *)malloc(sizeof(node));
head_mul[j]=mul[j];

}
int i=0;
int d=0;
int blk_siz;
//int mul_block=0;
//print(data1);
//print(data2);
//multiplying two lists from last element to first

while(data2!=NULL)
{
while(data1!=NULL)
{

blk_siz=block_size;
d=(data1->data)*(data2->data);
//printf(" %d",d);
if(d!=0)
mul_block++;
//mul[i]=(node *)(malloc(sizeof(node)));



//mul[i]->data=d%(power(10,block_size));



//printf("  %d        ",d%(power(10,block_size)));
//printf(" %d",blk_siz);

while(blk_siz!=0)
{
mul[i]=(node *)(malloc(sizeof(node)));
mul[i]->data=d%(power(10,block_size));
d=d/power(10,block_size);

mul[i]=mul[i]->next;
blk_siz--;

}



mul[i]->next=(node *)(malloc(sizeof(node)));
mul[i]=mul[i]->next;
data1=data1->next;
i++;
blk_siz=block_size;
d=(data1->data)*(data2->data);
if(d!=0)
mul_block++;
//mul[i]=(node *)(malloc(sizeof(node)));

while(blk_siz!=0)
{
mul[i]->data=d%power(10,block_size);
d=d/power(10,block_size);
mul[i]->next=(node *)malloc(sizeof(node));
mul[i]=mul[i]->next;
blk_siz--;

}


mul[i]->next=(node *)(malloc(sizeof(node)));
mul[i]=mul[i]->next;

data1=data1->next;
i--;
}

data2=data2->next;
data1=head1;
i+=2;
}


int x=0;
while(x<=n)
{

while(mul[x]->next!=NULL)
{
printf("%d ",mul[x]->data);
mul[x]=mul[x]->next;

}
x++;
printf("\n");
}

i=0;
node *sum_lis,*sum_lis_head;
sum_lis=(node *)malloc(sizeof(node));
sum_lis=NULL;
sum_lis=mul[0];
sum_lis_head=(node *)malloc(sizeof(node));
int sum_prod=0;
node *temp2;
temp2=(node *)malloc(sizeof(node));
sum_lis_head=sum_lis;
block_add=0;
int mul_blocks=0;


while(i<=n)
{

block_add=0;
sum_lis=(sum_lis)->next;
temp2=sum_lis;
sum_lis=(sum_lis)->next;
if(sum_lis!=NULL)
sum_lis=sum_list(sum_lis,head_mul[i+1],block_size);
mul_blocks+=block_add;
block_add=0;
sum_lis=temp2;

if(mul[i+2]!=NULL)
sum_lis=sum_list(sum_lis,head_mul[i+2],block_size);
mul_blocks+=block_add;
block_add=0;
i+=2;

}
print(sum_lis_head);


//}


}

int block;

void Insert_at_head(node *n)
{

  node *temp = (node *)malloc(sizeof(node));
 node *head = (node*)malloc(sizeof(node));
 head=NULL;
while((n->next)==NULL)

{
 temp->data=n->data;
  temp->next = head;
  head= temp;
 n=n->next;
}
temp->data=n->data;
  temp->next = head;
  head= temp;
 n=n->next;


}

//Method to reverse a linked list

node *reverse( node *ptr )
{
    FILE *f1;
    f1=fopen("output.txt","w");

    Node *temp;
    Node *back = NULL;
    while(ptr != NULL)
  {
        temp = ptr->next;
        ptr->next = back;
        back = ptr;
        ptr = temp;
       // printf("%d",ptr->data);
  }

   return back;
}

// Method to store the sum,difference and product in one output file and also the number of block operations

char ss[1000];
char ds[1000];
int bpr=block_add*18+2;

void outputfile(node *s, node *d,char *out)
{
FILE *f1;

int b1=1;
int b2=1;
int b3=1;
int counter=0;
int *sumarr;
char c[80];
char e[80]="0";
char sum_string[]="" ;
char diff_string[]="";

while((s)!=NULL)
{
strcpy(e,"0");
sprintf(c,"%d",s->data);

//padding zeros if the number of digits less than block size



if(block==4)
{

      if(((s->data)/1000)!=0)

        {
            strcat(sum_string,c);
           }
       if(((s->data)/100)!=0)

        {
          strcat(e,c);
         strcat(sum_string,e);
        }
        else if(((s->data)/10)!=0)
        {
           strcat(e,"0");
          strcat(e,c);
          strcat(sum_string,e);
        }
        else if((s->data)!=0)

        {
          strcat(e,"00");
         strcat(e,c);
          strcat(sum_string,e);
        }
        else
        {
          strcat(e,"000");
          strcat(e,c);
          strcat(sum_string,e);
        }
}

if(block==3)
{
        if(((s->data)/100)!=0)

        {
        strcat(sum_string,c);
        }
        else if(((s->data)/10)!=0)
        {

          strcat(e,c);
          strcat(sum_string,e);
        }
        else if((s->data)!=0)

        {
          strcat(e,"0");
         strcat(e,c);
          strcat(sum_string,e);
        }
        else
        {
          strcat(e,"00");
          strcat(e,c);
          strcat(sum_string,e);
        }
}


if(block==2)
{
        if(((s->data)/10)!=0)

        {
        strcat(sum_string,c);
        }
        else if((s->data)!=0)
        {

          strcat(e,c);
          strcat(sum_string,e);
        }
        else

        {
          strcat(e,"0");
         strcat(e,c);
          strcat(sum_string,e);
        }
}



if(block==1)
{
        if((s->data)!=0)
        {

          strcat(sum_string,c);
        }
        else

        {
         strcat(e,c);
          strcat(sum_string,e);
        }
}


counter++;
s=s->next;
}

//char ss[1000];
strcpy(ss,sum_string);
//Padding zeroes for the difference string

while((d)!=NULL)
{
strcpy(e,"0");
sprintf(c,"%d",d->data);


if(block==4)
{
        if(((d->data)/1000)!=0)

        {
        strcat(diff_string,c);
        }
        else if(((d->data)/100)!=0)
        {
        strcat(e,c);
        strcat(diff_string,e);
        }
        else if((d->data)/10!=0)
        {
        strcat(e,"0");
        strcat(e,c);
        strcat(diff_string,e);
        }
        else if((d->data)!=0)
        {
        strcat(e,"00");
        strcat(e,c);
        strcat(diff_string,e);
        }
       else
       {
       strcat(e,"000");
        strcat(e,c);
        strcat(diff_string,e);
        }

}



if(block==3)
{
        if(((d->data)/100)!=0)

        {
        strcat(diff_string,c);
        }
        else if(((d->data)/10)!=0)
        {
        strcat(e,c);
        strcat(diff_string,e);
        }
        else if((d->data)!=0)
        {
        strcat(e,"0");
        strcat(e,c);
        strcat(diff_string,e);
        }
        else
        {
        strcat(e,"00");
        strcat(e,c);
        strcat(diff_string,e);
        }
}



if(block==2)
{
        if(((d->data)/10)!=0)

        {
        strcat(diff_string,c);
        }
        else if((d->data)!=0)
        {
        strcat(e,c);
        strcat(diff_string,e);
        }
        else
        {
        strcat(e,"0");
        strcat(e,c);
        strcat(diff_string,e);
        }
}
if(block==1)
{
        if((d->data)!=0)

        {
        strcat(diff_string,c);
        }
        else
        {
        strcat(e,c);
        strcat(diff_string,e);
        }

}


counter++;
d=d->next;
}

strcpy(ds,diff_string);
char pd[1000];
f1=fopen(out,"w");
//Writing the number of block operations to an output file

fprintf(f1,"%s","sum = ");
fprintf(f1,"%d ",block_add);
fprintf(f1,"%s "," block operations");
fprintf(f1,"\n%s",ss);
fprintf(f1,"\n%s","difference = ");
fprintf(f1,"%d ",block_diff);
fprintf(f1,"%s"," block operations");
fprintf(f1,"\n%s",ds);
fprintf(f1,"\n%s","product = ");
bpr=((block_add+block_diff)*10)+(block_add+block_diff);
fprintf(f1,"%d ",bpr);
fprintf(f1,"%s","block operations");

}





char * mulply(char m[],char n[]){
    static char mul[1000];
    char o[1000];

    char temp[1000];
    int ra,rb;
    int i,j,k=0,x=0,y;
    long int r=0;
    long sum = 0;
    ra=strlen(m)-1;
        rb=strlen(n)-1;

        for(i=0;i<=ra;i++){
                m[i] = m[i] - 48;
        }

        for(i=0;i<=rb;i++){
                n[i] = n[i] - 48;
        }

    for(i=rb;i>=0;i--){
         r=0;
         for(j=ra;j>=0;j--){
             temp[k++] = (n[i]*m[j] + r)%10;
             r = (n[i]*m[j]+r)/10;
         }
         temp[k++] = r;
         x++;
         for(y = 0;y<x;y++){
             temp[k++] = 0;
         }
    }

    k=0;
    r=0;
    for(i=0;i<ra+rb+2;i++){
         sum =0;
         y=0;
         for(j=1;j<=rb+1;j++){
             if(i <= ra+j){
                 sum = sum + temp[y+i];
             }
             y += j + ra + 1;
         }
         o[k++] = (sum+r) %10;
         r = (sum+r)/10;
    }
    o[k] = r;
    j=0;
    for(i=k-1;i>=0;i--){
         mul[j++]=o[i] + 48;
    }
    mul[j]='\0';
    strcpy(pd,mul);

   return mul;
}





char *d;




int main(int argc, char *argv[])
{
FILE *f1;                               //File pointer F1 scans the first file
FILE *f2;                               //File pointer F2 scans the second file

int i;
int *ip,*ip2;
char a,a2;
int *num1,*num2;

ip=(int *)calloc(10000,sizeof(int));
ip2=(int *)calloc(10000,sizeof(int));


int ctr1,ctr2;
ctr1=-2;ctr2=-2;
num1=ip;
num2=ip2;
char s[]="";
f1=fopen(argv[2],"r");
f2=fopen(argv[3],"r");

if(argc!=5)
{
printf("\nInvalid arguments\n");
exit(1);
}

//Coverting character to integer in the first file

while(!feof(f1))
{
   fscanf(f1,"%c",&a);
   *ip=a-48;
   ip++;
   ctr1++;
}

//converting character to integer in the second file

while(!feof(f2))
{
   fscanf(f2,"%c",&a2);
   *ip2=a2-48;
   ip2++;
   ctr2++;
}

int l,k;

block=atoi(argv[1]);
k=block;
int bsize;
bsize=block;
node *start1,*temp1;
node *result=NULL;
start1 = (node *)malloc(sizeof(node));


  for(i=ctr1-1;i>=0;i=i-k)
   {
     int num=0;
    l=k-1;
   while(l>=0)
   {
   if((i-l)>=0)
   {
    num=num+(num1[i-l]*pow(10,l));
    }
   l=l-1;
   }
   insert_at_tail(start1,num);
  }

//Printing the two linked lists

  int l2;
  node *start2,*temp2;
  start2 = (node *)malloc(sizeof(node));
  temp2 = start2;
  temp2 -> next = NULL;


for(i=ctr2-1;i>=0;i=i-k)
   {
     int numx=0;
    l2=k-1;
   while(l2>=0)
   {
   if((i-l2)>=0)
    {
    numx=numx+(num2[i-l2]*pow(10,l2));
    }
   l2=l2-1;
   }
  insert_at_tail(start2,numx);
  }


 fclose(f1);
 fclose(f2);
node *sl,*dl;
char *c;
int la,lb;
sl=(node *)malloc(sizeof(node));
dl=(node *)malloc(sizeof(node));
sl=sum_list(start1->next,start2->next,k);                //s1 points to the first element of the sum list
dl=diff_list(start1->next,start2->next,k);               //d1 points to the first element of the difference list
Insert_at_head(sl->next);
printf("\n");
Insert_at_head(sl->next);
printf("\n");
node *sum_rev;
node *diff_rev;
sum_rev=reverse(sl);                                      //reversing the sum list
diff_rev=reverse(dl);                                     //reversing the difference list
outputfile(sum_rev,diff_rev,argv[4]);                   //storing the sum,difference and the block operations in an output file
d=mulply(ss,ds);
outputfile(sum_rev,diff_rev,argv[4]);                   //storing the sum,difference and the block operations in an output file
printf("\n");
printf("\n");
FILE *f3;
f3=fopen(argv[4],"w");
fseek(f3,1000,SEEK_SET);
fprintf(f3,"\n%s",d);
printf("\n");
return 1;

}

