/* $Id$Revision: */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2007 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#include "glcompfont.h"
#include "glcompset.h"
#include "glpangofont.h"
#include "glcomptexture.h"
#include "glutils.h"
#include "memory.h"
#include <GL/glut.h>

void print_bitmap_string(void *font, char *s)
{
    if (s && strlen(s)) {
	while (*s) {
	    glutBitmapCharacter(font, *s);
//         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *s);
	    s++;
	}
    }
}

void init_gl_vars(glCompFont * f)
{

/*    glGetIntegerv(GL_POLYGON_MODE, f->glcache.poly);

    if (f->glcache.poly[0] != GL_FILL)
	glPolygonMode(GL_FRONT, GL_FILL);
    if (f->glcache.poly[1] != GL_FILL)
	glPolygonMode(GL_BACK, GL_FILL);

    f->glcache.istextureon = glIsEnabled(GL_TEXTURE_2D);
    if (!f->glcache.istextureon)
	glEnable(GL_TEXTURE_2D);
    f->glcache.isdepthon = glIsEnabled(GL_DEPTH_TEST);
    if (f->glcache.isdepthon)
	glDisable(GL_DEPTH_TEST);
    f->glcache.islightingon = glIsEnabled(GL_LIGHTING);
    if (f->glcache.islightingon)
	glDisable(GL_LIGHTING);
    glGetIntegerv(GL_MATRIX_MODE, &f->glcache.matrix);

    f->glcache.isblendon = glIsEnabled(GL_BLEND);
    glGetIntegerv(GL_BLEND_SRC, &f->glcache.blendfrom);
    glGetIntegerv(GL_BLEND_DST, &f->glcache.blendto);
    if (&f->glcache.isblendon)
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
}

void restore_gl_vars(glCompFont * f)
{
/*    if (f->glcache.poly[0] != GL_FILL)
	glPolygonMode(GL_FRONT, f->glcache.poly[0]);
    if (f->glcache.poly[1] != GL_FILL)
	glPolygonMode(GL_BACK, f->glcache.poly[1]);

    if (f->glcache.islightingon)
	glEnable(GL_LIGHTING);

    if (!f->glcache.isblendon) {
	glDisable(GL_BLEND);
	glBlendFunc(f->glcache.blendfrom, f->glcache.blendto);
    } else
	glBlendFunc(f->glcache.blendfrom, f->glcache.blendto);

    if (f->glcache.isdepthon)
	glEnable(GL_DEPTH_TEST);
    if (!f->glcache.istextureon)
	glDisable(GL_TEXTURE_2D);
    glMatrixMode(f->glcache.matrix);*/
}
void glprintfglut(void *font, GLfloat xpos, GLfloat ypos, GLfloat zpos,
		  char *bf)
{
    glRasterPos3f(xpos, ypos, zpos + 0.001);
    print_bitmap_string(font, bf);


}



static void
glPrintf(glCompFont * font, GLfloat xpos, GLfloat ypos, GLfloat zpos,
	 GLfloat width, char *bf, int usez)
{

//      GLfloat size = font->size;
//    GLfloat x = xpos;
//    GLfloat y = ypos;

    //set the color
    glColor4f(font->color.R, font->color.G, font->color.B, font->color.A);
    if (!font)
	return;
    if (font->type == gluttext) {
	glprintfglut(font->glutfont, xpos, ypos, zpos, bf);
	return;
    }

}

void
glprintf(glCompFont * font, GLfloat xpos, GLfloat ypos, GLfloat zpos,
	 GLfloat width, char *bf)
{
    glPrintf(font, xpos, ypos, zpos, width, bf, 0);
}

void
glprintfz(glCompFont * font, GLfloat xpos, GLfloat ypos, GLfloat zpos,
	  GLfloat width, char *bf)
{
    glPrintf(font, xpos, ypos, zpos, width, bf, 0);
}



static int fontId(fontset_t * fontset, char *fontdesc)
{
    int ind = 0;
    for (ind = 0; ind < fontset->count; ind++) {
	if (strcmp(fontset->fonts[ind]->fontdesc, fontdesc) == 0)
	    return ind;
    }
    return -1;
}

static int glutfontId(fontset_t * fontset, void *glutfont)
{
    int ind = 0;
    for (ind = 0; ind < fontset->count; ind++) {
	if (fontset->fonts[ind]->glutfont == glutfont)
	    return ind;
    }
    return -1;
}


