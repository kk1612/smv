#define CPP
#include "options.h"

#include <stdio.h>
#include <string.h>
#include GLUT_H
#include <math.h>

#include "smokeviewvars.h"
#include "IOscript.h"
#include "MALLOCC.h"
#include "glui_smoke.h"
#include "glui_bounds.h"

GLUI_Rollout *ROLLOUT_slice_bound=NULL;
GLUI_Rollout *ROLLOUT_slice_chop=NULL;
GLUI_Rollout *ROLLOUT_part_bound=NULL;
GLUI_Rollout *ROLLOUT_part_chop=NULL;
GLUI_Rollout *ROLLOUT_zone_bound=NULL;

#ifdef pp_MEMDEBUG
#define MEMCHECK 1
#endif

GLUI *glui_bounds=NULL;

#ifdef pp_NEWBOUND_DIALOG
GLUI_Button *BUTTON_slice_percentile = NULL;
#endif
GLUI_Button *BUTTON_globalalpha = NULL;
GLUI_Button *BUTTON_updatebound = NULL;
GLUI_Button *BUTTON_reloadbound=NULL;
GLUI_Button *BUTTON_compress=NULL;
GLUI_Button *BUTTON_step=NULL;
GLUI_Button *BUTTON_script_stop=NULL;
GLUI_Button *BUTTON_script_start=NULL;
GLUI_Button *BUTTON_script_saveini=NULL;
GLUI_Button *BUTTON_script_render=NULL;
GLUI_Button *BUTTON_update_line_contour=NULL;
GLUI_Button *BUTTON_ini_load=NULL;
GLUI_Button *BUTTON_script_setsuffix=NULL;
GLUI_Button *BUTTON_script_runscript=NULL;
GLUI_Button *BUTTON_SETTIME=NULL;
GLUI_Button *BUTTON_EVAC = NULL;
GLUI_Button *BUTTON_PART = NULL;
GLUI_Button *BUTTON_SLICE = NULL;
GLUI_Button *BUTTON_VSLICE = NULL;
GLUI_Button *BUTTON_PLOT3D = NULL;
GLUI_Button *BUTTON_3DSMOKE = NULL;
GLUI_Button *BUTTON_BOUNDARY = NULL;
GLUI_Button *BUTTON_ISO = NULL;
#ifdef pp_NEWBOUND_DIALOG
GLUI_Button *BUTTON_slice_global_bounds = NULL;
GLUI_Button *BUTTON_slice_global_bounds_loaded = NULL;
GLUI_Button *BUTTON_slice_percentile_bounds = NULL;
#endif

GLUI_Listbox *LIST_colortable = NULL;
GLUI_Listbox *LIST_iso_colorbar = NULL;

#ifdef pp_MEMDEBUG
GLUI_Rollout *ROLLOUT_memcheck=NULL;
#endif
GLUI_Rollout *ROLLOUT_boundary_temp_threshold;
GLUI_Rollout *ROLLOUT_boundary_duplicates;
GLUI_Rollout *ROLLOUT_iso_settings;
GLUI_Rollout *ROLLOUT_iso_bounds;
GLUI_Rollout *ROLLOUT_iso_color;
GLUI_Rollout *ROLLOUT_script = NULL;
GLUI_Rollout *ROLLOUT_config = NULL;
GLUI_Rollout *ROLLOUT_boundary_bound = NULL;
GLUI_Rollout *ROLLOUT_boundary_chop = NULL;
GLUI_Rollout *ROLLOUT_plot3d_bound = NULL;
GLUI_Rollout *ROLLOUT_plot3d_chop = NULL;
GLUI_Rollout *ROLLOUT_autoload=NULL;
GLUI_Rollout *ROLLOUT_compress=NULL;
GLUI_Rollout *ROLLOUT_plot3d=NULL,*ROLLOUT_part=NULL,*ROLLOUT_slice=NULL,*ROLLOUT_bound=NULL,*ROLLOUT_iso=NULL;
GLUI_Rollout *ROLLOUT_iso_colors = NULL;
GLUI_Rollout *ROLLOUT_smoke3d=NULL,*ROLLOUT_volsmoke3d=NULL;
GLUI_Rollout *ROLLOUT_time=NULL,*ROLLOUT_colorbar=NULL;
GLUI_Rollout *ROLLOUT_outputpatchdata=NULL;
GLUI_Rollout *ROLLOUT_boundimmersed = NULL;
GLUI_Rollout *ROLLOUT_filebounds = NULL;
GLUI_Rollout *ROLLOUT_showhide = NULL;
GLUI_Rollout *ROLLOUT_slice_average = NULL;
GLUI_Rollout *ROLLOUT_slice_histogram = NULL;
GLUI_Rollout *ROLLOUT_slice_vector = NULL;
GLUI_Rollout *ROLLOUT_line_contour = NULL;
GLUI_Rollout *ROLLOUT_slicedups = NULL;
GLUI_Rollout *ROLLOUT_vector = NULL;
GLUI_Rollout *ROLLOUT_isosurface = NULL;
GLUI_Rollout *ROLLOUT_boundary_settings = NULL;
GLUI_Rollout *ROLLOUT_particle_settings=NULL;

#ifndef pp_NEWBOUND_DIALOG
GLUI_Panel *PANEL_slice_bound = NULL;
#endif

GLUI_Panel *PANEL_partread = NULL;
#ifdef pp_SLICETHREAD
GLUI_Panel *PANEL_sliceread = NULL;
#endif
GLUI_Panel *PANEL_boundary_outline_type = NULL;
GLUI_Panel *PANEL_iso1 = NULL;
GLUI_Panel *PANEL_iso2 = NULL;
GLUI_Panel *PANEL_geomexp = NULL;
GLUI_Panel *PANEL_slice_smoke = NULL;
GLUI_Panel *PANEL_immersed = NULL;
GLUI_Panel *PANEL_immersed_region = NULL;
GLUI_Panel *PANEL_immersed_drawas = NULL;
GLUI_Panel *PANEL_immersed_outlinetype = NULL;
GLUI_Panel *PANEL_where = NULL;
GLUI_Panel *PANEL_sliceshow=NULL;
GLUI_Panel *PANEL_slicedup = NULL;
GLUI_Panel *PANEL_vectorslicedup = NULL;
GLUI_Panel *PANEL_iso_eachlevel = NULL;
GLUI_Panel *PANEL_iso_alllevels = NULL;
GLUI_Panel *PANEL_files = NULL;
GLUI_Panel *PANEL_bounds = NULL;
GLUI_Panel *PANEL_zone_a=NULL, *PANEL_zone_b=NULL;
GLUI_Panel *PANEL_evac_direction=NULL;
GLUI_Panel *PANEL_pan1=NULL;
GLUI_Panel *PANEL_pan2=NULL;
GLUI_Panel *PANEL_run=NULL;
GLUI_Panel *PANEL_record=NULL;
GLUI_Panel *PANEL_script1=NULL;
GLUI_Panel *PANEL_script1a=NULL;
GLUI_Panel *PANEL_script1b=NULL;
GLUI_Panel *PANEL_script1c=NULL;
GLUI_Panel *PANEL_script2a=NULL;
GLUI_Panel *PANEL_script2b=NULL;
GLUI_Panel *PANEL_script3=NULL;
GLUI_Panel *PANEL_transparency2=NULL;
GLUI_Panel *PANEL_time2=NULL;
GLUI_Panel *PANEL_time1a=NULL;
GLUI_Panel *PANEL_time2a=NULL;
GLUI_Panel *PANEL_time2b=NULL;
GLUI_Panel *PANEL_time2c=NULL;
GLUI_Panel *PANEL_outputpatchdata=NULL;

#ifdef pp_SLICETHREAD
GLUI_Spinner *SPINNER_nslicethread_ids = NULL;
#endif
GLUI_Spinner *SPINNER_npartthread_ids = NULL;
GLUI_Spinner *SPINNER_iso_outline_ioffset = NULL;
GLUI_Spinner *SPINNER_histogram_width_factor = NULL;
GLUI_Spinner *SPINNER_histogram_nbuckets=NULL;
GLUI_Spinner *SPINNER_iso_level = NULL;
GLUI_Spinner *SPINNER_iso_colors[4];
GLUI_Spinner *SPINNER_iso_transparency;
GLUI_Spinner *SPINNER_transparent_level = NULL;
GLUI_Spinner *SPINNER_line_contour_num=NULL;
GLUI_Spinner *SPINNER_line_contour_width=NULL;
GLUI_Spinner *SPINNER_line_contour_min=NULL;
GLUI_Spinner *SPINNER_line_contour_max=NULL;
GLUI_Spinner *SPINNER_timebounds=NULL;
GLUI_Spinner *SPINNER_tload_begin=NULL;
GLUI_Spinner *SPINNER_tload_end=NULL;
GLUI_Spinner *SPINNER_tload_skip=NULL;
GLUI_Spinner *SPINNER_plot3d_vectorpointsize=NULL,*SPINNER_plot3d_vectorlinewidth=NULL,*SPINNER_plot3d_vectorlinelength=NULL;
GLUI_Spinner *SPINNER_sliceaverage=NULL;
GLUI_Spinner *SPINNER_smoke3dzipstep=NULL;
GLUI_Spinner *SPINNER_slicezipstep=NULL;
GLUI_Spinner *SPINNER_isozipstep=NULL;
GLUI_Spinner *SPINNER_boundzipstep=NULL;
GLUI_Spinner *SPINNER_partstreaklength=NULL;
GLUI_Spinner *SPINNER_partpointsize=NULL;
GLUI_Spinner *SPINNER_isopointsize=NULL;
GLUI_Spinner *SPINNER_isolinewidth=NULL;
GLUI_Spinner *SPINNER_plot3dpointsize=NULL;
GLUI_Spinner *SPINNER_plot3dlinewidth=NULL;
GLUI_Spinner *SPINNER_streaklinewidth=NULL;
GLUI_Spinner *SPINNER_vectorpointsize=NULL;
GLUI_Spinner *SPINNER_vectorlinewidth=NULL;
GLUI_Spinner *SPINNER_vectorlinelength=NULL;
GLUI_Spinner *SPINNER_slicevectorskip=NULL;
GLUI_Spinner *SPINNER_plot3dvectorskip=NULL;

GLUI_Listbox *LIST_scriptlist=NULL;
GLUI_Listbox *LIST_ini_list=NULL;

GLUI_EditText *EDIT_iso_valmin=NULL;
GLUI_EditText *EDIT_iso_valmax=NULL;
GLUI_EditText *EDIT_zone_min=NULL, *EDIT_zone_max=NULL;
GLUI_EditText *EDIT_ini=NULL;
GLUI_EditText *EDIT_renderdir=NULL;
GLUI_EditText *EDIT_rendersuffix=NULL;
GLUI_EditText *EDIT_slice_min=NULL, *EDIT_slice_max=NULL;
GLUI_EditText *EDIT_slice_chopmin=NULL, *EDIT_slice_chopmax=NULL;
GLUI_EditText *EDIT_patch_chopmin=NULL, *EDIT_patch_chopmax=NULL;
GLUI_EditText *EDIT_part_chopmin=NULL, *EDIT_part_chopmax=NULL;
GLUI_EditText *EDIT_patch_min=NULL, *EDIT_patch_max=NULL;
GLUI_EditText *EDIT_part_min=NULL, *EDIT_part_max=NULL;
GLUI_EditText *EDIT_p3_min=NULL, *EDIT_p3_max=NULL;
GLUI_EditText *EDIT_p3_chopmin=NULL, *EDIT_p3_chopmax=NULL;

GLUI_Checkbox *CHECKBOX_show_boundary_outline=NULL;
#ifdef pp_SLICETHREAD
GLUI_Checkbox *CHECKBOX_slice_multithread = NULL;
#endif
GLUI_Checkbox *CHECKBOX_part_multithread = NULL;
GLUI_Checkbox *CHECKBOX_partfast = NULL;
GLUI_Checkbox *CHECKBOX_show_slice_shaded = NULL;
GLUI_Checkbox *CHECKBOX_show_slice_outlines = NULL;
GLUI_Checkbox *CHECKBOX_show_slice_points = NULL;

GLUI_Checkbox *CHECKBOX_show_iso_shaded=NULL;
GLUI_Checkbox *CHECKBOX_show_iso_outline=NULL;
GLUI_Checkbox *CHECKBOX_show_iso_points=NULL;

GLUI_Checkbox *CHECKBOX_boundary_load_incremental=NULL;
GLUI_Checkbox *CHECKBOX_slice_load_incremental=NULL;
GLUI_Checkbox *CHECKBOX_histogram_show_numbers=NULL;
GLUI_Checkbox *CHECKBOX_histogram_show_graph=NULL;
GLUI_Checkbox *CHECKBOX_histogram_show_outline=NULL;
GLUI_Checkbox *CHECKBOX_color_vector_black = NULL;
GLUI_Checkbox *CHECKBOX_show_node_slices_and_vectors=NULL;
GLUI_Checkbox *CHECKBOX_show_cell_slices_and_vectors=NULL;
GLUI_Checkbox *CHECKBOX_cache_boundarydata=NULL;
GLUI_Checkbox *CHECKBOX_showpatch_both=NULL;
GLUI_Checkbox *CHECKBOX_showchar=NULL, *CHECKBOX_showonlychar;
GLUI_Checkbox *CHECKBOX_script_step=NULL;
GLUI_Checkbox *CHECKBOX_show_evac_slices=NULL;
GLUI_Checkbox *CHECKBOX_constant_coloring=NULL;
GLUI_Checkbox *CHECKBOX_show_evac_color=NULL;
GLUI_Checkbox *CHECKBOX_data_coloring=NULL;
GLUI_Checkbox *CHECKBOX_sort2=NULL;
GLUI_Checkbox *CHECKBOX_smooth2=NULL;
GLUI_Checkbox *CHECKBOX_overwrite_all=NULL;
GLUI_Checkbox *CHECKBOX_compress_autoloaded=NULL;
GLUI_Checkbox *CHECKBOX_erase_all=NULL;
GLUI_Checkbox *CHECKBOX_multi_task=NULL;
GLUI_Checkbox *CHECKBOX_slice_setchopmin=NULL;
GLUI_Checkbox *CHECKBOX_slice_setchopmax=NULL;
GLUI_Checkbox *CHECKBOX_p3_setchopmin=NULL, *CHECKBOX_p3_setchopmax=NULL;
GLUI_Checkbox *CHECKBOX_patch_setchopmin=NULL, *CHECKBOX_patch_setchopmax=NULL;
GLUI_Checkbox *CHECKBOX_part_setchopmin=NULL, *CHECKBOX_part_setchopmax=NULL;
GLUI_Checkbox *CHECKBOX_showtracer=NULL;
GLUI_Checkbox *CHECKBOX_cellcenter_slice_interp=NULL;
GLUI_Checkbox *CHECKBOX_skip_subslice=NULL;
GLUI_Checkbox *CHECKBOX_turb_slice=NULL;
GLUI_Checkbox *CHECKBOX_average_slice=NULL;
GLUI_Checkbox *CHECKBOX_cache_qdata=NULL;
GLUI_Checkbox *CHECKBOX_use_tload_begin=NULL;
GLUI_Checkbox *CHECKBOX_use_tload_end=NULL;
GLUI_Checkbox *CHECKBOX_use_tload_skip=NULL;
GLUI_Checkbox *CHECKBOX_research_mode=NULL;

GLUI_RadioGroup *RADIO_iso_setmin=NULL;
GLUI_RadioGroup *RADIO_iso_setmax=NULL;
GLUI_RadioGroup *RADIO_transparency_option=NULL;
GLUI_RadioGroup *RADIO_slice_celltype=NULL;
GLUI_RadioGroup *RADIO_slice_edgetype=NULL;
GLUI_RadioGroup *RADIO_boundary_edgetype = NULL;
GLUI_RadioGroup *RADIO_show_slice_in_obst=NULL;
GLUI_RadioGroup *RADIO_boundaryslicedup = NULL;
GLUI_RadioGroup *RADIO_slicedup = NULL;
GLUI_RadioGroup *RADIO_vectorslicedup = NULL;
GLUI_RadioGroup *RADIO_histogram_static=NULL;
GLUI_RadioGroup *RADIO_showhide = NULL;
GLUI_RadioGroup *RADIO_contour_type = NULL;
GLUI_RadioGroup *RADIO_zone_setmin=NULL, *RADIO_zone_setmax=NULL;
GLUI_RadioGroup *RADIO_bf=NULL, *RADIO_p3=NULL,*RADIO_slice=NULL;
GLUI_RadioGroup *RADIO_part5=NULL;
GLUI_RadioGroup *RADIO_plot3d_isotype=NULL;
GLUI_RadioGroup *RADIO_plot3d_display=NULL;
#ifndef pp_NEWBOUND_DIALOG
GLUI_RadioGroup *RADIO_slice_setmin=NULL, *RADIO_slice_setmax=NULL;
#endif
GLUI_RadioGroup *RADIO_patch_setmin=NULL, *RADIO_patch_setmax=NULL;
GLUI_RadioGroup *RADIO_part_setmin=NULL, *RADIO_part_setmax=NULL;
#ifdef pp_MEMDEBUG
GLUI_RadioGroup *RADIO_memcheck=NULL;
#endif
GLUI_RadioGroup *RADIO_p3_setmin=NULL, *RADIO_p3_setmax=NULL;
#ifdef pp_NEWBOUND_DIALOG
GLUI_RadioGroup *RADIO_slice_loaded_only = NULL;
#endif

GLUI_RadioButton *RADIOBUTTON_plot3d_iso_hidden=NULL;
GLUI_RadioButton *RADIOBUTTON_zone_permin=NULL;
GLUI_RadioButton *RADIOBUTTON_zone_permax=NULL;
GLUI_RadioButton *RADIO_part_setmin_percentile=NULL;
GLUI_RadioButton *RADIO_part_setmax_percentile=NULL;

GLUI_StaticText *STATIC_bound_min_unit=NULL;
GLUI_StaticText *STATIC_bound_max_unit=NULL;
GLUI_StaticText *STATIC_slice_min_unit=NULL;
GLUI_StaticText *STATIC_slice_max_unit=NULL;
#ifdef pp_NEWBOUND_DIALOG
GLUI_StaticText *STATIC_slice_min = NULL;
GLUI_StaticText *STATIC_slice_max = NULL;
#endif

GLUI_StaticText *STATIC_part_min_unit=NULL;
GLUI_StaticText *STATIC_part_max_unit=NULL;
GLUI_StaticText *STATIC_plot3d_min_unit=NULL;
GLUI_StaticText *STATIC_plot3d_max_unit=NULL;
GLUI_StaticText *STATIC_bound_cmin_unit=NULL;
GLUI_StaticText *STATIC_bound_cmax_unit=NULL;
GLUI_StaticText *STATIC_slice_cmin_unit=NULL;
GLUI_StaticText *STATIC_slice_cmax_unit=NULL;
GLUI_StaticText *STATIC_part_cmin_unit=NULL;
GLUI_StaticText *STATIC_part_cmax_unit=NULL;
GLUI_StaticText *STATIC_plot3d_cmin_unit=NULL;
GLUI_StaticText *STATIC_plot3d_cmax_unit=NULL;

#define ZONE_ROLLOUT 0
#define SMOKE3D_ROLLOUT 1
#define BOUNDARY_ROLLOUT 2
#define ISO_ROLLOUT 3
#define PART_ROLLOUT 4
#define EVAC_ROLLOUT 5
#define PLOT3D_ROLLOUT 6
#define SLICE_ROLLOUT 7

#define ISO_ROLLOUT_BOUNDS 0
#define ISO_ROLLOUT_SETTINGS 1
#define ISO_ROLLOUT_COLOR 2

#define SLICE_BOUND             0
#define SLICE_CHOP              1
#define SLICE_AVERAGE_ROLLOUT   2
#define SLICE_VECTOR_ROLLOUT    3
#define LINE_CONTOUR_ROLLOUT    4
#define SLICE_HISTOGRAM_ROLLOUT 5
#define SLICE_DUP_ROLLOUT       6
#define SLICE_SETTINGS_ROLLOUT  7

#define PLOT3D_BOUND              0
#define PLOT3D_CHOP               1
#define PLOT3D_VECTOR_ROLLOUT     2
#define PLOT3D_ISOSURFACE_ROLLOUT 3

#define LOAD_ROLLOUT 0
#define SHOWHIDE_ROLLOUT 1
#define COMPRESS_ROLLOUT 2
#define SCRIPT_ROLLOUT 3
#define CONFIG_ROLLOUT 4
#define FILEBOUNDS_ROLLOUT 5
#define TIME_ROLLOUT 6
#define MEMCHECK_ROLLOUT 7

procdata  boundprocinfo[8],   fileprocinfo[8],   plot3dprocinfo[4];
int      nboundprocinfo = 0, nfileprocinfo = 0, nplot3dprocinfo=0;
procdata  isoprocinfo[3], subboundprocinfo[6], sliceprocinfo[8], particleprocinfo[3];
int      nisoprocinfo=0, nsubboundprocinfo=0, nsliceprocinfo=0, nparticleprocinfo=0;

/* ------------------ UpdateGluiPartFast ------------------------ */

extern "C" void UpdateGluiPartFast(void){
  if(CHECKBOX_partfast!=NULL)CHECKBOX_partfast->set_int_val(partfast);
  if(CHECKBOX_part_multithread!=NULL)CHECKBOX_part_multithread->set_int_val(part_multithread);
  PartBoundCB(PARTFAST);
}

/* ------------------ UpdateListIsoColorobar ------------------------ */

extern "C" void UpdateListIsoColorobar(void){
  if(LIST_iso_colorbar!=NULL)LIST_iso_colorbar->set_int_val(iso_colorbar_index);
}


/* ------------------ UpdateGluiIsoBounds ------------------------ */

extern "C" void UpdateGluiIsoBounds(void){
  if(setisomin==PERCENTILE_MIN||setisomin==GLOBAL_MIN){
    if(setisomin==PERCENTILE_MIN)glui_iso_valmin=iso_percentile_min;
    if(setisomin==GLOBAL_MIN)glui_iso_valmin=iso_global_min;
    if(EDIT_iso_valmin!=NULL)EDIT_iso_valmin->set_float_val(glui_iso_valmin);
  }
  if(setisomax==PERCENTILE_MAX||setisomax==GLOBAL_MAX){
    if(setisomax==PERCENTILE_MAX)glui_iso_valmax=iso_percentile_max;
    if(setisomax==GLOBAL_MAX)glui_iso_valmax=iso_global_max;
    if(EDIT_iso_valmax!=NULL)EDIT_iso_valmax->set_float_val(glui_iso_valmax);
  }
}

/* ------------------ LoadIncrementalCB1 ------------------------ */

extern "C" void LoadIncrementalCB1(int var){
  if(CHECKBOX_boundary_load_incremental!=NULL)CHECKBOX_boundary_load_incremental->set_int_val(load_incremental);
  if(CHECKBOX_slice_load_incremental!=NULL)CHECKBOX_slice_load_incremental->set_int_val(load_incremental);
}

/* ------------------ UpdateVectorpointsize ------------------------ */

extern "C" void UpdateVectorpointsize(void){
  if(SPINNER_vectorpointsize!=NULL)SPINNER_vectorpointsize->set_int_val(vectorpointsize);
}

/* ------------------ UpdateSliceDupDialog ------------------------ */

extern "C" void UpdateSliceDupDialog(void){
  if(RADIO_boundaryslicedup != NULL)RADIO_boundaryslicedup->set_int_val(boundaryslicedup_option);
  if(RADIO_slicedup != NULL)RADIO_slicedup->set_int_val(slicedup_option);
  if(RADIO_vectorslicedup != NULL)RADIO_vectorslicedup->set_int_val(vectorslicedup_option);
}

/* ------------------ UpdateImmersedControls ------------------------ */

extern "C" void UpdateImmersedControls(void){
}

/* ------------------ UpdateIsoControls ------------------------ */

void UpdateIsoControls(void){
  if(use_transparency_data==1){
    if(SPINNER_iso_colors[3] != NULL)SPINNER_iso_colors[3]->enable();
    if(SPINNER_iso_transparency != NULL)SPINNER_iso_transparency->enable();
    if(BUTTON_updatebound != NULL)BUTTON_updatebound->enable();
  }
  else{
    if(SPINNER_iso_colors[3] != NULL)SPINNER_iso_colors[3]->disable();
    if(SPINNER_iso_transparency != NULL)SPINNER_iso_transparency->disable();
    if(BUTTON_updatebound != NULL)BUTTON_updatebound->disable();
  }
}

/* ------------------ UpdateHistogramType ------------------------ */

extern "C" void UpdateHistogramType(void){
  RADIO_histogram_static->set_int_val(histogram_static);
  CHECKBOX_histogram_show_graph->set_int_val(histogram_show_graph);
  CHECKBOX_histogram_show_numbers->set_int_val(histogram_show_numbers);
  CHECKBOX_histogram_show_outline->set_int_val(histogram_show_outline);
}

/* ------------------ UpdateShowSliceInObst ------------------------ */

extern "C" void UpdateShowSliceInObst(void){
  RADIO_show_slice_in_obst->set_int_val(show_slice_in_obst);
  if(show_slice_in_obst!=show_slice_in_obst_old){
    SliceBoundCB(FILEUPDATE);
    show_slice_in_obst_old = show_slice_in_obst;
  }
}

/* ------------------ UpdateIsoColorlevel ------------------------ */

extern "C" void UpdateIsoColorlevel(void){
  IsoBoundCB(ISO_LEVEL);
  IsoBoundCB(ISO_COLORS);
}

/* ------------------ ParticleRolloutCB ------------------------ */

void ParticleRolloutCB(int var){
  ToggleRollout(particleprocinfo, nparticleprocinfo, var);
}

/* ------------------ Plot3dRolloutCB ------------------------ */

void Plot3dRolloutCB(int var){
  ToggleRollout(plot3dprocinfo, nplot3dprocinfo, var);
}

/* ------------------ SliceRolloutCB ------------------------ */

void SliceRolloutCB(int var){
  ToggleRollout(sliceprocinfo, nsliceprocinfo, var);
}

/* ------------------ IsoRolloutCB ------------------------ */

void IsoRolloutCB(int var){
  ToggleRollout(isoprocinfo, nisoprocinfo, var);
}

/* ------------------ BoundRolloutCB ------------------------ */

