#include <stdio.h>
#include <stdlib.h>

FILE *fout;
char *v;

void board(FILE* fout,int n,int m)
{
    fprintf(fout,"<rect x='%d' y='%d' width='200' height='200' fill='lime' stroke-width='4' stroke='pink' /> \n",n,m);
    fprintf(fout,"<polyline points='%d,%d %d,%d %d,%d %d,%d' stroke='red' stroke-width='4' fill='none' />\n",n+25,m+125,n+25,m+175,n+175,m+175,n+175,m+75);
    fprintf(fout,"<line x1='%d' y1='%d' x2='%d' y2='%d' stroke='black' stroke-width='4' />\n",n+25,m+25,n+175,m+175);
}

void disk(FILE* fout,int nr,int n,int m)
{
    if(nr==1)
        fprintf(fout,"<circle cx='%d' cy='%d' r='20' fill='purple' />",n,m);
    else if(nr==2)
        fprintf(fout,"<circle cx='%d' cy='%d' r='35' fill='orange' />",n,m);
    else if(nr==3)
        fprintf(fout,"<circle cx='%d' cy='%d' r='55' fill='red' />",n,m);
        else
        fprintf(fout,"<circle cx='%d' cy='%d' r='75' fill='blue' />",n,m);
}

void hanoi(int n,int m,int a,int b,int c)
{
    static int x=25,y=25+225,q=125,w=125+225;
    int aux;

    if(n==1)
    {
        board(fout,x,y);
        board(fout,x+225,y);
        board(fout,x+450,y);
        y+=225;
        v[n]=b;

        aux=m;
        while(aux!=0)
        {
            if(v[aux]==1)
            {
                q=125;
            }
            else if(v[aux]==2)
            {
                q=125+225;
            }
            else if(v[aux]==3)
            {
                q=125+450;
            }
            disk(fout,aux,q,w);
            aux--;
        }
        w+=225;
    }
    else
    {
        hanoi(n-1,m,a,c,b);


        board(fout,x,y);
        board(fout,x+225,y);
        board(fout,x+450,y);
        y+=225;

        v[n]=b;
        aux=m;

        while(aux!=0)
        {
            if(v[aux]==1)
            {
                q=125;
            }
            else if(v[aux]==2)
            {
                q=125+225;
            }
            else if(v[aux]==3)
            {
                q=125+450;
            }
            disk(fout,aux,q,w);
            aux--;
        }
        w+=225;

        hanoi(n-1,m,c,b,a);
    }
}

int main()
{
    int n,m,x,y,q,w,aux;

    fout=fopen("hanoi.svg","w");
    if(fout==NULL)
    {
        printf("Error on writing!\n");
        return -1;
    }

    v=malloc(5*sizeof(int));

    printf("Insert the number of disks here:");
    scanf("%d",&n);
    m=n;

    fprintf(fout,"<svg xmlns='http://www.w3.org/2000/svg' version='1.1' width='1000px' height='4500px' >\n");

    //first row
    x=25;
    y=25;
    q=125;
    w=125;
    board(fout,x,y);
    board(fout,x+225,y);
    board(fout,x+450,y);
    aux=m;
    while(aux!=0)
    {
        disk(fout,aux,q,w);
        v[aux]=1;
        aux--;
    }

    hanoi(n,m,1,3,2);
    fprintf(fout,"</svg>");
    fclose(fout);
    free(v);
    return 0;
}