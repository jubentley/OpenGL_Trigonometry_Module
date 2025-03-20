/*#####################################################################
#
#	Trigonometry Module (Header)
#
#	Author:		Justin Bentley
#	Date:		25/04/2018 >> 14/05/2019
#	Version:	2.0
#	GLfloat variables need "glut.h", "glew.h" or equivalent
#
######################################################################*/

#include <cmath>
//#include "glut.h"
//#include "GL/glew.h"

#ifndef Trig_def 
#define Trig_def 
//GLfloat V2VDistance(GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X2, GLfloat Y2, GLfloat Z2);

//Distance Vertice XYZ to Vertice XYZ in GLfloat
//Does not go in negatve
inline GLfloat Dist3D(GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X2, GLfloat Y2, GLfloat Z2) {
	return sqrt(pow((X2 - X1), 2) + pow((Y2 - Y1), 2) + pow((Z2 - Z1), 2));	//add z for 3d//Judith
}
inline GLfloat Dist2D(GLfloat X1, GLfloat Y1, GLfloat X2, GLfloat Y2) {
	return sqrt(pow((X2 - X1), 2) + pow((Y2 - Y1), 2));	//add z for 3d//Judith
}
//2x XYZ and a distance, returns true if within
inline bool DistSimple(GLfloat X1, GLfloat Y1, GLfloat Z1, \
	GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat Dist) {
	if (abs(X2 - X1) > Dist) { return false; }
	if (abs(Y2 - Y1) > Dist) { return false; }
	if (abs(Z2 - Z1) > Dist) { return false; }
	return true;
}
//New XYZ from Old XYZ + Angles/Dist(Speed) - Pointer Return
inline void MovePlane2(GLfloat oldx, GLfloat oldy, GLfloat oldz,
	GLfloat roll, GLfloat pitch, GLfloat yaw, GLfloat speed,
	GLfloat *resultx, GLfloat *resulty, GLfloat *resultz)
{
	GLfloat tmpx, tmpy, tmpz;
	GLfloat newx, newy, newz;
	//360 Angle Safety
	for (int i = 0; i < 4; i++) {	
		if (yaw > 360) { yaw = yaw - 360; }
		if (yaw < 0) { yaw = yaw + 360; }
		if (pitch > 360) { pitch = pitch - 360; }
		if (pitch < 0) { pitch = pitch + 360; }
		if (roll > 360) { roll = roll - 360; }
		if (roll < 0) { roll = roll + 360; }
	}
	roll = roll * 3.1416 / 180;	//TO RADS
	pitch = pitch * 3.1416 / 180;
	yaw = yaw * 3.1416 / 180;

	tmpy = 0; /* set to origin */
	tmpx = 0;
	tmpz = speed; /* move us forward by speed */

	newx = (tmpx * cos(roll)) - (tmpy * sin(roll)); // rotate around z
	newy = (tmpx * sin(roll)) + (tmpy * cos(roll));
	tmpx = newx;
	tmpy = newy;

	newy = (tmpy * cos(pitch)) - (tmpz * sin(pitch)); // rotate around x
	newz = (tmpy * sin(pitch)) + (tmpz * cos(pitch));
	tmpy = newy;
	tmpz = newz;

	newx = (tmpz * sin(yaw)) + (tmpx * cos(yaw));
	newz = (tmpz * cos(yaw)) - (tmpx * sin(yaw));
	tmpx = newx;
	tmpz = newz;

	newx = tmpx + oldx;
	newy = tmpy + oldy;
	newz = tmpz + oldz;

	*resultx = newx;
	*resulty = newy;
	*resultz = newz;

}
#endif