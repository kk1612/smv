#include "options.h"
#ifdef WIN32
#ifdef __MINGW32__
#include <stddef.h>
#endif
#endif

#include GLUT_H
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "smokeviewvars.h"

/* ------------------ OutputAxisLabels ------------------------ */

void OutputAxisLabels(){
  float x, y, z;
  float x0, y0, z0;

  glPushMatrix();
  glScalef(SCALE2SMV(1.0),SCALE2SMV(1.0),SCALE2SMV(1.0));
  glTranslatef(-xbar0,-ybar0,-zbar0);

  x = (xbar0+xbarORIG)/2.0;
  y = (ybar0+ybarORIG)/2.0;
  z = (zbar0+zbarORIG)/2.0;
  x0 = xbar0 - SCALE2FDS(0.02);
  y0 = ybar0 - SCALE2FDS(0.02);
  z0 = zbar0 - SCALE2FDS(0.02);

  Output3Text(foregroundcolor,   x,y0, z0, "X");
  Output3Text(foregroundcolor, x0,  y, z0, "Y");
  Output3Text(foregroundcolor, x0,y0,   z, "Z");

  glPopMatrix();
}

/* ------------------ OutputSText3 ------------------------ */

void OutputSText3(float x, float y, float z, char *string){
  char *c;
  float u[3]={0.0,0.0,1.0},v[3];
  float axis[3],angle,theta;
  float quateye[4],quatz[4],rot[16];
  float scale_x, scale_y;


  if(string==NULL)return;
  scale_x = SCALE2FDS(scaled_font3d_height2width*(float)scaled_font3d_height/(float)104.76)/(float)port_pixel_width;
  scale_y = SCALE2FDS((float)scaled_font3d_height/(float)152.38)/(float)port_pixel_height;
  glPushMatrix();
  glTranslatef(x,y,z);
  v[0]=fds_eyepos[0]-x;
  v[1]=fds_eyepos[1]-y;
  v[2]=fds_eyepos[2]-z;
  RotateU2V(u,v,axis,&angle);
  theta=atan2(v[0],-v[1])*RAD2DEG;
  AngleAxis2Quat(theta*DEG2RAD,u,quatz);
  AngleAxis2Quat(angle,axis,quateye);
  MultQuat(quateye,quatz,quateye);
  Quat2Rot(quateye,rot);

  glRotatef(90.0,cos(theta*DEG2RAD),sin(theta*DEG2RAD),0.0);
  glRotatef(theta,u[0],u[1],u[2]);

  glScalef(scale_x,scale_y,1.0);
  for(c=string; *c != '\0'; c++){
    glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
  }
  glPopMatrix();
}


/* ------------------ OutputSText2r ------------------------ */

void OutputSText2r(float x, float y, float z, char *string){
  char *c;
  int total_width=0;
  float scale_x, scale_y;

  if(string==NULL)return;
  total_width=0;
  for(c=string; *c != '\0'; c++){
    total_width+=glutStrokeWidth(GLUT_STROKE_ROMAN,*c);
  }
  glPushMatrix();
  scale_x = port_unit_width*(scaled_font2d_height2width*(float)scaled_font2d_height/(float)104.76)/(float)port_pixel_width;
  scale_y = port_unit_height*((float)scaled_font2d_height/(float)152.38)/(float)port_pixel_height;
  if(render_mode==RENDER_NORMAL&&resolution_multiplier>1&&render_status==RENDER_ON){
    scale_x *= (float)resolution_multiplier;
    scale_y *= (float)resolution_multiplier;
  }
  glTranslatef(x-scale_x*total_width,y,z);
  glScalef(scale_x,scale_y,1.0);
  for(c=string; *c != '\0'; c++){
    glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
  }
  glPopMatrix();
}

/* ------------------ OutputSText2 ------------------------ */

