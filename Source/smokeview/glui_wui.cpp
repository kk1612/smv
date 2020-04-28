#define CPP
#include "options.h"

#include <stdio.h>
#include <string.h>
#include GLUT_H
#include <math.h>

#include "smokeviewvars.h"
#include "glui_bounds.h"
#include "glui_wui.h"

GLUI_Panel *PANEL_terrain=NULL;

GLUI *glui_wui=NULL;

GLUI_Panel *PANEL_wui=NULL;
GLUI_Panel *PANEL_fire_line=NULL;
GLUI_Panel *PANEL_terrain_hidden1=NULL;
GLUI_Panel *PANEL_terrain_color=NULL;
GLUI_Panel *PANEL_terrain_type=NULL;
GLUI_Panel *PANEL_terrain_normal=NULL;

GLUI_RadioGroup *RADIO_terrain_type=NULL;

GLUI_RadioButton *RADIOBUTTON_texture=NULL;
GLUI_RadioButton *RADIOBUTTON_wui_1a=NULL;
GLUI_RadioButton *RADIOBUTTON_wui_1b=NULL;
GLUI_RadioButton *RADIOBUTTON_wui_1c=NULL;
GLUI_RadioButton *RADIOBUTTON_wui_1d=NULL;

GLUI_Spinner *SPINNER_red_min=NULL;
GLUI_Spinner *SPINNER_green_min=NULL;
GLUI_Spinner *SPINNER_blue_min=NULL;
GLUI_Spinner *SPINNER_red_max=NULL;
GLUI_Spinner *SPINNER_green_max=NULL;
GLUI_Spinner *SPINNER_blue_max=NULL;
GLUI_Spinner *SPINNER_vertical_factor=NULL;
GLUI_Spinner *SPINNER_fire_line_min=NULL;
GLUI_Spinner *SPINNER_fire_line_max=NULL;

GLUI_StaticText *STATIC_wui_1=NULL;
GLUI_StaticText *STATIC_wui_2=NULL;

GLUI_Button *BUTTON_wui_1=NULL;
GLUI_Button *BUTTON_wui_2=NULL;


/* ------------------ UpdateGluiWui ------------------------ */

extern "C" void UpdateGluiWui(void){
  if(RADIO_terrain_type!=NULL){
    RADIO_terrain_type->set_int_val(visTerrainType);
  }
}

/* ------------------ GluiWuiSetup ------------------------ */

