/*
 *  Final Project
 *  3D rendering of the Sweet Cow Louisville Ice Cream Shop
 *  Nhi Nguyen
 *
 *  Help code provided by Willem A. (Vlakkies) Schreuder
 *
 *  Key bindings:
 * 0          Reset view angle
 * o or O     Open front door
 * a          Turn left in first person
 * w          Zoom in, in first person view
 * s          Zoom out, in first person view
 * d          Turn right in first person view
 * arrows     Change view angle (perspective/orthogonal)
 * m or M     Toggle perspective and orthogonal modes
 * f or F     View scene in first person perspective
 * +/-        Change field of view (FOV) angle (perspective)
 * PgDn/PgUp  Zoom in and out
 *  +/-        Change field of view angle
 * ' '        Toggle shadows
 * b or B     Jump to view ice cream freezer
 * ESC        Exit

 */
#include "CSCIx229.h"
typedef struct {float x,y,z;} Point;
//  Global variables
int          mode=1;    // Display mode
int fp=1;
int          obj=15;    // Display objects (bitmap)
int          move=0;    // Light movement
int          axes=0;    // Display axes
int          n=8;       // Number of slices
int          th=-30;    // Azimuth of view angle
int          ph=+30;    // Elevation of view angle
int viewth=15;    //  Azimuth of view angle
int viewph=20;    //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int          tex2d[46];  // Textures (names)
// int          move=1;    // Light movement
int          dt=50;     // Timer period (ms)
double       asp=1;     // Aspect ratio
double       dim=25;     // Size of world
int          zh=0;      // Light azimuth
float        Ylight=25;  // Elevation of light
float        Lpos[4];   // Light position
float        Lpos2[4];
unsigned int framebuf=0;// Frame buffer id
double       Svec[4];   // Texture planes S
double       Tvec[4];   // Texture planes T
double       Rvec[4];   // Texture planes R
double       Qvec[4];   // Texture planes Q
int          Width;     // Window width
int          Height;    // Window height
int          shadowdim; // Size of shadow map textures
int          shader;    // Shader
int shadows=1;
double y=0;
/* Eye coords */
double Ex = 13;
double Ey = 1.5;
double Ez = 24;
int rot = -15; //rotation var for first person
int door_open=0;
/* Camera looking coords
 * Don't need a y coord because up-down view cannot be altered in fp
 */
double Cx = 0;
double Cy = 0;
double Cz = 0;
char* text[]={"Shadows","Shadow Map"};

/*
 *  Set projection
 */
static void myProject()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if(fp) {
      gluPerspective(fov,asp,.01,4*dim);
   }
   else {
      if (mode)
         gluPerspective(fov,asp,dim/4,4*dim);
      //  Orthogonal projection
      else
         glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   }
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

void drawCylinder(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, int rail,int size, int seat, int rott, int blackk){//int tex) {
   float r;
   float b;
   float g;
   double radius = 0.25, height = 1;

   glPushMatrix();

   //  Transform cylinder
   glTranslated(x,y,z);
   if (rail==1){
   glRotated(th,0,0,1);
   glRotated(th,1,0,0);}
   else{
     glRotated(th,0,0,1);
     //glRotated(th,1,0,0);
   }

   glScaled(dx,dy,dz);
   if(seat==1){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[1]);
 }
 else if (seat==2){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[34]);
 }
 else if (seat==3){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[35]);
 }
 else if (seat==4){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[36]);
 }
 else if (seat==5){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[37]);
 }
 else if (seat==6){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[38]);
 }
 else if (seat==7){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[39]);
 }
 else if (seat==8){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[40]);
 }
 else if (seat==9){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[41]);
 }
 else if (seat==10){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[42]);
 }
 else if (seat==11){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[43]);
 }
 else if (seat==100){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[9]);
 }
 else if (seat==45){
   //  Enable textures
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[45]);
 }
 else{
   glEnable(GL_TEXTURE_2D);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,tex2d[4]);
 }

  double i;


  //glBindTexture(GL_TEXTURE_2D,tex2d[1]);
  if (blackk==1){
    r = b = g = 0.1;
  }
  else if(blackk==2){
    r = b = g = 1;
  }
  else if(blackk==3){
    r = b = g = 0.38;
  }
  else if(blackk==4){
    r=0.17;
    b=0.42;
    g=0.60;
  }
  else if(blackk==5){
    r=b=g=0.9;
  }
  else {
    r = b = g = 0.5;
  }
  glColor3f(r,b,g);
  glNormal3d(0,1,0);
  /* Top of Cylinder */
  glBegin(GL_TRIANGLE_FAN);
  glTexCoord2f(0.5,0.5);
  glVertex3d(0.0, height, 0.0);
     for(i = 0.0; i <= size; i+=10) {
        glTexCoord2f(0.5*Cos(i)+0.6, -0.5*Sin(i)+0.5);
        if(rott!=0){
        glVertex3d(radius * Cos(i-40), height, radius * Sin(i-40));}
        else{glVertex3d(radius * Cos(i), height, radius * Sin(i));}
     }
  glEnd();
  if(seat==1 || seat==2 || seat==3 || seat==4 || seat==5 || seat==6 || seat==7 || seat==8 || seat==9 || seat==10 || seat==11 ||seat==45 ){//keep only top tex
    glDisable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,tex2d[2]);
    glColor3f(r,b,g);
    glNormal3d(0,-1,0);
    /* Bottom of Cylinder */
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0.0, -height, 0.0);
    for(i = 0.0; i <= size; i+=10) {
      glVertex3d(radius * Cos(i), -height, radius * Sin(i));
    }
    glEnd();
    double j;
    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= size; j+=.125) {
      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);
      glColor3f(r,b,g);//transparency only applies to seats()
      glNormal3d(Cos(j), 0, Sin(j));
      glVertex3d(x, y, z);
    }
    glEnd();
}
  else{
    glColor3f(r,b,g);
    glNormal3d(0,-1,0);
    /* Bottom of Cylinder */
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5,0.5);
    glVertex3d(0.0, -height, 0.0);
    for(i = 0.0; i <= size; i+=10) {
      glTexCoord2f(0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
      glVertex3d(radius * Cos(i), -height, radius * Sin(i));
    }
    glEnd();
    double j;
    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= size; j+=.125) {
      const float tc = (j / (float) 360);
      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);
      glColor3f(r,b,g);//transparency only applies to seats()
      glNormal3d(Cos(j), 0, Sin(j));
      glTexCoord2f(-tc, 0.0); glVertex3d(x, -y, z);
      glTexCoord2f(-tc, 1.0); glVertex3d(x, y, z);
    }
    glEnd();
  }
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void metro_rack(double x,double y,double z,int th,int black)
{
  glPushMatrix();
  // glRotatef(180,0,1,0);
  if (th != 0){
  glRotated(90,0,1,0);}
  for (double j=0;j<6;j+=1.5){
  drawCylinder(x,-2.1+j,z,0.4,1,0.4,0,0,360,0,0,black);//leg metro rack
  drawCylinder(x,-2.1+j,z+2,0.4,1,0.4,0,0,360,0,0,black);//leg metro rack
  drawCylinder(x+4,-2.1+j,z,0.4,1,0.4,0,0,360,0,0,black);//leg metro rack
  drawCylinder(x+4,-2.1+j,z+2,0.4,1,0.4,0,0,360,0,0,black);//leg metro rack
  }
  for (double j=0;j<5.6;j+=1.8){
    drawCylinder(x,-2.7+j,z+1,0.1,1,0.1,90,1,360,0,0,black);//outer wire x dir
    drawCylinder(x+4,-2.7+j,z+1,0.1,1,0.1,90,1,360,0,0,black);//outer wire x dir
    drawCylinder(x+2,-2.7+j,z,0.1,2,0.1,90,0,360,0,0,black);//outer wire z dir
    drawCylinder(x+2,-2.7+j,z+2,0.1,2,0.1,90,0,360,0,0,black);//outer wire z dir

    for (double i=0;i<4;i+=0.1){
      drawCylinder(x+i,-2.7+j,z+1,0.05,1,0.05,90,1,360,0,0,black);//inner rack x direction
      }
    for (double k=0;k<2;k+=0.5){
      drawCylinder(x+2,-2.7+j,z+k,0.05,2,0.05,90,0,360,0,0,black);//inner rack z direction
      }
  }
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}