void BoundRolloutCB(int var){
  ToggleRollout(boundprocinfo, nboundprocinfo, var);
  if(nzoneinfo>0){
    if(var==ZONE_ROLLOUT){
      SliceBoundCB(SETZONEVALMINMAX);
    }
    if(var==SLICE_ROLLOUT){
      list_slice_index = CLAMP(list_slice_index,0,nlist_slice_index-1);
      RADIO_slice->set_int_val(list_slice_index);
      SliceBoundCB(FILETYPEINDEX);
    }
  }
}

/* ------------------ SubBoundRolloutCB ------------------------ */

void SubBoundRolloutCB(int var){
  ToggleRollout(subboundprocinfo, nsubboundprocinfo, var);
}

/* ------------------ FileRolloutCB ------------------------ */

void FileRolloutCB(int var){
  ToggleRollout(fileprocinfo, nfileprocinfo, var);
}

/* ------------------ UpdateGluiZoneBounds ------------------------ */

extern "C" void UpdateGluiZoneBounds(void){
  if(EDIT_zone_min!=NULL)EDIT_zone_min->set_float_val(zonemin);
  if(EDIT_zone_max!=NULL)EDIT_zone_max->set_float_val(zonemax);
}
/* ------------------ UpdateGluiVecFactor ------------------------ */

extern "C" void UpdateGluiVecFactor(void){
  if(SPINNER_plot3d_vectorlinelength!=NULL)SPINNER_plot3d_vectorlinelength->set_float_val(vecfactor);
  if(SPINNER_vectorlinelength!=NULL)SPINNER_vectorlinelength->set_float_val(vecfactor);
}

/* ------------------ UpdateGluiPartSetBounds ------------------------ */

extern "C" void UpdateGluiPartSetBounds(int minbound_type, int maxbound_type){
  if(RADIO_part_setmin!=NULL)RADIO_part_setmin->set_int_val(minbound_type);
  if(RADIO_part_setmax!=NULL)RADIO_part_setmax->set_int_val(maxbound_type);
  PartBoundCB(FILETYPEINDEX);
}

  /* ------------------ UpdateGluiPartUnits ------------------------ */

extern "C" void UpdateGluiPartUnits(void){
  if(STATIC_part_min_unit!=NULL){
    if(partmin_unit!=NULL){
      STATIC_part_min_unit->set_name((char *)partmin_unit);
    }
    else{
      STATIC_part_min_unit->set_name((char *)"");
    }
  }
  if(STATIC_part_cmin_unit!=NULL){
    if(partmin_unit!=NULL){
      STATIC_part_cmin_unit->set_name((char *)partmin_unit);
    }
    else{
      STATIC_part_cmin_unit->set_name((char *)"");
    }
  }
  if(STATIC_part_max_unit!=NULL){
    if(partmax_unit!=NULL){
      STATIC_part_max_unit->set_name((char *)partmax_unit);
    }
    else{
      STATIC_part_max_unit->set_name((char *)"");
    }
  }
  if(STATIC_part_cmax_unit!=NULL){
    if(partmax_unit!=NULL){
      STATIC_part_cmax_unit->set_name((char *)partmax_unit);
    }
    else{
      STATIC_part_cmax_unit->set_name((char *)"");
    }
  }
}

/* ------------------ UpdateGluiPlot3D_units ------------------------ */

extern "C" void UpdateGluiPlot3D_units(void){
  if(STATIC_plot3d_min_unit!=NULL&&plot3dmin_unit!=NULL){
    STATIC_plot3d_min_unit->set_name((char *)plot3dmin_unit);
  }
  if(STATIC_plot3d_max_unit!=NULL&&plot3dmax_unit!=NULL){
    STATIC_plot3d_max_unit->set_name((char *)plot3dmax_unit);
  }
  if(STATIC_plot3d_cmin_unit!=NULL&&plot3dmin_unit!=NULL){
    STATIC_plot3d_cmin_unit->set_name((char *)plot3dmin_unit);
  }
  if(STATIC_plot3d_cmax_unit!=NULL&&plot3dmax_unit!=NULL){
    STATIC_plot3d_cmax_unit->set_name((char *)plot3dmax_unit);
  }
}

/* ------------------ UpdateGluiSliceUnits ------------------------ */

extern "C" void UpdateGluiSliceUnits(void){
  if(STATIC_slice_min_unit!=NULL&&glui_slicemin_unit!=NULL){
    STATIC_slice_min_unit->set_name((char *)glui_slicemin_unit);
  }
  if(STATIC_slice_max_unit!=NULL&&glui_slicemax_unit!=NULL){
    STATIC_slice_max_unit->set_name((char *)glui_slicemax_unit);
  }
  if(STATIC_slice_cmin_unit!=NULL&&glui_slicemin_unit!=NULL){
    STATIC_slice_cmin_unit->set_name((char *)glui_slicemin_unit);
  }
  if(STATIC_slice_cmax_unit!=NULL&&glui_slicemax_unit!=NULL){
    STATIC_slice_cmax_unit->set_name((char *)glui_slicemax_unit);
  }
}

/* ------------------ UpdateGluiBoundaryUnits ------------------------ */

extern "C" void UpdateGluiBoundaryUnits(void){
  if(STATIC_bound_min_unit!=NULL&&patchmin_unit!=NULL){
    STATIC_bound_min_unit->set_name((char *)patchmin_unit);
  }
  if(STATIC_bound_max_unit!=NULL&&patchmax_unit!=NULL){
    STATIC_bound_max_unit->set_name((char *)patchmax_unit);
  }
  if(STATIC_bound_cmin_unit!=NULL&&patchmin_unit!=NULL){
    STATIC_bound_cmin_unit->set_name((char *)patchmin_unit);
  }
  if(STATIC_bound_cmax_unit!=NULL&&patchmax_unit!=NULL){
    STATIC_bound_cmax_unit->set_name((char *)patchmax_unit);
  }
}

/* ------------------ UpdateResearchMode ------------------------ */

extern "C" void UpdateResearchMode(void){
  SliceBoundCB(RESEARCH_MODE);
  if(CHECKBOX_research_mode!=NULL)CHECKBOX_research_mode->set_int_val(research_mode);
}
/* ------------------ UpdateScriptStop ------------------------ */

extern "C" void UpdateScriptStop(void){
  if(BUTTON_script_start!=NULL)BUTTON_script_start->enable();
  if(BUTTON_script_stop!=NULL)BUTTON_script_stop->disable();
  if(BUTTON_script_runscript!=NULL)BUTTON_script_runscript->enable();
  if(EDIT_renderdir!=NULL)EDIT_renderdir->enable();
}

/* ------------------ UpdateScriptStart ------------------------ */

extern "C" void UpdateScriptStart(void){
  if(BUTTON_script_start!=NULL)BUTTON_script_start->disable();
  if(BUTTON_script_stop!=NULL)BUTTON_script_stop->enable();
  if(BUTTON_script_runscript!=NULL)BUTTON_script_runscript->disable();
  if(EDIT_renderdir!=NULL)EDIT_renderdir->disable();
}

/* ------------------ UpdateScriptStep ------------------------ */

extern "C" void UpdateScriptStep(void){
  CHECKBOX_script_step->set_int_val(script_step);
  if(script_step==1){
    BUTTON_step->enable();
  }
  else{
    BUTTON_step->disable();
  }
}

/* ------------------ UpdateEvacParms ------------------------ */

extern "C" void UpdateEvacParms(void){
  if(CHECKBOX_show_evac_slices!=NULL)CHECKBOX_show_evac_slices->set_int_val(show_evac_slices);
  if(CHECKBOX_constant_coloring!=NULL)CHECKBOX_constant_coloring->set_int_val(constant_evac_coloring);
  if(CHECKBOX_data_coloring!=NULL)CHECKBOX_data_coloring->set_int_val(data_evac_coloring);
  if(CHECKBOX_show_evac_color!=NULL)CHECKBOX_show_evac_color->set_int_val(show_evac_colorbar);
}

/* ------------------ UpdateGluiPlot3D ------------------------ */

extern "C" void UpdateGluiPlot3D(void){
  Plot3DBoundCB(UNLOAD_QDATA);
}

/* ------------------ PartBoundCBInit ------------------------ */

extern "C" void PartBoundCBInit(void){
  PartBoundCB(FILETYPEINDEX);
}


/* ------------------ ColorTableCompare ------------------------ */

int ColorTableCompare(const void *arg1, const void *arg2){
  colortabledata *cti, *ctj;
  int i, j;

  i = *(int *)arg1;
  j = *(int *)arg2;

  cti = colortableinfo + i;
  ctj = colortableinfo + j;

  return(strcmp(cti->label, ctj->label));
}

/* ------------------ UpdateColorTableList ------------------------ */

extern "C" void UpdateColorTableList(int ncolortableinfo_old){
  int i, *order=NULL;

  if(LIST_colortable==NULL)return;
  for(i = -1; i<ncolortableinfo_old; i++){
    LIST_colortable->delete_item(i);
  }

  if(ncolortableinfo>0){
    NewMemory((void **)&order, ncolortableinfo*sizeof(int));
    for(i = 0; i < ncolortableinfo; i++){
      order[i] = i;
    }
    qsort((int *)order, (size_t)ncolortableinfo, sizeof(int), ColorTableCompare);
  }


  for(i = -1; i<ncolortableinfo; i++){
    if(i==-1){
      LIST_colortable->add_item(i, "Custom");
    }
    else{
      colortabledata *cti;

      cti = colortableinfo+order[i];
      LIST_colortable->add_item(i, cti->label);
    }
  }
  if(ncolortableinfo>0){
    FREEMEMORY(order);
  }
}

/* ------------------ FileShowCB ------------------------ */