glCompFont *glut_font_init(void)
{
    glCompFont *font = NEW(glCompFont);
    font->color.R = 1.00;
    font->color.G = 1.00;
    font->color.B = 1.00;
    font->color.A = 1.00;


/*	font->fontheight=12;
	font->tIncX=0.0;
	font->tIncY=0.0;
	font->texId=-1;
	font->fontdesc=(char*)0;




	font->tIncX = (float)pow (C_DPI, -1);
	font->tIncY = (float)pow (R_DPI, -1);

	
	for (y = 1 - font->tIncY; y >= 0; y -= font->tIncY)
	{
		for (x = 0; x <= 1 - font->tIncX; x += font->tIncX, idx ++)
		{
			font->bmp[idx][0]=x;
			font->bmp[idx][1]=y;
		}
	}*/
    return font;
}

void delete_font(glCompFont * f)
{
    if (f->fontdesc)
	free(f->fontdesc);
    if (f->tex)
	glCompDeleteTexture(f->tex);
    free(f);

}

glCompFont *new_font(glCompSet * s, char *text, glCompColor * c,glCompFontType type, char *fontdesc, int fs,int is2D)
{
    glCompFont *font = (glCompFont*) malloc(sizeof(glCompFont));
    font->reference = 0;
    font->color.R = c->R;
    font->color.G = c->G;
    font->color.B = c->B;
    font->color.A = c->A;
    font->justify.VJustify = GL_FONTVJUSTIFY;
    font->justify.HJustify = GL_FONTHJUSTIFY;
    font->type=type;
    font->is2D=is2D;

    if (font->type == gluttext)
	font->glutfont = DEFAULT_GLUT_FONT;
    else
	font->glutfont = (void *) 0;

    font->fontdesc = strdup(fontdesc);
    font->size = fs;
    font->transparent = 1;
    font->optimize = GL_FONTOPTIMIZE;
    if (text)
	font->tex =
	    glCompSetAddNewTexLabel(s, font->fontdesc, font->size, text,
				    is2D);
    return font;

}



glCompFont *new_font_from_parent(glCompObj * o, char *text)
{
    glCompCommon *parent;
    glCompFont *font = NEW(glCompFont);
    parent = o->common.parent;
    if (parent) {
	parent = o->common.parent;
	font->reference = 1;
	font->color.R = parent->font->color.R;
	font->color.G = parent->font->color.G;
	font->color.B = parent->font->color.B;
	font->color.A = parent->font->color.A;

	font->type = parent->font->type;
	font->glutfont = parent->font->glutfont;
	font->fontdesc = strdup(parent->font->fontdesc);
	font->size = parent->font->size;
	font->transparent = parent->font->transparent;
	font->justify.VJustify = parent->font->justify.VJustify;
	font->justify.HJustify = parent->font->justify.HJustify;
	font->optimize = parent->font->optimize;
	font->is2D=parent->font->is2D;
	if (text) {
	    if (strlen(text))
		font->tex =
		    glCompSetAddNewTexLabel(parent->compset,
					    font->fontdesc, font->size,
					    text, parent->font->is2D);
	}
    } else {			/*no parent */

	glCompColor c;
	c.R = GLCOMPSET_FONT_COLOR_R;
	c.G = GLCOMPSET_FONT_COLOR_G;
	c.B = GLCOMPSET_FONT_COLOR_B;
	c.A = GLCOMPSET_FONT_COLOR_ALPHA;
	font =
	    new_font(o->common.compset, text, &c, pangotext,
		     GLCOMPSET_FONT_DESC, GLCOMPSET_FONT_SIZE,1);
    }
    return font;
}



#ifndef _WIN32
#define TMPTEMP "/tmp/_sfXXXX"
#endif

fontset_t *fontset_init()
{
    fontset_t *fs = NEW(fontset_t);
    fs->activefont = -1;
    fs->count = 0;
#ifdef _WIN32
    fs->font_directory = "c:/fontfiles";	//FIX ME
#else
    fs->font_directory = strdup(TMPTEMP);
    mkdtemp(fs->font_directory);
#endif
    fs->fonts = 0;
    return fs;
}

static char *fontpath = NULL;
static size_t fontpathsz = 0;

glCompFont *add_glut_font(fontset_t * fontset, void *glutfont)
{
    int id;
    id = glutfontId(fontset, glutfont);
    if (id == -1) {
	fontset->fonts =
	    ALLOC(fontset->count + 1, fontset->fonts, glCompFont *);
	fontset->fonts[fontset->count] = glut_font_init();
	fontset->fonts[fontset->count]->type = gluttext;
	fontset->fonts[fontset->count]->glutfont = glutfont;
	fontset->count++;
	return fontset->fonts[fontset->count - 1];
    } else
	return fontset->fonts[id];
}