static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, int tex, double r, double g, double b, double a)
{

  double tex_x=1;
  double tex_y=1;

  //  glRotatef(180,0,1,0);

   //  Enable textures
   if (tex!=0 && tex!= 100 && tex!=5 && tex!=8 && tex!=44 && tex !=1000){ //texture on

   glEnable(GL_TEXTURE_2D);
  //  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

   glBindTexture(GL_TEXTURE_2D,tex2d[tex]);
   glColor4f(r,g,b,a);
   tex_x=1;
   tex_y=1;
      }
   else if(tex==5){
     glEnable(GL_TEXTURE_2D);
     glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
     glColor3f(1,1,1);
     glBindTexture(GL_TEXTURE_2D,tex2d[tex]);
     tex_x=2;
     tex_y=1;
   }
   else if(tex==100){//ridiculous num to apply wall texture,because it is 0 in loader
     tex = 0;
     glEnable(GL_TEXTURE_2D);
     glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
     glColor3f(1,1,1);
     glBindTexture(GL_TEXTURE_2D,tex2d[tex]);
     tex_x=20;
     tex_y=20;

   }
   else if(tex==8){
     glEnable(GL_TEXTURE_2D);
     glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
     glColor3f(1,1,1);
     glBindTexture(GL_TEXTURE_2D,tex2d[tex]);
     tex_x=5;
     tex_y=5;
   }

   else{
     glDisable(GL_TEXTURE_2D);
   }
   if(tex==6 || tex==10){
    glDisable(GL_TEXTURE_2D);
   }
   if (tex==1000){
       glEnable(GL_BLEND);
      //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //  Save transformation
        glPushMatrix();
        //  Offset, scale and rotate
        glTranslated(x,y,z);
        glRotated(th,0,1,0);
        glScaled(dx,dy,dz);

        //  Top
        glBegin(GL_QUADS);
        glColor4f(r,g,b,a);
        glNormal3f( 0,+1, 0);
        glVertex3f(-1,+1,+1);
        glVertex3f(+1,+1,+1);
        glVertex3f(+1,+1,-1);
        glVertex3f(-1,+1,-1);
        glEnd();
        //  Front
        glBegin(GL_QUADS);
        glColor4f(r,g,b,a);
        glNormal3f( 0, 0, 1);
        glVertex3f(-1,-1, 1);
        glVertex3f(+1,-1, 1);
        glVertex3f(+1,+1, 1);
        glVertex3f(-1,+1, 1);

        glEnd();

        //  Back
        glBegin(GL_QUADS);
        glColor4f(r,g,b,a);
        glNormal3f( 0, 0,-1);
        glVertex3f(+1,-1,-1);
        glVertex3f(-1,-1,-1);
        glVertex3f(-1,+1,-1);
        glVertex3f(+1,+1,-1);

        glEnd();
        //  Right
        glBegin(GL_QUADS);
        glColor4f(r,g,b,a);
        glNormal3f(+1, 0, 0);
        glVertex3f(+1,-1,+1);
        glVertex3f(+1,-1,-1);
        glVertex3f(+1,+1,-1);
        glVertex3f(+1,+1,+1);

        glEnd();
        //  Left
        glBegin(GL_QUADS);
        glColor4f(r,g,b,a);
        glNormal3f(-1, 0, 0);
        glVertex3f(-1,-1,-1);
        glVertex3f(-1,-1,+1);
        glVertex3f(-1,+1,+1);
        glVertex3f(-1,+1,-1);
        glEnd();

        //  Bottom
        glBegin(GL_QUADS);
        glColor4f(r,g,b,a);
        glNormal3f( 0,-1, 0);
        glVertex3f(-1,-1,-1);
        glVertex3f(+1,-1,-1);
        glVertex3f(+1,-1,+1);
        glVertex3f(-1,-1,+1);

        glEnd();
        // glDisable(GL_BLEND);
        glPopMatrix();
   }
   else if(tex==44){
     glPushMatrix();
     //  Offset, scale and rotate
     glTranslated(x,y,z);
     glRotated(th,0,1,0);
     glScaled(dx,dy,dz);
     glEnable(GL_TEXTURE_2D);
     glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
     glColor3f(0.29,0,0);
     glBindTexture(GL_TEXTURE_2D,tex2d[tex]);
     if (0<x){
       tex_x=19;
       tex_y=3.5;
     }
     else if(-2<x && x<0){
       tex_x=15;
       tex_y=3.35;
     }
     else{
       tex_x=5;
       tex_y=20;
     }
     //  Top
     glBegin(GL_QUADS);
     glColor3f(0.29,0,0);
     glNormal3f( 0,+1, 0);
     glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
     glTexCoord2f(tex_x,0); glVertex3f(+1,+1,+1);
     glTexCoord2f(tex_x,tex_y); glVertex3f(+1,+1,-1);
     glTexCoord2f(0,tex_y); glVertex3f(-1,+1,-1);
     glEnd();
     //  Front
     glBegin(GL_QUADS);
     glColor3f(0.29,0,0);
     glNormal3f( 0, 0, 1);
     glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
     glTexCoord2f(tex_x,0); glVertex3f(+1,-1, 1);
     glTexCoord2f(tex_x,tex_y); glVertex3f(+1,+1, 1);
     glTexCoord2f(0,tex_y); glVertex3f(-1,+1, 1);

     glEnd();
     //  Right
     glBegin(GL_QUADS);
     glColor3f(0.29,0,0);
     glNormal3f(+1, 0, 0);
      glTexCoord2f(0,tex_y);glVertex3f(+1,-1,+1);
      glTexCoord2f(0,0);glVertex3f(+1,-1,-1);
      glTexCoord2f(tex_x,0);glVertex3f(+1,+1,-1);
      glTexCoord2f(tex_x,tex_y);glVertex3f(+1,+1,+1);

     glEnd();
     //  Left
     glBegin(GL_QUADS);
     glColor3f(0.29,0,0);
     glNormal3f(-1, 0, 0);
     glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
     glTexCoord2f(0,tex_y); glVertex3f(-1,-1,+1);
     glTexCoord2f(tex_x,tex_y); glVertex3f(-1,+1,+1);
     glTexCoord2f(tex_x,0); glVertex3f(-1,+1,-1);
     glEnd();

     //  Bottom
     glBegin(GL_QUADS);
      glColor3f(0.29,0,0);
     glNormal3f( 0,-1, 0);
     glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
     glTexCoord2f(tex_x,0); glVertex3f(+1,-1,-1);
     glTexCoord2f(tex_x,tex_y); glVertex3f(+1,-1,+1);
     glTexCoord2f(0,tex_y); glVertex3f(-1,-1,+1);
     glEnd();
     glDisable(GL_TEXTURE_2D);
     if(tex==44){
       a=1;
       glEnable(GL_TEXTURE_2D);
       glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
       glColor3f(0.03,0.55,1);
       glBindTexture(GL_TEXTURE_2D,tex2d[tex]);
       if (0<x){
         tex_x=19;
         tex_y=3.5;
       }
       else if(-2<x && x<0){
         tex_x=15;
         tex_y=3.35;
       }
       else{
         tex_x=5;
         tex_y=20;
       }
     //  Back
     glBegin(GL_QUADS);
     glColor3f(0.03,0.55,1);
     glNormal3f( 0, 0,-1);
     glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
     glTexCoord2f(tex_x,0); glVertex3f(-1,-1,-1);
     glTexCoord2f(tex_x,tex_y); glVertex3f(-1,+1,-1);
     glTexCoord2f(0,tex_y); glVertex3f(+1,+1,-1);
     glEnd();}
     glPopMatrix();
   }
   else{

   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   //  Top
   glBegin(GL_QUADS);
   glColor4f(r,g,b,1);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(tex_x,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(tex_x,tex_y); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,tex_y); glVertex3f(-1,+1,-1);
   glEnd();
  //  glEnd();
   if(tex==5){//no texure from here on, grey out everything else
     glDisable(GL_TEXTURE_2D);
     r=0.1;
     b=0.1;
     g=0.1;
   }
   if(tex==6|| tex==10){
     glEnable(GL_TEXTURE_2D);
     r=b=g=1;
   }
   //  Front
   glBegin(GL_QUADS);
   glColor4f(r,g,b,a);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(tex_x,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(tex_x,tex_y); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,tex_y); glVertex3f(-1,+1, 1);

   glEnd();
   if(tex==6){
     glEnable(GL_TEXTURE_2D);
     glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
     glColor3f(1,1,1);
     glBindTexture(GL_TEXTURE_2D,tex2d[4]);
   }
   if(tex==10||tex==11){
     glEnable(GL_TEXTURE_2D);
     glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
     glColor3f(1,1,1);
     glBindTexture(GL_TEXTURE_2D,tex2d[9]);
   }


   //  Right
   glBegin(GL_QUADS);
   glColor4f(r,g,b,a);
   glNormal3f(+1, 0, 0);
    glTexCoord2f(0,tex_y);glVertex3f(+1,-1,+1);
    glTexCoord2f(0,0);glVertex3f(+1,-1,-1);
    glTexCoord2f(tex_x,0);glVertex3f(+1,+1,-1);
    glTexCoord2f(tex_x,tex_y);glVertex3f(+1,+1,+1);

   glEnd();
   //  Left
   glBegin(GL_QUADS);
   glColor4f(r,g,b,a);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(0,tex_y); glVertex3f(-1,-1,+1);
   glTexCoord2f(tex_x,tex_y); glVertex3f(-1,+1,+1);
   glTexCoord2f(tex_x,0); glVertex3f(-1,+1,-1);
   glEnd();

   //  Bottom
   glBegin(GL_QUADS);
   glColor4f(r,g,b,a);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(tex_x,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(tex_x,tex_y); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,tex_y); glVertex3f(-1,-1,+1);

   glEnd();


     //  Back
     glBegin(GL_QUADS);
     glColor4f(r,g,b,a);
     glNormal3f( 0, 0,-1);
     glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
     glTexCoord2f(tex_x,0); glVertex3f(-1,-1,-1);
     glTexCoord2f(tex_x,tex_y); glVertex3f(-1,+1,-1);
     glTexCoord2f(0,tex_y); glVertex3f(+1,+1,-1);
     glEnd();

    glPopMatrix();
 }
   //  Undo transformations and textures

   glDisable(GL_TEXTURE_2D);
}
static void dip_cab(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th,int side)
{

  glPushMatrix();
  if(side==1){
    glRotatef(90,0,1,0);
  }
  glDisable(GL_TEXTURE_2D);
if(side==1 ||side==2){
  //x =1 , y=-2 z=-2
 cube(x,y,z,2.1,1.4,1.4,0,9,1,1,1,1);
 cube(x,y+1.6,z-0.15,2.1,0.2,1.23,0,4,0.5,0.5,0.5,1);}
 glRotated(0,0,1,0);
 if(side==0){
 cube(1,-2,-6.5,2.1,1.4,1.4,180,9,1,1,1,1);
 cube(1,-0.4,-6.35,2.1,0.2,1.23,180,4,0.5,0.5,0.5,1);}
glPopMatrix();
glPushMatrix();
if(side==1){
  glRotatef(90,0,1,0);
}
 if (th==0){
    if(side==1||side==2){
    drawCylinder(x,y+1.4,z+1,1.62,2.1,1.60,90,0,90,0,0,0);
    }
 }
    else {
      //glRotated(180,1,0,0);
      glRotated(180,1,0,0);
      glRotated(180,0,0,1);
      if(side==0){
      drawCylinder(-1,-0.6,7.5,1.62,2.1,1.6,90,0,90,0,0,0);}
    }
    // glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
static void Lcounter(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{

   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   //  //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(0.5f,0.35f,0.05f);
    glBindTexture(GL_TEXTURE_2D,tex2d[3]);
    //left countertop side
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,1);glVertex3f(-8, 0, 0);
   glTexCoord2f(1,1);glVertex3f(-8,0,1);
   glTexCoord2f(1,0);glVertex3f(-8,-0.16,1);
   glTexCoord2f(0,0);glVertex3f(-8,-0.16,0);
   glEnd();
   //  Front
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,1);glVertex3f(-8,0,+1);
   glTexCoord2f(1,1);glVertex3f(+1.5,0,+1);
   glTexCoord2f(1,0);glVertex3f(+1.5,-0.16,+1);
   glTexCoord2f(0,0);glVertex3f(-8,-0.16,+1);
   glEnd();
   //Bottom
     glBegin(GL_QUADS);
     glColor3f(0.5f, 0.35f, 0.05f);
     glNormal3f(0, -1, 0);
     glTexCoord2f(0,1);glVertex3f(-8,-0.16,+1);
     glTexCoord2f(1,1);glVertex3f(+1.5,-0.16,+1);
     glTexCoord2f(1,0);glVertex3f(+1.5,-0.16,-1);
     glTexCoord2f(0,0);glVertex3f(-8,-0.16,-1);
     glEnd();
    //parallel countertop outside edge
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.35f, 0.05f);
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0,1);glVertex3f(4.5,0,-3);
    glTexCoord2f(1,1);glVertex3f(+1.5,0,+1);
    glTexCoord2f(1,0);glVertex3f(+1.5,-0.16,+1);
    glTexCoord2f(0,0);glVertex3f(4.5,-0.16,-3);
    glEnd();
    //parallel countertop bottom edge
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.35f, 0.05f);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0,1);glVertex3f(4.5,-0.16,-3);
    glTexCoord2f(1,1);glVertex3f(+1.5,-0.16,+1);
    glTexCoord2f(1,0);glVertex3f(+1.5,-0.16,-1);
    glTexCoord2f(0,0);glVertex3f(4.5,-0.16,-3);
    glEnd();

   //  Offset, scale and rotate

   glScaled(dx,dy,dz); //don't want to scale above

   //  Front
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,1);glVertex3f(-8,0,0);
   glTexCoord2f(1,1);glVertex3f(+1.5,0,0);
   glTexCoord2f(1,0);glVertex3f(+1.5,-0.16,0);
   glTexCoord2f(0,0);glVertex3f(-8,-0.16,0);
   glEnd();



   //  Right
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f(1/sqrt(2), 0, 1/sqrt(2));
   glTexCoord2f(0,1);glVertex3f(+1.5,0,0);
   glTexCoord2f(1,1);glVertex3f(+4,0,-3);
   glTexCoord2f(1,0);glVertex3f(+4,-0.16,-3);
   glTexCoord2f(0,0);glVertex3f(+1.5,-0.16,0);
   glEnd();

  //  //  Left
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.35f, 0.05f);
    glNormal3f(-1,0,0);
    glTexCoord2f(0,1);glVertex3f(-8, 0, -1);
    glTexCoord2f(1,1);glVertex3f(-8,0,0);
    glTexCoord2f(1,0);glVertex3f(-8,-0.16,0);
    glTexCoord2f(0,0);glVertex3f(-8,-0.16,-1);
    glEnd();

   //  Top
   glBegin(GL_QUADS);
  glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f(0, 1, 0);
   glTexCoord2f(0,0);glVertex3f(-8,0,+1);//bottom left
   glTexCoord2f(1,1);glVertex3f(+1.5,0,+1);//bottom right
  glTexCoord2f(1,0);glVertex3f(+3,0,-1);//top left
   glTexCoord2f(0,1);glVertex3f(-8,0,-1);//top left
   glEnd();

  //parallelogram
  //top
  glBegin(GL_QUADS);
  glColor3f(0.5f, 0.35f, 0.05f);//brown
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);glVertex3f(+1,0,-1);
  glTexCoord2f(1,0);glVertex3f(+3,0,-1);
  glTexCoord2f(1,1);glVertex3f(+4.5,0,-3);
  glTexCoord2f(0,1);glVertex3f(+2.5,0,-3);
  glEnd();
  //glDisable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glColor3f(1,1,1);
  glBindTexture(GL_TEXTURE_2D,tex2d[0]);
  //wall texture from here on needed
  //repeat and make smaller so use (0,0) to (10,10) coords
  //  //  Back
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glNormal3f(0, 0, -1);
    glTexCoord2f(10,10);glVertex3f(+2,0,-1);
    glTexCoord2f(0,10);glVertex3f(-8,0,-1);
    glTexCoord2f(0,0);glVertex3f(-8,-0.16,-1);
    glTexCoord2f(10,0);glVertex3f(+2,-0.16,-1);
    glEnd();
  //  //  Bottom
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0,10);glVertex3f(-8,-0.16,0);//bottom left
    glTexCoord2f(10,10);glVertex3f(+1,-0.16,0);//bottom right
    glTexCoord2f(10,0);glVertex3f(+1,-0.16,-1);//bottom right
    glTexCoord2f(0,0);glVertex3f(-8,-0.16,-1);//top left
    glEnd();

  //back
  glBegin(GL_QUADS);
  glColor3f(1,1,1);
  glNormal3f(0,0,-1);
  glTexCoord2f(10,0);glVertex3f(+2,0,-2);
  glTexCoord2f(0,0);glVertex3f(+2,-0.16,-2);
  glTexCoord2f(0,10);glVertex3f(+4,-0.16,-5);
  glTexCoord2f(10,10);glVertex3f(+4,0,-5);
  glEnd();
  //left
  glBegin(GL_QUADS);
  glColor3f(1,1,1);
  glNormal3f(-1/sqrt(2),0,-1/sqrt(2));
  glTexCoord2f(10,10);glVertex3f(+2,0,-2);
  glTexCoord2f(10,0);glVertex3f(+2,-0.16,-2);
  glTexCoord2f(0,0);glVertex3f(+1,-0.16,-1);
  glTexCoord2f(0,10);glVertex3f(+1,0,-1);
  glEnd();



   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

}