extern "C" void FileShowCB(int var){
  updatemenu = 1;
  switch(var){
  case FILESHOW_sizes:
    GetFileSizes();
    break;
  case  FILESHOW_plot3d:
    switch(showhide_option){
    case SHOWALL_FILES:
    case SHOWONLY_FILE:
      Plot3DShowMenu(SHOWALL_PLOT3D);
      break;
    case HIDEALL_FILES:
      Plot3DShowMenu(HIDEALL_PLOT3D);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case FILESHOW_evac:
    switch(showhide_option){
    case SHOWALL_FILES:
      EvacShowMenu(SHOWALL_EVAC);
      break;
    case SHOWONLY_FILE:
      EvacShowMenu(SHOWALL_EVAC);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      if(nsliceloaded != 0)ShowHideSliceMenu(GLUI_HIDEALL_SLICE);
      if(nvsliceloaded != 0)ShowVSliceMenu(GLUI_HIDEALL_VSLICE);
      if(npatchloaded != 0)ShowBoundaryMenu(GLUI_HIDEALL_BOUNDARY);
      break;
    case HIDEALL_FILES:
      EvacShowMenu(HIDEALL_EVAC);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_particle:
    switch(showhide_option){
    case SHOWALL_FILES:
      ParticleShowMenu(SHOWALL_PARTICLE);
      break;
    case SHOWONLY_FILE:
      ParticleShowMenu(SHOWALL_PARTICLE);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      if(nsliceloaded != 0)ShowHideSliceMenu(GLUI_HIDEALL_SLICE);
      if(nvsliceloaded != 0)ShowVSliceMenu(GLUI_HIDEALL_VSLICE);
      if(npatchloaded != 0)ShowBoundaryMenu(GLUI_HIDEALL_BOUNDARY);
      break;
    case HIDEALL_FILES:
      ParticleShowMenu(HIDEALL_PARTICLE);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_slice:
    switch(showhide_option){
    case SHOWALL_FILES:
      ShowHideSliceMenu(GLUI_SHOWALL_SLICE);
      break;
    case SHOWONLY_FILE:
      ShowHideSliceMenu(GLUI_SHOWALL_SLICE);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(nvsliceloaded != 0)ShowVSliceMenu(GLUI_HIDEALL_VSLICE);
      if(npatchloaded != 0)ShowBoundaryMenu(GLUI_HIDEALL_BOUNDARY);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      break;
    case HIDEALL_FILES:
      ShowHideSliceMenu(GLUI_HIDEALL_SLICE);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_vslice:
    switch(showhide_option){
    case SHOWALL_FILES:
      ShowVSliceMenu(GLUI_SHOWALL_VSLICE);
      break;
    case SHOWONLY_FILE:
      ShowVSliceMenu(GLUI_SHOWALL_VSLICE);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(npatchloaded != 0)ShowBoundaryMenu(GLUI_HIDEALL_BOUNDARY);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nsliceloaded != 0)ShowHideSliceMenu(GLUI_HIDEALL_SLICE);
      break;
    case HIDEALL_FILES:
      ShowVSliceMenu(GLUI_HIDEALL_VSLICE);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_boundary:
    switch(showhide_option){
    case SHOWALL_FILES:
      ShowBoundaryMenu(GLUI_SHOWALL_BOUNDARY);
      break;
    case SHOWONLY_FILE:
      ShowBoundaryMenu(GLUI_SHOWALL_BOUNDARY);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nvsliceloaded != 0)ShowVSliceMenu(GLUI_HIDEALL_VSLICE);
      if(nsliceloaded != 0)ShowHideSliceMenu(GLUI_HIDEALL_SLICE);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      break;
    case HIDEALL_FILES:
      ShowBoundaryMenu(GLUI_HIDEALL_BOUNDARY);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_3dsmoke:
    switch(showhide_option){
    case SHOWALL_FILES:
      Smoke3DShowMenu(SHOWALL_SMOKE3D);
      break;
    case SHOWONLY_FILE:
      Smoke3DShowMenu(SHOWALL_SMOKE3D);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(npatchloaded != 0)ShowBoundaryMenu(GLUI_HIDEALL_BOUNDARY);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nvsliceloaded != 0)ShowVSliceMenu(GLUI_HIDEALL_VSLICE);
      if(nsliceloaded != 0)ShowHideSliceMenu(GLUI_HIDEALL_SLICE);
      if(nisoloaded != 0)IsoShowMenu(HIDEALL_ISO);
      break;
    case HIDEALL_FILES:
      Smoke3DShowMenu(HIDEALL_SMOKE3D);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case  FILESHOW_isosurface:
    switch(showhide_option){
    case SHOWALL_FILES:
      IsoShowMenu(SHOWALL_ISO);
      break;
    case SHOWONLY_FILE:
      IsoShowMenu(SHOWALL_ISO);
      if(nevacloaded != 0)EvacShowMenu(HIDEALL_EVAC);
      if(nsmoke3dloaded != 0)Smoke3DShowMenu(HIDEALL_SMOKE3D);
      if(npatchloaded != 0)ShowBoundaryMenu(GLUI_HIDEALL_BOUNDARY);
      if(npartloaded != 0)ParticleShowMenu(HIDEALL_PARTICLE);
      if(nvsliceloaded != 0)ShowVSliceMenu(GLUI_HIDEALL_VSLICE);
      if(nsliceloaded != 0)ShowHideSliceMenu(GLUI_HIDEALL_SLICE);
      break;
    case HIDEALL_FILES:
      IsoShowMenu(HIDEALL_ISO);
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  default:
    break;
  }
}

#ifdef pp_MEMDEBUG

/* ------------------ MemcheckCB ------------------------ */

void MemcheckCB(int var){
  switch(var){
  case MEMCHECK:
    set_memcheck(list_memcheck_index);
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}
#endif

/* ------------------ BoundsDlgCB ------------------------ */

void BoundsDlgCB(int var){
  switch(var){
  case CLOSE_BOUNDS:
#ifndef pp_CLOSEOFF
    glui_bounds->hide();
    updatemenu = 1;
#endif
    break;
  case SAVE_SETTINGS_BOUNDS:
    WriteIni(LOCAL_INI, NULL);
    break;
  case COMPRESS_FILES:
    PRINTF("compressing\n");
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ ImmersedBoundCB ------------------------ */

#define SHOW_POLYGON_EDGES 0
#define SHOW_TRIANGLE_EDGES 1
#define HIDE_EDGES 2
extern "C" void ImmersedBoundCB(int var){
  updatemenu = 1;
  switch(var){
    int i;

  case IMMERSED_SWITCH_CELLTYPE:
    glui_slice_edgetype  = slice_edgetypes[slice_celltype];
    glui_show_slice_shaded  = show_slice_shaded[slice_celltype];
    glui_show_slice_outlines = show_slice_outlines[slice_celltype];
    glui_show_slice_points   = show_slice_points[slice_celltype];
    for(i=0;i<3;i++){
      switch(slice_edgetypes[i]){
        case IMMERSED_POLYGON:
        case IMMERSED_TRIANGLE:
          show_slice_outlines[i]=1;
          break;
        case IMMERSED_HIDDEN:
          show_slice_outlines[i]=0;
          break;
      }
    }
    if(RADIO_slice_edgetype!=NULL)RADIO_slice_edgetype->set_int_val(glui_slice_edgetype);
    if(CHECKBOX_show_slice_shaded!=NULL)CHECKBOX_show_slice_shaded->set_int_val(glui_show_slice_shaded);
    if(CHECKBOX_show_slice_outlines!=NULL)CHECKBOX_show_slice_outlines->set_int_val(glui_show_slice_outlines);
    if(CHECKBOX_show_slice_points!=NULL)CHECKBOX_show_slice_points->set_int_val(glui_show_slice_points);

    break;
  case IMMERSED_SET_DRAWTYPE:
    if(glui_show_slice_outlines == 0){
      glui_slice_edgetype = IMMERSED_HIDDEN;
    }
    else{
      if(glui_slice_edgetype == IMMERSED_HIDDEN)glui_slice_edgetype = IMMERSED_TRIANGLE;
    }
    slice_edgetypes[slice_celltype]     = glui_slice_edgetype;
    show_slice_shaded[slice_celltype]   = glui_show_slice_shaded;
    show_slice_outlines[slice_celltype] = glui_show_slice_outlines;
    show_slice_points[slice_celltype]   = glui_show_slice_points;
    if(RADIO_slice_edgetype!=NULL)RADIO_slice_edgetype->set_int_val(glui_slice_edgetype);
    break;
  case IMMERSED_SWITCH_EDGETYPE:
    switch (glui_slice_edgetype){
    case SHOW_POLYGON_EDGES:
    case SHOW_TRIANGLE_EDGES:
      glui_show_slice_outlines=1;
      break;
    case HIDE_EDGES:
      glui_show_slice_outlines=0;
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    ImmersedBoundCB(IMMERSED_SET_DRAWTYPE);
    if(CHECKBOX_show_slice_outlines!=NULL)CHECKBOX_show_slice_outlines->set_int_val(glui_show_slice_outlines);
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ BoundBoundCB ------------------------ */

void BoundBoundCB(int var){
  int i;

  switch(var){
  case SHOW_BOUNDARY_OUTLINE:
    if(ngeom_data==0)break;
    if(show_boundary_outline==1&&boundary_edgetype==IMMERSED_HIDDEN)boundary_edgetype = IMMERSED_POLYGON;
    if(show_boundary_outline==0&&boundary_edgetype!=IMMERSED_HIDDEN)boundary_edgetype = IMMERSED_HIDDEN;
    if(boundary_edgetype!=RADIO_boundary_edgetype->get_int_val())RADIO_boundary_edgetype->set_int_val(boundary_edgetype);
    break;
  case BOUNDARY_EDGETYPE:
    if(boundary_edgetype==IMMERSED_HIDDEN&&show_boundary_outline==1)show_boundary_outline=0;
    if(boundary_edgetype!=IMMERSED_HIDDEN&&show_boundary_outline==0)show_boundary_outline=1;
    if(show_boundary_outline!=CHECKBOX_show_boundary_outline->get_int_val())CHECKBOX_show_boundary_outline->set_int_val(show_boundary_outline);
    break;
  case UPDATE_BOUNDARYSLICEDUPS:
    UpdateBoundarySliceDups();
    updatemenu = 1;
    break;
  case SHOWPATCH_BOTH:
    updatefacelists = 1;
    updatehiddenfaces = 1;
    break;
  case CACHE_BOUNDARYDATA:
    if(cache_boundarydata == 0){
      BUTTON_updatebound->disable();
    }
    else{
      BUTTON_updatebound->enable();
    }
    break;
  case VALMAX:
  case VALMIN:
    break;
  case HIDEPATCHSURFACE:
    updatefacelists = 1;
    break;
  case FRAMELOADING:
    boundframestep = boundframeskip + 1;
    boundzipstep = boundzipskip + 1;
    updatemenu = 1;
    break;
  case CHOPUPDATE:
    UpdateChopColors();
    break;
  case SETCHOPMINVAL:
    UpdateChopColors();
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    switch(setpatchchopmin){
    case DISABLE:
      EDIT_patch_chopmin->disable();
      break;
    case ENABLE:
      EDIT_patch_chopmin->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    UpdateHideBoundarySurface();
    break;
  case SETCHOPMAXVAL:
    UpdateChopColors();
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    switch(setpatchchopmax){
    case DISABLE:
      EDIT_patch_chopmax->disable();
      break;
    case ENABLE:
      EDIT_patch_chopmax->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    UpdateHideBoundarySurface();
    break;
  case CHOPVALMIN:
    ASSERT(EDIT_patch_min != NULL);
    EDIT_patch_min->set_float_val(patchmin);
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    UpdateChopColors();
    break;
  case CHOPVALMAX:
    ASSERT(EDIT_patch_max != NULL);
    EDIT_patch_max->set_float_val(patchmax);
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    UpdateChopColors();
    break;
  case SHOWCHAR:
    if(CHECKBOX_showchar != NULL&&CHECKBOX_showonlychar != NULL){
      if(vis_threshold == 1){
        CHECKBOX_showonlychar->enable();
      }
      else{
        CHECKBOX_showonlychar->disable();
      }
    }
    updatemenu = 1;
    updatefacelists = 1;
    break;
  case FILETYPEINDEX:
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index_old]);
    Global2LocalBoundaryBounds(patchlabellist[list_patch_index]);

    EDIT_patch_min->set_float_val(patchmin);
    EDIT_patch_max->set_float_val(patchmax);
    EDIT_patch_chopmin->set_float_val(patchchopmin);
    EDIT_patch_chopmax->set_float_val(patchchopmax);

    BoundBoundCB(SETVALMIN);
    BoundBoundCB(SETVALMAX);
    if(RADIO_patch_setmin != NULL)RADIO_patch_setmin->set_int_val(setpatchmin);
    if(RADIO_patch_setmax != NULL)RADIO_patch_setmax->set_int_val(setpatchmax);
    if(CHECKBOX_patch_setchopmin != NULL)CHECKBOX_patch_setchopmin->set_int_val(setpatchchopmin);
    if(CHECKBOX_patch_setchopmax != NULL)CHECKBOX_patch_setchopmax->set_int_val(setpatchchopmax);

    switch(setpatchchopmin){
    case DISABLE:
      EDIT_patch_chopmin->disable();
      break;
    case ENABLE:
      EDIT_patch_chopmin->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    switch(setpatchchopmax){
    case DISABLE:
      EDIT_patch_chopmax->disable();
      break;
    case ENABLE:
      EDIT_patch_chopmax->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }

    list_patch_index_old = list_patch_index;
    UpdateHideBoundarySurface();
    break;
  case SETVALMIN:
    switch(setpatchmin){
    case PERCENTILE_MIN:
    case GLOBAL_MIN:
      EDIT_patch_min->disable();
      break;
    case SET_MIN:
      EDIT_patch_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    BoundBoundCB(FILEUPDATE);
    break;
  case SETVALMAX:
    switch(setpatchmax){
    case PERCENTILE_MAX:
    case GLOBAL_MAX:
      EDIT_patch_max->disable();
      break;
    case SET_MAX:
      EDIT_patch_max->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    BoundBoundCB(FILEUPDATE);
    break;
  case FILEUPDATE:
    Local2GlobalBoundaryBounds(patchlabellist[list_patch_index]);
    break;
  case FILEUPDATEDATA:
    UpdateAllBoundaryColors();
    break;
  case FILERELOAD:
    BoundBoundCB(FILEUPDATE);
    for(i = 0;i < npatchinfo;i++){
      patchdata *patchi;

      patchi = patchinfo + i;
      if(patchi->loaded == 0)continue;
      LoadBoundaryMenu(i);
    }
    EDIT_patch_min->set_float_val(patchmin);
    EDIT_patch_max->set_float_val(patchmax);
    break;
  case COMPRESS_FILES:
    CompressSVZip();
    break;
  case COMPRESS_AUTOLOADED:
    updatemenu = 1;
    break;
  case OVERWRITE:
    if(overwrite_all == 1){
      CHECKBOX_erase_all->set_int_val(0);
    }
    updatemenu = 1;
    break;
  case ERASE:
    if(erase_all == 1){
      CHECKBOX_overwrite_all->set_int_val(0);
    }
    updatemenu = 1;
    break;
  case STARTUP:
    BoundsDlgCB(SAVE_SETTINGS_BOUNDS);
    break;
  case SAVE_FILE_LIST:
    Set3DSmokeStartup();
    BoundsDlgCB(SAVE_SETTINGS_BOUNDS);
    break;
  case LOAD_FILES:
    LoadFiles();
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ Smoke3dBoundCB ------------------------ */

void Smoke3dBoundCB(int var){
  switch(var){
  case FRAMELOADING:
    smoke3dframestep = smoke3dframeskip + 1;
    smoke3dzipstep = smoke3dzipskip + 1;
    updatemenu = 1;
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ TimeBoundCB ------------------------ */

void TimeBoundCB(int var){

  updatemenu = 1;
  switch(var){
  case SET_TIME:
    SetTimeVal(glui_time);
    break;
  case TBOUNDS:
    if(use_tload_begin == 1 || use_tload_end == 1 || use_tload_skip == 1){
      UpdateTBounds();
    }
    break;
  case TBOUNDS_USE:
    if(use_tload_begin == 1){
      SPINNER_tload_begin->enable();
    }
    else{
      SPINNER_tload_begin->disable();
    }
    if(use_tload_end == 1){
      SPINNER_tload_end->enable();
    }
    else{
      SPINNER_tload_end->disable();
    }
    if(use_tload_skip == 1){
      SPINNER_tload_skip->enable();
    }
    else{
      SPINNER_tload_skip->disable();
    }
    UpdateTBounds();
    break;
  case RELOAD_ALL_DATA:
    ReloadMenu(RELOAD_ALL_NOW);
    break;
  case RELOAD_INCREMENTAL_DATA:
    ReloadMenu(RELOAD_INCREMENTAL_NOW);
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ ScriptCB ------------------------ */

void ScriptCB(int var){
  char label[1024];
  char *name;
  int id;
  int len, i;
  int set_renderlabel;

  switch(var){
  case SCRIPT_STEP_NOW:
    Keyboard('^', FROM_SMOKEVIEW);
    break;
  case SCRIPT_CANCEL_NOW:
    current_script_command = NULL;
    runscript = 0;
    first_frame_index = 0;
    script_startframe = -1;
    script_skipframe = -1;
    script_step = 0;
    GluiScriptEnable();
    render_status = RENDER_OFF;
    break;
  case SCRIPT_RENDER_DIR:
    strcpy(label, script_renderdir);
    TrimBack(label);
    name = TrimFront(label);
    set_renderlabel = 0;
    if(name != NULL&&strlen(name) != strlen(script_renderdir)){
      strcpy(script_renderdir, name);
      set_renderlabel = 1;
    }
    name = script_renderdir;
    len = strlen(script_renderdir);
    if(len == 0)break;
    for(i = 0;i < len;i++){
#ifdef WIN32
      if(name[i] == '/'){
        set_renderlabel = 1;
        name[i] = '\\';
      }
#else
      if(name[i] == '\\'){
        set_renderlabel = 1;
        name[i] = '/';
      }
#endif
    }
#ifdef WIN32
    if(name[len - 1] != '\\'){
      set_renderlabel = 1;
      strcat(name, dirseparator);
    }
#else
    if(name[len - 1] != '/'){
      set_renderlabel = 1;
      strcat(name, dirseparator);
    }
#endif
    if(set_renderlabel == 1){
      EDIT_renderdir->set_text(script_renderdir);
    }
    break;
  case SCRIPT_RENDER:
    Keyboard('r', FROM_SMOKEVIEW);
    break;
  case SCRIPT_RENDER_SUFFIX:
  {
    char *suffix;

    TrimBack(script_renderfilesuffix);
    suffix = TrimFront(script_renderfilesuffix);
    strcpy(script_renderfile, "");
    if(strlen(suffix) > 0){
      strcpy(script_renderfile, fdsprefix);
      strcat(script_renderfile, "_");
      strcat(script_renderfile, suffix);
      strcpy(label, _("Render: "));
      strcat(label, script_renderfile);
    }
    else{
      strcpy(label, _("Render"));
    }
    BUTTON_script_render->set_name(label);
  }
  break;
  case SCRIPT_START:
    ScriptMenu(SCRIPT_START_RECORDING);
    break;
  case SCRIPT_STOP:
    ScriptMenu(SCRIPT_STOP_RECORDING);
    break;
  case SCRIPT_RUNSCRIPT:
    name = 5 + BUTTON_script_runscript->name;
    PRINTF("running script: %s\n", name);
    ScriptMenu(LIST_scriptlist->get_int_val());
    break;
  case SCRIPT_LIST:
    id = LIST_scriptlist->get_int_val();
    name = GetScriptFileName(id);
    if(name != NULL&&strlen(name) > 0){
      strcpy(label, _("Run:"));
      strcat(label, name);
      BUTTON_script_runscript->set_name(label);
    }
    break;
  case SCRIPT_SAVEINI:
    name = 5 + BUTTON_script_saveini->name;
    if(strlen(name) > 0){
      inifiledata *inifile;

      strcpy(script_filename, name);
      inifile = InsertIniFile(name);
      WriteIni(SCRIPT_INI, script_filename);
      if(inifile != NULL&&LIST_ini_list != NULL){
        LIST_ini_list->add_item(inifile->id, inifile->file);
      }
    }
    WriteIni(LOCAL_INI, NULL);
    break;
  case SCRIPT_LOADINI:
  {
    char *ini_filename;

    id = LIST_ini_list->get_int_val();
    ini_filename = GetIniFileName(id);
    if(ini_filename == NULL)break;
    if(strcmp(ini_filename, caseini_filename) == 0){
      ReadIni(NULL);
    }
    else if(id >= 0){
      char *script_filename2;

      if(strlen(ini_filename) == 0)break;
      script_filename2 = script_filename;
      strcpy(script_filename, ini_filename);
      windowresized = 0;
      ReadIni(script_filename2);
    }
    if(scriptoutstream != NULL){
      fprintf(scriptoutstream, "LOADINIFILE\n");
      fprintf(scriptoutstream, " %s\n", ini_filename);
    }
  }
  break;
  case SCRIPT_STEP:
    UpdateScriptStep();
    updatemenu = 1;
    break;
  case SCRIPT_EDIT_INI:
    strcpy(label, _("Save"));
    strcat(label, fdsprefix);
    TrimBack(script_inifile_suffix);
    if(strlen(script_inifile_suffix) > 0){
      strcat(label, "_");
      strcat(label, script_inifile_suffix);
    }
    strcat(label, ".ini");
    BUTTON_script_saveini->set_name(label);
    break;
  case SCRIPT_SETSUFFIX:
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ SliceBoundMenu ------------------------ */
#ifdef pp_NEWBOUND_DIALOG
void GenerateSliceBoundDialog(void){

  GLUI_Panel *PANEL_a=NULL, *PANEL_b=NULL, *PANEL_c, *PANEL_d = NULL, *PANEL_e = NULL;

  ROLLOUT_slice_bound = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _("Bound data"), false, 0, SliceRolloutCB);
  INSERT_ROLLOUT(ROLLOUT_slice_bound, glui_bounds);
  ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slice_bound, 0, glui_bounds);

  PANEL_a = glui_bounds->add_panel_to_panel(ROLLOUT_slice_bound, "", GLUI_PANEL_NONE);

  EDIT_slice_min = glui_bounds->add_edittext_to_panel(PANEL_a, "", GLUI_EDITTEXT_FLOAT, &glui_slicemin, VALMIN, SliceBoundCB);
  glui_bounds->add_column_to_panel(PANEL_a, false);

  STATIC_slice_min_unit = glui_bounds->add_statictext_to_panel(PANEL_a, "xx");
  STATIC_slice_min_unit->set_w(10);

  STATIC_slice_min = glui_bounds->add_statictext_to_panel(PANEL_a, "min");
  STATIC_slice_min->set_w(4);

  PANEL_b = glui_bounds->add_panel_to_panel(ROLLOUT_slice_bound, "", GLUI_PANEL_NONE);

  EDIT_slice_max = glui_bounds->add_edittext_to_panel(PANEL_b, "", GLUI_EDITTEXT_FLOAT, &glui_slicemax, VALMAX, SliceBoundCB);
  glui_bounds->add_column_to_panel(PANEL_b, false);

  STATIC_slice_max_unit = glui_bounds->add_statictext_to_panel(PANEL_b, "yy");
  STATIC_slice_max_unit->set_w(10);

  STATIC_slice_max = glui_bounds->add_statictext_to_panel(PANEL_b, "max");
  STATIC_slice_max->set_w(4);

  PANEL_c = glui_bounds->add_panel_to_panel(ROLLOUT_slice_bound, "Set/Show Bounds");

  BUTTON_slice_percentile_bounds = glui_bounds->add_button_to_panel(PANEL_c, _("Percentile"), PERCENTILE_BOUNDS_LOADED, SliceBoundCB);
  BUTTON_slice_global_bounds = glui_bounds->add_button_to_panel(PANEL_c, _("Global"), GLOBAL_BOUNDS, SliceBoundCB);

  RADIO_slice_loaded_only = glui_bounds->add_radiogroup_to_panel(PANEL_c,  &slice_loaded_only, SLICE_LOADED_ONLY, SliceBoundCB);
  glui_bounds->add_radiobutton_to_group(RADIO_slice_loaded_only, "all");
  glui_bounds->add_radiobutton_to_group(RADIO_slice_loaded_only, "loaded");
  SliceBoundCB(SLICE_LOADED_ONLY);

  glui_bounds->add_button_to_panel(ROLLOUT_slice_bound, _("Update"), FILEUPDATE, SliceBoundCB);

  ROLLOUT_slice_chop = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _("Truncate data"), false, 1, SliceRolloutCB);
  INSERT_ROLLOUT(ROLLOUT_slice_chop, glui_bounds);
  ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slice_chop, 1, glui_bounds);

  PANEL_d = glui_bounds->add_panel_to_panel(ROLLOUT_slice_chop, "", GLUI_PANEL_NONE);

  EDIT_slice_chopmin = glui_bounds->add_edittext_to_panel(PANEL_d, "", GLUI_EDITTEXT_FLOAT, &glui_slicechopmin, CHOPVALMIN, SliceBoundCB);
  glui_bounds->add_column_to_panel(PANEL_d, false);

  STATIC_slice_cmin_unit = glui_bounds->add_statictext_to_panel(PANEL_d, "xx");
  STATIC_slice_cmin_unit->set_w(10);
  glui_bounds->add_column_to_panel(PANEL_d, false);
  CHECKBOX_slice_setchopmin = glui_bounds->add_checkbox_to_panel(PANEL_d, _("Below"), &glui_setslicechopmin, SETCHOPMINVAL, SliceBoundCB);

  PANEL_e = glui_bounds->add_panel_to_panel(ROLLOUT_slice_chop, "", GLUI_PANEL_NONE);

  EDIT_slice_chopmax = glui_bounds->add_edittext_to_panel(PANEL_e, "", GLUI_EDITTEXT_FLOAT, &glui_slicechopmax, CHOPVALMAX, SliceBoundCB);
  glui_bounds->add_column_to_panel(PANEL_e, false);

  STATIC_slice_cmax_unit = glui_bounds->add_statictext_to_panel(PANEL_e, "xx");
  glui_bounds->add_column_to_panel(PANEL_e, false);
  STATIC_slice_cmax_unit->set_w(10);
  CHECKBOX_slice_setchopmax = glui_bounds->add_checkbox_to_panel(PANEL_e, _("Above"), &glui_setslicechopmax, SETCHOPMAXVAL, SliceBoundCB);
}
#endif

/* ------------------ BoundMenu ------------------------ */

void GenerateBoundDialogs(GLUI_Rollout **bound_rollout, GLUI_Rollout **chop_rollout, GLUI_Panel *PANEL_panel, char *button_title,
  GLUI_EditText **EDIT_con_min, GLUI_EditText **EDIT_con_max,
  GLUI_RadioGroup **RADIO_con_setmin, GLUI_RadioGroup **RADIO_con_setmax,
  GLUI_RadioButton **RADIO_CON_setmin_percentile, GLUI_RadioButton **RADIO_CON_setmax_percentile,
  GLUI_Checkbox **CHECKBOX_con_setchopmin, GLUI_Checkbox **CHECKBOX_con_setchopmax,
  GLUI_EditText **EDIT_con_chopmin, GLUI_EditText **EDIT_con_chopmax,
  GLUI_StaticText **STATIC_con_min_unit, GLUI_StaticText **STATIC_con_max_unit,
  GLUI_StaticText **STATIC_con_cmin_unit, GLUI_StaticText **STATIC_con_cmax_unit,
  GLUI_Button **BUTTON_update, GLUI_Button **BUTTON_reload,
  GLUI_Panel **PANEL_bound,

  int *setminval, int *setmaxval,
  float *minval, float *maxval,
  int *setchopminval, int *setchopmaxval,
  float *chopminval, float *chopmaxval,
  int updatebounds,
  int truncatebounds,
  GLUI_Update_CB FILE_CB,

  GLUI_Update_CB PROC_CB, procdata *procinfo, int *nprocinfo){

  GLUI_RadioButton *percentile_min, *percentile_max;
  GLUI_Panel *PANEL_a, *PANEL_b, *PANEL_c;
  GLUI_Rollout *PANEL_e = NULL, *PANEL_g = NULL;
  GLUI_Panel *PANEL_f = NULL, *PANEL_h = NULL;

  PANEL_g = glui_bounds->add_rollout_to_panel(PANEL_panel, _("Bound data"), false, 0, PROC_CB);
  if(PANEL_bound!=NULL)*PANEL_bound = PANEL_g;
  INSERT_ROLLOUT(PANEL_g, glui_bounds);
  if(bound_rollout!=NULL){
    *bound_rollout = PANEL_g;
    ADDPROCINFO(procinfo, *nprocinfo, PANEL_g, 0, glui_bounds);
  }

  PANEL_a = glui_bounds->add_panel_to_panel(PANEL_g, "", GLUI_PANEL_NONE);

  *EDIT_con_min = glui_bounds->add_edittext_to_panel(PANEL_a, "", GLUI_EDITTEXT_FLOAT, minval, VALMIN, FILE_CB);
  if(*setminval==0){
    (*EDIT_con_min)->disable();
  }
  glui_bounds->add_column_to_panel(PANEL_a, false);

  if(STATIC_con_min_unit!=NULL){
    *STATIC_con_min_unit = glui_bounds->add_statictext_to_panel(PANEL_a, "xx");
    glui_bounds->add_column_to_panel(PANEL_a, false);
    (*STATIC_con_min_unit)->set_w(10);
  }

  *RADIO_con_setmin = glui_bounds->add_radiogroup_to_panel(PANEL_a, setminval, SETVALMIN, FILE_CB);
  percentile_min = glui_bounds->add_radiobutton_to_group(*RADIO_con_setmin, _("percentile min"));
  if(RADIO_CON_setmin_percentile!=NULL)*RADIO_CON_setmin_percentile = percentile_min;
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmin, _("set min"));
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmin, _("global min"));

  PANEL_b = glui_bounds->add_panel_to_panel(PANEL_g, "", GLUI_PANEL_NONE);

  *EDIT_con_max = glui_bounds->add_edittext_to_panel(PANEL_b, "", GLUI_EDITTEXT_FLOAT, maxval, VALMAX, FILE_CB);
  if(*setminval==0){
    (*EDIT_con_max)->disable();
  }
  glui_bounds->add_column_to_panel(PANEL_b, false);

  if(STATIC_con_max_unit!=NULL){
    *STATIC_con_max_unit = glui_bounds->add_statictext_to_panel(PANEL_b, "yy");
    glui_bounds->add_column_to_panel(PANEL_b, false);
    (*STATIC_con_max_unit)->set_w(10);
  }

  *RADIO_con_setmax = glui_bounds->add_radiogroup_to_panel(PANEL_b, setmaxval, SETVALMAX, FILE_CB);
  percentile_max = glui_bounds->add_radiobutton_to_group(*RADIO_con_setmax, _("percentile max"));
  if(RADIO_CON_setmax_percentile!=NULL)*RADIO_CON_setmax_percentile = percentile_max;
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmax, _("set max"));
  glui_bounds->add_radiobutton_to_group(*RADIO_con_setmax, _("global max"));

  PANEL_c = glui_bounds->add_panel_to_panel(PANEL_g, "", GLUI_PANEL_NONE);

  if(updatebounds==UPDATE_BOUNDS){
    glui_bounds->add_button_to_panel(PANEL_c, _("Update"), FILEUPDATE, FILE_CB);
  }
  else if(updatebounds==RELOAD_BOUNDS){
    glui_bounds->add_button_to_panel(PANEL_c, button_title, FILERELOAD, FILE_CB);
  }
  else{
    BUTTON_updatebound = glui_bounds->add_button_to_panel(PANEL_c, _("Update using cached data"), FILEUPDATEDATA, FILE_CB);
    BUTTON_reloadbound = glui_bounds->add_button_to_panel(PANEL_c, button_title, FILERELOAD, FILE_CB);
  }

  if(EDIT_con_chopmin!=NULL&&EDIT_con_chopmax!=NULL&&CHECKBOX_con_setchopmin!=NULL&&CHECKBOX_con_setchopmax!=NULL){
    PANEL_e = glui_bounds->add_rollout_to_panel(PANEL_panel, _("Truncate data"), false, 1, PROC_CB);
    INSERT_ROLLOUT(PANEL_e, glui_bounds);
    if(chop_rollout!=NULL){
      *chop_rollout = PANEL_e;
      ADDPROCINFO(procinfo, *nprocinfo, PANEL_e, 1, glui_bounds);
    }

    PANEL_f = glui_bounds->add_panel_to_panel(PANEL_e, "", GLUI_PANEL_NONE);

    *EDIT_con_chopmin = glui_bounds->add_edittext_to_panel(PANEL_f, "", GLUI_EDITTEXT_FLOAT, chopminval, CHOPVALMIN, FILE_CB);
    glui_bounds->add_column_to_panel(PANEL_f, false);

    if(STATIC_con_cmin_unit!=NULL){
      *STATIC_con_cmin_unit = glui_bounds->add_statictext_to_panel(PANEL_f, "xx");
      (*STATIC_con_cmin_unit)->set_w(10);
      glui_bounds->add_column_to_panel(PANEL_f, false);
    }
    *CHECKBOX_con_setchopmin = glui_bounds->add_checkbox_to_panel(PANEL_f, _("Below"), setchopminval, SETCHOPMINVAL, FILE_CB);

    PANEL_h = glui_bounds->add_panel_to_panel(PANEL_e, "", GLUI_PANEL_NONE);

    *EDIT_con_chopmax = glui_bounds->add_edittext_to_panel(PANEL_h, "", GLUI_EDITTEXT_FLOAT, chopmaxval, CHOPVALMAX, FILE_CB);
    glui_bounds->add_column_to_panel(PANEL_h, false);

    if(STATIC_con_cmax_unit!=NULL){
      *STATIC_con_cmax_unit = glui_bounds->add_statictext_to_panel(PANEL_h, "xx");
      glui_bounds->add_column_to_panel(PANEL_h, false);
      (*STATIC_con_cmax_unit)->set_w(10);
    }
    *CHECKBOX_con_setchopmax = glui_bounds->add_checkbox_to_panel(PANEL_h, _("Above"), setchopmaxval, SETCHOPMAXVAL, FILE_CB);

    if(truncatebounds==TRUNCATE_BOUNDS){
      glui_bounds->add_button_to_panel(PANEL_e, _("Update"), CHOPUPDATE, FILE_CB);
    }
  }
}

/* ------------------ GluiBoundsSetup ------------------------ */

extern "C" void GluiBoundsSetup(int main_window){
  int i;
  int nradio;
  int have_part, have_evac;

  update_glui_bounds=0;
  if(glui_bounds!=NULL){
    glui_bounds->close();
    glui_bounds=NULL;
  }
  overwrite_all=0;
  glui_bounds = GLUI_Master.create_glui( "Files/Bounds",0,0,0 );
  glui_bounds->hide();

  PANEL_files = glui_bounds->add_panel("Files", true);

  ROLLOUT_autoload = glui_bounds->add_rollout_to_panel(PANEL_files,_("Auto load"), false, LOAD_ROLLOUT, FileRolloutCB);
  INSERT_ROLLOUT(ROLLOUT_autoload, glui_bounds);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_autoload, LOAD_ROLLOUT, glui_bounds);

  glui_bounds->add_checkbox_to_panel(ROLLOUT_autoload, _("Auto load at startup"),
    &loadfiles_at_startup, STARTUP, BoundBoundCB);
  glui_bounds->add_button_to_panel(ROLLOUT_autoload, _("Save auto load file list"), SAVE_FILE_LIST, BoundBoundCB);
  glui_bounds->add_button_to_panel(ROLLOUT_autoload, _("Auto load now"), LOAD_FILES, BoundBoundCB);

  // -------------- Show/Hide Loaded files -------------------

  if(npartinfo > 0 || nsliceinfo > 0 || nvsliceinfo > 0 || nisoinfo > 0 || npatchinfo || nsmoke3dinfo > 0 || nplot3dinfo > 0){
    ROLLOUT_showhide = glui_bounds->add_rollout_to_panel(PANEL_files,_("Show/Hide"), false, SHOWHIDE_ROLLOUT, FileRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_showhide, glui_bounds);
    ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_showhide, SHOWHIDE_ROLLOUT, glui_bounds);

    RADIO_showhide = glui_bounds->add_radiogroup_to_panel(ROLLOUT_showhide, &showhide_option);
    glui_bounds->add_radiobutton_to_group(RADIO_showhide, _("Show"));
    glui_bounds->add_radiobutton_to_group(RADIO_showhide, _("Show only"));
    glui_bounds->add_radiobutton_to_group(RADIO_showhide, _("Hide"));

    glui_bounds->add_column_to_panel(ROLLOUT_showhide, false);

    if(nevac > 0){}
    if(npartinfo > 0 && nevac != npartinfo)BUTTON_PART = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Particle", FILESHOW_particle, FileShowCB);
    if(nevac > 0)BUTTON_EVAC = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Evacuation", FILESHOW_evac, FileShowCB);
    if(nsliceinfo > 0)BUTTON_SLICE = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Slice", FILESHOW_slice, FileShowCB);
    if(nvsliceinfo > 0)BUTTON_VSLICE = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Vector", FILESHOW_vslice, FileShowCB);
    if(nisoinfo > 0)BUTTON_ISO = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Isosurface", FILESHOW_isosurface, FileShowCB);
    if(npatchinfo > 0)BUTTON_BOUNDARY = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Boundary", FILESHOW_boundary, FileShowCB);
    if(nsmoke3dinfo > 0)BUTTON_3DSMOKE = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "3D smoke/fire", FILESHOW_3dsmoke, FileShowCB);
    if(nplot3dinfo > 0)BUTTON_PLOT3D = glui_bounds->add_button_to_panel(ROLLOUT_showhide, "Plot3D", FILESHOW_plot3d, FileShowCB);
    glui_bounds->add_button_to_panel(ROLLOUT_showhide, "File Sizes", FILESHOW_sizes, FileShowCB);


    UpdateShowHideButtons();
  }


#ifdef pp_COMPRESS
  if(smokezippath != NULL && (npatchinfo > 0 || nsmoke3dinfo > 0 || nsliceinfo > 0)){
    ROLLOUT_compress = glui_bounds->add_rollout_to_panel(PANEL_files,_("Compress"), false, COMPRESS_ROLLOUT, FileRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_compress, glui_bounds);
    ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_compress, COMPRESS_ROLLOUT, glui_bounds);

    CHECKBOX_erase_all = glui_bounds->add_checkbox_to_panel(ROLLOUT_compress, _("Erase compressed files"),
      &erase_all, ERASE, BoundBoundCB);
    CHECKBOX_overwrite_all = glui_bounds->add_checkbox_to_panel(ROLLOUT_compress, _("Overwrite compressed files"),
      &overwrite_all, OVERWRITE, BoundBoundCB);
    CHECKBOX_compress_autoloaded = glui_bounds->add_checkbox_to_panel(ROLLOUT_compress, _("Compress only autoloaded files"),
      &compress_autoloaded, COMPRESS_AUTOLOADED, BoundBoundCB);
    if(nsliceinfo > 0){
      SPINNER_slicezipstep = glui_bounds->add_spinner_to_panel(ROLLOUT_compress, _("Slice frame Skip"), GLUI_SPINNER_INT, &slicezipskip,
        FRAMELOADING, SliceBoundCB);
      SPINNER_slicezipstep->set_int_limits(0, 100);
    }
    if(nisoinfo > 0){
      SPINNER_isozipstep = glui_bounds->add_spinner_to_panel(ROLLOUT_compress, _("Compressed file frame skip"), GLUI_SPINNER_INT, &isozipskip,
        FRAMELOADING, IsoBoundCB);
      SPINNER_isozipstep->set_int_limits(0, 100);
    }
    if(nsmoke3dinfo > 0){
      SPINNER_smoke3dzipstep = glui_bounds->add_spinner_to_panel(ROLLOUT_compress, _("3D smoke frame skip"), GLUI_SPINNER_INT, &smoke3dzipskip,
        FRAMELOADING, Smoke3dBoundCB);
      SPINNER_smoke3dzipstep->set_int_limits(0, 100);
    }
    if(npatchinfo > 0){
      SPINNER_boundzipstep = glui_bounds->add_spinner_to_panel(ROLLOUT_compress, _("Boundary file frame skip"),
        GLUI_SPINNER_INT, &boundzipskip, FRAMELOADING, BoundBoundCB);
      SPINNER_boundzipstep->set_int_limits(0, 100);
    }
    BUTTON_compress = glui_bounds->add_button_to_panel(ROLLOUT_compress, _("Run smokezip"), COMPRESS_FILES, BoundBoundCB);
  }
#endif

  ROLLOUT_script = glui_bounds->add_rollout_to_panel(PANEL_files,_("Scripts"), false, SCRIPT_ROLLOUT, FileRolloutCB);
  INSERT_ROLLOUT(ROLLOUT_script, glui_bounds);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_script, SCRIPT_ROLLOUT, glui_bounds);

  PANEL_script1 = glui_bounds->add_panel_to_panel(ROLLOUT_script, _("Script files"), false);
  PANEL_record = glui_bounds->add_panel_to_panel(PANEL_script1, _("Record"), true);

  PANEL_script1a = glui_bounds->add_panel_to_panel(PANEL_record, "", false);
  BUTTON_script_start = glui_bounds->add_button_to_panel(PANEL_script1a, _("Start"), SCRIPT_START, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script1a, false);
  BUTTON_script_stop = glui_bounds->add_button_to_panel(PANEL_script1a, _("Stop"), SCRIPT_STOP, ScriptCB);
  BUTTON_script_stop->disable();

  PANEL_run = glui_bounds->add_panel_to_panel(PANEL_script1, _("Run"), true);
  PANEL_script1b = glui_bounds->add_panel_to_panel(PANEL_run, "", false);
  BUTTON_script_runscript = glui_bounds->add_button_to_panel(PANEL_script1b, _("Run script"), SCRIPT_RUNSCRIPT, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script1b, false);
  CHECKBOX_script_step = glui_bounds->add_checkbox_to_panel(PANEL_run, _("Step through script"), &script_step, SCRIPT_STEP, ScriptCB);
  BUTTON_step = glui_bounds->add_button_to_panel(PANEL_run, _("Next"), SCRIPT_STEP_NOW, ScriptCB);
  UpdateScriptStep();
  glui_bounds->add_button_to_panel(PANEL_run, _("Cancel script"), SCRIPT_CANCEL_NOW, ScriptCB);

  LIST_scriptlist = glui_bounds->add_listbox_to_panel(PANEL_script1b, _("Select:"), &script_index, SCRIPT_LIST, ScriptCB);
  {
    scriptfiledata *scriptfile;

    for(scriptfile = first_scriptfile.next; scriptfile->next != NULL; scriptfile = scriptfile->next){
      char *file;
      int len;

      file = scriptfile->file;
      if(file == NULL)continue;
      if(FILE_EXISTS(file) == NO)continue;
      len = strlen(file);
      if(len <= 0)continue;

      LIST_scriptlist->add_item(scriptfile->id, file);
    }
    ScriptCB(SCRIPT_LIST);
  }

  ROLLOUT_config = glui_bounds->add_rollout_to_panel(PANEL_files, "Config", false, CONFIG_ROLLOUT, FileRolloutCB);
  INSERT_ROLLOUT(ROLLOUT_config, glui_bounds);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_config, CONFIG_ROLLOUT, glui_bounds);

  PANEL_script2a = glui_bounds->add_panel_to_panel(ROLLOUT_config, "", false);
  EDIT_ini = glui_bounds->add_edittext_to_panel(PANEL_script2a, "suffix:", GLUI_EDITTEXT_TEXT, script_inifile_suffix, SCRIPT_EDIT_INI, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script2a, false);
  BUTTON_script_setsuffix = glui_bounds->add_button_to_panel(PANEL_script2a, _("Set"), SCRIPT_SETSUFFIX, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script2a, false);
  BUTTON_script_saveini = glui_bounds->add_button_to_panel(PANEL_script2a, _("Save:"), SCRIPT_SAVEINI, ScriptCB);
  ScriptCB(SCRIPT_EDIT_INI);

  PANEL_script2b = glui_bounds->add_panel_to_panel(ROLLOUT_config, "", false);
  ini_index = -2;
  LIST_ini_list = glui_bounds->add_listbox_to_panel(PANEL_script2b, _("Select:"), &ini_index);
  {
    inifiledata *inifile;

    for(inifile = first_inifile.next; inifile->next != NULL; inifile = inifile->next){
      if(inifile->file != NULL&&FILE_EXISTS(inifile->file) == YES){
        if(ini_index == -2)ini_index = inifile->id;
        LIST_ini_list->add_item(inifile->id, inifile->file);
      }
    }
  }
  glui_bounds->add_column_to_panel(PANEL_script2b, false);
  BUTTON_ini_load = glui_bounds->add_button_to_panel(PANEL_script2b, _("Load"), SCRIPT_LOADINI, ScriptCB);

  PANEL_script3 = glui_bounds->add_panel_to_panel(ROLLOUT_script, _("Render"), true);
  EDIT_renderdir = glui_bounds->add_edittext_to_panel(PANEL_script3, _("directory:"),
    GLUI_EDITTEXT_TEXT, script_renderdir, SCRIPT_RENDER_DIR, ScriptCB);
  EDIT_renderdir->set_w(260);
  PANEL_script1c = glui_bounds->add_panel_to_panel(PANEL_script3, "", false);
  BUTTON_script_render = glui_bounds->add_button_to_panel(PANEL_script1c, _("Render"), SCRIPT_RENDER, ScriptCB);
  glui_bounds->add_column_to_panel(PANEL_script1c, false);
  EDIT_rendersuffix = glui_bounds->add_edittext_to_panel(PANEL_script1c, _("suffix:"),
    GLUI_EDITTEXT_TEXT, script_renderfilesuffix, SCRIPT_RENDER_SUFFIX, ScriptCB);
  EDIT_rendersuffix->set_w(130);
  ScriptCB(SCRIPT_RENDER_SUFFIX);

// ----------------------------------- Bounds ----------------------------------------

  PANEL_bounds = glui_bounds->add_panel("Bounds",true);
  ROLLOUT_filebounds = glui_bounds->add_rollout_to_panel(PANEL_bounds,_("Data"), false, FILEBOUNDS_ROLLOUT, FileRolloutCB);
  INSERT_ROLLOUT(ROLLOUT_filebounds, glui_bounds);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_filebounds, FILEBOUNDS_ROLLOUT, glui_bounds);

  /*  zone (cfast) */

  if(nzoneinfo>0){
    ROLLOUT_zone_bound = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,_("Zone/slice temperatures"),false,ZONE_ROLLOUT,BoundRolloutCB);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_zone_bound, ZONE_ROLLOUT, glui_bounds);

    PANEL_zone_a = glui_bounds->add_panel_to_panel(ROLLOUT_zone_bound,"",GLUI_PANEL_NONE);

    EDIT_zone_min = glui_bounds->add_edittext_to_panel(PANEL_zone_a,"",GLUI_EDITTEXT_FLOAT,&zonemin,ZONEVALMINMAX,SliceBoundCB);
    if(setzonemin==0){
      EDIT_zone_min->disable();
      if(EDIT_slice_min!=NULL)EDIT_slice_min->disable();
    }
    else{
      EDIT_zone_min->enable();
      if(EDIT_slice_min!=NULL)EDIT_slice_min->enable();
    }
    glui_bounds->add_column_to_panel(PANEL_zone_a,false);

    RADIO_zone_setmin = glui_bounds->add_radiogroup_to_panel(PANEL_zone_a,&setzonemin,SETZONEVALMINMAX,SliceBoundCB);
    RADIOBUTTON_zone_permin=glui_bounds->add_radiobutton_to_group(RADIO_zone_setmin,_("percentile min"));
    glui_bounds->add_radiobutton_to_group(RADIO_zone_setmin,_("set min"));
    glui_bounds->add_radiobutton_to_group(RADIO_zone_setmin,_("global min"));

    PANEL_zone_b = glui_bounds->add_panel_to_panel(ROLLOUT_zone_bound,"",GLUI_PANEL_NONE);

    EDIT_zone_max = glui_bounds->add_edittext_to_panel(PANEL_zone_b,"",GLUI_EDITTEXT_FLOAT,&zonemax,ZONEVALMINMAX,SliceBoundCB);
    if(setzonemax==0){
      EDIT_zone_max->disable();
      if(EDIT_slice_max!=NULL)EDIT_slice_max->disable();
    }
    else{
      EDIT_zone_max->enable();
      if(EDIT_slice_max!=NULL)EDIT_slice_max->enable();
    }
    glui_bounds->add_column_to_panel(PANEL_zone_b,false);

    RADIO_zone_setmax = glui_bounds->add_radiogroup_to_panel(PANEL_zone_b,&setzonemax,SETZONEVALMINMAX,SliceBoundCB);
    RADIOBUTTON_zone_permax=glui_bounds->add_radiobutton_to_group(RADIO_zone_setmax,_("percentile max"));
    glui_bounds->add_radiobutton_to_group(RADIO_zone_setmax,_("set max"));
    glui_bounds->add_radiobutton_to_group(RADIO_zone_setmax,_("global max"));

    RADIOBUTTON_zone_permin->disable();
    RADIOBUTTON_zone_permax->disable();
    SliceBoundCB(SETZONEVALMINMAX);
  }

  // ----------------------------------- 3D smoke ----------------------------------------

  if(nsmoke3dinfo>0||nvolrenderinfo>0){
    ROLLOUT_smoke3d = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,_("3D smoke"),false,SMOKE3D_ROLLOUT,BoundRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_smoke3d, glui_bounds);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_smoke3d, SMOKE3D_ROLLOUT, glui_bounds);
  }

  // ----------------------------------- Boundary ----------------------------------------

  if(npatchinfo>0){
    glui_active=1;
    ROLLOUT_bound = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,_("Boundary"),false,BOUNDARY_ROLLOUT,BoundRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_bound, glui_bounds);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_bound, BOUNDARY_ROLLOUT, glui_bounds);

    nradio=0;
    for(i=0;i<npatchinfo;i++){
      patchdata *patchi;

      patchi = patchinfo + i;
      if(patchi->firstshort==1)nradio++;
    }

    if(nradio>1){
      RADIO_bf = glui_bounds->add_radiogroup_to_panel(ROLLOUT_bound, &list_patch_index, FILETYPEINDEX, BoundBoundCB);
      for(i=0;i<npatchinfo;i++){
        patchdata *patchi;

        patchi = patchinfo + i;
        if(patchi->firstshort==1)glui_bounds->add_radiobutton_to_group(RADIO_bf,patchi->label.shortlabel);
      }
#ifdef pp_FSEEK
      CHECKBOX_boundary_load_incremental=glui_bounds->add_checkbox_to_panel(ROLLOUT_bound, _("incremental data loading"), &load_incremental, BOUNDARY_LOAD_INCREMENTAL, LoadIncrementalCB);
      LoadIncrementalCB(BOUNDARY_LOAD_INCREMENTAL);
#endif
      glui_bounds->add_column_to_panel(ROLLOUT_bound,false);
    }

    GenerateBoundDialogs(&ROLLOUT_boundary_bound,&ROLLOUT_boundary_chop,ROLLOUT_bound,_("Reload Boundary File(s)"),
      &EDIT_patch_min,&EDIT_patch_max,&RADIO_patch_setmin,&RADIO_patch_setmax,NULL,NULL,
      &CHECKBOX_patch_setchopmin, &CHECKBOX_patch_setchopmax,
      &EDIT_patch_chopmin, &EDIT_patch_chopmax,
      &STATIC_bound_min_unit,&STATIC_bound_max_unit,
      &STATIC_bound_cmin_unit,&STATIC_bound_cmax_unit,
      &BUTTON_updatebound, &BUTTON_reloadbound,
      NULL,
      &setpatchmin,&setpatchmax,&patchmin,&patchmax,
      &setpatchchopmin, &setpatchchopmax,
      &patchchopmin, &patchchopmax,
      UPDATERELOAD_BOUNDS,DONT_TRUNCATE_BOUNDS,
      BoundBoundCB,
      SubBoundRolloutCB,subboundprocinfo,&nsubboundprocinfo);

    UpdateBoundaryListIndex2(patchinfo->label.shortlabel);
    UpdateHideBoundarySurface();
    BoundBoundCB(CACHE_BOUNDARYDATA);

    ROLLOUT_outputpatchdata = glui_bounds->add_rollout_to_panel(ROLLOUT_bound,_("Output data"),false,
             BOUNDARY_OUTPUT_ROLLOUT,SubBoundRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_outputpatchdata, glui_bounds);
    ADDPROCINFO(subboundprocinfo, nsubboundprocinfo, ROLLOUT_outputpatchdata, BOUNDARY_OUTPUT_ROLLOUT, glui_bounds);

    glui_bounds->add_checkbox_to_panel(ROLLOUT_outputpatchdata,_("Output data to file"),&output_patchdata);

    PANEL_outputpatchdata = glui_bounds->add_panel_to_panel(ROLLOUT_outputpatchdata,"",GLUI_PANEL_NONE);

    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"tmin",GLUI_SPINNER_FLOAT,&patchout_tmin);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"xmin",GLUI_SPINNER_FLOAT,&patchout_xmin);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"ymin",GLUI_SPINNER_FLOAT,&patchout_ymin);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"zmin",GLUI_SPINNER_FLOAT,&patchout_zmin);

    glui_bounds->add_column_to_panel(PANEL_outputpatchdata,false);

    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"tmax",GLUI_SPINNER_FLOAT,&patchout_tmax);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"xmax",GLUI_SPINNER_FLOAT,&patchout_xmax);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"ymax",GLUI_SPINNER_FLOAT,&patchout_ymax);
    glui_bounds->add_spinner_to_panel(PANEL_outputpatchdata,"zmax",GLUI_SPINNER_FLOAT,&patchout_zmax);

    if(activate_threshold==1){
      ROLLOUT_boundary_temp_threshold = glui_bounds->add_rollout_to_panel(ROLLOUT_bound,_("Temperature threshold"),false,BOUNDARY_THRESHOLD_ROLLOUT,SubBoundRolloutCB);
      INSERT_ROLLOUT(ROLLOUT_boundary_temp_threshold, glui_bounds);
      ADDPROCINFO(subboundprocinfo, nsubboundprocinfo, ROLLOUT_boundary_temp_threshold, BOUNDARY_THRESHOLD_ROLLOUT, glui_bounds);

      CHECKBOX_showchar=glui_bounds->add_checkbox_to_panel(ROLLOUT_boundary_temp_threshold,_("Show"),&vis_threshold,SHOWCHAR,BoundBoundCB);
      CHECKBOX_showonlychar=glui_bounds->add_checkbox_to_panel(ROLLOUT_boundary_temp_threshold,_("Show only threshold"),&vis_onlythreshold,SHOWCHAR,BoundBoundCB);
      {
        char label[256];

        strcpy(label,"Temperature (");
        strcat(label,degC);
        strcat(label,") ");
        glui_bounds->add_spinner_to_panel(ROLLOUT_boundary_temp_threshold,label,GLUI_SPINNER_FLOAT,&temp_threshold);
      }
      BoundBoundCB(SHOWCHAR);
    }

    ROLLOUT_boundary_settings = glui_bounds->add_rollout_to_panel(ROLLOUT_bound, _("Settings"),false, BOUNDARY_SETTINGS_ROLLOUT, SubBoundRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_boundary_settings, glui_bounds);
    ADDPROCINFO(subboundprocinfo, nsubboundprocinfo, ROLLOUT_boundary_settings, BOUNDARY_SETTINGS_ROLLOUT, glui_bounds);

    if(ngeom_data > 0){
      glui_bounds->add_checkbox_to_panel(ROLLOUT_boundary_settings, _("shaded"), &show_boundary_shaded);
      CHECKBOX_show_boundary_outline=glui_bounds->add_checkbox_to_panel(ROLLOUT_boundary_settings, _("outline"), &show_boundary_outline, SHOW_BOUNDARY_OUTLINE, BoundBoundCB);
      glui_bounds->add_checkbox_to_panel(ROLLOUT_boundary_settings, _("points"), &show_boundary_points);

      PANEL_boundary_outline_type = glui_bounds->add_panel_to_panel(ROLLOUT_boundary_settings,"outline type");
      RADIO_boundary_edgetype = glui_bounds->add_radiogroup_to_panel(PANEL_boundary_outline_type, &boundary_edgetype, BOUNDARY_EDGETYPE, BoundBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_boundary_edgetype, _("polygon"));
      glui_bounds->add_radiobutton_to_group(RADIO_boundary_edgetype, _("triangle"));
      glui_bounds->add_radiobutton_to_group(RADIO_boundary_edgetype, _("none"));
      BoundBoundCB(BOUNDARY_EDGETYPE);
      BoundBoundCB(SHOW_BOUNDARY_OUTLINE);

      PANEL_geomexp = glui_bounds->add_panel_to_panel(ROLLOUT_boundary_settings,"experimental");
      glui_bounds->add_checkbox_to_panel(PANEL_geomexp, _("smooth normals"), &geomdata_smoothnormals);
      glui_bounds->add_checkbox_to_panel(PANEL_geomexp, _("smooth color/data"), &geomdata_smoothcolors);
      glui_bounds->add_checkbox_to_panel(PANEL_geomexp, _("lighting"), &geomdata_lighting);

      glui_bounds->add_spinner_to_panel(ROLLOUT_boundary_settings, "line width", GLUI_SPINNER_FLOAT, &geomboundary_linewidth);
      glui_bounds->add_spinner_to_panel(ROLLOUT_boundary_settings, "point size", GLUI_SPINNER_FLOAT, &geomboundary_pointsize);
      glui_bounds->add_separator_to_panel(ROLLOUT_boundary_settings);
    }
    CHECKBOX_cache_boundarydata = glui_bounds->add_checkbox_to_panel(ROLLOUT_boundary_settings, _("Cache boundary data"), &cache_boundarydata, CACHE_BOUNDARYDATA, BoundBoundCB);
    CHECKBOX_showpatch_both = glui_bounds->add_checkbox_to_panel(ROLLOUT_boundary_settings, _("Display exterior data"), &showpatch_both, SHOWPATCH_BOTH, BoundBoundCB);


    if(nboundaryslicedups > 0){
      ROLLOUT_boundary_duplicates = glui_bounds->add_rollout_to_panel(ROLLOUT_bound, "Duplicates", false,BOUNDARY_DUPLICATE_ROLLOUT,SubBoundRolloutCB);
      INSERT_ROLLOUT(ROLLOUT_boundary_duplicates, glui_bounds);
      ADDPROCINFO(subboundprocinfo, nsubboundprocinfo, ROLLOUT_boundary_duplicates, BOUNDARY_DUPLICATE_ROLLOUT, glui_bounds);

      RADIO_boundaryslicedup = glui_bounds->add_radiogroup_to_panel(ROLLOUT_boundary_duplicates, &boundaryslicedup_option,UPDATE_BOUNDARYSLICEDUPS,BoundBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_boundaryslicedup, _("Keep all"));
      glui_bounds->add_radiobutton_to_group(RADIO_boundaryslicedup, _("Keep fine"));
      glui_bounds->add_radiobutton_to_group(RADIO_boundaryslicedup, _("Keep coarse"));
    }
  }

  // ----------------------------------- Isosurface ----------------------------------------

  if(nisoinfo>0){
    ROLLOUT_iso = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds, "Isosurface", false, ISO_ROLLOUT, BoundRolloutCB);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_iso, ISO_ROLLOUT, glui_bounds);

    if(niso_bounds>0){
      ROLLOUT_iso_bounds = glui_bounds->add_rollout_to_panel(ROLLOUT_iso, "Bound data", true, ISO_ROLLOUT_BOUNDS, IsoRolloutCB);
      INSERT_ROLLOUT(ROLLOUT_iso_bounds, glui_bounds);
      ADDPROCINFO(isoprocinfo, nisoprocinfo, ROLLOUT_iso_bounds, ISO_ROLLOUT_BOUNDS, glui_bounds);

      PANEL_iso1 = glui_bounds->add_panel_to_panel(ROLLOUT_iso_bounds, "", GLUI_PANEL_NONE);
      EDIT_iso_valmin = glui_bounds->add_edittext_to_panel(PANEL_iso1, "", GLUI_EDITTEXT_FLOAT, &glui_iso_valmin, ISO_VALMIN, IsoBoundCB);
      glui_bounds->add_column_to_panel(PANEL_iso1, false);
      RADIO_iso_setmin = glui_bounds->add_radiogroup_to_panel(PANEL_iso1, &setisomin, ISO_SETVALMIN, IsoBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_iso_setmin, _("percentile min"));
      glui_bounds->add_radiobutton_to_group(RADIO_iso_setmin, _("set min"));
      glui_bounds->add_radiobutton_to_group(RADIO_iso_setmin, _("global min"));
      IsoBoundCB(ISO_SETVALMIN);

      PANEL_iso2 = glui_bounds->add_panel_to_panel(ROLLOUT_iso_bounds, "", GLUI_PANEL_NONE);
      EDIT_iso_valmax = glui_bounds->add_edittext_to_panel(PANEL_iso2, "", GLUI_EDITTEXT_FLOAT, &glui_iso_valmax, ISO_VALMAX, IsoBoundCB);
      glui_bounds->add_column_to_panel(PANEL_iso2, false);
      RADIO_iso_setmax = glui_bounds->add_radiogroup_to_panel(PANEL_iso2, &setisomax, ISO_SETVALMAX, IsoBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_iso_setmax, _("percentile max"));
      glui_bounds->add_radiobutton_to_group(RADIO_iso_setmax, _("set max"));
      glui_bounds->add_radiobutton_to_group(RADIO_iso_setmax, _("global max"));
      IsoBoundCB(ISO_SETVALMAX);
    }

    ROLLOUT_iso_settings = glui_bounds->add_rollout_to_panel(ROLLOUT_iso, "Settings", true, ISO_ROLLOUT_SETTINGS, IsoRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_iso_settings, glui_bounds);
    ADDPROCINFO(isoprocinfo, nisoprocinfo, ROLLOUT_iso_settings, ISO_ROLLOUT_SETTINGS, glui_bounds);

    visAIso = show_iso_shaded*1+show_iso_outline*2+show_iso_points*4;
    CHECKBOX_show_iso_shaded = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _("shaded"), &show_iso_shaded, ISO_SURFACE, IsoBoundCB);
    CHECKBOX_show_iso_outline = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _("outline"), &show_iso_outline, ISO_OUTLINE, IsoBoundCB);
    CHECKBOX_show_iso_points = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _("points"), &show_iso_points, ISO_POINTS, IsoBoundCB);

    SPINNER_isolinewidth = glui_bounds->add_spinner_to_panel(ROLLOUT_iso_settings, _("line width"), GLUI_SPINNER_FLOAT, &isolinewidth);
    SPINNER_isolinewidth->set_float_limits(1.0, 10.0);
    SPINNER_iso_outline_ioffset = glui_bounds->add_spinner_to_panel(ROLLOUT_iso_settings, "outline offset", GLUI_SPINNER_INT, &iso_outline_ioffset, ISO_OUTLINE_IOFFSET, IsoBoundCB);
    SPINNER_iso_outline_ioffset->set_int_limits(0, 200);
    SPINNER_isopointsize = glui_bounds->add_spinner_to_panel(ROLLOUT_iso_settings, _("point size"), GLUI_SPINNER_FLOAT, &isopointsize);
    SPINNER_isopointsize->set_float_limits(1.0, 10.0);

    glui_bounds->add_separator_to_panel(ROLLOUT_iso_settings);

