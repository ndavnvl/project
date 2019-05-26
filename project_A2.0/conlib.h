/*////////////////////////////////////////////////////////////////////////////
// CONLIB.h : console helper functions for Advanced Programming Workshop
////////////////////////////////////////////////////////////////////////////*/

#ifndef __CONLIB_H__
#define __CONLIB_H__

////////////////////////////////////////////////////////////////////////////*/

int	GotoXY(int x, int y);			/* moves cursor to given position (x,y) */
int	MaxXY(int *px, int *py);		/* retrieves current maximal window coordinates */
int	ClearConsole();					/* clears console window */


int	ConShowCursor(int bVisible);	/* controls the cursor visibility (depends on bVisible value) */

/*////////////////////////////////////////////////////////////////////////////
// Input functions
////////////////////////////////////////////////////////////////////////////*/

int KeyPressed();	/* non zero if key was pressed */
int GetKey();		/* returns key code, positive means regular character,
					   negative means extended character */

/*////////////////////////////////////////////////////////////////////////////
// Special characters codes
////////////////////////////////////////////////////////////////////////////*/

#define KEY_ESC		27

/*////////////////////////////////////////////////////////////////////////////
// Extended characters codes
////////////////////////////////////////////////////////////////////////////*/

#define KEY_UP		-72		/* Up arrow */
#define KEY_LEFT	-75		/* Left arrow */
#define KEY_RIGHT	-77		/* Right arrow */
#define KEY_DOWN	-80		/* Down arrow */

/*////////////////////////////////////////////////////////////////////////////
// Text atrributes
////////////////////////////////////////////////////////////////////////////*/

#ifndef FOREGROUND_BLUE

#define FOREGROUND_BLUE      0x0001 /* text color contains blue. */
#define FOREGROUND_GREEN     0x0002 /* text color contains green. */
#define FOREGROUND_RED       0x0004 /* text color contains red. */
#define FOREGROUND_INTENSITY 0x0008 /* text color is intensified. */
#define BACKGROUND_BLUE      0x0010 /* background color contains blue. */
#define BACKGROUND_GREEN     0x0020 /* background color contains green. */
#define BACKGROUND_RED       0x0040 /* background color contains red. */
#define BACKGROUND_INTENSITY 0x0080 /* background color is intensified. */

#endif /* FOREGROUND_BLUE */

/* sets current text (foreground&background) attribute */
int SetColor(int color);

#endif /*__CONLIB_H__ */
