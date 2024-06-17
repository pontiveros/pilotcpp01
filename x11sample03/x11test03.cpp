/* ****************************************************************************** */
/* ****************************************************************************** */
/* **** File: x11test03.cpp                                                  **** */
/* **** Compile: gcc x11test02.cpp -L/usr/X11R6/lib -lX11 -o prog02          **** */
/* **** Debug: gdb                                                           **** */
/* ****************************************************************************** */
/* ****************************************************************************** */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_WIDTH  800 
#define WINDOW_HEIGHT 600

int main(void) {
    // Init Display view
    Display *d;
    Window w;
    XEvent e;
    GC gc;
    const char *msg = "Hello, World!";
    int s;
    XFontStruct *fontInfo;
    XColor color, dummy;
    XGCValues gr_values;

    d = XOpenDisplay(NULL);

    if (d == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1, BlackPixel(d, s), WhitePixel(d, s));

    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    // Variables
    Pixmap bitmap;
    unsigned int bitmap_width  = WINDOW_WIDTH / 2;
    unsigned int bitmap_height = WINDOW_HEIGHT / 2;

    int rectX = (WINDOW_WIDTH / 4);
    int rectY = (WINDOW_HEIGHT / 4);
   
    XAllocNamedColor(d, DefaultColormap(d, s),"blue", &color,&dummy);
   
    fontInfo = XLoadQueryFont(d,"6x10");

    gr_values.font = fontInfo->fid;
    gr_values.foreground = color.pixel;

    gc = XCreateGC(d,w,GCFont+GCForeground, &gr_values);

    int rc = XReadBitmapFile(d, w, "usersimage.bmp", &bitmap_width, &bitmap_height, &bitmap, &rectX, &rectY);
    XCopyPlane(d, bitmap, w, gc,0, 0, bitmap_width, bitmap_height,0, 0, 1);
    XMapWindow(d, w);
    XFlush(d);

   int running = 1;
   while (running != 0) {
      int nResult = XNextEvent(d, &e);
      printf("nResult: %d...\n", nResult);
      printf("e.type: %d\n", e.type);
 
      if (e.type == KeyRelease) {
         printf("keymap-type: %d\n", e.xkeymap.type);
         printf("xkey-keycode: %u\n", e.xkey.keycode);
         printf("xkey-state: %u\n", e.xkey.state);
         running = 0;
      }
   }

   XCloseDisplay(d);
   return 0;
}
