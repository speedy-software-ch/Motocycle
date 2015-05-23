#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <windows.h>

/*
 PLEASE NOTE: the program will require SDL.dll which is located in
              dev-c++'s dll directory. You have to copy it to you
			  program's home directory or the path.
 */

/* The screen surface */
SDL_Surface *screen = NULL; //Main Screen Buffer
SDL_Surface *Background = NULL;  //Background Surface
SDL_Surface *SG = NULL;  //Start Game Menu Item Surface
SDL_Surface *Credits = NULL;  //Credits  Menu Item Surface
SDL_Surface *Quit = NULL;  //Quit Menu Item Surface
SDL_Surface *MP = NULL;   //Selection Point Surface
SDL_Surface *Info = NULL;  //Credits Background Surface
SDL_Surface *Subtitles = NULL;  //Credits Text Surface
SDL_Surface *BG = NULL;  //Street Background Surface
SDL_Surface *Panel = NULL;  //Panel Surface
SDL_Surface *Line = NULL;   //Street Line Surface
SDL_Surface *RS = NULL;   //Street Border Surface

int Status = 0;
int mode = 0;
int scroll=400;
int AS = 0;
int delay_AS = 0;
int sscroll = 0;
int LineH=-150;
int v=0;


/* This function draws to the screen; replace this with your own code! */
void LoadBitmaps();

void LoadBitmaps()
{
     Background = SDL_LoadBMP("BG.tsb");
     SG = SDL_LoadBMP("M11.bmp");
     Credits = SDL_LoadBMP("M21.bmp");
     Quit = SDL_LoadBMP("M31.bmp");
     MP = SDL_LoadBMP("Menup.bmp");
     Info = SDL_LoadBMP("Info.bmp");
     Subtitles = SDL_LoadBMP("Subtitles.bmp");
     Panel = SDL_LoadBMP("Panel.bmp");
     BG = SDL_LoadBMP("SG/1.bmp");
     RS = SDL_LoadBMP("RS.bmp");
     Line = SDL_LoadBMP("RSR.bmp");
     Line->w =  0;
     Line->h = 0;
 }
 
 void DrawIMG(SDL_Surface *img, int x, int y);
 
 void DrawIMG(SDL_Surface *img, int x, int y)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_BlitSurface(img, NULL, screen, &dest);
}

int main (int argc, char *argv[])
{
    char *msg;
    int done;

    /* Initialize SDL */
    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        sprintf (msg, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        MessageBox (0, msg, "Error", MB_ICONHAND); 
        free (msg);
        exit (1);
    }
    atexit (SDL_Quit);

    /* Set 800x600 32-bits video mode */
    screen = SDL_SetVideoMode (800, 600, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    if (screen == NULL)
    {
        sprintf (msg, "Couldn't set 800x600x32 video mode: %s\n",
          SDL_GetError ());
        MessageBox (0, msg, "Error", MB_ICONHAND); 
        free (msg);
        exit (2);
    }
    SDL_WM_SetCaption ("Tetris Game", NULL);
        LoadBitmaps();
    done = 0;
    while (!done)
    {
        SDL_Event event;
        if(mode==0)
        {
        DrawIMG(Background,0,0);
        SDL_SetColorKey(SG, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(SG->format, 255, 255, 255));
                           DrawIMG(SG,200,200);
        SDL_SetColorKey(Credits, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Credits->format, 255, 255, 255));                   
                           DrawIMG(Credits,200,280);
                           
                           SDL_SetColorKey(Quit, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Quit->format, 255, 255, 255));
                           DrawIMG(Quit,200,330);
                           SDL_SetColorKey(MP, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(MP->format, 255, 255, 255));
                           DrawIMG(MP,150,(Status*50)+210);
                           }
        /* Check for events */
        while (SDL_PollEvent (&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                 if ( event.key.keysym.sym == SDLK_ESCAPE ) { if(mode==0) { Status = 2; } else { mode=0 ;} }
                 if ( event.key.keysym.sym == SDLK_RIGHT ) { v=v-40; }
                 if ( event.key.keysym.sym == SDLK_LEFT ) { v=v+140; }
                 if ( event.key.keysym.sym == SDLK_DOWN ) { if(Status<2) { Status++; } else { Status=0; } }
                 if ( event.key.keysym.sym == SDLK_UP) { if(Status>0) { Status--; } else {Status=2; } }
                 if ( event.key.keysym.sym == SDLK_RETURN) { if(Status==1) { mode = 1; } if(Status==2) {done = 1; } if(Status==0) { mode=2; } }
                break;                    
            case SDL_QUIT:
                done = 1;
                break;
            default:
                break;
            }

            
        }
        if(mode==2)
        {
                   if(LineH<600)
                   {
                DrawIMG(BG,0,0);
                SDL_SetColorKey(Line, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Line->format, 255, 0, 0));
                DrawIMG(Line,v,LineH);
                LineH=LineH+40;
                Line->w = Line->w + 13;
                Line->h = Line->h + 13;
                }
                else
                {
                    Line->w = 0;
                    Line->h = 0;
                    LineH=-150;
                    }
                    SDL_SetColorKey(RS, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(RS->format, 255, 0, 0));
                    DrawIMG(RS,v+200,LineH-400);
                SDL_SetColorKey(Panel, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Panel->format, 255, 0, 0));
                DrawIMG(Panel,0,200);                    
                   }
                    if(mode==1)
            {
                       DrawIMG(Info,0,0);
                       scroll=scroll-4;
                       SDL_SetColorKey(Subtitles, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Subtitles->format, 255, 255, 255));
                       DrawIMG(Subtitles,-50,scroll);
                       }
        SDL_Flip(screen);
    }
    return 0;
}
