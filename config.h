/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 6;        /* border pixel of windows */
static const unsigned int gappx     = 20;        /* gap pixel between windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int extrabarright      = 0;        /* 1 means extra bar text on right */
static const char statussep         = ';';      /* separator between status bars */
static const char *fonts[]          = { "Hack Nerd Font Mono:size=14" };
static const char dmenufont[]       = "monospace:size=14";
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

/* monitor positioning definitions */
#define MON_ANY -1
#define MON_LEFT 2
#define MON_MID 0
#define MON_RIGHT 1

#define TAG_1 1
#define TAG_2 2
#define TAG_3 4
#define TAG_4 8
#define TAG_5 16
#define TAG_6 32
#define TAG_7 64
#define TAG_8 128
#define TAG_9 256

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title (strstr)                tags mask   isfloating   monitor	 scratch */
	{ NULL,       NULL,       "scratchpad",                 0,          1,           MON_ANY,       's' },
	{ NULL,       NULL,       "Settings",                   0,          1,           MON_ANY},
	{ NULL,       NULL,       "Base Converter",             0,          1,           MON_ANY},

	{ NULL,       NULL,       "broken", /* Spotify */       TAG_1,      0,           MON_LEFT},
	{ NULL,       NULL,       "Slack",             				  TAG_2,      0,           MON_LEFT},
	{ NULL,       NULL,       "Discord",             				TAG_4,      0,           MON_LEFT},
	{ NULL,       NULL,       "RSS",             						TAG_7,      0,           MON_MID},
	{ NULL,       NULL,       "another-redis",             	TAG_8,      0,           MON_MID},
	{ NULL,       NULL,       "AWS VPN",             				TAG_8,      0,           MON_MID},
	{ NULL,       NULL,       "beekeeper",             			TAG_9,      0,           MON_MID},
	{ NULL,       NULL,       "Postman",             				TAG_2,      0,           MON_RIGHT},
	{ NULL,       NULL,       "Whale",             					TAG_4,      0,           MON_RIGHT},
	{ NULL,       NULL,       "Google Chrome",             	TAG_9,      0,           MON_RIGHT},
	{ NULL,       NULL,       "Zoom",             					TAG_7,      0,           MON_RIGHT},
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
static const char *monitor1cmd[]  =  { "mousemove.sh", "1", NULL };
static const char *monitor2cmd[]  =  { "mousemove.sh", "2", NULL };
static const char *monitor3cmd[]  =  { "mousemove.sh", "3", NULL };
static const char *playpausecmd[]  =  { "playerctl", "play-pause", NULL };
static const char *gimpcmd[]  =    { "gimp", NULL };
static const char *msgcmd[]  =    { "discord", NULL };
static const char *postmancmd[]  =  { "postman", NULL };
static const char *scancmd[]  =   { "scan", NULL };
static const char *screenshotcmd[]  =  { "deepin-screenshot", NULL };
static const char *slackcmd[]  =  { "slack", NULL };
static const char *spotifycmd[] = {"spotify", NULL};
static const char *translatecmd[]  =  { "tagainijisho", NULL };
static const char *sqlcmd[]  =  { "beekeeper", NULL };
static const char *vlccmd[]  =    { "vlc", NULL };
static const char *webcmd[]  =    { "firefox", NULL };
static const char *whalecmd[]  =  { "whale", NULL };
static const char *xkillcmd[]  =  { "xkill", NULL };
static const char *zoomcmd[]  =   { "zoom", NULL };


/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", "-g", "100x30+200+100", "-f", "Monospace:14", "-e", "/bin/bash", "--init-file", "/home/regular/.bashrc_scratch", NULL};

/* M80 keymappings */
// F1: 0x1008ff03
// F2: 0x1008ff02
// F3: 0x1008ff4a
// F4: 0x1008ff4b
// F5: 0x1008ff06
// F6: 0x1008ff05
// F7: 0x1008ff16
// F8: 0x1008ff14
// F9: 0x1008ff17
// F10: 0x1008ff12
// F11: 0x1008ff11
// F12: 0x1008ff13

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
	{ MODKEY,                       XK_comma,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,      setgaps,        {.i = -15 } },
	{ MODKEY,                       XK_equal,      setgaps,        {.i = +15 } },
	{ MODKEY|ShiftMask,             XK_equal,      setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_F12,        spawn,          {.v = suscmd } },
	{ MODKEY,                       XK_Delete,     spawn,          {.v = suscmd } },
	{ MODKEY,                       0x1008ff13,    spawn,          {.v = suscmd } },
	{ MODKEY|ShiftMask,             XK_F12,        spawn,          {.v = offcmd } },
	{ MODKEY|ShiftMask,             XK_Delete,     spawn,          {.v = offcmd } },
	{ MODKEY|ShiftMask,             0x1008ff13,    spawn,          {.v = offcmd } },
	{ MODKEY,                       XK_F11,        spawn,          {.v = rebootcmd } },
	{ MODKEY,                       XK_Prior,      spawn,          {.v = rebootcmd } },
	{ MODKEY,                       0x1008ff11,    spawn,          {.v = rebootcmd } },
	{ MODKEY,                       XK_F5,         spawn,          {.v = scancmd } },
	{ MODKEY,                       0x1008ff06,    spawn,          {.v = scancmd } },
	{ MODKEY,                       XK_q,          spawn_notify,   {.v = sqlcmd } },
	{ MODKEY,                       XK_v,          spawn_notify,   {.v = vlccmd } },
	{ MODKEY,                       XK_a,          spawn_notify,   {.v = slackcmd } },
	{ MODKEY,                       XK_c,          spawn_notify,   {.v = spotifycmd } },
	{ MODKEY,                       XK_e,          spawn_notify,   {.v = whalecmd } },
	{ MODKEY,                       XK_n,          spawn_notify,   {.v = translatecmd } },
	{ MODKEY,                       XK_p,          spawn_notify,   {.v = postmancmd } },
	{ MODKEY,                       XK_x,          spawn_notify,   {.v = xkillcmd } },
	{ 0,                            XK_Print,      spawn_notify,   {.v = screenshotcmd } },
	{ MODKEY,                       XK_KP_Add,     spawn_notify,   {.v = upvol } },
	{ MODKEY,                       XK_KP_Subtract,spawn_notify,   {.v = downvol } },
	{ MODKEY,                       XK_KP_Multiply,spawn_notify,   {.v = mutevol } },
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
	{ LockMask,                     XK_1,          spawn,          {.v = monitor1cmd } },
	{ LockMask,                     XK_2,          spawn,          {.v = monitor2cmd } },
	{ LockMask,                     XK_3,          spawn,          {.v = monitor3cmd } },
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