static void counters(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th,int tex,float r, float g, float b, int woodtop, int mid_div )
{
  //  Save transformation
  glPushMatrix();
  //  Offset, scale and rotate
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);
  int tex_x=1;
  int tex_y=1;
 //  //  Enable textures
 if(tex==1){
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glColor3f(0.5f,0.35f,0.05f);
  glBindTexture(GL_TEXTURE_2D,tex2d[3]);
}
else{
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glColor3f(r,g,b);
  glBindTexture(GL_TEXTURE_2D,tex2d[tex]);
}
if(mid_div==1){
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glColor3f(1,1,1);
  glBindTexture(GL_TEXTURE_2D,tex2d[0]);
  r=1;
  g=1;
  b=1;
  tex_x=10;
  tex_y=10;
  //glDisable(GL_TEXTURE_2D);
}

 glBegin(GL_QUADS);
 //  Front -- doesn't need texture anywhere
 glColor3f(r,g,b);
 glNormal3d(0,0,1);
 glTexCoord2f(0,0);glVertex3f(-1,-0.16, 1);
 glTexCoord2f(tex_x,0);glVertex3f(+1,-0.16, 1);
 glTexCoord2f(tex_x,tex_y);glVertex3f(+1,0, 1);
 glTexCoord2f(0,tex_y);glVertex3f(-1,0, 1);
 glEnd();
 //  Back
 glBegin(GL_QUADS);
 glColor3f(r,g,b);
 glNormal3d(0,0,-1);
 glTexCoord2f(0,tex_y);glVertex3f(+1,-0.16,-1);
 glTexCoord2f(0,0);glVertex3f(-1,-0.16,-1);
 glTexCoord2f(tex_x,0);glVertex3f(-1,0,-1);
 glTexCoord2f(tex_x,tex_y);glVertex3f(+1,0,-1);
 glEnd();
 //  Right
 glBegin(GL_QUADS);
 glColor3f(r,g,b);
 glNormal3d(1,0,0);
 glTexCoord2f(tex_x,0);glVertex3f(+1,-0.16,+1);
 glTexCoord2f(0,0);glVertex3f(+1,-0.16,-1);
 glTexCoord2f(0,tex_y);glVertex3f(+1,0,-1);
 glTexCoord2f(tex_x,tex_y);glVertex3f(+1,0,+1);
 glEnd();
 if (woodtop==1){

 //  Left-- top needs texture
 glBegin(GL_QUADS);
 glColor3f(r,g,b);
 glNormal3d(-1,0,0);
 glTexCoord2f(0,0);glVertex3f(-1,-0.16,-1);
 glTexCoord2f(tex_x,0);glVertex3f(-1,-0.16,+1);
 glTexCoord2f(tex_x,tex_y); glVertex3f(-1,0,+1);
 glTexCoord2f(0,tex_y);glVertex3f(-1,0,-1);
 glEnd();
 //  Top -- needs texture if it's not the bottom shelf
 glBegin(GL_QUADS);
 glColor3f(r,g,b);
 glNormal3d(0,1,0);
 glTexCoord2f(0,tex_y);glVertex3f(-1,0,+1);
 glTexCoord2f(tex_x,tex_y);glVertex3f(+1,0,+1);
 glTexCoord2f(tex_x,0);glVertex3f(+1,0,-1);
 glTexCoord2f(0,0);glVertex3f(-1,0,-1);
 glEnd();}

 //  Bottom
 glBegin(GL_QUADS);
 glColor3f(r,g,b);
 glNormal3d(0,-1,0);
 glTexCoord2f(0,0);glVertex3f(-1,-0.16,-1);
 glTexCoord2f(0,tex_y);glVertex3f(+1,-0.16,-1);
 glTexCoord2f(1,tex_y);glVertex3f(+1,-0.16,+1);
 glTexCoord2f(1,0);glVertex3f(-1,-0.16,+1);
 glEnd();

 //  Undo transformations and textures

 //  Left-- wall textures
 if (woodtop==0){
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,tex2d[0]);
 glBegin(GL_QUADS);
 glColor3f(1,1,1);
 glNormal3d(-1,0,0);
 glTexCoord2f(0,0);glVertex3f(-1,-0.16,-1);
 glTexCoord2f(10,0);glVertex3f(-1,-0.16,+1);
 glTexCoord2f(10,10); glVertex3f(-1,0,+1);
 glTexCoord2f(0,10);glVertex3f(-1,0,-1);
 glEnd();
 //top
 glBegin(GL_QUADS);
 glColor3f(1,1,1);
 glNormal3d(0,1,0);
 glTexCoord2f(0,10);glVertex3f(-1,0,+1);
 glTexCoord2f(10,10);glVertex3f(+1,0,+1);
 glTexCoord2f(10,0);glVertex3f(+1,0,-1);
 glTexCoord2f(0,0);glVertex3f(-1,0,-1);
 glEnd();}
 //glEnd();

 glPopMatrix();
 glDisable(GL_TEXTURE_2D);

}


