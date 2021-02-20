/*
 * (c) Copyright 1996 Digital Equipment Corporation.
 * (c) Copyright 1996 Hewlett-Packard Company.
 * (c) Copyright 1996 International Business Machines Corp.
 * (c) Copyright 1996 Sun Microsystems, Inc.
 * (c) Copyright 1996 Novell, Inc.
 * (c) Copyright 1996 FUJITSU LIMITED.
 * (c) Copyright 1996 Hitachi.
 *
 * $TOG: XpmI.h /main/10 1999/09/01 17:16:10 mgreess $
 */

#ifndef _XpmI_h
#define _XpmI_h

#ifdef __cplusplus
extern "C" {
#endif

/* Xpm internal symbols are prefixed with _Xm */

#define xpmParseData _XmxpmParseData
#define xpmParseDataAndCreate _XmxpmParseDataAndCreate
#define xpmFreeColorTable _XmxpmFreeColorTable
#define xpmInitAttributes _XmxpmInitAttributes
#define xpmInitXpmImage _XmxpmInitXpmImage
#define xpmInitXpmInfo _XmxpmInitXpmInfo
#define xpmSetInfoMask _XmxpmSetInfoMask
#define xpmSetInfo _XmxpmSetInfo
#define xpmSetAttributes _XmxpmSetAttributes
#define xpmCreatePixmapFromImage _XmxpmCreatePixmapFromImage
#define xpmCreateImageFromPixmap _XmxpmCreateImageFromPixmap
#define xpmHashTableInit _XmxpmHashTableInit
#define xpmHashTableFree _XmxpmHashTableFree
#define xpmHashSlot _XmxpmHashSlot
#define xpmHashIntern _XmxpmHashIntern
#define xpmNextString _XmxpmNextString
#define xpmNextUI _XmxpmNextUI
#define xpmGetString _XmxpmGetString
#define xpmNextWord _XmxpmNextWord
#define xpmGetCmt _XmxpmGetCmt
#define xpmParseHeader _XmxpmParseHeader
#define xpmParseValues _XmxpmParseValues
#define xpmParseColors _XmxpmParseColors
#define xpmParseExtensions _XmxpmParseExtensions
#define xpmReadRgbNames _XmxpmReadRgbNames
#define xpmGetRgbName _XmxpmGetRgbName
#define xpmFreeRgbNames _XmxpmFreeRgbNames
#define xpmGetRGBfromName _XmxpmGetRGBfromName
#define xpm_xynormalizeimagebits _Xmxpm_xynormalizeimagebits
#define xpm_znormalizeimagebits _Xmxpm_znormalizeimagebits
#define xpmstrdup _Xmxpmstrdup
#define xpmstrcasecmp _Xmxpmstrcasecmp
#define xpmatoui _Xmxpmatoui
#define xpmDataTypes _XmxpmDataTypes
#define xpmColorKeys _XmxpmColorKeys

/* The following is the original XpmI.h header file,
   except that it includes XpmP.h instead of xpm.h */

/*
 * Copyright (C) 1989-95 GROUPE BULL
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * GROUPE BULL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of GROUPE BULL shall not be
 * used in advertising or otherwise to promote the sale, use or other dealings
 * in this Software without prior written authorization from GROUPE BULL.
 */

/*****************************************************************************\
* XpmI.h:                                                                     *
*                                                                             *
*  XPM library                                                                *
*  Internal Include file                                                      *
*                                                                             *
*  ** Everything defined here is subject to changes any time. **              *
*                                                                             *
*  Developed by Arnaud Le Hors                                                *
\*****************************************************************************/

/*
 * The code related to FOR_MSW has been added by
 * HeDu (hedu@cul-ipn.uni-kiel.de) 4/94
 */

#ifndef XPMI_h
#define XPMI_h

#include "XpmP.h"

/*
 * lets try to solve include files
 */

#include <stdio.h>
#include <stdlib.h>
/* stdio.h doesn't declare popen on a Sequent DYNIX OS */
#ifdef sequent
extern FILE *popen();
#endif

#if defined(SYSV) || defined(SVR4) || defined(VMS) || defined(WIN32) || defined (_SVID_SOURCE)
#include <string.h>

#ifndef index
#define index strchr
#endif

#ifndef rindex
#define rindex strrchr
#endif

#else  /* defined(SYSV) || defined(SVR4) || defined(VMS) */
#include <strings.h>
#endif



#if defined(SYSV) || defined(SVR4) || defined(VMS) || defined(WIN32)
#ifndef bcopy
#define bcopy(source, dest, count) memcpy(dest, source, count)
#endif
#ifndef bzero
#define bzero(b, len) memset(b, 0, len)
#endif
#endif

/* the following is defined in X11R6 but not in previous versions */
#ifdef __alpha
#ifndef LONG64
#define LONG64
#endif
#endif

#ifdef VMS
#include <unixio.h>
#include <file.h>
#endif

/* The following should help people wanting to use their own memory allocation
 * functions. To avoid the overhead of a function call when the standard
 * functions are used these are all macros, even the XpmFree function which
 * needs to be a real function for the outside world though.
 * So if change these be sure to change the XpmFree function in misc.c
 * accordingly.
 */
#ifndef NO_XPMFREE_MACRO
#ifdef XpmFree
#undef XpmFree
#endif
#define XpmFree(ptr) free(ptr)
#endif

#ifndef FOR_MSW
#define XpmMalloc(size) malloc((size))
#define XpmRealloc(ptr, size) realloc((ptr), (size))
#define XpmCalloc(nelem, elsize) calloc((nelem), (elsize))
#else
/* checks for mallocs bigger than 64K */
#define XpmMalloc(size) boundCheckingMalloc((long)(size))/* in simx.[ch] */
#define XpmRealloc(ptr, size) boundCheckingRealloc((ptr),(long)(size))
#define XpmCalloc(nelem, elsize) \
		boundCheckingCalloc((long)(nelem),(long) (elsize))
#endif

/* X.org security patch 0687 */
#if defined(SCO) || defined(__USLC__)
#include <stdint.h>    /* For SIZE_MAX */
#endif
#include <limits.h>
#ifndef SIZE_MAX
# ifdef ULONG_MAX
#  define SIZE_MAX ULONG_MAX
# else
#  define SIZE_MAX UINT_MAX
# endif
#endif
/* END: X.org security patch 0687 */

#define XPMMAXCMTLEN BUFSIZ
typedef struct {
    unsigned int type;
    union {
	FILE *file;
	char **data;
    }     stream;
    char *cptr;
    unsigned int line;
    int CommentLength;
    char Comment[XPMMAXCMTLEN];
    char *Bcmt, *Ecmt, Bos, Eos;
    int format;			/* 1 if XPM1, 0 otherwise */
}      xpmData;

#define XPMARRAY 0
#define XPMFILE  1
#define XPMPIPE  2
#define XPMBUFFER 3

#define EOL '\n'
#define TAB '\t'
#define SPC ' '

typedef struct {
    char *type;			/* key word */
    char *Bcmt;			/* string beginning comments */
    char *Ecmt;			/* string ending comments */
    char Bos;			/* character beginning strings */
    char Eos;			/* character ending strings */
    char *Strs;			/* strings separator */
    char *Dec;			/* data declaration string */
    char *Boa;			/* string beginning assignment */
    char *Eoa;			/* string ending assignment */
}      xpmDataType;

extern xpmDataType xpmDataTypes[];

/*
 * rgb values and ascii names (from rgb text file) rgb values,
 * range of 0 -> 65535 color mnemonic of rgb value
 */
typedef struct {
    int r, g, b;
    char *name;
}      xpmRgbName;

/* Maximum number of rgb mnemonics allowed in rgb text file. */
#define MAX_RGBNAMES 1024

extern char *xpmColorKeys[];

#define TRANSPARENT_COLOR "None"	/* this must be a string! */

/* number of xpmColorKeys */
#define NKEYS 5

/* XPM internal routines */

FUNC(xpmParseData, int, (xpmData *data, XpmImage *image, XpmInfo *info));
FUNC(xpmParseDataAndCreate, int, (Display *display, xpmData *data,
				  XImage **image_return,
				  XImage **shapeimage_return,
				  XpmImage *image, XpmInfo *info,
				  XpmAttributes *attributes));

FUNC(xpmFreeColorTable, void, (XpmColor *colorTable, int ncolors));

FUNC(xpmInitAttributes, void, (XpmAttributes *attributes));

FUNC(xpmInitXpmImage, void, (XpmImage *image));

FUNC(xpmInitXpmInfo, void, (XpmInfo *info));

FUNC(xpmSetInfoMask, void, (XpmInfo *info, XpmAttributes *attributes));
FUNC(xpmSetInfo, void, (XpmInfo *info, XpmAttributes *attributes));
FUNC(xpmSetAttributes, void, (XpmAttributes *attributes, XpmImage *image,
			      XpmInfo *info));

#ifndef FOR_MSW
FUNC(xpmCreatePixmapFromImage, void, (Display *display, Drawable d,
				      XImage *ximage, Pixmap *pixmap_return));

FUNC(xpmCreateImageFromPixmap, void, (Display *display, Pixmap pixmap,
				      XImage **ximage_return,
				      unsigned int *width,
				      unsigned int *height));
#endif

/* structures and functions related to hastable code */

typedef struct _xpmHashAtom {
    char *name;
    void *data;
}      *xpmHashAtom;

typedef struct {
    unsigned int size;   /* X.org security patch: 0687 */
    unsigned int limit;  /* X.org security patch: 0687 */
    unsigned int used;   /* X.org security patch: 0687 */
    xpmHashAtom *atomTable;
}      xpmHashTable;

FUNC(xpmHashTableInit, int, (xpmHashTable *table));
FUNC(xpmHashTableFree, void, (xpmHashTable *table));
FUNC(xpmHashSlot, xpmHashAtom *, (xpmHashTable *table, char *s));
FUNC(xpmHashIntern, int, (xpmHashTable *table, char *tag, void *data));

#define HashAtomData(i) ((void *)i)
#define HashColorIndex(slot) ((unsigned int)((*slot)->data))
#define USE_HASHTABLE (cpp > 2 && ncolors > 4)

/* I/O utility */

FUNC(xpmNextString, int, (xpmData *mdata));
FUNC(xpmNextUI, int, (xpmData *mdata, unsigned int *ui_return));
FUNC(xpmGetString, int, (xpmData *mdata, char **sptr, unsigned int *l));

#define xpmGetC(mdata) \
	((!mdata->type || mdata->type == XPMBUFFER) ? \
	 (*mdata->cptr++) : (getc(mdata->stream.file)))

FUNC(xpmNextWord, unsigned int,
     (xpmData *mdata, char *buf, unsigned int buflen));
FUNC(xpmGetCmt, int, (xpmData *mdata, char **cmt));
FUNC(xpmParseHeader, int, (xpmData *mdata));
FUNC(xpmParseValues, int, (xpmData *data, unsigned int *width,
			   unsigned int *height, unsigned int *ncolors,
			   unsigned int *cpp, unsigned int *x_hotspot,
			   unsigned int *y_hotspot, unsigned int *hotspot,
			   unsigned int *extensions));

FUNC(xpmParseColors, int, (xpmData *data, unsigned int ncolors,
			   unsigned int cpp, XpmColor **colorTablePtr,
			   xpmHashTable *hashtable));

FUNC(xpmParseExtensions, int, (xpmData *data, XpmExtension **extensions,
			       unsigned int *nextensions));

/* RGB utility */

FUNC(xpmReadRgbNames, int, (char *rgb_fname, xpmRgbName *rgbn));
FUNC(xpmGetRgbName, char *, (xpmRgbName *rgbn, int rgbn_max,
			     int red, int green, int blue));
FUNC(xpmFreeRgbNames, void, (xpmRgbName *rgbn, int rgbn_max));
#ifdef FOR_MSW
FUNC(xpmGetRGBfromName,int, (char *name, int *r, int *g, int *b));
#endif

FUNC(xpm_xynormalizeimagebits, void, (register unsigned char *bp,
				      register XImage *img));
FUNC(xpm_znormalizeimagebits, void, (register unsigned char *bp,
				     register XImage *img));

/*
 * Macros
 *
 * The XYNORMALIZE macro determines whether XY format data requires
 * normalization and calls a routine to do so if needed. The logic in
 * this module is designed for LSBFirst byte and bit order, so
 * normalization is done as required to present the data in this order.
 *
 * The ZNORMALIZE macro performs byte and nibble order normalization if
 * required for Z format data.
 *
 * The XYINDEX macro computes the index to the starting byte (char) boundary
 * for a bitmap_unit containing a pixel with coordinates x and y for image
 * data in XY format.
 *
 * The ZINDEX* macros compute the index to the starting byte (char) boundary
 * for a pixel with coordinates x and y for image data in ZPixmap format.
 *
 */

#define XYNORMALIZE(bp, img) \
    if ((img->byte_order == MSBFirst) || (img->bitmap_bit_order == MSBFirst)) \
	xpm_xynormalizeimagebits((unsigned char *)(bp), img)

#define ZNORMALIZE(bp, img) \
    if (img->byte_order == MSBFirst) \
	xpm_znormalizeimagebits((unsigned char *)(bp), img)

#define XYINDEX(x, y, img) \
    ((y) * img->bytes_per_line) + \
    (((x) + img->xoffset) / img->bitmap_unit) * (img->bitmap_unit >> 3)

#define ZINDEX(x, y, img) ((y) * img->bytes_per_line) + \
    (((x) * img->bits_per_pixel) >> 3)

#define ZINDEX32(x, y, img) ((y) * img->bytes_per_line) + ((x) << 2)

#define ZINDEX16(x, y, img) ((y) * img->bytes_per_line) + ((x) << 1)

#define ZINDEX8(x, y, img) ((y) * img->bytes_per_line) + (x)

#define ZINDEX1(x, y, img) ((y) * img->bytes_per_line) + ((x) >> 3)

#ifdef __STDC__
#define Const const
#else
#define Const /**/
#endif

#ifdef NEED_STRDUP
FUNC(xpmstrdup, char *, (char *s1));
#else
#undef xpmstrdup
#define xpmstrdup strdup
#endif

#ifdef NEED_STRCASECMP                   
FUNC(xpmstrcasecmp, int, (char *s1, char *s2));
#else
#undef xpmstrcasecmp
#define xpmstrcasecmp strcasecmp
#endif

FUNC(xpmatoui, unsigned int,
     (char *p, unsigned int l, unsigned int *ui_return));

#endif

#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#endif /* _XpmI_h */