glCompFont *add_font(fontset_t * fontset, char *fontdesc, int fs)
{
    int id;
    size_t sz;

    id = fontId(fontset, fontdesc);
    if (id == -1) {
	sz = strlen(fontset->font_directory) + strlen(fontdesc) + 6;
	if (sz > fontpathsz) {
	    fontpathsz = 2 * sz;
	    fontpath = ALLOC(fontpathsz, fontpath, char);
	}
/*	sprintf(fontpath, "%s/%s.png", fontset->font_directory, fontdesc);
	if (create_font_file(fontdesc,fs, fontpath, (float) 32, (float) 32) ==
	    0) {
	    fontset->fonts =
		ALLOC(fontset->count + 1, fontset->fonts, glCompFont *);
	    fontset->fonts[fontset->count] = tf = font_init();
	    tf->fontdesc = strdup(fontdesc);
		fontset->fonts[fontset->count]->type = pangotext;
	    glGenTextures(1, &(tf->texId));	//get  opengl texture name
	    if ((tf->texId >= 0) && glCompLoadFontPNG(fontpath, tf->texId)) {
		fontset->activefont = fontset->count;
		fontset->count++;
		return fontset->fonts[fontset->count - 1];
	    } else
		return NULL;
	} else
	    return NULL;
    } else
	return fontset->fonts[id];*/
    }

    return NULL;
}

void free_font_set(fontset_t * fontset)
{
    int ind;
    for (ind = 0; ind < fontset->count; ind++) {
#ifndef _WIN32
	sprintf(fontpath, "%s/%s.png", fontset->font_directory,
		fontset->fonts[ind]->fontdesc);
	unlink(fontpath);
#endif
	free(fontset->fonts[ind]->fontdesc);
	free(fontset->fonts[ind]);
    }
    free(fontset->fonts);
#ifndef _WIN32
    if (fontset->font_directory)
	rmdir(fontset->font_directory);
#endif
    if (fontset->font_directory)
	free(fontset->font_directory);
    free(fontset);
}

void fontColor(glCompFont * font, float r, float g, float b, float a)
{

    font->color.R = r;
    font->color.G = g;
    font->color.B = b;
    font->color.A = a;
}


/*texture base 3d text rendering*/
void glCompDrawText3D(glCompFont * f,GLfloat x,GLfloat y,GLfloat z,GLfloat w,GLfloat h)
{
	glEnable(GL_BLEND);		// Turn Blending On
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,f->tex->id);
	glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);glVertex3d(x,y,z);
		glTexCoord2d(1.0f, 1.0f);glVertex3d(x+w,y,z);
		glTexCoord2d(1.0f, 0.0f);glVertex3d(x+w,y+h,z);
		glTexCoord2d(0.0f, 0.0f);glVertex3d(x,y+h,z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

}
/*bitmap base 2D text rendering */
void glCompDrawText(glCompFont * f,GLfloat x,GLfloat y)
{
    glRasterPos2f(x, y);
    glDrawPixels(f->tex->width, f->tex->height, GL_RGBA, GL_UNSIGNED_BYTE,
		 f->tex->data);
}

/*text rendering functions, depends on a globject to retrieve stats*/
void glCompRenderText(glCompFont * f, glCompObj * parentObj)
{
    static glCompCommon ref;
    GLfloat x, y, z, w, h;
    if (!f->tex)
	return;
    x = 0;
    y = 0;
    w = f->tex->width;
    h = f->tex->height;
    ref = parentObj->common;
    z = ref.pos.z;
    switch (f->justify.HJustify) {
    case glFontHJustifyNone:
    case glFontHJustifyLeft:
	x = ref.refPos.x;
	break;
    case glFontHJustifyRight:
	x = ref.refPos.x + (ref.width - f->tex->width);
	break;
    case glFontHJustifyCenter:
	x = ref.refPos.x + (ref.width - f->tex->width) / (GLfloat) 2.0;
	break;
    }
    switch (f->justify.VJustify) {
    case glFontVJustifyNone:
    case glFontVJustifyBottom:
	y = ref.pos.y;
	break;
    case glFontVJustifyTop:
	x = ref.refPos.y + (ref.height - f->tex->height);
	break;
    case glFontVJustifyCenter:
	y = ref.refPos.y + (ref.height - f->tex->height) / (GLfloat) 2.0;
	break;
    }
	z=ref.refPos.z;

    glCompSetColor(&f->color);
		glCompDrawText(f,x,y);

}