#ifdef pp_BETA
    CHECKBOX_sort2 = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _("Sort transparent surfaces:"), &sort_iso_triangles, SORT_SURFACES, SliceBoundCB);
#endif
    CHECKBOX_smooth2 = glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _("Smooth isosurfaces"), &smooth_iso_normal, SMOOTH_SURFACES, SliceBoundCB);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_settings, _("wrapup in background"), &iso_multithread);

    ROLLOUT_iso_color = glui_bounds->add_rollout_to_panel(ROLLOUT_iso, "Color/transparency", false, ISO_ROLLOUT_COLOR, IsoRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_iso_color, glui_bounds);
    ADDPROCINFO(isoprocinfo, nisoprocinfo, ROLLOUT_iso_color, ISO_ROLLOUT_COLOR, glui_bounds);

    RADIO_transparency_option = glui_bounds->add_radiogroup_to_panel(ROLLOUT_iso_color, &iso_transparency_option,ISO_TRANSPARENCY_OPTION,IsoBoundCB);
    glui_bounds->add_radiobutton_to_group(RADIO_transparency_option, _("transparent(constant)"));
    glui_bounds->add_radiobutton_to_group(RADIO_transparency_option, _("transparent(varying)"));
    glui_bounds->add_radiobutton_to_group(RADIO_transparency_option, _("opaque"));
    IsoBoundCB(ISO_TRANSPARENCY_OPTION);

    PANEL_iso_alllevels = glui_bounds->add_panel_to_panel(ROLLOUT_iso_color, "All levels", true);

    SPINNER_iso_transparency = glui_bounds->add_spinner_to_panel(PANEL_iso_alllevels, "alpha", GLUI_SPINNER_INT, &glui_iso_transparency, ISO_TRANSPARENCY, IsoBoundCB);
    BUTTON_updatebound = glui_bounds->add_button_to_panel(PANEL_iso_alllevels, _("Apply"), GLOBAL_ALPHA, IsoBoundCB);

    PANEL_iso_eachlevel = glui_bounds->add_panel_to_panel(ROLLOUT_iso_color, "Each level", true);
    SPINNER_iso_level = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "level:", GLUI_SPINNER_INT, &glui_iso_level, ISO_LEVEL, IsoBoundCB);
    SPINNER_iso_level->set_int_limits(1, MAX_ISO_COLORS);
    LIST_colortable = glui_bounds->add_listbox_to_panel(PANEL_iso_eachlevel, _("Color:"), &i_colortable_list, COLORTABLE_LIST, IsoBoundCB);
    SPINNER_iso_colors[0] = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "red:", GLUI_SPINNER_INT, glui_iso_colors+0, ISO_COLORS, IsoBoundCB);
    SPINNER_iso_colors[1] = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "green:", GLUI_SPINNER_INT, glui_iso_colors+1, ISO_COLORS, IsoBoundCB);
    SPINNER_iso_colors[2] = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "blue:", GLUI_SPINNER_INT, glui_iso_colors+2, ISO_COLORS, IsoBoundCB);
    SPINNER_iso_colors[3] = glui_bounds->add_spinner_to_panel(PANEL_iso_eachlevel, "alpha:", GLUI_SPINNER_INT, glui_iso_colors+3, ISO_COLORS, IsoBoundCB);

    UpdateColorTableList(-1);

    SPINNER_iso_colors[0]->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);
    SPINNER_iso_colors[1]->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);
    SPINNER_iso_colors[2]->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);
    SPINNER_iso_colors[3]->set_int_limits(1, 255, GLUI_LIMIT_CLAMP);
    IsoBoundCB(ISO_LEVEL);
    IsoBoundCB(ISO_COLORS);

    if(ncolorbars>0){
      LIST_iso_colorbar = glui_bounds->add_listbox_to_panel(ROLLOUT_iso_color, "colormap:", &iso_colorbar_index, ISO_COLORBAR_LIST, IsoBoundCB);
      for(i = 0; i<ncolorbars; i++){
        colorbardata *cbi;

        cbi = colorbarinfo+i;
        cbi->label_ptr = cbi->label;
        LIST_iso_colorbar->add_item(i, cbi->label_ptr);
      }
      LIST_iso_colorbar->set_int_val(iso_colorbar_index);
      IsoBoundCB(ISO_COLORBAR_LIST);
    }
    glui_bounds->add_spinner_to_panel(ROLLOUT_iso_color, "min:", GLUI_SPINNER_FLOAT, &iso_valmin);
    glui_bounds->add_spinner_to_panel(ROLLOUT_iso_color, "max:", GLUI_SPINNER_FLOAT, &iso_valmax);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_iso_color,_("Show"),&show_iso_color);
  }

  /* Particle File Bounds  */

  have_part = 0;
  have_evac = 0;
  if(npartinfo > 0 && nevac != npartinfo)have_part = 1;
  if(nevac > 0)have_evac = 1;
  if(have_part==1||have_evac==1){
    char label[100];

    strcpy(label, "");
    if(have_part == 1)strcat(label, "Particle");
    if(have_part == 1 && have_evac == 1)strcat(label, "/");
    if(have_evac == 1)strcat(label, "Evac");

    glui_active=1;
    ROLLOUT_part = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,label,false,PART_ROLLOUT,BoundRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_part, glui_bounds);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_part, PART_ROLLOUT, glui_bounds);

    if(npart5prop>0){
      ipart5prop=0;
      ipart5prop_old=0;
      RADIO_part5 = glui_bounds->add_radiogroup_to_panel(ROLLOUT_part,&ipart5prop,FILETYPEINDEX,PartBoundCB);

      for(i=0;i<npart5prop;i++){
        partpropdata *partpropi;

        partpropi = part5propinfo + i;
        glui_bounds->add_radiobutton_to_group(RADIO_part5,partpropi->label->shortlabel);
      }

      glui_bounds->add_column_to_panel(ROLLOUT_part,false);

      {
        partpropdata *propi;

        propi = part5propinfo;
        setpartmin=propi->setvalmin;
        setpartmax=propi->setvalmax;
        setpartchopmin=propi->setchopmin;
        setpartchopmax=propi->setchopmax;
      }

      PartBoundCB(FILETYPEINDEX);
      PartBoundCB(SETVALMIN);
      PartBoundCB(SETVALMAX);
    }

    {
      char boundmenulabel[100];

      strcpy(boundmenulabel, "Reload ");
      strcat(boundmenulabel, label);
      strcat(boundmenulabel, " File");
      if(npartinfo > 1)strcat(boundmenulabel, "s");
      GenerateBoundDialogs(&ROLLOUT_part_bound,&ROLLOUT_part_chop,ROLLOUT_part,boundmenulabel,
        &EDIT_part_min,&EDIT_part_max,&RADIO_part_setmin,&RADIO_part_setmax,
        &RADIO_part_setmin_percentile,&RADIO_part_setmax_percentile,
        &CHECKBOX_part_setchopmin, &CHECKBOX_part_setchopmax,
        &EDIT_part_chopmin, &EDIT_part_chopmax,
        &STATIC_part_min_unit,&STATIC_part_max_unit,
        NULL,NULL,
        NULL,NULL,
        NULL,
        &setpartmin,&setpartmax,&partmin,&partmax,
        &setpartchopmin,&setpartchopmax,&partchopmin,&partchopmax,
        RELOAD_BOUNDS,DONT_TRUNCATE_BOUNDS,
        PartBoundCB,
        ParticleRolloutCB,particleprocinfo,&nparticleprocinfo
      );
      RADIO_part_setmin_percentile->disable();
      RADIO_part_setmax_percentile->disable();
      PartBoundCB(FILETYPEINDEX);
      ROLLOUT_particle_settings = glui_bounds->add_rollout_to_panel(ROLLOUT_part,"Settings",false,
        PARTICLE_SETTINGS, ParticleRolloutCB);
      INSERT_ROLLOUT(ROLLOUT_particle_settings, glui_bounds);
      ADDPROCINFO(particleprocinfo, nparticleprocinfo, ROLLOUT_particle_settings, PARTICLE_SETTINGS, glui_bounds);

      SPINNER_partpointsize=glui_bounds->add_spinner_to_panel(ROLLOUT_particle_settings,_("Particle size"),GLUI_SPINNER_FLOAT,&partpointsize);
      SPINNER_partpointsize->set_float_limits(1.0,100.0);
      SPINNER_streaklinewidth=glui_bounds->add_spinner_to_panel(ROLLOUT_particle_settings,_("Streak line width"),GLUI_SPINNER_FLOAT,&streaklinewidth);
      SPINNER_streaklinewidth->set_float_limits(1.0,100.0);

      SPINNER_partstreaklength=glui_bounds->add_spinner_to_panel(ROLLOUT_particle_settings,_("Streak length (s)"),GLUI_SPINNER_FLOAT,&float_streak5value,STREAKLENGTH,PartBoundCB);
      SPINNER_partstreaklength->set_float_limits(0.0,tmax_part);

      CHECKBOX_showtracer=glui_bounds->add_checkbox_to_panel(ROLLOUT_particle_settings,_("Always show tracers"),&show_tracers_always,TRACERS,PartBoundCB);

      PANEL_partread=glui_bounds->add_panel_to_panel(ROLLOUT_particle_settings,_("Particle loading"));
      CHECKBOX_partfast = glui_bounds->add_checkbox_to_panel(PANEL_partread, _("Fast loading(streaks disabled)"), &partfast, PARTFAST, PartBoundCB);
      CHECKBOX_part_multithread = glui_bounds->add_checkbox_to_panel(PANEL_partread, _("Parallel loading"), &part_multithread);
      SPINNER_npartthread_ids = glui_bounds->add_spinner_to_panel(PANEL_partread, _("Files loaded at once"), GLUI_SPINNER_INT, &npartthread_ids);
      if(npartinfo>1){
        SPINNER_npartthread_ids->set_int_limits(1,MIN(npartinfo,MAX_PART_THREADS));
      }
      else{
        SPINNER_npartthread_ids->set_int_limits(1,1);
      }
      PartBoundCB(PARTFAST);
    }
    PartBoundCB(FILETYPEINDEX);
  }

  if(have_evac==1){
    glui_active=1;

    glui_bounds->add_checkbox_to_panel(ROLLOUT_part,_("Select avatar"),&select_avatar);
    CHECKBOX_show_evac_slices=glui_bounds->add_checkbox_to_panel(ROLLOUT_part,_("Show slice menus"),&show_evac_slices,SHOW_EVAC_SLICES,SliceBoundCB);
    PANEL_evac_direction=glui_bounds->add_panel_to_panel(ROLLOUT_part,_("Direction vectors"));
    CHECKBOX_constant_coloring=glui_bounds->add_checkbox_to_panel(PANEL_evac_direction,_("Constant coloring"),&constant_evac_coloring,SHOW_EVAC_SLICES,SliceBoundCB);
    CHECKBOX_data_coloring=glui_bounds->add_checkbox_to_panel(PANEL_evac_direction,_("Data coloring"),&data_evac_coloring,DATA_EVAC_COLORING,SliceBoundCB);
    CHECKBOX_show_evac_color=glui_bounds->add_checkbox_to_panel(PANEL_evac_direction,_("Show colorbar (when data coloring)"),&show_evac_colorbar,SHOW_EVAC_SLICES,SliceBoundCB);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_part,_("View from selected Avatar"),&view_from_selected_avatar);
  }

  // ----------------------------------- Plot3D ----------------------------------------

  if(nplot3dinfo>0){
    glui_active=1;
    ROLLOUT_plot3d = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,"Plot3D",false,PLOT3D_ROLLOUT,BoundRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_plot3d, glui_bounds);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_plot3d, PLOT3D_ROLLOUT, glui_bounds);

    RADIO_p3 = glui_bounds->add_radiogroup_to_panel(ROLLOUT_plot3d,&list_p3_index,FILETYPEINDEX,Plot3DBoundCB);
    for(i=0;i<MAXPLOT3DVARS;i++){
      glui_bounds->add_radiobutton_to_group(RADIO_p3,plot3dinfo[0].label[i].shortlabel);
    }
    CHECKBOX_cache_qdata = glui_bounds->add_checkbox_to_panel(ROLLOUT_plot3d, _("Cache Plot3D data"), &cache_qdata, UNLOAD_QDATA, Plot3DBoundCB);
    glui_bounds->add_column_to_panel(ROLLOUT_plot3d,false);


    GenerateBoundDialogs(&ROLLOUT_plot3d_bound, &ROLLOUT_plot3d_chop, ROLLOUT_plot3d, "Reload Plot3D file(s)",
      &EDIT_p3_min, &EDIT_p3_max, &RADIO_p3_setmin, &RADIO_p3_setmax, NULL, NULL,
      &CHECKBOX_p3_setchopmin, &CHECKBOX_p3_setchopmax,
      &EDIT_p3_chopmin, &EDIT_p3_chopmax,
      &STATIC_plot3d_min_unit, &STATIC_plot3d_max_unit,
      &STATIC_plot3d_cmin_unit, &STATIC_plot3d_cmax_unit,
      NULL, NULL,
      NULL,
      &setp3min_temp, &setp3max_temp, &p3min_temp, &p3max_temp,
      &setp3chopmin_temp, &setp3chopmax_temp, &p3chopmin_temp, &p3chopmax_temp,
      RELOAD_BOUNDS, TRUNCATE_BOUNDS,
      Plot3DBoundCB,
      Plot3dRolloutCB,plot3dprocinfo,&nplot3dprocinfo
    );

    ROLLOUT_vector = glui_bounds->add_rollout_to_panel(ROLLOUT_plot3d,_("Vector"),false,PLOT3D_VECTOR_ROLLOUT, Plot3dRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_vector, glui_bounds);
    ADDPROCINFO(plot3dprocinfo, nplot3dprocinfo, ROLLOUT_vector, PLOT3D_VECTOR_ROLLOUT, glui_bounds);

    glui_bounds->add_checkbox_to_panel(ROLLOUT_vector,_("Show vectors"),&visVector,UPDATEPLOT,Plot3DBoundCB);
    SPINNER_plot3d_vectorpointsize=glui_bounds->add_spinner_to_panel(ROLLOUT_vector,_("Point size"),GLUI_SPINNER_FLOAT,&vectorpointsize,UPDATE_VECTOR,Plot3DBoundCB);
    SPINNER_plot3d_vectorpointsize->set_float_limits(1.0,10.0);
    SPINNER_plot3d_vectorlinewidth=glui_bounds->add_spinner_to_panel(ROLLOUT_vector,_("Vector width"),GLUI_SPINNER_FLOAT,&vectorlinewidth,UPDATE_VECTOR,Plot3DBoundCB);
    SPINNER_plot3d_vectorlinewidth->set_float_limits(1.0,10.0);
    SPINNER_plot3d_vectorlinelength=glui_bounds->add_spinner_to_panel(ROLLOUT_vector,_("Vector length"),GLUI_SPINNER_FLOAT,&vecfactor,UPDATE_VECTOR,Plot3DBoundCB);
    SPINNER_plot3d_vectorlinelength->set_float_limits(0.0,20.0);
    SPINNER_plot3dvectorskip=glui_bounds->add_spinner_to_panel(ROLLOUT_vector,_("Vector skip"),GLUI_SPINNER_INT,&vectorskip,PLOT3D_VECTORSKIP,Plot3DBoundCB);
    SPINNER_plot3dvectorskip->set_int_limits(1,4);

    ROLLOUT_isosurface = glui_bounds->add_rollout_to_panel(ROLLOUT_plot3d,"Isosurface",false,PLOT3D_ISOSURFACE_ROLLOUT, Plot3dRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_isosurface, glui_bounds);
    ADDPROCINFO(plot3dprocinfo, nplot3dprocinfo, ROLLOUT_isosurface, PLOT3D_ISOSURFACE_ROLLOUT, glui_bounds);

    PANEL_pan1 = glui_bounds->add_panel_to_panel(ROLLOUT_isosurface,"",GLUI_PANEL_NONE);

    glui_bounds->add_checkbox_to_panel(PANEL_pan1,"Show isosurface",&visiso,PLOTISO,Plot3DBoundCB);
    SPINNER_plot3dpointsize=glui_bounds->add_spinner_to_panel(PANEL_pan1,_("Point size"),GLUI_SPINNER_FLOAT,
      &plot3dpointsize);
    SPINNER_plot3dpointsize->set_float_limits(1.0,10.0);

    SPINNER_plot3dlinewidth=glui_bounds->add_spinner_to_panel(PANEL_pan1,_("Line width"),GLUI_SPINNER_FLOAT,
      &plot3dlinewidth);
    SPINNER_plot3dlinewidth->set_float_limits(1.0,10.0);
