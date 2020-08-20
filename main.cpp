#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <string>
#include<bits/stdc++.h>
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
int X1,X2,Y1,Y2,XC1,YC1,XC2,YC2,XC3,YC3,XC4,YC4;
double a,b;
struct point
{
    int x,y;
};
vector<string> arr;
vector<point> pixles;
void addToPixels(int x,int y)
{
    point p;
    p.x=x;
    p.y=y;
    pixles.push_back(p);
}
static int counter=0;
int roundd(double j)
{
    return (int)(j+.5);
}
bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

vector<point> SeplinsVec;
void DrawLineParamtric(HDC hdc,int x1,int y1, int x2, int y2,COLORREF c)
{
    counter++;
    std::string str ="DrawLineParamtric "+std::to_string(x1)+" "+std::to_string(y1)+" "+std::to_string(x2)+" "+std::to_string(y2);
    arr.push_back(str);
    for(double t=0; t<=1; t+=0.001)
    {
        int x=roundd(x1+(t*(x2-x1)));
        int y=roundd(y1+(t*(y2-y1)));
        addToPixels(x,y);
        SetPixel(hdc,x,y,c);
    }
}
void DrawLineIntDDA(HDC hdc,int x1,int y1,int x2, int y2,COLORREF c)
{
    counter++;
    std::string str ="DrawLineIntDDA "+std::to_string(x1)+" "+std::to_string(y1)+" "+std::to_string(x2)+" "+std::to_string(y2);
    arr.push_back(str);
    int x=x1;
    int y=y1;
    int dx=x2-x1;
    int dy=y2-y1;
    int e=(2*dy)-dx;
    addToPixels(x1,y1);
    SetPixel(hdc,x1,y1,c);
    while(x<x2)
    {
        x++;
        if(e>=0)
        {
            y++;
            e-=2*dx;
        }
        e+=2*dy;
        addToPixels(x,y);
        SetPixel(hdc,x,y,c);
    }
}
void DrawLineMidPoint(HDC hdc,int x1,int y1, int x2, int y2,COLORREF c)
{
    counter++;
    std::string str ="DrawLineMidPoint "+std::to_string(x1)+" "+std::to_string(y1)+" "+std::to_string(x2)+" "+std::to_string(y2);
    arr.push_back(str);
    int x=x1;
    int y=y1;
    int dx=x2-x1;
    int dy=y2-y1;
    int d=dx-(2*dy);
    int d1=(2*dx)-(2*dy);
    int d2=-(2*dy);
    addToPixels(x,y);
    SetPixel(hdc,x,y,c);
    while(x<x2)
    {
        if(d<=0)
        {
            x++;
            y++;
            d+=d1;
        }
        else
        {
            x++;
            d+=d2;
        }
        addToPixels(x,y);
        SetPixel(hdc,x,y,c);
    }
}
void drawellipseDirect(HDC hdc,int xc,int yc,int a,int b,COLORREF c)
{
    counter++;
    std::string str ="drawellipseDirect "+std::to_string(xc)+" "+std::to_string(yc)+" "+std::to_string(a)+" "+std::to_string(b);
    arr.push_back(str);
    for(double q=0; q<=6.2857; q+=0.001)
    {

        int x=roundd(xc+a*cos(q));
        int y=roundd(yc+b*sin(q));
        addToPixels(x,y);
        SetPixel(hdc,x,y,c);
    }
}
void draw4points(HDC hdc,int xc,int yc,int x,int y,COLORREF c)
{
    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc-x,yc-y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    addToPixels(xc+x,yc+y);
    addToPixels(xc-x,yc+y);
    addToPixels(xc-x,yc-y);
    addToPixels(xc+x,yc-y);
}
void DrawellipseMidpoint(HDC hdc,int xc,int yc,int rx,int ry,COLORREF c)
{
    counter++;
    std::string str ="DrawellipseMidpoint "+std::to_string(xc)+" "+std::to_string(yc)+" "+std::to_string(rx)+" "+std::to_string(ry);
    arr.push_back(str);

    int x=0,y=ry;
    //double d=1-r;
    double p=pow(ry,2)+pow(rx,2)/4-pow(rx,2)*pow(ry,1);
    draw4points(hdc,xc,yc,x,y,c);
    while((2*x*ry*ry)<(2*y*rx*rx))
    {
        draw4points(hdc,xc,yc,x,y,c);
        if(p<0)
        {
            x=x+1;
            p=p+(2*ry*ry*x)+(ry*ry);
        }
        else
        {
            x=x+1;
            y=y-1;
            p=p+(2*ry*ry*x+ry*ry)-(2*rx*rx*y);
        }
    }
    p=((float)x+0.5)*((float)x+0.5)*ry*ry+(y-1)*(y-1)*rx*rx-rx*rx*ry*ry;

    while(y>=0)
    {
        draw4points(hdc,xc,yc,x,y,c);

        if(p>0)
        {
            y=y-1;
            p=p-(2*rx*rx*y)+(rx*rx);

        }
        else
        {
            y=y-1;
            x=x+1;
            p=p+(2*ry*ry*x)-(2*rx*rx*y)-(rx*rx);
        }
    }
}
void drawellipsePolar(HDC hdc,int xc,int yc,int a,int b,COLORREF c)
{
    counter++;
    std::string str ="drawellipsePolar "+std::to_string(xc)+" "+std::to_string(yc)+" "+std::to_string(a)+" "+std::to_string(b);
    arr.push_back(str);
    double x=a, y=0;
    draw4points(hdc,xc,yc,x,y,c);
    while(x>0)
    {
        x--;
        y=sqrt((b*b)-(((x*x)*(b*b))/(a*a)));
        draw4points(hdc,xc,yc,x,y,c);
    }
}
void hermite(HDC hdc,point p1,point p4,point r1,point r4,COLORREF c)
{
    counter++;
    std::string str ="hermite "+std::to_string(p1.x)+" "+std::to_string(p1.y)+" "+std::to_string(p4.x)+" "+std::to_string(p4.y)+" "+std::to_string(r1.x)+" "+std::to_string(r1.y)+" "+std::to_string(r4.x)+" "+std::to_string(r4.y);
    arr.push_back(str);
    float x,y,t;
    for(t=0.0; t<=1.0; t+=.001)
    {
        x=roundd((2*t*t*t-3*t*t+1)*p1.x+(-2*t*t*t+3*t*t)*p4.x+(t*t*t-2*t*t+t)*r1.x+(t*t*t-t*t)*r4.x);
        y=roundd((2*t*t*t-3*t*t+1)*p1.y+(-2*t*t*t+3*t*t)*p4.y+(t*t*t-2*t*t+t)*r1.y+(t*t*t-t*t)*r4.y);
        addToPixels(x,y);
        SetPixel(hdc,x,y,c);
    }
}
void bezier(HDC hdc,point p1,point p4,point r1,point r4,COLORREF c)
{
    counter++;
    std::string str ="bezier "+std::to_string(p1.x)+" "+std::to_string(p1.y)+" "+std::to_string(p4.x)+" "+std::to_string(p4.y)+" "+std::to_string(r1.x)+" "+std::to_string(r1.y)+" "+std::to_string(r4.x)+" "+std::to_string(r4.y);
    arr.push_back(str);
    float x,y,t;
    for(t=0.0; t<=1.0; t+=.001)
    {
        x=roundd((-1*t*t*t+3*t*t-3*t+1)*p1.x+(-3*t*t*t+3*t*t)*r1.x+(3*t*t*t-6*t*t+3*t)*p4.x+(t*t*t)*r4.x);
        y=roundd((-1*t*t*t+3*t*t-3*t+1)*p1.y+(-3*t*t*t+3*t*t)*r1.y+(3*t*t*t-6*t*t+3*t)*p4.y+(t*t*t)*r4.y);
        addToPixels(x,y);
        SetPixel(hdc,x,y,c);
    }
}
void Splines(HDC hdc,point p1,point p2,point p3,COLORREF c)
{
   counter++;
    std::string str ="Splines "+std::to_string(p1.x)+" "+std::to_string(p1.y)+" "+std::to_string(p2.x)+" "+std::to_string(p2.y)+" "+std::to_string(p3.x)+" "+std::to_string(p3.y);
    arr.push_back(str);
    float x,y,t;
    for(t=0.0; t<=1.0; t+=.001)
    {
        x=roundd((2*t*t-3*t+1)*p1.x+(-4*t*t+4*t)*p2.x+(2*t*t-1*t)*p3.x);
        y=roundd((2*t*t-3*t+1)*p1.y+(-4*t*t+4*t)*p2.y+(2*t*t-1*t)*p3.y);
        addToPixels(x,y);
        SetPixel(hdc,x,y,c);
    }

}
void SplinesVector(HDC hdc,vector<point> points,COLORREF c)
{
    for(int i=1;i<points.size()-1;i+=2)
    {
        Splines(hdc,points[i],points[i+1],points[i+2],c);
    }
}
union OutCode.
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};
OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)
        out.left=1;
    else if(x>xright)
        out.right=1;
    if(y>ytop)
        out.top=1;
    else if(y<ybottom)
        out.bottom=1;
    return out;
}
pair<int, int> VIntersect(double xs,double ys,double xe,double ye,int x,double &xi,double &yi)
{
    pair<int,int> p;
    xi=x;
    yi=ys+(x-xs)*(ye-ys)/(xe-xs);
    p.first=xi;
    p.second=yi;
    return p;
}
pair<int, int> HIntersect(double xs,double ys,double xe,double ye,int y,double &xi,double &yi)
{
    pair<int,int> p;
    yi=y;
    xi=xs+(y-ys)*(xe-xs)/(ye-ys);
    p.first=xi;
    p.second=yi;
    return p;
}
void CohenSuth(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom,COLORREF C)
{
    counter++;
    std::string str ="CohenSuth "+std::to_string(xs)+" "+std::to_string(ys)+" "+std::to_string(xe)+" "+std::to_string(ye)+" "+std::to_string(xleft)+" "+std::to_string(ytop)+" "+std::to_string(xright)+" "+std::to_string(ybottom);
    arr.push_back(str);
    double x1=xs,y1=ys,x2=xe,y2=ye;
    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        pair<int, int> point;
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)
                point = VIntersect(x1,y1,x2,y2,xleft, xi, yi);
            else if(out1.top)
                point = HIntersect(x1,y1,x2,y2,ytop, xi, yi);
            else if(out1.right)
                point = VIntersect(x1,y1,x2,y2,xright, xi, yi);
            else
                point = HIntersect(x1,y1,x2,y2,ybottom, xi, yi);
            x1=point.first;
            y1=point.second;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)
                point = VIntersect(x1,y1,x2,y2,xleft,xi,yi);
            else if(out2.top)
                point = HIntersect(x1,y1,x2,y2,ytop,xi,yi);
            else if(out2.right)
                point = VIntersect(x1,y1,x2,y2,xright,xi,yi);
            else
                point = HIntersect(x1,y1,x2,y2,ybottom,xi,yi);
            x2=point.first;
            y2=point.second;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All)
    {
        DrawLineParamtric(hdc,x1,y1,x2,y2,C);
    }
}
void loadLog(HDC hdc)
{
    COLORREF c=RGB(0,0,0);
    ifstream file;
    string str;
    file.open("saved.txt");
    int counterin=0;

    if(file.is_open())
    {
        //getline(file,str,'|');
        // arr.push_back(str);
        //counterin++;
        while(!file.eof())
        {
            getline(file,str,'|');
            if(!str.empty())
                arr.push_back(str);
            counterin++;
        }


        file.close();
        remove("saved.txt");
//arr.push_back("DrawLineParamtric 60 76 155 150");
//arr.push_back("drawellipseDirect 194 59 235 157");
        for(int i=0; i<counterin-1; i++)
        {
            string row=arr[i];
            stringstream ssin(row);
            std::vector<string> arrstr((istream_iterator<std::string>(ssin)),
                                       istream_iterator<std::string>());
            if(arrstr[0]=="DrawLineParamtric")
            {
                DrawLineParamtric(hdc,std::stoi(arrstr[1]),std::stoi(arrstr[2]),std::stoi(arrstr[3]),std::stoi(arrstr[4]),c);
            }
            else if(arrstr[0]=="DrawLineIntDDA")
            {
                DrawLineIntDDA(hdc,std::stoi(arrstr[1]),std::stoi(arrstr[2]),std::stoi(arrstr[3]),std::stoi(arrstr[4]),c);
            }
            else if(arrstr[0]=="DrawLineMidPoint")
            {
                DrawLineMidPoint(hdc,std::stoi(arrstr[1]),std::stoi(arrstr[2]),std::stoi(arrstr[3]),std::stoi(arrstr[4]),c);
            }
            else if(arrstr[0]=="drawellipseDirect")
            {
                drawellipseDirect(hdc,std::stoi(arrstr[1]),std::stoi(arrstr[2]),std::stoi(arrstr[3]),std::stoi(arrstr[4]),c);
            }
            else if(arrstr[0]=="DrawellipseMidpoint")
            {
                DrawellipseMidpoint(hdc,std::stoi(arrstr[1]),std::stoi(arrstr[2]),std::stoi(arrstr[3]),std::stoi(arrstr[4]),c);
            }
            else if(arrstr[0]=="drawellipsePolar")
            {
                drawellipsePolar(hdc,std::stoi(arrstr[1]),std::stoi(arrstr[2]),std::stoi(arrstr[3]),std::stoi(arrstr[4]),c);
            }
            else if(arrstr[0]=="bezier")
            {
                point p1;
                p1.x=stoi(arrstr[1]);
                p1.y=stoi(arrstr[2]);
                point p4;
                p4.x=stoi(arrstr[3]);
                p4.y=stoi(arrstr[4]);
                point r1;
                r1.x=stoi(arrstr[5]);
                r1.y=stoi(arrstr[6]);
                point r4;
                r4.x=stoi(arrstr[7]);
                r4.y=stoi(arrstr[8]);
                bezier(hdc,p1,p4,r1,r4,c);
            }
            else if(arrstr[0]=="hermite")
            {
                point p1;
                p1.x=stoi(arrstr[1]);
                p1.y=stoi(arrstr[2]);
                point p4;
                p4.x=stoi(arrstr[3]);
                p4.y=stoi(arrstr[4]);
                point r1;
                r1.x=stoi(arrstr[5]);
                r1.y=stoi(arrstr[6]);
                point r4;
                r4.x=stoi(arrstr[7]);
                r4.y=stoi(arrstr[8]);
                hermite(hdc,p1,p4,r1,r4,c);
            }
            else if(arrstr[0]=="CohenSuth")
            {
                int xs=stoi(arrstr[1]);
                int ys=stoi(arrstr[2]);
                int xe=stoi(arrstr[3]);
                int ye=stoi(arrstr[4]);
                int xleft=stoi(arrstr[5]);
                int ytop=stoi(arrstr[6]);
                int xright=stoi(arrstr[7]);
                int ybottom=stoi(arrstr[8]);
                CohenSuth(hdc,xs,ys,xe,ye,xleft,ytop,xright,ybottom,c);
            }
            else if(arrstr[0]=="Splines")
            {
                point p1;
                p1.x=stoi(arrstr[1]);
                p1.y=stoi(arrstr[2]);
                point p2;
                p2.x=stoi(arrstr[3]);
                p2.y=stoi(arrstr[4]);
                point p3;
                p3.x=stoi(arrstr[5]);
                p3.y=stoi(arrstr[6]);
                Splines(hdc,p1,p2,p3,c);
            }

        }
    }
    //saveLog();
}
void loadPixles(HDC hdc)
{
    vector<string>streamPixles;
    COLORREF c=RGB(0,0,0);
    ifstream file;
    string str;
    file.open("Pixels.txt");
    int counterin=0;
    if(file.is_open())
    {
        while(!file.eof())
        {
            getline(file,str,'|');
            if(!str.empty())
            {
                streamPixles.push_back(str);
            }
            counterin++;
        }
       file.close();
    for(int i=0;i<counterin-1;i++)
    {
        string row=streamPixles[i];
        stringstream ssin(row);
        std::vector<string> arrstr((istream_iterator<std::string>(ssin)),istream_iterator<std::string>());
        SetPixel(hdc,std::stoi(arrstr[0]),std::stoi(arrstr[1]),c);
    }
    streamPixles.clear();
    }
}
void savePixels()
{
    ofstream file;
    file.open("Pixels.txt");
    if(!file)
    {
      cout<<"Error in creating file.."<<endl;
    }
    cout<<"\nFile created successfully."<<endl;
    for (point &p : pixles)
    {
        file << p.x<<' '<<p.y<< '|';
    };
    file.close();
    cout<<"\nFile saved and closed succesfully."<<endl;
}
bool flagsOfFunctions[15];
void setFlags(int num)
{
    for(int i=0; i<15; i++)
    {
        if(i==num)
            flagsOfFunctions[i]=true;
        else
            flagsOfFunctions[i]=false;
    }
}
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
/*  This function is called by the Windows function DispatchMessage()  */
void saveLog()
{
    ofstream file;
    file.open("saved.txt");
    for (string &s : arr)
    {
        file << s << "|";
    };
    file.close();
}
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int counter = 0;
    HDC hdc=GetDC(hwnd);
    static int oldx1,oldx2,oldy1,oldy2;
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
    {
        HMENU hmenubar= CreateMenu();
        HMENU hline=CreateMenu();
        HMENU hellipse=CreateMenu();
        HMENU hcurve=CreateMenu();
        HMENU hopperation=CreateMenu();
        HMENU herase=CreateMenu();
        //HMENU save=CreateMenu();
        AppendMenu(hmenubar,MF_POPUP,(UINT_PTR)hline,"Line");
        AppendMenu(hmenubar,MF_POPUP,(UINT_PTR)hellipse,"Ellipse");
        AppendMenu(hmenubar,MF_POPUP,(UINT_PTR)hcurve,"Curve");
        AppendMenu(hmenubar,MF_POPUP,12,"Clipping");
        AppendMenu(hmenubar,MF_POPUP,(UINT_PTR)hopperation,"Operations");
        AppendMenu(hmenubar,MF_POPUP,(UINT_PTR)herase,"erase");

        AppendMenu(hline,MF_STRING,1,"Parametric");
        AppendMenu(hline,MF_STRING,2,"DDA");
        AppendMenu(hline,MF_STRING,3,"Mid Point");

        AppendMenu(hellipse,MF_STRING,4,"Direct");
        AppendMenu(hellipse,MF_STRING,5,"Polar");
        AppendMenu(hellipse,MF_STRING,6,"Mid Point");

        AppendMenu(hcurve,MF_STRING,7,"Bezier");
        AppendMenu(hcurve,MF_STRING,8,"Hermite");
        AppendMenu(hcurve,MF_STRING,9,"Splines");

        AppendMenu(hopperation,MF_STRING,10,"Save");
        AppendMenu(hopperation,MF_STRING,11,"Load");
        AppendMenu(hopperation,MF_STRING,13,"Load by Pixels");

        AppendMenu(herase,MF_STRING,14,"Erase");
        AppendMenu(herase,MF_STRING,15,"Erase and Save");


        SetMenu(hwnd,hmenubar);
        break;
    }
    case WM_COMMAND:
        switch(wParam)
        {
        case 1:
        {
            setFlags(0);
            break;
        }
        case 2:
        {
            setFlags(1);
            break;
        }
        case 3:
        {
            setFlags(2);
            break;
        }
        case 4:
        {
            setFlags(3);
            break;
        }
        case 5:
        {
            setFlags(4);
            break;
        }
        case 6:
        {
            setFlags(5);
            break;
        }
        case 7:
        {
            setFlags(6);
            break;
        }
        case 8:
        {
            setFlags(7);
            break;
        }
        case 9:
        {
            setFlags(8);
            break;
        }
        case 10:
        {
            setFlags(9);
            break;
        }
        case 11:
        {
            setFlags(10);
            break;
        }
        case 12:
        {
            setFlags(11);
            break;
        }
        case 13:
        {
            setFlags(12);
            break;
        }
         case 14:
        {
            setFlags(13);
            break;
        }
         case 15:
        {
            setFlags(14);
            break;
        }

        }
    case WM_LBUTTONDOWN:
    {
        X1=LOWORD(lParam);
        Y1=HIWORD(lParam);
        if (counter != 0)
            break;

        break;
    }
    case WM_LBUTTONUP:
        X2=LOWORD(lParam);
        Y2=HIWORD(lParam);
        a=roundd(sqrt(pow(X2-X1,2.0)+pow(Y2-Y1,2.0)));
        b= ((3/4.0)*a);
        hdc=GetDC(hwnd);
        if(flagsOfFunctions[0]==true)
        {
            DrawLineParamtric(hdc,X1,Y1,X2,Y2,RGB(0,0,0));
        }
        else if(flagsOfFunctions[1]==true)
        {
            DrawLineIntDDA(hdc,X1,Y1,X2,Y2,RGB(0,0,0));
        }
        else if(flagsOfFunctions[2]==true)
        {
            DrawLineMidPoint(hdc,X1,Y1,X2,Y2,RGB(0,0,0));
        }
        else if(flagsOfFunctions[3]==true)
        {
            drawellipseDirect(hdc,X1,Y1,a,b,RGB(0,0,0));
        }
        else if(flagsOfFunctions[4]==true)
        {
            drawellipsePolar(hdc,X1,Y1,a,b,RGB(0,0,0));
        }
        else if(flagsOfFunctions[5]==true)
        {
            DrawellipseMidpoint(hdc,X1,Y1,a,b,RGB(0,0,0));
        }
        else if(flagsOfFunctions[9]==true)
        {
            cout<<"hello save"<<endl;
            saveLog();
            savePixels();
            cout<<"bye save"<<endl;
        }
        else if(flagsOfFunctions[10]==true)
        {
            cout<<"hello load"<<endl;
            loadLog(hdc);
            cout<<"bye load"<<endl;
        }
        else if(flagsOfFunctions[12]==true)
        {
            cout<<"hello load pixels"<<endl;
            loadPixles(hdc);
            cout<<"bye load pixels"<<endl;
        }
         else if(flagsOfFunctions[13]==true)
        {
            arr.clear();
            pixles.clear();
            InvalidateRect(hwnd,NULL,TRUE);
        }
         else if(flagsOfFunctions[14]==true)
        {
            saveLog();
            savePixels();
            InvalidateRect(hwnd,NULL,TRUE);
        }
        else if(flagsOfFunctions[11]==true)
        {
            if(counter==0)
            {
                DrawLineParamtric(hdc, X1, Y1, X1, Y2, COLORREF(RGB(0, 0, 0)));
                DrawLineParamtric(hdc, X1, Y1, X2, Y1, COLORREF(RGB(0, 0, 0)));
                DrawLineParamtric(hdc, X1, Y2, X2, Y2, COLORREF(RGB(0, 0, 0)));
                DrawLineParamtric(hdc, X2, Y1, X2, Y2, COLORREF(RGB(0, 0, 0)));
                oldx1=X1;
                oldx2=X2;
                oldy1=Y1;
                oldy2=Y2;
            }
        }
        ReleaseDC(hwnd,hdc);
        if (counter != 0)
            break;
        counter = 1;
        break;
    case WM_LBUTTONDBLCLK:
        if(counter == 1)
        {
            XC1 = LOWORD(lParam);
            YC1 = HIWORD(lParam);
            counter++;
        }
        else if(counter == 2)
        {
            XC2 = LOWORD(lParam);
            YC2 = HIWORD(lParam);
            counter++;
        }
        else if(counter == 3)
        {
            XC3 = LOWORD(lParam);
            YC3 = HIWORD(lParam);
            counter++;
        }
        printf("Counter = %d\n", counter);
        if(counter == 4)
        {
            XC4=LOWORD(lParam);
            YC4=HIWORD(lParam);
            hdc = GetDC(hwnd);
            point w1;
            w1.x=XC1;
            w1.y=YC1;
            point w2;
            w2.x=XC2;
            w2.y=YC2;
            point w3;
            w3.x=XC3;
            w3.y=YC3;
            point w4;
            w4.x=XC4;
            w4.y=YC4;
            SeplinsVec.push_back(w1);
            SeplinsVec.push_back(w2);
            SeplinsVec.push_back(w3);
            if(flagsOfFunctions[6]==true)
            {
                bezier(hdc,w1,w2,w3,w4,RGB(0,0,0));
            }
            else if(flagsOfFunctions[7]==true)
            {
                hermite(hdc,w1,w2,w3,w4,RGB(0,0,0));
            }
             else if(flagsOfFunctions[8]==true)
            {
                //Splines(hdc,w1,w2,w3,RGB(0,0,0));
                SplinesVector(hdc,SeplinsVec,RGB(0,0,0));
            }
            else if(flagsOfFunctions[11]==true)
            {
                cout<<"believer"<<endl;
                CohenSuth(hdc,XC1,YC1,XC2,YC2,oldx1,oldy2,oldx2,oldy1,RGB(0,0,0));
                CohenSuth(hdc,XC1,YC1,XC3,YC3,oldx1,oldy2,oldx2,oldy1,RGB(0,0,0));
                CohenSuth(hdc,XC3,YC3,XC2,YC2,oldx1,oldy2,oldx2,oldy1,RGB(0,0,0));
            }
            counter = 1;
            ReleaseDC(hwnd,hdc);
        }
        break;
    case WM_DESTROY:
        //saveLog();
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