static void seats(double x, double z, int slant)
{
  // glPushMatrix();
  // glRotatef(180,0,1,0);

  //glColor3f(1,1,1);

  //4 horizontal seats base x=5.5 z=4.8
  drawCylinder(x,-3.1,z,1.5,0.05,1.5,0,0,360,0,0,0);
  drawCylinder(x-2.5,-3.1,z,1.5,0.05,1.5,0,0,360,0,0,0);
  drawCylinder(x-5,-3.1,z,1.5,0.05,1.5,0,0,360,0,0,0);
  drawCylinder(x-7.5,-3.1,z,1.5,0.05,1.5,0,0,360,0,0,0);
  //stool leg
  drawCylinder(x,-2.1,z,0.7,1,0.7,0,0,360,0,0,0);
  drawCylinder(x-2.5,-2.1,z,0.7,1,0.7,0,0,360,0,0,0);
  drawCylinder(x-5,-2.1,z,0.7,1,0.7,0,0,360,0,0,0);
  drawCylinder(x-7.5,-2.1,z,0.7,1,0.7,0,0,360,0,0,0);
  //grey top
  drawCylinder(x,-1.1,z,2,0.04,2,0,0,360,1,0,0);
  drawCylinder(x-2.5,-1.1,z,2,0.04,2,0,0,360,1,0,0);
  drawCylinder(x-5,-1.1,z,2,0.04,2,0,0,360,1,0,0);
  drawCylinder(x-7.5,-1.1,z,2,0.04,2,0,0,360,1,0,0);
  if (slant==0){//5th seat in front of shop
    drawCylinder(x-10,-3.1,z,1.5,0.05,1.5,0,0,360,0,0,0);
    drawCylinder(x-10,-2.1,z,0.7,1,0.7,0,0,360,0,0,0);
    drawCylinder(x-10,-1.1,z,2,0.04,2,0,0,360,1,0,0);
  }
  else{
    //slant seats
    drawCylinder(7.3+2,-3.1,1.6,1.5,0.05,1.5,0,0,360,0,0,0);
    drawCylinder(6.1+2,-3.1,3.1,1.6,0.05,1.5,0,0,360,0,0,0);
    drawCylinder(7.3+2,-2.1,1.6,0.7,1,0.7,0,0,360,0,0,0);
    drawCylinder(6.1+2,-2.1,3.1,0.7,1,0.7,0,0,360,0,0,0);
    //rotate top two seats
    drawCylinder(7.3+2,-1.1,1.6,2,0.04,2,0,0,360,1,1,0);
    drawCylinder(6.1+2,-1.1,3.1,2,0.04,2,0,0,360,1,1,0);
  }

  //clear top
  //  Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  drawCylinder(x,-1.02,z,2,0.04,2,0,0,360,0,0,0);
  drawCylinder(x-2.5,-1.02,z,2,0.04,2,0,0,360,0,0,0);
  drawCylinder(x-5,-1.02,z,2,0.04,2,0,0,360,0,0,0);
  drawCylinder(x-7.5,-1.02,z,2,0.04,2,0,0,360,0,0,0);
  if (slant==0){
    drawCylinder(x-10,-1.02,z,2,0.04,2,0,0,360,0,0,0);
  }
  else{
    //slant
    drawCylinder(7.3+2,-1.02,1.6,2,0.04,2,0,0,360,0,0,0);
    drawCylinder(6.1+2,-1.02,3.1,2,0.04,2,0,0,360,0,0,0);
  }
  glDisable(GL_BLEND);
  // glPopMatrix();
}
static void menu(double z){
  glPushMatrix();
  glScaled(1,1.7,1.4);
  cube(-9.2,3.1,z,0.1,1.8,1.2,0,4,0.90,0.90,0.90,1);//board
  cube(-9.2,3.1,z-1.2,0.1,1.8,0.04,0,7,1, 1,1,1);//right
  cube(-9.2,3.1,z+1.2,0.1,1.8,0.04,0,7,1, 1,1,1);//left
  cube(-9.2,1.25,z,0.12,0.04,1.24,0,7,1, 1,1,1);//right
  cube(-9.2,4.95,z,0.12,0.04,1.24,0,7,1, 1,1,1);//right
  glPopMatrix();
}
static void flavors(){
  glPushMatrix();
  glRotatef(0,0,0,1);
  glRotatef(90,0,1,0);
  //int j =0;
  for (int i=0;i<12;i+=1){
    double j= i;
    cube(1.15,8-j/2,-9.1,0.75,0.2,0.03,0,tex2d[9+i],1, 1,1,1);
    cube(2.75,8-j/2,-9.1,0.75,0.2,0.03,0,tex2d[21+i],1, 1,1,1);
  }
  // cube(1.15,3,-9.1,0.75,0.2,0.03,0,tex2d[22],1, 1,1,1);
  glPopMatrix();
}
static void circle_mags(){
  glPushMatrix();
  glRotatef(180,0,1,0);
  glRotatef(130,1,0,0);
  // drawCylinder(2,4,2,1,1,1,90,1,360,2,1,2);//outer wire x dir
            //  z  x    y
  drawCylinder(9.1,-6.4,-4,4,0.03,4,90,0,360,2,1,2);//left big mag 1
  drawCylinder(9.1,-3.5,-2,4,0.03,4,90,0,360,3,1,2);//left big mag 2
  drawCylinder(9.1,-4.6,-3.5,3,0.03,3,90,0,360,4,1,2);//left small mag 1
  drawCylinder(9.1,-5.3,-2,3,0.03,3,90,0,360,5,1,2);//left small mag 2
  drawCylinder(9.1,-4.1,-0.4,2.8,0.03,2.8,90,0,360,6,1,2);//left small mag 3

  drawCylinder(9.1,0.7,-9.3,4,0.03,4,90,0,360,7,1,2);//right big mag 1
  drawCylinder(9.1,1.95,-6,4,0.03,4,90,0,360,8,1,2);//right big mag 2
  drawCylinder(9.1,2,-7.8,2.8,0.03,2.8,90,0,360,11,1,2);//right small mag 1
  drawCylinder(9.1,0.5,-7.2,2.8,0.03,2.8,90,0,360,10,1,2);//right small mag 2
  drawCylinder(9.1,-1,-9.2,2.8,0.03,2.8,90,0,360,9,1,2);//right small mag 3
  // drawCylinder(9.1,-5.3,-2,3,0.03,3,90,0,360,5,1,2);//right small mag 2
  // drawCylinder(9.1,-4.1,-0.4,2.8,0.03,2.8,90,0,360,6,1,2);//right small mag 3

  glPopMatrix();
}
static void walls()
{
  float zz= 6;
  glPushMatrix();
  int theta[2] = {180,90};
  //back wall
  cube(7.3,-1.3,-15-zz,7.7,2,0.16,theta[0],9,0.3, 0.6,0.95,1);//bottom blue back
  cube(7.3,4.7,-15-zz,7.7,4,0.16,theta[0],9,0.1, 0.5,0.8,1);//top blue back

  // cube(4,-1.3,-15-zz,11,2,0.16,theta[0],9,0.3, 0.6,0.95,1);//bottom blue back
  // cube(4,4.7,-15-zz,11,4,0.16,theta[0],9,0.1, 0.5,0.8,1);//top blue back
  for(double k=0;k<13;k+=1.8){
    for(double i=0;i<1;i+=1.7){
      for(double j=0;j<1.5;j+=0.5){
        cube(0+j+k,-1.75,-14.69-zz,0.2,1.5,0.04,180,7,1, 1,1,1);//thick plank
      }
      cube(1.4+i+k,-1.75,-14.69-zz,0.1,1.5,0.04,180,7,1, 1,1,1);//thin plank
    }
    cube(7.3,-1,-14.78-zz,7.7,0.04,0.02,180,7,1, 1,1,1);//horiz plank
    cube(7.3,-2.5,-14.78-zz,7.7,0.04,0.02,180,7,1, 1,1,1);//horiz plank
  }
  //right wall
  cube(15,-1.3,-3,18,2,0.16,theta[1],9,0.3, 0.6,0.95,1);//bottom blue back
  cube(15,4.7,-3,18,4,0.16,theta[1],9,0.1, 0.5,0.8,1);//top blue back

  glRotated(90,0,1,0);
  //right wall
  for(double k=0;k<36;k+=1.8){
    for(double i=0;i<1;i+=1.7){
      for(double j=0;j<1.5;j+=0.5){
        cube(-14.8+j+k,-1.75,14.69,0.2,1.5,0.04,180,7,1, 1,1,1);//thick plank
      }
      cube(-13.4+i+k,-1.75,14.69,0.1,1.5,0.04,180,7,1, 1,1,1);//thin plank
    }
    cube(3,-1,14.78,18,0.04,0.02,180,7,1, 1,1,1);//horiz plank
    cube(3,-2.5,14.78,18,0.04,0.02,180,7,1, 1,1,1);//horiz plank
  }

  glPopMatrix();
}
static void walk_in()
{
    //cube(-14.7,0,-2,4.3,3,6,0,0,1,1,1,1);

    cube(-14.7,0,3.8,4.3,3,0.2,0,4,0.50,0.50,0.50,1);//back
    // cube(-14.7,-0.5,-7.8,1.5,2.5,0.2,0,4,0.50,0.50,0.50,1);//door
    cube(-12.1,-.5,-7.8,1.3,2.5,0.2,0,4,0.50,0.50,0.50,1);//front left
    cube(-17.3,-.5,-7.8,1.3,2.5,0.2,0,4,0.50,0.50,0.50,1);//front right
    cube(-14.7,2.5,-7.8,3.9,0.5,0.2,0,4,0.50,0.50,0.50,1);//front top
    cube(-10.6,0,-2.2,0.2,3,5.8,0,4,0.50,0.50,0.50,1);//right
    cube(-18.8,0,-2.2,0.2,3,5.8,0,4,0.50,0.50,0.50,1);//left
    cube(-14.7,3.2,-2,4.3,0.2,6,0,4,0.50,0.50,0.50,1);//top
    cube(-14.7,-3,-2,4.3,0.2,6,0,4,0.50,0.50,0.50,1);//bottom
}
static void sinks(){
  glPushMatrix();
  glTranslated(-7,-1,-25);
  glRotatef(90,0,1,0);
  cube(-5,0,-6.5,0.7,0.8,0.01,0,4,0.50,0.50,0.50,1);
  cube(-5,0,-5,0.7,0.8,0.01,0,4,0.50,0.50,0.50,1);
  cube(-5,0,-3.5,0.7,0.8,0.01,0,4,0.50,0.50,0.50,1);
  cube(-5,0,-2,0.7,0.8,0.01,0,4,0.50,0.50,0.50,1);
  glPopMatrix();
  glPushMatrix();
  glTranslated(-7,-1,-25);
  glRotatef(90,1,0,0);
  cube(-4.25,5,0.8,2.25,0.7,0.01,0,4,0.50,0.50,0.50,1);//bottom
  cube(-1,5.2,-0.7,1,0.9,0.1,0,4,0.50,0.50,0.50,1);//right top
  cube(-1,6.0,-0.8,1.1,0.1,0.2,0,4,0.50,0.50,0.50,1);//right top bottom
  cube(0.1,5.2,-0.8,0.1,0.9,0.2,0,4,0.50,0.50,0.50,1);//right top right
  cube(-2,5.9,-0.8,0.1,0.2,0.2,0,4,0.50,0.50,0.50,1);//right top left
  cube(-7.5,5.2,-0.7,1,0.9,0.1,0,4,0.50,0.50,0.50,1);//left top
  cube(-1-6.5,6.0,-0.8,1.1,0.1,0.2,0,4,0.50,0.50,0.50,1);//left top bottom
  cube(-8.5,5.2,-0.8,0.1,0.9,0.2,0,4,0.50,0.50,0.50,1);//left top right
  cube(-6.5,5.9,-0.8,0.1,0.2,0.2,0,4,0.50,0.50,0.50,1);//left top left
  glPopMatrix();
  glPushMatrix();
  glTranslated(-7,-1,-25);
  cube(-4.25,0,4.3,2.25,0.8,0.01,0,4,0.50,0.50,0.50,1);//back
  cube(-4.25,0,5.7,2.25,0.8,0.01,0,4,0.50,0.50,0.50,1);//front
  glPopMatrix();
}
static void shakes(double x, double y, double z, int rott){
  glPushMatrix();
  // glRotatef(180,0,1,0);
  if (rott==1){
    glRotated(90,0,1,0);
  }
  glTranslated(0,0.2,0);
  drawCylinder(x,y-0.59,z,1.6,0.1,1.2,0,0,180,0,0,4);//base
  cube(x,y,z-0.05,0.37,0.65,0.1,0,4,0.38,0.38,0.38,1);//back
  drawCylinder(x,-y,z,1.5,0.15,1.2,0,0,180,0,0,4);//top
  drawCylinder(x-0.2,y+0.25,z+0.15,0.1,0.4,0.1,0,0,180,0,0,5);//l spindle
  drawCylinder(x-0.2,y-0.15,z+0.15,0.2,0.01,0.2,0,0,180,0,0,5);//l spindle spokes
  drawCylinder(x,y+0.25,z+0.2,0.1,0.4,0.1,0,0,180,0,0,5);//m spindle
  drawCylinder(x,y-0.15,z+0.2,0.2,0.01,0.2,0,0,180,0,0,5);//m spindle spokes
  drawCylinder(x+0.2,y+0.25,z+0.15,0.1,0.4,0.1,0,0,180,0,0,5);//r spindle
  drawCylinder(x+0.2,y-0.15,z+0.15,0.2,0.01,0.2,0,0,180,0,0,5);//r spindle spokes
  glPopMatrix();
}
static void tables(double x,double z, int size,int rott){
  //0 or anything else = regular, 1 = big, 2 = small, 3 megabig
  glPushMatrix();
  // glRotatef(180,0,1,0);

  if (size==1||size==3){//big table
    if(rott!=0){

      glRotated(90,0,1,0);
    }
  //table legs
  drawCylinder(x,-2.1,z-1,0.4,1.4,0.4,0,0,360,0,0,0);
  drawCylinder(x,-2.1,z+3,0.4,1.4,0.4,0,0,360,0,0,0);
  drawCylinder(x+2,-2.1,z-1,0.4,1.4,0.4,0,0,360,0,0,0);
  drawCylinder(x+2,-2.1,z+3,0.4,1.4,0.4,0,0,360,0,0,0);
  //tabletop
  cube(x+1,-1+.2,z+1,1.2,0.1,2.4,0,4,0.50,0.50,0.50,1);
  //lower tabletop
  cube(x+1,-2.7+.2,z+1,1.1,0.07,2.2,0,4,0.50,0.50,0.50,1);
  if (size==3){
  //upper part of table
  drawCylinder(x,-0.35,z-1,0.4,0.5,0.4,0,0,360,0,0,0);
  drawCylinder(x,-0.35,z+3,0.4,0.5,0.4,0,0,360,0,0,0);
  drawCylinder(x+0.75,-0.35,z-1,0.4,0.5,0.4,0,0,360,0,0,0);
  drawCylinder(x+0.75,-0.35,z+3,0.4,0.5,0.4,0,0,360,0,0,0);
  cube(x+0.5,0+.2,z+1,0.5,0.07,2.2,0,4,0.50,0.50,0.50,1);//upper tabletop
}

  }
  else if (size==2){
    //table legs
    drawCylinder(x,-2.1,z,0.4,1.4,0.4,0,0,360,0,0,0);
    drawCylinder(x,-2.1,z+2,0.4,1.4,0.4,0,0,360,0,0,0);
    drawCylinder(x+1,-2.1,z,0.4,1.4,0.4,0,0,360,0,0,0);
    drawCylinder(x+1,-2.1,z+2,0.4,1.4,0.4,0,0,360,0,0,0);
    //tabletop
    cube(x+0.5,-1+.2,z+1,0.6,0.1,1.2,0,4,0.50,0.50,0.50,1);
    //lower tabletop
    cube(x+0.5,-2.7+.2,z+1,0.55,0.07,1.1,0,4,0.50,0.50,0.50,1);
  }
  else{
  //table legs
  drawCylinder(x,-2.1,z,0.4,1.4,0.4,0,0,360,0,0,0);
  drawCylinder(x,-2.1,z+2,0.4,1.4,0.4,0,0,360,0,0,0);
  drawCylinder(x+2,-2.1,z,0.4,1.4,0.4,0,0,360,0,0,0);
  drawCylinder(x+2,-2.1,z+2,0.4,1.4,0.4,0,0,360,0,0,0);
  //tabletop
  cube(x+1,-1+.2,z+1,1.2,0.1,1.2,0,4,0.50,0.50,0.50,1);
  //lower tabletop
  cube(x+1,-2.7+.2,z+1,1.1,0.07,1.1,0,4,0.50,0.50,0.50,1);
}
glPopMatrix();
}
static void handrail(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th,int top)
{

   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   if (top==1){
     glRotated(th,0,0,1);//}
     glRotated(th,1,0,0);
     glRotated(th,0,1,0);
     glRotated(th,0,1,0);}
   else {glRotated(th,0,1,0);}
   glScaled(dx,dy,dz);
  double i;
  //bottom
  glColor3f(0.1,0.1,0.1);
  glNormal3d(0,-1,0);
  glBegin(GL_TRIANGLE_FAN);

  glTexCoord2f(0.5,0.5);
  glVertex3d(0.0, 0, 0.0);
     for(i = 0.0; i <= 360; i+=10) {

        // glTexCoord2f(-0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
        glVertex3d(0.5 *0.5 *Cos(i), 0, 0.5*0.5 * Sin(i));
     }
  glEnd();
  //side
  double a = (.75 - 1) / 0.66*0.5;
  double b = 1;
  glBegin(GL_TRIANGLE_STRIP);
  for(i = 0.0; i <= 360; i+=10) {
    // glColor3f(1,0,1);
    glColor3f(0.1,0.1,0.1);
    glNormal3d(Cos(i), 0, Sin(i));
    double x = 0.5 *0.5* Cos(i);
    double z = 0.5 *0.5* Sin(i);
    double height2 = a * x + b;
    glVertex3d(x, 0.0,z);
    glVertex3d(x, height2,z);}
  glEnd();
  //top
  // double a = (H2 - H) / 0.5 * D;
  // double b = 1;

  glBegin(GL_TRIANGLE_FAN);
  // glTexCoord2f(0.5,0.5);
  glVertex3d(0.0, 1, 0); // center
  for(i = 0.0; i <= 360; i+=10) {
    double x = 0.5* 0.5 * Cos(i);
    double z = 0.5*0.5 * Sin(i);
    double height3 = a * x + b;
    // glTexCoord2f(-0.5*Cos(i)*0.5, 0.5*Sin(i)*0.5);
    glVertex3d(x,height3,z);}
  glEnd();
   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void toppings_fridge(){

  cube(-1+2,-1.7,-12,1.2,1.2,1.2,0,4,0.50,0.50,0.50,1);//base
  drawCylinder(-0.3+2,-3,-12.7,0.5,0.1,0.5,90,0,360,0,0,1);//wheel 1
  drawCylinder(-1.8+2,-3,-12.7,0.5,0.1,0.5,90,0,360,0,0,1);//wheel 2
  drawCylinder(-1.8+2,-3,-11.2,0.5,0.1,0.5,90,0,360,0,0,1);//wheel 3
  drawCylinder(-0.3+2,-3,-11.2,0.5,0.1,0.5,90,0,360,0,0,1);//wheel 4
  cube(-1+2,0,-12.9,1.2,0.5,0.3,0,4,0.50,0.50,0.50,1);//top shelf
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glColor3f(0.5,0.5,0.5);
  glBindTexture(GL_TEXTURE_2D,tex2d[4]);

  //right
  glBegin(GL_POLYGON);
  glNormal3d(-1,0,0);
  glTexCoord2f(0,1);glVertex3f(-2.1+2,0.35,-12.6);
  glTexCoord2f(0,0);glVertex3f(-2.1+2,-0.5,-12.6);
  glTexCoord2f(1,0);glVertex3f(-2.1+2,-0.5,-10.8);
  glEnd();
  //left
  glBegin(GL_POLYGON);
  glNormal3d(1,0,0);
  glTexCoord2f(0,1);glVertex3f(0.1+2,0.35,-12.6);
  glTexCoord2f(0,0);glVertex3f(0.1+2,-0.5,-12.6);
  glTexCoord2f(1,0);glVertex3f(0.1+2,-0.5,-10.8);
  glEnd();
  glBegin(GL_QUADS);
  glColor3f(0.38,0.38,0.38);
  glNormal3d(0,1,0);
  glVertex3f(-2.1+2,-0.5,-10.8);
  glVertex3f(0.1+2,-0.5,-10.8);
  glVertex3f(0.1+2,0.35,-12.6);
  glVertex3f(-2.1+2,0.35,-12.6);
  glEnd();
  cube(-0.8+2,-0.3,-11,0.03,0.1,0.03,0,4,0.50,0.50,0.50,1);//handle
  cube(-1.1+2,-0.3,-11,0.03,0.1,0.03,0,4,0.50,0.50,0.50,1);//handle
  cube(-0.95+2,-0.2,-11,0.2,0.03,0.03,0,4,0.50,0.50,0.50,1);//handle
  cube(-1+2,-1.7,-10.75,1,1,0.05,0,0,0.1,0.1,0.1,1);//base
  cube(-1+2,-1.7,-10.6,1.2,1.2,0.1,0,4,0.50,0.50,0.50,1);//door
  cube(0.1+2,-2.3,-10.75,0.05,0.1,0.05,0,4,0.50,0.50,0.50,1);//door hinge
  cube(0.1+2,-1.1,-10.75,0.05,0.1,0.05,0,4,0.50,0.50,0.50,1);//door hinge

  // glPopMatrix();

}
static void floor_mat(double x, double z, int th)
{
  glPushMatrix();
  // glRotatef(180,0,1,0);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ZERO);
  glRotated(th,0,1,0);
  cube(x,-3.1,z,2,0.05,1.1,0,5,1,1,1,1);//base
  glDisable(GL_BLEND);
  glPopMatrix();
}
static void cake_freezer(){
  float zz= 5.5;//moving everything back towards back wall
  glPushMatrix();
  // glRotatef(180,0,1,0);

  cube(13,0.05,-14-zz,1.7,3.3,0.1,0,4,0.50,0.50,0.50,1);//back
  cube(11.25,0.05,-12.7-zz,1.4,3.3,0.1,90,4,0.50,0.50,0.50,1);//left
  cube(12.9,-0.35,-11.4-zz,0.1,2.8,0.1,90,4,0.50,0.50,0.50,1);//middle
  cube(14.6,0.05,-12.7-zz,1.4,3.3,0.1,270,4,0.50,0.50,0.50,1);//right
  cube(12.91,-2.7,-12.69-zz,1.39,0.5,1.59,270,4,0.50,0.50,0.50,1);//bottom
  cube(12.925,3.3,-12.7-zz,1.77,0.1,1.4,0,4,0.50,0.50,0.50,1);//top
  cube(12.925,2.85,-12.51-zz,1.7,0.45,1.2,0,6,0.8,0.8,0.8,1);//top

  cube(12.1,-2.2,-11.29-zz,0.71,0.05,0.01,0,0,0.1,0.1,0.1,0.4);//l door rubber bot
  cube(11.358,0.045,-11.29-zz,0.05,2.3,0.01,0,0,0.1,0.1,0.1,0.4);//l door rubber l
  cube(12.85,0.045,-11.29-zz,0.05,2.3,0.01,0,0,0.1,0.1,0.1,0.4);//l door rubber r
  cube(12.1,2.3,-11.29-zz,0.71,0.05,0.01,0,0,0.1,0.1,0.1,0.4);//l door rubber top

  cube(13,0.045,-11.29-zz,0.05,2.3,0.01,0,0,0.1,0.1,0.1,0.4);//r door rubber l
  cube(14.51,0.045,-11.29-zz,0.05,2.3,0.01,0,0,0.1,0.1,0.1,0.4);//r door rubber r
  cube(13.758,-2.2,-11.29-zz,0.71,0.05,0.01,0,0,0.1,0.1,0.1,0.4);//r door rubber bot
  cube(13.758,2.3,-11.29-zz,0.71,0.05,0.01,0,0,0.1,0.1,0.1,0.4);//r door rubber top

  cube(12.1,-2.2,-11.235-zz,0.73,0.09,0.04,0,4,0.50,0.50,0.50,1);//l door frame bot
  cube(12.1,-2.2,-11.2-zz,0.75,0.02,0.04,0,4,0.50,0.50,0.50,1);//l door frame bot inner
  cube(11.358,0.045,-11.235-zz,0.055,2.35,0.04,0,4,0.50,0.50,0.50,1);//l door frame l
  cube(11.358,0.045,-11.2-zz,0.02,2.25,0.04,0,4,0.50,0.50,0.50,1);//l door frame l inner
  cube(12.1,2.3,-11.235-zz,0.73,0.09,0.04,0,4,0.50,0.50,0.50,1);//l door frame top
  cube(12.1,2.3,-11.2-zz,0.75,0.02,0.04,0,4,0.50,0.50,0.50,1);//l door frame top inner
  cube(12.845,0.045,-11.235-zz,0.055,2.345,0.04,0,4,0.50,0.50,0.50,1);//l door frame r
  cube(12.845,0.045,-11.2-zz,0.02,2.25,0.04,0,4,0.50,0.50,0.50,1);//l door frame r inner

  cube(13.772,-2.2,-11.235-zz,0.73,0.09,0.04,0,4,0.50,0.50,0.50,1);//r door frame bot
  cube(13.7715,-2.2,-11.2-zz,0.77,0.02,0.04,0,4,0.50,0.50,0.50,1);//r door frame bot inner
  cube(13,0.045,-11.235-zz,0.055,2.35,0.04,0,4,0.50,0.50,0.50,1);//r door frame l
  cube(13,0.045,-11.2-zz,0.02,2.25,0.04,0,4,0.50,0.50,0.50,1);//r door frame l inner
  cube(13.76,2.3,-11.235-zz,0.73,0.09,0.04,0,4,0.50,0.50,0.50,1);//r door frame top
  cube(13.755,2.3,-11.2-zz,0.77,0.02,0.04,0,4,0.50,0.50,0.50,1);//r door frame top inner
  cube(14.51,0.045,-11.235-zz,0.055,2.35,0.04,0,4,0.50,0.50,0.50,1);//r door frame r
  cube(14.51,0.045,-11.2-zz,0.02,2.25,0.04,0,4,0.50,0.50,0.50,1);//r door frame r inner

  cube(12.842,0.045,-11-zz,0.04,0.6,0.02,0,4,0.50,0.50,0.50,1);//left door handle
  cube(12.842,-0.4,-11.1-zz,0.02,0.02,0.08,0,4,0.50,0.50,0.50,1);//left door handle attach
  cube(12.842,0.45,-11.1-zz,0.02,0.02,0.08,0,4,0.50,0.50,0.50,1);//left door handle attach
  cube(12.997,0.045,-11-zz,0.04,0.6,0.02,0,4,0.50,0.50,0.50,1);//right door handle
  cube(12.997,-0.4,-11.1-zz,0.02,0.02,0.08,0,4,0.50,0.50,0.50,1);//left door handle attach
  cube(12.997,0.45,-11.1-zz,0.02,0.02,0.08,0,4,0.50,0.50,0.50,1);//left door handle attach
  int x = 11;
  int z = -14;
  double space1[5] ={0,0.5,0.9,1.7,2.9};
  for (int j=0;j<5;j+=1){//get correct spacing between racks (as seen in shop)
    double s =space1[j];
    drawCylinder(x+0.35,-2+s,z+1-zz,0.1,1,0.1,90,1,360,0,0,2);//outer wire x dir
    drawCylinder(x+2,-2+s,z+1-zz,0.1,1,0.1,90,1,360,0,0,2);//outer wire x dir
    drawCylinder(x+1+0.125,-2+s,z+0.2-zz,0.1,0.875,0.1,90,0,360,0,0,2);//outer wire z dir
    drawCylinder(x+1+0.125,-2+s,z+2-zz,0.1,0.875,0.1,90,0,360,0,0,2);//outer wire z dir

    for (double i=0;i<1.5;i+=0.1){
      drawCylinder(x+0.5+i,-2+s,z+1-zz,0.05,1,0.05,90,1,360,0,0,2);//inner rack x direction
      }
    for (double k=0;k<2;k+=0.7){
      drawCylinder(x+1+0.125,-2+s,z+k-zz,0.05,0.875,0.05,90,0,360,0,0,2);//inner rack z direction
      }
  }
  drawCylinder(13,-0.5,-12-zz,0.1,2.5,0.1,0,0,360,0,0,2);//holds up shelves
  x=-15;
  z=-14;
  glRotated(180,0,0,1);
  double space2[7] ={-0.6,0,0.6,1.2,1.8,2.5,3};
  for (int j=0;j<7;j+=1){//get correct spacing between racks (as seen in shop)
    double s =space2[j];
    drawCylinder(x+0.35,-1+s,z+1-zz,0.1,1,0.1,90,1,360,0,0,2);//outer wire x dir
    drawCylinder(x+2,-1+s,z+1-zz,0.1,1,0.1,90,1,360,0,0,2);//outer wire x dir
    drawCylinder(x+1+0.125,-1+s,z+0.2-zz,0.1,0.82,0.1,90,0,360,0,0,2);//outer wire z dir
    drawCylinder(x+1+0.125,-1+s,z+2-zz,0.1,0.82,0.1,90,0,360,0,0,2);//outer wire z dir

    for (double i=0;i<1.5;i+=0.1){
      drawCylinder(x+0.5+i,-1+s,z+1-zz,0.05,1,0.05,90,1,360,0,0,2);//inner rack x direction
      }
    for (double k=0;k<2;k+=0.7){
      drawCylinder(x+1+0.125,-1+s,z+k-zz,0.05,0.82,0.05,90,0,360,0,0,2);//inner rack z direction
      }
  }
  glPopMatrix();
  glPushMatrix();
    glRotated(-30,1,0,0);
    cube(12.91,5.4+0.8,-11-zz+.75,0.01,0.05,1.59,90,4,0.50,0.50,0.50,1);//vents
    cube(12.91,5.3+0.8,-11.1-zz+.75,0.01,0.05,1.59,90,4,0.50,0.50,0.50,1);//vents
    cube(12.91,5.2+0.8,-11.15-zz+.75,0.01,0.05,1.59,90,4,0.50,0.50,0.50,1);//vents
    cube(12.91,5.1+0.8,-11.2-zz+.75,0.01,0.05,1.59,90,4,0.50,0.50,0.50,1);//vents
    cube(12.91,5+0.8,-11.25-zz+.75,0.01,0.05,1.59,90,4,0.50,0.50,0.50,1);//vents
  glPopMatrix();
  glPushMatrix();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  cube(12.1,0.05,-11.25-5.5,0.68,2.15,0.05,0,1000,1,1,1,0.4);//left door
  cube(13.74,0.05,-11.25-5.5,0.68,2.15,0.05,0,1000,1,1,1,0.4);//right door
  glPopMatrix();
  glDisable(GL_BLEND);
}


 static void fullrail(int flip,int th){
   glPushMatrix();
   if (flip==0){
     handrail(10+2,-3.25,3,0.5,2.6,0.5,th,0);
     handrail(10+2,-.649,0.4,0.5,2.6,0.5,th,1);
     drawCylinder(10+2,-.649,-2.5,0.5,3,0.5,th,1,360,0,0,1);
   }
   else if (flip==1){
     glRotatef(180,0,1,0);
     handrail(-10-2,-3.25,7,0.5,2.6,0.5,th,0);
     handrail(-10-2,-.649,4.4,0.5,2.6,0.5,th,1);
   }
   glPopMatrix();

 }
 static void windows(){
   glPushMatrix();
   glScaled(0.9,1,1);
   glTranslated(-2,0,0);
   //sides
   cube(3.6,2.7,15,0.1,4,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(10.8,1.9,15,0.1,4.9,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(10.8+1.8,1.9,15,0.1,4.9,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(10.8+1.8+5.9,1.9,15,0.1,4.9,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(10.8+1.8+5.9-1.9,1.9,15,0.1,4.9,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(-3.6,2.7,15,0.1,4,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(-10.8,2.7,15,0.15,4,0.15,0,4,0.5,0.5,0.5,1);//window divider
   //top/bottom
   cube(0+0.9,2.7+4,15,10.9+.9,0.15,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(0+0.9,2.7-4,15,10.9+.9,0.15,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(0+0.9+10.8,2.7-4-1.7,15,1,0.15,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(0+0.9+10.8+5.8,2.7-4-1.7,15,1,0.15,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(0+0.9+10.8+5.9,2.7-4,15,1,0.15,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(0+0.9+10.8+3.9,2.7+4,15,3,0.15,0.15,0,4,0.5,0.5,0.5,1);//window divider
   cube(0+0.9+10.8+3,2.7+1,15,3.9,0.15,0.15,0,4,0.5,0.5,0.5,1);//window divider
   if(!door_open){//door
     glPushMatrix();
     cube(14.6-.05,3.435,15,1.85,0.035,0.05,0,4,0.5,0.5,0.5,1);//door top
     cube(14.6-.05,-3.1,15,1.85,0.035,0.05,0,4,0.5,0.5,0.5,1);//door bottom
     cube(14.6+1.82-.05,0.18,15,0.1,3.27,0.07,0,4,0.5,0.5,0.5,1);//door
     cube(14.6-1.82+.05,0.18,15,0.1,3.27,0.07,0,4,0.5,0.5,0.5,1);//door
     cube(14.6-.07,0,14.6,1.3,0.1,0.07,0,4,0.5,0.5,0.5,1);//door inside handle
     cube(14.6-.07,0,14.7,1.2,0.09,0.03,0,4,0.1,0.1,0.1,1);//door inside handle
     glPopMatrix();
     glPushMatrix();
     glRotated(90,0,1,0);
     glRotated(90,1,0,0);
     drawCylinder(-15.2,14.7,-1.5,4,0.01,4,90,0,360,45,0,2);//door sticker outside
     glPopMatrix();

     glPushMatrix();
     glRotated(270,0,1,0);
     glRotated(90,1,0,0);
     drawCylinder(15,-14.7,-1.5,4,0.01,4,90,0,360,45,0,2);//door sticker inside
     glPopMatrix();

     glPushMatrix();
     glTranslated(10.4,0,15.3);//door handle
     glRotated(90,1,0,0);
     glScaled(0.5,0.05,0.08);
     fullrail(0,90);
     fullrail(1,90);
     glPopMatrix();
   }
   else{
   glPushMatrix();
   glRotated(85,0,1,0);
   cube(-14.6-1-.05,3.435,15-1,1.85,0.035,0.05,0,4,0.5,0.5,0.5,1);//door top
   cube(-14.6-1-.05,-3.1,15-1,1.85,0.035,0.05,0,4,0.5,0.5,0.5,1);//door bottom
   cube(-14.6+1.82-1+.05,0.18,15-1,0.1,3.27,0.07,0,4,0.5,0.5,0.5,1);//door
   cube(-14.6-1.82-1-.05,0.18,15-1,0.1,3.27,0.07,0,4,0.5,0.5,0.5,1);//door
   glPushMatrix();
   glRotated(180,0,1,0);
   cube(14.6-.05+1,0,-14.6+0.2,1.3,0.1,0.07,0,4,0.5,0.5,0.5,1);//door inside handle
   cube(14.6-.05+1,0,-14.7+0.4,1.2,0.09,0.03,0,4,0.1,0.1,0.1,1);//door inside handle
   glPopMatrix();
   glPushMatrix();
   glRotated(90,0,1,0);
   glRotated(90,1,0,0);
   drawCylinder(-14.1,-15.6,-1.5,4,0.01,4,90,0,360,45,0,2);//door sticker outside
   glPopMatrix();

   glPushMatrix();
   glRotated(270,0,1,0);
   glRotated(90,1,0,0);
   drawCylinder(14,15.6,-1.5,4,0.01,4,90,0,360,45,0,2);//door sticker inside
   glPopMatrix();

   glPushMatrix();
   glTranslated(-11.45,0,13.8);//door handle
   glRotated(90,1,0,0);
   glRotated(180,0,0,1);
   glScaled(0.5,0.05,0.08);
   fullrail(0,90);
   fullrail(1,90);
   glPopMatrix();

   glPopMatrix();
 }
 glPopMatrix();
 }
 static void buckets(double x, double z, int num){
   for (int i=0;i<num;i+=1){
     //x=-13 z=
   drawCylinder(x,-2+i*(0.8)-0.3,z,1.6,0.4,1.6,0,0,360,100,0,2);//bucket
   drawCylinder(x,-1.62+i*(0.8)-0.3,z,1.7,0.02,1.7,0,0,360,100,0,2);//bucket lid
  //  drawCylinder(-13,-0.2-1,-7,1.6,0.4,1.6,0,0,360,100,0,2);//bucket
  //  drawCylinder(-13,0.22-1,-7,1.7,0.02,1.7,0,0,360,100,0,2);//bucket lid
 }
 }
/*
 *  Set light
 *    light>0 bright
 *    light<0 dim
 *    light=0 off
 */
static void Light(int light)
{
   //  Set light position
   Lpos[0] = 2*Cos(zh);
   Lpos[1] = Ylight;
   Lpos[2] = -2*Sin(zh);
   Lpos[3] = 1;
   Lpos2[0] = -13;
   Lpos2[1] = Ylight-25;
   Lpos2[2] = -5;
   Lpos2[3] = 1;

   //  Enable lighting
   if (light)
   {
      float Med[]  = {0.3,0.3,0.3,1.0};
      float High[] = {1.0,1.0,1.0,1.0};
      //  Enable lighting with normalization
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      glLightfv(GL_LIGHT0,GL_POSITION,Lpos);
      glLightfv(GL_LIGHT0,GL_AMBIENT,Med);
      glLightfv(GL_LIGHT0,GL_DIFFUSE,High);
      // glEnable(GL_LIGHT2);
      // glLightfv(GL_LIGHT2,GL_POSITION,Lpos2);
      // glLightfv(GL_LIGHT2,GL_AMBIENT,Med);
      // glLightfv(GL_LIGHT2,GL_DIFFUSE,High);
   }
   else
   {
      glDisable(GL_LIGHTING);
      glDisable(GL_COLOR_MATERIAL);
      glDisable(GL_NORMALIZE);
   }
}

/*
 *  Draw scene
 *    light (true enables lighting)
 */
void Scene(int light)
{

   //  Set light position and properties
   Light(light);
   //Draw scene
   glPushMatrix();
   sinks();
   dip_cab(1,-2,-2,2.5,1.5,1,0,2);
   dip_cab(1-2,-1.66,-0.5,2.5,1.5,1,180,0);
   dip_cab(15,-2,-17.5,2.5,1.5,1,0,1);
   counters(6.5+2,0,-4,1,1,4,0,1,0.5, 0.35, 0.05,1,0);//top serve top
   counters(6.2+2,-0.16,-4,0.5,4,4,0,4,0.5, 0.5, 0.5,1,0);//top serve middle
   counters(4.54+2,-0.651,0.38,0.8,1,1.6,0,4,0.50,0.50,0.50,1,0);//top serve bottom triangle 1
   counters(5.5+2,-0.65,0.38,0.4,1,0.4,0,4,0.50,0.50,0.50,1,0);//top serve bottom triangle 2
   counters(5.16+2,-0.65,-4,1.4,1,3.99,0,4,0.50,0.50,0.50,1,0);//top serve bottom
   counters(6+2,-3,-4,1,1,4,0,1,0.5, 0.35, 0.05,0,0);//bottom serve
   counters(5.5+2,-3,0,0.5,1,0.8,0,1,0.5, 0.35, 0.05,0,0);//bottom serve
   counters(6.84+2,-0.16,-4.0,0.16,18.75,4,0,1,0.5, 0.35, 0.05,0,0);//back serve
   counters(5.99+2,-0.7,-5.9,1,14.4,0.1,0,1,0.5, 0.35, 0.05,0,1);//mid divider
   Lcounter(3+2,0,3,1,19.75,1,0);
   counters(5.99+2,-0.80,-7.9,1,14.75,0.1,0,1,0.5, 0.35, 0.05,1,0);//end divider serve
   fullrail(0,90);
   fullrail(1,90);

   cube(1,-1.16,-4.25,2.4,2,0.5,0,100,1,1,1,1);//island
   cube(1,1,-4.25,2.6,0.16,0.58,0,3,0.5, 0.35, 0.05,1);//island top
   //back partial wall
   cube(-0.26,0.7,-13.55,6.6,4,0.25,0,100,1,1,1,1);
   cube(-0.26,6.7,-13.55,6.6,2,0.25,0,9,0.1, 0.5,0.8,1);//top blue back
   cube(-0.26,-1.3,-14.05,6.6,2,0.25,0,9,0.3, 0.6,0.95,1);
   cube(-0.26,4.7,-14.05,6.6,4,0.25,0,9,0.1, 0.5,0.8,1);//top blue back
   glPushMatrix();
   glRotated(90,0,1,0);
   //left partial wall -- Menuu
   cube(2,0.7,-9.8,6,4,0.5,0,100,1,1,1,1);
   cube(2,6.7,-9.8,6,2,0.5,0,9,0.1, 0.5,0.8,1);//top blue back
   //end of hallway wall
   cube(17.2,0.7,-6.9,3.9,4,0.16,0,100,1,1,1,1);
   cube(17.2,6.7,-6.9,3.9,2,0.16,0,9,0.1, 0.5,0.8,1);//top blue back
   cube(17.2,-1.3,-6.7,3.8,2,0.16,0,9,0.3, 0.6,0.95,1);
   cube(17.2,4.7,-6.7,3.8,4,0.16,0,9,0.1, 0.5,0.8,1);//top blue back
   glPopMatrix();
   metro_rack(-12,0,4,0,0);//backup cake cones
   metro_rack(-9,0,-18.5,1,0);//backup sugar cones
   metro_rack(13.7,0,-9.5,1,0);//sink area
   glPushMatrix();
   glScaled(0.7,0.8,0.7);
   metro_rack(-26,0,-9,0,1);//walk in
   glPopMatrix();
   glPushMatrix();
   glRotated(90,0,1,0);
   glScaled(0.7,0.8,0.7);
   metro_rack(-5,0,-18,0,1);//walk in
   glPopMatrix();
   seats(5.5,4.8,1);
   glPushMatrix();
   glRotatef(180,0,1,0);
   seats(3.8,-12.8,0);
   glPopMatrix();
   cube(-5.4,-1.35,13.25,0.3,1.8,1.7,0,9,0.1, 0.5,0.8,1);//small wall between fton seats/window tables
   cube(-5.4,0.5,13.2,0.35,0.1,1.755,0,3,0.5f,0.35f,0.05f,1);//top for above
   cube(1.3,0,14,6.4,0.1,0.7,0,3,0.5f,0.35f,0.05f,1);//counter seats near window
   cube(-3,-1,14.7,0.1,1,0.05,0,4,0.1, 0.1,0.1,1);//holds up counter by window
   cube(0,-1,14.7,0.1,1,0.05,0,4,0.1, 0.1,0.1,1);//holds up counter by window
   cube(3,-1,14.7,0.1,1,0.05,0,4,0.1, 0.1,0.1,1);//holds up counter by window
   cube(6,-1,14.7,0.1,1,0.05,0,4,0.1, 0.1,0.1,1);//holds up counter by window
   glPushMatrix();
   glRotated(-45,1,0,0);
   cube(-3,-1-10+.7,1+9,0.1,0.4,0.05,0,4,0.1, 0.1,0.1,1);//holds up counter by window
   cube(0,-1-10+.7,1+9,0.1,0.4,0.05,0,4,0.1, 0.1,0.1,1);//holds up counter by window
   cube(3,-1-10+.7,1+9,0.1,0.4,0.05,0,4,0.1, 0.1,0.1,1);//holds up counter by window
   cube(6,-1-10+.7,1+9,0.1,0.4,0.05,0,4,0.1, 0.1,0.1,1);//holds up counter by window
   glPopMatrix();
   cube(-14,0.5,12.4,3,3.5,2,0,4,0.50,0.50,0.50,1);//fridge
   cube(-14,0,10.3,1.5,2.9,0.1,0,4,0.5,0.5,0.5,1);//fridge door
   cube(-14.7,0,10.1,0.5,0.05,0.05,0,4,1,1,1,1);//fridge handle
   cube(-15,0,10.29,0.05,0.05,0.15,0,4,1,1,1,1);//fridge handle
   cube(-14.4,0,10.29,0.05,0.05,0.15,0,4,1,1,1,1);//fridge handle
   tables(-10+1,-7.7+1,2,0);//shake station 1
   tables(-10+1,-0.3+1,0,0);//backup table
   tables(-10+1,-4+1,3,0);//big table with additional top
   tables(-14,-9,1,1);//big table near window
   tables(-5,-13,0,0);//shake station 2
   tables(-2.5,-13,0,0);//shake station 3
   toppings_fridge();

   cake_freezer();
   shakes(-5.9+2,-0.25,-12.95,0);
   shakes(-3.4+2,-0.25,-12.95,0);
   shakes(6.7-1,-0.25,-10+1,1);
   walk_in();
   glPushMatrix();
   glRotatef(90,0,1,0);
   cube(3,2.7,-19,18,6,0.16,0,100,0.9,0.9,0.9,0.9);//left farthest wall
   glPopMatrix();
   windows();
   buckets(-11.5,-7,4);
   buckets(-11.5,-6,2);
   buckets(-11.5,-4,3);
   buckets(-11.5,-3,5);
   buckets(-12.5,-3,2);
   buckets(-11.5,-1,3);
   buckets(-13.5,3,3);
   buckets(-14.5,3,1);
   buckets(-15.5,3,5);
   buckets(-16.5,3,6);
   buckets(-17.8,3,6);
   buckets(-17.8,2,6);
   buckets(-16.8,2,3);
   buckets(-17.8,1,5);
   buckets(-17.8,0,3);
   buckets(-17.8,-1,4);
   glPopMatrix();
   //  Disable textures
   //if (light) glDisable(GL_TEXTURE_2D);

   //  The floor, ceiling and walls don't cast a shadow, so bail here
   if (!light) return;
    glPushMatrix();
    glRotatef(180,0,1,0);

    cube(2,-3.32,3,17,0.16,18,0,2,0.5, 0.5, 0.5,1);//floor
    glPopMatrix();
    cube(-13,2.7,-21,6,6,0.16,0,100,0.9,0.9,0.9,0.9);//back left wall
    menu(-4.25);
    menu(-1.4);
    menu(1.4);
    walls();

    floor_mat(-1+2,0.78,0);
    floor_mat(-1+2,-9.2,0);
    floor_mat(1.5,3.3+2,90);
    floor_mat(5.6,3.3+2,90);
    floor_mat(3-1,-6.7+1,90);
    flavors();
    circle_mags();
    cube(-15.45,2.7,15.1,3.8,6.1,0.16,0,44,0.1,0.3,0.8,1);//tall brick
    cube(1.68,7.8,15.1,13.38,1,0.16,0,44,0.1,0.3,0.8,1);//long brick top
    cube(-1,-2.45,15.1,10.65,1,0.16,0,44,0.1,0.3,0.8,1);
   //  Enable textures for floor, ceiling and walls
  //  glEnable(GL_TEXTURE_2D);
  //
  //  //  Water texture for floor and ceiling
  //  glBindTexture(GL_TEXTURE_2D,tex2d[0]);
  //  glColor3f(1.0,1.0,1.0);
  //  for (k=-1;k<=box;k+=2)
      // Wall(0,0,0, 0,90*k , 8,8,box?6:2 , 4);
  //  //  Crate texture for walls
  //  glBindTexture(GL_TEXTURE_2D,tex2d[1]);
  //  for (k=0;k<4*box;k++)
      // Wall(0,0,0, 90*k,0 , 8,box?6:2,8 , 1);

   //  Disable textures
  //  glDisable(GL_TEXTURE_2D);
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   int id;
   const double len=1.5;
   glEnable(GL_DEPTH_TEST);
   glLoadIdentity();
   //  Erase the window and the depth buffers
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Disable lighting
   glDisable(GL_LIGHTING);
   //  Eye position
  //  float Ex = -2*dim*Sin(th)*Cos(ph);
  //  float Ey = +2*dim        *Sin(ph);
  //  float Ez = +2*dim*Cos(th)*Cos(ph);
  if (fp) {
   Cx = +2*dim*Sin(rot); //Ajust the camera vector based on rot
   Cz = -2*dim*Cos(rot);
   gluLookAt(Ex,Ey,Ez, Cx+Ex,Ey,Cz+Ez, 0,1,0); //  Use gluLookAt, y is the up-axis
 }
 else {
    //  Perspective - set eye position
    if (mode)
    {
      //glUseProgram(0);
       double px = -2*dim*Sin(viewth)*Cos(viewph);
       double py = +2*dim        *Sin(viewph);
       double pz = +2*dim*Cos(viewth)*Cos(viewph);
       gluLookAt(px,py,pz , 0,0,0 , 0,Cos(viewph),0);
      //  Project(fov,asp,dim);
      //  glViewport(0,0,Width,Height);
    }
    //  Orthogonal - set world orientation
    else
    {
       glRotatef(viewph,1,0,0);
       glRotatef(viewth,0,1,0);
       //glViewport(0,0,Width,Height);
    }

 }

      glViewport(0,0,Width,Height);

   //  Draw light position as sphere (still no lighting here)
   glColor3f(1,1,1);
   glPushMatrix();
   glTranslated(Lpos[0],Lpos[1],Lpos[2]);
   glutSolidSphere(0.03,10,10);
   glPopMatrix();
   //  Enable shader program
   if (shadows){
   glUseProgram(shader);
   id = glGetUniformLocation(shader,"tex");
   if (id>=0) glUniform1i(id,0);
   id = glGetUniformLocation(shader,"depth");
   if (id>=0) glUniform1i(id,1);

   // Set up the eye plane for projecting the shadow map on the scene
   glActiveTexture(GL_TEXTURE1);
   glTexGendv(GL_S,GL_EYE_PLANE,Svec);
   glTexGendv(GL_T,GL_EYE_PLANE,Tvec);
   glTexGendv(GL_R,GL_EYE_PLANE,Rvec);
   glTexGendv(GL_Q,GL_EYE_PLANE,Qvec);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE);
   glActiveTexture(GL_TEXTURE0);}

   // Draw objects in the scene (including walls)
   Scene(1);

   //  Disable shader program
   glUseProgram(0);
   //draw windows
   glPushMatrix();
   glScaled(0.9,1,1);
   glTranslated(-2,0,0);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    cube(0,2.7,15,3.55,4,0.05,0,1000,0.5,0.5,0.5,0.5);//middle big window
    cube(7.2,2.7,15,3.5,4,0.05,0,1000,0.5,0.5,0.5,0.5);//right big window
    cube(-7.2,2.7,15,3.5,4,0.05,0,1000,0.5,0.5,0.5,0.5);//left big window
    cube(11.6,1.9,15,0.9,4.9,0.05,0,1000,0.5,0.5,0.5,0.5);//left small window
    cube(17.5,1.9,15,0.9,4.9,0.05,0,1000,0.5,0.5,0.5,0.5);//right small window
    cube(14.5,5.1,15,2,1.5,0.05,0,1000,0.5,0.5,0.5,0.5);//top small window
    if (!door_open){
      cube(14.6,0.15,15,1.8,3.225,0.05,0,1000,0.5,0.5,0.5,0.5);//door
    }
    else{
      glPushMatrix();
      glRotated(85,0,1,0);
      cube(-14.6-1,0.15,15-1,1.8,3.225,0.05,0,1000,0.5,0.5,0.5,0.5);//door
      glPopMatrix();
    }
    glPopMatrix();
    glDisable(GL_BLEND);
   //  Draw axes (white)
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }

glWindowPos2i(5,5);
  if (fp) {
      Print("FP=On View Angle=%d",rot);
      glWindowPos2i(5,25);
   }

else{
  Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s" ,
    viewth,viewph,dim,fov,mode?"Perpective":"Orthogonal");
}

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  Build Shadow Map
 */
void ShadowMap(void)
{
   double Lmodel[16];  //  Light modelview matrix
   double Lproj[16];   //  Light projection matrix
   double Tproj[16];   //  Texture projection matrix
   double Dim=20.0;     //  Bounding radius of scene
   double Ldist;       //  Distance from light to scene center

   //  Save transforms and modes
   glPushMatrix();
   glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
   //  No write to color buffer and no smoothing
   glShadeModel(GL_FLAT);
   glColorMask(0,0,0,0);
   // Overcome imprecision
   glEnable(GL_POLYGON_OFFSET_FILL);

   //  Turn off lighting and set light position
   Light(0);

   //  Light distance
   Ldist = sqrt(Lpos[0]*Lpos[0] + Lpos[1]*Lpos[1] + Lpos[2]*Lpos[2]);
   if (Ldist<1.1*Dim) Ldist = 1.1*Dim;

   //  Set perspective view from light position
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(114.6*atan(Dim/Ldist),1,Ldist-Dim,Ldist+Dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(Lpos[0],Lpos[1],Lpos[2] , 0,0,0 , 0,1,0);
   //  Size viewport to desired dimensions
   glViewport(0,0,shadowdim,shadowdim);

   // Redirect traffic to the frame buffer
   glBindFramebuffer(GL_FRAMEBUFFER,framebuf);

   // Clear the depth buffer
   glClear(GL_DEPTH_BUFFER_BIT);
   // Draw all objects that can cast a shadow
   Scene(0);

   //  Retrieve light projection and modelview matrices
   glGetDoublev(GL_PROJECTION_MATRIX,Lproj);
   glGetDoublev(GL_MODELVIEW_MATRIX,Lmodel);

   // Set up texture matrix for shadow map projection,
   // which will be rolled into the eye linear
   // texture coordinate generation plane equations
   glLoadIdentity();
   glTranslated(0.5,0.5,0.5);
   glScaled(0.5,0.5,0.5);
   glMultMatrixd(Lproj);
   glMultMatrixd(Lmodel);

   // Retrieve result and transpose to get the s, t, r, and q rows for plane equations
   glGetDoublev(GL_MODELVIEW_MATRIX,Tproj);
   Svec[0] = Tproj[0];    Tvec[0] = Tproj[1];    Rvec[0] = Tproj[2];    Qvec[0] = Tproj[3];
   Svec[1] = Tproj[4];    Tvec[1] = Tproj[5];    Rvec[1] = Tproj[6];    Qvec[1] = Tproj[7];
   Svec[2] = Tproj[8];    Tvec[2] = Tproj[9];    Rvec[2] = Tproj[10];   Qvec[2] = Tproj[11];
   Svec[3] = Tproj[12];   Tvec[3] = Tproj[13];   Rvec[3] = Tproj[14];   Qvec[3] = Tproj[15];

   // Restore normal drawing state
   glShadeModel(GL_SMOOTH);
   glColorMask(1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);
   glPopAttrib();
   glPopMatrix();
   glBindFramebuffer(GL_FRAMEBUFFER,0);

   //  Check if something went wrong
   ErrCheck("ShadowMap");
}

/*
 *
 */
void InitMap()
{
   unsigned int shadowtex; //  Shadow buffer texture id
   int n;

   //  Make sure multi-textures are supported
   glGetIntegerv(GL_MAX_TEXTURE_UNITS,&n);
   if (n<2) Fatal("Multiple textures not supported\n");

   //  Get maximum texture buffer size
   glGetIntegerv(GL_MAX_TEXTURE_SIZE,&shadowdim);
   //  Limit texture size to maximum buffer size
   glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE,&n);
   if (shadowdim>n) shadowdim = n;
   //  Limit texture size to 2048 for performance
   if (shadowdim>2048) shadowdim = 2048;
   if (shadowdim<512) Fatal("Shadow map dimensions too small %d\n",shadowdim);

   //  Do Shadow textures in MultiTexture 1
   glActiveTexture(GL_TEXTURE1);

   //  Allocate and bind shadow texture
   glGenTextures(1,&shadowtex);
   glBindTexture(GL_TEXTURE_2D,shadowtex);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, shadowdim, shadowdim, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

   //  Map single depth value to RGBA (this is called intensity)
   glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE,GL_INTENSITY);

   //  Set texture mapping to clamp and linear interpolation
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   //  Set automatic texture generation mode to Eye Linear
   glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
   glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
   glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
   glTexGeni(GL_Q,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);

   // Switch back to default textures
   glActiveTexture(GL_TEXTURE0);

   // Attach shadow texture to frame buffer
   glGenFramebuffers(1,&framebuf);
   glBindFramebuffer(GL_FRAMEBUFFER,framebuf);
   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowtex, 0);
   //  Don't write or read to visible color buffer
   glDrawBuffer(GL_NONE);
   glReadBuffer(GL_NONE);
   //  Make sure this all worked
   if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) Fatal("Error setting up frame buffer\n");
   glBindFramebuffer(GL_FRAMEBUFFER,0);

   //  Check if something went wrong
   ErrCheck("InitMap");

   //  Create shadow map
   ShadowMap();
}

/*
 *  GLUT calls this routine when nothing else is going on
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,1440.0);
   //  Update shadow map
   ShadowMap();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
   //  Schedule update
  //if (move) glutTimerFunc(dt,idle,0);
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
  if(!fp) {
    //  Right arrow key - increase angle by 5 degrees
    if (key == GLUT_KEY_RIGHT)
       viewth += 5;
    //  Left arrow key - decrease angle by 5 degrees
    else if (key == GLUT_KEY_LEFT)
       viewth -= 5;
    //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_UP)
       viewph += 5;
    //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN)
       viewph -= 5;
    //  Keep angles to +/-360 degrees
     //  PageUp key - increase dim
     else if (key == GLUT_KEY_PAGE_UP && dim>1)
        dim -= 0.1;
     //  PageDown key - decrease dim
     else if (key == GLUT_KEY_PAGE_DOWN)
        dim += 0.1;
     //  Keep angles to +/-360 degrees
     viewth %= 360;
     viewph %= 360;
  }
  //  Update projection
  myProject();
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0'){
      viewth = 15;
      viewph = 20;

    }
   //  open door
    else if (ch == 'o' || ch=='O') {
       door_open = 1-door_open;
     }
     else if (ch == 'f' || ch == 'F')
     {
        fp = 1-fp;
     }
     else if(ch=='b'||ch=='B'){
       Ex=-15;
       Ez=-18;
       rot=-180;
       shadows=1-shadows;
     }
     else if (ch==' '){
     shadows=1-shadows;}
     if (fp) {
        double dt = 0.05;
        if (ch == '0'){
           Ey = 1.5;
           Ex = 13;
           Ez= 24;
           rot= -15;

         }
        else if (ch == 'w' || ch == 'W'){
           Ex += Cx*dt; //Update the eye vector based on the camera vector
           Ez += Cz*dt;
        }
        else if (ch == 'a' || ch == 'A'){
           rot -= 5;
        }
        else if (ch == 's' || ch == 'S'){
           Ex -= Cx*dt;
           Ez -= Cz*dt;
        }
        else if (ch == 'd' || ch == 'D'){
           rot += 5;
        }

        //  Keep angles to +/-360 degrees
        rot %= 360;
     }
     else {
        //  Reset view angle
        if (ch == '0'){
          viewth=15;
          viewph=20;
        }
        //  Switch display mode
        else if (ch == 'm' || ch == 'M')
           mode = 1-mode;
           //  Change field of view angle
           else if (ch == '-' && ch>1){
              fov--;}
           else if (ch == '+' && ch<179) {
              fov++;}


     }
   //  Update screen size when mode changes
  //  if (ch == 'm' || ch == 'M') glutReshapeWindow(mode?2*Width:Width/2,Height);
   //  Update shadow map if light position or objects changed
   if (strchr("<>oO-+[]",ch)) ShadowMap();
   //  Animate if requested
  glutIdleFunc(move?NULL:NULL);
   //  Update projection
   myProject();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Store window dimensions
   Width  = width;
   Height = height;
   //  Set the viewport to the entire window
   glViewport(0,0, Width,Height);

   //  Set projection
   myProject();
}

//
//  Read text file
//
static char* ReadText(const char *file)
{
   int   n;
   char* buffer;
   //  Open file
   FILE* f = fopen(file,"rt");
   if (!f) Fatal("Cannot open text file %s\n",file);
   //  Seek to end to determine size, then rewind
   fseek(f,0,SEEK_END);
   n = ftell(f);
   rewind(f);
   //  Allocate memory for the whole file
   buffer = (char*)malloc(n+1);
   if (!buffer) Fatal("Cannot allocate %d bytes for text file %s\n",n+1,file);
   //  Snarf the file
   if (fread(buffer,n,1,f)!=1) Fatal("Cannot read %d bytes for text file %s\n",n,file);
   buffer[n] = 0;
   //  Close and return
   fclose(f);
   return buffer;
}

//
//  Print Shader Log
//
static void PrintShaderLog(int obj,const char* file)
{
   int len=0;
   glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&len);
   if (len>1)
   {
      int n=0;
      char* buffer = (char *)malloc(len);
      if (!buffer) Fatal("Cannot allocate %d bytes of text for shader log\n",len);
      glGetShaderInfoLog(obj,len,&n,buffer);
      fprintf(stderr,"%s:\n%s\n",file,buffer);
      free(buffer);
   }
   glGetShaderiv(obj,GL_COMPILE_STATUS,&len);
   if (!len) Fatal("Error compiling %s\n",file);
}

//
//  Print Program Log
//
void PrintProgramLog(int obj)
{
   int len=0;
   glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&len);
   if (len>1)
   {
      int n=0;
      char* buffer = (char *)malloc(len);
      if (!buffer) Fatal("Cannot allocate %d bytes of text for program log\n",len);
      glGetProgramInfoLog(obj,len,&n,buffer);
      fprintf(stderr,"%s\n",buffer);
   }
   glGetProgramiv(obj,GL_LINK_STATUS,&len);
   if (!len) Fatal("Error linking program\n");
}

//
//  Create Shader
//
void CreateShader(int prog,const GLenum type,const char* file)
{
   //  Create the shader
   int shader = glCreateShader(type);
   //  Load source code from file
   char* source = ReadText(file);
   glShaderSource(shader,1,(const char**)&source,NULL);
   free(source);
   //  Compile the shader
   glCompileShader(shader);
   //  Check for errors
   PrintShaderLog(shader,file);
   //  Attach to shader program
   glAttachShader(prog,shader);
}

//
//  Create Shader Program
//
int CreateShaderProg(const char* VertFile,const char* FragFile)
{
   //  Create program
   int prog = glCreateProgram();
   //  Create and compile vertex shader
   if (VertFile) CreateShader(prog,GL_VERTEX_SHADER,VertFile);
   //  Create and compile fragment shader
   if (FragFile) CreateShader(prog,GL_FRAGMENT_SHADER,FragFile);
   //  Link program
   glLinkProgram(prog);
   //  Check for errors
   PrintProgramLog(prog);
   //  Return name
   return prog;
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Final Project - Nhi Nguyen");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
   if (!GLEW_VERSION_2_0) Fatal("OpenGL 2.0 not supported\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(NULL);
   //  Load textures
   tex2d[0] = LoadTexBMP("whitewall1.bmp");
   tex2d[1] = LoadTexBMP("cow.bmp");
   tex2d[2] = LoadTexBMP("floor.bmp");
   tex2d[3] = LoadTexBMP("counter.bmp");
   tex2d[4] = LoadTexBMP("metal.bmp");
   tex2d[5] = LoadTexBMP("floormat2.bmp");
   tex2d[6] = LoadTexBMP("simplymoolicious.bmp");
   tex2d[7] = LoadTexBMP("wood_panel.bmp");
   tex2d[8] = LoadTexBMP("walk_in.bmp");
   tex2d[9] = LoadTexBMP("white.bmp");
   tex2d[10] = LoadTexBMP("flav1.bmp");
   tex2d[11] = LoadTexBMP("flav2.bmp");
   tex2d[12] = LoadTexBMP("flav3.bmp");
   tex2d[13] = LoadTexBMP("flav4.bmp");
   tex2d[14] = LoadTexBMP("flav5.bmp");
   tex2d[15] = LoadTexBMP("flav6.bmp");
   tex2d[16] = LoadTexBMP("flav7.bmp");
   tex2d[17] = LoadTexBMP("flav8.bmp");
   tex2d[18] = LoadTexBMP("flav9.bmp");
   tex2d[19] = LoadTexBMP("flav10.bmp");
   tex2d[20] = LoadTexBMP("flav11.bmp");
   tex2d[21] = LoadTexBMP("flav12.bmp");
   tex2d[22] = LoadTexBMP("flav13.bmp");
   tex2d[23] = LoadTexBMP("flav14.bmp");
   tex2d[24] = LoadTexBMP("flav15.bmp");
   tex2d[25] = LoadTexBMP("flav16.bmp");
   tex2d[26] = LoadTexBMP("flav17.bmp");
   tex2d[27] = LoadTexBMP("flav18.bmp");
   tex2d[28] = LoadTexBMP("flav19.bmp");
   tex2d[29] = LoadTexBMP("flav20.bmp");
   tex2d[30] = LoadTexBMP("flav21.bmp");
   tex2d[31] = LoadTexBMP("flav22.bmp");
   tex2d[32] = LoadTexBMP("flav23.bmp");
   tex2d[33] = LoadTexBMP("flav24.bmp");
   tex2d[34] = LoadTexBMP("bigmag1.bmp");
   tex2d[35] = LoadTexBMP("bigmag2.bmp");
   tex2d[36] = LoadTexBMP("littlemag1.bmp");
   tex2d[37] = LoadTexBMP("littlemag2.bmp");
   tex2d[38] = LoadTexBMP("littlemag3.bmp");
   tex2d[39] = LoadTexBMP("bigmag3.bmp");
   tex2d[40] = LoadTexBMP("bigmag4.bmp");
   tex2d[41] = LoadTexBMP("littlemag4.bmp");
   tex2d[42] = LoadTexBMP("littlemag5.bmp");
   tex2d[43] = LoadTexBMP("littlemag6.bmp");
   tex2d[44] = LoadTexBMP("bricks.bmp");
   tex2d[45] = LoadTexBMP("cow2.bmp");

   // Enable Z-buffer
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glPolygonOffset(4,0);
   //  Initialize texture map
   shader = CreateShaderProg("shadow.vert","shadow.frag");
   //  Initialize texture map
   InitMap();
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