//    glui_bounds->add_column_to_panel(ROLLOUT_isosurface);
    PANEL_pan2 = glui_bounds->add_panel_to_panel(ROLLOUT_isosurface,"",GLUI_PANEL_NONE);
    RADIO_plot3d_isotype=glui_bounds->add_radiogroup_to_panel(PANEL_pan2,&p3dsurfacetype,PLOTISOTYPE,Plot3DBoundCB);
    RADIOBUTTON_plot3d_iso_hidden=glui_bounds->add_radiobutton_to_group(RADIO_plot3d_isotype,_("Hidden"));
    glui_bounds->add_radiobutton_to_group(RADIO_plot3d_isotype,_("shaded"));
    glui_bounds->add_radiobutton_to_group(RADIO_plot3d_isotype,_("outline"));
    glui_bounds->add_radiobutton_to_group(RADIO_plot3d_isotype,_("points"));
    RADIOBUTTON_plot3d_iso_hidden->disable();

    p3min_temp=p3min[0];
    p3max_temp=p3max[0];
    p3chopmin_temp=p3chopmin[0];
    p3chopmax_temp=p3chopmax[0];
    glui_bounds->add_column_to_panel(ROLLOUT_plot3d,false);

    Plot3DBoundCB(FILETYPEINDEX);
    Plot3DBoundCB(UNLOAD_QDATA);
  }

  // ----------------------------------- Slice ----------------------------------------

  if(nsliceinfo>0){
    int index;

    glui_active=1;
    ROLLOUT_slice = glui_bounds->add_rollout_to_panel(ROLLOUT_filebounds,"Slice",false,SLICE_ROLLOUT,BoundRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_slice, glui_bounds);
    ADDPROCINFO(boundprocinfo, nboundprocinfo, ROLLOUT_slice, SLICE_ROLLOUT, glui_bounds);

    RADIO_slice = glui_bounds->add_radiogroup_to_panel(ROLLOUT_slice,&list_slice_index,FILETYPEINDEX,SliceBoundCB);

    index=0;
    for(i=0;i<nsliceinfo;i++){
      if(sliceinfo[i].firstshort_slice==1){
        GLUI_RadioButton *RADIOBUTTON_slicetype;

        RADIOBUTTON_slicetype=glui_bounds->add_radiobutton_to_group(RADIO_slice,sliceinfo[i].label.shortlabel);
        if(strcmp(sliceinfo[i].label.shortlabel,_("Fire line"))==0){
          RADIOBUTTON_slicetype->disable();
          fire_line_index=index;
        }
        if(nzoneinfo>0&&strcmp(sliceinfo[i].label.shortlabel, _("TEMP"))==0){
          slicebounds[index].dlg_valmin = zonemin;
          slicebounds[index].dlg_valmax = zonemax;
#ifndef pp_NEWBOUND_DIALOG
          slicebounds[index].dlg_setvalmin = setzonemin;
          slicebounds[index].dlg_setvalmax = setzonemax;
#endif
        }
        index++;
      }
    }
    nlist_slice_index = index;

    glui_bounds->add_column_to_panel(ROLLOUT_slice,false);

#ifdef pp_NEWBOUND_DIALOG
    glui_slicemin = slicebounds[list_slice_index].dlg_valmin;
    glui_slicemax = slicebounds[list_slice_index].dlg_valmax;
    GenerateSliceBoundDialog();
#else
    GenerateBoundDialogs(&ROLLOUT_slice_bound,&ROLLOUT_slice_chop,ROLLOUT_slice,"Reload Slice File(s)",
      &EDIT_slice_min,&EDIT_slice_max,&RADIO_slice_setmin,&RADIO_slice_setmax,NULL,NULL,
      &CHECKBOX_slice_setchopmin, &CHECKBOX_slice_setchopmax,
      &EDIT_slice_chopmin, &EDIT_slice_chopmax,
      &STATIC_slice_min_unit,&STATIC_slice_max_unit,
      &STATIC_slice_cmin_unit,&STATIC_slice_cmax_unit,
      NULL,NULL,
      &PANEL_slice_bound,
      &glui_setslicemin,&glui_setslicemax,&glui_slicemin,&glui_slicemax,
      &glui_setslicechopmin, &glui_setslicechopmax,
      &glui_slicechopmin, &glui_slicechopmax,
      UPDATE_BOUNDS,DONT_TRUNCATE_BOUNDS,
      SliceBoundCB,
      SliceRolloutCB, sliceprocinfo, &nsliceprocinfo
    );
#endif

    ROLLOUT_slice_histogram = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _("Histogram"), false, SLICE_HISTOGRAM_ROLLOUT, SliceRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_slice_histogram, glui_bounds);
    ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slice_histogram, SLICE_HISTOGRAM_ROLLOUT, glui_bounds);

    RADIO_histogram_static = glui_bounds->add_radiogroup_to_panel(ROLLOUT_slice_histogram,&histogram_static);
    glui_bounds->add_radiobutton_to_group(RADIO_histogram_static,_("each time"));
    glui_bounds->add_radiobutton_to_group(RADIO_histogram_static,_("all times"));
    SPINNER_histogram_width_factor=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_histogram, _("val at left"), GLUI_SPINNER_FLOAT,&histogram_width_factor);
    SPINNER_histogram_width_factor->set_float_limits(1.0,100.0);
    SPINNER_histogram_nbuckets=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_histogram, _("bins"), GLUI_SPINNER_INT,&histogram_nbuckets,UPDATE_HISTOGRAM,SliceBoundCB);
    SPINNER_histogram_nbuckets->set_int_limits(3,255);
    CHECKBOX_histogram_show_numbers = glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_histogram, _("percentages"), &histogram_show_numbers, INIT_HISTOGRAM, SliceBoundCB);
    CHECKBOX_histogram_show_graph=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_histogram, _("graph"), &histogram_show_graph, INIT_HISTOGRAM, SliceBoundCB);
    CHECKBOX_histogram_show_outline=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_histogram, _("outline"), &histogram_show_outline);

    ROLLOUT_slice_average=glui_bounds->add_rollout_to_panel(ROLLOUT_slice,_("Average data"),false,SLICE_AVERAGE_ROLLOUT,SliceRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_slice_average, glui_bounds);
    ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slice_average, SLICE_AVERAGE_ROLLOUT, glui_bounds);

    CHECKBOX_average_slice=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_average,_("Average slice data"),&slice_average_flag);
    SPINNER_sliceaverage=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_average,_("Time interval"),GLUI_SPINNER_FLOAT,&slice_average_interval);
    SPINNER_sliceaverage->set_float_limits(0.0,MAX(120.0,tour_tstop));
    glui_bounds->add_button_to_panel(ROLLOUT_slice_average,_("Reload"),ALLFILERELOAD,SliceBoundCB);

    ROLLOUT_slice_vector = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _("Vector"), false, SLICE_VECTOR_ROLLOUT, SliceRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_slice_vector, glui_bounds);
    ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slice_vector, SLICE_VECTOR_ROLLOUT, glui_bounds);

    SPINNER_vectorpointsize = glui_bounds->add_spinner_to_panel(ROLLOUT_slice_vector, _("Point size"), GLUI_SPINNER_FLOAT,
      &vectorpointsize,UPDATE_VECTOR,SliceBoundCB);
    SPINNER_vectorpointsize->set_float_limits(1.0,20.0);
    SPINNER_vectorlinewidth=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_vector,_("Vector width"),GLUI_SPINNER_FLOAT,&vectorlinewidth,UPDATE_VECTOR,SliceBoundCB);
    SPINNER_vectorlinewidth->set_float_limits(1.0,20.0);
    SPINNER_vectorlinelength=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_vector,_("Vector length"),GLUI_SPINNER_FLOAT,&vecfactor,UPDATE_VECTOR,SliceBoundCB);
    SPINNER_vectorlinelength->set_float_limits(0.0,20.0);
    SPINNER_slicevectorskip=glui_bounds->add_spinner_to_panel(ROLLOUT_slice_vector,_("Vector skip"),GLUI_SPINNER_INT,&vectorskip,SLICE_VECTORSKIP,SliceBoundCB);
    SPINNER_slicevectorskip->set_int_limits(1,4);
    CHECKBOX_color_vector_black = glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_vector, _("Color black"), &color_vector_black);

    CHECKBOX_show_node_slices_and_vectors=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_vector,_("Show vectors and node centered slices"),&show_node_slices_and_vectors);
    CHECKBOX_show_node_slices_and_vectors=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice_vector,_("Show vectors and cell centered slices"),&show_cell_slices_and_vectors);
    ROLLOUT_line_contour = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _("Line contours"), false, LINE_CONTOUR_ROLLOUT, SliceRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_line_contour, glui_bounds);
    ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_line_contour, LINE_CONTOUR_ROLLOUT, glui_bounds);

    slice_line_contour_min = 0.0;
    slice_line_contour_max=1.0;
    SPINNER_line_contour_min=glui_bounds->add_spinner_to_panel(ROLLOUT_line_contour,_("Min"),GLUI_SPINNER_FLOAT,
      &slice_line_contour_min,LINE_CONTOUR_VALUE,SliceBoundCB);
    SPINNER_line_contour_max=glui_bounds->add_spinner_to_panel(ROLLOUT_line_contour,_("Max"),GLUI_SPINNER_FLOAT,
      &slice_line_contour_max,LINE_CONTOUR_VALUE,SliceBoundCB);
    slice_line_contour_num=1;
    SPINNER_line_contour_num=glui_bounds->add_spinner_to_panel(ROLLOUT_line_contour,_("Number of contours"),GLUI_SPINNER_INT,
      &slice_line_contour_num,LINE_CONTOUR_VALUE,SliceBoundCB);
    SPINNER_line_contour_width=glui_bounds->add_spinner_to_panel(ROLLOUT_line_contour,_("contour width"),GLUI_SPINNER_FLOAT,&slice_line_contour_width);
    SPINNER_line_contour_width->set_float_limits(1.0,10.0);
      RADIO_contour_type = glui_bounds->add_radiogroup_to_panel(ROLLOUT_line_contour,&slice_contour_type);
    glui_bounds->add_radiobutton_to_group(RADIO_contour_type,_("line"));
#ifdef _DEBUG
    glui_bounds->add_radiobutton_to_group(RADIO_contour_type,_("stepped"));
#endif

    BUTTON_update_line_contour=glui_bounds->add_button_to_panel(ROLLOUT_line_contour,_("Update contours"),UPDATE_LINE_CONTOUR_VALUE,SliceBoundCB);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_line_contour,_("Show contours"),&vis_slice_contours);

    if(n_embedded_meshes>0){
      CHECKBOX_skip_subslice=glui_bounds->add_checkbox_to_panel(ROLLOUT_slice,_("Skip coarse sub-slice"),&skip_slice_in_embedded_mesh);
    }
    if(nslicedups > 0){
      ROLLOUT_slicedups = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, _("Duplicates"), false, SLICE_DUP_ROLLOUT, SliceRolloutCB);
      INSERT_ROLLOUT(ROLLOUT_slicedups, glui_bounds);
      ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_slicedups, SLICE_DUP_ROLLOUT, glui_bounds);

      PANEL_slicedup = glui_bounds->add_panel_to_panel(ROLLOUT_slicedups,"slices",true);
      RADIO_slicedup = glui_bounds->add_radiogroup_to_panel(PANEL_slicedup, &slicedup_option,UPDATE_SLICEDUPS,SliceBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_slicedup, _("Keep all"));
      glui_bounds->add_radiobutton_to_group(RADIO_slicedup, _("Keep fine"));
      glui_bounds->add_radiobutton_to_group(RADIO_slicedup, _("Keep coarse"));

      PANEL_vectorslicedup = glui_bounds->add_panel_to_panel(ROLLOUT_slicedups,"vector slices",true);
      RADIO_vectorslicedup = glui_bounds->add_radiogroup_to_panel(PANEL_vectorslicedup, &vectorslicedup_option, UPDATE_SLICEDUPS, SliceBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_vectorslicedup, _("Keep all"));
      glui_bounds->add_radiobutton_to_group(RADIO_vectorslicedup, _("Keep fine"));
      glui_bounds->add_radiobutton_to_group(RADIO_vectorslicedup, _("Keep coarse"));
    }


    ROLLOUT_boundimmersed = glui_bounds->add_rollout_to_panel(ROLLOUT_slice, "Settings",false,SLICE_SETTINGS_ROLLOUT,SliceRolloutCB);
    INSERT_ROLLOUT(ROLLOUT_boundimmersed, glui_bounds);
    ADDPROCINFO(sliceprocinfo, nsliceprocinfo, ROLLOUT_boundimmersed, SLICE_SETTINGS_ROLLOUT, glui_bounds);

    if(ngeom_data > 0){
      PANEL_immersed = glui_bounds->add_panel_to_panel(ROLLOUT_boundimmersed, "slice(geometry)", true);
      PANEL_immersed_region = glui_bounds->add_panel_to_panel(PANEL_immersed, "region", true);
      RADIO_slice_celltype = glui_bounds->add_radiogroup_to_panel(PANEL_immersed_region, &slice_celltype, IMMERSED_SWITCH_CELLTYPE, ImmersedBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_slice_celltype, "gas");
      glui_bounds->add_radiobutton_to_group(RADIO_slice_celltype, "solid(geometry)");
      glui_bounds->add_radiobutton_to_group(RADIO_slice_celltype, "cut cell");

      glui_bounds->add_column_to_panel(PANEL_immersed, false);
      PANEL_immersed_drawas = glui_bounds->add_panel_to_panel(PANEL_immersed, "draw as", true);
      CHECKBOX_show_slice_shaded = glui_bounds->add_checkbox_to_panel(PANEL_immersed_drawas, "shaded", &glui_show_slice_shaded, IMMERSED_SET_DRAWTYPE, ImmersedBoundCB);
      CHECKBOX_show_slice_outlines = glui_bounds->add_checkbox_to_panel(PANEL_immersed_drawas, "outline", &glui_show_slice_outlines, IMMERSED_SET_DRAWTYPE, ImmersedBoundCB);
      CHECKBOX_show_slice_points = glui_bounds->add_checkbox_to_panel(PANEL_immersed_drawas, "points", &glui_show_slice_points, IMMERSED_SET_DRAWTYPE, ImmersedBoundCB);
      glui_bounds->add_spinner_to_panel(PANEL_immersed_drawas, "line width", GLUI_SPINNER_FLOAT, &geomslice_linewidth);
      glui_bounds->add_spinner_to_panel(PANEL_immersed_drawas, "point size", GLUI_SPINNER_FLOAT, &geomslice_pointsize);

      glui_bounds->add_column_to_panel(PANEL_immersed, false);
      PANEL_immersed_outlinetype = glui_bounds->add_panel_to_panel(PANEL_immersed, "outline type", true);
      RADIO_slice_edgetype = glui_bounds->add_radiogroup_to_panel(PANEL_immersed_outlinetype, &glui_slice_edgetype, IMMERSED_SWITCH_EDGETYPE, ImmersedBoundCB);
      glui_bounds->add_radiobutton_to_group(RADIO_slice_edgetype, _("polygon"));
      glui_bounds->add_radiobutton_to_group(RADIO_slice_edgetype, _("triangle"));
      glui_bounds->add_radiobutton_to_group(RADIO_slice_edgetype, _("none"));

      ImmersedBoundCB(IMMERSED_SWITCH_CELLTYPE);
      ImmersedBoundCB(IMMERSED_SWITCH_EDGETYPE);
    }

    PANEL_sliceshow = glui_bounds->add_panel_to_panel(ROLLOUT_boundimmersed, "slice(regular)", true);
    RADIO_show_slice_in_obst = glui_bounds->add_radiogroup_to_panel(PANEL_sliceshow, &show_slice_in_obst, SLICE_IN_OBST, SliceBoundCB);
    glui_bounds->add_radiobutton_to_group(RADIO_show_slice_in_obst, "gas");
    glui_bounds->add_radiobutton_to_group(RADIO_show_slice_in_obst, "gas and solid(obst)");
    glui_bounds->add_radiobutton_to_group(RADIO_show_slice_in_obst, "solid(obst)");

    SPINNER_transparent_level = glui_bounds->add_spinner_to_panel(ROLLOUT_boundimmersed, _("Transparent level"), GLUI_SPINNER_FLOAT, &transparent_level, TRANSPARENTLEVEL, SliceBoundCB);
    SPINNER_transparent_level->set_float_limits(0.0, 1.0);

    if(nfedinfo>0){
      glui_bounds->add_checkbox_to_panel(ROLLOUT_boundimmersed, "Regenerate FED data", &regenerate_fed);
    }
    CHECKBOX_research_mode = glui_bounds->add_checkbox_to_panel(ROLLOUT_boundimmersed, _("Research display mode"), &research_mode, RESEARCH_MODE, SliceBoundCB);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_boundimmersed, _("Output data to file"), &output_slicedata);