void OutputSText2(float x, float y, float z, char *string){
  char *c;
  int total_width=0;
  float scale_x, scale_y;

  if(string==NULL)return;
  total_width=0;
  for(c=string; *c != '\0'; c++){
    total_width+=glutStrokeWidth(GLUT_STROKE_ROMAN,*c);
  }
  glPushMatrix();
  scale_x = (25.0/36.0)*port_unit_width*(scaled_font2d_height2width*(float)scaled_font2d_height/(float)104.76)/(float)port_pixel_width;
  scale_y = (12.0/18.0)*(25.0/18.0)*port_unit_height*((float)scaled_font2d_height/(float)152.38)/(float)port_pixel_height;
  if(render_mode == RENDER_NORMAL&&resolution_multiplier > 1&&render_status==RENDER_ON){
    scale_x *= (float)resolution_multiplier;
    scale_y *= (float)resolution_multiplier;
  }
  glTranslatef(x,y,z);
  glScalef(scale_x,scale_y,1.0);
  glTranslatef(0.0,25.0,0.0);
  for(c=string; *c != '\0'; c++){
    glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
  }
  glPopMatrix();
}

/* ------------------ Output3Val ------------------------ */

void Output3Val(float x, float y, float z, float val){
  char string[256];

  sprintf(string,"%f",val);
  TrimZeros(string);
  Output3Text(foregroundcolor,x,y,z,string);
}

/* ------------------ Output3Text ------------------------ */

void Output3Text(float *color, float x, float y, float z, char *string){
  char *c;

  if(string==NULL)return;
  glColor3fv(color);

  if(fontindex==SCALED_FONT){
    ScaleFont3D();
    OutputSText3(x,y,z,string);
  }
  else{
    glRasterPos3f(x, y, z);
    for(c=string; *c!='\0'; c++){
      glutBitmapCharacter(large_font,(unsigned char)*c);
    }
  }
}

/* ------------------ OutputLargeText ------------------------ */

void OutputLargeText(float x, float y, char *string){
  char *c;

  if(string==NULL)return;
  glColor3fv(foregroundcolor);
  glRasterPos2f(x, y);
  for(c=string; *c!='\0'; c++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,(unsigned char)*c);
  }
}

/* ------------------ OutputText ------------------------ */

void OutputText(float x, float y, char *string){
  char *c;

  if(string==NULL)return;
  glColor3fv(foregroundcolor);
  if(fontindex==SCALED_FONT){
    ScaleFont2D();
    OutputSText2(x,y,0.0,string);
    return;
  }
  else{
    glRasterPos2f(x, y);
    for(c=string; *c!='\0'; c++){
      glutBitmapCharacter(large_font,(unsigned char)*c);
    }
  }
}

/* ------------------ OutputBarText ------------------------ */

void OutputBarText(float x, float y, const GLfloat *color, char *string){
  char *c;

  if(string==NULL)return;
  glColor3fv(color);

  if(fontindex==SCALED_FONT){
    ScaleFont2D();
    OutputSText2(x,y,0.0,string);
  }
  else{
    glRasterPos2f(x, y);
    for(c=string; *c!='\0'; c++){
      glutBitmapCharacter(small_font,(unsigned char)(*c));
    }
  }
}

/* ------------------ DrawLabels ------------------------ */

