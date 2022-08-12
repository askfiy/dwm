#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 5, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 5;   /* systray spacing，default: 2 */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 0;     /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "agave Nerd Font:size=14", "JoyPixels:size=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "agave Nerd Font:size=14";
static const char normal_fg[]       = "#D9E0EE";
static const char normal_bg[]       = "#1E1E2E";
static const char normal_bd[]       = "#575268";
static const char focus_fg[]        = "#D9E0EE";
static const char focus_bg[]        = "#575268";
static const char focus_bd[]        = "#96CDFB";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normal_fg, normal_bg, normal_bd },
	[SchemeSel]  = { focus_fg,  focus_bg,  focus_bd  },
};

/* tagging */
static const char *tags[] = { " ", " ", " ", " ", " ", " ", " ", " ", " " };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                     instance    title       tags mask     isfloating   monitor */
	{"Wine",                      NULL,      NULL,       1 << 7,       1,              -1},
	{"picgo",                     NULL,      NULL,       1 << 8,       1,              -1},
	{"Clash for Windows",         NULL,      NULL,       1 << 8,       1,              -1},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "ﰦ ",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ " ",      monocle },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "ulauncher", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "180x40", NULL };

// voice control
#define XF86_F1 0xffbe
#define XF86_F2 0xffbf
#define XF86_F3 0xffc0

static const char *incr_volume[] = { "amixer", "sset", "Master", "5%+", "unmute", NULL };
static const char *decr_volume[] = { "amixer", "sset", "Master", "5%-", "unmute", NULL };
static const char *toggle_volume[] = { "amixer", "sset", "Master", "toggle", NULL };

// screen backlight brightness adjustment
#define XF86_F5 0xffc2
#define XF86_F6 0xffc3

static const char *incr_backlight[] = { "xbacklight", "-inc", "10", NULL };
static const char *decr_backlight[] = { "xbacklight", "-dec", "10", NULL };

// disable or enable Touchpad
/*
You can see your touchpad id using xinput list
*/
#define XF86_F10 0xffc7
#define XF86_F11 0xffc8

static const char *enable_touchpad[] = { "xinput", "enable", "12", NULL };
static const char *disable_touchpad[] = { "xinput", "disable", "12", NULL };

// switch display device
#define XF86_LF 0x5b
#define XF86_RF 0x5d

static const char *display_to_edp01[] = {"xrandr", "--output", "DP-1", "--off", "--output", "eDP-1", "--auto", NULL };
static const char *display_to_dp01[] = {"xrandr", "--output", "DP-1", "--mode", "1920x1080", "--rate", "60", "--output", "eDP-1", "--off", NULL };

// if xinput list-props 12 | grep 'Device Enabled ([[:digit:]]\+):\s*1' >/dev/null; then xinput disable 12; else xinput enable 12; fi

// screenshot
static const char *flameshot_gui[] = { "flameshot", "gui", NULL };

// static const char *scrot_to_clipboard[] = {
// 	"scrot",
// 	"-s",
// 	"/tmp/scrot_%F_%T_$wx$h.png",
// 	"-e",
// 	"xclip -selection clipboard -target image/png -i $f",
// 	NULL 
// };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_o,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ ShiftMask,                    XF86_F2,    spawn,          {.v = decr_volume } },
	{ ShiftMask,                    XF86_F3,    spawn,          {.v = incr_volume } },
	{ ShiftMask,                    XF86_F1,    spawn,          {.v = toggle_volume } },
	{ ShiftMask,                    XF86_F5,    spawn,          {.v = decr_backlight } },
	{ ShiftMask,                    XF86_F6,    spawn,          {.v = incr_backlight } },
	{ ShiftMask,                    XF86_F10,   spawn,          {.v = enable_touchpad } },
	{ ShiftMask,                    XF86_F11,   spawn,          {.v = disable_touchpad } },
	{ MODKEY,                       XF86_LF,    spawn,          {.v = display_to_edp01 } },
	{ MODKEY,                       XF86_RF,    spawn,          {.v = display_to_dp01 } },
	// { Mod1Mask,                     XK_a,      spawn,          {.v = scrot_to_clipboard } },
	{ Mod1Mask,                     XK_a,      spawn,          {.v = flameshot_gui} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
