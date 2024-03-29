// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: DisplayArariboia-ILI9488

#include "../ui.h"


// COMPONENT MonitorPanel

lv_obj_t * ui_MonitorPanel_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_MonitorPanel;
    cui_MonitorPanel = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_MonitorPanel, 82);
    lv_obj_set_height(cui_MonitorPanel, 32);
    lv_obj_set_x(cui_MonitorPanel, 0);
    lv_obj_set_y(cui_MonitorPanel, 20);
    lv_obj_set_align(cui_MonitorPanel, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(cui_MonitorPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(cui_MonitorPanel, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cui_MonitorPanel, lv_color_hex(0x2C2C2C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_MonitorPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(cui_MonitorPanel, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(cui_MonitorPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(cui_MonitorPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(cui_MonitorPanel, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_MONITORPANEL_NUM);
    children[UI_COMP_MONITORPANEL_MONITORPANEL] = cui_MonitorPanel;
    lv_obj_add_event_cb(cui_MonitorPanel, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_MonitorPanel, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_MonitorPanel_create_hook(cui_MonitorPanel);
    return cui_MonitorPanel;
}

