/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#1c1c1c";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#c5c5c5";
static const char col_cyan[]        = "#048ac7";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_cyan, col_gray1,  col_cyan  },
};

/* tagging */
static const char *tags[] = {"", "", "", "", "5","6", "7", "8", "9"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{"Gimp",  NULL,       NULL,       1 << 8,       0,           -1 },
    	{"Stremio", NULL, NULL, 1 << 3, 0, -1},
    	{"feh", NULL, NULL, 0, 1,  -1},
    	{"Qalculate-gtk", NULL, NULL, 0, 1,  -1},
    	{NULL, "Toolkit", NULL, 0, 1, -1},
    	{"lxpolkit", NULL, NULL, 0, 1, -1},
    	{"Lxpolkit", NULL, NULL, 0, 1, -1},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define TERMINAL "st"
#define BROWSER "browser"

#include <X11/XF86keysym.h>
/* commands */
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ 0,	                	XF86XK_Launch3, spawn,     {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  zoom,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	
	// MEDIA
	
    	{MODKEY, 			XK_z, 	   spawn,         SHCMD("playerctl play-pause --player=spotify")},
    	{MODKEY | ShiftMask, 		XK_z,      spawn, 	  SHCMD("playerctl play-pause")},
    	{MODKEY, XK_Up, spawn, SHCMD("amixer -D pulse sset 'Master' 5%+")},
    	{MODKEY, XK_Down, spawn, SHCMD("amixer -D pulse sset 'Master' 5%-")},
    	{0, XF86XK_AudioRaiseVolume, spawn, SHCMD("amixer -D pulse sset 'Master' 5%+")},
    	{0, XF86XK_AudioLowerVolume, spawn, SHCMD("amixer -D pulse sset 'Master' 5%-")},
    	{0, XF86XK_AudioMute, spawn, SHCMD("amixer -D pulse sset 'Master' toggle")},
    	{MODKEY | ShiftMask, XK_Left, spawn, SHCMD("playerctl previous")},
    	{MODKEY | ShiftMask, XK_Right, spawn, SHCMD("playerctl next")},
    	{MODKEY , XK_Left,  spawn, SHCMD("playerctl previous --player=spotify")},
    	{MODKEY , XK_Right, spawn, SHCMD("playerctl next --player=spotify")},
    	{MODKEY, XK_x, spawn, SHCMD("medcontrol")},
    	{MODKEY, XK_p, spawn, SHCMD("stremio")},
    	{MODKEY, XK_m, spawn, SHCMD("spotify")},

	// APPS

    	{MODKEY, XK_d, spawn, SHCMD("dmenu_run_history")},
    	{MODKEY, XK_e, spawn, SHCMD(TERMINAL " nnn -a")},
    	{MODKEY, XK_h, spawn, SHCMD("cheat.sh")},
    	{MODKEY, XK_f, spawn, SHCMD(BROWSER)},
    	{MODKEY | ShiftMask, XK_r, spawn, SHCMD(TERMINAL " htop")},

	// UTILS
	
    	{MODKEY, XK_c, spawn, SHCMD("clipmenu")},
    	{MODKEY, XK_l, spawn, SHCMD("lockscreen.sh")},
    	{0, XK_Scroll_Lock, spawn, SHCMD("suspend.sh")},

	// GAPS
	
	{ MODKEY,                       XK_KP_Subtract,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_KP_Add,  setgaps,        {.i = +1 } },

	// SCREENSHOT
	
    	{0, XK_Print, spawn, SHCMD("flameshot gui")},
	{MODKEY, XK_Print, spawn, SHCMD("flameshot full -p ~/Pictures -c")},

	// BACKLIGHT
    	{0, XF86XK_MonBrightnessUp, spawn, SHCMD("xbacklight -inc 10")},
    	{0, XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 10")},

};


#include "shiftview.c"

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ClkTagBar, 0, Button4, shiftview, {.i = -1}},
	{ClkTagBar, 0, Button5, shiftview, {.i = 1}},


};