void DrawLabels(void){
  labeldata *thislabel;

  glPushMatrix();
  glScalef(SCALE2SMV(1.0),SCALE2SMV(1.0),SCALE2SMV(1.0));
  glTranslatef(-xbar0,-ybar0,-zbar0);
  for(thislabel=label_first_ptr->next;thislabel->next!=NULL;thislabel=thislabel->next){
    float *labelcolor,*tstart_stop,*xyz;
    int drawlabel;

    drawlabel=0;
    tstart_stop=thislabel->tstart_stop;
    xyz=thislabel->xyz;
    if(thislabel->useforegroundcolor==1){
      labelcolor=foregroundcolor;
    }
    else{
      labelcolor=thislabel->frgb;
    }
    if(plotstate!=DYNAMIC_PLOTS||thislabel->show_always==1||showtime==0)drawlabel=1;
    if(drawlabel==0&&plotstate==DYNAMIC_PLOTS&&showtime==1){
      if(tstart_stop[0]<0.0||tstart_stop[1]<0.0)drawlabel=1;
      if(drawlabel==0&&global_times[itimes]>=tstart_stop[0]-0.05&&global_times[itimes]<=tstart_stop[1]+0.05)drawlabel=1;
    }
    if(drawlabel==1){
      Output3Text(labelcolor,xyz[0],xyz[1],xyz[2],thislabel->name);
      if(thislabel->show_tick==1){
        float *xyztick, *xyztickdir;
        float xb[3], xe[3];
        int i;

        xyztick = thislabel->tick_begin;
        xyztickdir = thislabel->tick_direction;
        for(i = 0; i<3; i++){
          xb[i] = xyz[i]+xyztick[i];
          xe[i] = xb[i]+xyztickdir[i];
        }
        AntiAliasLine(ON);
        glLineWidth(ticklinewidth);
        glBegin(GL_LINES);
        glVertex3fv(xb);
        glVertex3fv(xe);
        glEnd();
        AntiAliasLine(OFF);
      }
    }
  }
  glPopMatrix();
}

/* ------------------ LabelNext ------------------------ */

labeldata *LabelNext(labeldata *label){
  labeldata *thislabel;

  if(label==NULL)return NULL;
  if(label_first_ptr->next->next==NULL)return NULL;
  for(thislabel=label->next;thislabel!=label;thislabel=thislabel->next){
    if(thislabel->next==NULL)thislabel=label_first_ptr->next;
    if(thislabel->labeltype==TYPE_SMV)continue;
    return thislabel;
  }
  return NULL;
}

/* ------------------ LabelPrevious ------------------------ */

labeldata *LabelPrevious(labeldata *label){
  labeldata *thislabel;

  if(label==NULL)return NULL;
  if(label_last_ptr->prev->prev==NULL)return NULL;
  for(thislabel=label->prev;thislabel!=label;thislabel=thislabel->prev){
    if(thislabel->prev==NULL)thislabel=label_last_ptr->prev;
    if(thislabel->labeltype==TYPE_SMV)continue;
    return thislabel;
  }
  return NULL;
}

/* ------------------ LabelInit ------------------------ */

int LabelInit(labeldata *gl){
  labeldata *thislabel;

  for(thislabel=label_first_ptr->next;thislabel->next!=NULL;thislabel=thislabel->next){
    if(thislabel->labeltype==TYPE_SMV)continue;
    LabelCopy(gl,thislabel);
    return 1;
  }
  return 0;
}

/* ------------------ LabelGetNUserLabels ------------------------ */

int LabelGetNUserLabels(void){
  int count=0;
  labeldata *thislabel;

  for(thislabel=label_first_ptr->next;thislabel->next!=NULL;thislabel=thislabel->next){
    if(thislabel->labeltype==TYPE_INI)count++;
  }
  return count;
}

/* ------------------ LabelGet ------------------------ */

labeldata *LabelGet(char *name){
  labeldata *thislabel;

  if(name==NULL)return NULL;
  for(thislabel=label_first_ptr->next;thislabel->next!=NULL;thislabel=thislabel->next){
    if(strcmp(thislabel->name,name)==0)return thislabel;
  }
  return NULL;
}

/* ------------------ LabelInsertBefore ------------------------ */

void LabelInsertBefore(labeldata *listlabel, labeldata *label){
  labeldata *prev, *next;

  next = listlabel;
  prev = listlabel->prev;
  prev->next = label;
  label->prev = prev;
  next->prev=label;
  label->next=next;
}

/* ------------------ LabelDelete ------------------------ */

