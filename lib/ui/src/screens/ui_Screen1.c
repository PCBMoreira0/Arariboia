// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: DisplayArariboia-ILI9488

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Panel2 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel2, 284);
    lv_obj_set_height(ui_Panel2, 303);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x081A48), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RPM_Monitor_Container = lv_obj_create(ui_Panel2);
    lv_obj_remove_style_all(ui_RPM_Monitor_Container);
    lv_obj_set_width(ui_RPM_Monitor_Container, 222);
    lv_obj_set_height(ui_RPM_Monitor_Container, 266);
    lv_obj_set_align(ui_RPM_Monitor_Container, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_RPM_Monitor_Container, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_RPM_R_Container = lv_obj_create(ui_RPM_Monitor_Container);
    lv_obj_remove_style_all(ui_RPM_R_Container);
    lv_obj_set_width(ui_RPM_R_Container, 93);
    lv_obj_set_height(ui_RPM_R_Container, 152);
    lv_obj_set_align(ui_RPM_R_Container, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(ui_RPM_R_Container, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_RPM_R_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_RPM_R_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_RPM_R_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_RPM_R_Container, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MonitorPanel = ui_MonitorPanel_create(ui_RPM_R_Container);
    lv_obj_set_x(ui_MonitorPanel, 0);
    lv_obj_set_y(ui_MonitorPanel, 20);

    ui_RPM_L = lv_label_create(ui_MonitorPanel);
    lv_obj_set_width(ui_RPM_L, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RPM_L, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_RPM_L, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RPM_L, "9999");
    lv_obj_set_style_text_color(ui_RPM_L, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RPM_L, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RPM_L, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RPM_L_Text = lv_label_create(ui_RPM_R_Container);
    lv_obj_set_width(ui_RPM_L_Text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RPM_L_Text, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_RPM_L_Text, "RPM L");
    lv_obj_set_style_text_color(ui_RPM_L_Text, lv_color_hex(0xFFF9F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RPM_L_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RPM_L_Text, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MonitorPanel4 = ui_MonitorPanel_create(ui_RPM_R_Container);
    lv_obj_set_x(ui_MonitorPanel4, 0);
    lv_obj_set_y(ui_MonitorPanel4, 0);
    lv_obj_set_align(ui_MonitorPanel4, LV_ALIGN_BOTTOM_MID);

    ui_Current_RPM_L = lv_label_create(ui_MonitorPanel4);
    lv_obj_set_width(ui_Current_RPM_L, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Current_RPM_L, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Current_RPM_L, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Current_RPM_L, "000");
    lv_obj_set_style_text_color(ui_Current_RPM_L, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Current_RPM_L, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Current_RPM_L, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Current_RPM_L_Text = lv_label_create(ui_RPM_R_Container);
    lv_obj_set_width(ui_Current_RPM_L_Text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Current_RPM_L_Text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Current_RPM_L_Text, 0);
    lv_obj_set_y(ui_Current_RPM_L_Text, -35);
    lv_obj_set_align(ui_Current_RPM_L_Text, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_Current_RPM_L_Text, "Corrente L");
    lv_obj_set_style_text_color(ui_Current_RPM_L_Text, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Current_RPM_L_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Current_RPM_L_Text, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RPM_Warning = lv_obj_create(ui_RPM_Monitor_Container);
    lv_obj_set_width(ui_RPM_Warning, 24);
    lv_obj_set_height(ui_RPM_Warning, 24);
    lv_obj_set_x(ui_RPM_Warning, 0);
    lv_obj_set_y(ui_RPM_Warning, 8);
    lv_obj_set_align(ui_RPM_Warning, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_RPM_Warning, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_RPM_Warning, 45, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RPM_Warning, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RPM_Warning, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RPM_L_Container = lv_obj_create(ui_RPM_Monitor_Container);
    lv_obj_remove_style_all(ui_RPM_L_Container);
    lv_obj_set_width(ui_RPM_L_Container, 93);
    lv_obj_set_height(ui_RPM_L_Container, 152);
    lv_obj_set_align(ui_RPM_L_Container, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(ui_RPM_L_Container, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_RPM_L_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_RPM_L_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_RPM_L_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_RPM_L_Container, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MonitorPanel1 = ui_MonitorPanel_create(ui_RPM_L_Container);
    lv_obj_set_x(ui_MonitorPanel1, 0);
    lv_obj_set_y(ui_MonitorPanel1, 18);

    ui_RPM_R = lv_label_create(ui_MonitorPanel1);
    lv_obj_set_width(ui_RPM_R, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RPM_R, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_RPM_R, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RPM_R, "9999");
    lv_obj_set_style_text_color(ui_RPM_R, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RPM_R, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RPM_R, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MonitorPanel5 = ui_MonitorPanel_create(ui_RPM_L_Container);
    lv_obj_set_x(ui_MonitorPanel5, 0);
    lv_obj_set_y(ui_MonitorPanel5, 0);
    lv_obj_set_align(ui_MonitorPanel5, LV_ALIGN_BOTTOM_MID);

    ui_Current_RPM_R = lv_label_create(ui_MonitorPanel5);
    lv_obj_set_width(ui_Current_RPM_R, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Current_RPM_R, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Current_RPM_R, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Current_RPM_R, "000");
    lv_obj_set_style_text_color(ui_Current_RPM_R, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Current_RPM_R, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Current_RPM_R, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RPM_R_Text = lv_label_create(ui_RPM_L_Container);
    lv_obj_set_width(ui_RPM_R_Text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RPM_R_Text, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_RPM_R_Text, "RPM R");
    lv_obj_set_style_text_color(ui_RPM_R_Text, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RPM_R_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RPM_R_Text, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Current_RPM_R_Text = lv_label_create(ui_RPM_L_Container);
    lv_obj_set_width(ui_Current_RPM_R_Text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Current_RPM_R_Text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Current_RPM_R_Text, 0);
    lv_obj_set_y(ui_Current_RPM_R_Text, -35);
    lv_obj_set_align(ui_Current_RPM_R_Text, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_Current_RPM_R_Text, "Corrente R");
    lv_obj_set_style_text_color(ui_Current_RPM_R_Text, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Current_RPM_R_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Current_RPM_R_Text, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel1, 196);
    lv_obj_set_height(ui_Panel1, 303);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0xFD5401), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Battery_and_Sola_Panel_Container = lv_obj_create(ui_Panel1);
    lv_obj_remove_style_all(ui_Battery_and_Sola_Panel_Container);
    lv_obj_set_width(ui_Battery_and_Sola_Panel_Container, 93);
    lv_obj_set_height(ui_Battery_and_Sola_Panel_Container, 152);
    lv_obj_set_align(ui_Battery_and_Sola_Panel_Container, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Battery_and_Sola_Panel_Container, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_Battery_and_Sola_Panel_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Battery_and_Sola_Panel_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Battery_and_Sola_Panel_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Battery_and_Sola_Panel_Container, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MonitorPanel2 = ui_MonitorPanel_create(ui_Battery_and_Sola_Panel_Container);
    lv_obj_set_x(ui_MonitorPanel2, 0);
    lv_obj_set_y(ui_MonitorPanel2, 18);
    lv_obj_set_style_bg_color(ui_MonitorPanel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MonitorPanel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Battery_Value = lv_label_create(ui_MonitorPanel2);
    lv_obj_set_width(ui_Battery_Value, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Battery_Value, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Battery_Value, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Battery_Value, "9999");
    lv_obj_set_style_text_font(ui_Battery_Value, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Battery_Text = lv_label_create(ui_Battery_and_Sola_Panel_Container);
    lv_obj_set_width(ui_Battery_Text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Battery_Text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Battery_Text, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Battery_Text, "Tensao");
    lv_obj_set_style_text_font(ui_Battery_Text, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MonitorPanel3 = ui_MonitorPanel_create(ui_Battery_and_Sola_Panel_Container);
    lv_obj_set_x(ui_MonitorPanel3, 0);
    lv_obj_set_y(ui_MonitorPanel3, 0);
    lv_obj_set_align(ui_MonitorPanel3, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(ui_MonitorPanel3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MonitorPanel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Solar_Panel_Value = lv_label_create(ui_MonitorPanel3);
    lv_obj_set_width(ui_Solar_Panel_Value, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Solar_Panel_Value, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Solar_Panel_Value, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Solar_Panel_Value, "9999");
    lv_obj_set_style_text_font(ui_Solar_Panel_Value, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Solar_Panel_Text = lv_label_create(ui_Battery_and_Sola_Panel_Container);
    lv_obj_set_width(ui_Solar_Panel_Text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Solar_Panel_Text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Solar_Panel_Text, 0);
    lv_obj_set_y(ui_Solar_Panel_Text, -35);
    lv_obj_set_align(ui_Solar_Panel_Text, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Solar_Panel_Text, "Corrente Painel");
    lv_obj_set_style_text_font(ui_Solar_Panel_Text, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel3 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel3, 480);
    lv_obj_set_height(ui_Panel3, 17);
    lv_obj_set_align(ui_Panel3, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Panel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image1, &ui_img_arariboialogopcn_png);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 128
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 128
    lv_obj_set_x(ui_Image1, 44);
    lv_obj_set_y(ui_Image1, -45);
    lv_obj_set_align(ui_Image1, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image1, 80);

    lv_obj_add_event_cb(ui_Screen1, ui_event_Screen1, LV_EVENT_ALL, NULL);

}
