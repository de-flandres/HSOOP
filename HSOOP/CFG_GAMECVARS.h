/*

#pragma once

const int rate = 100000; // 100000
const DWORD dw_rate = 0xCAB00;	// engine.dll

const int cl_cmdrate = 100; //100
const DWORD dw_cl_cmdrate = 0x3CAAB8;	// engine.dll

const int cl_updaterate = 100; // 100
const DWORD dw_cl_updaterate = 0x3CAB50;	// engine.dll

const float cl_interp_ratio = 0.0f; // 0
const DWORD dw_cl_interp_ratio = 0x54B97C;	// client.dll

const float cl_interp = 0.0f; // 0
const DWORD dw_cl_interp = 0x54B9C4;	// client.dll

const float cl_resend = 4.0f; // 4
const DWORD dw_cl_resend = 0x40D07C;	// engine.dll

const int cl_lagcompensation = 1; // 1
const DWORD dw_cl_lagcompensation = 0x5913E0;	// client.dll

const int cl_timeout = 30;
const DWORD dw_cl_timeout = 0x41CF18;	// engine.dll

const float net_maxroutable = 1200.0f; // 1200
const DWORD dw_net_maxroutable = 0x40215C;	// engine.dll

const int net_splitrate = 30; // 30
const DWORD dw_net_splitrate = 0x4025E0;	// engine.dll

const int net_splitpacket_maxrate = 30000; // 30000
const DWORD dw_net_splitpacket_maxrate = 0x402508;	// engine.dll

// ---------------------------------------------------------------------------- //

const int cl_forcepreload = 1;
const DWORD dw_cl_forcepreload = 0x41CFF0;	// engine.dll

const int cl_ragdoll_limit = 0;
const DWORD dw_cl_ragdoll_limit = 0x5A2160;	// client.dll

const int con_enable = 1;
const DWORD dw_con_enable = 0x41D658;	// engine.dll

const int dsp_enhance_stereo = 1;
const DWORD dw_dsp_enhance_stereo = 0x5ABD90;	// engine.dll

const int func_break_max_pieces = 0;
const DWORD dw_func_break_max_pieces = 0x59F898;	// client.dll

const float mat_monitorgamma_tv_enabled = 1.0f;
const DWORD dw_mat_monitorgamma_tv_enabled = 0xEF4B4;	// materialsystem.dll

const float mat_grain_scale_override = 0.0f;
const DWORD dw_mat_grain_scale_override = 0x761B4;	// stdshader_dx9.dll

const int spec_allowroaming = 1;
const DWORD dw_spec_allowroaming = 0x5A1420;	// client.dll

const int sk_autoaim_mode = 2;
const DWORD dw_sk_autoaim_mode = 0x5699B8;	// client.dll

// ---------------------------------------------------------------------------- //

const int m_rawinput = 1;
const DWORD dw_m_rawinput = 0x56EFB8;	// client.dll

const int m_filter = 0;
const DWORD dw_m_filter = 0x56F048;	// client.dll

const int m_mouseaccel1 = 0;
const DWORD dw_m_mouseaccel1 = 0x56F000;	// client.dll

const int m_mouseaccel2 = 0;
const DWORD dw_m_mouseaccel2 = 0x56EF70;	// client.dll

const int m_customaccel = 0;
const DWORD dw_m_customaccel = 0x56F240;	// client.dll

const float m_mousespeed = 0.0f;
const DWORD dw_m_mousespeed = 0x56F35C;	// client.dll

const float m_pitch = 0.022f;
const DWORD dw_m_pitch = 0x56F164;	// client.dll

const float m_yaw = 0.022f;
const DWORD dw_m_yaw = 0x56F1AC;	// client.dll

// ---------------------------------------------------------------------------- //

const int cl_autohelp = 0;
const DWORD dw_cl_autohelp = 0x5A3B78;	// client.dll

const int gameinstructor_enable = 0;
const DWORD dw_gameinstructor_enable = 0x545E90;	// client.dll

const int cl_hidemenu_spawnmode = 5;
const DWORD dw_cl_hidemenu_spawnmode = 0x5B9CB8;	// client.dll

const int cl_hidemenu_spawnclass_hunter = 5;
const DWORD dw_cl_hidemenu_spawnclass_hunter = 0x5B9D00;	// client.dll

const int cl_hidemenu_spawnclass_smoker = 5;
const DWORD dw_cl_hidemenu_spawnclass_smoker = 0x5B9D48;	// client.dll

const int cl_hidemenu_spawnclass_boomer = 5;
const DWORD dw_cl_hidemenu_spawnclass_boomer = 0x5B9D90;	// client.dll

// ---------------------------------------------------------------------------- //

const float cl_glow_item_r = 0.0f;
const DWORD dw_cl_glow_item_r = 0x5B37D4;	// client.dll

const float cl_glow_item_g = 1.0f;
const DWORD dw_cl_glow_item_g = 0x5B381C;	// client.dll

const float cl_glow_item_b = 0.0f;
const DWORD dw_cl_glow_item_b = 0x5B3864;	// client.dll

const float cl_glow_item_far_r = 1.0f;
const DWORD dw_cl_glow_item_far_r = 0x5B38AC;	// client.dll

const float cl_glow_item_far_g = 0.7f;
const DWORD dw_cl_glow_item_far_g = 0x5B38F4;	// client.dll

const float cl_glow_item_far_b = 0.0f;
const DWORD dw_cl_glow_item_far_b = 0x5B393C;	// client.dll

const float cl_glow_survivor_hurt_r = 1.0f;
const DWORD dw_cl_glow_survivor_hurt_r = 0x5AC39C;	// client.dll

const float cl_glow_survivor_hurt_g = 0.0f;
const DWORD dw_cl_glow_survivor_hurt_g = 0x5AC3E4;	// client.dll

const float cl_glow_survivor_hurt_b = 0.0f;
const DWORD dw_cl_glow_survivor_hurt_b = 0x5AC42C;	// client.dll

const float cl_glow_survivor_vomit_r = 0.9f;
const DWORD dw_cl_glow_survivor_vomit_r = 0x5AC474;	// client.dll

const float cl_glow_survivor_vomit_g = 0.0f;
const DWORD dw_cl_glow_survivor_vomit_g = 0x5AC4BC;	// client.dll

const float cl_glow_survivor_vomit_b = 0.9f;
const DWORD dw_cl_glow_survivor_vomit_b = 0x5AC504;	// client.dll

const float cl_glow_ghost_infected_r = 0.55f;
const DWORD dw_cl_glow_ghost_infected_r = 0x5AC114;	// client.dll

const float cl_glow_ghost_infected_g = 0.55f;
const DWORD dw_cl_glow_ghost_infected_g = 0x5AC15C;	// client.dll

const float cl_glow_ghost_infected_b = 0.55f;
const DWORD dw_cl_glow_ghost_infected_b = 0x5AC1A4;	// client.dll

const float cl_glow_infected_r = 0.0f;
const DWORD dw_cl_glow_infected_r = 0x5AC03C;	// client.dll

const float cl_glow_infected_g = 0.5f;
const DWORD dw_cl_glow_infected_g = 0x5AC084;	// client.dll

const float cl_glow_infected_b = 1.0f;
const DWORD dw_cl_glow_infected_b = 0x5AC0CC;	// client.dll

const float cl_glow_infected_vomit_r = 0.9f;
const DWORD dw_cl_glow_infected_vomit_r = 0x5AC1EC;	// client.dll

const float cl_glow_infected_vomit_g = 0.0f;
const DWORD dw_cl_glow_infected_vomit_g = 0x5AC234;	// client.dll

const float cl_glow_infected_vomit_b = 0.9f;
const DWORD dw_cl_glow_infected_vomit_b = 0x5AC27C;	// client.dll

const float cl_glow_survivor_r = 0.0f;
const DWORD dw_cl_glow_survivor_r = 0x5AC2C4;	// client.dll

const float cl_glow_survivor_g = 0.5f;
const DWORD dw_cl_glow_survivor_g = 0x5AC30C;	// client.dll

const float cl_glow_survivor_b = 1.0f;
const DWORD dw_cl_glow_survivor_b = 0x5AC354;	// client.dll

const float cl_glow_survivor_health_high_r = 0.0f;
const DWORD dw_cl_glow_survivor_health_high_r = 0x5AC8AC;	// client.dll

const float cl_glow_survivor_health_high_g = 1.0f;
const DWORD dw_cl_glow_survivor_health_high_g = 0x5AC8F4;	// client.dll

const float cl_glow_survivor_health_high_b = 0.0f;
const DWORD dw_cl_glow_survivor_health_high_b = 0x5AC93C;	// client.dll

const float cl_glow_survivor_health_med_r = 1.0f;
const DWORD dw_cl_glow_survivor_health_med_r = 0x5AC6FC;	// client.dll

const float cl_glow_survivor_health_med_g = 1.0f;
const DWORD dw_cl_glow_survivor_health_med_g = 0x5AC744;	// client.dll

const float cl_glow_survivor_health_med_b = 0.0f;
const DWORD dw_cl_glow_survivor_health_med_b = 0x5AC78C;	// client.dll

const float cl_glow_survivor_health_low_r = 1.0f;
const DWORD dw_cl_glow_survivor_health_low_r = 0x5AC54C;	// client.dll

const float cl_glow_survivor_health_low_g = 0.0f;
const DWORD dw_cl_glow_survivor_health_low_g = 0x5AC594;	// client.dll

const float cl_glow_survivor_health_low_b = 0.0f;
const DWORD dw_cl_glow_survivor_health_low_b = 0x5AC5DC;	// client.dll

*/