void LabelDelete(labeldata *label){
  labeldata *prev, *next;

  prev = label->prev;
  next =label->next;
  CheckMemory;
  FREEMEMORY(label);
  prev->next=next;
  next->prev=prev;
}

/* ------------------ LabelCopy ------------------------ */

void LabelCopy(labeldata *label_to, labeldata *label_from){
  labeldata *prev, *next;

  prev=label_to->prev;
  next=label_to->next;
  memcpy(label_to,label_from,sizeof(labeldata));
  label_to->prev=prev;
  label_to->next=next;

}

/* ------------------ LabelResort ------------------------ */

void LabelResort(labeldata *label){
  labeldata labelcopy;

  CheckMemory;
  memcpy(&labelcopy,label,sizeof(labeldata));
  CheckMemory;
  LabelDelete(label);
  LabelInsert(&labelcopy);
}

/* ------------------ LabelInsertAfter ------------------------ */

void LabelInsertAfter(labeldata *listlabel, labeldata *label){
  labeldata *prev, *next;

  prev = listlabel;
  next = listlabel->next;
  prev->next = label;
  label->prev = prev;
  next->prev=label;
  label->next=next;
}

/* ------------------ LabelPrint ------------------------ */

void LabelPrint(void){
  labeldata *thislabel;
  float *xyz;

  for(thislabel=label_first_ptr->next;thislabel->next!=NULL;thislabel=thislabel->next){
    xyz = thislabel->xyz;
    PRINTF("label: %s position: %f %f %f\n",thislabel->name,xyz[0],xyz[1],xyz[2]);
  }
}

/* ------------------ LabelInsert ------------------------ */

labeldata *LabelInsert(labeldata *labeltemp){
  labeldata *newlabel, *thislabel;
  labeldata *firstuserptr, *lastuserptr;

  NewMemory((void **)&newlabel,sizeof(labeldata));
  memcpy(newlabel,labeltemp,sizeof(labeldata));

  thislabel = LabelGet(newlabel->name);
  if(thislabel!=NULL){
    LabelInsertAfter(thislabel->prev,newlabel);
    return newlabel;
  }

  firstuserptr=label_first_ptr->next;
  if(firstuserptr==label_last_ptr)firstuserptr=NULL;

  lastuserptr=label_last_ptr->prev;
  if(lastuserptr==label_first_ptr)lastuserptr=NULL;

  if(firstuserptr!=NULL&&strcmp(newlabel->name,firstuserptr->name)<0){
    LabelInsertBefore(firstuserptr,newlabel);
    return newlabel;
  }
  if(lastuserptr!=NULL&&strcmp(newlabel->name,lastuserptr->name)>0){
    LabelInsertAfter(lastuserptr,newlabel);
    return newlabel;
  }
  if(firstuserptr==NULL&&lastuserptr==NULL){
    LabelInsertAfter(label_first_ptr,newlabel);
    return newlabel;
  }
  for(thislabel=label_first_ptr->next;thislabel->next!=NULL;thislabel=thislabel->next){
    labeldata *nextlabel;

    nextlabel=thislabel->next;
    if(strcmp(thislabel->name,newlabel->name)<0&&strcmp(newlabel->name,nextlabel->name)<0){
      LabelInsertAfter(thislabel,newlabel);
      return newlabel;
    }
  }
  return NULL;
}

/* ----------------------- ScaleFont2D ----------------------------- */

void ScaleFont2D(void){
  if(render_mode == RENDER_360){
    glLineWidth((float)resolution_multiplier*(float)scaled_font2d_thickness);
  }
  else{
    glLineWidth((float)scaled_font2d_thickness);
  }
}

/* ----------------------- ScaleFont3D ----------------------------- */

void ScaleFont3D(void){
  if(render_mode == RENDER_360){
    glLineWidth((float)resolution_multiplier*(float)scaled_font3d_thickness);
  }
  else{
    glLineWidth((float)scaled_font3d_thickness);
  }
}

