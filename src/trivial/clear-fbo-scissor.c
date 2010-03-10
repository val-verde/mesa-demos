/*
 * Use scissor to clear the four quadrants of the FBO to different
 * colors.  Then draw a grey triangle in the middle.
 */


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/glut.h>


static int Width = 512, Height = 512;
static GLuint MyFB, MyRB;


#define CheckError() assert(glGetError() == 0)


static void
Init(void)
{
   fprintf(stderr, "GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
   fprintf(stderr, "GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
   fprintf(stderr, "GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
   fflush(stderr);

   if (!glutExtensionSupported("GL_EXT_framebuffer_object")) {
      printf("GL_EXT_framebuffer_object not found!\n");
      exit(0);
   }

   glGenFramebuffersEXT(1, &MyFB);
   glGenRenderbuffersEXT(1, &MyRB);

   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, MyFB);

   glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, MyRB);

   glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                                GL_RENDERBUFFER_EXT, MyRB);

   glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB, Width, Height);

   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}


static void
Reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);

   Width = width;
   Height = height;
   glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGB, Width, Height);
}


static void
Key(unsigned char key, int x, int y)
{
   if (key == 27) {
      exit(0);
   }
   glutPostRedisplay();
}


static void
Draw(void)
{
   GLboolean scissor = GL_TRUE;
   GLboolean copyPix = GL_FALSE;

   /* draw to user framebuffer */
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, MyFB);
   glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
   glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);

   glViewport(0, 0, Width, Height);
   CheckError();

   if (scissor) {
      glEnable(GL_SCISSOR_TEST);

      /* lower-left = red */
      glClearColor(1, 0, 0, 0);
      glScissor(0, 0, Width / 2, Height / 2);
      glClear(GL_COLOR_BUFFER_BIT); 

      /* lower-right = green */
      glClearColor(0, 1, 0, 0);
      glScissor(Width / 2, 0, Width - Width / 2, Height / 2);
      glClear(GL_COLOR_BUFFER_BIT); 

      /* upper-left = blue */
      glClearColor(0, 0, 1, 0);
      glScissor(0, Height / 2, Width / 2, Height - Height / 2);
      glClear(GL_COLOR_BUFFER_BIT); 

      /* upper-right = white */
      glClearColor(1, 1, 1, 0);
      glScissor(Width / 2, Height / 2, Width - Width / 2, Height - Height / 2);
      glClear(GL_COLOR_BUFFER_BIT); 

      glDisable(GL_SCISSOR_TEST);
   }
   else {
      glClearColor(0, 1, 0, 0);
      glClear(GL_COLOR_BUFFER_BIT);
   }

   /* gray triangle in middle, pointing up */
   glColor3f(0.5, 0.5, 0.5);
   glBegin(GL_TRIANGLES);
   glVertex2f(Width/4, Height/4);
   glVertex2f(Width*3/4, Height/4);
   glVertex2f(Width/2, Height*3/4);
   glVertex2f(-0.5, -0.5);
   glVertex2f(+0.5, -0.5);
   glVertex2f( 0.0, 0.7);
   glEnd();

   CheckError();

   /* copy fbo to window */
   glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, MyFB);
   glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
   glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
   glDrawBuffer(GL_BACK);
   
   if (copyPix) {
      glWindowPos2i(0, 0);
      glCopyPixels(0, 0, Width, Height, GL_COLOR);
   }
   else {
      GLubyte *buffer = malloc(Width * Height * 4);

      /* read from user framebuffer */
      glReadPixels(0, 0, Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

      /* draw to window */
      glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
      glWindowPos2iARB(0, 0);
      glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

      free(buffer);
   }

   /* Bind normal framebuffer */
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

   glutSwapBuffers();

   CheckError();
}


int
main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowPosition(100, 0);
   glutInitWindowSize(Width, Height);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

   if (!glutCreateWindow(argv[0])) {
      exit(1);
   }

   glewInit();
   Init();
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Key);
   glutDisplayFunc(Draw);
   glutMainLoop();
   return 0;
}
