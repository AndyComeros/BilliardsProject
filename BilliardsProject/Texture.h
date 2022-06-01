#pragma once
#include <GL\freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXROW 500
#define MAXCOL 500

typedef unsigned char pixel[3];

pixel** InputImage(char* fileName, int width, int height);
void displayImage(pixel** imageData, int w, int h, int x, int y);
void reshapeTexture(int w, int h);