#ifdef pp_FSEEK
    glui_bounds->add_checkbox_to_panel(ROLLOUT_boundimmersed, _("incremental data loading"), &load_incremental, SLICE_LOAD_INCREMENTAL, LoadIncrementalCB);
    LoadIncrementalCB(SLICE_LOAD_INCREMENTAL);
#endif
    glui_bounds->add_checkbox_to_panel(ROLLOUT_boundimmersed, _("Use C for slice input"), &use_cslice);
    glui_bounds->add_spinner_to_panel(ROLLOUT_boundimmersed,"slice offset",GLUI_SPINNER_FLOAT,&sliceoffset_all);

    if(nterraininfo>0){
      glui_bounds->add_checkbox_to_panel(ROLLOUT_boundimmersed, _("terrain slice overlap"), &terrain_slice_overlap);
    }
    PANEL_slice_smoke = glui_bounds->add_panel_to_panel(ROLLOUT_boundimmersed, "slice fire", true);
    glui_bounds->add_checkbox_to_panel(PANEL_slice_smoke, _("max blending"), &slices3d_max_blending);
    glui_bounds->add_checkbox_to_panel(PANEL_slice_smoke, _("show all 3D slices"), &showall_3dslices);

#ifdef pp_SLICETHREAD
    PANEL_sliceread = glui_bounds->add_panel_to_panel(ROLLOUT_boundimmersed, "Slice file loading", true);
    CHECKBOX_slice_multithread = glui_bounds->add_checkbox_to_panel(PANEL_sliceread, _("Parallel loading"), &slice_multithread);
    SPINNER_nslicethread_ids = glui_bounds->add_spinner_to_panel(PANEL_sliceread, _("Files loaded at once"), GLUI_SPINNER_INT, &nslicethread_ids);
    if(nsliceinfo>1){
      SPINNER_nslicethread_ids->set_int_limits(1, MIN(nsliceinfo, MAX_SLICE_THREADS));
    }
    else{
      SPINNER_nslicethread_ids->set_int_limits(1, 1);
    }
#endif

#ifdef pp_SMOKETEST
    glui_bounds->add_checkbox_to_panel(ROLLOUT_boundimmersed, _("opacity adjustment"), &slice_opacity_adjustment);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_boundimmersed, _("sort slices"), &sort_slices);
    glui_bounds->add_checkbox_to_panel(ROLLOUT_boundimmersed, _("show sorted slice labels"), &show_sort_labels);
#endif

    SliceBoundCB(FILETYPEINDEX);
  }

  // ----------------------------------- Time ----------------------------------------

  ROLLOUT_time = glui_bounds->add_rollout_to_panel(PANEL_bounds,"Time", false, TIME_ROLLOUT, FileRolloutCB);
  INSERT_ROLLOUT(ROLLOUT_time, glui_bounds);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_time, TIME_ROLLOUT, glui_bounds);

  PANEL_time1a = glui_bounds->add_panel_to_panel(ROLLOUT_time,"",false);
  SPINNER_timebounds=glui_bounds->add_spinner_to_panel(PANEL_time1a,_("Time:"),GLUI_SPINNER_FLOAT,&glui_time);
  glui_bounds->add_spinner_to_panel(PANEL_time1a, _("Offset:"), GLUI_SPINNER_FLOAT, &timeoffset);
  glui_bounds->add_column_to_panel(PANEL_time1a,false);
  SPINNER_timebounds->set_float_limits(0.0,3600.0*24);
  BUTTON_SETTIME=glui_bounds->add_button_to_panel(PANEL_time1a,_("Set"),SET_TIME,TimeBoundCB);

  PANEL_time2 = glui_bounds->add_panel_to_panel(ROLLOUT_time,_("Data loading"),true);

  PANEL_time2a = glui_bounds->add_panel_to_panel(PANEL_time2,"",false);
  SPINNER_tload_begin=glui_bounds->add_spinner_to_panel(PANEL_time2a,_("min time"),GLUI_SPINNER_FLOAT,&tload_begin,TBOUNDS,TimeBoundCB);
  glui_bounds->add_column_to_panel(PANEL_time2a,false);
  CHECKBOX_use_tload_begin=glui_bounds->add_checkbox_to_panel(PANEL_time2a,"",&use_tload_begin,TBOUNDS_USE,TimeBoundCB);

  PANEL_time2b = glui_bounds->add_panel_to_panel(PANEL_time2,"",false);
  SPINNER_tload_end=glui_bounds->add_spinner_to_panel(PANEL_time2b,_("max time"),GLUI_SPINNER_FLOAT,&tload_end,TBOUNDS,TimeBoundCB);
  glui_bounds->add_column_to_panel(PANEL_time2b,false);
  CHECKBOX_use_tload_end=glui_bounds->add_checkbox_to_panel(PANEL_time2b,"",&use_tload_end,TBOUNDS_USE,TimeBoundCB);

  PANEL_time2c = glui_bounds->add_panel_to_panel(PANEL_time2,"",false);
  SPINNER_tload_skip=glui_bounds->add_spinner_to_panel(PANEL_time2c,_("frame skip"),GLUI_SPINNER_INT,&tload_skip,TBOUNDS,TimeBoundCB);
  glui_bounds->add_column_to_panel(PANEL_time2c,false);
  CHECKBOX_use_tload_skip=glui_bounds->add_checkbox_to_panel(PANEL_time2c,"",&use_tload_skip,TBOUNDS_USE,TimeBoundCB);
  SPINNER_tload_skip->set_int_limits(0,1000);

  glui_bounds->add_button_to_panel(PANEL_time2,_("Reload all data"), RELOAD_ALL_DATA,TimeBoundCB);
  glui_bounds->add_button_to_panel(PANEL_time2, _("Reload new data"), RELOAD_INCREMENTAL_DATA, TimeBoundCB);

  TimeBoundCB(TBOUNDS_USE);

  // ----------------------------------- Memory check ----------------------------------------

#ifdef pp_MEMDEBUG
  ROLLOUT_memcheck = glui_bounds->add_rollout(_("Memory check"),false,MEMCHECK_ROLLOUT,FileRolloutCB);
  INSERT_ROLLOUT(ROLLOUT_memcheck, glui_bounds);
  ADDPROCINFO(fileprocinfo, nfileprocinfo, ROLLOUT_memcheck, MEMCHECK_ROLLOUT, glui_bounds);

  list_memcheck_index = 0;
  RADIO_memcheck = glui_bounds->add_radiogroup_to_panel(ROLLOUT_memcheck,&list_memcheck_index,MEMCHECK, MemcheckCB);
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,_("Unlimited"));
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,"1 GB");
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,"2 GB");
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,"4 GB");
  glui_bounds->add_radiobutton_to_group(RADIO_memcheck,"8 GB");
#endif

  glui_bounds->add_button(_("Save settings"), SAVE_SETTINGS_BOUNDS, BoundsDlgCB);
#ifdef pp_CLOSEOFF
  GLUI_Button *BUTTON_button1=glui_bounds->add_button(_("Close"), CLOSE_BOUNDS, BoundsDlgCB);
  BUTTON_button1->disable();
#else
  glui_bounds->add_button(_("Close"), CLOSE_BOUNDS, BoundsDlgCB);
#endif

  glui_bounds->set_main_gfx_window( main_window );
}

/* ------------------ CompressOnOff ------------------------ */

extern "C" void CompressOnOff(int flag){
  switch(flag){
    case OFF:
      if(BUTTON_compress!=NULL)BUTTON_compress->disable();
      if(CHECKBOX_overwrite_all!=NULL)CHECKBOX_overwrite_all->disable();
      if(CHECKBOX_erase_all!=NULL)CHECKBOX_erase_all->disable();
      if(CHECKBOX_multi_task!=NULL)CHECKBOX_multi_task->disable();
      break;
    case ON:
      if(BUTTON_compress!=NULL)BUTTON_compress->enable();
      if(CHECKBOX_overwrite_all!=NULL)CHECKBOX_overwrite_all->enable();
      if(CHECKBOX_erase_all!=NULL)CHECKBOX_erase_all->enable();
      if(CHECKBOX_multi_task!=NULL)CHECKBOX_multi_task->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
  }
}

/* ------------------ Plot3DBoundCB ------------------------ */

