/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 6;        /* border pixel of windows */
static const unsigned int gappx     = 50;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const char *upvol[]   = { "amixer", "set", "Master", "3%+",     NULL };
static const char *downvol[] = { "amixer", "set", "Master", "3%-",     NULL };
static const char *mutevol[] = { "amixer", "set", "Master", "toggle", NULL };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title                         tags mask   isfloating   monitor */
	//{ "Gimp",     NULL,       NULL,                       0,          1,           -1 },
	{ NULL,       NULL,       "scratchpad",                 0,          1,           -1,       's' },
	{ NULL,       NULL,       "Settings",                   0,          1,           -1},
	{ NULL,       NULL,       "GTick 0.5.4",                0,          1,           -1},
	{ NULL,       NULL,       "Base Converter",             0,          1,           -1},
};

#include "horizgrid.c"
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "###",      horizgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* additional mouse button definitions */
#define Button6 6
#define Button7 7
#define Button8 8
#define Button9 9

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  =   { "st", NULL };
static const char *suscmd[]  =    { "systemctl", "suspend", NULL };
static const char *offcmd[]  =    { "systemctl", "poweroff", NULL };
static const char *rebootcmd[]  = { "systemctl", "reboot", NULL };
static const char *webcmd[]  =    { "firefox", NULL };
static const char *msgcmd[]  =    { "discord", NULL };
static const char *zoomcmd[]  =   { "zoom", NULL };
static const char *gimpcmd[]  =    { "gimp", NULL };
static const char *scancmd[]  =   { "scan", NULL };
static const char *vlccmd[]  =    { "vlc", NULL };
static const char *slackcmd[]  =  { "slack", NULL };
static const char *spotifycmd[] = {"spotify", NULL};
static const char *devhelpcmd[]  =  { "devhelp", NULL };
static const char *translatecmd[]  =  { "google-translate", NULL };
static const char *messengercmd[]  =  { "caprine", NULL };
static const char *playpausecmd[]  =  { "playerctl", "play-pause", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", "-g", "100x30+100+100", "-f", "Monospace:14", "-e", "/bin/bash", "--init-file", "/home/regular/Sync/code/src/shell/scratch_init.sh", NULL};

static Key keys[] = {
	/* modifier                     key            function        argument */
	{ MODKEY,                       XK_r,          spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,     spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,          spawn_notify,   {.v = webcmd } },
	{ MODKEY,                       XK_s,          spawn_notify,   {.v = msgcmd } },
	{ MODKEY,                       XK_z,          spawn_notify,   {.v = zoomcmd } },
	{ MODKEY,                       XK_g,          spawn_notify,   {.v = gimpcmd } },
	{ MODKEY,                       XK_grave,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,          togglebar,      {0} },
	{ MODKEY,                       XK_j,          focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,     zoom,           {0} },
    { MODKEY,                       XK_Tab,        view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,     {0} },
	{ MODKEY,                       XK_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_h,          setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating, {0} },
	{ MODKEY,                       XK_0,          view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_period,     focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_minus,      setgaps,        {.i = -15 } },
	{ MODKEY,                       XK_equal,      setgaps,        {.i = +15 } },
	{ MODKEY|ShiftMask,             XK_equal,      setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_F12,        spawn,          {.v = suscmd } },
	{ MODKEY|ShiftMask,             XK_F12,        spawn,          {.v = offcmd } },
	{ MODKEY,                       XK_F11,        spawn,          {.v = rebootcmd } },
	{ MODKEY,                       XK_F5,         spawn,          {.v = scancmd } },
	{ MODKEY,                       XK_v,          spawn_notify,   {.v = vlccmd } },
	{ MODKEY,                       XK_a,          spawn_notify,   {.v = slackcmd } },
	{ MODKEY,                       XK_c,          spawn_notify,   {.v = spotifycmd } },
	{ MODKEY,                       XK_e,          spawn_notify,   {.v = devhelpcmd } },
	{ MODKEY,                       XK_n,          spawn_notify,   {.v = translatecmd } },
	{ MODKEY,                       XK_p,          spawn_notify,   {.v = messengercmd } },
 	{ MODKEY,                       XK_Down,       moveresize,     {.v = "0x 150y 0w 0h" } },
 	{ MODKEY,                       XK_Up,         moveresize,     {.v = "0x -150y 0w 0h" } },
 	{ MODKEY,                       XK_Right,      moveresize,     {.v = "150x 0y 0w 0h" } },
 	{ MODKEY,                       XK_Left,       moveresize,     {.v = "-150x 0y 0w 0h" } },
 	{ MODKEY|ShiftMask,             XK_Down,       moveresize,     {.v = "0x 0y 0w 150h" } },
 	{ MODKEY|ShiftMask,             XK_Up,         moveresize,     {.v = "0x 0y 0w -150h" } },
 	{ MODKEY|ShiftMask,             XK_Right,      moveresize,     {.v = "0x 0y 150w 0h" } },
 	{ MODKEY|ShiftMask,             XK_Left,       moveresize,     {.v = "0x 0y -150w 0h" } },
 	{ MODKEY|ControlMask,           XK_Up,         moveresizeedge, {.v = "t"} },
 	{ MODKEY|ControlMask,           XK_Down,       moveresizeedge, {.v = "b"} },
 	{ MODKEY|ControlMask,           XK_Left,       moveresizeedge, {.v = "l"} },
 	{ MODKEY|ControlMask,           XK_Right,      moveresizeedge, {.v = "r"} },
 	{ MODKEY|ControlMask|ShiftMask, XK_Up,         moveresizeedge, {.v = "T"} },
 	{ MODKEY|ControlMask|ShiftMask, XK_Down,       moveresizeedge, {.v = "B"} },
 	{ MODKEY|ControlMask|ShiftMask, XK_Left,       moveresizeedge, {.v = "L"} },
 	{ MODKEY|ControlMask|ShiftMask, XK_Right,      moveresizeedge, {.v = "R"} },
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkRootWin,           MODKEY,         Button4,        spawn,          {.v = upvol   } },
	{ ClkRootWin,           MODKEY,         Button5,        spawn,          {.v = downvol } },
	{ ClkRootWin,           MODKEY,         Button8,        spawn,          {.v = mutevol } },
	{ ClkRootWin,           MODKEY,         Button9,        spawn_notify,   {.v = playpausecmd } },
    { ClkClientWin,         MODKEY,         Button4,        spawn,          {.v = upvol   } },
	{ ClkClientWin,         MODKEY,         Button5,        spawn,          {.v = downvol } },
	{ ClkClientWin,         MODKEY,         Button8,        spawn,          {.v = mutevol } },
	{ ClkClientWin,         MODKEY,         Button9,        spawn_notify,   {.v = playpausecmd } },
};

