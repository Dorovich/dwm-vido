/* See LICENSE file for copyright and license details. */

#define TERMINAL 	"st"
#define BROWSER		"librewolf"
#define VISUAL		"emacsclient -c -a 'emacs'"
#define FILEMAN_GUI 	"pcmanfm"
#define FILEMAN_CLI 	"lf"
#define SCRIPTCTL	"scriptctl"
#define GAPPX 		6

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int gappih    = GAPPX;    /* horiz inner gap between windows */
static const unsigned int gappiv    = GAPPX;    /* vert inner gap between windows */
static const unsigned int gappoh    = GAPPX;    /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = GAPPX;    /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "mononoki NF:size=14" };
static const char dmenufont[]       = "mononoki NF:size=14";
static const char col_bg[]          = "#151515";
static const char col_fg[]          = "#d1d1d1";
static const char col_accent[]      = "#346475";
static const char *colors[][3]      = {
	/*               fg         bg            border   */
	[SchemeNorm] = { col_fg,    col_bg,       col_bg },
	[SchemeSel]  = { col_fg,    col_accent,   col_accent },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                       instance       title               tags mask  isfloating  monitor */
	{ "Gimp",                      NULL,          NULL,               0,         1,          -1 },
	{ "Steam",                     NULL,          "Lista de amigos",  0,         1,          -1 },
	{ NULL,                        NULL,          "IDI-Lab",          0,         1,          -1 },
	{ "thunderbird",               "Msgcompose",  NULL,               0,         1,          -1 },
	{ "FilePicker",                NULL,          NULL,               0,         1,          -1 },
	{ "robloxplayerlauncher.exe",  NULL,          NULL,               0,         1,          -1 },
	{ NULL,                        NULL,          "SCPSL",            0,         1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
#define SCRIPT(scr) { .v = (const char*[]){ SCRIPTCTL, scr, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]	= { "dmenu_run", "-m", dmenumon, "-i", "-p", "Run:", NULL };
static const char *termcmd[]	= { TERMINAL, NULL };
static const char *browsercmd[]	= { BROWSER, NULL };
static const char *qbcmd[]	= { "qutebrowser", NULL };
static const char *gfilescmd[]	= { FILEMAN_GUI, NULL };
static const char *filescmd[]	= { TERMINAL, "-e", FILEMAN_CLI, NULL };
static const char *lockcmd[]	= { "slock", NULL };
static const char *editorcmd[]	= { "/bin/sh", "-c", VISUAL, NULL };

/* ver README.org para más información sobre las teclas */
static const Key keys[] = {
	/* modifier                     key        function        argument */
    
        /* Sesión */
	{ MODKEY,             		XK_Escape, spawn,          {.v = lockcmd } },
	{ MODKEY,             		XK_F1,     spawn,          SHCMD("ayuda") },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, /* restart */
#ifdef SCRIPTCTL
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SCRIPT("wmquit") },
#else
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, /* quit dwm */
#endif

        /* Programas */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,           		XK_b,      spawn,      	   {.v = browsercmd } },
	{ MODKEY|ShiftMask,           	XK_b,      spawn,      	   {.v = qbcmd } },
	{ MODKEY,           		XK_w,      spawn,      	   {.v = filescmd } },
	{ MODKEY|ShiftMask,           	XK_w,      spawn,      	   {.v = gfilescmd } },
	{ MODKEY,           		XK_e,      spawn,      	   {.v = editorcmd } },

        /* Desplazar foco */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },

        /* Gestionar ventanas */
	{ MODKEY,             		XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,             		XK_f,      togglefullscr,  {0} },
	{ MODKEY,              		XK_g,      togglegaps,     {0} },
	{ MODKEY,             		XK_s,      togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_s,      setlayout,      {.v = &layouts[1]} }, /* Floating */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* Tiled */
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[2]} }, /* Monocle */
	{ MODKEY|ShiftMask,             XK_Tab,    setlayout,      {0} },
        
        /* Gestionar etiquetas */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
        
        /* Scripts */
#ifdef SCRIPTCTL
	{ MODKEY,                       XK_m,      spawn,          SCRIPT("music") },
	{ MODKEY,                       XK_p,      spawn,          SCRIPT("password") },
	{ MODKEY,              		XK_o,      spawn,          SCRIPT("soundout") },
	{ MODKEY,              		XK_x,      spawn,          SCRIPT("kill") },
	{ MODKEY,                       XK_Insert, spawn,          SCRIPT("snippet") },
	{ MODKEY,                       XK_Print,  spawn,          SCRIPT("screenshot") },
	{ MODKEY,                       XK_plus,   spawn,          SCRIPT("volume-up") },
	{ MODKEY,                       XK_minus,  spawn,          SCRIPT("volume-down") },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          SCRIPT("launch-steamapp") },
	{ MODKEY,             		XK_r,      spawn,          SCRIPT(NULL) },
#endif
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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
};

