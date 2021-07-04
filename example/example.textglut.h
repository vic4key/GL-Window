#pragma once

#include "example.h"

#include <glwnd/glut.h>

class GLViewExampleTextGLUT : public GLView
{
public:
  GLViewExampleTextGLUT() : GLView() {}
  virtual ~GLViewExampleTextGLUT() {}

  virtual void on_display()
  {
    // render text by GLUT bitmap font

    glColor3d(1., 1., 1.);

    glut::render_string(this, p2d(-0.9, +0.9), "GLUT Bitmap Helvetica 18", glut::bitmap_fonts::GLUT_BITMAP_HELVETICA_18);
    glut::render_string(this, p2d(-0.9, +0.7), "GLUT Bitmap Helvetica 18", glut::bitmap_fonts::GLUT_BITMAP_HELVETICA_18);
    glut::render_string(this, p2d(-0.9, +0.5), "GLUT Bitmap Helvetica 12", glut::bitmap_fonts::GLUT_BITMAP_HELVETICA_12);
    glut::render_string(this, p2d(-0.9, +0.3), "GLUT Bitmap Helvetica 10", glut::bitmap_fonts::GLUT_BITMAP_HELVETICA_10);
    glut::render_string(this, p2d(-0.9, +0.1), "GLUT Bitmap Times Roman 24", glut::bitmap_fonts::GLUT_BITMAP_TIMES_ROMAN_24);
    glut::render_string(this, p2d(-0.9, -0.1), "GLUT Bitmap Times Roman 10", glut::bitmap_fonts::GLUT_BITMAP_TIMES_ROMAN_10);
    glut::render_string(this, p2d(-0.9, -0.3), "GLUT Bitmap 9 By 15", glut::bitmap_fonts::GLUT_BITMAP_9_BY_15);
    glut::render_string(this, p2d(-0.9, -0.5), "GLUT Bitmap 8 By 13", glut::bitmap_fonts::GLUT_BITMAP_8_BY_13);

    // render text by GLUT stroke font

    glColor3d(0., 1., 0.);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 30.0);
    {
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      {
        gluLookAt(
          0.0, 0.0, 2.0,  // eye
          0.0, 0.0, 0.0,  // position
          0.0, 1.0, 0.0); // direction

        glPushMatrix();
        {
          glLineWidth(3.F);

          static double angle = 0.;
          if (angle++ > 360.F) angle = 0.F;
          glRotated(angle, 0., 0., 1.); // rotate around z-axis

          glut::render_string(this, p3d(-0.9, -0.7, 0.0), "GLUT Stroke Mono", glut::stroke_fonts::GLUT_STROKE_ROMAN, 0.001);
          glut::render_string(this, p3d(-0.9, -0.9, 0.0), "GLUT Stroke Mono Roman", glut::stroke_fonts::GLUT_STROKE_MONO_ROMAN, 0.001);
        }
        glPopMatrix();
      }
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
    }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
  }
};