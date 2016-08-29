/* Simple Tic Tac Toe Game */

#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
using namespace std;

void gotoRowCol(int rpos, int cpos)
{
    int xpos=cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}


void clrscr()
{
    gotoRowCol(0,0);
    for(int ri=0; ri<42; ri++)
    {
        for(int ci=0; ci<84; ci++)
        {
            cout<<" ";
        }
    }

    gotoRowCol(0,0);
}

void PrintGrid(int r,int c,int dim,char s)
{
    for(int ri=dim; ri<dim*dim; ri+=dim)
    {
        for(int ci=0; ci<=dim*dim; ci++)
        {
            gotoRowCol(ri,ci);
            cout<<s;
        }
    }
    for (int ci=dim; ci<dim*dim; ci+=dim)
    {
        for(int ri=0; ri<=dim*dim; ri++)
        {
            gotoRowCol(ri,ci);
            cout<<s;
        }
    }
}

void PrintScreen(int B[],int dim)
{
    system("cls");
    int R=dim/2+1,C=(dim/2);
    for (int x=1; x<=dim; x++)
    {
        for (int y=1; y<=dim; y++)
        {
            gotoRowCol(R,C);
            cout<<B[(x-1)*dim+(y-1)];
            C+=dim;
        }
        R+=dim;
        C=(dim/2);
    }
}

int TakeInput(int &r,int &c,int Turn)
{
    cout<< "\nEnter Player "<<Turn<< " Co-ordinates (x and y):";
    cin>>r>>c;
}

bool Validate(int r,int c,int B[],int dim)
{
    return B[(r-1)*dim+c-1]==0;
}
void  Write_on_Board(int r,int c,int B[],int dim,int Turn)
{
    B[(r-1)*dim+c-1]=Turn;
}

int  TwoD_to_OneD(int r,int c,int B[],int dim)
{
    return B[(r-1)*dim+c-1];
}

int  Win(int B[],int dim,int turn)
{
    int counter=0;
    for (int x=1; x<=dim; x++)
    {
        counter=0;
        for(int i=1; i<=dim; i++)
        {
            if (TwoD_to_OneD(x,i,B,dim)==turn)
            {
                counter++;
            }
            if (counter==dim)
            {
                return counter;
            }
        }

    }
    for (int x=1; x<=dim; x++)
    {
        counter=0;
        for(int i=1; i<=dim; i++)
        {
            if (TwoD_to_OneD(i,x,B,dim)==turn)
            {
                counter++;
            }
            if (counter==dim)
            {
                return counter;
            }
        }

    }
    counter=0;
    for (int x=1; x<=dim; x++)
    {
        if (TwoD_to_OneD(x,x,B,dim)==turn)
        {
            counter++;
        }

        if (counter==dim)
        {
            return counter;
        }



    }
    counter=0;
    for (int x=1; x<=dim; x++)
    {
        if (TwoD_to_OneD(x,dim-x+1,B,dim)==turn)
        {
            counter++;
        }

        if (counter==dim)
        {
            return counter;
        }
    }
}

bool Draw(int r ,int c,int B[],int dim,int turn)
{
    for(int i=1; i<=dim; i++)
    {
        for(int x=1; x<=dim; x++)
        {
            if(TwoD_to_OneD(i,x,B,dim)==0)
            {
                return false;
            }

        }
    }
    return true;
}

int TurnChange(int & Turn)
{
    if(Turn==1)
    {
        Turn=2;
    }
    else if (Turn==2)
    {
        Turn=1;
    }
    return Turn;
}

int main()
{
    system("mode 300,300");
    const int dim=3;
    int B[dim*dim]= {0};
    int r=0,c=0;
    char s=-80;
    int Is_Turn_Changed=1;
    int Turn=1;

    do
    {

        PrintGrid(r,c,dim,s);
        TakeInput(r,c,Turn);
        if(Validate(r,c,B,dim)==true&&r<=dim&&c<=dim)
        {
            Write_on_Board(r,c,B,dim,Turn);

        }
        else
        {
            system("cls");
            cout<<"Wrong Input!Input again...";
            cout<<"\nPress Any Key To Enter Again...";
            getch();
            system("cls");
            PrintScreen(B,dim);
            continue;
        }
        PrintScreen(B,dim);
        PrintGrid(r,c,dim,s);
        if (Win(B,dim,Turn)==dim)
        {
            cout<<endl<<"\nPlayer "<<Turn<<" Wins!!!";
            Is_Turn_Changed=2;
        }
        else if (Draw(r,c,B,dim,Turn)==true)
        {
            cout<<endl<<"\nGame Over!!!";
            Is_Turn_Changed=3;
        }
        TurnChange(Turn);

    }
    while(Is_Turn_Changed==1);
    getch();
    return 0;
}