extern "C" void GluiWuiSetup(int main_window){
  update_glui_wui=0;
  if(glui_wui!=NULL){
    glui_wui->close();
    glui_wui=NULL;
  }
  glui_wui = GLUI_Master.create_glui(_("Terrain"),0,0,0);
  glui_wui->hide();

  PANEL_terrain = glui_wui->add_panel("",GLUI_PANEL_NONE);

  if(nterraininfo>0){
    PANEL_terrain_color=glui_wui->add_panel_to_panel(PANEL_terrain,_("3D surface color"));
//  glui_labels->add_statictext_to_panel(PANEL_tick2,"                    x");
//  glui_labels->add_column_to_panel(PANEL_tick2,false);

    STATIC_wui_1=glui_wui->add_statictext_to_panel(PANEL_terrain_color,_("                  Min"));
    SPINNER_red_min=glui_wui->add_spinner_to_panel(PANEL_terrain_color,_("red"),GLUI_SPINNER_INT,terrain_rgba_zmin,TERRAIN_COLORS,WuiCB);
    SPINNER_green_min=glui_wui->add_spinner_to_panel(PANEL_terrain_color,_("green"),GLUI_SPINNER_INT,terrain_rgba_zmin+1,TERRAIN_COLORS,WuiCB);
    SPINNER_blue_min=glui_wui->add_spinner_to_panel(PANEL_terrain_color,_("blue"),GLUI_SPINNER_INT,terrain_rgba_zmin+2,TERRAIN_COLORS,WuiCB);
    glui_wui->add_column_to_panel(PANEL_terrain_color,false);

    STATIC_wui_2=glui_wui->add_statictext_to_panel(PANEL_terrain_color,_("                  Max"));
    SPINNER_red_max=glui_wui->add_spinner_to_panel(PANEL_terrain_color,"",GLUI_SPINNER_INT,terrain_rgba_zmax,TERRAIN_COLORS,WuiCB);
    SPINNER_green_max=glui_wui->add_spinner_to_panel(PANEL_terrain_color,"",GLUI_SPINNER_INT,terrain_rgba_zmax+1,TERRAIN_COLORS,WuiCB);
    SPINNER_blue_max=glui_wui->add_spinner_to_panel(PANEL_terrain_color,"",GLUI_SPINNER_INT,terrain_rgba_zmax+2,TERRAIN_COLORS,WuiCB);

      SPINNER_red_min->set_int_limits(0,255,GLUI_LIMIT_CLAMP);
    SPINNER_green_min->set_int_limits(0,255,GLUI_LIMIT_CLAMP);
     SPINNER_blue_min->set_int_limits(0,255,GLUI_LIMIT_CLAMP);
      SPINNER_red_max->set_int_limits(0,255,GLUI_LIMIT_CLAMP);
    SPINNER_green_max->set_int_limits(0,255,GLUI_LIMIT_CLAMP);
     SPINNER_blue_max->set_int_limits(0,255,GLUI_LIMIT_CLAMP);

    PANEL_terrain_hidden1=glui_wui->add_panel_to_panel(PANEL_terrain,"",GLUI_PANEL_NONE);
    PANEL_terrain_type=glui_wui->add_panel_to_panel(PANEL_terrain_hidden1,_("Surface view"));
    RADIO_terrain_type=glui_wui->add_radiogroup_to_panel(PANEL_terrain_type,&visTerrainType,TERRAIN_TYPE,WuiCB);
    RADIOBUTTON_wui_1a=glui_wui->add_radiobutton_to_group(RADIO_terrain_type,_("3D surface"));
    RADIOBUTTON_wui_1b=glui_wui->add_radiobutton_to_group(RADIO_terrain_type,_("2D stepped"));
    RADIOBUTTON_wui_1c=glui_wui->add_radiobutton_to_group(RADIO_terrain_type,_("2D lines"));
    RADIOBUTTON_texture=glui_wui->add_radiobutton_to_group(RADIO_terrain_type,_("Image"));
    RADIOBUTTON_wui_1d=glui_wui->add_radiobutton_to_group(RADIO_terrain_type,_("Hidden"));
    RADIOBUTTON_wui_1b->disable();
    RADIOBUTTON_wui_1c->disable();

    if(terrain_texture==NULL||terrain_texture->loaded==0){
      RADIOBUTTON_texture->disable();
    }

    glui_wui->add_column_to_panel(PANEL_terrain_hidden1,false);

    PANEL_fire_line=glui_wui->add_panel_to_panel(PANEL_terrain_hidden1,_("Fire line"));
    SPINNER_fire_line_min=glui_wui->add_spinner_to_panel(PANEL_fire_line,"chop below:",GLUI_SPINNER_FLOAT,&fire_line_min,TERRAIN_MIN,WuiCB);
    SPINNER_fire_line_max=glui_wui->add_spinner_to_panel(PANEL_fire_line,"color red above:",GLUI_SPINNER_FLOAT,&fire_line_max,TERRAIN_MAX,WuiCB);
    glui_wui->add_button_to_panel(PANEL_fire_line,_("Update"),TERRAIN_FIRE_LINE_UPDATE,WuiCB);

    SPINNER_vertical_factor=glui_wui->add_spinner_to_panel(PANEL_terrain_hidden1,"vertical exaggeration",GLUI_SPINNER_FLOAT,&vertical_factor,TERRAIN_VERT,WuiCB);
    SPINNER_vertical_factor->set_float_limits(0.25,4.0,GLUI_LIMIT_CLAMP);
    glui_wui->add_checkbox_to_panel(PANEL_terrain_hidden1, "show grid", &show_terrain_grid);
    PANEL_terrain_normal=glui_wui->add_panel_to_panel(PANEL_terrain_hidden1,_("normals"));
    glui_wui->add_checkbox_to_panel(PANEL_terrain_normal, "show", &show_terrain_normals);
    glui_wui->add_spinner_to_panel(PANEL_terrain_normal, "length", GLUI_SPINNER_FLOAT, &terrain_normal_length);
    glui_wui->add_spinner_to_panel(PANEL_terrain_normal, "skip", GLUI_SPINNER_INT, &terrain_normal_skip);

    BUTTON_wui_1=glui_wui->add_button("Save settings",SAVE_SETTINGS_WUI,WuiCB);
    BUTTON_wui_2=glui_wui->add_button("Close",WUI_CLOSE,WuiCB);
#ifdef pp_CLOSEOFF
    BUTTON_wui_2->disable();
#endif
  }

  glui_wui->set_main_gfx_window( main_window );
}

/* ------------------ HideGluiWui ------------------------ */

extern "C" void HideGluiWui(void){
  CloseRollouts(glui_wui);
}

/* ------------------ ShowGluiWui ------------------------ */

extern "C" void ShowGluiWui(void){
  if(glui_wui!=NULL)glui_wui->show();
}

/* ------------------ WuiCB ------------------------ */

extern "C" void WuiCB(int var){
  int fire_line_type;

  switch(var){
    case TERRAIN_MIN:
    case TERRAIN_MAX:
      break;
    case TERRAIN_FIRE_LINE_UPDATE:
      fire_line_type= GetSliceBoundsIndexFromLabel("Fire line");
      if(fire_line_type<0)break;
      list_slice_index=fire_line_type;
      UpdateSliceList(list_slice_index);

      SliceBoundCB(FILETYPEINDEX);

#ifndef pp_NEWBOUND_DIALOG
      glui_setslicemin = SET_MIN;
      glui_setslicemax = SET_MAX;
#endif
      glui_slicemin=20.0;
      glui_slicemax=fire_line_max;
      glui_setslicechopmin = 1;
      glui_setslicechopmax = 0;
      glui_slicechopmin=fire_line_min;

      SliceBoundCB(SETVALMIN);
      SliceBoundCB(SETVALMAX);
      SliceBoundCB(VALMIN);
      SliceBoundCB(VALMAX);

      SliceBoundCB(SETCHOPMINVAL);
      SliceBoundCB(SETCHOPMAXVAL);
      SliceBoundCB(CHOPVALMIN);
      SliceBoundCB(CHOPVALMAX);

      SliceBoundCB(FILEUPDATE);
      SliceBoundCB(CHOPUPDATE);
      break;
    case TERRAIN_COLORS:
      UpdateTerrainColors();
      break;
    case TERRAIN_VERT:
      UpdateTerrain(0,vertical_factor);
      break;
    case TERRAIN_TYPE:
      if(visTerrainType==TERRAIN_3D){
        planar_terrain_slice=0;
      }
      else{
        planar_terrain_slice=1;
      }
      updatemenu=1;
      break;
  case SAVE_SETTINGS_WUI:
    WriteIni(LOCAL_INI,NULL);
    break;
  case WUI_CLOSE:
    HideGluiWui();
    break;

  default:
    ASSERT(FFALSE);
    break;
  }
}