extern "C" void Plot3DBoundCB(int var){
  int i;

  switch(var){
  case UNLOAD_QDATA:
    if(cache_qdata==0){
     ROLLOUT_isosurface->disable();
    }
    else{
      int enable_isosurface;

      enable_isosurface=1;
      for(i=0;i<nmeshes;i++){
        meshdata *meshi;
        plot3ddata *plot3di;

        meshi = meshinfo + i;
        if(meshi->plot3dfilenum==-1)continue;
        plot3di = plot3dinfo + meshi->plot3dfilenum;
        if(plot3di->loaded==0||plot3di->display==0)continue;
        if(meshi->qdata==NULL){
          enable_isosurface=0;
          break;
        }
      }
      if(enable_isosurface==1)ROLLOUT_isosurface->enable();
      if(enable_isosurface==0)ROLLOUT_isosurface->disable();
    }
    break;
  case PLOT3D_VECTORSKIP:
    if(SPINNER_slicevectorskip!=NULL)SPINNER_slicevectorskip->set_int_val(vectorskip);
    break;
  case UPDATE_VECTOR_FROM_SMV:
    if(SPINNER_vectorpointsize!=NULL&&SPINNER_vectorlinewidth!=NULL&&SPINNER_vectorlinelength!=NULL){
      SPINNER_vectorpointsize->set_float_val(vectorpointsize);
      SPINNER_vectorlinewidth->set_float_val(vectorlinewidth);
      SPINNER_vectorlinelength->set_float_val(vecfactor);
    }
    Plot3DBoundCB(UPDATE_VECTOR);
    break;
  case UPDATE_VECTOR:
    UpdatePlotSlice(XDIR);
    UpdatePlotSlice(YDIR);
    UpdatePlotSlice(ZDIR);
    break;
  case CHOPUPDATE:
    UpdateChopColors();
    break;
  case SETCHOPMINVAL:
    UpdateChopColors();
    switch(setp3chopmin_temp){
      case DISABLE:
        EDIT_p3_chopmin->disable();
        break;
      case ENABLE:
        EDIT_p3_chopmin->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    break;
  case SETCHOPMAXVAL:
    UpdateChopColors();
    switch(setp3chopmax_temp){
      case DISABLE:
        EDIT_p3_chopmax->disable();
        break;
      case ENABLE:
        EDIT_p3_chopmax->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    break;
  case CHOPVALMIN:
    p3chopmin[list_p3_index]=p3chopmin_temp;
    setp3chopmin[list_p3_index]=setp3chopmin_temp;

    UpdateChopColors();
    break;
  case CHOPVALMAX:
    p3chopmax[list_p3_index]=p3chopmax_temp;
    setp3chopmax[list_p3_index]=setp3chopmax_temp;

    UpdateChopColors();
    break;
  case PLOTISO:
    visiso = 1 - visiso;
    HandleIso();
    glutPostRedisplay();
    break;
  case PLOTISOTYPE:
    updatemenu=1;
    break;
  case UPDATEPLOT:
    UpdateRGBColors(COLORBAR_INDEX_NONE);
    updatemenu=1;
    glutPostRedisplay();
    break;
  case FILETYPEINDEX:
   p3min[list_p3_index_old]=p3min_temp;
   p3max[list_p3_index_old]=p3max_temp;
   setp3min[list_p3_index_old]=setp3min_temp;
   setp3max[list_p3_index_old]=setp3max_temp;
   p3chopmin[list_p3_index_old]=p3chopmin_temp;
   p3chopmax[list_p3_index_old]=p3chopmax_temp;
   setp3chopmin[list_p3_index_old]=setp3chopmin_temp;
   setp3chopmax[list_p3_index_old]=setp3chopmax_temp;

   p3min_temp=p3min[list_p3_index];
   p3max_temp=p3max[list_p3_index];
   setp3min_temp=setp3min[list_p3_index];
   setp3max_temp=setp3max[list_p3_index];
   p3chopmin_temp=p3chopmin[list_p3_index];
   p3chopmax_temp=p3chopmax[list_p3_index];
   setp3chopmin_temp=setp3chopmin[list_p3_index];
   setp3chopmax_temp=setp3chopmax[list_p3_index];
   if(plot3dinfo!=NULL){
     plot3dmin_unit = (unsigned char *)plot3dinfo->label[list_p3_index].unit;
     plot3dmax_unit = plot3dmin_unit;
     UpdateGluiPlot3D_units();
   }

   EDIT_p3_min->set_float_val(p3min_temp);
   EDIT_p3_max->set_float_val(p3max_temp);
   EDIT_p3_chopmin->set_float_val(p3chopmin_temp);
   EDIT_p3_chopmax->set_float_val(p3chopmax_temp);

   list_p3_index_old=list_p3_index;
   RADIO_p3_setmin->set_int_val(setp3min_temp);
   RADIO_p3_setmax->set_int_val(setp3max_temp);
   CHECKBOX_p3_setchopmin->set_int_val(setp3chopmin_temp);
   CHECKBOX_p3_setchopmax->set_int_val(setp3chopmax_temp);
   Plot3DBoundCB(SETCHOPMINVAL);
   Plot3DBoundCB(SETCHOPMAXVAL);
   Plot3DBoundCB(SETVALMIN);
   Plot3DBoundCB(SETVALMAX);
   break;
  case SETVALMIN:
   switch(setp3min_temp){
    case PERCENTILE_MIN:
    case GLOBAL_MIN:
      EDIT_p3_min->disable();
      break;
    case SET_MIN:
    case CHOP_MIN:
      EDIT_p3_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
   }
   break;
  case SETVALMAX:
     switch(setp3max_temp){
      case PERCENTILE_MIN:
      case GLOBAL_MIN:
        EDIT_p3_max->disable();
        break;
      case SET_MIN:
      case CHOP_MIN:
        EDIT_p3_max->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
     }
   break;
  case FILEUPDATE:
   p3min[list_p3_index] =    p3min_temp;
   p3max[list_p3_index] =    p3max_temp;
   setp3min[list_p3_index] = setp3min_temp;
   setp3max[list_p3_index] = setp3max_temp;
   break;
  case FILERELOAD:
   Plot3DBoundCB(FILEUPDATE);
   for(i=0;i<nplot3dinfo;i++){
     if(plot3dinfo[i].loaded==0)continue;
     LoadPlot3dMenu(i);
   }
   UpdateGlui();
   break;
  case VALMIN:
  case VALMAX:
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ UpdateTracers ------------------------ */

extern "C" void UpdateTracers(void){
  if(CHECKBOX_showtracer==NULL)return;
  CHECKBOX_showtracer->set_int_val(show_tracers_always);
}


/* ------------------ UpdateGluiIsotype ------------------------ */

extern "C" void UpdateGluiIsotype(void){
  CHECKBOX_show_iso_shaded->set_int_val(visAIso&1);
  CHECKBOX_show_iso_outline->set_int_val((visAIso&2)/2);
  CHECKBOX_show_iso_points->set_int_val((visAIso&4)/4);
}


/* ------------------ UpdateGluiPlot3Dtype ------------------------ */

extern "C" void UpdateGluiPlot3Dtype(void){
  RADIO_plot3d_isotype->set_int_val(p3dsurfacetype);
}
/* ------------------ UpdateChar ------------------------ */

extern "C" void UpdateChar(void){
  if(CHECKBOX_showchar==NULL)return;
  if(canshow_threshold==1){
    CHECKBOX_showchar->enable();
  }
  else{
    CHECKBOX_showchar->disable();
  }
  CHECKBOX_showchar->set_int_val(vis_threshold);
  BoundBoundCB(SHOWCHAR);
}

/* ------------------ UpdatePlot3dListIndex ------------------------ */

extern "C" void UpdatePlot3dListIndex(void){
  int i;

  if(RADIO_p3==NULL)return;
  i = RADIO_p3->get_int_val();
  if(i!=plotn-1){
    p3min[i]=p3min_temp;
    p3max[i]=p3max_temp;
    setp3min[i]=setp3min_temp;
    setp3max[i]=setp3max_temp;

    p3chopmin[i]=p3chopmin_temp;
    p3chopmax[i]=p3chopmax_temp;
    setp3chopmin[i]=setp3chopmin_temp;
    setp3chopmax[i]=setp3chopmax_temp;
  }

  i=plotn-1;
  list_p3_index_old=i;
  if(i<0)i=0;
  if(i>MAXPLOT3DVARS-1)i= MAXPLOT3DVARS-1;
  RADIO_p3->set_int_val(i);
  p3min_temp = p3min[i];
  p3max_temp = p3max[i];
  setp3min_temp = setp3min[i];
  setp3max_temp = setp3max[i];

  p3chopmin_temp = p3chopmin[i];
  p3chopmax_temp = p3chopmax[i];
  setp3chopmin_temp = setp3chopmin[i];
  setp3chopmax_temp = setp3chopmax[i];
  if(nplot3dinfo>0){
    Plot3DBoundCB(SETVALMIN);
    Plot3DBoundCB(SETVALMAX);
    Plot3DBoundCB(SETCHOPMINVAL);
    Plot3DBoundCB(SETCHOPMAXVAL);
  }
  UpdateChopColors();
  UpdateGlui();
}

/* ------------------ GetColorTableIndex ------------------------ */

int GetColorTableIndex(int *color){
  int i;

  if(colortableinfo==NULL)return -1;
  for(i=0;i<ncolortableinfo;i++){
    colortabledata *cti;

    cti = colortableinfo + i;
    if(color[0]==cti->color[0]&&color[1]==cti->color[1]&&color[2]==cti->color[2])return i;
  }
  return -1;
}

/* ------------------ GetColorTable ------------------------ */

colortabledata *GetColorTable(char *label){
  int i;

  if(label==NULL||strlen(label)==0)return NULL;
  for(i=0;i<ncolortableinfo;i++){
    colortabledata *cti;

    cti = colortableinfo + i;
    if(strcmp(label,cti->label)==0)return cti;
  }
  return NULL;
}

/* ------------------ IsoBoundCB ------------------------ */

extern "C" void IsoBoundCB(int var){
  int i;
  float *iso_color;

  switch(var){
  case ISO_OUTLINE_IOFFSET:
    iso_outline_offset = (float)iso_outline_ioffset/1000.0;
  break;
  case ISO_COLORBAR_LIST:
    iso_colorbar = colorbarinfo + iso_colorbar_index;
    ColorbarMenu(iso_colorbar_index);
    updatemenu = 1;
    update_texturebar = 1;
    break;
  case ISO_TRANSPARENCY_OPTION:
    switch(iso_transparency_option){
      case ISO_TRANSPARENT_CONSTANT:
        use_transparency_data=1;
        iso_opacity_change=0;
        break;
      case ISO_TRANSPARENT_VARYING:
        use_transparency_data=1;
        iso_opacity_change=1;
        break;
      case ISO_OPAQUE:
        use_transparency_data=0;
        iso_opacity_change=1;
        break;
    }
    SliceBoundCB(DATA_transparent);
    break;
  case COLORTABLE_LIST:
    if(i_colortable_list>=0){
      colortabledata *cti;

      cti = colortableinfo+i_colortable_list;
      glui_iso_colors[0] = cti->color[0];
      glui_iso_colors[1] = cti->color[1];
      glui_iso_colors[2] = cti->color[2];
      glui_iso_colors[3] = cti->color[3];
      IsoBoundCB(ISO_COLORS);
      if(SPINNER_iso_colors[0]!=NULL)SPINNER_iso_colors[0]->set_int_val(glui_iso_colors[0]);
      if(SPINNER_iso_colors[1]!=NULL)SPINNER_iso_colors[1]->set_int_val(glui_iso_colors[1]);
      if(SPINNER_iso_colors[2]!=NULL)SPINNER_iso_colors[2]->set_int_val(glui_iso_colors[2]);
      if(SPINNER_iso_colors[3]!=NULL)SPINNER_iso_colors[3]->set_int_val(glui_iso_colors[3]);
    }
    break;

  case ISO_LEVEL:
    iso_color = iso_colors+4*(glui_iso_level-1);
    glui_iso_colors[0] = CLAMP(255*iso_color[0]+0.1, 0, 255);
    glui_iso_colors[1] = CLAMP(255*iso_color[1]+0.1, 0, 255);
    glui_iso_colors[2] = CLAMP(255*iso_color[2]+0.1, 0, 255);
    glui_iso_colors[3] = CLAMP(255*iso_color[3]+0.1, 1, 255);

    if(SPINNER_iso_colors[0]!=NULL)SPINNER_iso_colors[0]->set_int_val(glui_iso_colors[0]);
    if(SPINNER_iso_colors[1]!=NULL)SPINNER_iso_colors[1]->set_int_val(glui_iso_colors[1]);
    if(SPINNER_iso_colors[2]!=NULL)SPINNER_iso_colors[2]->set_int_val(glui_iso_colors[2]);
    if(SPINNER_iso_colors[3]!=NULL)SPINNER_iso_colors[3]->set_int_val(glui_iso_colors[3]);
    if(LIST_colortable != NULL){
      i_colortable_list = CLAMP(GetColorTableIndex(glui_iso_colors), -1, ncolortableinfo - 1);
      LIST_colortable->set_int_val(i_colortable_list);
    }
    break;
  case GLOBAL_ALPHA:
    for(i = 0; i < MAX_ISO_COLORS; i++){
      iso_colors[4 * i + 3] = iso_transparency;
    }
    if(SPINNER_iso_colors[3]!=NULL)SPINNER_iso_colors[3]->set_int_val(glui_iso_transparency);
    IsoBoundCB(ISO_COLORS);
    break;
  case ISO_TRANSPARENCY:
    iso_transparency = CLAMP(((float)glui_iso_transparency + 0.1) / 255.0,0.0,1.0);
    break;
  case ISO_COLORS:
    iso_color = iso_colors+4*(glui_iso_level-1);
    iso_color[0] = ((float)glui_iso_colors[0]+0.1)/255.0;
    iso_color[1] = ((float)glui_iso_colors[1]+0.1)/255.0;
    iso_color[2] = ((float)glui_iso_colors[2]+0.1)/255.0;
    iso_color[3] = ((float)glui_iso_colors[3]+0.1)/255.0;

    for(i = 0; i < MAX_ISO_COLORS; i++){
      float graylevel;

      graylevel = TOBW(iso_colors+4*i);
      iso_colorsbw[4 * i + 0] = graylevel;
      iso_colorsbw[4 * i + 1] = graylevel;
      iso_colorsbw[4 * i + 2] = graylevel;
      iso_colorsbw[4 * i + 3] = iso_colors[4 * i + 3];
    }
    UpdateIsoColors();
    if(LIST_colortable!=NULL){
      i_colortable_list = CLAMP(GetColorTableIndex(glui_iso_colors), -1, ncolortableinfo-1);
      LIST_colortable->set_int_val(i_colortable_list);
    }
    break;
  case FRAMELOADING:
    isoframestep_global=isoframeskip_global+1;
    isozipstep=isozipskip+1;
    updatemenu=1;
    break;
  case ISO_SURFACE:
  case  ISO_OUTLINE:
  case ISO_POINTS:
    visAIso= 1*show_iso_shaded + 2*show_iso_outline + 4*show_iso_points;
    updatemenu=1;
    break;
  case ISO_SETVALMIN:
    switch (setisomin){
      case SET_MIN:
        iso_valmin=glui_iso_valmin;
        EDIT_iso_valmin->enable();
        break;
      case PERCENTILE_MIN:
        iso_valmin = iso_percentile_min;
        EDIT_iso_valmin->disable();
        break;
      case GLOBAL_MIN:
        iso_valmin = iso_global_min;
        EDIT_iso_valmin->disable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    glui_iso_valmin=iso_valmin;
    EDIT_iso_valmin->set_float_val(glui_iso_valmin);
    glutPostRedisplay();
    break;
  case ISO_SETVALMAX:
    switch (setisomax){
      case SET_MAX:
        iso_valmax=glui_iso_valmax;
        EDIT_iso_valmax->enable();
        break;
      case PERCENTILE_MAX:
        iso_valmax = iso_percentile_max;
        EDIT_iso_valmax->disable();
        break;
      case GLOBAL_MAX:
        iso_valmax = iso_global_max;
        EDIT_iso_valmax->disable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    glui_iso_valmax = iso_valmax;
    EDIT_iso_valmax->set_float_val(glui_iso_valmax);
    glutPostRedisplay();
    break;
  case ISO_VALMIN:
    iso_valmin=glui_iso_valmin;
    glutPostRedisplay();
    break;
  case ISO_VALMAX:
    iso_valmax=glui_iso_valmax;
    glutPostRedisplay();
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ AddScriptList ------------------------ */

extern "C" void AddScriptList(char *file, int id){
  if(file!=NULL&&strlen(file)>0&&LIST_scriptlist!=NULL){
    LIST_scriptlist->add_item(id,file);
  }
}

/* ------------------ GluiScriptEnable ------------------------ */

extern "C" void GluiScriptEnable(void){
    BUTTON_script_start->enable();
    BUTTON_script_stop->enable();
    BUTTON_script_runscript->enable();
    LIST_scriptlist->enable();
    BUTTON_script_saveini->enable();
    BUTTON_script_setsuffix->enable();
    EDIT_ini->enable();
  }

/* ------------------ GluiScriptDisable ------------------------ */

extern "C"  void GluiScriptDisable(void){
    BUTTON_script_start->disable();
    BUTTON_script_stop->disable();
    BUTTON_script_runscript->disable();
    LIST_scriptlist->disable();
    BUTTON_script_saveini->disable();
    BUTTON_script_setsuffix->disable();
    EDIT_ini->disable();
  }

/* ------------------ UpdateBoundaryListIndex ------------------------ */

extern "C" void UpdateBoundaryListIndex(int patchfilenum){
  int i;
  if(RADIO_bf==NULL)return;
  for(i=0;i<npatch2;i++){
    patchdata *patchi;

    patchi = patchinfo + patchfilenum;
    if(strcmp(patchlabellist[i],patchi->label.shortlabel)==0){
      if(RADIO_bf == NULL){
        list_patch_index = i;
      }
      else {
        RADIO_bf->set_int_val(i);
      }
      list_patch_index_old=list_patch_index;
      Global2LocalBoundaryBounds(patchlabellist[i]);
      RADIO_patch_setmin->set_int_val(setpatchmin);
      RADIO_patch_setmax->set_int_val(setpatchmax);
      EDIT_patch_min->set_float_val(patchmin);
      EDIT_patch_max->set_float_val(patchmax);

      CHECKBOX_patch_setchopmin->set_int_val(setpatchchopmin);
      CHECKBOX_patch_setchopmax->set_int_val(setpatchchopmax);
      EDIT_patch_chopmin->set_float_val(patchchopmin);
      EDIT_patch_chopmax->set_float_val(patchchopmax);

      if(setpatchmin==SET_MIN){
        EDIT_patch_min->enable();
      }
      else{
        EDIT_patch_min->disable();
      }
      if(setpatchmax==SET_MAX){
        EDIT_patch_max->enable();
      }
      else{
        EDIT_patch_max->disable();
      }

      if(setpatchchopmin==SET_MIN){
        EDIT_patch_chopmin->enable();
      }
      else{
        EDIT_patch_chopmin->disable();
      }
      if(setpatchchopmax==SET_MAX){
        EDIT_patch_chopmax->enable();
      }
      else{
        EDIT_patch_chopmax->disable();
      }
      return;
    }
  }
}

/* ------------------ UpdateBoundaryListIndex2 ------------------------ */

extern "C" void UpdateBoundaryListIndex2(char *label){
  int i;
  for(i=0;i<npatch2;i++){
    if(strcmp(patchlabellist[i],label)==0){
      UpdateBoundaryListIndex(patchlabellist_index[i]);
      break;
    }
  }
}

/* ------------------ UpdateGluiStreakValue ------------------------ */

extern "C" void UpdateGluiStreakValue(float rvalue){
  float_streak5value=rvalue;
  if(SPINNER_partstreaklength!=NULL){
    SPINNER_partstreaklength->set_float_val(rvalue);
    SPINNER_partstreaklength->set_float_limits(0.0,tmax_part);
  }
}

/* ------------------ PartBoundCB ------------------------ */

void PartBoundCB(int var){
  partpropdata *prop_new, *prop_old;

  prop_new = part5propinfo + ipart5prop;
  prop_old = part5propinfo + ipart5prop_old;
  switch(var){
  case VALMIN:
    if(setpartmin==SET_MIN)prop_new->user_min=partmin;
    break;
  case VALMAX:
    if(setpartmax==SET_MAX)prop_new->user_max = partmax;
    break;
  case FILETYPEINDEX:

    // save data from controls

    prop_old->setvalmin=setpartmin;
    prop_old->setvalmax=setpartmax;
    if(setpartmin==SET_MIN){
      prop_old->user_min=partmin;
    }
    if(setpartmax==SET_MAX){
      prop_old->user_max=partmax;
    }
    prop_old->setchopmin=setpartchopmin;
    prop_old->setchopmax=setpartchopmax;
    prop_old->chopmin=partchopmin;
    prop_old->chopmax=partchopmax;

    // copy data to controls

    setpartmin=prop_new->setvalmin;
    if(setpartmin==PERCENTILE_MIN)setpartmin = GLOBAL_MIN;

    setpartmax = prop_new->setvalmax;
    if(setpartmax==PERCENTILE_MAX)setpartmax = GLOBAL_MAX;

    PartBoundCB(SETVALMIN);
    PartBoundCB(SETVALMAX);

    setpartchopmin=prop_new->setchopmin;
    setpartchopmax=prop_new->setchopmax;
    partchopmin=prop_new->chopmin;
    partchopmax=prop_new->chopmax;

    partmin_unit = (unsigned char *)prop_new->label->unit;
    partmax_unit = partmin_unit;
    UpdateGluiPartUnits();

    // update controls

    if(RADIO_part_setmin!=NULL)RADIO_part_setmin->set_int_val(setpartmin);
    if(RADIO_part_setmax!=NULL)RADIO_part_setmax->set_int_val(setpartmax);


    if(EDIT_part_chopmin!=NULL)EDIT_part_chopmin->set_float_val(partchopmin);
    if(EDIT_part_chopmax!=NULL)EDIT_part_chopmax->set_float_val(partchopmax);
    if(CHECKBOX_part_setchopmin!=NULL)CHECKBOX_part_setchopmin->set_int_val(setpartchopmin);
    if(CHECKBOX_part_setchopmax!=NULL)CHECKBOX_part_setchopmax->set_int_val(setpartchopmax);

    ipart5prop_old = ipart5prop;

    if(CHECKBOX_part_setchopmin!=NULL)PartBoundCB(SETCHOPMINVAL);
    if(CHECKBOX_part_setchopmax!=NULL)PartBoundCB(SETCHOPMAXVAL);

    break;
  case STREAKLENGTH:
    UpdateStreakValue(float_streak5value-0.001);
    if(float_streak5value==0.0){
      streak5show=0;
    }
    else{
      streak5show=1;
    }
    updatemenu=1;
    break;
  case TRACERS:
  case PARTFAST:
    if(partfast==0||npartinfo<=1){
      CHECKBOX_part_multithread->disable();
      SPINNER_npartthread_ids->disable();
    }
    else{
      CHECKBOX_part_multithread->enable();
      SPINNER_npartthread_ids->enable();
    }
    CHECKBOX_part_multithread->set_int_val(part_multithread);
    updatemenu=1;
    break;
  case FRAMELOADING:
    partframestep=partframeskip+1;
    evacframestep=evacframeskip+1;
    evacframestep=evacframeskip+1;
    updatemenu=1;
    break;
  case CHOPUPDATE:
    UpdateChopColors();
    break;
  case SETCHOPMINVAL:
    prop_new->setchopmin=setpartchopmin;
    prop_new->chopmin=partchopmin;
    UpdateChopColors();
    switch(setpartchopmin){
      case DISABLE:
      EDIT_part_chopmin->disable();
      break;
      case ENABLE:
      EDIT_part_chopmin->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case SETCHOPMAXVAL:
    prop_new->setchopmax=setpartchopmax;
    prop_new->chopmax=partchopmax;
    UpdateChopColors();
    switch(setpartchopmax){
      case DISABLE:
      EDIT_part_chopmax->disable();
      break;
      case ENABLE:
      EDIT_part_chopmax->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case CHOPVALMIN:
    prop_new->setchopmin=setpartchopmin;
    prop_new->chopmin=partchopmin;
    if(EDIT_part_chopmin!=NULL)EDIT_part_chopmin->set_float_val(partchopmin);
    UpdateChopColors();
    break;
  case CHOPVALMAX:
    prop_new->setchopmax=setpartchopmax;
    prop_new->chopmax=partchopmax;
    if(EDIT_part_chopmax!=NULL)EDIT_part_chopmax->set_float_val(partchopmax);
    UpdateChopColors();
    break;
  case SETVALMIN:
    if(setpartmin_old==SET_MIN){
      if(prop_old!=NULL)prop_old->user_min=partmin;
    }
    setpartmin_old=setpartmin;
    if(prop_new!=NULL)prop_new->setvalmin = setpartmin;
    switch(setpartmin){
    case PERCENTILE_MIN:
      if(prop_new!=NULL)partmin=prop_new->percentile_min;
      if(EDIT_part_min!=NULL)EDIT_part_min->disable();
      break;
    case GLOBAL_MIN:
      if(prop_new!=NULL)partmin=prop_new->global_min;
      if(EDIT_part_min!=NULL)EDIT_part_min->disable();
      break;
    case SET_MIN:
      if(prop_new!=NULL)partmin=prop_new->user_min;
      if(EDIT_part_min!=NULL)EDIT_part_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    if(prop_new!=NULL)prop_new->valmin=partmin;
    if(EDIT_part_min!=NULL)EDIT_part_min->set_float_val(partmin);
   break;
  case SETVALMAX:
    if(setpartmax_old==SET_MAX){
      if(prop_old!=NULL)prop_old->user_max=partmax;
    }
    setpartmax_old=setpartmax;
    if(prop_new!=NULL)prop_new->setvalmax = setpartmax;
    switch(setpartmax){
    case PERCENTILE_MAX:
      if(prop_new!=NULL)partmax=prop_new->percentile_max;
      if(EDIT_part_max!=NULL)EDIT_part_max->disable();
      break;
    case GLOBAL_MAX:
      if(prop_new!=NULL)partmax=prop_new->global_max;
      if(EDIT_part_max!=NULL)EDIT_part_max->disable();
      break;
    case SET_MAX:
      if(prop_new!=NULL)partmax=prop_new->user_max;
      if(EDIT_part_max!=NULL)EDIT_part_max->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    if(prop_new!=NULL)prop_new->valmax=partmax;
    if(EDIT_part_max!=NULL)EDIT_part_max->set_float_val(partmax);
   break;
  case FILERELOAD:
    {
      int prop_index_SAVE;

     prop_index_SAVE= global_prop_index;
     PartBoundCB(FILETYPEINDEX);
     if(EDIT_part_min!=NULL&&setpartmin==SET_MIN)PartBoundCB(SETVALMIN);
     if(EDIT_part_max!=NULL&&setpartmax==SET_MAX)PartBoundCB(SETVALMAX);
     LoadParticleMenu(PARTFILE_RELOADALL);
     LoadEvacMenu(EVACFILE_RELOADALL);
     UpdateGlui();
     ParticlePropShowMenu(prop_index_SAVE);
    }
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ UpdateZoneTempBounds ------------------------ */

#ifdef pp_NEWBOUND_DIALOG
void UpdateZoneTempBounds(float valmin, float valmax){
#else
void UpdateZoneTempBounds(int setvalmin, float valmin, int setvalmax, float valmax){
#endif
  int slice_index;

  if(nzoneinfo>0&&RADIO_slice!=NULL){
    slice_index = RADIO_slice->get_int_val();
    if(strcmp(slicebounds[slice_index].shortlabel, "TEMP")==0){
#ifdef pp_NEWBOUND_DIALOG
      setzonemin = SET_MIN;
      setzonemax = SET_MAX;
#else
      setzonemin = setvalmin;
      setzonemax = setvalmax;
#endif
      zonemin = valmin;
      zonemax = valmax;
      if(EDIT_zone_min!=NULL)EDIT_zone_min->set_float_val(valmin);
      if(EDIT_zone_max!=NULL)EDIT_zone_max->set_float_val(valmax);
#ifndef pp_NEWBOUND_DIALOG
      if(RADIO_zone_setmin!=NULL)RADIO_zone_setmin->set_int_val(setvalmin);
      if(RADIO_zone_setmax!=NULL)RADIO_zone_setmax->set_int_val(setvalmax);
#endif
      SliceBoundCB(FILEUPDATE);
    }
  }
}

/* ------------------ UpdateSliceTempBounds ------------------------ */

#ifdef pp_NEWBOUND_DIALOG
void UpdateSliceTempBounds(float valmin, float valmax){
#else
void UpdateSliceTempBounds(int setvalmin, float valmin, int setvalmax, float valmax){
#endif
  int temp_index;

  if(slicebounds_temp==NULL||RADIO_slice==NULL)return;
  temp_index = slicebounds_temp-slicebounds;
#ifdef pp_NEWBOUND_DIALOG
    slicebounds_temp->dlg_valmin = valmin;
    slicebounds_temp->dlg_valmax = valmax;
#else
  if(setvalmin==SET_MIN){
    slicebounds_temp->dlg_valmin = valmin;
  }
  else{
    slicebounds_temp->global_valmin = valmin;
  }
  if(setvalmax==SET_MAX){
    slicebounds_temp->dlg_valmax = valmax;
  }
  else{
    slicebounds_temp->global_valmax = valmax;
  }
  slicebounds_temp->dlg_setvalmin = setvalmin;
  slicebounds_temp->dlg_setvalmax = setvalmax;
#endif

  if(RADIO_slice==NULL)return;
  RADIO_slice->set_int_val(temp_index);
  EDIT_slice_min->set_float_val(valmin);
  EDIT_slice_max->set_float_val(valmax);
#ifndef pp_NEWBOUND_DIALOG
  RADIO_slice_setmin->set_int_val(setvalmin);
  RADIO_slice_setmax->set_int_val(setvalmax);
#endif
  SliceBounds2Glui(temp_index);
}

#ifdef pp_NEWBOUND_DIALOG

/* ------------------ Glui2SliceBounds ------------------------ */

void Glui2SliceBounds(void){
  if(slicebounds==NULL)return;
  slicebounds[list_slice_index].dlg_valmin    = glui_slicemin;
  slicebounds[list_slice_index].setchopmin    = glui_setslicechopmin;
  slicebounds[list_slice_index].chopmin       = glui_slicechopmin;

  slicebounds[list_slice_index].dlg_valmax    = glui_slicemax;
  slicebounds[list_slice_index].setchopmax    = glui_setslicechopmax;
  slicebounds[list_slice_index].chopmax       = glui_slicechopmax;
}
#else

/* ------------------ SetSliceMin ------------------------ */

void SetSliceMin(int setslicemin_local, float slicemin_local, int setslicechopmin_local, float slicechopmin_local){
  if(slicebounds == NULL)return;
#ifndef pp_NEWBOUND_DIALOG
  slicebounds[list_slice_index].dlg_setvalmin  = setslicemin_local;
#endif
  slicebounds[list_slice_index].dlg_valmin = slicemin_local;
  slicebounds[list_slice_index].setchopmin = setslicechopmin_local;
  slicebounds[list_slice_index].chopmin    = slicechopmin_local;
}
/* ------------------ SetSliceMax ------------------------ */

void SetSliceMax(int setslicemax_local, float slicemax_local, int setslicechopmax_local, float slicechopmax_local){
  if(slicebounds==NULL)return;
#ifndef pp_NEWBOUND_DIALOG
  slicebounds[list_slice_index].dlg_setvalmax  = setslicemax_local;
#endif
  slicebounds[list_slice_index].dlg_valmax = slicemax_local;
  slicebounds[list_slice_index].setchopmax = setslicechopmax_local;
  slicebounds[list_slice_index].chopmax    = slicechopmax_local;
}
#endif

/* ------------------ SliceBoundCB ------------------------ */

extern "C" void SliceBoundCB(int var){
  int error,i;
  int ii;
  slicedata *sd;
  int last_slice;

  updatemenu=1;
#ifdef pp_NEWBOUND_DIALOG
  if(var==SLICE_LOADED_ONLY){
    if(slice_loaded_only==1){
      BUTTON_slice_percentile_bounds->enable();
    }
    else{
      BUTTON_slice_percentile_bounds->disable();
    }
    return;
  }
  if(var==PERCENTILE_BOUNDS_LOADED){
    float per_min, per_max;

    SliceBoundCB(GLOBAL_BOUNDS);
    GetSlicePercentileBounds(slicebounds[list_slice_index].label->shortlabel, glui_slicemin, glui_slicemax, &per_min, &per_max);
    if(per_min<=per_max){
      slicebounds[list_slice_index].percentile_valmin = per_min;
      slicebounds[list_slice_index].percentile_valmax = per_max;
      slicebounds[list_slice_index].dlg_valmin = per_min;
      slicebounds[list_slice_index].dlg_valmax = per_max;
      EDIT_slice_min->set_float_val(per_min);
      EDIT_slice_max->set_float_val(per_max);
    }
    return;
  }
  if(var==GLOBAL_BOUNDS_MIN){
    slicebounds[list_slice_index].dlg_valmin = slicebounds[list_slice_index].global_valmin;
    EDIT_slice_min->set_float_val(slicebounds[list_slice_index].dlg_valmin);
    return;
  }
  if(var==GLOBAL_BOUNDS_MAX){
    slicebounds[list_slice_index].dlg_valmax = slicebounds[list_slice_index].global_valmax;
    EDIT_slice_max->set_float_val(slicebounds[list_slice_index].dlg_valmax);
    return;
  }
  if(var==GLOBAL_BOUNDS){
    if(slice_loaded_only==0){
      SliceBoundCB(GLOBAL_BOUNDS_MIN);
      SliceBoundCB(GLOBAL_BOUNDS_MAX);
    }
    else{
      float slice_min, slice_max;
      int slice_loaded=0;

      slice_min = 1.0;
      slice_max = 0.0;
      for(i = 0; i<nsliceinfo; i++){
        slicedata *slicei;

        slicei = sliceinfo+i;
        if(slicei->loaded==0||strcmp(slicei->label.shortlabel, slicebounds[list_slice_index].shortlabel)!=0)continue;
        slice_loaded = 1;
        if(slicei->file_min>slicei->file_max)continue;
        if(slice_min>slice_max){
          slice_min = slicei->file_min;
          slice_max = slicei->file_max;
        }
        else{
          slice_min = MIN(slice_min, slicei->file_min);
          slice_max = MAX(slice_max, slicei->file_max);
        }
      }
      if(slice_loaded==0)printf("no slices of type %s are loaded - minimum  slice bound not updated\n",slicebounds[list_slice_index].shortlabel);
      if(slice_min<=slice_max){
        slicebounds[list_slice_index].dlg_valmin = slice_min;
        EDIT_slice_min->set_float_val(slice_min);
        slicebounds[list_slice_index].dlg_valmax = slice_max;
        EDIT_slice_max->set_float_val(slice_max);
      }
    }
    return;
  }
  if(var==GLOBAL_BOUNDS_MAX_LOADED){
    float slice_min, slice_max;
    int slice_loaded=0;

    slice_min = 1.0;
    slice_max = 0.0;
    for(i = 0; i<nsliceinfo; i++){
      slicedata *slicei;

      slicei = sliceinfo+i;
      if(slicei->loaded==0||strcmp(slicei->label.shortlabel, slicebounds[list_slice_index].shortlabel)!=0)continue;
      slice_loaded=1;
      if(slicei->file_min>slicei->file_max)continue;
      if(slice_min>slice_max){
        slice_min = slicei->file_min;
        slice_max = slicei->file_max;
      }
      else{
        slice_min = MIN(slice_min, slicei->file_min);
        slice_max = MAX(slice_max, slicei->file_max);
      }
    }
    if(slice_loaded==0)printf("no slices of type %s are loaded - maximum  slice bound not updated\n",slicebounds[list_slice_index].shortlabel);
    if(slice_min<=slice_max){
      slicebounds[list_slice_index].dlg_valmax = slice_max;
      EDIT_slice_max->set_float_val(slice_max);
    }
    return;
  }
  if(var==GLOBAL_BOUNDS_LOADED){
    SliceBoundCB(GLOBAL_BOUNDS_MIN_LOADED);
    SliceBoundCB(GLOBAL_BOUNDS_MAX_LOADED);
    return;
  }
#endif
  if(var==UPDATE_HISTOGRAM){
    update_slice_hists = 1;
    histograms_defined = 0;
    return;
  }
  if(var == INIT_HISTOGRAM){
    if(histogram_show_graph == 1 || histogram_show_numbers == 1){
      update_slice_hists = 1;
      visColorbarVertical = 1;
    }
    return;
  }
  if(var==SLICE_IN_OBST){
    if(show_slice_in_obst!=show_slice_in_obst_old){
      SliceBoundCB(FILEUPDATE);
      show_slice_in_obst_old = show_slice_in_obst;
    }
    return;
  }
  if(var==DATA_transparent){
    UpdateTransparency();
    UpdateChopColors();
    UpdateIsoControls();
    return;
  }

  if(var==COLORBAR_EXTREME2){
    UpdateExtreme();
    return;
  }
  if(var==COLORBAR_LIST2){
      selectedcolorbar_index= GetColorbarListIndex();
      UpdateColorbarList();
      ColorbarMenu(selectedcolorbar_index);
      ColorbarGlobal2Local();
  }
  if(var==COLORBAR_SMOOTH){
    updatemenu=1;
    return;
  }
  switch(var){
    case UPDATE_SLICEDUPS:
    updatemenu = 1;
    break;
    case SLICE_VECTORSKIP:
      if(SPINNER_plot3dvectorskip!=NULL)SPINNER_plot3dvectorskip->set_int_val(vectorskip);
      break;
    case ZONEVALMINMAX:
      GetZoneColors(zonetu, nzonetotal, izonetu,zonemin, zonemax, nrgb, nrgb_full, colorlabelzone, colorvalueszone, zonescale, zonelevels256);
      GetZoneColors(zonetl, nzonetotal, izonetl, zonemin, zonemax, nrgb, nrgb_full, colorlabelzone, colorvalueszone, zonescale, zonelevels256);
      if(have_zonefl==1)GetZoneColors(zonefl, nzonetotal, izonefl, zonemin, zonemax, nrgb, nrgb_full, colorlabelzone, colorvalueszone, zonescale, zonelevels256);
      if(have_zonelw==1)GetZoneColors(zonelw, nzonetotal, izonelw, zonemin, zonemax, nrgb, nrgb_full, colorlabelzone, colorvalueszone, zonescale, zonelevels256);
      if(have_zoneuw==1)GetZoneColors(zoneuw, nzonetotal, izoneuw, zonemin, zonemax, nrgb, nrgb_full, colorlabelzone, colorvalueszone, zonescale, zonelevels256);
      if(have_zonecl==1)GetZoneColors(zonecl, nzonetotal, izonecl, zonemin, zonemax, nrgb, nrgb_full, colorlabelzone, colorvalueszone, zonescale, zonelevels256);
      if(have_target_data==1)GetZoneColors(zonetargets, nzonetotal_targets, izonetargets, zonemin, zonemax, nrgb, nrgb_full, colorlabelzone, colorvalueszone, zonescale, zonelevels256);
#ifdef pp_NEWBOUND_DIALOG
      UpdateSliceTempBounds(zonemin, zonemax);
#else
      UpdateSliceTempBounds(setzonemin, zonemin, setzonemax, zonemax);
#endif
      zoneusermin=zonemin;
      zoneusermax=zonemax;
      break;
    case SETZONEVALMINMAX:
      if(setzonemin==SET_MIN){
        EDIT_zone_min->enable();
        if(EDIT_slice_min!=NULL)EDIT_slice_min->enable();
        zonemin=zoneusermin;
        EDIT_zone_min->set_float_val(zonemin);
      }
      else{
        EDIT_zone_min->disable();
        if(EDIT_slice_min!=NULL)EDIT_slice_min->disable();
        EDIT_zone_min->set_float_val(zoneglobalmin);
      }
      if(setzonemax==SET_MAX){
        EDIT_zone_max->enable();
        if(EDIT_slice_max!=NULL)EDIT_slice_max->enable();
        zonemax = zoneusermax;
        EDIT_zone_max->set_float_val(zonemax);
      }
      else{
        EDIT_zone_max->disable();
        if(EDIT_slice_max!=NULL)EDIT_slice_max->disable();
        EDIT_zone_max->set_float_val(zoneglobalmax);
      }
      GetZoneColors(zonetu, nzonetotal, izonetu,zonemin, zonemax, nrgb, nrgb_full, colorlabelzone, colorvalueszone, zonescale, zonelevels256);
      GetZoneColors(zonetl, nzonetotal, izonetl, zonemin, zonemax, nrgb, nrgb_full, colorlabelzone, colorvalueszone, zonescale, zonelevels256);
#ifdef pp_NEWBOUND_DIALOG
      UpdateSliceTempBounds(zonemin, zonemax);
#else
      UpdateSliceTempBounds(setzonemin, zonemin, setzonemax, zonemax);
#endif
      break;
    case COLORBAR_LIST2:
      if(selectedcolorbar_index2 == bw_colorbar_index){
        setbwdata = 1;
        ColorbarMenu(bw_colorbar_index);
      }
      else{
        setbwdata = 0;
      }
      IsoBoundCB(ISO_COLORS);
      SetLabelControls();
      break;
    case RESEARCH_MODE:
      for(i=0;i<nsliceinfo;i++){
        slicedata *slicei;

        slicei = sliceinfo + i;
        if(slicei->loaded==0||slicei->display==0)continue;
        UpdateSliceList(GetSliceBoundsIndex(slicei));
        break;
      }
      if(research_mode==1){
        axislabels_smooth=0;
        visColorbarVertical_save=visColorbarVertical;
        visColorbarVertical=1;

        // slice files

        if(nsliceloaded > 0){
#ifndef pp_NEWBOUND_DIALOG
          glui_setslicemin_save = glui_setslicemin;
          glui_setslicemin = GLOBAL_MIN;

          glui_setslicemax_save = glui_setslicemax;
          glui_setslicemax = GLOBAL_MAX;
#endif
#ifndef pp_NEWBOUND_DIALOG
          glui_setslicemin_save = glui_setslicemin;
#endif
          glui_slicemin_save = glui_slicemin;
          SliceBoundCB(SETVALMIN);

#ifndef pp_NEWBOUND_DIALOG
          glui_setslicemax_save = glui_setslicemax;
#endif
          glui_slicemax_save = glui_slicemax;
          SliceBoundCB(SETVALMAX);
        }

        // boundary files

        if(npatchloaded > 0){
          setpatchmin_save = setpatchmin;
          patchmin_save = patchmin;
          setpatchmin = GLOBAL_MIN;
          BoundBoundCB(SETVALMIN);

          setpatchmax_save = setpatchmax;
          patchmax_save = patchmax;
          setpatchmax = GLOBAL_MAX;
          BoundBoundCB(SETVALMAX);
          BoundBoundCB(FILERELOAD);
        }

        // particle files

        if(npartloaded>0){
          setpartmin_save = setpartmin;
          partmin_save = partmin;
          setpartmin = GLOBAL_MIN;
          PartBoundCB(SETVALMIN);

          setpartmax_save = setpartmax;
          partmax_save = partmax;
          setpartmax = GLOBAL_MAX;
          PartBoundCB(SETVALMAX);
          PartBoundCB(FILERELOAD);
        }

        // plot3d files

        if(nplot3dloaded>0){
          for(i = 0; i < MAXPLOT3DVARS; i++){
            setp3min_save[i] = setp3min[i];
            p3min_save[i] = p3min[i];
            setp3min[i] = GLOBAL_MIN;

            setp3max_save[i] = setp3max[i];
            p3max_save[i] = p3max[i];
            setp3max[i] = GLOBAL_MAX;
          }
          Plot3DBoundCB(SETVALMIN);
          Plot3DBoundCB(SETVALMAX);
          Plot3DBoundCB(FILERELOAD);
        }

        PRINTF("research mode on\n");
      }
      else{
        visColorbarVertical=visColorbarVertical_save;

        // slice files

        if(nsliceloaded > 0){
          SliceBoundCB(SETVALMIN);
          SliceBoundCB(VALMIN);

          SliceBoundCB(SETVALMAX);
          SliceBoundCB(VALMAX);
        }

        // boundary files

        if(npatchloaded > 0){
          setpatchmin = setpatchmin_save;
          BoundBoundCB(SETVALMIN);
          patchmin = patchmin_save;
          BoundBoundCB(VALMIN);

          setpatchmax = setpatchmax_save;
          BoundBoundCB(SETVALMAX);
          patchmax = patchmax_save;
          BoundBoundCB(VALMAX);
          BoundBoundCB(FILERELOAD);
        }

        // particle files

        if(npartloaded > 0){
          setpartmin = setpartmin_save;
          PartBoundCB(SETVALMIN);
          partmin = partmin_save;
          PartBoundCB(VALMIN);

          setpartmax = setpartmax_save;
          PartBoundCB(SETVALMAX);
          partmax = partmax_save;
          PartBoundCB(VALMAX);
          PartBoundCB(FILERELOAD);
        }

        // Plot3D files

        if(nplot3dloaded > 0){
          for(i = 0; i < MAXPLOT3DVARS; i++){
            setp3min[i] = setp3min_save[i];
            p3min[i] = p3min_save[i];

            setp3max[i] = setp3max_save[i];
            p3max[i] = p3max_save[i];
          }
          Plot3DBoundCB(SETVALMIN);
          Plot3DBoundCB(VALMIN);
          Plot3DBoundCB(SETVALMAX);
          Plot3DBoundCB(VALMAX);
          Plot3DBoundCB(FILERELOAD);
        }

        PRINTF("research mode off\n");
      }
      UpdateAxisLabelsSmooth();
      SliceBoundCB(FILEUPDATE);
      break;
    case SMOOTH_SURFACES:
      CHECKBOX_smooth2->set_int_val(smooth_iso_normal);
      break;
    case SORT_SURFACES:
      sort_geometry=sort_iso_triangles;
      for(i=nsurfinfo;i<nsurfinfo+MAX_ISO_COLORS+1;i++){
        surfdata *surfi;

        surfi = surfinfo + i;
        surfi->transparent_level=transparent_level;
      }
      CHECKBOX_sort2->set_int_val(sort_iso_triangles);
      IsoBoundCB(GLOBAL_ALPHA);
      break;
    case SHOW_EVAC_SLICES:
      data_evac_coloring = 1-constant_evac_coloring;
      UpdateSliceMenuShow();
      if(CHECKBOX_data_coloring!=NULL)CHECKBOX_data_coloring->set_int_val(data_evac_coloring);
      break;
    case DATA_EVAC_COLORING:
      constant_evac_coloring = 1-data_evac_coloring;
      UpdateSliceMenuShow();
      if(CHECKBOX_constant_coloring!=NULL)CHECKBOX_constant_coloring->set_int_val(constant_evac_coloring);
      break;
    case COLORBAND:
      UpdateRGBColors(colorbar_select_index);
      break;
    case TRANSPARENTLEVEL:
      for(i=nsurfinfo;i<nsurfinfo+MAX_ISO_COLORS+1;i++){
        surfdata *surfi;

        surfi = surfinfo + i;
        surfi->transparent_level=transparent_level;
      }
      UpdateRGBColors(COLORBAR_INDEX_NONE);
      if(SPINNER_transparent_level!=NULL)SPINNER_transparent_level->set_float_val(transparent_level);
      break;
    case LINE_CONTOUR_VALUE:
      if(slice_line_contour_num<1){
        slice_line_contour_num=1;
        SPINNER_line_contour_num->set_int_val(slice_line_contour_num);
      }
      if(slice_line_contour_num==1&&slice_line_contour_min!=slice_line_contour_max){
        slice_line_contour_max=slice_line_contour_min;
        SPINNER_line_contour_max->set_float_val(slice_line_contour_max);
      }
      slicebounds[list_slice_index].line_contour_min=slice_line_contour_min;
      slicebounds[list_slice_index].line_contour_max=slice_line_contour_max;
      slicebounds[list_slice_index].line_contour_num=slice_line_contour_num;
      break;
    case UPDATE_LINE_CONTOUR_VALUE:
      UpdateSliceContours(list_slice_index,slice_line_contour_min, slice_line_contour_max,slice_line_contour_num);
      break;
  case UPDATE_VECTOR_FROM_SMV:
    if(SPINNER_plot3d_vectorpointsize!=NULL&&SPINNER_plot3d_vectorlinewidth!=NULL&&SPINNER_plot3d_vectorlinelength!=NULL){
      SPINNER_plot3d_vectorpointsize->set_float_val(vectorpointsize);
      SPINNER_plot3d_vectorlinewidth->set_float_val(vectorlinewidth);
      SPINNER_plot3d_vectorlinelength->set_float_val(vecfactor);
    }
    SliceBoundCB(UPDATE_VECTOR);
    break;
  case UPDATE_VECTOR:
    break;
  case FRAMELOADING:
    sliceframestep=sliceframeskip+1;
    slicezipstep=slicezipskip+1;
    updatemenu=1;
    break;
  case CHOPUPDATE:
    UpdateChopColors();
    break;
  case SETCHOPMINVAL:
    UpdateChopColors();
#ifdef pp_NEWBOUND_DIALOG
    Glui2SliceBounds();
#else
    SetSliceMin(glui_setslicemin, glui_slicemin, glui_setslicechopmin, glui_slicechopmin);
#endif
    switch(glui_setslicechopmin){
      case DISABLE:
        EDIT_slice_chopmin->disable();
        break;
      case ENABLE:
        EDIT_slice_chopmin->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    break;
  case SETCHOPMAXVAL:
    UpdateChopColors();
#ifdef pp_NEWBOUND_DIALOG
    Glui2SliceBounds();
#else
    SetSliceMax(glui_setslicemax, glui_slicemax, glui_setslicechopmax, glui_slicechopmax);
#endif
    switch(glui_setslicechopmax){
      case DISABLE:
      EDIT_slice_chopmax->disable();
      break;
      case ENABLE:
      EDIT_slice_chopmax->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    break;
  case CHOPVALMIN:
    if(EDIT_slice_min!=NULL)EDIT_slice_min->set_float_val(glui_slicemin);
#ifdef pp_NEWBOUND_DIALOG
    Glui2SliceBounds();
#else
    SetSliceMin(glui_setslicemin, glui_slicemin, glui_setslicechopmin, glui_slicechopmin);
#endif
    UpdateChopColors();
    break;
  case CHOPVALMAX:
    if(EDIT_slice_max!=NULL)EDIT_slice_max->set_float_val(glui_slicemax);
#ifdef pp_NEWBOUND_DIALOG
    Glui2SliceBounds();
#else
    SetSliceMax(glui_setslicemax,glui_slicemax,glui_setslicechopmax,glui_slicechopmax);
#endif
    UpdateChopColors();
    break;
  case SETVALMIN:
#ifndef pp_NEWBOUND_DIALOG
    switch(glui_setslicemin){
    case PERCENTILE_MIN:
    case GLOBAL_MIN:
      if(EDIT_slice_min!=NULL)EDIT_slice_min->disable();
      if(EDIT_zone_min!=NULL)EDIT_zone_min->disable();
      break;
    case SET_MIN:
      if(EDIT_slice_min!=NULL)EDIT_slice_min->enable();
      if(EDIT_zone_min!=NULL)EDIT_zone_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    if(RADIO_slice_setmin!=NULL)RADIO_slice_setmin->set_int_val(glui_setslicemin);
#endif
#ifdef pp_NEWBOUND_DIALOG
    Glui2SliceBounds();
    UpdateZoneTempBounds(glui_slicemin, glui_slicemax);
#else
    SetSliceMin(glui_setslicemin, glui_slicemin, glui_setslicechopmin, glui_slicechopmin);
    UpdateZoneTempBounds(glui_setslicemin, glui_slicemin, glui_setslicemax, glui_slicemax);
#endif
    break;
  case SETVALMAX:
#ifndef pp_NEWBOUND_DIALOG
    switch(glui_setslicemax){
      case PERCENTILE_MAX:
      case GLOBAL_MAX:
        if(EDIT_slice_max!=NULL)EDIT_slice_max->disable();
        if(EDIT_zone_max!=NULL)EDIT_zone_max->disable();
        break;
      case SET_MAX:
        if(EDIT_slice_max!=NULL)EDIT_slice_max->enable();
        if(EDIT_zone_max!=NULL)EDIT_zone_max->enable();
        break;
      default:
        ASSERT(FFALSE);
        break;
    }
    if(RADIO_slice_setmax!=NULL)RADIO_slice_setmax->set_int_val(glui_setslicemax);
#endif
#ifdef pp_NEWBOUND_DIALOG
    Glui2SliceBounds();
    UpdateZoneTempBounds(glui_slicemin, glui_slicemax);
#else
    SetSliceMax(glui_setslicemax, glui_slicemax, glui_setslicechopmax, glui_slicechopmax);
    UpdateZoneTempBounds(glui_setslicemin, glui_slicemin, glui_setslicemax, glui_slicemax);
#endif
    break;
  case VALMIN:
#ifdef pp_NEWBOUND_DIALOG
    if(is_fed_colorbar==1&&ABS(glui_slicemin)>0.001){
#else
    if(is_fed_colorbar==1&&glui_setslicemin==1&&ABS(glui_slicemin)>0.001){
#endif
      printf("***warning: min/max bounds for the FED colorbar are set to 0.0 and 3.0 respectively.\n");
      printf("   To use different min/max bounds, change the colorbar.\n");
      glui_slicemin = 0.0;
    }
    if(EDIT_slice_min!=NULL)EDIT_slice_min->set_float_val(glui_slicemin);
#ifdef pp_NEWBOUND_DIALOG
    Glui2SliceBounds();
    UpdateZoneTempBounds(glui_slicemin, glui_slicemax);
#else
    SetSliceMin(glui_setslicemin, glui_slicemin, glui_setslicechopmin, glui_slicechopmin);
    UpdateZoneTempBounds(glui_setslicemin, glui_slicemin, glui_setslicemax, glui_slicemax);
#endif
    break;
  case VALMAX:
#ifdef pp_NEWBOUND_DIALOG
    if(is_fed_colorbar==1&&ABS(glui_slicemax-3.0)>0.001){
#else
    if(is_fed_colorbar==1&&glui_setslicemax==1&&ABS(glui_slicemax-3.0)>0.001){
#endif
      printf("***warning: min/max bounds for the FED colorbar are set to 0.0 and 3.0 respectively.\n");
      printf("   To use different min/max bounds, change the colorbar.\n");
      glui_slicemax = 3.0;
    }
    if(EDIT_slice_max!=NULL)EDIT_slice_max->set_float_val(glui_slicemax);
#ifdef pp_NEWBOUND_DIALOG
    Glui2SliceBounds();
    UpdateZoneTempBounds(glui_slicemin, glui_slicemax);
#else
    SetSliceMax(glui_setslicemax,glui_slicemax,glui_setslicechopmax,glui_slicechopmax);
    UpdateZoneTempBounds(glui_setslicemin, glui_slicemin, glui_setslicemax, glui_slicemax);
#endif
    break;
  case FILETYPEINDEX:
    if(slice_bounds_dialog==1&&list_slice_index==fire_line_index){
      slice_bounds_dialog=0;
      if(ROLLOUT_slice_bound!=NULL){
        ROLLOUT_slice_bound->close();
        ROLLOUT_slice_bound->disable();
      }
      if(ROLLOUT_slice_chop!=NULL){
        ROLLOUT_slice_chop->close();
        ROLLOUT_slice_chop->disable();
      }
    }
    if(slice_bounds_dialog==0&&list_slice_index!=fire_line_index){
      slice_bounds_dialog=1;
      if(ROLLOUT_slice_bound!=NULL){
        ROLLOUT_slice_bound->enable();
      }
      if(ROLLOUT_slice_chop!=NULL){
        ROLLOUT_slice_chop->enable();
      }
    }
    SliceBounds2Glui(list_slice_index);
    if(EDIT_slice_min!=NULL)EDIT_slice_min->set_float_val(glui_slicemin);
    if(EDIT_slice_max!=NULL)EDIT_slice_max->set_float_val(glui_slicemax);

#ifndef pp_NEWBOUND_DIALOG
    RADIO_slice_setmin->set_int_val(glui_setslicemin);
    RADIO_slice_setmax->set_int_val(glui_setslicemax);
#endif

    EDIT_slice_chopmin->set_float_val(glui_slicechopmin);
    EDIT_slice_chopmax->set_float_val(glui_slicechopmax);
    CHECKBOX_slice_setchopmin->set_int_val(glui_setslicechopmin);
    CHECKBOX_slice_setchopmax->set_int_val(glui_setslicechopmax);

    if(glui_setslicechopmin==1){
      EDIT_slice_chopmin->enable();
    }
    else{
      EDIT_slice_chopmin->disable();
    }
    if(glui_setslicechopmax==1){
      EDIT_slice_chopmax->enable();
    }
    else{
      EDIT_slice_chopmax->disable();
    }
    SPINNER_line_contour_min->set_float_val(slice_line_contour_min);
    SPINNER_line_contour_max->set_float_val(slice_line_contour_max);
    SPINNER_line_contour_num->set_int_val(slice_line_contour_num);
    if(ROLLOUT_zone_bound!=NULL){
      int slice_index;

      slice_index = RADIO_slice->get_int_val();
      if(strcmp(slicebounds[slice_index].shortlabel, "TEMP")==0){
        BoundRolloutCB(ZONE_ROLLOUT);
        if(ROLLOUT_slice_bound!=NULL)ROLLOUT_slice_bound->disable();
      }
      else{
        if(ROLLOUT_slice_bound!=NULL)ROLLOUT_slice_bound->enable();
      }
    }
#ifndef pp_NEWBOUND_DIALOG
    switch(glui_setslicemin){
    case PERCENTILE_MIN:
    case GLOBAL_MIN:
      if(EDIT_slice_min!=NULL)EDIT_slice_min->disable();
      break;
    case SET_MIN:
      if(EDIT_slice_min!=NULL)EDIT_slice_min->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
    switch(glui_setslicemax){
    case PERCENTILE_MIN:
    case GLOBAL_MAX:
      if(EDIT_slice_max!=NULL)EDIT_slice_max->disable();
      break;
    case SET_MAX:
      if(EDIT_slice_max!=NULL)EDIT_slice_max->enable();
      break;
    default:
      ASSERT(FFALSE);
      break;
    }
#endif
    break;
  case FILEUPDATE:
    use_slice_glui_bounds = 1;
#ifndef pp_NEWBOUND_DIALOG
    glui_setslicemin_save = glui_setslicemin;
    glui_setslicemax_save = glui_setslicemax;
#endif
    slice_fileupdate++;
    if(slice_fileupdate>1){
      slice_fileupdate--;
      break;
    }
    for(ii = nslice_loaded - 1; ii >= 0; ii--){
      i = slice_loaded_list[ii];
      sd = sliceinfo + i;
      if(sd->slicefile_labelindex == slicefile_labelindex){
        last_slice = i;
        break;
      }
    }
    for(ii = 0; ii < nslice_loaded; ii++){
      i = slice_loaded_list[ii];
      sd = sliceinfo + i;
      if(sd->slicefile_labelindex == slicefile_labelindex){
        int set_slicecolor;

        set_slicecolor = DEFER_SLICECOLOR;
        if(i == last_slice)set_slicecolor = SET_SLICECOLOR;
        ReadSlice("", i, RESETBOUNDS, set_slicecolor, &error);
      }
    }
    slice_fileupdate--;
    use_slice_glui_bounds = 0;
#ifndef pp_NEWBOUND_DIALOG
    glui_setslicemin = glui_setslicemin_save;
    glui_setslicemax = glui_setslicemax_save;
#endif
    break;
  case FILERELOAD:
    SliceBoundCB(FILEUPDATE);
    if(slicefilenum>=0&&slicefilenum<nsliceinfo){
      LoadSliceMenu(slicefilenum);
    }
    else{
      LoadSliceMenu(0);
    }
    UpdateGlui();
    break;
  case ALLFILERELOAD:
    ReloadAllSliceFiles();
    break;
  default:
    ASSERT(FFALSE);
    break;
  }
}

/* ------------------ UpdateSliceList ------------------------ */

extern "C" void UpdateSliceList(int index){
  if(glui_defined==0)return;
  RADIO_slice->set_int_val(index);
}

/* ------------------ UpdateSliceListIndex ------------------------ */

extern "C" void UpdateSliceListIndex(int sfn){
  int i;
  int slice_filetype;
  slicedata *sd;

  if(glui_defined==0)return;
  if(sfn<0){
    UpdateSliceFilenum();
    sfn=slicefilenum;
  }
  if(sfn < 0)return;
  sd = sliceinfo+sfn;
  slice_filetype = GetSliceBoundsIndex(sd);
  if(slice_filetype>=0&&slice_filetype<nslicebounds){
    i = slice_filetype;
    RADIO_slice->set_int_val(i);
    SliceBounds2Glui(i);
    list_slice_index=i;
    SliceBoundCB(SETVALMIN);
    SliceBoundCB(SETVALMAX);
    SliceBoundCB(VALMIN);
    SliceBoundCB(VALMAX);
    SliceBoundCB(SETCHOPMINVAL);
    SliceBoundCB(SETCHOPMAXVAL);
    SliceBoundCB(CHOPVALMIN);
    SliceBoundCB(CHOPVALMAX);
    if(nzoneinfo>0){
      if(strcmp(slicebounds[i].shortlabel, "TEMP")==0){
        BoundRolloutCB(ZONE_ROLLOUT);
        if(ROLLOUT_slice_bound!=NULL)ROLLOUT_slice_bound->disable();
      }
      else{
        if(ROLLOUT_slice_bound!=NULL)ROLLOUT_slice_bound->enable();
      }
    }
  }
}

/* ------------------ UpdateGlui ------------------------ */

extern "C" void UpdateGlui(void){
  GLUI_Master.sync_live_all();
}

/* ------------------ ShowGluiBounds ------------------------ */

extern "C" void ShowGluiBounds(int menu_id){
  if(menu_id==DIALOG_BOUNDS){
    if(nsliceinfo>0){
      int islice;

      islice=RADIO_slice->get_int_val();
      SliceBounds2Glui(islice);
      SliceBoundCB(SETVALMIN);
      SliceBoundCB(SETVALMAX);
      SliceBoundCB(VALMIN);
      SliceBoundCB(VALMAX);
    }
    if(npatchinfo>0){
      int ipatch;

      if(RADIO_bf == NULL){
        ipatch = list_patch_index;
      }
      else {
        ipatch = RADIO_bf->get_int_val();
      }
      Global2LocalBoundaryBounds(patchlabellist[ipatch]);
      BoundBoundCB(SETVALMIN);
      BoundBoundCB(SETVALMAX);
    }
    if(npartinfo>0&&npartinfo!=nevac){
      PartBoundCB(SETVALMIN);
      PartBoundCB(SETVALMAX);
    }
    if(nplot3dinfo>0){
      Plot3DBoundCB(SETVALMIN);
      Plot3DBoundCB(SETVALMAX);
    }

    if(nsliceinfo>0||npatchinfo>0)UpdateGlui();

    UpdateChar();
    FileRolloutCB(FILEBOUNDS_ROLLOUT);
  }
  else if(menu_id == DIALOG_SHOWFILES){
    FileRolloutCB(SHOWHIDE_ROLLOUT);
  }
  else if(menu_id==DIALOG_CONFIG){
    FileRolloutCB(CONFIG_ROLLOUT);
  }
  else if(menu_id==DIALOG_AUTOLOAD){
    FileRolloutCB(LOAD_ROLLOUT);
  }
  else if(menu_id==DIALOG_TIME){
    FileRolloutCB(TIME_ROLLOUT);
  }
  else if(menu_id==DIALOG_SCRIPT){
    FileRolloutCB(SCRIPT_ROLLOUT);
  }
  else if(menu_id == DIALOG_SMOKEZIP){
    FileRolloutCB(COMPRESS_ROLLOUT);
  }
  else if(menu_id == DIALOG_3DSMOKE){
    FileRolloutCB(FILEBOUNDS_ROLLOUT);
    BoundRolloutCB(SMOKE3D_ROLLOUT);
  }
  glui_bounds->show();
}


/* ------------------ ShowBoundsDialog ------------------------ */

extern "C" void ShowBoundsDialog(int type){
  ShowGluiBounds(DIALOG_3DSMOKE);
  switch (type){
    case DLG_3DSMOKE:
      if(ROLLOUT_smoke3d!=NULL)ROLLOUT_smoke3d->open();
      break;
    case DLG_BOUNDARY:
      if(ROLLOUT_bound!=NULL)ROLLOUT_bound->open();
      break;
    case DLG_SLICE:
      if(ROLLOUT_slice != NULL)ROLLOUT_slice->open();
      break;
    case DLG_PART:
      if(ROLLOUT_part!=NULL)ROLLOUT_part->open();
      break;
    case DLG_PLOT3D:
      if(ROLLOUT_plot3d!=NULL)ROLLOUT_plot3d->open();
      break;
    case DLG_ISO:
      if(ROLLOUT_iso!=NULL)ROLLOUT_iso->open();
      break;
  }
}

/* ------------------ EnableBoundaryGlui ------------------------ */

extern "C" void EnableBoundaryGlui(void){
  ROLLOUT_boundary_bound->enable();
}

/* ------------------ DisableBoundaryGlui ------------------------ */

extern "C" void DisableBoundaryGlui(void){
  ROLLOUT_boundary_bound->disable();
}

/* ------------------ UpdateOverwrite ------------------------ */

extern "C" void UpdateOverwrite(void){
  if(CHECKBOX_overwrite_all!=NULL)CHECKBOX_overwrite_all->set_int_val(overwrite_all);
  if(CHECKBOX_compress_autoloaded!=NULL)CHECKBOX_compress_autoloaded->set_int_val(compress_autoloaded);
}

/* ------------------ HideGluiBounds ------------------------ */

extern "C" void HideGluiBounds(void){
  CloseRollouts(glui_bounds);
}

/* ------------------ UpdateVectorWidgets ------------------------ */

extern "C" void UpdateVectorWidgets(void){
  Plot3DBoundCB(UPDATE_VECTOR_FROM_SMV);
  SliceBoundCB(UPDATE_VECTOR_FROM_SMV);
}

/* ------------------ UpdatePlot3dDisplay ------------------------ */

extern "C" void UpdatePlot3dDisplay(void){
  if(RADIO_plot3d_display!=NULL)RADIO_plot3d_display->set_int_val(contour_type);
}

/* ------------------ UpdateGluiTimeBounds ------------------------ */

extern "C" void UpdateGluiTimeBounds(float time_min, float time_max){
  if(SPINNER_timebounds!=NULL){
    SPINNER_timebounds->set_float_limits(time_min,time_max);
  }
}

/* ------------------ UpdateTBounds ------------------------ */

extern "C" void UpdateTBounds(void){
  settmin_p=use_tload_begin;
  settmax_p=use_tload_end;
  tmin_p=tload_begin;
  tmax_p=tload_end;

  settmin_s=use_tload_begin;
  settmax_s=use_tload_end;
  tmin_s=tload_begin;
  tmax_s=tload_end;

  settmin_i=use_tload_begin;
  settmax_i=use_tload_end;
  tmin_i=tload_begin;
  tmax_i=tload_end;

  settmin_s=use_tload_begin;
  settmax_s=use_tload_end;
  tmin_s=tload_begin;
  tmax_s=tload_end;

  settmin_b=use_tload_begin;
  settmax_b=use_tload_end;
  tmin_b=tload_begin;
  tmax_b=tload_end;

  if(use_tload_skip==1){
    smoke3dframeskip=tload_skip;
    boundframeskip=tload_skip;
    isoframeskip_global=tload_skip;
    partframeskip=tload_skip;
    evacframeskip=tload_skip;
    sliceframeskip=tload_skip;
  }
  else{
    smoke3dframeskip=0;
    boundframeskip=0;
    isoframeskip_global=0;
    partframeskip=0;
    evacframeskip=0;
    sliceframeskip=0;
  }

  Smoke3dBoundCB(FRAMELOADING);
  BoundBoundCB(FRAMELOADING);
  IsoBoundCB(FRAMELOADING);
  PartBoundCB(FRAMELOADING);
  SliceBoundCB(FRAMELOADING);
}

/* ------------------ UpdateShowHideButtons ------------------------ */

extern "C" void UpdateShowHideButtons(void){

//  if(CHECKBOX_label_3 != NULL){
//    CHECKBOX_label_3->set_int_val(hide_overlaps);
//  }
  if(BUTTON_PART != NULL){
    if(npartloaded == 0){
      BUTTON_PART->disable();
    }
    else{
      BUTTON_PART->enable();
    }
  }

  if(BUTTON_SLICE != NULL){
    if(nsliceloaded == 0){
      BUTTON_SLICE->disable();
    }
    else{
      BUTTON_SLICE->enable();
    }
  }

  if(BUTTON_VSLICE != NULL){
    if(nvsliceloaded == 0){
      BUTTON_VSLICE->disable();
    }
    else{
      BUTTON_VSLICE->enable();
    }
  }

  if(BUTTON_ISO != NULL){
    if(nisoloaded == 0){
      BUTTON_ISO->disable();
    }
    else{
      BUTTON_ISO->enable();
    }
  }

  if(BUTTON_BOUNDARY != NULL){
    if(npatchloaded == 0){
      BUTTON_BOUNDARY->disable();
    }
    else{
      BUTTON_BOUNDARY->enable();
    }
  }

  if(BUTTON_3DSMOKE != NULL){
    if(nsmoke3dloaded == 0){
      BUTTON_3DSMOKE->disable();
    }
    else{
      BUTTON_3DSMOKE->enable();
    }
  }

  if(BUTTON_PLOT3D != NULL){
    if(nplot3dloaded == 0){
      BUTTON_PLOT3D->disable();
    }
    else{
      BUTTON_PLOT3D->enable();
    }
  }

  if(nplot3dloaded == 0 && nsmoke3dloaded == 0 && nisoloaded == 0 && nsliceloaded == 0 && npartloaded == 0 && npatchloaded == 0){
    if(RADIO_showhide != NULL)RADIO_showhide->disable();
  }
  else{
    if(RADIO_showhide != NULL)RADIO_showhide->enable();
  }
}
