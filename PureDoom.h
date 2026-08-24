//-----------------------------------------------------------------------------
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
//-----------------------------------------------------------------------------
/* Pure DOOM usage

   Do this:
      #define DOOM_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   // i.e. it should look like this:
   #include ...
   #include ...
   #include ...
   #define DOOM_IMPLEMENTATION
   #include "PureDOOM.h"

*/
//-----------------------------------------------------------------------------


#ifndef __DOOM_H__
#define __DOOM_H__


// Sample rate of sound samples from doom
#define DOOM_SAMPLERATE 11025

// MIDI tick needs to be called 140 times per seconds
#define DOOM_MIDI_RATE 140

// Hide menu options. If for say your platform doesn't support mouse or
// MIDI playback, you can hide these settings from the menu.
#define DOOM_FLAG_HIDE_MOUSE_OPTIONS 1 // Remove mouse options from menu
#define DOOM_FLAG_HIDE_SOUND_OPTIONS 2 // Remove sound options from menu
#define DOOM_FLAG_HIDE_MUSIC_OPTIONS 4 // Remove music options from menu

// Darken background when menu is open, making it more readable. This
// uses a bit more CPU and redraws the HUD every frame
#define DOOM_FLAG_MENU_DARKEN_BG 8


#if __cplusplus
extern "C" {
#endif

typedef enum
{
    DOOM_SEEK_CUR = 1,
    DOOM_SEEK_END = 2,
    DOOM_SEEK_SET = 0
} doom_seek_t;


typedef void(*doom_print_fn)(const char* str);
typedef void*(*doom_malloc_fn)(int size);
typedef void(*doom_free_fn)(void* ptr);
typedef void*(*doom_open_fn)(const char* filename, const char* mode);
typedef void(*doom_close_fn)(void* handle);
typedef int(*doom_read_fn)(void* handle, void *buf, int count);
typedef int(*doom_write_fn)(void* handle, const void *buf, int count);
typedef int(*doom_seek_fn)(void* handle, int offset, doom_seek_t origin);
typedef int(*doom_tell_fn)(void* handle);
typedef int(*doom_eof_fn)(void* handle);
typedef void(*doom_gettime_fn)(int* sec, int* usec);
typedef void(*doom_exit_fn)(int code);
typedef char*(*doom_getenv_fn)(const char* var);


// Doom key mapping
typedef enum
{
    DOOM_KEY_UNKNOWN = -1,
    DOOM_KEY_TAB = 9,
    DOOM_KEY_ENTER = 13,
    DOOM_KEY_ESCAPE = 27,
    DOOM_KEY_SPACE = 32,
    DOOM_KEY_APOSTROPHE = '\'',
    DOOM_KEY_MULTIPLY = '*',
    DOOM_KEY_COMMA = ',',
    DOOM_KEY_MINUS = 0x2d,
    DOOM_KEY_PERIOD = '.',
    DOOM_KEY_SLASH = '/',
    DOOM_KEY_0 = '0',
    DOOM_KEY_1 = '1',
    DOOM_KEY_2 = '2',
    DOOM_KEY_3 = '3',
    DOOM_KEY_4 = '4',
    DOOM_KEY_5 = '5',
    DOOM_KEY_6 = '6',
    DOOM_KEY_7 = '7',
    DOOM_KEY_8 = '8',
    DOOM_KEY_9 = '9',
    DOOM_KEY_SEMICOLON = ';',
    DOOM_KEY_EQUALS = 0x3d,
    DOOM_KEY_LEFT_BRACKET = '[',
    DOOM_KEY_RIGHT_BRACKET = ']',
    DOOM_KEY_A = 'a',
    DOOM_KEY_B = 'b',
    DOOM_KEY_C = 'c',
    DOOM_KEY_D = 'd',
    DOOM_KEY_E = 'e',
    DOOM_KEY_F = 'f',
    DOOM_KEY_G = 'g',
    DOOM_KEY_H = 'h',
    DOOM_KEY_I = 'i',
    DOOM_KEY_J = 'j',
    DOOM_KEY_K = 'k',
    DOOM_KEY_L = 'l',
    DOOM_KEY_M = 'm',
    DOOM_KEY_N = 'n',
    DOOM_KEY_O = 'o',
    DOOM_KEY_P = 'p',
    DOOM_KEY_Q = 'q',
    DOOM_KEY_R = 'r',
    DOOM_KEY_S = 's',
    DOOM_KEY_T = 't',
    DOOM_KEY_U = 'u',
    DOOM_KEY_V = 'v',
    DOOM_KEY_W = 'w',
    DOOM_KEY_X = 'x',
    DOOM_KEY_Y = 'y',
    DOOM_KEY_Z = 'z',
    DOOM_KEY_BACKSPACE = 127,
    DOOM_KEY_CTRL = (0x80 + 0x1d), // Both left and right
    DOOM_KEY_LEFT_ARROW = 0xac,
    DOOM_KEY_UP_ARROW = 0xad,
    DOOM_KEY_RIGHT_ARROW = 0xae,
    DOOM_KEY_DOWN_ARROW = 0xaf,
    DOOM_KEY_SHIFT = (0x80 + 0x36), // Both left and right
    DOOM_KEY_ALT = (0x80 + 0x38), // Both left and right
    DOOM_KEY_F1 = (0x80 + 0x3b),
    DOOM_KEY_F2 = (0x80 + 0x3c),
    DOOM_KEY_F3 = (0x80 + 0x3d),
    DOOM_KEY_F4 = (0x80 + 0x3e),
    DOOM_KEY_F5 = (0x80 + 0x3f),
    DOOM_KEY_F6 = (0x80 + 0x40),
    DOOM_KEY_F7 = (0x80 + 0x41),
    DOOM_KEY_F8 = (0x80 + 0x42),
    DOOM_KEY_F9 = (0x80 + 0x43),
    DOOM_KEY_F10 = (0x80 + 0x44),
    DOOM_KEY_F11 = (0x80 + 0x57),
    DOOM_KEY_F12 = (0x80 + 0x58),
    DOOM_KEY_PAUSE = 0xff
} doom_key_t;


// Mouse button mapping
typedef enum
{
    DOOM_LEFT_BUTTON = 0,
    DOOM_RIGHT_BUTTON = 1,
    DOOM_MIDDLE_BUTTON = 2
} doom_button_t;


// For the software renderer. Default is 320x200
void doom_set_resolution(int width, int height);

// Set default configurations. Lets say, changing arrows to WASD as default controls
void doom_set_default_int(const char* name, int value);
void doom_set_default_string(const char* name, const char* value);

// set callbacks
void doom_set_print(doom_print_fn print_fn);
void doom_set_malloc(doom_malloc_fn malloc_fn, doom_free_fn free_fn);
void doom_set_file_io(doom_open_fn open_fn,
                      doom_close_fn close_fn,
                      doom_read_fn read_fn,
                      doom_write_fn write_fn,
                      doom_seek_fn seek_fn,
                      doom_tell_fn tell_fn,
                      doom_eof_fn eof_fn);
void doom_set_gettime(doom_gettime_fn gettime_fn);
void doom_set_exit(doom_exit_fn exit_fn);
void doom_set_getenv(doom_getenv_fn getenv_fn);

// Initializes DOOM and start things up. Call only call one
void doom_init(int argc, char** argv, int flags);

// Call this every frame
void doom_update(void); // This will update at 35 FPS
void doom_force_update(void); // This will run a frame everytime it's called, regardless of FPS.

// Channels: 1 = indexed, 3 = RGB, 4 = RGBA
const unsigned char* doom_get_framebuffer(int channels);

// It is always 2048 bytes in size
short* doom_get_sound_buffer(void);

// Call this 140 times per second. Or about every 7ms. 
// Returns midi message. Keep calling it until it returns 0.
unsigned long doom_tick_midi(void);

// Events
void doom_key_down(doom_key_t key);
void doom_key_up(doom_key_t key);
void doom_button_down(doom_button_t button);
void doom_button_up(doom_button_t button);
void doom_mouse_move(int delta_x, int delta_y);


#ifdef __cplusplus
} // extern "C"
#endif

#endif
#ifndef __D_ENGLSH__
#define __D_ENGLSH__


//
// Printed strings for translation
//

//
// D_Main.C
//
#define D_DEVSTR "Development mode ON.\n"
#define D_CDROM "CD-ROM Version: default.cfg from c:\\doomdata\n"

//
//        M_Menu.C
//
#define PRESSKEY "press a key."
#define PRESSYN "press y or n."
#define QUITMSG "are you sure you want to\nquit this great game?"
#define LOADNET "you can't do load while in a net game!\n\n" PRESSKEY
#define QLOADNET "you can't quickload during a netgame!\n\n" PRESSKEY
#define QSAVESPOT "you haven't picked a quicksave slot yet!\n\n" PRESSKEY
#define SAVEDEAD "you can't save if you aren't playing!\n\n" PRESSKEY
#define QSPROMPT "quicksave over your game named\n\n'%s'?\n\n" PRESSYN
#define QLPROMPT "do you want to quickload the game named\n\n'%s'?\n\n" PRESSYN

#define QSPROMPT_1 "quicksave over your game named\n\n'"
#define QSPROMPT_2 "'?\n\n" PRESSYN
#define QLPROMPT_1 "do you want to quickload the game named\n\n'%s"
#define QLPROMPT_2 "'?\n\n" PRESSYN

#define NEWGAME \
"you can't start a new game\n"\
"while in a network game.\n\n" PRESSKEY

#define NIGHTMARE \
"are you sure? this skill level\n"\
"isn't even remotely fair.\n\n" PRESSYN

#define SWSTRING \
"this is the shareware version of doom.\n\n"\
"you need to order the entire trilogy.\n\n" PRESSKEY

#define MSGOFF "Messages OFF"
#define MSGON "Messages ON"
#define CROSSOFF "Crosshair OFF"
#define CROSSON "Crosshair ON"
#define ALWAYSRUNOFF "Always run OFF"
#define ALWAYSRUNON "Always run ON"
#define NETEND "you can't end a netgame!\n\n" PRESSKEY
#define ENDGAME "are you sure you want to end the game?\n\n" PRESSYN

#define DOSY "(press y to quit)"

#define DETAILHI "High detail"
#define DETAILLO "Low detail"
#define GAMMALVL0 "Gamma correction OFF"
#define GAMMALVL1 "Gamma correction level 1"
#define GAMMALVL2 "Gamma correction level 2"
#define GAMMALVL3 "Gamma correction level 3"
#define GAMMALVL4 "Gamma correction level 4"
#define EMPTYSTRING "empty slot"

//
// P_inter.C
//
#define GOTARMOR    "Picked up the armor."
#define GOTMEGA     "Picked up the MegaArmor!"
#define GOTHTHBONUS "Picked up a health bonus."
#define GOTARMBONUS "Picked up an armor bonus."
#define GOTSTIM     "Picked up a stimpack."
#define GOTMEDINEED "Picked up a medikit that you REALLY need!"
#define GOTMEDIKIT  "Picked up a medikit."
#define GOTSUPER    "Supercharge!"

#define GOTBLUECARD "Picked up a blue keycard."
#define GOTYELWCARD "Picked up a yellow keycard."
#define GOTREDCARD  "Picked up a red keycard."
#define GOTBLUESKUL "Picked up a blue skull key."
#define GOTYELWSKUL "Picked up a yellow skull key."
#define GOTREDSKULL "Picked up a red skull key."

#define GOTINVUL    "Invulnerability!"
#define GOTBERSERK  "Berserk!"
#define GOTINVIS    "Partial Invisibility"
#define GOTSUIT     "Radiation Shielding Suit"
#define GOTMAP      "Computer Area Map"
#define GOTVISOR    "Light Amplification Visor"
#define GOTMSPHERE  "MegaSphere!"

#define GOTCLIP     "Picked up a clip."
#define GOTCLIPBOX  "Picked up a box of bullets."
#define GOTROCKET   "Picked up a rocket."
#define GOTROCKBOX  "Picked up a box of rockets."
#define GOTCELL     "Picked up an energy cell."
#define GOTCELLBOX  "Picked up an energy cell pack."
#define GOTSHELLS   "Picked up 4 shotgun shells."
#define GOTSHELLBOX "Picked up a box of shotgun shells."
#define GOTBACKPACK "Picked up a backpack full of ammo!"

#define GOTBFG9000  "You got the BFG9000!  Oh, yes."
#define GOTCHAINGUN "You got the chaingun!"
#define GOTCHAINSAW "A chainsaw!  Find some meat!"
#define GOTLAUNCHER "You got the rocket launcher!"
#define GOTPLASMA   "You got the plasma gun!"
#define GOTSHOTGUN  "You got the shotgun!"
#define GOTSHOTGUN2 "You got the super shotgun!"

//
// P_Doors.C
//
#define PD_BLUEO    "You need a blue key to activate this object"
#define PD_REDO     "You need a red key to activate this object"
#define PD_YELLOWO  "You need a yellow key to activate this object"
#define PD_BLUEK    "You need a blue key to open this door"
#define PD_REDK     "You need a red key to open this door"
#define PD_YELLOWK  "You need a yellow key to open this door"

//
// G_game.C
//
#define GGSAVED     "game saved."

//
// HU_stuff.C
//
#define HUSTR_MSGU "[Message unsent]"

#define HUSTR_E1M1 "E1M1: Hangar"
#define HUSTR_E1M2 "E1M2: Nuclear Plant"
#define HUSTR_E1M3 "E1M3: Toxin Refinery"
#define HUSTR_E1M4 "E1M4: Command Control"
#define HUSTR_E1M5 "E1M5: Phobos Lab"
#define HUSTR_E1M6 "E1M6: Central Processing"
#define HUSTR_E1M7 "E1M7: Computer Station"
#define HUSTR_E1M8 "E1M8: Phobos Anomaly"
#define HUSTR_E1M9 "E1M9: Military Base"

#define HUSTR_E2M1 "E2M1: Deimos Anomaly"
#define HUSTR_E2M2 "E2M2: Containment Area"
#define HUSTR_E2M3 "E2M3: Refinery"
#define HUSTR_E2M4 "E2M4: Deimos Lab"
#define HUSTR_E2M5 "E2M5: Command Center"
#define HUSTR_E2M6 "E2M6: Halls of the Damned"
#define HUSTR_E2M7 "E2M7: Spawning Vats"
#define HUSTR_E2M8 "E2M8: Tower of Babel"
#define HUSTR_E2M9 "E2M9: Fortress of Mystery"

#define HUSTR_E3M1 "E3M1: Hell Keep"
#define HUSTR_E3M2 "E3M2: Slough of Despair"
#define HUSTR_E3M3 "E3M3: Pandemonium"
#define HUSTR_E3M4 "E3M4: House of Pain"
#define HUSTR_E3M5 "E3M5: Unholy Cathedral"
#define HUSTR_E3M6 "E3M6: Mt. Erebus"
#define HUSTR_E3M7 "E3M7: Limbo"
#define HUSTR_E3M8 "E3M8: Dis"
#define HUSTR_E3M9 "E3M9: Warrens"

#define HUSTR_E4M1 "E4M1: Hell Beneath"
#define HUSTR_E4M2 "E4M2: Perfect Hatred"
#define HUSTR_E4M3 "E4M3: Sever The Wicked"
#define HUSTR_E4M4 "E4M4: Unruly Evil"
#define HUSTR_E4M5 "E4M5: They Will Repent"
#define HUSTR_E4M6 "E4M6: Against Thee Wickedly"
#define HUSTR_E4M7 "E4M7: And Hell Followed"
#define HUSTR_E4M8 "E4M8: Unto The Cruel"
#define HUSTR_E4M9 "E4M9: Fear"

#define HUSTR_1 "level 1: entryway"
#define HUSTR_2 "level 2: underhalls"
#define HUSTR_3 "level 3: the gantlet"
#define HUSTR_4 "level 4: the focus"
#define HUSTR_5 "level 5: the waste tunnels"
#define HUSTR_6 "level 6: the crusher"
#define HUSTR_7 "level 7: dead simple"
#define HUSTR_8 "level 8: tricks and traps"
#define HUSTR_9 "level 9: the pit"
#define HUSTR_10 "level 10: refueling base"
#define HUSTR_11 "level 11: 'o' of destruction!"

#define HUSTR_12 "level 12: the factory"
#define HUSTR_13 "level 13: downtown"
#define HUSTR_14 "level 14: the inmost dens"
#define HUSTR_15 "level 15: industrial zone"
#define HUSTR_16 "level 16: suburbs"
#define HUSTR_17 "level 17: tenements"
#define HUSTR_18 "level 18: the courtyard"
#define HUSTR_19 "level 19: the citadel"
#define HUSTR_20 "level 20: gotcha!"

#define HUSTR_21 "level 21: nirvana"
#define HUSTR_22 "level 22: the catacombs"
#define HUSTR_23 "level 23: barrels o' fun"
#define HUSTR_24 "level 24: the chasm"
#define HUSTR_25 "level 25: bloodfalls"
#define HUSTR_26 "level 26: the abandoned mines"
#define HUSTR_27 "level 27: monster condo"
#define HUSTR_28 "level 28: the spirit world"
#define HUSTR_29 "level 29: the living end"
#define HUSTR_30 "level 30: icon of sin"

#define HUSTR_31 "level 31: wolfenstein"
#define HUSTR_32 "level 32: grosse"

#define PHUSTR_1 "level 1: congo"
#define PHUSTR_2 "level 2: well of souls"
#define PHUSTR_3 "level 3: aztec"
#define PHUSTR_4 "level 4: caged"
#define PHUSTR_5 "level 5: ghost town"
#define PHUSTR_6 "level 6: baron's lair"
#define PHUSTR_7 "level 7: caughtyard"
#define PHUSTR_8 "level 8: realm"
#define PHUSTR_9 "level 9: abattoire"
#define PHUSTR_10 "level 10: onslaught"
#define PHUSTR_11 "level 11: hunted"

#define PHUSTR_12 "level 12: speed"
#define PHUSTR_13 "level 13: the crypt"
#define PHUSTR_14 "level 14: genesis"
#define PHUSTR_15 "level 15: the twilight"
#define PHUSTR_16 "level 16: the omen"
#define PHUSTR_17 "level 17: compound"
#define PHUSTR_18 "level 18: neurosphere"
#define PHUSTR_19 "level 19: nme"
#define PHUSTR_20 "level 20: the death domain"

#define PHUSTR_21 "level 21: slayer"
#define PHUSTR_22 "level 22: impossible mission"
#define PHUSTR_23 "level 23: tombstone"
#define PHUSTR_24 "level 24: the final frontier"
#define PHUSTR_25 "level 25: the temple of darkness"
#define PHUSTR_26 "level 26: bunker"
#define PHUSTR_27 "level 27: anti-christ"
#define PHUSTR_28 "level 28: the sewers"
#define PHUSTR_29 "level 29: odyssey of noises"
#define PHUSTR_30 "level 30: the gateway of hell"

#define PHUSTR_31 "level 31: cyberden"
#define PHUSTR_32 "level 32: go 2 it"

#define THUSTR_1 "level 1: system control"
#define THUSTR_2 "level 2: human bbq"
#define THUSTR_3 "level 3: power control"
#define THUSTR_4 "level 4: wormhole"
#define THUSTR_5 "level 5: hanger"
#define THUSTR_6 "level 6: open season"
#define THUSTR_7 "level 7: prison"
#define THUSTR_8 "level 8: metal"
#define THUSTR_9 "level 9: stronghold"
#define THUSTR_10 "level 10: redemption"
#define THUSTR_11 "level 11: storage facility"

#define THUSTR_12 "level 12: crater"
#define THUSTR_13 "level 13: nukage processing"
#define THUSTR_14 "level 14: steel works"
#define THUSTR_15 "level 15: dead zone"
#define THUSTR_16 "level 16: deepest reaches"
#define THUSTR_17 "level 17: processing area"
#define THUSTR_18 "level 18: mill"
#define THUSTR_19 "level 19: shipping/respawning"
#define THUSTR_20 "level 20: central processing"

#define THUSTR_21 "level 21: administration center"
#define THUSTR_22 "level 22: habitat"
#define THUSTR_23 "level 23: lunar mining project"
#define THUSTR_24 "level 24: quarry"
#define THUSTR_25 "level 25: baron's den"
#define THUSTR_26 "level 26: ballistyx"
#define THUSTR_27 "level 27: mount pain"
#define THUSTR_28 "level 28: heck"
#define THUSTR_29 "level 29: river styx"
#define THUSTR_30 "level 30: last call"

#define THUSTR_31 "level 31: pharaoh"
#define THUSTR_32 "level 32: caribbean"

#define HUSTR_CHATMACRO1 "I'm ready to kick butt!"
#define HUSTR_CHATMACRO2 "I'm OK."
#define HUSTR_CHATMACRO3 "I'm not looking too good!"
#define HUSTR_CHATMACRO4 "Help!"
#define HUSTR_CHATMACRO5 "You suck!"
#define HUSTR_CHATMACRO6 "Next time, scumbag..."
#define HUSTR_CHATMACRO7 "Come here!"
#define HUSTR_CHATMACRO8 "I'll take care of it."
#define HUSTR_CHATMACRO9 "Yes"
#define HUSTR_CHATMACRO0 "No"

#define HUSTR_TALKTOSELF1 "You mumble to yourself"
#define HUSTR_TALKTOSELF2 "Who's there?"
#define HUSTR_TALKTOSELF3 "You scare yourself"
#define HUSTR_TALKTOSELF4 "You start to rave"
#define HUSTR_TALKTOSELF5 "You've lost it..."

#define HUSTR_MESSAGESENT "[Message Sent]"

// The following should NOT be changed unless it seems
// just AWFULLY necessary

#define HUSTR_PLRGREEN  "Green: "
#define HUSTR_PLRINDIGO "Indigo: "
#define HUSTR_PLRBROWN  "Brown: "
#define HUSTR_PLRRED    "Red: "

#define HUSTR_KEYGREEN  'g'
#define HUSTR_KEYINDIGO 'i'
#define HUSTR_KEYBROWN  'b'
#define HUSTR_KEYRED    'r'

//
// AM_map.C
//

#define AMSTR_FOLLOWON  "Follow Mode ON"
#define AMSTR_FOLLOWOFF "Follow Mode OFF"

#define AMSTR_GRIDON    "Grid ON"
#define AMSTR_GRIDOFF   "Grid OFF"

#define AMSTR_MARKEDSPOT    "Marked Spot"
#define AMSTR_MARKSCLEARED  "All Marks Cleared"

//
// ST_stuff.C
//

#define STSTR_MUS       "Music Change"
#define STSTR_NOMUS     "IMPOSSIBLE SELECTION"
#define STSTR_DQDON     "Degreelessness Mode On"
#define STSTR_DQDOFF    "Degreelessness Mode Off"

#define STSTR_KFAADDED  "Very Happy Ammo Added"
#define STSTR_FAADDED   "Ammo (no keys) Added"

#define STSTR_NCON      "No Clipping Mode ON"
#define STSTR_NCOFF     "No Clipping Mode OFF"

#define STSTR_BEHOLD    "inVuln, Str, Inviso, Rad, Allmap, or Lite-amp"
#define STSTR_BEHOLDX   "Power-up Toggled"

#define STSTR_CHOPPERS  "... doesn't suck - GM"
#define STSTR_CLEV      "Changing Level..."

//
// F_Finale.C
//
#define E1TEXT \
"Once you beat the big badasses and\n"\
"clean out the moon base you're supposed\n"\
"to win, aren't you? Aren't you? Where's\n"\
"your fat reward and ticket home? What\n"\
"the hell is this? It's not supposed to\n"\
"end this way!\n"\
"\n" \
"It stinks like rotten meat, but looks\n"\
"like the lost Deimos base.  Looks like\n"\
"you're stuck on The Shores of Hell.\n"\
"The only way out is through.\n"\
"\n"\
"To continue the DOOM experience, play\n"\
"The Shores of Hell and its amazing\n"\
"sequel, Inferno!\n"


#define E2TEXT \
"You've done it! The hideous cyber-\n"\
"demon lord that ruled the lost Deimos\n"\
"moon base has been slain and you\n"\
"are triumphant! But ... where are\n"\
"you? You clamber to the edge of the\n"\
"moon and look down to see the awful\n"\
"truth.\n" \
"\n"\
"Deimos floats above Hell itself!\n"\
"You've never heard of anyone escaping\n"\
"from Hell, but you'll make the bastards\n"\
"sorry they ever heard of you! Quickly,\n"\
"you rappel down to  the surface of\n"\
"Hell.\n"\
"\n" \
"Now, it's on to the final chapter of\n"\
"DOOM! -- Inferno."


#define E3TEXT \
"The loathsome spiderdemon that\n"\
"masterminded the invasion of the moon\n"\
"bases and caused so much death has had\n"\
"its ass kicked for all time.\n"\
"\n"\
"A hidden doorway opens and you enter.\n"\
"You've proven too tough for Hell to\n"\
"contain, and now Hell at last plays\n"\
"fair -- for you emerge from the door\n"\
"to see the green fields of Earth!\n"\
"Home at last.\n" \
"\n"\
"You wonder what's been happening on\n"\
"Earth while you were battling evil\n"\
"unleashed. It's good that no Hell-\n"\
"spawn could have come through that\n"\
"door with you ..."


#define E4TEXT \
"the spider mastermind must have sent forth\n"\
"its legions of hellspawn before your\n"\
"final confrontation with that terrible\n"\
"beast from hell.  but you stepped forward\n"\
"and brought forth eternal damnation and\n"\
"suffering upon the horde as a true hero\n"\
"would in the face of something so evil.\n"\
"\n"\
"besides, someone was gonna pay for what\n"\
"happened to daisy, your pet rabbit.\n"\
"\n"\
"but now, you see spread before you more\n"\
"potential pain and gibbitude as a nation\n"\
"of demons run amok among our cities.\n"\
"\n"\
"next stop, hell on earth!"


// after level 6, put this:
#define C1TEXT \
"YOU HAVE ENTERED DEEPLY INTO THE INFESTED\n" \
"STARPORT. BUT SOMETHING IS WRONG. THE\n" \
"MONSTERS HAVE BROUGHT THEIR OWN REALITY\n" \
"WITH THEM, AND THE STARPORT'S TECHNOLOGY\n" \
"IS BEING SUBVERTED BY THEIR PRESENCE.\n" \
"\n"\
"AHEAD, YOU SEE AN OUTPOST OF HELL, A\n" \
"FORTIFIED ZONE. IF YOU CAN GET PAST IT,\n" \
"YOU CAN PENETRATE INTO THE HAUNTED HEART\n" \
"OF THE STARBASE AND FIND THE CONTROLLING\n" \
"SWITCH WHICH HOLDS EARTH'S POPULATION\n" \
"HOSTAGE."

// After level 11, put this:
#define C2TEXT \
"YOU HAVE WON! YOUR VICTORY HAS ENABLED\n" \
"HUMANKIND TO EVACUATE EARTH AND ESCAPE\n"\
"THE NIGHTMARE.  NOW YOU ARE THE ONLY\n"\
"HUMAN LEFT ON THE FACE OF THE PLANET.\n"\
"CANNIBAL MUTATIONS, CARNIVOROUS ALIENS,\n"\
"AND EVIL SPIRITS ARE YOUR ONLY NEIGHBORS.\n"\
"YOU SIT BACK AND WAIT FOR DEATH, CONTENT\n"\
"THAT YOU HAVE SAVED YOUR SPECIES.\n"\
"\n"\
"BUT THEN, EARTH CONTROL BEAMS DOWN A\n"\
"MESSAGE FROM SPACE: \"SENSORS HAVE LOCATED\n"\
"THE SOURCE OF THE ALIEN INVASION. IF YOU\n"\
"GO THERE, YOU MAY BE ABLE TO BLOCK THEIR\n"\
"ENTRY.  THE ALIEN BASE IS IN THE HEART OF\n"\
"YOUR OWN HOME CITY, NOT FAR FROM THE\n"\
"STARPORT.\" SLOWLY AND PAINFULLY YOU GET\n"\
"UP AND RETURN TO THE FRAY."


// After level 20, put this:
#define C3TEXT \
"YOU ARE AT THE CORRUPT HEART OF THE CITY,\n"\
"SURROUNDED BY THE CORPSES OF YOUR ENEMIES.\n"\
"YOU SEE NO WAY TO DESTROY THE CREATURES'\n"\
"ENTRYWAY ON THIS SIDE, SO YOU CLENCH YOUR\n"\
"TEETH AND PLUNGE THROUGH IT.\n"\
"\n"\
"THERE MUST BE A WAY TO CLOSE IT ON THE\n"\
"OTHER SIDE. WHAT DO YOU CARE IF YOU'VE\n"\
"GOT TO GO THROUGH HELL TO GET TO IT?"


// After level 29, put this:
#define C4TEXT \
"THE HORRENDOUS VISAGE OF THE BIGGEST\n"\
"DEMON YOU'VE EVER SEEN CRUMBLES BEFORE\n"\
"YOU, AFTER YOU PUMP YOUR ROCKETS INTO\n"\
"HIS EXPOSED BRAIN. THE MONSTER SHRIVELS\n"\
"UP AND DIES, ITS THRASHING LIMBS\n"\
"DEVASTATING UNTOLD MILES OF HELL'S\n"\
"SURFACE.\n"\
"\n"\
"YOU'VE DONE IT. THE INVASION IS OVER.\n"\
"EARTH IS SAVED. HELL IS A WRECK. YOU\n"\
"WONDER WHERE BAD FOLKS WILL GO WHEN THEY\n"\
"DIE, NOW. WIPING THE SWEAT FROM YOUR\n"\
"FOREHEAD YOU BEGIN THE LONG TREK BACK\n"\
"HOME. REBUILDING EARTH OUGHT TO BE A\n"\
"LOT MORE FUN THAN RUINING IT WAS.\n"



// Before level 31, put this:
#define C5TEXT \
"CONGRATULATIONS, YOU'VE FOUND THE SECRET\n"\
"LEVEL! LOOKS LIKE IT'S BEEN BUILT BY\n"\
"HUMANS, RATHER THAN DEMONS. YOU WONDER\n"\
"WHO THE INMATES OF THIS CORNER OF HELL\n"\
"WILL BE."


// Before level 32, put this:
#define C6TEXT \
"CONGRATULATIONS, YOU'VE FOUND THE\n"\
"SUPER SECRET LEVEL!  YOU'D BETTER\n"\
"BLAZE THROUGH THIS ONE!\n"


// after map 06        
#define P1TEXT  \
"You gloat over the steaming carcass of the\n"\
"Guardian.  With its death, you've wrested\n"\
"the Accelerator from the stinking claws\n"\
"of Hell.  You relax and glance around the\n"\
"room.  Damn!  There was supposed to be at\n"\
"least one working prototype, but you can't\n"\
"see it. The demons must have taken it.\n"\
"\n"\
"You must find the prototype, or all your\n"\
"struggles will have been wasted. Keep\n"\
"moving, keep fighting, keep killing.\n"\
"Oh yes, keep living, too."


// after map 11
#define P2TEXT \
"Even the deadly Arch-Vile labyrinth could\n"\
"not stop you, and you've gotten to the\n"\
"prototype Accelerator which is soon\n"\
"efficiently and permanently deactivated.\n"\
"\n"\
"You're good at that kind of thing."


// after map 20
#define P3TEXT \
"You've bashed and battered your way into\n"\
"the heart of the devil-hive.  Time for a\n"\
"Search-and-Destroy mission, aimed at the\n"\
"Gatekeeper, whose foul offspring is\n"\
"cascading to Earth.  Yeah, he's bad. But\n"\
"you know who's worse!\n"\
"\n"\
"Grinning evilly, you check your gear, and\n"\
"get ready to give the bastard a little Hell\n"\
"of your own making!"

// after map 30
#define P4TEXT \
"The Gatekeeper's evil face is splattered\n"\
"all over the place.  As its tattered corpse\n"\
"collapses, an inverted Gate forms and\n"\
"sucks down the shards of the last\n"\
"prototype Accelerator, not to mention the\n"\
"few remaining demons.  You're done. Hell\n"\
"has gone back to pounding bad dead folks \n"\
"instead of good live ones.  Remember to\n"\
"tell your grandkids to put a rocket\n"\
"launcher in your coffin. If you go to Hell\n"\
"when you die, you'll need it for some\n"\
"final cleaning-up ..."

// before map 31
#define P5TEXT \
"You've found the second-hardest level we\n"\
"got. Hope you have a saved game a level or\n"\
"two previous.  If not, be prepared to die\n"\
"aplenty. For master marines only."

// before map 32
#define P6TEXT \
"Betcha wondered just what WAS the hardest\n"\
"level we had ready for ya?  Now you know.\n"\
"No one gets out alive."


#define T1TEXT \
"You've fought your way out of the infested\n"\
"experimental labs.   It seems that UAC has\n"\
"once again gulped it down.  With their\n"\
"high turnover, it must be hard for poor\n"\
"old UAC to buy corporate health insurance\n"\
"nowadays..\n"\
"\n"\
"Ahead lies the military complex, now\n"\
"swarming with diseased horrors hot to get\n"\
"their teeth into you. With luck, the\n"\
"complex still has some warlike ordnance\n"\
"laying around."


#define T2TEXT \
"You hear the grinding of heavy machinery\n"\
"ahead.  You sure hope they're not stamping\n"\
"out new hellspawn, but you're ready to\n"\
"ream out a whole herd if you have to.\n"\
"They might be planning a blood feast, but\n"\
"you feel about as mean as two thousand\n"\
"maniacs packed into one mad killer.\n"\
"\n"\
"You don't plan to go down easy."


#define T3TEXT \
"The vista opening ahead looks real damn\n"\
"familiar. Smells familiar, too -- like\n"\
"fried excrement. You didn't like this\n"\
"place before, and you sure as hell ain't\n"\
"planning to like it now. The more you\n"\
"brood on it, the madder you get.\n"\
"Hefting your gun, an evil grin trickles\n"\
"onto your face. Time to take some names."

#define T4TEXT \
"Suddenly, all is silent, from one horizon\n"\
"to the other. The agonizing echo of Hell\n"\
"fades away, the nightmare sky turns to\n"\
"blue, the heaps of monster corpses start \n"\
"to evaporate along with the evil stench \n"\
"that filled the air. Jeeze, maybe you've\n"\
"done it. Have you really won?\n"\
"\n"\
"Something rumbles in the distance.\n"\
"A blue light begins to glow inside the\n"\
"ruined skull of the demon-spitter."


#define T5TEXT \
"What now? Looks totally different. Kind\n"\
"of like King Tut's condo. Well,\n"\
"whatever's here can't be any worse\n"\
"than usual. Can it?  Or maybe it's best\n"\
"to let sleeping gods lie.."


#define T6TEXT \
"Time for a vacation. You've burst the\n"\
"bowels of hell and by golly you're ready\n"\
"for a break. You mutter to yourself,\n"\
"Maybe someone else can kick Hell's ass\n"\
"next time around. Ahead lies a quiet town,\n"\
"with peaceful flowing water, quaint\n"\
"buildings, and presumably no Hellspawn.\n"\
"\n"\
"As you step off the transport, you hear\n"\
"the stomp of a cyberdemon's iron shoe."


//
// Character cast strings F_FINALE.C
//
#define CC_ZOMBIE   "ZOMBIEMAN"
#define CC_SHOTGUN  "SHOTGUN GUY"
#define CC_HEAVY    "HEAVY WEAPON DUDE"
#define CC_IMP      "IMP"
#define CC_DEMON    "DEMON"
#define CC_LOST     "LOST SOUL"
#define CC_CACO     "CACODEMON"
#define CC_HELL     "HELL KNIGHT"
#define CC_BARON    "BARON OF HELL"
#define CC_ARACH    "ARACHNOTRON"
#define CC_PAIN     "PAIN ELEMENTAL"
#define CC_REVEN    "REVENANT"
#define CC_MANCU    "MANCUBUS"
#define CC_ARCH     "ARCH-VILE"
#define CC_SPIDER   "THE SPIDER MASTERMIND"
#define CC_CYBER    "THE CYBERDEMON"
#define CC_HERO     "OUR HERO"


#endif


#ifndef __D_THINK__
#define __D_THINK__


//
// Experimental stuff.
// To compile this as "ANSI C with classes"
//  we will need to handle the various
//  action functions cleanly.
//
typedef void (*actionf_v)();
typedef void (*actionf_p1)(void*);
typedef void (*actionf_p2)(void*, void*);

typedef union
{
    actionf_p1 acp1;
    actionf_v  acv;
    actionf_p2 acp2;
} actionf_t;


// Historically, "think_t" is yet another
//  function pointer to a routine to handle
//  an actor.
typedef actionf_t think_t;


// Doubly linked list of actors.
typedef struct thinker_s
{
    struct thinker_s* prev;
    struct thinker_s* next;
    think_t function;
    long long pad;
} thinker_t;


#endif


#ifndef __DOOM_CONFIG_H__
#define __DOOM_CONFIG_H__


#if defined(WIN32)
#define DOOM_WIN32
#elif defined(__APPLE__)
#define DOOM_APPLE
#else
#define DOOM_LINUX
#endif


//#include "DOOM.h"


#define doom_abs(x) ((x) < 0 ? -(x) : (x))


extern char error_buf[260];
extern int doom_flags;
extern doom_print_fn doom_print;
extern doom_malloc_fn doom_malloc;
extern doom_free_fn doom_free;
extern doom_open_fn doom_open;
extern doom_close_fn doom_close;
extern doom_read_fn doom_read;
extern doom_write_fn doom_write;
extern doom_seek_fn doom_seek;
extern doom_tell_fn doom_tell;
extern doom_eof_fn doom_eof;
extern doom_gettime_fn doom_gettime;
extern doom_exit_fn doom_exit;
extern doom_getenv_fn doom_getenv;


const char* doom_itoa(int i, int radix);
const char* doom_ctoa(char c);
const char* doom_ptoa(void* p);
void doom_memset(void* ptr, int value, int num);
void* doom_memcpy(void* destination, const void* source, int num);
int doom_fprint(void* handle, const char* str);
int doom_strlen(const char* str);
char* doom_concat(char* dst, const char* src);
char* doom_strcpy(char* destination, const char* source);
char* doom_strncpy(char* destination, const char* source, int num);
int doom_strcmp(const char* str1, const char* str2);
int doom_strncmp(const char* str1, const char* str2, int n);
int doom_strcasecmp(const char* str1, const char* str2);
int doom_strncasecmp(const char* str1, const char* str2, int n);
int doom_atoi(const char* str);
int doom_atox(const char* str);
int doom_toupper(int c);


#endif
#ifndef __DOOMDEF__
#define __DOOMDEF__






//
// Global parameters/defines.
//
// DOOM version
enum
{
    VERSION = 110
};


// Game mode handling - identify IWAD version
//  to handle IWAD dependend animations etc.
typedef enum
{
    shareware,      // DOOM 1 shareware, E1, M9
    registered,     // DOOM 1 registered, E3, M27
    commercial,     // DOOM 2 retail, E1 M34
    // DOOM 2 german edition not handled
    retail,         // DOOM 1 retail, E4, M36
    indetermined    // Well, no IWAD found.
} GameMode_t;


// Mission packs - might be useful for TC stuff?
typedef enum
{
    doom,       // DOOM 1
    doom2,      // DOOM 2
    pack_tnt,   // TNT mission pack
    pack_plut,  // Plutonia pack
    none
} GameMission_t;


// Identify language to use, software localization.
typedef enum
{
    english,
    french,
    german,
    unknown
} Language_t;


// If rangecheck is undefined,
// most parameter validation debugging code will not be compiled
#define RANGECHECK

//
// For resize of screen, at start of game.
// It will not work dynamically, see visplanes.
//
#define BASE_WIDTH 320

// It is educational but futile to change this
//  scaling e.g. to 2. Drawing of status bar,
//  menues etc. is tied to the scale implied
//  by the graphics.
#define SCREEN_MUL 1
#define INV_ASPECT_RATIO 0.625 // 0.75, ideally

// Defines suck. C sucks.
// C++ might sucks for OOP, but it sure is a better C.
// So there.
// extern int SCREENWIDTH;
#define SCREENWIDTH 320
#define SCREENHEIGHT 200

// The maximum number of players, multiplayer/networking.
#define MAXPLAYERS 4

// State updates, number of tics / second.
#if defined(DOOM_FAST_TICK)
#define TICKMUL 2
#else
#define TICKMUL 1
#endif
#define TICRATE (35 * TICKMUL)


// The current state of the game: whether we are
// playing, gazing at the intermission screen,
// the game final animation, or a demo. 
typedef enum
{
    GS_LEVEL,
    GS_INTERMISSION,
    GS_FINALE,
    GS_DEMOSCREEN
} gamestate_t;


//
// Difficulty/skill settings/filters.
//

// Skill flags.
#define MTF_EASY    1
#define MTF_NORMAL  2
#define MTF_HARD    4

// Deaf monsters/do not react to sound.
#define MTF_AMBUSH  8


typedef enum
{
    sk_baby,
    sk_easy,
    sk_medium,
    sk_hard,
    sk_nightmare
} skill_t;


//
// Key cards.
//
typedef enum
{
    it_bluecard,
    it_yellowcard,
    it_redcard,
    it_blueskull,
    it_yellowskull,
    it_redskull,
    NUMCARDS
} card_t;


// The defined weapons,
// including a marker indicating
// user has not changed weapon.
typedef enum
{
    wp_fist,
    wp_pistol,
    wp_shotgun,
    wp_chaingun,
    wp_missile,
    wp_plasma,
    wp_bfg,
    wp_chainsaw,
    wp_supershotgun,
    NUMWEAPONS,
    // No pending weapon change.
    wp_nochange
} weapontype_t;


// Ammunition types defined.
typedef enum
{
    am_clip,    // Pistol / chaingun ammo.
    am_shell,   // Shotgun / double barreled shotgun.
    am_cell,    // Plasma rifle, BFG.
    am_misl,    // Missile launcher.
    NUMAMMO,
    am_noammo   // Unlimited for chainsaw / fist.        
} ammotype_t;


// Power up artifacts.
typedef enum
{
    pw_invulnerability,
    pw_strength,
    pw_invisibility,
    pw_ironfeet,
    pw_allmap,
    pw_infrared,
    NUMPOWERS
} powertype_t;


//
// Power up durations,
//  how many seconds till expiration,
//  assuming TICRATE is 35 ticks/second.
//
typedef enum
{
    INVULNTICS = (30 * TICRATE),
    INVISTICS = (60 * TICRATE),
    INFRATICS = (120 * TICRATE),
    IRONTICS = (60 * TICRATE)
} powerduration_t;


//
// DOOM keyboard definition.
// This is the stuff configured by Setup.Exe.
// Most key data are simple ascii (uppercased).
//
#define KEY_RIGHTARROW  0xae
#define KEY_LEFTARROW   0xac
#define KEY_UPARROW     0xad
#define KEY_DOWNARROW   0xaf
#define KEY_ESCAPE      27
#define KEY_ENTER       13
#define KEY_TAB         9
#define KEY_F1          (0x80+0x3b)
#define KEY_F2          (0x80+0x3c)
#define KEY_F3          (0x80+0x3d)
#define KEY_F4          (0x80+0x3e)
#define KEY_F5          (0x80+0x3f)
#define KEY_F6          (0x80+0x40)
#define KEY_F7          (0x80+0x41)
#define KEY_F8          (0x80+0x42)
#define KEY_F9          (0x80+0x43)
#define KEY_F10         (0x80+0x44)
#define KEY_F11         (0x80+0x57)
#define KEY_F12         (0x80+0x58)

#define KEY_BACKSPACE   127
#define KEY_PAUSE       0xff

#define KEY_EQUALS      0x3d
#define KEY_MINUS       0x2d

#define KEY_RSHIFT      (0x80+0x36)
#define KEY_RCTRL       (0x80+0x1d)
#define KEY_RALT        (0x80+0x38)

#define KEY_LALT        KEY_RALT


#endif          // __DOOMDEF__


#ifndef __D_ITEMS__
#define __D_ITEMS__


//#include "doomdef.h"


// Weapon info: sprite frames, ammunition use.
typedef struct
{
    ammotype_t ammo;
    int upstate;
    int downstate;
    int readystate;
    int atkstate;
    int flashstate;
} weaponinfo_t;


extern weaponinfo_t weaponinfo[NUMWEAPONS];


#endif


#ifndef __DOOMTYPE__
#define __DOOMTYPE__


// Fixed to use builtin bool type with C++.
#ifdef __cplusplus
typedef bool doom_boolean;
#else
#if !defined(false) && !defined(true)
typedef enum
{
    false, true
} doom_boolean;
#else
typedef int doom_boolean;
#endif
#endif


typedef unsigned char byte;


#define DOOM_MAXCHAR    ((char)0x7f)
#define DOOM_MAXSHORT   ((short)0x7fff)

// Max pos 32-bit int.
#define DOOM_MAXINT     ((int)0x7fffffff)        
#define DOOM_MAXLONG    ((long)0x7fffffff)
#define DOOM_MINCHAR    ((char)0x80)
#define DOOM_MINSHORT   ((short)0x8000)

// Max negative 32-bit integer.
#define DOOM_MININT     ((int)0x80000000)        
#define DOOM_MINLONG    ((long)0x80000000)


#endif


#ifndef __D_EVENT__
#define __D_EVENT__


//#include "doomtype.h"


//
// Event handling.
//

// Input event types.
typedef enum
{
    ev_keydown,
    ev_keyup,
    ev_mouse,
    ev_joystick
} evtype_t;


// Event structure.
typedef struct
{
    evtype_t type;
    int data1;  // keys / mouse/joystick buttons
    int data2;  // mouse/joystick x move
    int data3;  // mouse/joystick y move
} event_t;


typedef enum
{
    ga_nothing,
    ga_loadlevel,
    ga_newgame,
    ga_loadgame,
    ga_savegame,
    ga_playdemo,
    ga_completed,
    ga_victory,
    ga_worlddone,
    ga_screenshot
} gameaction_t;


//
// Button/action code definitions.
//
typedef enum
{
    // Press "Fire".
    BT_ATTACK = 1,
    // Use button, to open doors, activate switches.
    BT_USE = 2,

    // Flag: game events, not really buttons.
    BT_SPECIAL = 128,
    BT_SPECIALMASK = 3,

    // Flag, weapon change pending.
    // If true, the next 3 bits hold weapon num.
    BT_CHANGE = 4,
    // The 3bit weapon mask and shift, convenience.
    BT_WEAPONMASK = (8 + 16 + 32),
    BT_WEAPONSHIFT = 3,

    // Pause the game.
    BTS_PAUSE = 1,
    // Save the game at each console.
    BTS_SAVEGAME = 2,

    // Savegame slot numbers
    //  occupy the second byte of buttons.    
    BTS_SAVEMASK = (4 + 8 + 16),
    BTS_SAVESHIFT = 2,
} buttoncode_t;


//
// GLOBAL VARIABLES
//
#define MAXEVENTS (64 * 64) // [pd] Crank up the number because we pump them faster

extern event_t events[MAXEVENTS];
extern int eventhead;
extern int eventtail;

extern gameaction_t gameaction;


#endif


#ifndef __AMMAP_H__
#define __AMMAP_H__


//#include "d_event.h"


// Used by ST StatusBar stuff.
#define AM_MSGHEADER (('a'<<24)+('m'<<16))
#define AM_MSGENTERED (AM_MSGHEADER | ('e'<<8))
#define AM_MSGEXITED (AM_MSGHEADER | ('x'<<8))


// Called by main loop.
doom_boolean AM_Responder(event_t* ev);

// Called by main loop.
void AM_Ticker(void);

// Called by main loop,
// called instead of view drawer if automap active.
void AM_Drawer(void);

// Called to force the automap to quit
// if the level is completed while it is up.
void AM_Stop(void);


#endif


#ifndef __D_MAIN__
#define __D_MAIN__


//#include "d_event.h"


#define MAXWADFILES 20


extern char* wadfiles[MAXWADFILES];


void D_AddFile(char* file);

//
// D_DoomMain()
// Not a globally visible function, just included for source reference,
// calls all startup code, parses command line options.
// If not overrided by user input, calls N_AdvanceDemo.
//
void D_DoomMain(void);

// Called by IO functions when input is detected.
void D_PostEvent(event_t* ev);

//
// BASE LEVEL
//
void D_PageTicker(void);
void D_PageDrawer(void);
void D_AdvanceDemo(void);
void D_StartTitle(void);


#endif
#ifndef __D_TEXTUR__
#define __D_TEXTUR__


//#include "doomtype.h"


//
// Flats?
//
// a pic is an unmasked block of pixels
typedef struct
{
    byte width;
    byte height;
    byte data;
} pic_t;


#endif


#ifndef __D_TICCMD__
#define __D_TICCMD__


//#include "doomtype.h"


// The data sampled per tick (single player)
// and transmitted to other peers (multiplayer).
// Mainly movements/button commands per game tick,
// plus a checksum for internal state consistency.
typedef struct
{
    char forwardmove;   // *2048 for move
    char sidemove;      // *2048 for move
    short angleturn;    // <<16 for angle delta
    short consistancy;  // checks for net game
    byte chatchar;
    byte buttons;
} ticcmd_t;


#endif


#ifndef __DOOMDATA__
#define __DOOMDATA__


// The most basic types we use, portability.
//#include "doomtype.h"

// Some global defines, that configure the game.
//#include "doomdef.h"


//
// Map level types.
// The following data structures define the persistent format
// used in the lumps of the WAD files.
//

// Lump order in a map WAD: each map needs a couple of lumps
// to provide a complete scene geometry description.
enum
{
    ML_LABEL,       // A separator, name, ExMx or MAPxx
    ML_THINGS,      // Monsters, items..
    ML_LINEDEFS,    // LineDefs, from editing
    ML_SIDEDEFS,    // SideDefs, from editing
    ML_VERTEXES,    // Vertices, edited and BSP splits generated
    ML_SEGS,        // LineSegs, from LineDefs split by BSP
    ML_SSECTORS,    // SubSectors, list of LineSegs
    ML_NODES,       // BSP nodes
    ML_SECTORS,     // Sectors, from editing
    ML_REJECT,      // LUT, sector-sector visibility        
    ML_BLOCKMAP     // LUT, motion clipping, walls/grid element
};


// A single Vertex.
typedef struct
{
    short x;
    short y;
} mapvertex_t;


// A SideDef, defining the visual appearance of a wall,
// by setting textures and offsets.
typedef struct
{
    short textureoffset;
    short rowoffset;
    char toptexture[8];
    char bottomtexture[8];
    char midtexture[8];
    // Front sector, towards viewer.
    short sector;
} mapsidedef_t;


// A LineDef, as used for editing, and as input
// to the BSP builder.
typedef struct
{
    short v1;
    short v2;
    short flags;
    short special;
    short tag;
    // sidenum[1] will be -1 if one sided
    short sidenum[2];
} maplinedef_t;


//
// LineDef attributes.
//

// Solid, is an obstacle.
#define ML_BLOCKING 1

// Blocks monsters only.
#define ML_BLOCKMONSTERS 2

// Backside will not be present at all
//  if not two sided.
#define ML_TWOSIDED 4

// If a texture is pegged, the texture will have
// the end exposed to air held constant at the
// top or bottom of the texture (stairs or pulled
// down things) and will move with a height change
// of one of the neighbor sectors.
// Unpegged textures allways have the first row of
// the texture at the top pixel of the line for both
// top and bottom textures (use next to windows).

// upper texture unpegged
#define ML_DONTPEGTOP 8

// lower texture unpegged
#define ML_DONTPEGBOTTOM 16        

// In AutoMap: don't map as two sided: IT'S A SECRET!
#define ML_SECRET 32

// Sound rendering: don't let sound cross two of these.
#define ML_SOUNDBLOCK 64

// Don't draw on the automap at all.
#define ML_DONTDRAW 128

// Set if already seen, thus drawn in automap.
#define ML_MAPPED 256


// Sector definition, from editing.
typedef struct
{
    short floorheight;
    short ceilingheight;
    char floorpic[8];
    char ceilingpic[8];
    short lightlevel;
    short special;
    short tag;
} mapsector_t;


// SubSector, as generated by BSP.
typedef struct
{
    short numsegs;
    // Index of first one, segs are stored sequentially.
    short firstseg;
} mapsubsector_t;


// LineSeg, generated by splitting LineDefs
// using partition lines selected by BSP builder.
typedef struct
{
    short v1;
    short v2;
    short angle;
    short linedef;
    short side;
    short offset;
} mapseg_t;


//
// BSP node structure.
//

// Indicate a leaf.
#define NF_SUBSECTOR 0x8000

typedef struct
{
    // Partition line from (x,y) to x+dx,y+dy)
    short x;
    short y;
    short dx;
    short dy;

    // Bounding box for each child,
    // clip against view frustum.
    short bbox[2][4];

    // If NF_SUBSECTOR its a subsector,
    // else it's a node of another subtree.
    unsigned short children[2];
} mapnode_t;


// Thing definition, position, orientation and type,
// plus skill/visibility flags and attributes.
typedef struct
{
    short x;
    short y;
    short angle;
    short type;
    short options;
} mapthing_t;


#endif // __DOOMDATA__


#ifndef __DSTRINGS__
#define __DSTRINGS__


// All important printed strings.
// Language selection (message strings).
// Use -DFRENCH etc.

#ifdef FRENCH
//#include  "d_french.h" // Leave the extra space there, to throw off regex in PureDOOM.h creation
#else
//#include "d_englsh.h"
#endif


// Misc. other strings.
#define SAVEGAMENAME "doomsav"

//
// File locations,
//  relative to current position.
// Path names are OS-sensitive.
//
#define DEVMAPS "devmaps"
#define DEVDATA "devdata"

// Not done in french?

// QuitDOOM messages
#define NUM_QUITMESSAGES   22


extern char* endmsg[];


#endif


#ifndef __F_FINALE__
#define __F_FINALE__


//#include "doomtype.h"
//#include "d_event.h"


//
// FINALE
//

// Called by main loop.
doom_boolean F_Responder(event_t* ev);

// Called by main loop.
void F_Ticker(void);

// Called by main loop.
void F_Drawer(void);

void F_StartFinale(void);


#endif


#ifndef __F_WIPE_H__
#define __F_WIPE_H__


//
// SCREEN WIPE PACKAGE
//

enum
{
    // simple gradual pixel change for 8-bit only
    wipe_ColorXForm,

    // weird screen melt
    wipe_Melt,

    wipe_NUMWIPES
};


int wipe_StartScreen(int x, int y, int width, int height);
int wipe_EndScreen(int x, int y, int width, int height);
int wipe_ScreenWipe(int wipeno, int x, int y, int width, int height, int ticks);


#endif


#ifndef __G_GAME__
#define __G_GAME__


//#include "doomdef.h"
//#include "d_event.h"


//
// GAME
//
void G_DeathMatchSpawnPlayer(int playernum);

void G_InitNew(skill_t skill, int episode, int map);

// Can be called by the startup code or M_Responder.
// A normal game starts at map 1,
// but a warp test can start elsewhere
void G_DeferedInitNew(skill_t skill, int episode, int map);

void G_DeferedPlayDemo(char* demo);

// Can be called by the startup code or M_Responder,
// calls P_SetupLevel or W_EnterWorld.
void G_LoadGame(char* name);

void G_DoLoadGame(void);

// Called by M_Responder.
void G_SaveGame(int slot, char* description);

// Only called by startup code.
void G_RecordDemo(char* name);

void G_BeginRecording(void);

void G_TimeDemo(char* name);
doom_boolean G_CheckDemoStatus(void);

void G_ExitLevel(void);
void G_SecretExitLevel(void);

void G_WorldDone(void);

void G_Ticker(void);
doom_boolean G_Responder(event_t* ev);

void G_ScreenShot(void);


#endif


#ifndef __HU_STUFF_H__
#define __HU_STUFF_H__


//#include "d_event.h"


//
// Globally visible constants.
//
#define HU_FONTSTART '!'    // the first font characters
#define HU_FONTEND '_'      // the last font characters

// Calculate # of glyphs in font.
#define HU_FONTSIZE (HU_FONTEND - HU_FONTSTART + 1)        

#define HU_BROADCAST 5

#define HU_MSGREFRESH KEY_ENTER
#define HU_MSGX 0
#define HU_MSGY 0
#define HU_MSGWIDTH 64  // in characters
#define HU_MSGHEIGHT 1  // in lines

#define HU_MSGTIMEOUT (4*TICRATE)


//
// HEADS UP TEXT
//

void HU_Init(void);
void HU_Start(void);
doom_boolean HU_Responder(event_t* ev);
void HU_Ticker(void);
void HU_Drawer(void);
char HU_dequeueChatChar(void);
void HU_Erase(void);


#endif


#ifndef __I_NET__
#define __I_NET__


// Called by D_DoomMain.

void I_InitNetwork (void);
void I_NetCmd (void);


#endif


#ifndef __I_SYSTEM__
#define __I_SYSTEM__


//#include "d_ticcmd.h"
//#include "d_event.h"


// Called by DoomMain.
void I_Init(void);

// Called by startup code
// to get the ammount of memory to malloc
// for the zone management.
byte* I_ZoneBase(int* size);

// Called by D_DoomLoop,
// returns current time in tics.
int I_GetTime(void);

// Called by D_DoomLoop,
// called before processing any tics in a frame
// (just after displaying a frame).
// Time consuming syncronous operations
// are performed here (joystick reading).
// Can call D_PostEvent.
void I_StartFrame(void);

// Called by D_DoomLoop,
// called before processing each tic in a frame.
// Quick syncronous operations are performed here.
// Can call D_PostEvent.
void I_StartTic(void);

// Asynchronous interrupt functions should maintain private queues
// that are read by the synchronous functions
// to be converted into events.

// Either returns a null ticcmd,
// or calls a loadable driver to build it.
// This ticcmd will then be modified by the gameloop
// for normal input.
ticcmd_t* I_BaseTiccmd(void);

// Called by M_Responder when quit is selected.
// Clean exit, displays sell blurb.
void I_Quit(void);

// Allocates from low memory under dos,
// just mallocs under unix
byte* I_AllocLow(int length);

void I_Tactile(int on, int off, int total);

void I_Error(char* error);


#endif


#ifndef __I_VIDEO__
#define __I_VIDEO__


//#include "doomtype.h"


// Called by D_DoomMain,
// determines the hardware configuration
// and sets up the video mode
void I_InitGraphics(void);

void I_ShutdownGraphics(void);

// Takes full 8 bit values.
void I_SetPalette(byte* palette);

void I_UpdateNoBlit(void);
void I_FinishUpdate(void);

// Wait for vertical retrace or pause a bit.
void I_WaitVBL(int count);

void I_ReadScreen(byte* scr);

void I_BeginRead(void);
void I_EndRead(void);


#endif


#ifndef __INFO__
#define __INFO__


// Needed for action function pointer handling.
//#include "d_think.h"


typedef enum
{
    SPR_TROO,
    SPR_SHTG,
    SPR_PUNG,
    SPR_PISG,
    SPR_PISF,
    SPR_SHTF,
    SPR_SHT2,
    SPR_CHGG,
    SPR_CHGF,
    SPR_MISG,
    SPR_MISF,
    SPR_SAWG,
    SPR_PLSG,
    SPR_PLSF,
    SPR_BFGG,
    SPR_BFGF,
    SPR_BLUD,
    SPR_PUFF,
    SPR_BAL1,
    SPR_BAL2,
    SPR_PLSS,
    SPR_PLSE,
    SPR_MISL,
    SPR_BFS1,
    SPR_BFE1,
    SPR_BFE2,
    SPR_TFOG,
    SPR_IFOG,
    SPR_PLAY,
    SPR_POSS,
    SPR_SPOS,
    SPR_VILE,
    SPR_FIRE,
    SPR_FATB,
    SPR_FBXP,
    SPR_SKEL,
    SPR_MANF,
    SPR_FATT,
    SPR_CPOS,
    SPR_SARG,
    SPR_HEAD,
    SPR_BAL7,
    SPR_BOSS,
    SPR_BOS2,
    SPR_SKUL,
    SPR_SPID,
    SPR_BSPI,
    SPR_APLS,
    SPR_APBX,
    SPR_CYBR,
    SPR_PAIN,
    SPR_SSWV,
    SPR_KEEN,
    SPR_BBRN,
    SPR_BOSF,
    SPR_ARM1,
    SPR_ARM2,
    SPR_BAR1,
    SPR_BEXP,
    SPR_FCAN,
    SPR_BON1,
    SPR_BON2,
    SPR_BKEY,
    SPR_RKEY,
    SPR_YKEY,
    SPR_BSKU,
    SPR_RSKU,
    SPR_YSKU,
    SPR_STIM,
    SPR_MEDI,
    SPR_SOUL,
    SPR_PINV,
    SPR_PSTR,
    SPR_PINS,
    SPR_MEGA,
    SPR_SUIT,
    SPR_PMAP,
    SPR_PVIS,
    SPR_CLIP,
    SPR_AMMO,
    SPR_ROCK,
    SPR_BROK,
    SPR_CELL,
    SPR_CELP,
    SPR_SHEL,
    SPR_SBOX,
    SPR_BPAK,
    SPR_BFUG,
    SPR_MGUN,
    SPR_CSAW,
    SPR_LAUN,
    SPR_PLAS,
    SPR_SHOT,
    SPR_SGN2,
    SPR_COLU,
    SPR_SMT2,
    SPR_GOR1,
    SPR_POL2,
    SPR_POL5,
    SPR_POL4,
    SPR_POL3,
    SPR_POL1,
    SPR_POL6,
    SPR_GOR2,
    SPR_GOR3,
    SPR_GOR4,
    SPR_GOR5,
    SPR_SMIT,
    SPR_COL1,
    SPR_COL2,
    SPR_COL3,
    SPR_COL4,
    SPR_CAND,
    SPR_CBRA,
    SPR_COL6,
    SPR_TRE1,
    SPR_TRE2,
    SPR_ELEC,
    SPR_CEYE,
    SPR_FSKU,
    SPR_COL5,
    SPR_TBLU,
    SPR_TGRN,
    SPR_TRED,
    SPR_SMBT,
    SPR_SMGT,
    SPR_SMRT,
    SPR_HDB1,
    SPR_HDB2,
    SPR_HDB3,
    SPR_HDB4,
    SPR_HDB5,
    SPR_HDB6,
    SPR_POB1,
    SPR_POB2,
    SPR_BRS1,
    SPR_TLMP,
    SPR_TLP2,
    NUMSPRITES
} spritenum_t;


typedef enum
{
    S_NULL,
    S_LIGHTDONE,
    S_PUNCH,
    S_PUNCHDOWN,
    S_PUNCHUP,
    S_PUNCH1,
    S_PUNCH2,
    S_PUNCH3,
    S_PUNCH4,
    S_PUNCH5,
    S_PISTOL,
    S_PISTOLDOWN,
    S_PISTOLUP,
    S_PISTOL1,
    S_PISTOL2,
    S_PISTOL3,
    S_PISTOL4,
    S_PISTOLFLASH,
    S_SGUN,
    S_SGUNDOWN,
    S_SGUNUP,
    S_SGUN1,
    S_SGUN2,
    S_SGUN3,
    S_SGUN4,
    S_SGUN5,
    S_SGUN6,
    S_SGUN7,
    S_SGUN8,
    S_SGUN9,
    S_SGUNFLASH1,
    S_SGUNFLASH2,
    S_DSGUN,
    S_DSGUNDOWN,
    S_DSGUNUP,
    S_DSGUN1,
    S_DSGUN2,
    S_DSGUN3,
    S_DSGUN4,
    S_DSGUN5,
    S_DSGUN6,
    S_DSGUN7,
    S_DSGUN8,
    S_DSGUN9,
    S_DSGUN10,
    S_DSNR1,
    S_DSNR2,
    S_DSGUNFLASH1,
    S_DSGUNFLASH2,
    S_CHAIN,
    S_CHAINDOWN,
    S_CHAINUP,
    S_CHAIN1,
    S_CHAIN2,
    S_CHAIN3,
    S_CHAINFLASH1,
    S_CHAINFLASH2,
    S_MISSILE,
    S_MISSILEDOWN,
    S_MISSILEUP,
    S_MISSILE1,
    S_MISSILE2,
    S_MISSILE3,
    S_MISSILEFLASH1,
    S_MISSILEFLASH2,
    S_MISSILEFLASH3,
    S_MISSILEFLASH4,
    S_SAW,
    S_SAWB,
    S_SAWDOWN,
    S_SAWUP,
    S_SAW1,
    S_SAW2,
    S_SAW3,
    S_PLASMA,
    S_PLASMADOWN,
    S_PLASMAUP,
    S_PLASMA1,
    S_PLASMA2,
    S_PLASMAFLASH1,
    S_PLASMAFLASH2,
    S_BFG,
    S_BFGDOWN,
    S_BFGUP,
    S_BFG1,
    S_BFG2,
    S_BFG3,
    S_BFG4,
    S_BFGFLASH1,
    S_BFGFLASH2,
    S_BLOOD1,
    S_BLOOD2,
    S_BLOOD3,
    S_PUFF1,
    S_PUFF2,
    S_PUFF3,
    S_PUFF4,
    S_TBALL1,
    S_TBALL2,
    S_TBALLX1,
    S_TBALLX2,
    S_TBALLX3,
    S_RBALL1,
    S_RBALL2,
    S_RBALLX1,
    S_RBALLX2,
    S_RBALLX3,
    S_PLASBALL,
    S_PLASBALL2,
    S_PLASEXP,
    S_PLASEXP2,
    S_PLASEXP3,
    S_PLASEXP4,
    S_PLASEXP5,
    S_ROCKET,
    S_BFGSHOT,
    S_BFGSHOT2,
    S_BFGLAND,
    S_BFGLAND2,
    S_BFGLAND3,
    S_BFGLAND4,
    S_BFGLAND5,
    S_BFGLAND6,
    S_BFGEXP,
    S_BFGEXP2,
    S_BFGEXP3,
    S_BFGEXP4,
    S_EXPLODE1,
    S_EXPLODE2,
    S_EXPLODE3,
    S_TFOG,
    S_TFOG01,
    S_TFOG02,
    S_TFOG2,
    S_TFOG3,
    S_TFOG4,
    S_TFOG5,
    S_TFOG6,
    S_TFOG7,
    S_TFOG8,
    S_TFOG9,
    S_TFOG10,
    S_IFOG,
    S_IFOG01,
    S_IFOG02,
    S_IFOG2,
    S_IFOG3,
    S_IFOG4,
    S_IFOG5,
    S_PLAY,
    S_PLAY_RUN1,
    S_PLAY_RUN2,
    S_PLAY_RUN3,
    S_PLAY_RUN4,
    S_PLAY_ATK1,
    S_PLAY_ATK2,
    S_PLAY_PAIN,
    S_PLAY_PAIN2,
    S_PLAY_DIE1,
    S_PLAY_DIE2,
    S_PLAY_DIE3,
    S_PLAY_DIE4,
    S_PLAY_DIE5,
    S_PLAY_DIE6,
    S_PLAY_DIE7,
    S_PLAY_XDIE1,
    S_PLAY_XDIE2,
    S_PLAY_XDIE3,
    S_PLAY_XDIE4,
    S_PLAY_XDIE5,
    S_PLAY_XDIE6,
    S_PLAY_XDIE7,
    S_PLAY_XDIE8,
    S_PLAY_XDIE9,
    S_POSS_STND,
    S_POSS_STND2,
    S_POSS_RUN1,
    S_POSS_RUN2,
    S_POSS_RUN3,
    S_POSS_RUN4,
    S_POSS_RUN5,
    S_POSS_RUN6,
    S_POSS_RUN7,
    S_POSS_RUN8,
    S_POSS_ATK1,
    S_POSS_ATK2,
    S_POSS_ATK3,
    S_POSS_PAIN,
    S_POSS_PAIN2,
    S_POSS_DIE1,
    S_POSS_DIE2,
    S_POSS_DIE3,
    S_POSS_DIE4,
    S_POSS_DIE5,
    S_POSS_XDIE1,
    S_POSS_XDIE2,
    S_POSS_XDIE3,
    S_POSS_XDIE4,
    S_POSS_XDIE5,
    S_POSS_XDIE6,
    S_POSS_XDIE7,
    S_POSS_XDIE8,
    S_POSS_XDIE9,
    S_POSS_RAISE1,
    S_POSS_RAISE2,
    S_POSS_RAISE3,
    S_POSS_RAISE4,
    S_SPOS_STND,
    S_SPOS_STND2,
    S_SPOS_RUN1,
    S_SPOS_RUN2,
    S_SPOS_RUN3,
    S_SPOS_RUN4,
    S_SPOS_RUN5,
    S_SPOS_RUN6,
    S_SPOS_RUN7,
    S_SPOS_RUN8,
    S_SPOS_ATK1,
    S_SPOS_ATK2,
    S_SPOS_ATK3,
    S_SPOS_PAIN,
    S_SPOS_PAIN2,
    S_SPOS_DIE1,
    S_SPOS_DIE2,
    S_SPOS_DIE3,
    S_SPOS_DIE4,
    S_SPOS_DIE5,
    S_SPOS_XDIE1,
    S_SPOS_XDIE2,
    S_SPOS_XDIE3,
    S_SPOS_XDIE4,
    S_SPOS_XDIE5,
    S_SPOS_XDIE6,
    S_SPOS_XDIE7,
    S_SPOS_XDIE8,
    S_SPOS_XDIE9,
    S_SPOS_RAISE1,
    S_SPOS_RAISE2,
    S_SPOS_RAISE3,
    S_SPOS_RAISE4,
    S_SPOS_RAISE5,
    S_VILE_STND,
    S_VILE_STND2,
    S_VILE_RUN1,
    S_VILE_RUN2,
    S_VILE_RUN3,
    S_VILE_RUN4,
    S_VILE_RUN5,
    S_VILE_RUN6,
    S_VILE_RUN7,
    S_VILE_RUN8,
    S_VILE_RUN9,
    S_VILE_RUN10,
    S_VILE_RUN11,
    S_VILE_RUN12,
    S_VILE_ATK1,
    S_VILE_ATK2,
    S_VILE_ATK3,
    S_VILE_ATK4,
    S_VILE_ATK5,
    S_VILE_ATK6,
    S_VILE_ATK7,
    S_VILE_ATK8,
    S_VILE_ATK9,
    S_VILE_ATK10,
    S_VILE_ATK11,
    S_VILE_HEAL1,
    S_VILE_HEAL2,
    S_VILE_HEAL3,
    S_VILE_PAIN,
    S_VILE_PAIN2,
    S_VILE_DIE1,
    S_VILE_DIE2,
    S_VILE_DIE3,
    S_VILE_DIE4,
    S_VILE_DIE5,
    S_VILE_DIE6,
    S_VILE_DIE7,
    S_VILE_DIE8,
    S_VILE_DIE9,
    S_VILE_DIE10,
    S_FIRE1,
    S_FIRE2,
    S_FIRE3,
    S_FIRE4,
    S_FIRE5,
    S_FIRE6,
    S_FIRE7,
    S_FIRE8,
    S_FIRE9,
    S_FIRE10,
    S_FIRE11,
    S_FIRE12,
    S_FIRE13,
    S_FIRE14,
    S_FIRE15,
    S_FIRE16,
    S_FIRE17,
    S_FIRE18,
    S_FIRE19,
    S_FIRE20,
    S_FIRE21,
    S_FIRE22,
    S_FIRE23,
    S_FIRE24,
    S_FIRE25,
    S_FIRE26,
    S_FIRE27,
    S_FIRE28,
    S_FIRE29,
    S_FIRE30,
    S_SMOKE1,
    S_SMOKE2,
    S_SMOKE3,
    S_SMOKE4,
    S_SMOKE5,
    S_TRACER,
    S_TRACER2,
    S_TRACEEXP1,
    S_TRACEEXP2,
    S_TRACEEXP3,
    S_SKEL_STND,
    S_SKEL_STND2,
    S_SKEL_RUN1,
    S_SKEL_RUN2,
    S_SKEL_RUN3,
    S_SKEL_RUN4,
    S_SKEL_RUN5,
    S_SKEL_RUN6,
    S_SKEL_RUN7,
    S_SKEL_RUN8,
    S_SKEL_RUN9,
    S_SKEL_RUN10,
    S_SKEL_RUN11,
    S_SKEL_RUN12,
    S_SKEL_FIST1,
    S_SKEL_FIST2,
    S_SKEL_FIST3,
    S_SKEL_FIST4,
    S_SKEL_MISS1,
    S_SKEL_MISS2,
    S_SKEL_MISS3,
    S_SKEL_MISS4,
    S_SKEL_PAIN,
    S_SKEL_PAIN2,
    S_SKEL_DIE1,
    S_SKEL_DIE2,
    S_SKEL_DIE3,
    S_SKEL_DIE4,
    S_SKEL_DIE5,
    S_SKEL_DIE6,
    S_SKEL_RAISE1,
    S_SKEL_RAISE2,
    S_SKEL_RAISE3,
    S_SKEL_RAISE4,
    S_SKEL_RAISE5,
    S_SKEL_RAISE6,
    S_FATSHOT1,
    S_FATSHOT2,
    S_FATSHOTX1,
    S_FATSHOTX2,
    S_FATSHOTX3,
    S_FATT_STND,
    S_FATT_STND2,
    S_FATT_RUN1,
    S_FATT_RUN2,
    S_FATT_RUN3,
    S_FATT_RUN4,
    S_FATT_RUN5,
    S_FATT_RUN6,
    S_FATT_RUN7,
    S_FATT_RUN8,
    S_FATT_RUN9,
    S_FATT_RUN10,
    S_FATT_RUN11,
    S_FATT_RUN12,
    S_FATT_ATK1,
    S_FATT_ATK2,
    S_FATT_ATK3,
    S_FATT_ATK4,
    S_FATT_ATK5,
    S_FATT_ATK6,
    S_FATT_ATK7,
    S_FATT_ATK8,
    S_FATT_ATK9,
    S_FATT_ATK10,
    S_FATT_PAIN,
    S_FATT_PAIN2,
    S_FATT_DIE1,
    S_FATT_DIE2,
    S_FATT_DIE3,
    S_FATT_DIE4,
    S_FATT_DIE5,
    S_FATT_DIE6,
    S_FATT_DIE7,
    S_FATT_DIE8,
    S_FATT_DIE9,
    S_FATT_DIE10,
    S_FATT_RAISE1,
    S_FATT_RAISE2,
    S_FATT_RAISE3,
    S_FATT_RAISE4,
    S_FATT_RAISE5,
    S_FATT_RAISE6,
    S_FATT_RAISE7,
    S_FATT_RAISE8,
    S_CPOS_STND,
    S_CPOS_STND2,
    S_CPOS_RUN1,
    S_CPOS_RUN2,
    S_CPOS_RUN3,
    S_CPOS_RUN4,
    S_CPOS_RUN5,
    S_CPOS_RUN6,
    S_CPOS_RUN7,
    S_CPOS_RUN8,
    S_CPOS_ATK1,
    S_CPOS_ATK2,
    S_CPOS_ATK3,
    S_CPOS_ATK4,
    S_CPOS_PAIN,
    S_CPOS_PAIN2,
    S_CPOS_DIE1,
    S_CPOS_DIE2,
    S_CPOS_DIE3,
    S_CPOS_DIE4,
    S_CPOS_DIE5,
    S_CPOS_DIE6,
    S_CPOS_DIE7,
    S_CPOS_XDIE1,
    S_CPOS_XDIE2,
    S_CPOS_XDIE3,
    S_CPOS_XDIE4,
    S_CPOS_XDIE5,
    S_CPOS_XDIE6,
    S_CPOS_RAISE1,
    S_CPOS_RAISE2,
    S_CPOS_RAISE3,
    S_CPOS_RAISE4,
    S_CPOS_RAISE5,
    S_CPOS_RAISE6,
    S_CPOS_RAISE7,
    S_TROO_STND,
    S_TROO_STND2,
    S_TROO_RUN1,
    S_TROO_RUN2,
    S_TROO_RUN3,
    S_TROO_RUN4,
    S_TROO_RUN5,
    S_TROO_RUN6,
    S_TROO_RUN7,
    S_TROO_RUN8,
    S_TROO_ATK1,
    S_TROO_ATK2,
    S_TROO_ATK3,
    S_TROO_PAIN,
    S_TROO_PAIN2,
    S_TROO_DIE1,
    S_TROO_DIE2,
    S_TROO_DIE3,
    S_TROO_DIE4,
    S_TROO_DIE5,
    S_TROO_XDIE1,
    S_TROO_XDIE2,
    S_TROO_XDIE3,
    S_TROO_XDIE4,
    S_TROO_XDIE5,
    S_TROO_XDIE6,
    S_TROO_XDIE7,
    S_TROO_XDIE8,
    S_TROO_RAISE1,
    S_TROO_RAISE2,
    S_TROO_RAISE3,
    S_TROO_RAISE4,
    S_TROO_RAISE5,
    S_SARG_STND,
    S_SARG_STND2,
    S_SARG_RUN1,
    S_SARG_RUN2,
    S_SARG_RUN3,
    S_SARG_RUN4,
    S_SARG_RUN5,
    S_SARG_RUN6,
    S_SARG_RUN7,
    S_SARG_RUN8,
    S_SARG_ATK1,
    S_SARG_ATK2,
    S_SARG_ATK3,
    S_SARG_PAIN,
    S_SARG_PAIN2,
    S_SARG_DIE1,
    S_SARG_DIE2,
    S_SARG_DIE3,
    S_SARG_DIE4,
    S_SARG_DIE5,
    S_SARG_DIE6,
    S_SARG_RAISE1,
    S_SARG_RAISE2,
    S_SARG_RAISE3,
    S_SARG_RAISE4,
    S_SARG_RAISE5,
    S_SARG_RAISE6,
    S_HEAD_STND,
    S_HEAD_RUN1,
    S_HEAD_ATK1,
    S_HEAD_ATK2,
    S_HEAD_ATK3,
    S_HEAD_PAIN,
    S_HEAD_PAIN2,
    S_HEAD_PAIN3,
    S_HEAD_DIE1,
    S_HEAD_DIE2,
    S_HEAD_DIE3,
    S_HEAD_DIE4,
    S_HEAD_DIE5,
    S_HEAD_DIE6,
    S_HEAD_RAISE1,
    S_HEAD_RAISE2,
    S_HEAD_RAISE3,
    S_HEAD_RAISE4,
    S_HEAD_RAISE5,
    S_HEAD_RAISE6,
    S_BRBALL1,
    S_BRBALL2,
    S_BRBALLX1,
    S_BRBALLX2,
    S_BRBALLX3,
    S_BOSS_STND,
    S_BOSS_STND2,
    S_BOSS_RUN1,
    S_BOSS_RUN2,
    S_BOSS_RUN3,
    S_BOSS_RUN4,
    S_BOSS_RUN5,
    S_BOSS_RUN6,
    S_BOSS_RUN7,
    S_BOSS_RUN8,
    S_BOSS_ATK1,
    S_BOSS_ATK2,
    S_BOSS_ATK3,
    S_BOSS_PAIN,
    S_BOSS_PAIN2,
    S_BOSS_DIE1,
    S_BOSS_DIE2,
    S_BOSS_DIE3,
    S_BOSS_DIE4,
    S_BOSS_DIE5,
    S_BOSS_DIE6,
    S_BOSS_DIE7,
    S_BOSS_RAISE1,
    S_BOSS_RAISE2,
    S_BOSS_RAISE3,
    S_BOSS_RAISE4,
    S_BOSS_RAISE5,
    S_BOSS_RAISE6,
    S_BOSS_RAISE7,
    S_BOS2_STND,
    S_BOS2_STND2,
    S_BOS2_RUN1,
    S_BOS2_RUN2,
    S_BOS2_RUN3,
    S_BOS2_RUN4,
    S_BOS2_RUN5,
    S_BOS2_RUN6,
    S_BOS2_RUN7,
    S_BOS2_RUN8,
    S_BOS2_ATK1,
    S_BOS2_ATK2,
    S_BOS2_ATK3,
    S_BOS2_PAIN,
    S_BOS2_PAIN2,
    S_BOS2_DIE1,
    S_BOS2_DIE2,
    S_BOS2_DIE3,
    S_BOS2_DIE4,
    S_BOS2_DIE5,
    S_BOS2_DIE6,
    S_BOS2_DIE7,
    S_BOS2_RAISE1,
    S_BOS2_RAISE2,
    S_BOS2_RAISE3,
    S_BOS2_RAISE4,
    S_BOS2_RAISE5,
    S_BOS2_RAISE6,
    S_BOS2_RAISE7,
    S_SKULL_STND,
    S_SKULL_STND2,
    S_SKULL_RUN1,
    S_SKULL_RUN2,
    S_SKULL_ATK1,
    S_SKULL_ATK2,
    S_SKULL_ATK3,
    S_SKULL_ATK4,
    S_SKULL_PAIN,
    S_SKULL_PAIN2,
    S_SKULL_DIE1,
    S_SKULL_DIE2,
    S_SKULL_DIE3,
    S_SKULL_DIE4,
    S_SKULL_DIE5,
    S_SKULL_DIE6,
    S_SPID_STND,
    S_SPID_STND2,
    S_SPID_RUN1,
    S_SPID_RUN2,
    S_SPID_RUN3,
    S_SPID_RUN4,
    S_SPID_RUN5,
    S_SPID_RUN6,
    S_SPID_RUN7,
    S_SPID_RUN8,
    S_SPID_RUN9,
    S_SPID_RUN10,
    S_SPID_RUN11,
    S_SPID_RUN12,
    S_SPID_ATK1,
    S_SPID_ATK2,
    S_SPID_ATK3,
    S_SPID_ATK4,
    S_SPID_PAIN,
    S_SPID_PAIN2,
    S_SPID_DIE1,
    S_SPID_DIE2,
    S_SPID_DIE3,
    S_SPID_DIE4,
    S_SPID_DIE5,
    S_SPID_DIE6,
    S_SPID_DIE7,
    S_SPID_DIE8,
    S_SPID_DIE9,
    S_SPID_DIE10,
    S_SPID_DIE11,
    S_BSPI_STND,
    S_BSPI_STND2,
    S_BSPI_SIGHT,
    S_BSPI_RUN1,
    S_BSPI_RUN2,
    S_BSPI_RUN3,
    S_BSPI_RUN4,
    S_BSPI_RUN5,
    S_BSPI_RUN6,
    S_BSPI_RUN7,
    S_BSPI_RUN8,
    S_BSPI_RUN9,
    S_BSPI_RUN10,
    S_BSPI_RUN11,
    S_BSPI_RUN12,
    S_BSPI_ATK1,
    S_BSPI_ATK2,
    S_BSPI_ATK3,
    S_BSPI_ATK4,
    S_BSPI_PAIN,
    S_BSPI_PAIN2,
    S_BSPI_DIE1,
    S_BSPI_DIE2,
    S_BSPI_DIE3,
    S_BSPI_DIE4,
    S_BSPI_DIE5,
    S_BSPI_DIE6,
    S_BSPI_DIE7,
    S_BSPI_RAISE1,
    S_BSPI_RAISE2,
    S_BSPI_RAISE3,
    S_BSPI_RAISE4,
    S_BSPI_RAISE5,
    S_BSPI_RAISE6,
    S_BSPI_RAISE7,
    S_ARACH_PLAZ,
    S_ARACH_PLAZ2,
    S_ARACH_PLEX,
    S_ARACH_PLEX2,
    S_ARACH_PLEX3,
    S_ARACH_PLEX4,
    S_ARACH_PLEX5,
    S_CYBER_STND,
    S_CYBER_STND2,
    S_CYBER_RUN1,
    S_CYBER_RUN2,
    S_CYBER_RUN3,
    S_CYBER_RUN4,
    S_CYBER_RUN5,
    S_CYBER_RUN6,
    S_CYBER_RUN7,
    S_CYBER_RUN8,
    S_CYBER_ATK1,
    S_CYBER_ATK2,
    S_CYBER_ATK3,
    S_CYBER_ATK4,
    S_CYBER_ATK5,
    S_CYBER_ATK6,
    S_CYBER_PAIN,
    S_CYBER_DIE1,
    S_CYBER_DIE2,
    S_CYBER_DIE3,
    S_CYBER_DIE4,
    S_CYBER_DIE5,
    S_CYBER_DIE6,
    S_CYBER_DIE7,
    S_CYBER_DIE8,
    S_CYBER_DIE9,
    S_CYBER_DIE10,
    S_PAIN_STND,
    S_PAIN_RUN1,
    S_PAIN_RUN2,
    S_PAIN_RUN3,
    S_PAIN_RUN4,
    S_PAIN_RUN5,
    S_PAIN_RUN6,
    S_PAIN_ATK1,
    S_PAIN_ATK2,
    S_PAIN_ATK3,
    S_PAIN_ATK4,
    S_PAIN_PAIN,
    S_PAIN_PAIN2,
    S_PAIN_DIE1,
    S_PAIN_DIE2,
    S_PAIN_DIE3,
    S_PAIN_DIE4,
    S_PAIN_DIE5,
    S_PAIN_DIE6,
    S_PAIN_RAISE1,
    S_PAIN_RAISE2,
    S_PAIN_RAISE3,
    S_PAIN_RAISE4,
    S_PAIN_RAISE5,
    S_PAIN_RAISE6,
    S_SSWV_STND,
    S_SSWV_STND2,
    S_SSWV_RUN1,
    S_SSWV_RUN2,
    S_SSWV_RUN3,
    S_SSWV_RUN4,
    S_SSWV_RUN5,
    S_SSWV_RUN6,
    S_SSWV_RUN7,
    S_SSWV_RUN8,
    S_SSWV_ATK1,
    S_SSWV_ATK2,
    S_SSWV_ATK3,
    S_SSWV_ATK4,
    S_SSWV_ATK5,
    S_SSWV_ATK6,
    S_SSWV_PAIN,
    S_SSWV_PAIN2,
    S_SSWV_DIE1,
    S_SSWV_DIE2,
    S_SSWV_DIE3,
    S_SSWV_DIE4,
    S_SSWV_DIE5,
    S_SSWV_XDIE1,
    S_SSWV_XDIE2,
    S_SSWV_XDIE3,
    S_SSWV_XDIE4,
    S_SSWV_XDIE5,
    S_SSWV_XDIE6,
    S_SSWV_XDIE7,
    S_SSWV_XDIE8,
    S_SSWV_XDIE9,
    S_SSWV_RAISE1,
    S_SSWV_RAISE2,
    S_SSWV_RAISE3,
    S_SSWV_RAISE4,
    S_SSWV_RAISE5,
    S_KEENSTND,
    S_COMMKEEN,
    S_COMMKEEN2,
    S_COMMKEEN3,
    S_COMMKEEN4,
    S_COMMKEEN5,
    S_COMMKEEN6,
    S_COMMKEEN7,
    S_COMMKEEN8,
    S_COMMKEEN9,
    S_COMMKEEN10,
    S_COMMKEEN11,
    S_COMMKEEN12,
    S_KEENPAIN,
    S_KEENPAIN2,
    S_BRAIN,
    S_BRAIN_PAIN,
    S_BRAIN_DIE1,
    S_BRAIN_DIE2,
    S_BRAIN_DIE3,
    S_BRAIN_DIE4,
    S_BRAINEYE,
    S_BRAINEYESEE,
    S_BRAINEYE1,
    S_SPAWN1,
    S_SPAWN2,
    S_SPAWN3,
    S_SPAWN4,
    S_SPAWNFIRE1,
    S_SPAWNFIRE2,
    S_SPAWNFIRE3,
    S_SPAWNFIRE4,
    S_SPAWNFIRE5,
    S_SPAWNFIRE6,
    S_SPAWNFIRE7,
    S_SPAWNFIRE8,
    S_BRAINEXPLODE1,
    S_BRAINEXPLODE2,
    S_BRAINEXPLODE3,
    S_ARM1,
    S_ARM1A,
    S_ARM2,
    S_ARM2A,
    S_BAR1,
    S_BAR2,
    S_BEXP,
    S_BEXP2,
    S_BEXP3,
    S_BEXP4,
    S_BEXP5,
    S_BBAR1,
    S_BBAR2,
    S_BBAR3,
    S_BON1,
    S_BON1A,
    S_BON1B,
    S_BON1C,
    S_BON1D,
    S_BON1E,
    S_BON2,
    S_BON2A,
    S_BON2B,
    S_BON2C,
    S_BON2D,
    S_BON2E,
    S_BKEY,
    S_BKEY2,
    S_RKEY,
    S_RKEY2,
    S_YKEY,
    S_YKEY2,
    S_BSKULL,
    S_BSKULL2,
    S_RSKULL,
    S_RSKULL2,
    S_YSKULL,
    S_YSKULL2,
    S_STIM,
    S_MEDI,
    S_SOUL,
    S_SOUL2,
    S_SOUL3,
    S_SOUL4,
    S_SOUL5,
    S_SOUL6,
    S_PINV,
    S_PINV2,
    S_PINV3,
    S_PINV4,
    S_PSTR,
    S_PINS,
    S_PINS2,
    S_PINS3,
    S_PINS4,
    S_MEGA,
    S_MEGA2,
    S_MEGA3,
    S_MEGA4,
    S_SUIT,
    S_PMAP,
    S_PMAP2,
    S_PMAP3,
    S_PMAP4,
    S_PMAP5,
    S_PMAP6,
    S_PVIS,
    S_PVIS2,
    S_CLIP,
    S_AMMO,
    S_ROCK,
    S_BROK,
    S_CELL,
    S_CELP,
    S_SHEL,
    S_SBOX,
    S_BPAK,
    S_BFUG,
    S_MGUN,
    S_CSAW,
    S_LAUN,
    S_PLAS,
    S_SHOT,
    S_SHOT2,
    S_COLU,
    S_STALAG,
    S_BLOODYTWITCH,
    S_BLOODYTWITCH2,
    S_BLOODYTWITCH3,
    S_BLOODYTWITCH4,
    S_DEADTORSO,
    S_DEADBOTTOM,
    S_HEADSONSTICK,
    S_GIBS,
    S_HEADONASTICK,
    S_HEADCANDLES,
    S_HEADCANDLES2,
    S_DEADSTICK,
    S_LIVESTICK,
    S_LIVESTICK2,
    S_MEAT2,
    S_MEAT3,
    S_MEAT4,
    S_MEAT5,
    S_STALAGTITE,
    S_TALLGRNCOL,
    S_SHRTGRNCOL,
    S_TALLREDCOL,
    S_SHRTREDCOL,
    S_CANDLESTIK,
    S_CANDELABRA,
    S_SKULLCOL,
    S_TORCHTREE,
    S_BIGTREE,
    S_TECHPILLAR,
    S_EVILEYE,
    S_EVILEYE2,
    S_EVILEYE3,
    S_EVILEYE4,
    S_FLOATSKULL,
    S_FLOATSKULL2,
    S_FLOATSKULL3,
    S_HEARTCOL,
    S_HEARTCOL2,
    S_BLUETORCH,
    S_BLUETORCH2,
    S_BLUETORCH3,
    S_BLUETORCH4,
    S_GREENTORCH,
    S_GREENTORCH2,
    S_GREENTORCH3,
    S_GREENTORCH4,
    S_REDTORCH,
    S_REDTORCH2,
    S_REDTORCH3,
    S_REDTORCH4,
    S_BTORCHSHRT,
    S_BTORCHSHRT2,
    S_BTORCHSHRT3,
    S_BTORCHSHRT4,
    S_GTORCHSHRT,
    S_GTORCHSHRT2,
    S_GTORCHSHRT3,
    S_GTORCHSHRT4,
    S_RTORCHSHRT,
    S_RTORCHSHRT2,
    S_RTORCHSHRT3,
    S_RTORCHSHRT4,
    S_HANGNOGUTS,
    S_HANGBNOBRAIN,
    S_HANGTLOOKDN,
    S_HANGTSKULL,
    S_HANGTLOOKUP,
    S_HANGTNOBRAIN,
    S_COLONGIBS,
    S_SMALLPOOL,
    S_BRAINSTEM,
    S_TECHLAMP,
    S_TECHLAMP2,
    S_TECHLAMP3,
    S_TECHLAMP4,
    S_TECH2LAMP,
    S_TECH2LAMP2,
    S_TECH2LAMP3,
    S_TECH2LAMP4,
    NUMSTATES
} statenum_t;


typedef struct
{
    spritenum_t sprite;
    long frame;
    long tics;
    actionf_t action;
    statenum_t nextstate;
    long misc1, misc2;
} state_t;


extern state_t* states;
extern char** sprnames;

typedef enum
{
    MT_PLAYER,
    MT_POSSESSED,
    MT_SHOTGUY,
    MT_VILE,
    MT_FIRE,
    MT_UNDEAD,
    MT_TRACER,
    MT_SMOKE,
    MT_FATSO,
    MT_FATSHOT,
    MT_CHAINGUY,
    MT_TROOP,
    MT_SERGEANT,
    MT_SHADOWS,
    MT_HEAD,
    MT_BRUISER,
    MT_BRUISERSHOT,
    MT_KNIGHT,
    MT_SKULL,
    MT_SPIDER,
    MT_BABY,
    MT_CYBORG,
    MT_PAIN,
    MT_WOLFSS,
    MT_KEEN,
    MT_BOSSBRAIN,
    MT_BOSSSPIT,
    MT_BOSSTARGET,
    MT_SPAWNSHOT,
    MT_SPAWNFIRE,
    MT_BARREL,
    MT_TROOPSHOT,
    MT_HEADSHOT,
    MT_ROCKET,
    MT_PLASMA,
    MT_BFG,
    MT_ARACHPLAZ,
    MT_PUFF,
    MT_BLOOD,
    MT_TFOG,
    MT_IFOG,
    MT_TELEPORTMAN,
    MT_EXTRABFG,
    MT_MISC0,
    MT_MISC1,
    MT_MISC2,
    MT_MISC3,
    MT_MISC4,
    MT_MISC5,
    MT_MISC6,
    MT_MISC7,
    MT_MISC8,
    MT_MISC9,
    MT_MISC10,
    MT_MISC11,
    MT_MISC12,
    MT_INV,
    MT_MISC13,
    MT_INS,
    MT_MISC14,
    MT_MISC15,
    MT_MISC16,
    MT_MEGA,
    MT_CLIP,
    MT_MISC17,
    MT_MISC18,
    MT_MISC19,
    MT_MISC20,
    MT_MISC21,
    MT_MISC22,
    MT_MISC23,
    MT_MISC24,
    MT_MISC25,
    MT_CHAINGUN,
    MT_MISC26,
    MT_MISC27,
    MT_MISC28,
    MT_SHOTGUN,
    MT_SUPERSHOTGUN,
    MT_MISC29,
    MT_MISC30,
    MT_MISC31,
    MT_MISC32,
    MT_MISC33,
    MT_MISC34,
    MT_MISC35,
    MT_MISC36,
    MT_MISC37,
    MT_MISC38,
    MT_MISC39,
    MT_MISC40,
    MT_MISC41,
    MT_MISC42,
    MT_MISC43,
    MT_MISC44,
    MT_MISC45,
    MT_MISC46,
    MT_MISC47,
    MT_MISC48,
    MT_MISC49,
    MT_MISC50,
    MT_MISC51,
    MT_MISC52,
    MT_MISC53,
    MT_MISC54,
    MT_MISC55,
    MT_MISC56,
    MT_MISC57,
    MT_MISC58,
    MT_MISC59,
    MT_MISC60,
    MT_MISC61,
    MT_MISC62,
    MT_MISC63,
    MT_MISC64,
    MT_MISC65,
    MT_MISC66,
    MT_MISC67,
    MT_MISC68,
    MT_MISC69,
    MT_MISC70,
    MT_MISC71,
    MT_MISC72,
    MT_MISC73,
    MT_MISC74,
    MT_MISC75,
    MT_MISC76,
    MT_MISC77,
    MT_MISC78,
    MT_MISC79,
    MT_MISC80,
    MT_MISC81,
    MT_MISC82,
    MT_MISC83,
    MT_MISC84,
    MT_MISC85,
    MT_MISC86,
    NUMMOBJTYPES
} mobjtype_t;


typedef struct
{
    int        doomednum;
    int        spawnstate;
    int        spawnhealth;
    int        seestate;
    int        seesound;
    int        reactiontime;
    int        attacksound;
    int        painstate;
    int        painchance;
    int        painsound;
    int        meleestate;
    int        missilestate;
    int        deathstate;
    int        xdeathstate;
    int        deathsound;
    int        speed;
    int        radius;
    int        height;
    int        mass;
    int        damage;
    int        activesound;
    int        flags;
    int        raisestate;
} mobjinfo_t;


extern mobjinfo_t mobjinfo[NUMMOBJTYPES];


#endif


#ifndef __M_ARGV__
#define __M_ARGV__


//
// MISC
//
extern int myargc;
extern char** myargv;

// Returns the position of the given parameter
// in the arg list (0 if not found).
int M_CheckParm(char* check);


#endif


#ifndef __M_CHEAT__
#define __M_CHEAT__


//
// CHEAT SEQUENCE PACKAGE
//

#define SCRAMBLE(a) \
((((a)&1)<<7) + (((a)&2)<<5) + ((a)&4) + (((a)&8)<<1) \
 + (((a)&16)>>1) + ((a)&32) + (((a)&64)>>5) + (((a)&128)>>7))


typedef struct
{
    unsigned char* sequence;
    unsigned char* p;
} cheatseq_t;


int cht_CheckCheat(cheatseq_t* cht, char key);
void cht_GetParam(cheatseq_t* cht, char* buffer);


#endif


#ifndef __M_FIXED__
#define __M_FIXED__


//
// Fixed point, 32bit as 16.16.
//
#define FRACBITS 16
#define FRACUNIT (1<<FRACBITS)


typedef int fixed_t;


fixed_t FixedMul(fixed_t a, fixed_t b);
fixed_t FixedDiv(fixed_t a, fixed_t b);
fixed_t FixedDiv2(fixed_t a, fixed_t b);


#endif


#ifndef __M_BBOX__
#define __M_BBOX__


//#include "doomtype.h"
//#include "m_fixed.h"


// Bounding box coordinate storage.
enum
{
    BOXTOP,
    BOXBOTTOM,
    BOXLEFT,
    BOXRIGHT
}; // bbox coordinates


// Bounding box functions.
void M_ClearBox(fixed_t* box);
void M_AddToBox(fixed_t* box, fixed_t x, fixed_t y);


#endif


#ifndef __M_MENU__
#define __M_MENU__


//#include "d_event.h"


//
// MENUS
//
 
// Called by main loop,
// saves config file and calls I_Quit when user exits.
// Even when the menu is not displayed,
// this can resize the view and change game parameters.
// Does all the real work of the menu interaction.
doom_boolean M_Responder(event_t* ev);

// Called by main loop,
// only used for menu (skull cursor) animation.
void M_Ticker(void);

// Called by main loop,
// draws the menus directly into the screen buffer.
void M_Drawer(void);

// Called by D_DoomMain,
// loads the config file.
void M_Init(void);

// Called by intro code to force menu up upon a keypress,
// does nothing if menu is already up.
void M_StartControlPanel(void);


#endif


#ifndef __M_MISC__
#define __M_MISC__


//#include "doomtype.h"


//
// MISC
//
typedef struct
{
    char* name;
    int* location;
    int defaultvalue;
    int scantranslate; // PC scan code hack
    int untranslated; // lousy hack
    char** text_location; // [pd] int* location was used to store text pointer. Can't change to intptr_t unless we change all settings type
    char* default_text_value; // [pd] So we don't change defaultvalue behavior for int to intptr_t
} default_t;


doom_boolean M_WriteFile(char const* name, void* source, int length);
int M_ReadFile(char const* name, byte** buffer);
void M_ScreenShot(void);
void M_LoadDefaults(void);
void M_SaveDefaults(void);
int M_DrawText(int x, int y, doom_boolean direct, char* string);


#endif


#ifndef __M_RANDOM__
#define __M_RANDOM__


//#include "doomtype.h"


// Returns a number from 0 to 255,
// from a lookup table.
int M_Random(void);

// As M_Random, but used only by the play simulation.
int P_Random(void);

// Fix randoms for demos.
void M_ClearRandom(void);


#endif


#ifndef __M_SWAP__
#define __M_SWAP__


// Endianess handling.
// WAD files are stored little endian.
#ifdef __BIG_ENDIAN__
unsigned short SwapSHORT(unsigned short);
unsigned long SwapLONG(unsigned long);
#define SHORT(x) ((short)SwapSHORT((unsigned short) (x)))
#define LONG(x) ((long)SwapLONG((unsigned long) (x)))
#else
#define SHORT(x) (x)
#define LONG(x) (x)
#endif


#endif


#ifndef __P_SAVEG__
#define __P_SAVEG__


//#include "doomtype.h"


// Persistent storage/archiving.
// These are the load / save game routines.
void P_ArchivePlayers(void);
void P_UnArchivePlayers(void);
void P_ArchiveWorld(void);
void P_UnArchiveWorld(void);
void P_ArchiveThinkers(void);
void P_UnArchiveThinkers(void);
void P_ArchiveSpecials(void);
void P_UnArchiveSpecials(void);

extern byte* save_p;


#endif


#ifndef __P_SETUP__
#define __P_SETUP__


// NOT called by W_Ticker. Fixme.
void P_SetupLevel(int episode, int map, int playermask, skill_t skill);

// Called by startup code.
void P_Init(void);


#endif


#ifndef __P_TICK__
#define __P_TICK__


// Called by C_Ticker,
// can call G_PlayerExited.
// Carries out all thinking of monsters and players.
void P_Ticker(void);


#endif


#ifndef __R_SKY__
#define __R_SKY__

// SKY, store the number for name.
#define SKYFLATNAME "F_SKY1"

// The sky map is 256*128*4 maps.
#define ANGLETOSKYSHIFT 22

extern int skytexture;
extern int skytexturemid;

// Called whenever the view size changes.
void R_InitSkyMap(void);

#endif


#ifndef __S_SOUND__
#define __S_SOUND__


//
// Initializes sound stuff, including volume
// Sets channels, SFX and music volume,
// allocates channel buffer, sets S_sfx lookup.
//
void S_Init(int sfxVolume, int musicVolume);

//
// Per level startup code.
// Kills playing sounds at start of level,
//  determines music if any, changes music.
//
void S_Start(void);

//
// Start sound for thing at <origin>
//  using <sound_id> from sounds.h
//
void S_StartSound(void* origin, int sound_id);

// Will start a sound at a given volume.
void S_StartSoundAtVolume(void* origin, int sound_id, int volume);

// Stop sound for thing at <origin>
void S_StopSound(void* origin);

// Start music using <music_id> from sounds.h
void S_StartMusic(int music_id);

// Start music using <music_id> from sounds.h,
// and set whether looping
void S_ChangeMusic(int music_id, int looping);

// Stops the music fer sure.
void S_StopMusic(void);

// Stop and resume music, during game PAUSE.
void S_PauseSound(void);
void S_ResumeSound(void);

//
// Updates music & sounds
//
void S_UpdateSounds(void* listener);

void S_SetMusicVolume(int volume);
void S_SetSfxVolume(int volume);


#endif


#ifndef __SOUNDS__
#define __SOUNDS__


//
// SoundFX struct.
//
typedef struct sfxinfo_struct sfxinfo_t;

struct sfxinfo_struct
{
    // up to 6-character name
    char* name;

    // Sfx singularity (only one at a time)
    int singularity;

    // Sfx priority
    int priority;

    // referenced sound if a link
    sfxinfo_t* link;

    // pitch if a link
    int pitch;

    // volume if a link
    int volume;

    // sound data
    void* data;

    // this is checked every second to see if sound
    // can be thrown out (if 0, then decrement, if -1,
    // then throw out, if > 0, then it is in use)
    int usefulness;

    // lump number of sfx
    int lumpnum;
};


//
// MusicInfo struct.
//
typedef struct
{
    // up to 6-character name
    char* name;

    // lump number of music
    int lumpnum;

    // music data
    void* data;

    // music handle once registered
    int handle;
} musicinfo_t;


// the complete set of sound effects
extern sfxinfo_t* S_sfx;

// the complete set of music
extern musicinfo_t* S_music;

//
// Identifiers for all music in game.
//
typedef enum
{
    mus_None,
    mus_e1m1,
    mus_e1m2,
    mus_e1m3,
    mus_e1m4,
    mus_e1m5,
    mus_e1m6,
    mus_e1m7,
    mus_e1m8,
    mus_e1m9,
    mus_e2m1,
    mus_e2m2,
    mus_e2m3,
    mus_e2m4,
    mus_e2m5,
    mus_e2m6,
    mus_e2m7,
    mus_e2m8,
    mus_e2m9,
    mus_e3m1,
    mus_e3m2,
    mus_e3m3,
    mus_e3m4,
    mus_e3m5,
    mus_e3m6,
    mus_e3m7,
    mus_e3m8,
    mus_e3m9,
    mus_inter,
    mus_intro,
    mus_bunny,
    mus_victor,
    mus_introa,
    mus_runnin,
    mus_stalks,
    mus_countd,
    mus_betwee,
    mus_doom,
    mus_the_da,
    mus_shawn,
    mus_ddtblu,
    mus_in_cit,
    mus_dead,
    mus_stlks2,
    mus_theda2,
    mus_doom2,
    mus_ddtbl2,
    mus_runni2,
    mus_dead2,
    mus_stlks3,
    mus_romero,
    mus_shawn2,
    mus_messag,
    mus_count2,
    mus_ddtbl3,
    mus_ampie,
    mus_theda3,
    mus_adrian,
    mus_messg2,
    mus_romer2,
    mus_tense,
    mus_shawn3,
    mus_openin,
    mus_evil,
    mus_ultima,
    mus_read_m,
    mus_dm2ttl,
    mus_dm2int,
    NUMMUSIC
} musicenum_t;


//
// Identifiers for all sfx in game.
//
typedef enum
{
    sfx_None,
    sfx_pistol,
    sfx_shotgn,
    sfx_sgcock,
    sfx_dshtgn,
    sfx_dbopn,
    sfx_dbcls,
    sfx_dbload,
    sfx_plasma,
    sfx_bfg,
    sfx_sawup,
    sfx_sawidl,
    sfx_sawful,
    sfx_sawhit,
    sfx_rlaunc,
    sfx_rxplod,
    sfx_firsht,
    sfx_firxpl,
    sfx_pstart,
    sfx_pstop,
    sfx_doropn,
    sfx_dorcls,
    sfx_stnmov,
    sfx_swtchn,
    sfx_swtchx,
    sfx_plpain,
    sfx_dmpain,
    sfx_popain,
    sfx_vipain,
    sfx_mnpain,
    sfx_pepain,
    sfx_slop,
    sfx_itemup,
    sfx_wpnup,
    sfx_oof,
    sfx_telept,
    sfx_posit1,
    sfx_posit2,
    sfx_posit3,
    sfx_bgsit1,
    sfx_bgsit2,
    sfx_sgtsit,
    sfx_cacsit,
    sfx_brssit,
    sfx_cybsit,
    sfx_spisit,
    sfx_bspsit,
    sfx_kntsit,
    sfx_vilsit,
    sfx_mansit,
    sfx_pesit,
    sfx_sklatk,
    sfx_sgtatk,
    sfx_skepch,
    sfx_vilatk,
    sfx_claw,
    sfx_skeswg,
    sfx_pldeth,
    sfx_pdiehi,
    sfx_podth1,
    sfx_podth2,
    sfx_podth3,
    sfx_bgdth1,
    sfx_bgdth2,
    sfx_sgtdth,
    sfx_cacdth,
    sfx_skldth,
    sfx_brsdth,
    sfx_cybdth,
    sfx_spidth,
    sfx_bspdth,
    sfx_vildth,
    sfx_kntdth,
    sfx_pedth,
    sfx_skedth,
    sfx_posact,
    sfx_bgact,
    sfx_dmact,
    sfx_bspact,
    sfx_bspwlk,
    sfx_vilact,
    sfx_noway,
    sfx_barexp,
    sfx_punch,
    sfx_hoof,
    sfx_metal,
    sfx_chgun,
    sfx_tink,
    sfx_bdopn,
    sfx_bdcls,
    sfx_itmbk,
    sfx_flame,
    sfx_flamst,
    sfx_getpow,
    sfx_bospit,
    sfx_boscub,
    sfx_bossit,
    sfx_bospn,
    sfx_bosdth,
    sfx_manatk,
    sfx_mandth,
    sfx_sssit,
    sfx_ssdth,
    sfx_keenpn,
    sfx_keendt,
    sfx_skeact,
    sfx_skesit,
    sfx_skeatk,
    sfx_radio,
    NUMSFX
} sfxenum_t;

#endif


#ifndef __STSTUFF_H__
#define __STSTUFF_H__

//#include "doomtype.h"
//#include "d_event.h"

// Size of statusbar.
// Now sensitive for scaling.
#define ST_HEIGHT (32 * SCREEN_MUL)
#define ST_WIDTH SCREENWIDTH
#define ST_Y (SCREENHEIGHT - ST_HEIGHT)


//
// STATUS BAR
//

// Called by main loop.
doom_boolean ST_Responder(event_t* ev);

// Called by main loop.
void ST_Ticker(void);

// Called by main loop.
void ST_Drawer(doom_boolean fullscreen, doom_boolean refresh);

// Called when the console player is spawned on each level.
void ST_Start(void);

// Called by startup code.
void ST_Init(void);


// States for status bar code.
typedef enum
{
    AutomapState,
    FirstPersonState
} st_stateenum_t;


// States for the chat code.
typedef enum
{
    StartChatState,
    WaitDestState,
    GetChatState
} st_chatstateenum_t;


doom_boolean ST_Responder(event_t* ev);

#endif


#ifndef __TABLES__
#define __TABLES__


#ifdef LINUX

#else
#define PI 3.141592657
#endif

//#include "m_fixed.h"

#define FINEANGLES 8192
#define FINEMASK (FINEANGLES-1)

// 0x100000000 to 0x2000
#define ANGLETOFINESHIFT 19                

// Effective size is 10240.
extern fixed_t* finesine;

// Re-use data, is just PI/2 pahse shift.
extern fixed_t* finecosine;


// Effective size is 4096.
extern fixed_t* finetangent;

// Binary Angle Measument, BAM.
#define ANG45 0x20000000
#define ANG90 0x40000000
#define ANG180 0x80000000
#define ANG270 0xc0000000

#define SLOPERANGE 2048
#define SLOPEBITS 11
#define DBITS (FRACBITS - SLOPEBITS)

typedef unsigned angle_t;

// Effective size is 2049;
// The +1 size is to handle the case when x==y
//  without additional checking.
extern angle_t*                tantoangle;


// Utility function,
//  called by R_PointToAngle.
int SlopeDiv(unsigned num, unsigned den);


#endif


#ifndef __P_MOBJ__
#define __P_MOBJ__


// Basics.
//#include "tables.h"
//#include "m_fixed.h"

// We need the thinker_t stuff.
//#include "d_think.h"

// We need the WAD data structure for Map things,
// from the THINGS lump.
//#include "doomdata.h"

// States are tied to finite states are
//  tied to animation frames.
// Needs precompiled tables/data structures.
//#include "info.h"


//
// NOTES: mobj_t
//
// mobj_ts are used to tell the refresh where to draw an image,
// tell the world simulation when objects are contacted,
// and tell the sound driver how to position a sound.
//
// The refresh uses the next and prev links to follow
// lists of things in sectors as they are being drawn.
// The sprite, frame, and angle elements determine which patch_t
// is used to draw the sprite if it is visible.
// The sprite and frame values are allmost allways set
// from state_t structures.
// The statescr.exe utility generates the states.h and states.c
// files that contain the sprite/frame numbers from the
// statescr.txt source file.
// The xyz origin point represents a point at the bottom middle
// of the sprite (between the feet of a biped).
// This is the default origin position for patch_ts grabbed
// with lumpy.exe.
// A walking creature will have its z equal to the floor
// it is standing on.
//
// The sound code uses the x,y, and subsector fields
// to do stereo positioning of any sound effited by the mobj_t.
//
// The play simulation uses the blocklinks, x,y,z, radius, height
// to determine when mobj_ts are touching each other,
// touching lines in the map, or hit by trace lines (gunshots,
// lines of sight, etc).
// The mobj_t->flags element has various bit flags
// used by the simulation.
//
// Every mobj_t is linked into a single sector
// based on its origin coordinates.
// The subsector_t is found with R_PointInSubsector(x,y),
// and the sector_t can be found with subsector->sector.
// The sector links are only used by the rendering code,
// the play simulation does not care about them at all.
//
// Any mobj_t that needs to be acted upon by something else
// in the play world (block movement, be shot, etc) will also
// need to be linked into the blockmap.
// If the thing has the MF_NOBLOCK flag set, it will not use
// the block links. It can still interact with other things,
// but only as the instigator (missiles will run into other
// things, but nothing can run into a missile).
// Each block in the grid is 128*128 units, and knows about
// every line_t that it contains a piece of, and every
// interactable mobj_t that has its origin contained.  
//
// A valid mobj_t is a mobj_t that has the proper subsector_t
// filled in for its xy coordinates and is linked into the
// sector from which the subsector was made, or has the
// MF_NOSECTOR flag set (the subsector_t needs to be valid
// even if MF_NOSECTOR is set), and is linked into a blockmap
// block or has the MF_NOBLOCKMAP flag set.
// Links should only be modified by the P_[Un]SetThingPosition()
// functions.
// Do not change the MF_NO? flags while a thing is valid.
//
// Any questions?
//

//
// Misc. mobj flags
//
typedef enum
{
    // Call P_SpecialThing when touched.
    MF_SPECIAL = 1,
    // Blocks.
    MF_SOLID = 2,
    // Can be hit.
    MF_SHOOTABLE = 4,
    // Don't use the sector links (invisible but touchable).
    MF_NOSECTOR = 8,
    // Don't use the blocklinks (inert but displayable)
    MF_NOBLOCKMAP = 16,

    // Not to be activated by sound, deaf monster.
    MF_AMBUSH = 32,
    // Will try to attack right back.
    MF_JUSTHIT = 64,
    // Will take at least one step before attacking.
    MF_JUSTATTACKED = 128,
    // On level spawning (initial position),
    //  hang from ceiling instead of stand on floor.
    MF_SPAWNCEILING = 256,
    // Don't apply gravity (every tic),
    //  that is, object will float, keeping current height
    //  or changing it actively.
    MF_NOGRAVITY = 512,

    // Movement flags.
    // This allows jumps from high places.
    MF_DROPOFF = 0x400,
    // For players, will pick up items.
    MF_PICKUP = 0x800,
    // Player cheat. ???
    MF_NOCLIP = 0x1000,
    // Player: keep info about sliding along walls.
    MF_SLIDE = 0x2000,
    // Allow moves to any height, no gravity.
    // For active floaters, e.g. cacodemons, pain elementals.
    MF_FLOAT = 0x4000,
    // Don't cross lines
    //   ??? or look at heights on teleport.
    MF_TELEPORT = 0x8000,
    // Don't hit same species, explode on block.
    // Player missiles as well as fireballs of various kinds.
    MF_MISSILE = 0x10000,
    // Dropped by a demon, not level spawned.
    // E.g. ammo clips dropped by dying former humans.
    MF_DROPPED = 0x20000,
    // Use fuzzy draw (shadow demons or spectres),
    //  temporary player invisibility powerup.
    MF_SHADOW = 0x40000,
    // Flag: don't bleed when shot (use puff),
    //  barrels and shootable furniture shall not bleed.
    MF_NOBLOOD = 0x80000,
    // Don't stop moving halfway off a step,
    //  that is, have dead bodies slide down all the way.
    MF_CORPSE = 0x100000,
    // Floating to a height for a move, ???
    //  don't auto float to target's height.
    MF_INFLOAT = 0x200000,

    // On kill, count this enemy object
    //  towards intermission kill total.
    // Happy gathering.
    MF_COUNTKILL = 0x400000,

    // On picking up, count this item object
    //  towards intermission item total.
    MF_COUNTITEM = 0x800000,

    // Special handling: skull in flight.
    // Neither a cacodemon nor a missile.
    MF_SKULLFLY = 0x1000000,

    // Don't spawn this object
    //  in death match mode (e.g. key cards).
    MF_NOTDMATCH = 0x2000000,

    // Player sprites in multiplayer modes are modified
    //  using an internal color lookup table for re-indexing.
    // If 0x4 0x8 or 0xc,
    //  use a translation table for player colormaps
    MF_TRANSLATION = 0xc000000,
    // Hmm ???.
    MF_TRANSSHIFT = 26
} mobjflag_t;


// Map Object definition.
typedef struct mobj_s
{
    // List: thinker links.
    thinker_t thinker;

    // Info for drawing: position.
    fixed_t x;
    fixed_t y;
    fixed_t z;

    // More list: links in sector (if needed)
    struct mobj_s* snext;
    struct mobj_s* sprev;

    //More drawing info: to determine current sprite.
    angle_t angle;        // orientation
    spritenum_t sprite;        // used to find patch_t and flip value
    int frame;        // might be ORed with FF_FULLBRIGHT

    // Interaction info, by BLOCKMAP.
    // Links in blocks (if needed).
    struct mobj_s* bnext;
    struct mobj_s* bprev;

    struct subsector_s* subsector;

    // The closest interval over all contacted Sectors.
    fixed_t floorz;
    fixed_t ceilingz;

    // For movement checking.
    fixed_t radius;
    fixed_t height;

    // Momentums, used to update position.
    fixed_t momx;
    fixed_t momy;
    fixed_t momz;

    // If == validcount, already checked.
    int validcount;

    mobjtype_t type;
    mobjinfo_t* info; // &mobjinfo[mobj->type]

    int tics; // state tic counter
    state_t* state;
    int flags;
    int health;

    // Movement direction, movement generation (zig-zagging).
    int movedir; // 0-7
    int movecount; // when 0, select a new dir

    // Thing being chased/attacked (or 0),
    // also the originator for missiles.
    struct mobj_s* target;

    // Reaction time: if non 0, don't attack yet.
    // Used by player to freeze a bit after teleporting.
    int reactiontime;

    // If >0, the target will be chased
    // no matter what (even if shot)
    int threshold;

    // Additional info record for player avatars only.
    // Only valid if type == MT_PLAYER
    struct player_s* player;

    // Player number last looked for.
    int lastlook;

    // For nightmare respawn.
    mapthing_t spawnpoint;

    // Thing being chased/attacked for tracers.
    struct mobj_s* tracer;
} mobj_t;


#endif


#ifndef __P_PSPR__
#define __P_PSPR__

// Basic data types.
// Needs fixed point, and BAM angles.
//#include "m_fixed.h"
//#include "tables.h"

// Needs to include the precompiled
// sprite animation tables.
// Header generated by multigen utility.
// This includes all the data for thing animation,
// i.e. the Thing Atrributes table
// and the Frame Sequence table.
//#include "info.h"

//
// Frame flags:
// handles maximum brightness (torches, muzzle flare, light sources)
//
#define FF_FULLBRIGHT 0x8000 // flag in thing->frame
#define FF_FRAMEMASK 0x7fff


//
// Overlay psprites are scaled shapes
// drawn directly on the view screen,
// coordinates are given for a 320*200 view screen.
//
typedef enum
{
    ps_weapon,
    ps_flash,
    NUMPSPRITES
} psprnum_t;


typedef struct
{
    state_t* state;        // a 0 state means not active
    int tics;
    fixed_t sx;
    fixed_t sy;
} pspdef_t;


#endif


#ifndef __D_PLAYER__
#define __D_PLAYER__


// The player data structure depends on a number
// of other structs: items (internal inventory),
// animation states (closely tied to the sprites
// used to represent them, unfortunately).
//#include "d_items.h"
//#include "p_pspr.h"

// In addition, the player is just a special
// case of the generic moving object/actor.
//#include "p_mobj.h"

// Finally, for odd reasons, the player input
// is buffered within the player data struct,
// as commands per game tick.
//#include "d_ticcmd.h"


//
// Player states.
//
typedef enum
{
    // Playing or camping.
    PST_LIVE,
    // Dead on the ground, view follows killer.
    PST_DEAD,
    // Ready to restart/respawn???
    PST_REBORN
} playerstate_t;


//
// Player internal flags, for cheats and debug.
//
typedef enum
{
    // No clipping, walk through barriers.
    CF_NOCLIP = 1,
    // No damage, no health loss.
    CF_GODMODE = 2,
    // Not really a cheat, just a debug aid.
    CF_NOMOMENTUM = 4
} cheat_t;


//
// Extended player object info: player_t
//
typedef struct player_s
{
    mobj_t* mo;
    playerstate_t playerstate;
    ticcmd_t cmd;

    // Determine POV,
    //  including viewpoint bobbing during movement.
    // Focal origin above r.z
    fixed_t viewz;
    // Base height above floor for viewz.
    fixed_t viewheight;
    // Bob/squat speed.
    fixed_t deltaviewheight;
    // bounded/scaled total momentum.
    fixed_t bob;

    // This is only used between levels,
    // mo->health is used during levels.
    int health;
    int armorpoints;
    // Armor type is 0-2.
    int armortype;

    // Power ups. invinc and invis are tic counters.
    int powers[NUMPOWERS];
    doom_boolean cards[NUMCARDS];
    doom_boolean backpack;

    // Frags, kills of other players.
    int frags[MAXPLAYERS];
    weapontype_t readyweapon;

    // Is wp_nochange if not changing.
    weapontype_t pendingweapon;

    doom_boolean weaponowned[NUMWEAPONS];
    int ammo[NUMAMMO];
    int maxammo[NUMAMMO];

    // True if button down last tic.
    int attackdown;
    int usedown;

    // Bit flags, for cheats and debug.
    // See cheat_t, above.
    int cheats;

    // Refired shots are less accurate.
    int refire;

    // For intermission stats.
    int killcount;
    int itemcount;
    int secretcount;

    // Hint messages.
    char* message;

    // For screen flashing (red or bright).
    int damagecount;
    int bonuscount;

    // Who did damage (0 for floors/ceilings).
    mobj_t* attacker;

    // So gun flashes light up areas.
    int extralight;

    // Current PLAYPAL, ???
    //  can be set to REDCOLORMAP for pain, etc.
    int fixedcolormap;

    // Player skin colorshift,
    //  0-3 for which color to draw player.
    int colormap;

    // Overlay view sprites (gun, etc).
    pspdef_t psprites[NUMPSPRITES];

    // True if secret level has been done.
    doom_boolean didsecret;
} player_t;


//
// INTERMISSION
// Structure passed e.g. to WI_Start(wb)
//
typedef struct
{
    doom_boolean in;        // whether the player is in game

    // Player stats, kills, collected items etc.
    int skills;
    int sitems;
    int ssecret;
    int stime;
    int frags[4];
    int score;        // current score on entry, modified on return
} wbplayerstruct_t;


typedef struct
{
    int epsd;        // episode # (0-2)

    // if true, splash the secret level
    doom_boolean didsecret;

    // previous and next levels, origin 0
    int last;
    int next;

    int maxkills;
    int maxitems;
    int maxsecret;
    int maxfrags;

    // the par time
    int partime;

    // index of this player in game
    int pnum;

    wbplayerstruct_t plyr[MAXPLAYERS];
} wbstartstruct_t;


#endif


#ifndef __D_NET__
#define __D_NET__


//#include "d_player.h"


//
// Network play related stuff.
// There is a data struct that stores network
// communication related stuff, and another
// one that defines the actual packets to
// be transmitted.
//

#define DOOMCOM_ID                0x12345678l

// Max computers/players in a game.
#define MAXNETNODES                8

// Networking and tick handling related.
#define BACKUPTICS                12


typedef enum
{
    CMD_SEND = 1,
    CMD_GET = 2
} command_t;


//
// Network packet data.
//
typedef struct
{
    // High bit is retransmit request.
    unsigned checksum;
    // Only valid if NCMD_RETRANSMIT.
    byte retransmitfrom;

    byte starttic;
    byte player;
    byte numtics;
    ticcmd_t cmds[BACKUPTICS];
} doomdata_t;


typedef struct
{
    // Supposed to be DOOMCOM_ID?
    long id;

    // DOOM executes an int to execute commands.
    short intnum;
    // Communication between DOOM and the driver.
    // Is CMD_SEND or CMD_GET.
    short command;
    // Is dest for send, set by get (-1 = no packet).
    short remotenode;

    // Number of bytes in doomdata to be sent
    short datalength;

    // Info common to all nodes.
    // Console is allways node 0.
    short numnodes;
    // Flag: 1 = no duplication, 2-5 = dup for slow nets.
    short ticdup;
    // Flag: 1 = send a backup tic in every packet.
    short extratics;
    // Flag: 1 = deathmatch.
    short deathmatch;
    // Flag: -1 = new game, 0-5 = load savegame
    short savegame;
    short episode;  // 1-3
    short map;      // 1-9
    short skill;    // 1-5

    // Info specific to this node.
    short consoleplayer;
    short numplayers;

    // These are related to the 3-display mode,
    //  in which two drones looking left and right
    //  were used to render two additional views
    //  on two additional computers.
    // Probably not operational anymore.
    // 1 = left, 0 = center, -1 = right
    short angleoffset;
    // 1 = drone
    short drone;

    // The packet data to be sent.
    doomdata_t data;
} doomcom_t;


// Create any new ticcmds and broadcast to other players.
void NetUpdate(void);

// Broadcasts special packets to other players
//  to notify of game exit
void D_QuitNetGame(void);

//? how many ticks to run?
void TryRunTics(void);


#endif


#ifndef __D_STATE__
#define __D_STATE__


// We need globally shared data structures,
//  for defining the global state variables.
//#include "doomdata.h"
//#include "d_net.h"

// We need the playr data structure as well.
//#include "d_player.h"


// ------------------------
// Command line parameters.
//
extern doom_boolean nomonsters;     // checkparm of -nomonsters
extern doom_boolean respawnparm;    // checkparm of -respawn
extern doom_boolean fastparm;       // checkparm of -fast
extern doom_boolean devparm;        // DEBUG: launched with -devparm


// -----------------------------------------------------
// Game Mode - identify IWAD as shareware, retail etc.
//
extern GameMode_t gamemode;
extern GameMission_t gamemission;

// Set if homebrew PWAD stuff has been added.
extern doom_boolean modifiedgame;


// -------------------------------------------
// Language.
extern Language_t language;


// -------------------------------------------
// Selected skill type, map etc.
//

// Defaults for menu, methinks.
extern skill_t startskill;
extern int startepisode;
extern int startmap;

extern doom_boolean autostart;

// Selected by user. 
extern skill_t gameskill;
extern int gameepisode;
extern int gamemap;

// Nightmare mode flag, single player.
extern doom_boolean respawnmonsters;

// Netgame? Only true if >1 player.
extern doom_boolean netgame;

// Flag: true only if started as net deathmatch.
// An enum might handle altdeath/cooperative better.
extern doom_boolean deathmatch;

// -------------------------
// Internal parameters for sound rendering.
// These have been taken from the DOS version,
// but are not (yet) supported with Linux
// (e.g. no sound volume adjustment with menu.

// These are not used, but should be (menu).
// From m_menu.c:
// Sound FX volume has default, 0 - 15
// Music volume has default, 0 - 15
// These are multiplied by 8.
extern int snd_SfxVolume;      // maximum volume for sound
extern int snd_MusicVolume;    // maximum volume for music

// Current music/sfx card - index useless
//  w/o a reference LUT in a sound module.
// Ideally, this would use indices found
//  in: /usr/include/linux/soundcard.h
extern int snd_MusicDevice;
extern int snd_SfxDevice;

// Config file? Same disclaimer as above.
extern int snd_DesiredMusicDevice;
extern int snd_DesiredSfxDevice;


// -------------------------
// Status flags for refresh.
//

// Depending on view size - no status bar?
// Note that there is no way to disable the
//  status bar explicitely.
extern doom_boolean statusbaractive;

extern doom_boolean automapactive;  // In AutoMap mode?
extern doom_boolean menuactive;     // Menu overlayed?
extern doom_boolean paused;         // Game Pause?

extern doom_boolean viewactive;

extern doom_boolean nodrawers;
extern doom_boolean noblit;

extern int viewwindowx;
extern int viewwindowy;
extern int viewheight;
extern int viewwidth;
extern int scaledviewwidth;


// This one is related to the 3-screen display mode.
// ANG90 = left side, ANG270 = right
extern int viewangleoffset;

// Player taking events, and displaying.
extern int consoleplayer;
extern int displayplayer;


// -------------------------------------
// Scores, rating.
// Statistics on a given map, for intermission.
//
extern int totalkills;
extern int totalitems;
extern int totalsecret;

// Timer, for scores.
extern int levelstarttic;   // gametic at level start
extern int leveltime;       // tics in game play for par


// --------------------------------------
// DEMO playback/recording related stuff.
// No demo, there is a human player in charge?
// Disable save/end game?
extern doom_boolean usergame;

//?
extern doom_boolean demoplayback;
extern doom_boolean demorecording;

// Quit after playing a demo from cmdline.
extern doom_boolean singledemo;

//?
extern gamestate_t gamestate;


//-----------------------------
// Internal parameters, fixed.
// These are set by the engine, and not changed
// according to user inputs. Partly load from
// WAD, partly set at startup time.

extern int gametic;


// Bookkeeping on players - state.
extern player_t players[MAXPLAYERS];

// Alive? Disconnected?
extern doom_boolean playeringame[MAXPLAYERS];


// Player spawn spots for deathmatch.
#define MAX_DM_STARTS 10
extern mapthing_t deathmatchstarts[MAX_DM_STARTS];
extern mapthing_t* deathmatch_p;

// Player spawn spots.
extern mapthing_t playerstarts[MAXPLAYERS];

// Intermission stats.
// Parameters for world map / intermission.
extern wbstartstruct_t wminfo;


// LUT of ammunition limits for each kind.
// This doubles with BackPack powerup item.
extern int maxammo[NUMAMMO];


//-----------------------------------------
// Internal parameters, used for engine.
//

// File handling stuff.
extern char basedefault[1024];
extern void* debugfile;

// if true, load all graphics at level load
extern doom_boolean precache;

// wipegamestate can be set to -1
// to force a wipe on the next draw
extern gamestate_t wipegamestate;

extern int mouseSensitivity;
//?
// debug flag to cancel adaptiveness
extern doom_boolean singletics;

extern int bodyqueslot;


// Needed to store the number of the dummy sky flat.
// Used for rendering,
//  as well as tracking projectiles etc.
extern int skyflatnum;


// Netgame stuff (buffers and pointers, i.e. indices).

// This is ???
extern doomcom_t* doomcom;

// This points inside doomcom.
extern doomdata_t* netbuffer;


extern ticcmd_t localcmds[BACKUPTICS];
extern int rndindex;

extern int maketic;
extern int nettics[MAXNETNODES];

extern ticcmd_t netcmds[MAXPLAYERS][BACKUPTICS];
extern int ticdup;


#endif


#ifndef __I_SOUND__
#define __I_SOUND__


//#include "doomdef.h"



//#include "doomstat.h"
//#include "sounds.h"


// Init at program start...
void I_InitSound();

// ... update sound buffer and audio device at runtime...
void I_UpdateSound(void);
void I_SubmitSound(void);

// ... shut down and relase at program termination.
void I_ShutdownSound(void);


//
//  SFX I/O
//

// Initialize channels?
void I_SetChannels();

// Get raw data lump index for sound descriptor.
int I_GetSfxLumpNum(sfxinfo_t* sfxinfo);

// Starts a sound in a particular sound channel.
int I_StartSound(int id, int vol, int sep, int pitch, int priority);

// Stops a sound channel.
void I_StopSound(int handle);

// Called by S_*() functions
//  to see if a channel is still playing.
// Returns 0 if no longer playing, 1 if playing.
int I_SoundIsPlaying(int handle);

// Updates the volume, separation,
//  and pitch of a sound channel.
void I_UpdateSoundParams(int handle, int vol, int sep, int pitch);


//
//  MUSIC I/O
//
void I_InitMusic(void);
void I_ShutdownMusic(void);

// Volume.
void I_SetMusicVolume(int volume);

// PAUSE game handling.
void I_PauseSong(int handle);
void I_ResumeSong(int handle);

// Registers a song handle to song data.
int I_RegisterSong(void* data);

// Called by anything that wishes to start music.
//  plays a song, and when the song is done,
//  starts playing it again in an endless loop.
// Horrible thing to do, considering.
void I_PlaySong(int handle, int looping);

// Stops a song over 3 seconds.
void I_StopSong(int handle);

// See above (register), then think backwards
void I_UnRegisterSong(int handle);

// Get next MIDI message
unsigned long I_TickSong();


#endif


#ifndef __P_INTER__
#define __P_INTER__


//#include "d_player.h"


doom_boolean P_GivePower(player_t*, int);


#endif


#ifndef __R_DEFS__
#define __R_DEFS__


// Screenwidth.
//#include "doomdef.h"

// Some more or less basic data types
// we depend on.
//#include "m_fixed.h"

// We rely on the thinker data struct
// to handle sound origins in sectors.
//#include "d_think.h"
// SECTORS do store MObjs anyway.
//#include "p_mobj.h"


// Silhouette, needed for clipping Segs (mainly)
// and sprites representing things.
#define SIL_NONE 0
#define SIL_BOTTOM 1
#define SIL_TOP 2
#define SIL_BOTH 3

#define MAXDRAWSEGS 256


//
// INTERNAL MAP TYPES
// used by play and refresh
//

//
// Your plain vanilla vertex.
// Note: transformed values not buffered locally,
// like some DOOM-alikes ("wt", "WebView") did.
//
typedef struct
{
    fixed_t        x;
    fixed_t        y;
} vertex_t;


// Forward of LineDefs, for Sectors.
struct line_s;

// Each sector has a degenmobj_t in its center
// for sound origin purposes.
// I suppose this does not handle sound from
// moving objects (doppler), because
// position is prolly just buffered, not
// updated.
typedef struct
{
    thinker_t                thinker;        // not used for anything
    fixed_t                x;
    fixed_t                y;
    fixed_t                z;
} degenmobj_t;

//
// The SECTORS record, at runtime.
// Stores things/mobjs.
//
typedef struct
{
    fixed_t floorheight;
    fixed_t ceilingheight;
    short floorpic;
    short ceilingpic;
    short lightlevel;
    short special;
    short tag;

    // 0 = untraversed, 1,2 = sndlines -1
    int soundtraversed;

    // thing that made a sound (or null)
    mobj_t* soundtarget;

    // mapblock bounding box for height changes
    int blockbox[4];

    // origin for any sounds played by the sector
    degenmobj_t soundorg;

    // if == validcount, already checked
    int validcount;

    // list of mobjs in sector
    mobj_t* thinglist;

    // thinker_t for reversable actions
    void* specialdata;

    int linecount;
    struct line_s** lines;        // [linecount] size
} sector_t;


//
// The SideDef.
//
typedef struct
{
    // add this to the calculated texture column
    fixed_t textureoffset;

    // add this to the calculated texture top
    fixed_t rowoffset;

    // Texture indices.
    // We do not maintain names here. 
    short toptexture;
    short bottomtexture;
    short midtexture;

    // Sector the SideDef is facing.
    sector_t* sector;
} side_t;


//
// Move clipping aid for LineDefs.
//
typedef enum
{
    ST_HORIZONTAL,
    ST_VERTICAL,
    ST_POSITIVE,
    ST_NEGATIVE
} slopetype_t;


typedef struct line_s
{
    // Vertices, from v1 to v2.
    vertex_t* v1;
    vertex_t* v2;

    // Precalculated v2 - v1 for side checking.
    fixed_t dx;
    fixed_t dy;

    // Animation related.
    short flags;
    short special;
    short tag;

    // Visual appearance: SideDefs.
    // sidenum[1] will be -1 if one sided
    short sidenum[2];

    // Neat. Another bounding box, for the extent
    // of the LineDef.
    fixed_t bbox[4];

    // To aid move clipping.
    slopetype_t slopetype;

    // Front and back sector.
    // Note: redundant? Can be retrieved from SideDefs.
    sector_t* frontsector;
    sector_t* backsector;

    // if == validcount, already checked
    int validcount;

    // thinker_t for reversable actions
    void* specialdata;
} line_t;


//
// A SubSector.
// References a Sector.
// Basically, this is a list of LineSegs,
// indicating the visible walls that define
// (all or some) sides of a convex BSP leaf.
//
typedef struct subsector_s
{
    sector_t* sector;
    short numlines;
    short firstline;
} subsector_t;


//
// The LineSeg.
//
typedef struct
{
    vertex_t* v1;
    vertex_t* v2;

    fixed_t offset;

    angle_t angle;

    side_t* sidedef;
    line_t* linedef;

    // Sector references.
    // Could be retrieved from linedef, too.
    // backsector is 0 for one sided lines
    sector_t* frontsector;
    sector_t* backsector;
} seg_t;


//
// BSP node.
//
typedef struct
{
    // Partition line.
    fixed_t x;
    fixed_t y;
    fixed_t dx;
    fixed_t dy;

    // Bounding box for each child.
    fixed_t bbox[2][4];

    // If NF_SUBSECTOR its a subsector.
    unsigned short children[2];
} node_t;


// posts are runs of non masked source pixels
typedef struct
{
    byte topdelta;        // -1 is the last post in a column
    byte length;         // length data bytes follows
} post_t;

// column_t is a list of 0 or more post_t, (byte)-1 terminated
typedef post_t column_t;


//
// OTHER TYPES
//

// This could be wider for >8 bit display.
// Indeed, true color support is posibble
//  precalculating 24bpp lightmap/colormap LUT.
//  from darkening PLAYPAL to all black.
// Could even us emore than 32 levels.
typedef byte lighttable_t;


//
// ?
//
typedef struct drawseg_s
{
    seg_t* curline;
    int x1;
    int x2;

    fixed_t scale1;
    fixed_t scale2;
    fixed_t scalestep;

    // 0=none, 1=bottom, 2=top, 3=both
    int silhouette;

    // do not clip sprites above this
    fixed_t bsilheight;

    // do not clip sprites below this
    fixed_t tsilheight;

    // Pointers to lists for sprite clipping,
    //  all three adjusted so [x1] is first value.
    short* sprtopclip;
    short* sprbottomclip;
    short* maskedtexturecol;
} drawseg_t;


// Patches.
// A patch holds one or more columns.
// Patches are used for sprites and all masked pictures,
// and we compose textures from the TEXTURE1/2 lists
// of patches.
typedef struct
{
    short width;                // bounding box size 
    short height;
    short leftoffset;        // pixels to the left of origin 
    short topoffset;        // pixels below the origin 
    int columnofs[8];        // only [width] used
    // the [0] is &columnofs[width] 
} patch_t;


// A vissprite_t is a thing
//  that will be drawn during a refresh.
// I.e. a sprite object that is partly visible.
typedef struct vissprite_s
{
    // Doubly linked list.
    struct vissprite_s* prev;
    struct vissprite_s* next;

    int x1;
    int x2;

    // for line side calculation
    fixed_t gx;
    fixed_t gy;

    // global bottom / top for silhouette clipping
    fixed_t gz;
    fixed_t gzt;

    // horizontal position of x1
    fixed_t startfrac;

    fixed_t scale;

    // negative if flipped
    fixed_t xiscale;

    fixed_t texturemid;
    int patch;

    // for color translation and shadow draw,
    //  maxbright frames as well
    lighttable_t* colormap;

    int mobjflags;
} vissprite_t;


//        
// Sprites are patches with a special naming convention
//  so they can be recognized by R_InitSprites.
// The base name is NNNNFx or NNNNFxFx, with
//  x indicating the rotation, x = 0, 1-7.
// The sprite and frame specified by a thing_t
//  is range checked at run time.
// A sprite is a patch_t that is assumed to represent
//  a three dimensional object and may have multiple
//  rotations pre drawn.
// Horizontal flipping is used to save space,
//  thus NNNNF2F5 defines a mirrored patch.
// Some sprites will only have one picture used
// for all views: NNNNF0
//
typedef struct
{
    // If false use 0 for any position.
    // Note: as eight entries are available,
    //  we might as well insert the same name eight times.
    doom_boolean rotate;

    // Lump to use for view angles 0-7.
    short lump[8];

    // Flip bit (1 = flip) to use for view angles 0-7.
    byte flip[8];
} spriteframe_t;


//
// A sprite definition:
//  a number of animation frames.
//
typedef struct
{
    int numframes;
    spriteframe_t* spriteframes;
} spritedef_t;


//
// Now what is a visplane, anyway?
// 
typedef struct
{
    fixed_t height;
    int picnum;
    int lightlevel;
    int minx;
    int maxx;

    // leave pads for [minx-1]/[maxx+1]

    byte pad1;
    // Here lies the rub for all
    //  dynamic resize/change of resolution.
    byte top[SCREENWIDTH];
    byte pad2;
    byte pad3;
    // See above.
    byte bottom[SCREENWIDTH];
    byte pad4;
} visplane_t;


#endif


#ifndef __HULIB__
#define __HULIB__


// We are referring to patches.
//#include "r_defs.h"


// background and foreground screen numbers
// different from other modules.
#define BG 1
#define FG 0

// font stuff
#define HU_CHARERASE KEY_BACKSPACE

#define HU_MAXLINES 4
#define HU_MAXLINELENGTH 80


//
// Typedefs of widgets
//

// Text Line widget
//  (parent of Scrolling Text and Input Text widgets)
typedef struct
{
    // left-justified position of scrolling text window
    int x;
    int y;

    patch_t** f;                        // font
    int sc;                        // start character
    char l[HU_MAXLINELENGTH + 1];        // line of text
    int len;                              // current line length

    // whether this line needs to be udpated
    int needsupdate;
} hu_textline_t;


// Scrolling Text window widget
//  (child of Text Line widget)
typedef struct
{
    hu_textline_t l[HU_MAXLINES];        // text lines to draw
    int h;                // height in lines
    int cl;                // current line number

    // pointer to doom_boolean stating whether to update window
    doom_boolean* on;
    doom_boolean laston;                // last value of *->on.
} hu_stext_t;


// Input Text Line widget
//  (child of Text Line widget)
typedef struct
{
    hu_textline_t l;                // text line to input on

     // left margin past which I am not to delete characters
    int lm;

    // pointer to doom_boolean stating whether to update window
    doom_boolean* on;
    doom_boolean laston; // last value of *->on;
} hu_itext_t;


//
// Widget creation, access, and update routines
//

// initializes heads-up widget library
void HUlib_init(void);

//
// textline code
//

// clear a line of text
void HUlib_clearTextLine(hu_textline_t* t);

void HUlib_initTextLine(hu_textline_t* t, int x, int y, patch_t** f, int sc);

// returns success
doom_boolean HUlib_addCharToTextLine(hu_textline_t* t, char ch);

// returns success
doom_boolean HUlib_delCharFromTextLine(hu_textline_t* t);

// draws tline
void HUlib_drawTextLine(hu_textline_t* l, doom_boolean drawcursor);

// erases text line
void HUlib_eraseTextLine(hu_textline_t* l);


//
// Scrolling Text window widget routines
//

// ?
void HUlib_initSText(hu_stext_t* s,
                     int x,
                     int y,
                     int h,
                     patch_t** font,
                     int startchar,
                     doom_boolean* on);

// add a new line
void HUlib_addLineToSText(hu_stext_t* s);

// ?
void HUlib_addMessageToSText(hu_stext_t* s, char* prefix, char* msg);

// draws stext
void HUlib_drawSText(hu_stext_t* s);

// erases all stext lines
void HUlib_eraseSText(hu_stext_t* s);

// Input Text Line widget routines
void HUlib_initIText(hu_itext_t* it,
                     int x,
                     int y,
                     patch_t** font,
                     int startchar,
                     doom_boolean* on);

// enforces left margin
void HUlib_delCharFromIText(hu_itext_t* it);

// enforces left margin
void HUlib_eraseLineFromIText(hu_itext_t* it);

// resets line and left margin
void HUlib_resetIText(hu_itext_t* it);

// left of left-margin
void HUlib_addPrefixToIText(hu_itext_t* it, char* str);

// whether eaten
doom_boolean HUlib_keyInIText(hu_itext_t* it, unsigned char ch);

void HUlib_drawIText(hu_itext_t* it);

// erases all itext lines
void HUlib_eraseIText(hu_itext_t* it);


#endif


#ifndef __P_SPEC__
#define __P_SPEC__


//#include "p_mobj.h"
//#include "r_defs.h"


//
// End-level timer (-TIMER option)
//
extern doom_boolean levelTimer;
extern int levelTimeCount;


// Define values for map objects
#define MO_TELEPORTMAN          14


// at game start
void P_InitPicAnims(void);

// at map load
void P_SpawnSpecials(void);

// every tic
void P_UpdateSpecials(void);

// when needed
doom_boolean P_UseSpecialLine(mobj_t* thing, line_t* line, int side);

void P_ShootSpecialLine(mobj_t* thing, line_t* line);
void P_CrossSpecialLine(int linenum, int side, mobj_t* thing);
void P_PlayerInSpecialSector(player_t* player);
int twoSided(int sector, int line);
sector_t* getSector(int currentSector, int line, int side);
side_t* getSide(int currentSector, int line, int side);
fixed_t P_FindLowestFloorSurrounding(sector_t* sec);
fixed_t P_FindHighestFloorSurrounding(sector_t* sec);
fixed_t P_FindNextHighestFloor(sector_t* sec, int currentheight);
fixed_t P_FindLowestCeilingSurrounding(sector_t* sec);
fixed_t P_FindHighestCeilingSurrounding(sector_t* sec);
int P_FindSectorFromLineTag(line_t* line, int start);
int P_FindMinSurroundingLight(sector_t* sector, int max);
sector_t* getNextSector(line_t* line, sector_t* sec);

//
// SPECIAL
//
int EV_DoDonut(line_t* line);


//
// P_LIGHTS
//
typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    int count;
    int maxlight;
    int minlight;
} fireflicker_t;


typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    int count;
    int maxlight;
    int minlight;
    int maxtime;
    int mintime;
} lightflash_t;


typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    int count;
    int minlight;
    int maxlight;
    int darktime;
    int brighttime;
} strobe_t;


typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    int minlight;
    int maxlight;
    int direction;
} glow_t;


#define GLOWSPEED 8
#define STROBEBRIGHT 5
#define FASTDARK 15
#define SLOWDARK 35

void P_SpawnFireFlicker(sector_t* sector);
void T_LightFlash(lightflash_t* flash);
void P_SpawnLightFlash(sector_t* sector);
void T_StrobeFlash(strobe_t* flash);

void P_SpawnStrobeFlash(sector_t* sector, int fastOrSlow, int inSync);
void EV_StartLightStrobing(line_t* line);
void EV_TurnTagLightsOff(line_t* line);

void EV_LightTurnOn(line_t* line, int bright);

void T_Glow(glow_t* g);
void P_SpawnGlowingLight(sector_t* sector);


//
// P_SWITCH
//
typedef struct
{
    char* name1;
    char* name2;
    short episode;
} switchlist_t;


typedef enum
{
    top,
    middle,
    bottom
} bwhere_e;


typedef struct
{
    line_t* line;
    bwhere_e where;
    int btexture;
    int btimer;
    mobj_t* soundorg;
} button_t;


// max # of wall switches in a level
#define MAXSWITCHES 50

// 4 players, 4 buttons each at once, max.
#define MAXBUTTONS 16

// 1 second, in ticks. 
#define BUTTONTIME 35             


extern button_t buttonlist[MAXBUTTONS];


void P_ChangeSwitchTexture(line_t* line, int useAgain);
void P_InitSwitchList(void);


//
// P_PLATS
//
typedef enum
{
    up,
    down,
    waiting,
    in_stasis
} plat_e;


typedef enum
{
    perpetualRaise,
    downWaitUpStay,
    raiseAndChange,
    raiseToNearestAndChange,
    blazeDWUS
} plattype_e;


typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    fixed_t speed;
    fixed_t low;
    fixed_t high;
    int wait;
    int count;
    plat_e status;
    plat_e oldstatus;
    doom_boolean crush;
    int tag;
    plattype_e type;
} plat_t;


#define PLATWAIT 3
#define PLATSPEED FRACUNIT
#define MAXPLATS 30


extern plat_t* activeplats[MAXPLATS];


void T_PlatRaise(plat_t* plat);
int EV_DoPlat(line_t* line, plattype_e type, int amount);
void P_AddActivePlat(plat_t* plat);
void P_RemoveActivePlat(plat_t* plat);
void EV_StopPlat(line_t* line);
void P_ActivateInStasis(int tag);


//
// P_DOORS
//
typedef enum
{
    door_normal,
    close30ThenOpen,
    door_close,
    door_open,
    raiseIn5Mins,
    blazeRaise,
    blazeOpen,
    blazeClose
} vldoor_e;


typedef struct
{
    thinker_t thinker;
    vldoor_e type;
    sector_t* sector;
    fixed_t topheight;
    fixed_t speed;

    // 1 = up, 0 = waiting at top, -1 = down
    int direction;

    // tics to wait at the top
    int topwait;

    // (keep in case a door going down is reset)
    // when it reaches 0, start going down
    int topcountdown;
} vldoor_t;


#define VDOORSPEED                FRACUNIT*2
#define VDOORWAIT                150


void EV_VerticalDoor(line_t* line, mobj_t* thing);
int EV_DoDoor(line_t* line, vldoor_e type);
int EV_DoLockedDoor(line_t* line, vldoor_e type, mobj_t* thing);
void T_VerticalDoor(vldoor_t* door);
void P_SpawnDoorCloseIn30(sector_t* sec);
void P_SpawnDoorRaiseIn5Mins(sector_t* sec, int secnum);


//
// P_CEILNG
//
typedef enum
{
    lowerToFloor,
    raiseToHighest,
    lowerAndCrush,
    crushAndRaise,
    fastCrushAndRaise,
    silentCrushAndRaise
} ceiling_e;


typedef struct
{
    thinker_t thinker;
    ceiling_e type;
    sector_t* sector;
    fixed_t bottomheight;
    fixed_t topheight;
    fixed_t speed;
    doom_boolean crush;

    // 1 = up, 0 = waiting, -1 = down
    int direction;

    // ID
    int tag;
    int olddirection;
} ceiling_t;


#define CEILSPEED FRACUNIT
#define CEILWAIT 150
#define MAXCEILINGS 30


extern ceiling_t* activeceilings[MAXCEILINGS];


int EV_DoCeiling(line_t* line, ceiling_e type);
void T_MoveCeiling(ceiling_t* ceiling);
void P_AddActiveCeiling(ceiling_t* c);
void P_RemoveActiveCeiling(ceiling_t* c);
int EV_CeilingCrushStop(line_t* line);
void P_ActivateInStasisCeiling(line_t* line);


//
// P_FLOOR
//
typedef enum
{
    // lower floor to highest surrounding floor
    lowerFloor,

    // lower floor to lowest surrounding floor
    lowerFloorToLowest,

    // lower floor to highest surrounding floor VERY FAST
    turboLower,

    // raise floor to lowest surrounding CEILING
    raiseFloor,

    // raise floor to next highest surrounding floor
    raiseFloorToNearest,

    // raise floor to shortest height texture around it
    raiseToTexture,

    // lower floor to lowest surrounding floor
    //  and change floorpic
    lowerAndChange,

    raiseFloor24,
    raiseFloor24AndChange,
    raiseFloorCrush,

    // raise to next highest floor, turbo-speed
    raiseFloorTurbo,
    donutRaise,
    raiseFloor512
} floor_e;


typedef enum
{
    build8,        // slowly build by 8
    turbo16        // quickly build by 16
} stair_e;


typedef struct
{
    thinker_t thinker;
    floor_e type;
    doom_boolean crush;
    sector_t* sector;
    int direction;
    int newspecial;
    short texture;
    fixed_t floordestheight;
    fixed_t speed;
} floormove_t;


#define FLOORSPEED FRACUNIT


typedef enum
{
    ok,
    crushed,
    pastdest
} result_e;


result_e T_MovePlane(sector_t* sector, fixed_t speed, fixed_t dest, doom_boolean crush, int floorOrCeiling, int direction);
int EV_BuildStairs(line_t* line, stair_e type);
int EV_DoFloor(line_t* line, floor_e floortype);
void T_MoveFloor(floormove_t* floor);

//
// P_TELEPT
//
int EV_Teleport(line_t* line, int side, mobj_t* thing);


#endif


#ifndef __R_BSP__
#define __R_BSP__


//#include "r_defs.h"


extern seg_t* curline;
extern side_t* sidedef;
extern line_t* linedef;
extern sector_t* frontsector;
extern sector_t* backsector;

extern int rw_x;
extern int rw_stopx;

extern doom_boolean segtextured;

// false if the back side is the same plane
extern doom_boolean markfloor;
extern doom_boolean markceiling;

extern doom_boolean skymap;

extern drawseg_t drawsegs[MAXDRAWSEGS];
extern drawseg_t* ds_p;

extern lighttable_t** hscalelight;
extern lighttable_t** vscalelight;
extern lighttable_t** dscalelight;


typedef void (*drawfunc_t) (int start, int stop);


// BSP?
void R_ClearClipSegs(void);
void R_ClearDrawSegs(void);
void R_RenderBSPNode(int bspnum);


#endif


#ifndef __R_DRAW__
#define __R_DRAW__


//#include "r_defs.h"


extern lighttable_t* dc_colormap;
extern int dc_x;
extern int dc_yl;
extern int dc_yh;
extern fixed_t dc_iscale;
extern fixed_t dc_texturemid;

// first pixel in a column
extern byte* dc_source;


// The span blitting interface.
// Hook in assembler or system specific BLT
//  here.
void R_DrawColumn(void);
void R_DrawColumnLow(void);

// The Spectre/Invisibility effect.
void R_DrawFuzzColumn(void);
void R_DrawFuzzColumnLow(void);

// Draw with color translation tables,
//  for player sprite rendering,
//  Green/Red/Blue/Indigo shirts.
void R_DrawTranslatedColumn(void);
void R_DrawTranslatedColumnLow(void);

void R_VideoErase(unsigned ofs, int count);

extern int ds_y;
extern int ds_x1;
extern int ds_x2;

extern lighttable_t* ds_colormap;

extern fixed_t ds_xfrac;
extern fixed_t ds_yfrac;
extern fixed_t ds_xstep;
extern fixed_t ds_ystep;

// start of a 64*64 tile image
extern byte* ds_source;

extern byte* translationtables;
extern byte* dc_translation;


// Span blitting for rows, floor/ceiling.
// No Sepctre effect needed.
void R_DrawSpan(void);

// Low resolution mode, 160x200?
void R_DrawSpanLow(void);

void R_InitBuffer(int width, int height);


// Initialize color translation tables,
//  for player rendering etc.
void R_InitTranslationTables(void);

// Rendering function.
void R_FillBackScreen(void);

// If the view size is not full screen, draws a border around it.
void R_DrawViewBorder(void);


#endif


#ifndef __R_SEGS__
#define __R_SEGS__


//#include "r_defs.h"


void R_RenderMaskedSegRange(drawseg_t* ds, int x1, int x2);


#endif


#ifndef __R_STATE__
#define __R_STATE__


//#include "d_player.h" // Need data structure definitions.
//#include "r_defs.h"


//
// Refresh internal data structures,
// for rendering.
//

// needed for texture pegging
extern fixed_t* textureheight;

// needed for pre rendering (fracs)
extern fixed_t* spritewidth;

extern fixed_t* spriteoffset;
extern fixed_t* spritetopoffset;

extern lighttable_t* colormaps;

extern int viewwidth;
extern int scaledviewwidth;
extern int viewheight;

extern int firstflat;

// for global animation
extern int* flattranslation;
extern int* texturetranslation;

// Sprite....
extern int firstspritelump;
extern int lastspritelump;
extern int numspritelumps;

//
// Lookup tables for map data.
//
extern int numsprites;
extern spritedef_t* sprites;

extern int numvertexes;
extern vertex_t* vertexes;

extern int numsegs;
extern seg_t* segs;

extern int numsectors;
extern sector_t* sectors;

extern int numsubsectors;
extern subsector_t* subsectors;

extern int numnodes;
extern node_t* nodes;

extern int numlines;
extern line_t* lines;

extern int numsides;
extern side_t* sides;

//
// POV data.
//
extern fixed_t viewx;
extern fixed_t viewy;
extern fixed_t viewz;

extern angle_t viewangle;
extern player_t* viewplayer;

// ?
extern angle_t clipangle;

extern int viewangletox[FINEANGLES / 2];
extern angle_t xtoviewangle[SCREENWIDTH + 1];

extern fixed_t rw_distance;
extern angle_t rw_normalangle;

// angle to line origin
extern int rw_angle1;

// Segs count?
extern int sscount;

extern visplane_t* floorplane;
extern visplane_t* ceilingplane;


#endif


#ifndef __R_DATA__
#define __R_DATA__


//#include "r_defs.h"
//#include "r_state.h"


// Retrieve column data for span blitting.
byte* R_GetColumn(int tex, int col);

// I/O, setting up the stuff.
void R_InitData(void);
void R_PrecacheLevel(void);

// Retrieval.
// Floor/ceiling opaque texture tiles,
// lookup by name. For animation?
int R_FlatNumForName(char* name);

// Called by P_Ticker for switches and animations,
// returns the texture number for the texture name.
int R_TextureNumForName(char* name);
int R_CheckTextureNumForName(char* name);

#endif


#ifndef __R_MAIN__
#define __R_MAIN__

//#include "d_player.h"
//#include "r_data.h"


//
// POV related.
//
extern fixed_t viewcos;
extern fixed_t viewsin;

extern int viewwidth;
extern int viewheight;
extern int viewwindowx;
extern int viewwindowy;

extern int centerx;
extern int centery;

extern fixed_t centerxfrac;
extern fixed_t centeryfrac;
extern fixed_t projection;

extern int validcount;

extern int linecount;
extern int loopcount;


//
// Lighting LUT.
// Used for z-depth cuing per column/row,
// and other lighting effects (sector ambient, flash).
//

// Lighting constants.
// Now why not 32 levels here?
#define LIGHTLEVELS 16
#define LIGHTSEGSHIFT 4

#define MAXLIGHTSCALE 48
#define LIGHTSCALESHIFT 12
#define MAXLIGHTZ 128
#define LIGHTZSHIFT 20

extern lighttable_t* scalelight[LIGHTLEVELS][MAXLIGHTSCALE];
extern lighttable_t* scalelightfixed[MAXLIGHTSCALE];
extern lighttable_t* zlight[LIGHTLEVELS][MAXLIGHTZ];

extern int extralight;
extern lighttable_t* fixedcolormap;


// Number of diminishing brightness levels.
// There a 0-31, i.e. 32 LUT in the COLORMAP lump.
#define NUMCOLORMAPS 32


// Blocky/low detail mode.
//B remove this?
//  0 = high, 1 = low
extern int detailshift;


//
// Function pointers to switch refresh/drawing functions.
// Used to select shadow mode etc.
//
extern void (*colfunc) (void);
extern void (*basecolfunc) (void);
extern void (*fuzzcolfunc) (void);
// No shadow effects on floors.
extern void (*spanfunc) (void);


//
// Utility functions.
int R_PointOnSide(fixed_t x, fixed_t y, node_t* node);
int R_PointOnSegSide(fixed_t x, fixed_t y, seg_t* line);
angle_t R_PointToAngle(fixed_t x, fixed_t y);
angle_t R_PointToAngle2(fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2);
fixed_t R_PointToDist(fixed_t x, fixed_t y);
fixed_t R_ScaleFromGlobalAngle(angle_t visangle);
subsector_t* R_PointInSubsector(fixed_t x, fixed_t y);
void R_AddPointToBox(int x, int y, fixed_t* box);


//
// REFRESH - the actual rendering functions.
//

// Called by G_Drawer.
void R_RenderPlayerView(player_t* player);

// Called by startup code.
void R_Init(void);

// Called by M_Responder.
void R_SetViewSize(int blocks, int detail);

#endif


#ifndef __R_PLANE__
#define __R_PLANE__


//#include "r_data.h"


// Visplane related.
extern short* lastopening;

typedef void (*planefunction_t) (int top, int bottom);

extern planefunction_t floorfunc;
extern planefunction_t ceilingfunc_t;

extern short floorclip[SCREENWIDTH];
extern short ceilingclip[SCREENWIDTH];

extern fixed_t yslope[SCREENHEIGHT];
extern fixed_t distscale[SCREENWIDTH];

void R_InitPlanes(void);
void R_ClearPlanes(void);
void R_MapPlane(int y, int x1, int x2);
void R_MakeSpans(int x, int t1, int b1, int t2, int b2);
void R_DrawPlanes(void);
visplane_t* R_FindPlane(fixed_t height, int picnum, int lightlevel);
visplane_t* R_CheckPlane(visplane_t* pl, int start, int stop);


#endif


#ifndef __R_THINGS__
#define __R_THINGS__


//#include "r_defs.h"


#define MAXVISSPRITES 128


extern vissprite_t vissprites[MAXVISSPRITES];
extern vissprite_t* vissprite_p;
extern vissprite_t vsprsortedhead;

// Constant arrays used for psprite clipping
// and initializing clipping.
extern short negonearray[SCREENWIDTH];
extern short screenheightarray[SCREENWIDTH];

// vars for R_DrawMaskedColumn
extern short* mfloorclip;
extern short* mceilingclip;
extern fixed_t spryscale;
extern fixed_t sprtopscreen;

extern fixed_t pspritescale;
extern fixed_t pspriteiscale;


void R_DrawMaskedColumn(column_t* column);
void R_SortVisSprites(void);
void R_AddSprites(sector_t* sec);
void R_InitSprites(char** namelist);
void R_ClearSprites(void);
void R_DrawMasked(void);


#endif


#ifndef __R_LOCAL__
#define __R_LOCAL__

// Binary Angles, sine/cosine/atan lookups.
//#include "tables.h"

// Screen size related parameters.
//#include "doomdef.h"

// Include the refresh/render data structs.
//#include "r_data.h"

//
// Separate header file for each module.
//
//#include "r_main.h"
//#include "r_bsp.h"
//#include "r_segs.h"
//#include "r_plane.h"
//#include "r_data.h"
//#include "r_things.h"
//#include "r_draw.h"

#endif // __R_LOCAL__


#ifndef __P_LOCAL__
#define __P_LOCAL__


#ifndef __R_LOCAL__
//#include "r_local.h"
#endif


#define FLOATSPEED (FRACUNIT*4)

#define MAXHEALTH 100
#define VIEWHEIGHT (41*FRACUNIT)

// mapblocks are used to check movement
// against lines and things
#define MAPBLOCKUNITS 128
#define MAPBLOCKSIZE (MAPBLOCKUNITS*FRACUNIT)
#define MAPBLOCKSHIFT (FRACBITS+7)
#define MAPBMASK (MAPBLOCKSIZE-1)
#define MAPBTOFRAC (MAPBLOCKSHIFT-FRACBITS)


// player radius for movement checking
#define PLAYERRADIUS 16*FRACUNIT

// MAXRADIUS is for precalculated sector block boxes
// the spider demon is larger,
// but we do not have any moving sectors nearby
#define MAXRADIUS 32*FRACUNIT

#define GRAVITY FRACUNIT
#define MAXMOVE (30*FRACUNIT)

#define USERANGE (64*FRACUNIT)
#define MELEERANGE (64*FRACUNIT)
#define MISSILERANGE (32*64*FRACUNIT)

// follow a player exlusively for 3 seconds
#define BASETHRESHOLD 100


//
// P_TICK
//

// both the head and tail of the thinker list
extern thinker_t thinkercap;


void P_InitThinkers(void);
void P_AddThinker(thinker_t* thinker);
void P_RemoveThinker(thinker_t* thinker);


//
// P_PSPR
//
void P_SetupPsprites(player_t* curplayer);
void P_MovePsprites(player_t* curplayer);
void P_DropWeapon(player_t* player);


//
// P_USER
//
void P_PlayerThink(player_t* player);


//
// P_MOBJ
//
#define ONFLOORZ DOOM_MININT
#define ONCEILINGZ DOOM_MAXINT

// Time interval for item respawning.
#define ITEMQUESIZE                128


extern mapthing_t itemrespawnque[ITEMQUESIZE];
extern int itemrespawntime[ITEMQUESIZE];
extern int iquehead;
extern int iquetail;


void P_RespawnSpecials(void);
mobj_t* P_SpawnMobj(fixed_t x, fixed_t y, fixed_t z, mobjtype_t type);
void P_RemoveMobj(mobj_t* th);
doom_boolean P_SetMobjState(mobj_t* mobj, statenum_t state);
void P_MobjThinker(mobj_t* mobj);
void P_SpawnPuff(fixed_t x, fixed_t y, fixed_t z);
void P_SpawnBlood(fixed_t x, fixed_t y, fixed_t z, int damage);
mobj_t* P_SpawnMissile(mobj_t* source, mobj_t* dest, mobjtype_t type);
void P_SpawnPlayerMissile(mobj_t* source, mobjtype_t type);


//
// P_ENEMY
//
void P_NoiseAlert(mobj_t* target, mobj_t* emmiter);


//
// P_MAPUTL
//
typedef struct
{
    fixed_t x;
    fixed_t y;
    fixed_t dx;
    fixed_t dy;
} divline_t;


typedef struct
{
    fixed_t frac; // along trace line
    doom_boolean isaline;
    union
    {
        mobj_t* thing;
        line_t* line;
    } d;
} intercept_t;


#define MAXINTERCEPTS        128
extern intercept_t intercepts[MAXINTERCEPTS];
extern intercept_t* intercept_p;


typedef doom_boolean(*traverser_t) (intercept_t* in);


fixed_t P_AproxDistance(fixed_t dx, fixed_t dy);
int P_PointOnLineSide(fixed_t x, fixed_t y, line_t* line);
int P_PointOnDivlineSide(fixed_t x, fixed_t y, divline_t* line);
void P_MakeDivline(line_t* li, divline_t* dl);
fixed_t P_InterceptVector(divline_t* v2, divline_t* v1);
int P_BoxOnLineSide(fixed_t* tmbox, line_t* ld);


extern fixed_t opentop;
extern fixed_t openbottom;
extern fixed_t openrange;
extern fixed_t lowfloor;


void P_LineOpening(line_t* linedef);


doom_boolean P_BlockLinesIterator(int x, int y, doom_boolean(*func)(line_t*));
doom_boolean P_BlockThingsIterator(int x, int y, doom_boolean(*func)(mobj_t*));


#define PT_ADDLINES     1
#define PT_ADDTHINGS    2
#define PT_EARLYOUT     4


extern divline_t trace;


doom_boolean P_PathTraverse(fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2, int flags, doom_boolean(*trav) (intercept_t*));
void P_UnsetThingPosition(mobj_t* thing);
void P_SetThingPosition(mobj_t* thing);


//
// P_MAP
//

// If "floatok" true, move would be ok
// if within "tmfloorz - tmceilingz".
extern doom_boolean floatok;
extern fixed_t tmfloorz;
extern fixed_t tmceilingz;

extern line_t* ceilingline;


doom_boolean P_CheckPosition(mobj_t* thing, fixed_t x, fixed_t y);
doom_boolean P_TryMove(mobj_t* thing, fixed_t x, fixed_t y);
doom_boolean P_TeleportMove(mobj_t* thing, fixed_t x, fixed_t y);
void P_SlideMove(mobj_t* mo);
doom_boolean P_CheckSight(mobj_t* t1, mobj_t* t2);
void P_UseLines(player_t* player);
doom_boolean P_ChangeSector(sector_t* sector, doom_boolean crunch);


extern mobj_t* linetarget;        // who got hit (or 0)


fixed_t P_AimLineAttack(mobj_t* t1, angle_t angle, fixed_t distance);
void P_LineAttack(mobj_t* t1, angle_t angle, fixed_t distance, fixed_t slope, int damage);
void P_RadiusAttack(mobj_t* spot, mobj_t* source, int damage);


//
// P_SETUP
//
extern byte* rejectmatrix; // for fast sight rejection
extern short* blockmaplump; // offsets in blockmap are from here
extern short* blockmap;
extern int bmapwidth;
extern int bmapheight; // in mapblocks
extern fixed_t bmaporgx;
extern fixed_t bmaporgy; // origin of block map
extern mobj_t** blocklinks; // for thing chains


//
// P_INTER
//
extern int maxammo[NUMAMMO];
extern int clipammo[NUMAMMO];


void P_TouchSpecialThing(mobj_t* special, mobj_t* toucher);
void P_DamageMobj(mobj_t* target, mobj_t* inflictor, mobj_t* source, int damage);


//
// P_SPEC
//
//#include "p_spec.h"


#endif // __P_LOCAL__


#ifndef __STLIB__
#define __STLIB__


// We are referring to patches.
//#include "r_defs.h"


//
// Background and foreground screen numbers
//
#define STLIB_BG 4
#define STLIB_FG 0


//
// Typedefs of widgets
//

// Number widget
typedef struct
{
    // upper right-hand corner
    //  of the number (right-justified)
    int x;
    int y;

    // max # of digits in number
    int width;

    // last number value
    int oldnum;

    // pointer to current value
    int* num;

    // pointer to doom_boolean stating
    //  whether to update number
    doom_boolean* on;

    // list of patches for 0-9
    patch_t** p;

    // user data
    int data;
} st_number_t;


// Percent widget ("child" of number widget,
//  or, more precisely, contains a number widget.)
typedef struct
{
    // number information
    st_number_t n;

    // percent sign graphic
    patch_t* p;
} st_percent_t;


// Multiple Icon widget
typedef struct
{
    // center-justified location of icons
    int x;
    int y;

    // last icon number
    int oldinum;

    // pointer to current icon
    int* inum;

    // pointer to doom_boolean stating
    //  whether to update icon
    doom_boolean* on;

    // list of icons
    patch_t** p;

    // user data
    int data;
} st_multicon_t;


// Binary Icon widget
typedef struct
{
    // center-justified location of icon
    int x;
    int y;

    // last icon value
    int oldval;

    // pointer to current icon status
    doom_boolean* val;

    // pointer to doom_boolean
    //  stating whether to update icon
    doom_boolean* on;


    patch_t* p; // icon
    int data;   // user data

} st_binicon_t;


//
// Widget creation, access, and update routines
//

// Initializes widget library.
// More precisely, initialize STMINUS,
// everything else is done somewhere else.
//
void STlib_init(void);

// Number widget routines
void STlib_initNum(st_number_t* n,
                   int x,
                   int y,
                   patch_t** pl,
                   int* num,
                   doom_boolean* on,
                   int width);

void STlib_updateNum(st_number_t* n, doom_boolean refresh);

// Percent widget routines
void STlib_initPercent(st_percent_t* p,
                       int x,
                       int y,
                       patch_t** pl,
                       int* num,
                       doom_boolean* on,
                       patch_t* percent);

void STlib_updatePercent(st_percent_t* per, int refresh);

// Multiple Icon widget routines
void STlib_initMultIcon(st_multicon_t* mi,
                        int x,
                        int y,
                        patch_t** il,
                        int* inum,
                        doom_boolean* on);

void STlib_updateMultIcon(st_multicon_t* mi, doom_boolean refresh);

// Binary Icon widget routines
void STlib_initBinIcon(st_binicon_t* b,
                       int x,
                       int y,
                       patch_t* i,
                       doom_boolean* val,
                       doom_boolean* on);

void STlib_updateBinIcon(st_binicon_t* bi, doom_boolean refresh);

#endif


#ifndef __V_VIDEO__
#define __V_VIDEO__

//#include "doomtype.h"
//#include "doomdef.h"
//#include "r_data.h" // Needed because we are refering to patches.

//
// VIDEO
//

#define CENTERY (SCREENHEIGHT / 2)


// Screen 0 is the screen updated by I_Update screen.
// Screen 1 is an extra buffer.
extern byte* screens[5];
extern int dirtybox[4];
extern byte gammatable[5][256];
extern int usegamma;


// Allocates buffer screens, call before R_Init.
void V_Init(void);

void V_CopyRect(int srcx,
                int srcy,
                int srcscrn,
                int width,
                int height,
                int destx,
                int desty,
                int destscrn);

void V_DrawPatch(int x,
                 int y,
                 int scrn,
                 patch_t* patch);

void V_DrawPatchDirect(int x, 
                       int y, 
                       int scrn, 
                       patch_t* patch);

void V_DrawPatchRectDirect(int x, int y, int scrn, patch_t* patch, int src_x, int src_w);

// Draw a linear block of pixels into the view buffer.
void V_DrawBlock(int x,
                 int y,
                 int scrn,
                 int width,
                 int height,
                 byte* src);

// Reads a linear block of pixels into the view buffer.
void V_GetBlock(int x,
                int y,
                int scrn,
                int width,
                int height,
                byte* dest);

void V_MarkRect(int x,
                int y,
                int width,
                int height);

#endif


#ifndef __W_WAD__
#define __W_WAD__


//
// TYPES
//
typedef struct
{
    // Should be "IWAD" or "PWAD".
    char identification[4];
    int numlumps;
    int infotableofs;
} wadinfo_t;


typedef struct
{
    int filepos;
    int size;
    char name[8];
} filelump_t;


//
// WADFILE I/O related stuff.
//
typedef struct
{
    char name[8];
    void* handle;
    int position;
    int size;
} lumpinfo_t;


extern void** lumpcache;
extern lumpinfo_t* lumpinfo;
extern int numlumps;

void W_InitMultipleFiles(char** filenames);
void W_Reload(void);

int W_CheckNumForName(char* name);
int W_GetNumForName(char* name);

int W_LumpLength(int lump);
void W_ReadLump(int lump, void* dest);

void* W_CacheLumpNum(int lump, int tag);
void* W_CacheLumpName(char* name, int tag);


#endif


#ifndef __WI_STUFF__
#define __WI_STUFF__

//#include "doomdef.h"

// States for the intermission
typedef enum
{
    NoState = -1,
    StatCount,
    ShowNextLoc
} stateenum_t;

// Called by main loop, animate the intermission.
void WI_Ticker(void);

// Called by main loop,
// draws the intermission directly into the screen buffer.
void WI_Drawer(void);

// Setup for an intermission screen.
void WI_Start(wbstartstruct_t* wbstartstruct);

#endif


#ifndef __Z_ZONE__
#define __Z_ZONE__




//
// ZONE MEMORY
// PU - purge tags.
// Tags < 100 are not overwritten until freed.
#define PU_STATIC       1        // static entire execution time
#define PU_SOUND        2        // static while playing
#define PU_MUSIC        3        // static while playing
#define PU_DAVE         4        // anything else Dave wants static
#define PU_LEVEL        50       // static until level exited
#define PU_LEVSPEC      51       // a special thinker in a level
// Tags >= 100 are purgable whenever needed.
#define PU_PURGELEVEL   100
#define PU_CACHE        101


void  Z_Init(void);
void* Z_Malloc(int size, int tag, void* ptr);
void  Z_Free(void* ptr);
void  Z_FreeTags(int lowtag, int hightag);
void  Z_DumpHeap(int lowtag, int hightag);
void  Z_FileDumpHeap(void* f);
void  Z_CheckHeap(void);
void  Z_ChangeTag2(void* ptr, int tag);
int   Z_FreeMemory(void);


typedef struct memblock_s
{
    int size;       // including the header and possibly tiny fragments
    void** user;    // 0 if a free block
    int tag;        // purgelevel
    int id;         // should be ZONEID
    struct memblock_s* next;
    struct memblock_s* prev;
} memblock_t;

//
// This is used to get the local FILE:LINE info from CPP
// prior to really call the function in question.
//
#define Z_ChangeTag(p,t) \
{ \
    if (( (memblock_t *)( (byte *)(p) - sizeof(memblock_t)))->id!=0x1d4a11) \
    { \
        /*I_Error("Error: Z_CT at "__FILE__":%i",__LINE__);*/ \
        char buf[260]; \
        doom_strcpy(buf, "Error: Z_CT at " __FILE__ ":"); \
        doom_concat(buf, doom_itoa(__LINE__, 10)); \
        I_Error(buf); \
    } \
    Z_ChangeTag2(p,t); \
};


#endif



//#if defined(DOOM_IMPLEMENTATION)
#if defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#endif

//#include "DOOM.h"

//#include "d_main.h"
//#include "doomdef.h"
//#include "doomtype.h"
//#include "i_system.h"
//#include "m_argv.h"
//#include "m_misc.h"


extern byte* screens[5];
extern unsigned char screen_palette[256 * 3];
extern doom_boolean is_wiping_screen;
extern default_t defaults[];
extern int numdefaults;
extern signed short mixbuffer[2048];


unsigned char* screen_buffer = 0;
unsigned char* final_screen_buffer = 0;
int last_update_time = 0;
int button_states[3] = { 0 };
char itoa_buf[20];


char error_buf[260];
int doom_flags = 0;
doom_print_fn doom_print = 0;
doom_malloc_fn doom_malloc = 0;
doom_free_fn doom_free = 0;
doom_open_fn doom_open = 0;
doom_close_fn doom_close = 0;
doom_read_fn doom_read = 0;
doom_write_fn doom_write = 0;
doom_seek_fn doom_seek = 0;
doom_tell_fn doom_tell = 0;
doom_eof_fn doom_eof = 0;
doom_gettime_fn doom_gettime = 0;
doom_exit_fn doom_exit = 0;
doom_getenv_fn doom_getenv = 0;


void D_DoomLoop(void);
void D_UpdateWipe(void);
void I_UpdateSound();
unsigned long I_TickSong();


extern void doom_print_impl(const char* str);

extern void* doom_malloc_impl(int size);
extern void doom_free_impl(void* ptr);

extern void* doom_open_impl(const char* filename, const char* mode);
extern void doom_close_impl(void* handle);
extern int doom_read_impl(void* handle, void *buf, int count);
extern int doom_write_impl(void* handle, const void *buf, int count);
extern int doom_seek_impl(void* handle, int offset, doom_seek_t origin);
extern int doom_tell_impl(void* handle);
extern int doom_eof_impl(void* handle);

extern void doom_gettime_impl(int* sec, int* usec);

extern void doom_exit_impl(int code);

extern char* doom_getenv_impl(const char* var);


extern void doom_memset(void* ptr, int value, int num);


extern void* doom_memcpy(void* destination, const void* source, int num);


extern int doom_strlen(const char* str);

extern char* doom_concat(char* dst, const char* src);


extern char* doom_strcpy(char* dst, const char* src);


extern char* doom_strncpy(char* dst, const char* src, int num);


extern int doom_strcmp(const char* str1, const char* str2);


extern int doom_strncmp(const char* str1, const char* str2, int n);


extern int doom_toupper(int c);


extern int doom_strcasecmp(const char* str1, const char* str2);

extern int doom_strncasecmp(const char* str1, const char* str2, int n);

extern int doom_atoi(const char* str);

extern int doom_atox(const char* str);


extern const char* doom_itoa(int k, int radix);

extern const char* doom_ctoa(char c);


extern const char* doom_ptoa(void* p);


extern int doom_fprint(void* handle, const char* str);


extern default_t* get_default(const char* name);


extern void doom_set_resolution(int width, int height);


extern void doom_set_default_int(const char* name, int value);


extern void doom_set_default_string(const char* name, const char* value);


extern void doom_set_print(doom_print_fn print_fn);


extern void doom_set_malloc(doom_malloc_fn malloc_fn, doom_free_fn free_fn);


extern void doom_set_file_io(doom_open_fn open_fn,
                      doom_close_fn close_fn,
                      doom_read_fn read_fn,
                      doom_write_fn write_fn,
                      doom_seek_fn seek_fn,
                      doom_tell_fn tell_fn,
                      doom_eof_fn eof_fn);

extern void doom_set_gettime(doom_gettime_fn gettime_fn);


extern void doom_set_exit(doom_exit_fn exit_fn);

extern void doom_set_getenv(doom_getenv_fn getenv_fn);


extern void doom_init(int argc, char** argv, int flags);


extern void doom_update(void);


extern void doom_force_update(void);


extern const unsigned char* doom_get_framebuffer(int channels);


extern unsigned long doom_tick_midi(void);


extern short* doom_get_sound_buffer(void);


extern void doom_key_down(doom_key_t key);


extern void doom_key_up(doom_key_t key);

extern void doom_button_down(doom_button_t button);

extern void doom_button_up(doom_button_t button);


extern void doom_mouse_move(int delta_x, int delta_y);

#define REDS        (256-5*16)
#define REDRANGE    16
#define BLUES       (256-4*16+8)
#define BLUERANGE   8
#define GREENS      (7*16)
#define GREENRANGE  16
#define GRAYS       (6*16)
#define GRAYSRANGE  16
#define BROWNS      (4*16)
#define BROWNRANGE  16
#define YELLOWS     (256-32+7)
#define YELLOWRANGE 1
#define BLACK       0
#define WHITE       (256-47)

// Automap colors
#define BACKGROUND          BLACK
#define YOURCOLORS          WHITE
#define YOURRANGE           0
#define WALLCOLORS          REDS
#define WALLRANGE           REDRANGE
#define TSWALLCOLORS        GRAYS
#define TSWALLRANGE         GRAYSRANGE
#define FDWALLCOLORS        BROWNS
#define FDWALLRANGE         BROWNRANGE
#define CDWALLCOLORS        YELLOWS
#define CDWALLRANGE         YELLOWRANGE
#define THINGCOLORS         GREENS
#define THINGRANGE          GREENRANGE
#define SECRETWALLCOLORS    WALLCOLORS
#define SECRETWALLRANGE     WALLRANGE
#define GRIDCOLORS          (GRAYS + GRAYSRANGE/2)
#define GRIDRANGE           0
#define XHAIRCOLORS         GRAYS

// drawing stuff
#define FB 0

#define AM_PANDOWNKEY   KEY_DOWNARROW
#define AM_PANUPKEY     KEY_UPARROW
#define AM_PANRIGHTKEY  KEY_RIGHTARROW
#define AM_PANLEFTKEY   KEY_LEFTARROW
#define AM_ZOOMINKEY    '='
#define AM_ZOOMOUTKEY   '-'
#define AM_STARTKEY     KEY_TAB
#define AM_ENDKEY       KEY_TAB
#define AM_GOBIGKEY     '0'
#define AM_FOLLOWKEY    'f'
#define AM_GRIDKEY      'g'
#define AM_MARKKEY      'm'
#define AM_CLEARMARKKEY 'c'

#define AM_NUMMARKPOINTS 10

// scale on entry
#define INITSCALEMTOF (.2*FRACUNIT)
// how much the automap moves window per tic in frame-buffer coordinates
// moves 140 pixels in 1 second
#define F_PANINC        4
// how much zoom-in per tic
// goes to 2x in 1 second
#define M_ZOOMIN        ((int) (1.02*FRACUNIT))
// how much zoom-out per tic
// pulls out to 0.5x in 1 second
#define M_ZOOMOUT       ((int) (FRACUNIT/1.02))

// translates between frame-buffer and map distances
#define FTOM(x) FixedMul(((x)<<16),scale_ftom)
#define MTOF(x) (FixedMul((x),scale_mtof)>>16)
// translates between frame-buffer and map coordinates
#define CXMTOF(x)  (f_x + MTOF((x)-m_x))
#define CYMTOF(y)  (f_y + (f_h - MTOF((y)-m_y)))

// the following is crap
#define LINE_NEVERSEE ML_DONTDRAW


typedef struct
{
    int x, y;
} fpoint_t;


typedef struct
{
    fpoint_t a, b;
} fline_t;


typedef struct
{
    fixed_t                x, y;
} mpoint_t;


typedef struct
{
    mpoint_t a, b;
} mline_t;


typedef struct
{
    fixed_t slp, islp;
} islope_t;


//
// The vector graphics for the automap.
// A line drawing of the player pointing right,
// starting from the middle.
//
#define R ((8*PLAYERRADIUS)/7)
mline_t player_arrow[] = {
    { { -R + R / 8, 0 }, { R, 0 } }, // -----
    { { R, 0 }, { R - R / 2, R / 4 } },  // ----->
    { { R, 0 }, { R - R / 2, -R / 4 } },
    { { -R + R / 8, 0 }, { -R - R / 8, R / 4 } }, // >---->
    { { -R + R / 8, 0 }, { -R - R / 8, -R / 4 } },
    { { -R + 3 * R / 8, 0 }, { -R + R / 8, R / 4 } }, // >>--->
    { { -R + 3 * R / 8, 0 }, { -R + R / 8, -R / 4 } }
};
#undef R
#define NUMPLYRLINES (sizeof(player_arrow)/sizeof(mline_t))

#define R ((8*PLAYERRADIUS)/7)
mline_t cheat_player_arrow[] = {
    { { -R + R / 8, 0 }, { R, 0 } }, // -----
    { { R, 0 }, { R - R / 2, R / 6 } },  // ----->
    { { R, 0 }, { R - R / 2, -R / 6 } },
    { { -R + R / 8, 0 }, { -R - R / 8, R / 6 } }, // >----->
    { { -R + R / 8, 0 }, { -R - R / 8, -R / 6 } },
    { { -R + 3 * R / 8, 0 }, { -R + R / 8, R / 6 } }, // >>----->
    { { -R + 3 * R / 8, 0 }, { -R + R / 8, -R / 6 } },
    { { -R / 2, 0 }, { -R / 2, -R / 6 } }, // >>-d--->
    { { -R / 2, -R / 6 }, { -R / 2 + R / 6, -R / 6 } },
    { { -R / 2 + R / 6, -R / 6 }, { -R / 2 + R / 6, R / 4 } },
    { { -R / 6, 0 }, { -R / 6, -R / 6 } }, // >>-dd-->
    { { -R / 6, -R / 6 }, { 0, -R / 6 } },
    { { 0, -R / 6 }, { 0, R / 4 } },
    { { R / 6, R / 4 }, { R / 6, -R / 7 } }, // >>-ddt->
    { { R / 6, -R / 7 }, { R / 6 + R / 32, -R / 7 - R / 32 } },
    { { R / 6 + R / 32, -R / 7 - R / 32 }, { R / 6 + R / 10, -R / 7 } }
};
#undef R
#define NUMCHEATPLYRLINES (sizeof(cheat_player_arrow)/sizeof(mline_t))

#define R (FRACUNIT)
mline_t triangle_guy[] = {
    { { (fixed_t)(-.867 * R), (fixed_t)(-.5 * R) }, { (fixed_t)(.867 * R), (fixed_t)(-.5 * R) } },
    { { (fixed_t)(.867 * R), (fixed_t)(-.5 * R) } , { 0, R } },
    { { 0, R }, { (fixed_t)(-.867 * R), (fixed_t)(-.5 * R) } }
};
#undef R
#define NUMTRIANGLEGUYLINES (sizeof(triangle_guy)/sizeof(mline_t))

#define R (FRACUNIT)
mline_t thintriangle_guy[] = {
    { { (fixed_t)(-.5 * R), (fixed_t)(-.7 * R) }, { R, 0 } },
    { { R, 0 }, { (fixed_t)(-.5 * R), (fixed_t)(.7 * R) } },
    { { (fixed_t)(-.5 * R), (fixed_t)(.7 * R) }, { (fixed_t)(-.5 * R), (fixed_t)(-.7 * R) } }
};
#undef R
#define NUMTHINTRIANGLEGUYLINES (sizeof(thintriangle_guy)/sizeof(mline_t))


 int cheating = 0;
 int grid = 0;

 int leveljuststarted = 1; // kluge until AM_LevelInit() is called

 int finit_width = SCREENWIDTH;
 int finit_height = SCREENHEIGHT - 32;

// location of window on screen
 int f_x;
 int f_y;

// size of window on screen
 int f_w;
 int f_h;

 int lightlev; // used for funky strobing effect
 byte* fb; // pseudo-frame buffer
 int amclock;

 mpoint_t m_paninc; // how far the window pans each tic (map coords)
 fixed_t mtof_zoommul; // how far the window zooms in each tic (map coords)
 fixed_t ftom_zoommul; // how far the window zooms in each tic (fb coords)

 fixed_t m_x, m_y;   // LL x,y where the window is on the map (map coords)
 fixed_t m_x2, m_y2; // UR x,y where the window is on the map (map coords)

//
// width/height of window on map (map coords)
//
 fixed_t m_w;
 fixed_t m_h;

// based on level size
 fixed_t min_x;
 fixed_t min_y;
 fixed_t max_x;
 fixed_t max_y;

 fixed_t max_w; // max_x-min_x,
 fixed_t max_h; // max_y-min_y

// based on player size
 fixed_t min_w;
 fixed_t min_h;

 fixed_t min_scale_mtof; // used to tell when to stop zooming out
 fixed_t max_scale_mtof; // used to tell when to stop zooming in

// old stuff for recovery later
 fixed_t old_m_w, old_m_h;
 fixed_t old_m_x, old_m_y;

// old location used by the Follower routine
 mpoint_t f_oldloc;

// used by MTOF to scale from map-to-frame-buffer coords
 fixed_t scale_mtof = (fixed_t)INITSCALEMTOF;
// used by FTOM to scale from frame-buffer-to-map coords (=1/scale_mtof)
 fixed_t scale_ftom;

 player_t* plr; // the player represented by an arrow

 patch_t* marknums[10]; // numbers used for marking by the automap
 mpoint_t markpoints[AM_NUMMARKPOINTS]; // where the points are
 int markpointnum = 0; // next point to be assigned

 int followplayer = 1; // specifies whether to follow the player around

 unsigned char cheat_amap_seq[] = { 0xb2, 0x26, 0x26, 0x2e, 0xff };
 cheatseq_t cheat_amap = { cheat_amap_seq, 0 };


  doom_boolean stopped = true;


doom_boolean automapactive = false;


extern doom_boolean viewactive;


void V_MarkRect(int x, int y, int width, int height);


//
//
//
extern void AM_activateNewScale(void);


//
//
//
extern void AM_saveScaleAndLoc(void);


//
//
//
extern void AM_restoreScaleAndLoc(void);


//
// adds a marker at the current location
//
extern void AM_addMark(void);


//
// Determines bounding box of all vertices,
// sets global variables controlling zoom range.
//
extern void AM_findMinMaxBoundaries(void);


//
//
//
extern void AM_changeWindowLoc(void);

event_t st_notify;

//
//
//
extern void AM_initVariables(void);


//
// 
//
extern void AM_loadPics(void);


extern void AM_unloadPics(void);

extern void AM_clearMarks(void);

//
// should be called at the start of every level
// right now, i figure it out myself
//
extern void AM_LevelInit(void);


//
//
//
extern void AM_Stop(void);


//
//
//
extern void AM_Start(void);


//
// set the window scale to the maximum size
//
extern void AM_minOutWindowScale(void);


//
// set the window scale to the minimum size
//
extern void AM_maxOutWindowScale(void);


//
// Handle events (user inputs) in automap mode
//
extern doom_boolean AM_Responder(event_t* ev);


//
// Zooming
//
extern void AM_changeWindowScale(void);


//
//
//
extern void AM_doFollowPlayer(void);


//
//
//
extern void AM_updateLightLev(void);


//
// Updates on Game Tick
//
extern void AM_Ticker(void);


//
// Clear automap frame buffer.
//
extern void AM_clearFB(int color);


//
// Automap clipping of lines.
//
// Based on Cohen-Sutherland clipping algorithm but with a slightly
// faster reject and precalculated slopes.  If the speed is needed,
// use a hash algorithm to handle  the common cases.
//
extern doom_boolean AM_clipMline(mline_t* ml, fline_t* fl);


//
// Classic Bresenham w/ whatever optimizations needed for speed
//
extern void AM_drawFline(fline_t* fl, int color);


//
// Clip lines, draw visible part sof lines.
//
extern void AM_drawMline(mline_t* ml, int color);


//
// Draws flat (floor/ceiling tile) aligned grid lines.
//
extern void AM_drawGrid(int color);


//
// Determines visible lines, draws them.
// This is LineDef based, not LineSeg based.
//
extern void AM_drawWalls(void);


//
// Rotation in 2D.
// Used to rotate player arrow line character.
//
extern void AM_rotate(fixed_t* x, fixed_t* y, angle_t a);

extern void AM_drawLineCharacter(mline_t* lineguy,
                          int lineguylines,
                          fixed_t scale,
                          angle_t angle,
                          int color,
                          fixed_t x,
                          fixed_t y);



extern void AM_drawPlayers(void);


extern void AM_drawThings(int colors, int colorrange);


extern void AM_drawMarks(void);


extern void AM_drawCrosshair(int color);

extern void AM_Drawer(void);

weaponinfo_t weaponinfo[NUMWEAPONS] =
{
    {
        // fist
        am_noammo,
        S_PUNCHUP,
        S_PUNCHDOWN,
        S_PUNCH,
        S_PUNCH1,
        S_NULL
    },
    {
        // pistol
        am_clip,
        S_PISTOLUP,
        S_PISTOLDOWN,
        S_PISTOL,
        S_PISTOL1,
        S_PISTOLFLASH
    },
    {
        // shotgun
        am_shell,
        S_SGUNUP,
        S_SGUNDOWN,
        S_SGUN,
        S_SGUN1,
        S_SGUNFLASH1
    },
    {
        // chaingun
        am_clip,
        S_CHAINUP,
        S_CHAINDOWN,
        S_CHAIN,
        S_CHAIN1,
        S_CHAINFLASH1
    },
    {
        // missile launcher
        am_misl,
        S_MISSILEUP,
        S_MISSILEDOWN,
        S_MISSILE,
        S_MISSILE1,
        S_MISSILEFLASH1
    },
    {
        // plasma rifle
        am_cell,
        S_PLASMAUP,
        S_PLASMADOWN,
        S_PLASMA,
        S_PLASMA1,
        S_PLASMAFLASH1
    },
    {
        // bfg 9000
        am_cell,
        S_BFGUP,
        S_BFGDOWN,
        S_BFG,
        S_BFG1,
        S_BFGFLASH1
    },
    {
        // chainsaw
        am_noammo,
        S_SAWUP,
        S_SAWDOWN,
        S_SAW,
        S_SAW1,
        S_NULL
    },
    {
        // super shotgun
        am_shell,
        S_DSGUNUP,
        S_DSGUNDOWN,
        S_DSGUN,
        S_DSGUN1,
        S_DSGUNFLASH1
    },
};
#if defined(DOOM_WIN32)


#define X_OK 0
#define W_OK 2
#define R_OK 4
#define RW_OK 6
#elif defined(DOOM_APPLE)


#endif

//#include "doomdef.h"
//#include "doomstat.h"
//#include "dstrings.h"
//#include "sounds.h"
//#include "z_zone.h"
//#include "w_wad.h"
//#include "s_sound.h"
//#include "v_video.h"
//#include "f_finale.h"
//#include "f_wipe.h"
//#include "m_argv.h"
//#include "m_misc.h"
//#include "m_menu.h"
//#include "i_system.h"
//#include "i_sound.h"
//#include "i_video.h"
//#include "g_game.h"
//#include "hu_stuff.h"
//#include "wi_stuff.h"
//#include "st_stuff.h"
//#include "am_map.h"
//#include "p_setup.h"
//#include "r_local.h"
//#include "d_main.h"


#define MAXARGVS 100


char* wadfiles[MAXWADFILES];

doom_boolean devparm; // started game with -devparm
doom_boolean nomonsters; // checkparm of -nomonsters
doom_boolean respawnparm; // checkparm of -respawn
doom_boolean fastparm; // checkparm of -fast

doom_boolean drone;

doom_boolean singletics = true; // debug flag to cancel adaptiveness

doom_boolean is_wiping_screen = false;

skill_t startskill;
int startepisode;
int startmap;
doom_boolean autostart;

void* debugfile = 0;

doom_boolean advancedemo;

char wadfile[1024]; // primary wad file
char mapdir[1024]; // directory of development maps
char basedefault[1024]; // default file

//
// EVENT HANDLING
//
// Events are asynchronous inputs generally generated by the game user.
// Events can be discarded if no responder claims them
//
event_t events[MAXEVENTS];
int eventhead;
int eventtail;

// wipegamestate can be set to -1 to force a wipe on the next draw
gamestate_t wipegamestate = GS_DEMOSCREEN;
void R_ExecuteSetViewSize(void);

// print title for every printed line
char title[128];


extern  doom_boolean inhelpscreens;
extern doom_boolean setsizeneeded;
extern int showMessages;
extern doom_boolean demorecording;


void D_DoomLoop(void);
void D_CheckNetGame(void);
void D_ProcessEvents(void);
void G_BuildTiccmd(ticcmd_t* cmd);
void D_DoAdvanceDemo(void);


//
// D_PostEvent
// Called by the I/O functions when input is detected
//
extern void D_PostEvent(event_t* ev);


//
// D_ProcessEvents
// Send all the events of the given timestamp down the responder chain
//
extern void D_ProcessEvents(void);


//
// D_Display
//  draw current display, possibly wiping it from the previous
//
extern void D_Display(void);


//
//  D_DoomLoop
//
extern void D_UpdateWipe(void);


extern void D_DoomLoop(void);


//
//  DEMO LOOP
//
int demosequence;
int pagetic;
char* pagename;


//
// D_PageTicker
// Handles timing for warped projection
//
extern void D_PageTicker(void);


//
// D_PageDrawer
//
extern void D_PageDrawer(void);

//
// D_AdvanceDemo
// Called after each demo or intro demosequence finishes
//
extern void D_AdvanceDemo(void);


//
// This cycles through the demo sequences.
// FIXME - version dependend demo numbers?
//
extern void D_DoAdvanceDemo(void);

//
// D_StartTitle
//
extern void D_StartTitle(void);


//
// D_AddFile
//
extern void D_AddFile(char* file);


//
// IdentifyVersion
// Checks availability of IWAD files by name,
// to determine whether registered/commercial features
// should be executed (notably loading PWAD's).
//
extern void IdentifyVersion(void);


//
// Find a Response File
//
extern void FindResponseFile(void);

//
// D_DoomMain
//
extern void D_DoomMain(void);
#define NCMD_EXIT       0x80000000
#define NCMD_RETRANSMIT 0x40000000
#define NCMD_SETUP      0x20000000
#define NCMD_KILL       0x10000000 // kill game
#define NCMD_CHECKSUM   0x0fffffff

#define RESENDCOUNT     10
#define PL_DRONE        0x80 // bit flag in doomdata->player


doomcom_t* doomcom;
doomdata_t* netbuffer; // points inside doomcom

ticcmd_t localcmds[BACKUPTICS];

ticcmd_t netcmds[MAXPLAYERS][BACKUPTICS];
int nettics[MAXNETNODES];
doom_boolean nodeingame[MAXNETNODES]; // set false as nodes leave game
doom_boolean remoteresend[MAXNETNODES]; // set when local needs tics
int resendto[MAXNETNODES]; // set when remote needs tics
int resendcount[MAXNETNODES];

int nodeforplayer[MAXPLAYERS];

int maketic;
int lastnettic;
int skiptics;
int ticdup;
int maxsend; // BACKUPTICS/(2*ticdup)-1

doom_boolean reboundpacket;
doomdata_t reboundstore;

char exitmsg[80];
int gametime;
int frametics[4];
int frameon;
int frameskip[4];
int oldnettics;


extern int viewangleoffset;
extern doom_boolean advancedemo;


void D_ProcessEvents(void);
void G_BuildTiccmd(ticcmd_t* cmd);
void D_DoAdvanceDemo(void);


//
//
//
extern int NetbufferSize(void);

//
// Checksum 
//
extern unsigned NetbufferChecksum(void);


//
//
//
extern int ExpandTics(int low);


//
// HSendPacket
//
extern void HSendPacket(int node, int flags);


//
// HGetPacket
// Returns false if no packet is waiting
//
extern doom_boolean HGetPacket(void);


//
// GetPackets
//
extern void GetPackets(void);


//
// NetUpdate
// Builds ticcmds for console player,
// sends out a packet
//
extern void NetUpdate(void);


//
// CheckAbort
//
extern void CheckAbort(void);


//
// D_ArbitrateNetStart
//
extern void D_ArbitrateNetStart(void);


//
// D_CheckNetGame
// Works out player numbers among the net participants
//
extern void D_CheckNetGame(void);


//
// D_QuitNetGame
// Called before quitting to leave a net game
// without hanging the other players
//
extern void D_QuitNetGame(void);


//
// TryRunTics
//
extern void TryRunTics(void);
GameMode_t gamemode = indetermined;
GameMission_t gamemission = doom;

// Language.
Language_t language = english;

// Set if homebrew PWAD stuff has been added.
doom_boolean modifiedgame;
char* doom1_endmsg[] =
{
    // DOOM1
    QUITMSG,
    "please don't leave, there's more\ndemons to toast!",
    "let's beat it -- this is turning\ninto a bloodbath!",
    "i wouldn't leave if i were you.\ndos is much worse.",
    "you're trying to say you like dos\nbetter than me, right?",
    "don't leave yet -- there's a\ndemon around that corner!",
    "ya know, next time you come in here\ni'm gonna toast ya.",
    "go ahead and leave. see if i care.",
};
char* doom2_endmsg[] = {
    // QuitDOOM II messages
    QUITMSG,
    "you want to quit?\nthen, thou hast lost an eighth!",
    "don't go now, there's a \ndimensional shambler waiting\nat the dos prompt!",
    "get outta here and go back\nto your boring programs.",
    "if i were your boss, i'd \n deathmatch ya in a minute!",
    "look, bud. you leave now\nand you forfeit your body count!",
    "just leave. when you come\nback, i'll be waiting with a bat.",
    "you're lucky i don't smack\nyou for thinking about leaving.",
};
#define TEXTSPEED 3
#define TEXTWAIT 250


typedef struct
{
    char* name;
    mobjtype_t type;
} castinfo_t;


// Stage of animation:
//  0 = text, 1 = art screen, 2 = character cast
int finalestage;

int finalecount;

char* e1text = E1TEXT;
char* e2text = E2TEXT;
char* e3text = E3TEXT;
char* e4text = E4TEXT;

char* c1text = C1TEXT;
char* c2text = C2TEXT;
char* c3text = C3TEXT;
char* c4text = C4TEXT;
char* c5text = C5TEXT;
char* c6text = C6TEXT;

char* p1text = P1TEXT;
char* p2text = P2TEXT;
char* p3text = P3TEXT;
char* p4text = P4TEXT;
char* p5text = P5TEXT;
char* p6text = P6TEXT;

char* t1text = T1TEXT;
char* t2text = T2TEXT;
char* t3text = T3TEXT;
char* t4text = T4TEXT;
char* t5text = T5TEXT;
char* t6text = T6TEXT;

char* finaletext;
char* finaleflat;

castinfo_t castorder[] = {
    {CC_ZOMBIE, MT_POSSESSED},
    {CC_SHOTGUN, MT_SHOTGUY},
    {CC_HEAVY, MT_CHAINGUY},
    {CC_IMP, MT_TROOP},
    {CC_DEMON, MT_SERGEANT},
    {CC_LOST, MT_SKULL},
    {CC_CACO, MT_HEAD},
    {CC_HELL, MT_KNIGHT},
    {CC_BARON, MT_BRUISER},
    {CC_ARACH, MT_BABY},
    {CC_PAIN, MT_PAIN},
    {CC_REVEN, MT_UNDEAD},
    {CC_MANCU, MT_FATSO},
    {CC_ARCH, MT_VILE},
    {CC_SPIDER, MT_SPIDER},
    {CC_CYBER, MT_CYBORG},
    {CC_HERO, MT_PLAYER},

    {0,0}
};

int castnum;
int casttics;
state_t* caststate;
doom_boolean castdeath;
int castframes;
int castonmelee;
doom_boolean castattacking;


//
// F_StartCast
//
extern gamestate_t wipegamestate;
extern patch_t* hu_font[HU_FONTSIZE];


void         F_StartCast(void);
void         F_CastTicker(void);
doom_boolean F_CastResponder(event_t* ev);
void         F_CastDrawer(void);
void         V_DrawPatchFlipped(int x, int y, int scrn, patch_t* patch);


//
// F_StartFinale
//
extern void F_StartFinale(void);


extern doom_boolean F_Responder(event_t* event);


//
// F_Ticker
//
extern void F_Ticker(void);


//
// F_TextWrite
//
extern void F_TextWrite(void);


//
// Final DOOM 2 animation
// Casting by id Software.
//   in order of appearance
//
extern void F_StartCast(void);


//
// F_CastTicker
//
extern void F_CastTicker(void);


//
// F_CastResponder
//
extern doom_boolean F_CastResponder(event_t* ev);


extern void F_CastPrint(char* text);


//
// F_CastDrawer
//
extern void F_CastDrawer(void);


//
// F_DrawPatchCol
//
extern void F_DrawPatchCol(int x, patch_t* patch, int col);

//
// F_BunnyScroll
//
extern void F_BunnyScroll(void);


//
// F_Drawer
//
extern void F_Drawer(void);
 doom_boolean go = 0;

 byte* wipe_scr_start;
 byte* wipe_scr_end;
 byte* wipe_scr;

 int* y;


extern void wipe_shittyColMajorXform(short* array, int width, int height);


extern int wipe_initColorXForm(int width, int height, int ticks);


extern int wipe_doColorXForm(int width, int height, int ticks);

extern int wipe_exitColorXForm(int width, int height, int ticks);

extern int wipe_initMelt(int width, int height, int ticks);


extern int wipe_doMelt(int width, int height, int ticks);

extern int wipe_exitMelt(int width, int height, int ticks);


extern int wipe_StartScreen(int x, int y, int width, int height);


extern int wipe_EndScreen(int x, int y, int width, int height);

extern int wipe_ScreenWipe(int wipeno, int x, int y, int width, int height, int ticks);
#define SAVEGAMESIZE    0x2c000
#define SAVESTRINGSIZE  24
#define MAXPLMOVE       (forwardmove[1])
#define TURBOTHRESHOLD  0x32
#define SLOWTURNTICS    6
#define NUMKEYS         256
#define BODYQUESIZE     32
#define VERSIONSIZE     16
#define DEMOMARKER      0x80


// Prototypes
doom_boolean G_CheckDemoStatus(void);
void G_ReadDemoTiccmd(ticcmd_t* cmd);
void G_WriteDemoTiccmd(ticcmd_t* cmd);
void G_PlayerReborn(int player);
void G_InitNew(skill_t skill, int episode, int map);
void G_DoReborn(int playernum);
void G_DoLoadLevel(void);
void G_DoNewGame(void);
void G_DoLoadGame(void);
void G_DoPlayDemo(void);
void G_DoCompleted(void);
void G_DoWorldDone(void);
void G_DoSaveGame(void);
void P_SpawnPlayer(mapthing_t* mthing);
void R_ExecuteSetViewSize(void);


gameaction_t gameaction;
gamestate_t gamestate;
skill_t gameskill;
doom_boolean respawnmonsters;
int gameepisode;
int gamemap;

doom_boolean paused;
doom_boolean sendpause; // send a pause event next tic 
doom_boolean sendsave; // send a save event next tic 
doom_boolean usergame; // ok to save / end game 

doom_boolean timingdemo; // if true, exit with report on completion 
doom_boolean nodrawers; // for comparative timing purposes 
doom_boolean noblit; // for comparative timing purposes 
int starttime; // for comparative timing purposes           

doom_boolean viewactive;

doom_boolean deathmatch; // only if started as net death 
doom_boolean netgame; // only true if packets are broadcast 
doom_boolean playeringame[MAXPLAYERS];
player_t players[MAXPLAYERS];

int consoleplayer; // player taking events and displaying 
int displayplayer; // view being displayed 
int gametic;
int levelstarttic; // gametic at level start 
int totalkills, totalitems, totalsecret; // for intermission 

char demoname[32];
doom_boolean demorecording;
doom_boolean demoplayback;
doom_boolean netdemo;
byte* demobuffer;
byte* demo_p;
byte* demoend;
doom_boolean singledemo; // quit after playing a demo from cmdline 

doom_boolean precache = true; // if true, load all graphics at start 

wbstartstruct_t wminfo; // parms for world map / intermission 

short consistancy[MAXPLAYERS][BACKUPTICS];

byte* savebuffer;

// 
// controls (have defaults) 
// 
int key_right;
int key_left;

int key_up;
int key_down;
int key_strafeleft;
int key_straferight;
int key_fire;
int key_use;
int key_strafe;
int key_speed;

int mousebfire;
int mousebstrafe;
int mousebforward;
int mousemove;

int joybfire;
int joybstrafe;
int joybuse;
int joybspeed;

fixed_t forwardmove[2] = { 0x19, 0x32 };
fixed_t sidemove[2] = { 0x18, 0x28 };
fixed_t angleturn[3] = { 640, 1280, 320 }; // + slow turn 

doom_boolean gamekeydown[NUMKEYS];
int turnheld; // for accelerative turning 

doom_boolean mousearray[4];
doom_boolean* mousebuttons = &mousearray[1]; // allow [-1]

// mouse values are used once 
int mousex;
int mousey;

int dclicktime;
int dclickstate;
int dclicks;
int dclicktime2;
int dclickstate2;
int dclicks2;

// joystick values are repeated 
int joyxmove;
int joyymove;
doom_boolean joyarray[5];
doom_boolean* joybuttons = &joyarray[1]; // allow [-1] 

int savegameslot;
char savedescription[32];

mobj_t* bodyque[BODYQUESIZE];
int bodyqueslot;

void* statcopy; // for statistics driver

// DOOM Par Times
int pars[4][10] =
{
    {0},
    {0,30,75,120,90,165,180,180,30,165},
    {0,90,90,90,120,90,360,240,30,170},
    {0,90,45,90,150,90,90,165,30,135}
};

// DOOM II Par Times
int cpars[32] =
{
    30,90,120,120,90,150,120,120,270,90,        //  1-10
    210,150,150,150,210,150,420,150,210,150,    // 11-20
    240,150,180,150,150,300,330,420,300,180,    // 21-30
    120,30                                      // 31-32
};

doom_boolean secretexit;

char savename[256];

skill_t d_skill;
int d_episode;
int d_map;

char* defdemoname;


extern gamestate_t wipegamestate;
extern char* pagename;
extern doom_boolean setsizeneeded;

// The sky texture to be used instead of the F_SKY1 dummy.
extern int skytexture;


//
// G_BuildTiccmd
// Builds a ticcmd from all of the available inputs
// or reads it from the demo buffer. 
// If recording a demo, write it out 
// 
extern void G_BuildTiccmd(ticcmd_t* cmd);


//
// G_DoLoadLevel 
//
extern void G_DoLoadLevel(void);

//
// G_Responder  
// Get info needed to make ticcmd_ts for the players.
// 
extern doom_boolean G_Responder(event_t* ev);


//
// G_Ticker
// Make ticcmd_ts for the players.
//
extern void G_Ticker(void);


//
// PLAYER STRUCTURE FUNCTIONS
// also see P_SpawnPlayer in P_Things
//

//
// G_InitPlayer 
// Called at the start.
// Called by the game initialization functions.
//
extern void G_InitPlayer(int player);


//
// G_PlayerFinishLevel
// Can when a player completes a level.
//
extern void G_PlayerFinishLevel(int player);


//
// G_PlayerReborn
// Called after a player dies 
// almost everything is cleared and initialized 
//
extern void G_PlayerReborn(int player);

//
// G_CheckSpot  
// Returns false if the player cannot be respawned
// at the given mapthing_t spot  
// because something is occupying it 
//

extern doom_boolean G_CheckSpot(int playernum, mapthing_t* mthing);


//
// G_DeathMatchSpawnPlayer 
// Spawns a player at one of the random death match spots 
// called at level load and each death 
//
extern void G_DeathMatchSpawnPlayer(int playernum);
//
// G_DoReborn 
// 
extern void G_DoReborn(int playernum);

void G_ScreenShot(void)
{
    gameaction = ga_screenshot;
}


//
// G_DoCompleted 
//
extern void G_ExitLevel(void);
// Here's for the german edition.
extern void G_SecretExitLevel(void);

extern void G_DoCompleted(void);


//
// G_WorldDone 
//
extern void G_WorldDone(void);
extern void G_DoWorldDone(void);



//
// G_InitFromSavegame
// Can be called by the startup code or the menu task. 
//

extern void G_LoadGame(char* name);


extern void G_DoLoadGame(void);


//
// G_SaveGame
// Called by the menu task.
// Description is a 24 byte text string 
//
extern void G_SaveGame(int slot, char* description);

extern void G_DoSaveGame(void);


//
// G_InitNew
// Can be called by the startup code or the menu task,
// consoleplayer, displayplayer, playeringame[] should be set. 
//

extern void G_DeferedInitNew(skill_t skill, int episode, int map);

extern void G_DoNewGame(void);
extern void G_InitNew(skill_t skill, int episode, int map);

//
// DEMO RECORDING 
// 

extern void G_ReadDemoTiccmd(ticcmd_t* cmd);


extern void G_WriteDemoTiccmd(ticcmd_t* cmd);


//
// G_RecordDemo 
// 
extern void G_RecordDemo(char* name);


extern void G_BeginRecording(void);

//
// G_PlayDemo 
//


extern void G_DeferedPlayDemo(char* name);

extern void G_DoPlayDemo(void);

//
// G_TimeDemo 
//
extern void G_TimeDemo(char* name);


/*
===================
=
= G_CheckDemoStatus
=
= Called after a death or level completion to allow demos to be cleaned up
= Returns true if a new demo loop action will take place
===================
*/

extern doom_boolean G_CheckDemoStatus(void);
#define noterased viewwindowx


extern doom_boolean        automapactive;        // in AM_map.c


void HUlib_init(void)
{
}


extern void HUlib_clearTextLine(hu_textline_t* t);


extern void HUlib_initTextLine(hu_textline_t* t, int x, int y, patch_t** f, int sc);


extern doom_boolean HUlib_addCharToTextLine(hu_textline_t* t, char ch);


extern doom_boolean HUlib_delCharFromTextLine(hu_textline_t* t);

extern void HUlib_drawTextLine(hu_textline_t* l, doom_boolean drawcursor);


// sorta called by HU_Erase and just better darn get things straight
extern void HUlib_eraseTextLine(hu_textline_t* l);


extern void HUlib_initSText(hu_stext_t* s,
                     int x,
                     int y,
                     int h,
                     patch_t** font,
                     int startchar,
                     doom_boolean* on);


extern void HUlib_addLineToSText(hu_stext_t* s);


extern void HUlib_addMessageToSText(hu_stext_t* s, char* prefix, char* msg);


extern void HUlib_drawSText(hu_stext_t* s);


extern void HUlib_eraseSText(hu_stext_t* s);


extern void HUlib_initIText(hu_itext_t* it,
                     int x,
                     int y,
                     patch_t** font,
                     int startchar,
                     doom_boolean* on);


// The following deletion routines adhere to the left margin restriction
extern void HUlib_delCharFromIText(hu_itext_t* it);


extern void HUlib_eraseLineFromIText(hu_itext_t* it);


// Resets left margin as well
extern void HUlib_resetIText(hu_itext_t* it);


extern void HUlib_addPrefixToIText(hu_itext_t* it, char* str);


// wrapper function for handling general keyed input.
// returns true if it ate the key
extern doom_boolean HUlib_keyInIText(hu_itext_t* it, unsigned char ch);


extern void HUlib_drawIText(hu_itext_t* it);

extern void HUlib_eraseIText(hu_itext_t* it);
#define HU_TITLE  (mapnames[(gameepisode-1)*9+gamemap-1])
#define HU_TITLE2 (mapnames2[gamemap-1])
#define HU_TITLEP (mapnamesp[gamemap-1])
#define HU_TITLET (mapnamest[gamemap-1])
#define HU_TITLEHEIGHT 1
#define HU_TITLEX 0
#define HU_TITLEY (167 - SHORT(hu_font[0]->height))
#define HU_INPUTTOGGLE 't'
#define HU_INPUTX HU_MSGX
#define HU_INPUTY (HU_MSGY + HU_MSGHEIGHT*(SHORT(hu_font[0]->height) +1))
#define HU_INPUTWIDTH 64
#define HU_INPUTHEIGHT 1
#define QUEUESIZE 128


 player_t* plr;
 hu_textline_t w_title;
 hu_itext_t w_chat;
 doom_boolean always_off = false;
 char chat_dest[MAXPLAYERS];
 hu_itext_t w_inputbuffer[MAXPLAYERS];
 doom_boolean message_on;
 doom_boolean message_nottobefuckedwith;
 hu_stext_t w_message;
 int message_counter;
 doom_boolean headsupactive = false;
 char chatchars[QUEUESIZE];
 int head = 0;
 int tail = 0;

char* chat_macros[] =
{
    HUSTR_CHATMACRO0,
    HUSTR_CHATMACRO1,
    HUSTR_CHATMACRO2,
    HUSTR_CHATMACRO3,
    HUSTR_CHATMACRO4,
    HUSTR_CHATMACRO5,
    HUSTR_CHATMACRO6,
    HUSTR_CHATMACRO7,
    HUSTR_CHATMACRO8,
    HUSTR_CHATMACRO9
};

char* player_names[] =
{
    HUSTR_PLRGREEN,
    HUSTR_PLRINDIGO,
    HUSTR_PLRBROWN,
    HUSTR_PLRRED
};

 char* shiftxform;

 char french_shiftxform[] =
{
    0,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31,
    ' ', '!', '"', '#', '$', '%', '&',
    '"', // shift-'
    '(', ')', '*', '+',
    '?', // shift-,
    '_', // shift--
    '>', // shift-.
    '?', // shift-/
    '0', // shift-0
    '1', // shift-1
    '2', // shift-2
    '3', // shift-3
    '4', // shift-4
    '5', // shift-5
    '6', // shift-6
    '7', // shift-7
    '8', // shift-8
    '9', // shift-9
    '/',
    '.', // shift-;
    '<',
    '+', // shift-=
    '>', '?', '@',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '[', // shift-[
    '!', // shift-backslash - OH MY GOD DOES WATCOM SUCK
    ']', // shift-]
    '"', '_',
    '\'', // shift-`
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '{', '|', '}', '~', 127

};

 char english_shiftxform[] =
{
    0,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31,
    ' ', '!', '"', '#', '$', '%', '&',
    '"', // shift-'
    '(', ')', '*', '+',
    '<', // shift-,
    '_', // shift--
    '>', // shift-.
    '?', // shift-/
    ')', // shift-0
    '!', // shift-1
    '@', // shift-2
    '#', // shift-3
    '$', // shift-4
    '%', // shift-5
    '^', // shift-6
    '&', // shift-7
    '*', // shift-8
    '(', // shift-9
    ':',
    ':', // shift-;
    '<',
    '+', // shift-=
    '>', '?', '@',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '[', // shift-[
    '!', // shift-backslash - OH MY GOD DOES WATCOM SUCK
    ']', // shift-]
    '"', '_',
    '\'', // shift-`
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '{', '|', '}', '~', 127
};

char frenchKeyMap[128] =
{
    0,
    1,2,3,4,5,6,7,8,9,10,
    11,12,13,14,15,16,17,18,19,20,
    21,22,23,24,25,26,27,28,29,30,
    31,
    ' ','!','"','#','$','%','&','%','(',')','*','+',';','-',':','!',
    '0','1','2','3','4','5','6','7','8','9',':','M','<','=','>','?',
    '@','Q','B','C','D','E','F','G','H','I','J','K','L',',','N','O',
    'P','A','R','S','T','U','V','Z','X','Y','W','^','\\','$','^','_',
    '@','Q','B','C','D','E','F','G','H','I','J','K','L',',','N','O',
    'P','A','R','S','T','U','V','Z','X','Y','W','^','\\','$','^',127
};

char chat_char; // remove later.
patch_t* hu_font[HU_FONTSIZE];
doom_boolean chat_on;
doom_boolean message_dontfuckwithme;

extern int showMessages;
extern doom_boolean automapactive;


//
// Builtin map names.
// The actual names can be found in DStrings.h.
//

char* mapnames[] = // DOOM shareware/registered/retail (Ultimate) names.
{

    HUSTR_E1M1,
    HUSTR_E1M2,
    HUSTR_E1M3,
    HUSTR_E1M4,
    HUSTR_E1M5,
    HUSTR_E1M6,
    HUSTR_E1M7,
    HUSTR_E1M8,
    HUSTR_E1M9,

    HUSTR_E2M1,
    HUSTR_E2M2,
    HUSTR_E2M3,
    HUSTR_E2M4,
    HUSTR_E2M5,
    HUSTR_E2M6,
    HUSTR_E2M7,
    HUSTR_E2M8,
    HUSTR_E2M9,

    HUSTR_E3M1,
    HUSTR_E3M2,
    HUSTR_E3M3,
    HUSTR_E3M4,
    HUSTR_E3M5,
    HUSTR_E3M6,
    HUSTR_E3M7,
    HUSTR_E3M8,
    HUSTR_E3M9,

    HUSTR_E4M1,
    HUSTR_E4M2,
    HUSTR_E4M3,
    HUSTR_E4M4,
    HUSTR_E4M5,
    HUSTR_E4M6,
    HUSTR_E4M7,
    HUSTR_E4M8,
    HUSTR_E4M9,

    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL"
};

char* mapnames2[] = // DOOM 2 map names.
{
    HUSTR_1,
    HUSTR_2,
    HUSTR_3,
    HUSTR_4,
    HUSTR_5,
    HUSTR_6,
    HUSTR_7,
    HUSTR_8,
    HUSTR_9,
    HUSTR_10,
    HUSTR_11,

    HUSTR_12,
    HUSTR_13,
    HUSTR_14,
    HUSTR_15,
    HUSTR_16,
    HUSTR_17,
    HUSTR_18,
    HUSTR_19,
    HUSTR_20,

    HUSTR_21,
    HUSTR_22,
    HUSTR_23,
    HUSTR_24,
    HUSTR_25,
    HUSTR_26,
    HUSTR_27,
    HUSTR_28,
    HUSTR_29,
    HUSTR_30,
    HUSTR_31,
    HUSTR_32
};


char* mapnamesp[] = // Plutonia WAD map names.
{
    PHUSTR_1,
    PHUSTR_2,
    PHUSTR_3,
    PHUSTR_4,
    PHUSTR_5,
    PHUSTR_6,
    PHUSTR_7,
    PHUSTR_8,
    PHUSTR_9,
    PHUSTR_10,
    PHUSTR_11,

    PHUSTR_12,
    PHUSTR_13,
    PHUSTR_14,
    PHUSTR_15,
    PHUSTR_16,
    PHUSTR_17,
    PHUSTR_18,
    PHUSTR_19,
    PHUSTR_20,

    PHUSTR_21,
    PHUSTR_22,
    PHUSTR_23,
    PHUSTR_24,
    PHUSTR_25,
    PHUSTR_26,
    PHUSTR_27,
    PHUSTR_28,
    PHUSTR_29,
    PHUSTR_30,
    PHUSTR_31,
    PHUSTR_32
};


char* mapnamest[] = // TNT WAD map names.
{
    THUSTR_1,
    THUSTR_2,
    THUSTR_3,
    THUSTR_4,
    THUSTR_5,
    THUSTR_6,
    THUSTR_7,
    THUSTR_8,
    THUSTR_9,
    THUSTR_10,
    THUSTR_11,

    THUSTR_12,
    THUSTR_13,
    THUSTR_14,
    THUSTR_15,
    THUSTR_16,
    THUSTR_17,
    THUSTR_18,
    THUSTR_19,
    THUSTR_20,

    THUSTR_21,
    THUSTR_22,
    THUSTR_23,
    THUSTR_24,
    THUSTR_25,
    THUSTR_26,
    THUSTR_27,
    THUSTR_28,
    THUSTR_29,
    THUSTR_30,
    THUSTR_31,
    THUSTR_32
};

extern char ForeignTranslation(unsigned char ch);

extern void HU_Init(void);

extern void HU_Stop(void);

extern void HU_Start(void);

extern void HU_Drawer(void);

extern void HU_Erase(void);

extern void HU_Ticker(void);

extern void HU_queueChatChar(char c);

extern char HU_dequeueChatChar(void);

extern doom_boolean HU_Responder(event_t* ev);
#if defined(I_NET_ENABLED)
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif
//#include "doom_config.h"

#if defined(I_NET_ENABLED)
#if defined(DOOM_WIN32)
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include <WinSock2.h>
//#include <winsock.h>
#define IPPORT_USERRESERVED 5000
#pragma comment(lib, "ws2_32.lib")
#else
 //#include <sys/socket.h>
 //#include <netinet/in.h>
 //#include <arpa/inet.h>
 //#include <sys/ioctl.h>
#define SOCKET int
#endif
#else
#define IPPORT_USERRESERVED 5000
#endif

//#include "i_system.h"
//#include "d_event.h"
//#include "d_net.h"
//#include "m_argv.h"
//#include "doomstat.h"
//#include "i_net.h"


// For some odd reason...
#if !defined(DOOM_APPLE) // It doesn't complain on Win32? O_o
#define ntohl(x) \
        ((unsigned long int)((((unsigned long int)(x) & 0x000000ffU) << 24) | \
                             (((unsigned long int)(x) & 0x0000ff00U) <<  8) | \
                             (((unsigned long int)(x) & 0x00ff0000U) >>  8) | \
                             (((unsigned long int)(x) & 0xff000000U) >> 24)))

#define ntohs(x) \
        ((unsigned short int)((((unsigned short int)(x) & 0x00ff) << 8) | \
                              (((unsigned short int)(x) & 0xff00) >> 8))) \

#define htonl(x) ntohl(x)
#define htons(x) ntohs(x)
#endif


//
// NETWORKING
//

extern int doomport = (IPPORT_USERRESERVED + 0x1d);
extern int doomport_send = (IPPORT_USERRESERVED + 0x1e);

#if defined(I_NET_ENABLED)
SOCKET sendsocket;
SOCKET insocket;

struct sockaddr_in sendaddress[MAXNETNODES];
#endif

void (*netget) (void);
void (*netsend) (void);


void NetSend(void);
doom_boolean NetListen(void);


//
// UDPsocket
//
#if defined(I_NET_ENABLED)
SOCKET UDPsocket(void)
{
    SOCKET s;

    // allocate a socket
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0)
    {
        //I_Error("Error: can't create socket: %s", strerror(errno));
        
        doom_strcpy(error_buf, "Error: can't create socket: ");
        doom_concat(error_buf, strerror(errno));
        I_Error(error_buf);
    }

    return s;
}
#endif


//
// BindToLocalPort
//
#if defined(I_NET_ENABLED)
void BindToLocalPort(SOCKET s, int port)
{
    int v;
    struct sockaddr_in address;

    doom_memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = port;

    v = bind(s, (void*)&address, sizeof(address));
    if (v == -1)
    {
        //I_Error("Error: BindToPort: bind: %s", strerror(errno));
        
        doom_strcpy(error_buf, "Error: BindToPort: bind: ");
        doom_concat(error_buf, strerror(errno));
        I_Error(error_buf);
    }
}
#endif


//
// PacketSend
//
void PacketSend(void)
{
#if defined(I_NET_ENABLED)
    int c;
    doomdata_t sw;

    // byte swap
    sw.checksum = htonl(netbuffer->checksum);
    sw.player = netbuffer->player;
    sw.retransmitfrom = netbuffer->retransmitfrom;
    sw.starttic = netbuffer->starttic;
    sw.numtics = netbuffer->numtics;
    for (c = 0; c < netbuffer->numtics; c++)
    {
        sw.cmds[c].forwardmove = netbuffer->cmds[c].forwardmove;
        sw.cmds[c].sidemove = netbuffer->cmds[c].sidemove;
        sw.cmds[c].angleturn = htons(netbuffer->cmds[c].angleturn);
        sw.cmds[c].consistancy = htons(netbuffer->cmds[c].consistancy);
        sw.cmds[c].chatchar = netbuffer->cmds[c].chatchar;
        sw.cmds[c].buttons = netbuffer->cmds[c].buttons;
    }

    //doom_print ("sending %i\n",gametic);                
    c = sendto(sendsocket, (const char*)&sw, doomcom->datalength
               , 0, (void*)&sendaddress[doomcom->remotenode]
               , sizeof(sendaddress[doomcom->remotenode]));
#endif
}


//
// PacketGet
//
void PacketGet(void)
{
#if defined(I_NET_ENABLED)
    int i;
    int c;
    struct sockaddr_in fromaddress;
#if defined(__APPLE__)
    socklen_t fromlen;
#else
    int fromlen;
#endif
    doomdata_t sw;

    fromlen = sizeof(fromaddress);
    c = recvfrom(insocket, (char*)&sw, sizeof(sw), 0
                 , (struct sockaddr*)&fromaddress, &fromlen);
    if (c == -1)
    {
#if defined(DOOM_WIN32)
        int r = WSAGetLastError();
        if (r != WSAEWOULDBLOCK)
        {
            //I_Error("Error: GetPacket: %i", r);
            
            doom_strcpy(error_buf, "Error: GetPacket: ");
            doom_concat(error_buf, doom_itoa(r, 10));
            I_Error(error_buf);
        }
#else
        if (errno != EWOULDBLOCK)
        {
            //I_Error("Error: GetPacket: %s", strerror(errno));
            
            doom_strcpy(error_buf, "Error: GetPacket: ");
            doom_concat(error_buf, strerror(errno));
            I_Error(error_buf);
        }
#endif
        doomcom->remotenode = -1;                // no packet
        return;
    }

    {
        static int first = 1;
        if (first)
        {
            //doom_print("len=%d:p=[0x%x 0x%x] \n", c, *(int*)&sw, *((int*)&sw + 1));
            doom_print("len=");
            doom_print(doom_itoa(c, 10));
            doom_print(":p=[0x");
            doom_print(doom_itoa(*(int*)&sw, 16));
            doom_print(" 0x");
            doom_print(doom_itoa(*((int*)&sw + 1), 16));
            doom_print("] \n");
        }
        first = 0;
    }

    // find remote node number
    for (i = 0; i < doomcom->numnodes; i++)
        if (fromaddress.sin_addr.s_addr == sendaddress[i].sin_addr.s_addr)
            break;

    if (i == doomcom->numnodes)
    {
        // packet is not from one of the players (new game broadcast)
        doomcom->remotenode = -1; // no packet
        return;
    }

    doomcom->remotenode = i; // good packet from a game player
    doomcom->datalength = c;

    // byte swap
    netbuffer->checksum = ntohl(sw.checksum);
    netbuffer->player = sw.player;
    netbuffer->retransmitfrom = sw.retransmitfrom;
    netbuffer->starttic = sw.starttic;
    netbuffer->numtics = sw.numtics;

    for (c = 0; c < netbuffer->numtics; c++)
    {
        netbuffer->cmds[c].forwardmove = sw.cmds[c].forwardmove;
        netbuffer->cmds[c].sidemove = sw.cmds[c].sidemove;
        netbuffer->cmds[c].angleturn = ntohs(sw.cmds[c].angleturn);
        netbuffer->cmds[c].consistancy = ntohs(sw.cmds[c].consistancy);
        netbuffer->cmds[c].chatchar = sw.cmds[c].chatchar;
        netbuffer->cmds[c].buttons = sw.cmds[c].buttons;
    }
#endif
}


int GetLocalAddress(void)
{
#if defined(I_NET_ENABLED)
    char hostname[1024];
    struct hostent* hostentry; // host information entry
    int v;

    // get local address
    v = gethostname(hostname, sizeof(hostname));
    if (v == -1)
    {
        //I_Error("Error: GetLocalAddress : gethostname: errno %d", errno);
        
        doom_strcpy(error_buf, "Error: GetLocalAddress : gethostname: errno ");
        doom_concat(error_buf, strerror(errno));
        I_Error(error_buf);
    }

    hostentry = gethostbyname(hostname);
    if (!hostentry)
    {
        I_Error("Error: GetLocalAddress : gethostbyname: couldn't get local host");
    }

    return *(int*)hostentry->h_addr_list[0];
#else
    return 0;
#endif
}


//
// I_InitNetwork
//
extern void I_InitNetwork(void);



extern void I_NetCmd(void);
#define SAMPLECOUNT 512
#define NUM_CHANNELS 8
// It is 2 for 16bit, and 2 for two channels.
#define BUFMUL 4
#define MIXBUFFERSIZE (SAMPLECOUNT*BUFMUL)

#define SAMPLERATE 11025 // Hz
#define SAMPLESIZE 2 // 16bit

#define MAX_QUEUED_MIDI_MSGS 256

#define EVENT_RELEASE_NOTE 0
#define EVENT_PLAY_NOTE 1
#define EVENT_PITCH_BEND 2
#define EVENT_SYSTEM_EVENT 3
#define EVENT_CONTROLLER 4
#define EVENT_END_OF_MEASURE 5
#define EVENT_FINISH 6
#define EVENT_UNUSED 7

#define CONTROLLER_EVENT_ALL_SOUNDS_OFF 10
#define CONTROLLER_EVENT_ALL_NOTES_OFF 11
#define CONTROLLER_EVENT_MONO 12
#define CONTROLLER_EVENT_POLY 13
#define CONTROLLER_EVENT_RESET_ALL_CONTROLLERS 14
#define CONTROLLER_EVENT_EVENT 15

#define CONTROLLER_CHANGE_INSTRUMENT 0
#define CONTROLLER_BANK_SELECT 1
#define CONTROLLER_MODULATION 2
#define CONTROLLER_VOLUME 3
#define CONTROLLER_PAN 4
#define CONTROLLER_EXPRESSION 5
#define CONTROLLER_REVERB 6
#define CONTROLLER_CHORUS 7
#define CONTROLLER_SUSTAIN 8
#define CONTROLLER_SOFT 9


typedef struct
{
    char ID[4];
    unsigned short scoreLen;
    unsigned short scoreStart;
    unsigned short channels;
    unsigned short sec_channels;
    unsigned short instrCnt;
    unsigned short dummy;
} mus_header_t;


// A quick hack to establish a protocol between
// synchronous mix buffer updates and asynchronous
// audio writes. Probably redundant with gametic.
int flag = 0;

 unsigned char* mus_data = 0;
 mus_header_t mus_header;
 int mus_offset = 0;
 int mus_delay = 0;
 doom_boolean mus_loop = false;
 doom_boolean mus_playing = false;
 int mus_volume = 127;
 int mus_channel_volumes[16] = { 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };

 int looping = 0;
 int musicdies = -1;


// The number of internal mixing channels,
//  the samples calculated for each mixing step,
//  the size of the 16bit, 2 hardware channel (stereo)
//  mixing buffer, and the samplerate of the raw data.

// The actual lengths of all sound effects.
int lengths[NUMSFX];

// The actual output device.
int audio_fd;

// The global mixing buffer.
// Basically, samples from all active internal channels
//  are modifed and added, and stored in the buffer
//  that is submitted to the audio device.
signed short mixbuffer[MIXBUFFERSIZE];


// The channel step amount...
unsigned int channelstep[NUM_CHANNELS];
// ... and a 0.16 bit remainder of last step.
unsigned int channelstepremainder[NUM_CHANNELS];

// The channel data pointers, start and end.
unsigned char* channels[NUM_CHANNELS];
unsigned char* channelsend[NUM_CHANNELS];

// Time/gametic that the channel started playing,
//  used to determine oldest, which automatically
//  has lowest priority.
// In case number of active sounds exceeds
//  available channels.
int channelstart[NUM_CHANNELS];

// The sound in channel handles,
//  determined on registration,
//  might be used to unregister/stop/modify,
//  currently unused.
int channelhandles[NUM_CHANNELS];

// SFX id of the playing sound effect.
// Used to catch duplicates (like chainsaw).
int channelids[NUM_CHANNELS];

// Pitch to stepping lookup, unused.
int steptable[256];

// Volume lookups.
int vol_lookup[128 * 256];

// Hardware left and right channel volume lookup.
int* channelleftvol_lookup[NUM_CHANNELS];
int* channelrightvol_lookup[NUM_CHANNELS];

unsigned long queued_midi_msgs[MAX_QUEUED_MIDI_MSGS];
int queue_midi_head = 0;
int queue_midi_tail = 0;


void TickSong();


//
// This function loads the sound data from the WAD lump,
//  for single sound.
//
extern void* getsfx(char* sfxname, int* len);


//
// This function adds a sound to the
//  list of currently active sounds,
//  which is maintained as a given number
//  (eight, usually) of internal channels.
// Returns a handle.
//
extern int addsfx(int sfxid, int volume, int step, int seperation);


//
// SFX API
// Note: this was called by S_Init.
// However, whatever they did in the
// old DPMS based DOS version, this
// were simply dummies in the Linux
// version.
// See soundserver initdata().
//
extern void I_SetChannels();


extern void I_SetSfxVolume(int volume);


// MUSIC API - dummy. Some code from DOS version.
extern void I_SetMusicVolume(int volume);

//
// Retrieve the raw data lump index
//  for a given SFX name.
//
extern int I_GetSfxLumpNum(sfxinfo_t* sfx);


//
// Starting a sound means adding it
//  to the current list of active sounds
//  in the internal channels.
// As the SFX info struct contains
//  e.g. a pointer to the raw data,
//  it is ignored.
// As our sound handling does not handle
//  priority, it is ignored.
// Pitching (that is, increased speed of playback)
//  is set, but currently not used by mixing.
//
extern int I_StartSound(int id, int vol, int sep, int pitch, int priority);

extern void I_StopSound(int handle);


extern int I_SoundIsPlaying(int handle);


//
// This function loops all active (internal) sound
//  channels, retrieves a given number of samples
//  from the raw sound data, modifies it according
//  to the current (internal) channel parameters,
//  mixes the per channel samples into the global
//  mixbuffer, clamping it to the allowed range,
//  and sets up everything for transferring the
//  contents of the mixbuffer to the (two)
//  hardware channels (left and right, that is).
//
// This function currently supports only 16bit.
//
extern void I_UpdateSound(void);

//extern doom_sound_callbacks_t doom_sound_callbacks;
//extern doom_boolean skip_next_sound_update;

// 
// This would be used to write out the mixbuffer
//  during each game loop update.
// Updates sound buffer and audio device at runtime. 
// It is called during Timer interrupt with SNDINTR.
// Mixing now done synchronous, and
//  only output be done asynchronous?
//
extern void I_SubmitSound(void);


extern void I_UpdateSoundParams(int handle, int vol, int sep, int pitch);


extern void I_ShutdownSound(void);


extern void I_InitSound();


//
// MUSIC API.
//
extern void I_InitMusic(void);


extern void I_ShutdownMusic(void);


extern void I_PlaySong(int handle, int looping);


extern void I_PauseSong(int handle);


extern void I_ResumeSong(int handle);


extern void reset_all_channels();
extern void I_StopSong(int handle);


extern void I_UnRegisterSong(int handle);


extern int I_RegisterSong(void* data);


// Is the song playing?
extern int I_QrySongPlaying(int handle);


extern unsigned long I_TickSong();
int mb_used = 6 * (sizeof(void*) / 4);
ticcmd_t emptycmd;


extern doom_boolean demorecording;


extern void I_Tactile(int on, int off, int total);


extern ticcmd_t* I_BaseTiccmd(void);


extern int I_GetHeapSize(void);


extern byte* I_ZoneBase(int* size);


//
// I_GetTime
// returns time in 1/70th second tics
//
extern int I_GetTime(void);


//
// I_Init
//
extern void I_Init(void);


//
// I_Quit
//
extern void I_Quit(void);


extern void I_WaitVBL(int count);


extern byte* I_AllocLow(int length);


//
// I_Error
//
extern void I_Error(char* error);
#define POINTER_WARP_COUNTDOWN 1


// Fake mouse handling.
// This cannot work properly w/o DGA.
// Needs an invisible mouse cursor at least.
doom_boolean grabMouse;
int doPointerWarp = POINTER_WARP_COUNTDOWN;

unsigned char screen_palette[256 * 3];

doom_boolean mousemoved = false;
doom_boolean shmFinished;


// Blocky mode,
// replace each 320x200 pixel with multiply*multiply pixels.
// According to Dave Taylor, it still is a bonehead thing
// to use ....
static int multiply = 1;
static int lastmousex = 0;
static int lastmousey = 0;


extern void I_ShutdownGraphics(void);


//
// I_StartFrame
//
extern void I_StartFrame(void);


//
// I_StartTic
//
extern void I_StartTic(void);


//
// I_UpdateNoBlit
//
extern void I_UpdateNoBlit(void);


//
// I_FinishUpdate
//
extern void I_FinishUpdate(void);


//
// I_ReadScreen
//
extern void I_ReadScreen(byte* scr);


//
// I_SetPalette
//
extern void I_SetPalette(byte* palette);


void I_InitGraphics(void)
{
    screens[0] = (unsigned char*)doom_malloc(SCREENWIDTH * SCREENHEIGHT);
}
char** sprnames;


void A_Light0();
void A_WeaponReady();
void A_Lower();
void A_Raise();
void A_Punch();
void A_ReFire();
void A_FirePistol();
void A_Light1();
void A_FireShotgun();
void A_Light2();
void A_FireShotgun2();
void A_CheckReload();
void A_OpenShotgun2();
void A_LoadShotgun2();
void A_CloseShotgun2();
void A_FireCGun();
void A_GunFlash();
void A_FireMissile();
void A_Saw();
void A_FirePlasma();
void A_BFGsound();
void A_FireBFG();
void A_BFGSpray();
void A_Explode();
void A_Pain();
void A_PlayerScream();
void A_Fall();
void A_XScream();
void A_Look();
void A_Chase();
void A_FaceTarget();
void A_PosAttack();
void A_Scream();
void A_SPosAttack();
void A_VileChase();
void A_VileStart();
void A_VileTarget();
void A_VileAttack();
void A_StartFire();
void A_Fire();
void A_FireCrackle();
void A_Tracer();
void A_SkelWhoosh();
void A_SkelFist();
void A_SkelMissile();
void A_FatRaise();
void A_FatAttack1();
void A_FatAttack2();
void A_FatAttack3();
void A_BossDeath();
void A_CPosAttack();
void A_CPosRefire();
void A_TroopAttack();
void A_SargAttack();
void A_HeadAttack();
void A_BruisAttack();
void A_SkullAttack();
void A_Metal();
void A_SpidRefire();
void A_BabyMetal();
void A_BspiAttack();
void A_Hoof();
void A_CyberAttack();
void A_PainAttack();
void A_PainDie();
void A_KeenDie();
void A_BrainPain();
void A_BrainScream();
void A_BrainDie();
void A_BrainAwake();
void A_BrainSpit();
void A_SpawnSound();
void A_SpawnFly();
void A_BrainExplode();


//state_t states[NUMSTATES];
state_t* states;

mobjinfo_t mobjinfo[NUMMOBJTYPES] = {

    { // MT_PLAYER
        -1, // doomednum
        S_PLAY, // spawnstate
        100, // spawnhealth
        S_PLAY_RUN1, // seestate
        sfx_None, // seesound
        0, // reactiontime
        sfx_None, // attacksound
        S_PLAY_PAIN, // painstate
        255, // painchance
        sfx_plpain, // painsound
        S_NULL, // meleestate
        S_PLAY_ATK1, // missilestate
        S_PLAY_DIE1, // deathstate
        S_PLAY_XDIE1, // xdeathstate
        sfx_pldeth, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_DROPOFF | MF_PICKUP | MF_NOTDMATCH, // flags
        S_NULL                // raisestate
    },

    { // MT_POSSESSED
        3004, // doomednum
        S_POSS_STND, // spawnstate
        20, // spawnhealth
        S_POSS_RUN1, // seestate
        sfx_posit1, // seesound
        8, // reactiontime
        sfx_pistol, // attacksound
        S_POSS_PAIN, // painstate
        200, // painchance
        sfx_popain, // painsound
        0, // meleestate
        S_POSS_ATK1, // missilestate
        S_POSS_DIE1, // deathstate
        S_POSS_XDIE1, // xdeathstate
        sfx_podth1, // deathsound
        8, // speed
        20 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_posact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_POSS_RAISE1                // raisestate
    },

    { // MT_SHOTGUY
        9, // doomednum
        S_SPOS_STND, // spawnstate
        30, // spawnhealth
        S_SPOS_RUN1, // seestate
        sfx_posit2, // seesound
        8, // reactiontime
        0, // attacksound
        S_SPOS_PAIN, // painstate
        170, // painchance
        sfx_popain, // painsound
        0, // meleestate
        S_SPOS_ATK1, // missilestate
        S_SPOS_DIE1, // deathstate
        S_SPOS_XDIE1, // xdeathstate
        sfx_podth2, // deathsound
        8, // speed
        20 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_posact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_SPOS_RAISE1                // raisestate
    },

    { // MT_VILE
        64, // doomednum
        S_VILE_STND, // spawnstate
        700, // spawnhealth
        S_VILE_RUN1, // seestate
        sfx_vilsit, // seesound
        8, // reactiontime
        0, // attacksound
        S_VILE_PAIN, // painstate
        10, // painchance
        sfx_vipain, // painsound
        0, // meleestate
        S_VILE_ATK1, // missilestate
        S_VILE_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_vildth, // deathsound
        15, // speed
        20 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        500, // mass
        0, // damage
        sfx_vilact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_NULL                // raisestate
    },

    { // MT_FIRE
        -1, // doomednum
        S_FIRE1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_UNDEAD
        66, // doomednum
        S_SKEL_STND, // spawnstate
        300, // spawnhealth
        S_SKEL_RUN1, // seestate
        sfx_skesit, // seesound
        8, // reactiontime
        0, // attacksound
        S_SKEL_PAIN, // painstate
        100, // painchance
        sfx_popain, // painsound
        S_SKEL_FIST1, // meleestate
        S_SKEL_MISS1, // missilestate
        S_SKEL_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_skedth, // deathsound
        10, // speed
        20 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        500, // mass
        0, // damage
        sfx_skeact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_SKEL_RAISE1                // raisestate
    },

    { // MT_TRACER
        -1, // doomednum
        S_TRACER, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_skeatk, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_TRACEEXP1, // deathstate
        S_NULL, // xdeathstate
        sfx_barexp, // deathsound
        10 * FRACUNIT, // speed
        11 * FRACUNIT, // radius
        8 * FRACUNIT, // height
        100, // mass
        10, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_SMOKE
        -1, // doomednum
        S_SMOKE1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_FATSO
        67, // doomednum
        S_FATT_STND, // spawnstate
        600, // spawnhealth
        S_FATT_RUN1, // seestate
        sfx_mansit, // seesound
        8, // reactiontime
        0, // attacksound
        S_FATT_PAIN, // painstate
        80, // painchance
        sfx_mnpain, // painsound
        0, // meleestate
        S_FATT_ATK1, // missilestate
        S_FATT_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_mandth, // deathsound
        8, // speed
        48 * FRACUNIT, // radius
        64 * FRACUNIT, // height
        1000, // mass
        0, // damage
        sfx_posact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_FATT_RAISE1                // raisestate
    },

    { // MT_FATSHOT
        -1, // doomednum
        S_FATSHOT1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_firsht, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_FATSHOTX1, // deathstate
        S_NULL, // xdeathstate
        sfx_firxpl, // deathsound
        20 * FRACUNIT, // speed
        6 * FRACUNIT, // radius
        8 * FRACUNIT, // height
        100, // mass
        8, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_CHAINGUY
        65, // doomednum
        S_CPOS_STND, // spawnstate
        70, // spawnhealth
        S_CPOS_RUN1, // seestate
        sfx_posit2, // seesound
        8, // reactiontime
        0, // attacksound
        S_CPOS_PAIN, // painstate
        170, // painchance
        sfx_popain, // painsound
        0, // meleestate
        S_CPOS_ATK1, // missilestate
        S_CPOS_DIE1, // deathstate
        S_CPOS_XDIE1, // xdeathstate
        sfx_podth2, // deathsound
        8, // speed
        20 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_posact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_CPOS_RAISE1                // raisestate
    },

    { // MT_TROOP
        3001, // doomednum
        S_TROO_STND, // spawnstate
        60, // spawnhealth
        S_TROO_RUN1, // seestate
        sfx_bgsit1, // seesound
        8, // reactiontime
        0, // attacksound
        S_TROO_PAIN, // painstate
        200, // painchance
        sfx_popain, // painsound
        S_TROO_ATK1, // meleestate
        S_TROO_ATK1, // missilestate
        S_TROO_DIE1, // deathstate
        S_TROO_XDIE1, // xdeathstate
        sfx_bgdth1, // deathsound
        8, // speed
        20 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_bgact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_TROO_RAISE1                // raisestate
    },

    { // MT_SERGEANT
        3002, // doomednum
        S_SARG_STND, // spawnstate
        150, // spawnhealth
        S_SARG_RUN1, // seestate
        sfx_sgtsit, // seesound
        8, // reactiontime
        sfx_sgtatk, // attacksound
        S_SARG_PAIN, // painstate
        180, // painchance
        sfx_dmpain, // painsound
        S_SARG_ATK1, // meleestate
        0, // missilestate
        S_SARG_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_sgtdth, // deathsound
        10, // speed
        30 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        400, // mass
        0, // damage
        sfx_dmact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_SARG_RAISE1                // raisestate
    },

    { // MT_SHADOWS
        58, // doomednum
        S_SARG_STND, // spawnstate
        150, // spawnhealth
        S_SARG_RUN1, // seestate
        sfx_sgtsit, // seesound
        8, // reactiontime
        sfx_sgtatk, // attacksound
        S_SARG_PAIN, // painstate
        180, // painchance
        sfx_dmpain, // painsound
        S_SARG_ATK1, // meleestate
        0, // missilestate
        S_SARG_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_sgtdth, // deathsound
        10, // speed
        30 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        400, // mass
        0, // damage
        sfx_dmact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_SHADOW | MF_COUNTKILL, // flags
        S_SARG_RAISE1                // raisestate
    },

    { // MT_HEAD
        3005, // doomednum
        S_HEAD_STND, // spawnstate
        400, // spawnhealth
        S_HEAD_RUN1, // seestate
        sfx_cacsit, // seesound
        8, // reactiontime
        0, // attacksound
        S_HEAD_PAIN, // painstate
        128, // painchance
        sfx_dmpain, // painsound
        0, // meleestate
        S_HEAD_ATK1, // missilestate
        S_HEAD_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_cacdth, // deathsound
        8, // speed
        31 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        400, // mass
        0, // damage
        sfx_dmact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_FLOAT | MF_NOGRAVITY | MF_COUNTKILL, // flags
        S_HEAD_RAISE1                // raisestate
    },

    { // MT_BRUISER
        3003, // doomednum
        S_BOSS_STND, // spawnstate
        1000, // spawnhealth
        S_BOSS_RUN1, // seestate
        sfx_brssit, // seesound
        8, // reactiontime
        0, // attacksound
        S_BOSS_PAIN, // painstate
        50, // painchance
        sfx_dmpain, // painsound
        S_BOSS_ATK1, // meleestate
        S_BOSS_ATK1, // missilestate
        S_BOSS_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_brsdth, // deathsound
        8, // speed
        24 * FRACUNIT, // radius
        64 * FRACUNIT, // height
        1000, // mass
        0, // damage
        sfx_dmact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_BOSS_RAISE1                // raisestate
    },

    { // MT_BRUISERSHOT
        -1, // doomednum
        S_BRBALL1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_firsht, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_BRBALLX1, // deathstate
        S_NULL, // xdeathstate
        sfx_firxpl, // deathsound
        15 * FRACUNIT, // speed
        6 * FRACUNIT, // radius
        8 * FRACUNIT, // height
        100, // mass
        8, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_KNIGHT
        69, // doomednum
        S_BOS2_STND, // spawnstate
        500, // spawnhealth
        S_BOS2_RUN1, // seestate
        sfx_kntsit, // seesound
        8, // reactiontime
        0, // attacksound
        S_BOS2_PAIN, // painstate
        50, // painchance
        sfx_dmpain, // painsound
        S_BOS2_ATK1, // meleestate
        S_BOS2_ATK1, // missilestate
        S_BOS2_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_kntdth, // deathsound
        8, // speed
        24 * FRACUNIT, // radius
        64 * FRACUNIT, // height
        1000, // mass
        0, // damage
        sfx_dmact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_BOS2_RAISE1                // raisestate
    },

    { // MT_SKULL
        3006, // doomednum
        S_SKULL_STND, // spawnstate
        100, // spawnhealth
        S_SKULL_RUN1, // seestate
        0, // seesound
        8, // reactiontime
        sfx_sklatk, // attacksound
        S_SKULL_PAIN, // painstate
        256, // painchance
        sfx_dmpain, // painsound
        0, // meleestate
        S_SKULL_ATK1, // missilestate
        S_SKULL_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_firxpl, // deathsound
        8, // speed
        16 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        50, // mass
        3, // damage
        sfx_dmact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_FLOAT | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_SPIDER
        7, // doomednum
        S_SPID_STND, // spawnstate
        3000, // spawnhealth
        S_SPID_RUN1, // seestate
        sfx_spisit, // seesound
        8, // reactiontime
        sfx_shotgn, // attacksound
        S_SPID_PAIN, // painstate
        40, // painchance
        sfx_dmpain, // painsound
        0, // meleestate
        S_SPID_ATK1, // missilestate
        S_SPID_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_spidth, // deathsound
        12, // speed
        128 * FRACUNIT, // radius
        100 * FRACUNIT, // height
        1000, // mass
        0, // damage
        sfx_dmact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_NULL                // raisestate
    },

    { // MT_BABY
        68, // doomednum
        S_BSPI_STND, // spawnstate
        500, // spawnhealth
        S_BSPI_SIGHT, // seestate
        sfx_bspsit, // seesound
        8, // reactiontime
        0, // attacksound
        S_BSPI_PAIN, // painstate
        128, // painchance
        sfx_dmpain, // painsound
        0, // meleestate
        S_BSPI_ATK1, // missilestate
        S_BSPI_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_bspdth, // deathsound
        12, // speed
        64 * FRACUNIT, // radius
        64 * FRACUNIT, // height
        600, // mass
        0, // damage
        sfx_bspact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_BSPI_RAISE1                // raisestate
    },

    { // MT_CYBORG
        16, // doomednum
        S_CYBER_STND, // spawnstate
        4000, // spawnhealth
        S_CYBER_RUN1, // seestate
        sfx_cybsit, // seesound
        8, // reactiontime
        0, // attacksound
        S_CYBER_PAIN, // painstate
        20, // painchance
        sfx_dmpain, // painsound
        0, // meleestate
        S_CYBER_ATK1, // missilestate
        S_CYBER_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_cybdth, // deathsound
        16, // speed
        40 * FRACUNIT, // radius
        110 * FRACUNIT, // height
        1000, // mass
        0, // damage
        sfx_dmact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_NULL                // raisestate
    },

    { // MT_PAIN
        71, // doomednum
        S_PAIN_STND, // spawnstate
        400, // spawnhealth
        S_PAIN_RUN1, // seestate
        sfx_pesit, // seesound
        8, // reactiontime
        0, // attacksound
        S_PAIN_PAIN, // painstate
        128, // painchance
        sfx_pepain, // painsound
        0, // meleestate
        S_PAIN_ATK1, // missilestate
        S_PAIN_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_pedth, // deathsound
        8, // speed
        31 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        400, // mass
        0, // damage
        sfx_dmact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_FLOAT | MF_NOGRAVITY | MF_COUNTKILL, // flags
        S_PAIN_RAISE1                // raisestate
    },

    { // MT_WOLFSS
        84, // doomednum
        S_SSWV_STND, // spawnstate
        50, // spawnhealth
        S_SSWV_RUN1, // seestate
        sfx_sssit, // seesound
        8, // reactiontime
        0, // attacksound
        S_SSWV_PAIN, // painstate
        170, // painchance
        sfx_popain, // painsound
        0, // meleestate
        S_SSWV_ATK1, // missilestate
        S_SSWV_DIE1, // deathstate
        S_SSWV_XDIE1, // xdeathstate
        sfx_ssdth, // deathsound
        8, // speed
        20 * FRACUNIT, // radius
        56 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_posact, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_SSWV_RAISE1                // raisestate
    },

    { // MT_KEEN
        72, // doomednum
        S_KEENSTND, // spawnstate
        100, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_KEENPAIN, // painstate
        256, // painchance
        sfx_keenpn, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_COMMKEEN, // deathstate
        S_NULL, // xdeathstate
        sfx_keendt, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        72 * FRACUNIT, // height
        10000000, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY | MF_SHOOTABLE | MF_COUNTKILL, // flags
        S_NULL                // raisestate
    },

    { // MT_BOSSBRAIN
        88, // doomednum
        S_BRAIN, // spawnstate
        250, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_BRAIN_PAIN, // painstate
        255, // painchance
        sfx_bospn, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_BRAIN_DIE1, // deathstate
        S_NULL, // xdeathstate
        sfx_bosdth, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        10000000, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SHOOTABLE, // flags
        S_NULL                // raisestate
    },

    { // MT_BOSSSPIT
        89, // doomednum
        S_BRAINEYE, // spawnstate
        1000, // spawnhealth
        S_BRAINEYESEE, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        32 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOSECTOR, // flags
        S_NULL                // raisestate
    },

    { // MT_BOSSTARGET
        87, // doomednum
        S_NULL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        32 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOSECTOR, // flags
        S_NULL                // raisestate
    },

    { // MT_SPAWNSHOT
        -1, // doomednum
        S_SPAWN1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_bospit, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_firxpl, // deathsound
        10 * FRACUNIT, // speed
        6 * FRACUNIT, // radius
        32 * FRACUNIT, // height
        100, // mass
        3, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY | MF_NOCLIP, // flags
        S_NULL                // raisestate
    },

    { // MT_SPAWNFIRE
        -1, // doomednum
        S_SPAWNFIRE1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_BARREL
        2035, // doomednum
        S_BAR1, // spawnstate
        20, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_BEXP, // deathstate
        S_NULL, // xdeathstate
        sfx_barexp, // deathsound
        0, // speed
        10 * FRACUNIT, // radius
        42 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SHOOTABLE | MF_NOBLOOD, // flags
        S_NULL                // raisestate
    },

    { // MT_TROOPSHOT
        -1, // doomednum
        S_TBALL1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_firsht, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_TBALLX1, // deathstate
        S_NULL, // xdeathstate
        sfx_firxpl, // deathsound
        10 * FRACUNIT, // speed
        6 * FRACUNIT, // radius
        8 * FRACUNIT, // height
        100, // mass
        3, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_HEADSHOT
        -1, // doomednum
        S_RBALL1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_firsht, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_RBALLX1, // deathstate
        S_NULL, // xdeathstate
        sfx_firxpl, // deathsound
        10 * FRACUNIT, // speed
        6 * FRACUNIT, // radius
        8 * FRACUNIT, // height
        100, // mass
        5, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_ROCKET
        -1, // doomednum
        S_ROCKET, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_rlaunc, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_EXPLODE1, // deathstate
        S_NULL, // xdeathstate
        sfx_barexp, // deathsound
        20 * FRACUNIT, // speed
        11 * FRACUNIT, // radius
        8 * FRACUNIT, // height
        100, // mass
        20, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_PLASMA
        -1, // doomednum
        S_PLASBALL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_plasma, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_PLASEXP, // deathstate
        S_NULL, // xdeathstate
        sfx_firxpl, // deathsound
        25 * FRACUNIT, // speed
        13 * FRACUNIT, // radius
        8 * FRACUNIT, // height
        100, // mass
        5, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_BFG
        -1, // doomednum
        S_BFGSHOT, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        0, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_BFGLAND, // deathstate
        S_NULL, // xdeathstate
        sfx_rxplod, // deathsound
        25 * FRACUNIT, // speed
        13 * FRACUNIT, // radius
        8 * FRACUNIT, // height
        100, // mass
        100, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_ARACHPLAZ
        -1, // doomednum
        S_ARACH_PLAZ, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_plasma, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_ARACH_PLEX, // deathstate
        S_NULL, // xdeathstate
        sfx_firxpl, // deathsound
        25 * FRACUNIT, // speed
        13 * FRACUNIT, // radius
        8 * FRACUNIT, // height
        100, // mass
        5, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_PUFF
        -1, // doomednum
        S_PUFF1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_BLOOD
        -1, // doomednum
        S_BLOOD1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP, // flags
        S_NULL                // raisestate
    },

    { // MT_TFOG
        -1, // doomednum
        S_TFOG, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_IFOG
        -1, // doomednum
        S_IFOG, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_TELEPORTMAN
        14, // doomednum
        S_NULL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOSECTOR, // flags
        S_NULL                // raisestate
    },

    { // MT_EXTRABFG
        -1, // doomednum
        S_BFGEXP, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC0
        2018, // doomednum
        S_ARM1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC1
        2019, // doomednum
        S_ARM2, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC2
        2014, // doomednum
        S_BON1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC3
        2015, // doomednum
        S_BON2, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC4
        5, // doomednum
        S_BKEY, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_NOTDMATCH, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC5
        13, // doomednum
        S_RKEY, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_NOTDMATCH, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC6
        6, // doomednum
        S_YKEY, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_NOTDMATCH, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC7
        39, // doomednum
        S_YSKULL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_NOTDMATCH, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC8
        38, // doomednum
        S_RSKULL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_NOTDMATCH, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC9
        40, // doomednum
        S_BSKULL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_NOTDMATCH, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC10
        2011, // doomednum
        S_STIM, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC11
        2012, // doomednum
        S_MEDI, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC12
        2013, // doomednum
        S_SOUL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        S_NULL                // raisestate
    },

    { // MT_INV
        2022, // doomednum
        S_PINV, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC13
        2023, // doomednum
        S_PSTR, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        S_NULL                // raisestate
    },

    { // MT_INS
        2024, // doomednum
        S_PINS, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC14
        2025, // doomednum
        S_SUIT, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC15
        2026, // doomednum
        S_PMAP, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC16
        2045, // doomednum
        S_PVIS, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        S_NULL                // raisestate
    },

    { // MT_MEGA
        83, // doomednum
        S_MEGA, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        S_NULL                // raisestate
    },

    { // MT_CLIP
        2007, // doomednum
        S_CLIP, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC17
        2048, // doomednum
        S_AMMO, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC18
        2010, // doomednum
        S_ROCK, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC19
        2046, // doomednum
        S_BROK, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC20
        2047, // doomednum
        S_CELL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC21
        17, // doomednum
        S_CELP, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC22
        2008, // doomednum
        S_SHEL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC23
        2049, // doomednum
        S_SBOX, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC24
        8, // doomednum
        S_BPAK, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC25
        2006, // doomednum
        S_BFUG, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_CHAINGUN
        2002, // doomednum
        S_MGUN, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC26
        2005, // doomednum
        S_CSAW, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC27
        2003, // doomednum
        S_LAUN, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC28
        2004, // doomednum
        S_PLAS, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_SHOTGUN
        2001, // doomednum
        S_SHOT, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_SUPERSHOTGUN
        82, // doomednum
        S_SHOT2, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPECIAL, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC29
        85, // doomednum
        S_TECHLAMP, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC30
        86, // doomednum
        S_TECH2LAMP, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC31
        2028, // doomednum
        S_COLU, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC32
        30, // doomednum
        S_TALLGRNCOL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC33
        31, // doomednum
        S_SHRTGRNCOL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC34
        32, // doomednum
        S_TALLREDCOL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC35
        33, // doomednum
        S_SHRTREDCOL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC36
        37, // doomednum
        S_SKULLCOL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC37
        36, // doomednum
        S_HEARTCOL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC38
        41, // doomednum
        S_EVILEYE, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC39
        42, // doomednum
        S_FLOATSKULL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC40
        43, // doomednum
        S_TORCHTREE, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC41
        44, // doomednum
        S_BLUETORCH, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC42
        45, // doomednum
        S_GREENTORCH, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC43
        46, // doomednum
        S_REDTORCH, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC44
        55, // doomednum
        S_BTORCHSHRT, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC45
        56, // doomednum
        S_GTORCHSHRT, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC46
        57, // doomednum
        S_RTORCHSHRT, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC47
        47, // doomednum
        S_STALAGTITE, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC48
        48, // doomednum
        S_TECHPILLAR, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC49
        34, // doomednum
        S_CANDLESTIK, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC50
        35, // doomednum
        S_CANDELABRA, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC51
        49, // doomednum
        S_BLOODYTWITCH, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        68 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC52
        50, // doomednum
        S_MEAT2, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        84 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC53
        51, // doomednum
        S_MEAT3, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        84 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC54
        52, // doomednum
        S_MEAT4, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        68 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC55
        53, // doomednum
        S_MEAT5, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        52 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC56
        59, // doomednum
        S_MEAT2, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        84 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC57
        60, // doomednum
        S_MEAT4, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        68 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC58
        61, // doomednum
        S_MEAT3, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        52 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC59
        62, // doomednum
        S_MEAT5, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        52 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC60
        63, // doomednum
        S_BLOODYTWITCH, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        68 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC61
        22, // doomednum
        S_HEAD_DIE6, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC62
        15, // doomednum
        S_PLAY_DIE7, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC63
        18, // doomednum
        S_POSS_DIE5, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC64
        21, // doomednum
        S_SARG_DIE6, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC65
        23, // doomednum
        S_SKULL_DIE6, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC66
        20, // doomednum
        S_TROO_DIE5, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC67
        19, // doomednum
        S_SPOS_DIE5, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC68
        10, // doomednum
        S_PLAY_XDIE9, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC69
        12, // doomednum
        S_PLAY_XDIE9, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC70
        28, // doomednum
        S_HEADSONSTICK, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC71
        24, // doomednum
        S_GIBS, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        0, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC72
        27, // doomednum
        S_HEADONASTICK, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC73
        29, // doomednum
        S_HEADCANDLES, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC74
        25, // doomednum
        S_DEADSTICK, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC75
        26, // doomednum
        S_LIVESTICK, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC76
        54, // doomednum
        S_BIGTREE, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        32 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC77
        70, // doomednum
        S_BBAR1, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC78
        73, // doomednum
        S_HANGNOGUTS, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        88 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC79
        74, // doomednum
        S_HANGBNOBRAIN, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        88 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC80
        75, // doomednum
        S_HANGTLOOKDN, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        64 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC81
        76, // doomednum
        S_HANGTSKULL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        64 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC82
        77, // doomednum
        S_HANGTLOOKUP, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        64 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC83
        78, // doomednum
        S_HANGTNOBRAIN, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        16 * FRACUNIT, // radius
        64 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC84
        79, // doomednum
        S_COLONGIBS, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC85
        80, // doomednum
        S_SMALLPOOL, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP, // flags
        S_NULL                // raisestate
    },

    { // MT_MISC86
        81, // doomednum
        S_BRAINSTEM, // spawnstate
        1000, // spawnhealth
        S_NULL, // seestate
        sfx_None, // seesound
        8, // reactiontime
        sfx_None, // attacksound
        S_NULL, // painstate
        0, // painchance
        sfx_None, // painsound
        S_NULL, // meleestate
        S_NULL, // missilestate
        S_NULL, // deathstate
        S_NULL, // xdeathstate
        sfx_None, // deathsound
        0, // speed
        20 * FRACUNIT, // radius
        16 * FRACUNIT, // height
        100, // mass
        0, // damage
        sfx_None, // activesound
        MF_NOBLOCKMAP, // flags
        S_NULL                // raisestate
    }
};
int myargc;
char** myargv;


//
// M_CheckParm
// Checks for the given parameter
// in the program's command line arguments.
// Returns the argument number (1 to argc-1)
// or 0 if not present
extern int M_CheckParm(char* check);
extern void M_ClearBox(fixed_t* box);


extern void M_AddToBox(fixed_t* box, fixed_t x, fixed_t y);
int firsttime = 1;
unsigned char cheat_xlate_table[256];


//
// Called in st_stuff module, which handles the input.
// Returns a 1 if the cheat was successful, 0 if failed.
//
extern int cht_CheckCheat(cheatseq_t* cht, char key);


extern void cht_GetParam(cheatseq_t* cht, char* buffer);
extern fixed_t FixedMul(fixed_t a, fixed_t b);


//
// FixedDiv, C version.
//
extern fixed_t FixedDiv(fixed_t a, fixed_t b);


extern fixed_t FixedDiv2(fixed_t a, fixed_t b);
#define SAVESTRINGSIZE 24
#define SKULLXOFF -32
#define LINEHEIGHT 16


//
// MENU TYPEDEFS
//
typedef struct
{
    // 0 = no cursor here, 1 = ok, 2 = arrows ok
    short status;

    char* name;

    // choice = menu item #.
    // if status = 2,
    //   choice=0:leftarrow,1:rightarrow
    void (*routine)(int choice);

    // hotkey in menu
    char alphaKey;
} menuitem_t;


typedef struct menu_s
{
    short numitems; // # of menu items
    struct menu_s* prevMenu; // previous menu
    menuitem_t* menuitems; // menu items
    void (*routine)(); // draw routine
    short x;
    short y; // x,y of menu
    short lastOn; // last item user was on in menu
} menu_t;


typedef struct
{
    char* lump;
    int x, w;
    int offx;
    int offy;
} menu_custom_text_seg_t;


typedef struct
{
    char* name;
    menu_custom_text_seg_t segs[16];
} menu_custom_text_t;


extern int doom_flags;

extern patch_t* hu_font[HU_FONTSIZE];
extern doom_boolean message_dontfuckwithme;

extern doom_boolean chat_on; // in heads-up code

extern int mousemove;


//
// defaulted values
//
int mouseSensitivity; // has default

// Show messages has default, 0 = off, 1 = on
int showMessages;


// Blocky mode, has default, 0 = high, 1 = normal
int detailLevel;
int screenblocks; // has default

// temp for screenblocks (0-9)
int screenSize;

// -1 = no quicksave slot picked!
int quickSaveSlot;

// 1 = message to be printed
int messageToPrint;
// ...and here is the message string!
char* messageString;

// message x & y
int messx;
int messy;
int messageLastMenuActive;

// timed message = no input from user
doom_boolean messageNeedsInput;

void (*messageRoutine)(int response);

char* gammamsg[5];

// we are going to be entering a savegame string
int saveStringEnter;
int saveSlot; // which slot to save in
int saveCharIndex; // which char we're editing
// old save description before edit
char saveOldString[SAVESTRINGSIZE];

doom_boolean inhelpscreens;
doom_boolean menuactive;

extern doom_boolean sendpause;
char savegamestrings[10][SAVESTRINGSIZE];

char endstring[160];

short itemOn; // menu item skull is on
short skullAnimCounter; // skull animation counter
short whichSkull; // which skull to draw

// graphic name of skulls
// warning: initializer-string for array of chars is too long
char* skullName[2] = { "M_SKULL1","M_SKULL2" };

// current menudef
menu_t* currentMenu;

// We create new menu text by cutting into existing graphics and pasting them to create the new text.
// This way we don't ship code with embeded graphics that come from WAD files.
menu_custom_text_t menu_custom_texts[4];

int custom_texts_count;// = sizeof(menu_custom_texts) / sizeof(menu_custom_text_t);

char tempstring[80];
int epi;
char* detailNames[2];// = { "M_GDHIGH","M_GDLOW" };
char* msgNames[2];// = { "M_MSGOFF","M_MSGON" };

int quitsounds[8] =
{
    sfx_pldeth,
    sfx_dmpain,
    sfx_popain,
    sfx_slop,
    sfx_telept,
    sfx_posit1,
    sfx_posit3,
    sfx_sgtatk
};

int quitsounds2[8] =
{
    sfx_vilact,
    sfx_getpow,
    sfx_boscub,
    sfx_slop,
    sfx_skeswg,
    sfx_kntdth,
    sfx_bspact,
    sfx_sgtatk
};


//
// PROTOTYPES
//
void M_NewGame(int choice);
void M_Episode(int choice);
void M_ChooseSkill(int choice);
void M_LoadGame(int choice);
void M_SaveGame(int choice);
void M_Options(int choice);
void M_EndGame(int choice);
void M_ReadThis(int choice);
void M_ReadThis2(int choice);
void M_QuitDOOM(int choice);

void M_ChangeMessages(int choice);
void M_SfxVol(int choice);
void M_MusicVol(int choice);
void M_ChangeDetail(int choice);
void M_MouseOptions(int choice);
void M_SizeDisplay(int choice);
void M_StartGame(int choice);
void M_Sound(int choice);
void M_ChangeCrosshair(int choice);
void M_ChangeAlwaysRun(int choice);

void M_MouseMove(int choice);
void M_ChangeSensitivity(int choice);

void M_FinishReadThis(int choice);
void M_LoadSelect(int choice);
void M_SaveSelect(int choice);
void M_ReadSaveStrings(void);
void M_QuickSave(void);
void M_QuickLoad(void);

void M_DrawMainMenu(void);
void M_DrawReadThis1(void);
void M_DrawReadThis2(void);
void M_DrawNewGame(void);
void M_DrawEpisode(void);
void M_DrawOptions(void);
void M_DrawSound(void);
void M_DrawLoad(void);
void M_DrawSave(void);

void M_DrawSaveLoadBorder(int x, int y);
void M_SetupNextMenu(menu_t* menudef);
void M_DrawThermo(int x, int y, int thermWidth, int thermDot);
void M_DrawEmptyCell(menu_t* menu, int item);
void M_DrawSelCell(menu_t* menu, int item);
void M_WriteText(int x, int y, char* string);
int  M_StringWidth(char* string);
int  M_StringHeight(char* string);
void M_StartControlPanel(void);
void M_StartMessage(char* string, void* routine, doom_boolean input);
void M_StopMessage(void);
void M_ClearMenus(void);
void M_DrawMouseOptions(void);


//
// DOOM MENU
//
enum
{
    newgame = 0,
    options,
    loadgame,
    savegame,
    readthis,
    quitdoom,
    main_end
} main_e;

menuitem_t MainMenu[6];

menu_t  MainDef;


//
// EPISODE SELECT
//
enum
{
    ep1,
    ep2,
    ep3,
    ep4,
    ep_end
} episodes_e;

menuitem_t EpisodeMenu[] =
{
    {1,"M_EPI1", M_Episode,'k'},
    {1,"M_EPI2", M_Episode,'t'},
    {1,"M_EPI3", M_Episode,'i'},
    {1,"M_EPI4", M_Episode,'t'}
};

menu_t  EpiDef;


//
// NEW GAME
//
enum
{
    killthings,
    toorough,
    hurtme,
    violence,
    nightmare,
    newg_end
} newgame_e;

menuitem_t NewGameMenu[5];
menu_t  NewDef;


//
// OPTIONS MENU
//
menuitem_t* OptionsMenu;

enum
{
    endgame,
    messages,
    crosshair_opt,
    always_run_opt,
    //detail, // Details do nothing?
    scrnsize,
    option_empty1,
    mouseoptions,
    soundvol,
    opt_end
} options_e;

menuitem_t OptionsMenuFull[8];

menu_t  OptionsDef;


enum
{
    endgame_no_mouse,
    messages_no_mouse,
    crosshair_opt_no_mouse,
    always_run_opt_no_mouse,
    //detail_no_mouse, // Details do nothing?
    scrnsize_no_mouse,
    option_empty1_no_mouse,
    soundvol_no_mouse,
    opt_end_no_mouse
} options_e_no_mouse;

menuitem_t OptionsMenuNoMouse[7];

menu_t  OptionsNoMouseDef;


enum
{
    endgame_no_sound,
    messages_no_sound,
    crosshair_opt_no_sound,
    always_run_opt_no_sound,
    //detail_no_sound, // Details do nothing?
    scrnsize_no_sound,
    option_empty1_no_sound,
    mouseoptions_no_sound,
    opt_end_no_sound
} options_e_no_sound;

menuitem_t OptionsMenuNoSound[] =
{
    {1,"M_ENDGAM",  M_EndGame,'e'},
    {1,"M_MESSG",   M_ChangeMessages,'m'},
    {1,"TXT_CROS",  M_ChangeCrosshair,'c'},
    {1,"TXT_ARUN",  M_ChangeAlwaysRun,'r'},
    //{1,"M_DETAIL",  M_ChangeDetail,'g'}, // Details do nothing?
    {2,"M_SCRNSZ",  M_SizeDisplay,'s'},
    {-1,"",0},
    {1,"TXT_MOPT",  M_MouseOptions,'f'}
};

menu_t OptionsNoSoundDef =
{
    opt_end_no_sound,
    &MainDef,
    OptionsMenuNoSound,
    M_DrawOptions,
    60,37,
    0
};


enum
{
    endgame_no_sound_no_mouse,
    messages_no_sound_no_mouse,
    crosshair_opt_no_sound_no_mouse,
    always_run_top_no_sound_no_mouse,
    //detail_no_sound_no_mouse, // Details do nothing?
    scrnsize_no_sound_no_mouse,
    option_empty1_no_sound_no_mouse,
    opt_end_no_sound_no_mouse
} options_e_no_sound_no_mouse;

menuitem_t OptionsMenuNoSoundNoMouse[] =
{
    {1,"M_ENDGAM",  M_EndGame,'e'},
    {1,"M_MESSG",   M_ChangeMessages,'m'},
    {1,"TXT_CROS",  M_ChangeCrosshair,'c'},
    {1,"TXT_ARUN",  M_ChangeAlwaysRun,'r'},
    //{1,"M_DETAIL",  M_ChangeDetail,'g'}, // Details do nothing?
    {2,"M_SCRNSZ",  M_SizeDisplay,'s'},
    {-1,"",0}
};

menu_t OptionsNoSoundNoMouseDef =
{
    opt_end_no_sound_no_mouse,
    &MainDef,
    OptionsMenuNoSoundNoMouse,
    M_DrawOptions,
    60,37,
    0
};


//
// MOUSE OPTIONS
//
enum
{
    mousemov,
    mousesens,
    mouse_option_empty1,
    mouse_opt_end
} mouseoptions_e;

menuitem_t MouseOptionsMenu[3];

menu_t  MouseOptionsDef;


//
// Read This! MENU 1 & 2
//
enum
{
    rdthsempty1,
    read1_end
} read_e;

menuitem_t ReadMenu1[1];

menu_t  ReadDef1;

enum
{
    rdthsempty2,
    read2_end
} read_e2;

menuitem_t ReadMenu2[1];

menu_t  ReadDef2;

//
// SOUND VOLUME MENU
//
menuitem_t* SoundMenu;

enum
{
    sfx_vol,
    sfx_empty1,
    music_vol,
    sfx_empty2,
    sound_end
} sound_e;

menuitem_t SoundMenuFull[4];

menu_t  SoundDef;


enum
{
    music_vol_no_sfx,
    sfx_empty2_no_sfx,
    sound_end_no_sfx
} sound_e_no_sfx;

menuitem_t SoundMenuNoSFX[] =
{
    {2,"M_MUSVOL",M_MusicVol,'m'},
    {-1,"",0}
};

menu_t  SoundNoSFXDef =
{
    sound_end_no_sfx,
    &OptionsDef,
    SoundMenuNoSFX,
    M_DrawSound,
    80,64,
    0
};


enum
{
    sfx_vol_no_music,
    sfx_empty1_no_music,
    sound_end_no_music
} sound_e_no_music;

menuitem_t SoundMenuNoMusic[] =
{
    {2,"M_SFXVOL",M_SfxVol,'s'},
    {-1,"",0}
};

menu_t  SoundNoMusicDef =
{
    sound_end_no_music,
    &OptionsDef,
    SoundMenuNoMusic,
    M_DrawSound,
    80,64,
    0
};


//
// LOAD GAME MENU
//
enum
{
    load1,
    load2,
    load3,
    load4,
    load5,
    load6,
    load_end
} load_e;

menuitem_t DOOM_LoadMenu[6];

menu_t  LoadDef;

//
// SAVE GAME MENU
//
menuitem_t SaveMenu[6];

menu_t  SaveDef;


//
// M_DrawCustomMenuText
//  Draw several segments of patches to make up new text
//
extern void M_DrawCustomMenuText(char* name, int x, int y);


//
// M_ReadSaveStrings
//  read the strings from the savegame files
//
extern void M_ReadSaveStrings(void);


//
// M_LoadGame & Cie.
//
extern void M_DrawLoad(void);


//
// Draw border for the savegame description
//
extern void M_DrawSaveLoadBorder(int x, int y);


//
// User wants to load this game
//
extern void M_LoadSelect(int choice);

//
// Selected from DOOM menu
//
extern void M_LoadGame(int choice);

//
//  M_SaveGame & Cie.
//
extern void M_DrawSave(void);


//
// M_Responder calls this when user is finished
//
extern void M_DoSave(int slot);


//
// User wants to save. Start string input for M_Responder
//
extern void M_SaveSelect(int choice);


//
// Selected from DOOM menu
//
extern void M_SaveGame(int choice);

//
// M_QuickSave
//
extern void M_QuickSaveResponse(int ch);


extern void M_QuickSave(void);

//
// M_QuickLoad
//
extern void M_QuickLoadResponse(int ch);


extern void M_QuickLoad(void);


//
// Read This Menus
// Had a "quick hack to fix romero bug"
//
extern void M_DrawReadThis1(void);


//
// Read This Menus - optional second page.
//
extern void M_DrawReadThis2(void);


//
// Change Sfx & Music volumes
//
extern void M_DrawSound(void);

extern void M_Sound(int choice);


extern void M_MouseOptions(int choice);


extern void M_SfxVol(int choice);


extern void M_MusicVol(int choice);


//
// M_DrawMainMenu
//
extern void M_DrawMainMenu(void);


//
// M_NewGame
//
extern void M_DrawNewGame(void);


extern void M_NewGame(int choice);

//
// M_Episode
//
extern void M_DrawEpisode(void);

extern void M_VerifyNightmare(int ch);

extern void M_ChooseSkill(int choice);

extern void M_Episode(int choice);


//
// M_Options
//
extern void M_DrawOptions(void);


extern void M_DrawMouseOptions(void);


extern void M_Options(int choice);


//
// Toggle messages on/off
//
void M_ChangeMessages(int choice);


//
// Toggle crosshair on/off
//
extern void M_ChangeCrosshair(int choice);


//
// Toggle always-run on/off
//
extern void M_ChangeAlwaysRun(int choice);


//
// M_EndGame
//
extern void M_EndGameResponse(int ch);


extern void M_EndGame(int choice);


//
// M_ReadThis
//
extern void M_ReadThis(int choice);


extern void M_ReadThis2(int choice);


extern void M_FinishReadThis(int choice);


//
// M_QuitDOOM
//
extern void M_QuitResponse(int ch);


extern void M_QuitDOOM(int choice);


extern void M_ChangeSensitivity(int choice);


extern void M_MouseMove(int choice);


void M_ChangeDetail(int choice)
{
    choice = 0;
    detailLevel = 1 - detailLevel;

    // FIXME - does not work. Remove anyway?
    doom_print("M_ChangeDetail: low detail mode n.a.\n");
}


extern void M_SizeDisplay(int choice);


//
// Menu Functions
//
extern void M_DrawThermo(int x, int y, int thermWidth, int thermDot);


extern void M_DrawEmptyCell(menu_t* menu, int item);


extern void M_DrawSelCell(menu_t* menu, int item);


extern void M_StartMessage(char* string, void* routine, doom_boolean input);


extern void M_StopMessage(void);

//
// Find string width from hu_font chars
//
extern int M_StringWidth(char* string);


//
// Find string height from hu_font chars
//
extern int M_StringHeight(char* string);

//
// Write a string using the hu_font
//
extern void M_WriteText(int x, int y, char* string);


//
// CONTROL PANEL
//

//
// M_Responder
//
extern doom_boolean M_Responder(event_t* ev);


//
// M_StartControlPanel
//
extern void M_StartControlPanel(void);


//
// M_Drawer
// Called after the view has been rendered,
// but before it has been blitted.
//
extern void M_Drawer(void);


//
// M_ClearMenus
//
extern void M_ClearMenus(void);


//
// M_SetupNextMenu
//
extern void M_SetupNextMenu(menu_t* menudef);


//
// M_Ticker
//
extern void M_Ticker(void);


//
// M_Init
//
extern void M_Init(void);
#ifndef O_BINARY
#define O_BINARY 0
#endif
#define STRING_VALUE 0xFFFF


//
// SCREEN SHOTS
//
typedef struct
{
    char manufacturer;
    char version;
    char encoding;
    char bits_per_pixel;

    unsigned short xmin;
    unsigned short ymin;
    unsigned short xmax;
    unsigned short ymax;

    unsigned short hres;
    unsigned short vres;

    unsigned char palette[48];

    char reserved;
    char color_planes;
    unsigned short bytes_per_line;
    unsigned short palette_type;

    char filler[58];
    unsigned char data; // unbounded
} pcx_t;


//
// M_DrawText
// Returns the final X coordinate
// HU_Init must have been called to init the font
//
extern patch_t* hu_font[HU_FONTSIZE];


//
// DEFAULTS
//
extern int key_right;
extern int key_left;
extern int key_up;
extern int key_down;

extern int key_strafeleft;
extern int key_straferight;

extern int key_fire;
extern int key_use;
extern int key_strafe;
extern int key_speed;

extern int mousebfire;
extern int mousebstrafe;
extern int mousebforward;
extern int mousemove;

extern int joybfire;
extern int joybstrafe;
extern int joybuse;
extern int joybspeed;

extern int viewwidth;
extern int viewheight;

extern int mouseSensitivity;
extern int showMessages;

extern int detailLevel;

extern int screenblocks;

extern int showMessages;

// machine-independent sound params
extern int numChannels;

extern char* chat_macros[];

extern byte scantokey[128];


int usemouse;
int usejoystick;
int crosshair;
int always_run;


default_t defaults[40];


int numdefaults = sizeof(defaults) / sizeof(default_t);;
char* defaultfile;


extern int M_DrawText(int x, int y, doom_boolean direct, char* string);


//
// M_WriteFile
//
doom_boolean M_WriteFile(char const* name, void* source, int length);


//
// M_ReadFile
//
extern int M_ReadFile(char const* name, byte** buffer);


//
// M_SaveDefaults
//
extern void M_SaveDefaults(void);


//
// M_LoadDefaults
//
extern void M_LoadDefaults(void);


//
// WritePCXfile
//
extern void WritePCXfile(char* filename, byte* data, int width, int height, byte* palette);


//
// M_ScreenShot
//
extern void M_ScreenShot(void);
unsigned char rndtable[256];


int rndindex = 0;
int prndindex = 0;


// Which one is deterministic?
extern int P_Random(void);


extern int M_Random(void);


extern void M_ClearRandom(void);
#ifdef __BIG_ENDIAN__


// Swap 16bit, that is, MSB and LSB byte.
unsigned short SwapSHORT(unsigned short x)
{
    // No masking with 0xFF should be necessary. 
    return (x >> 8) | (x << 8);
}


// Swapping 32bit.
unsigned long SwapLONG(unsigned long x)
{
    return
        (x >> 24)
        | ((x >> 8) & 0xff00)
        | ((x << 8) & 0xff0000)
        | (x << 24);
}


#endif
ceiling_t* activeceilings[MAXCEILINGS];


//
// T_MoveCeiling
//
extern void T_MoveCeiling(ceiling_t* ceiling);


//
// EV_DoCeiling
// Move a ceiling up/down and all around!
//
extern int EV_DoCeiling(line_t* line, ceiling_e type);


//
// Add an active ceiling
//
extern void P_AddActiveCeiling(ceiling_t* c);


//
// Remove a ceiling's thinker
//
extern void P_RemoveActiveCeiling(ceiling_t* c);


//
// Restart a ceiling that's in-stasis
//
void P_ActivateInStasisCeiling(line_t* line);


//
// EV_CeilingCrushStop
// Stop a ceiling from crushing!
//
extern int EV_CeilingCrushStop(line_t* line);
extern void T_VerticalDoor(vldoor_t* door);


//
// EV_DoLockedDoor
// Move a locked door up/down
//
extern int EV_DoLockedDoor(line_t* line, vldoor_e type, mobj_t* thing);


extern int EV_DoDoor(line_t* line, vldoor_e type);


//
// EV_VerticalDoor : open a door manually, no tag value
//
extern void EV_VerticalDoor(line_t* line, mobj_t* thing);


//
// Spawn a door that closes after 30 seconds
//
extern void P_SpawnDoorCloseIn30(sector_t* sec);


//
// Spawn a door that opens after 5 minutes
//
extern void P_SpawnDoorRaiseIn5Mins(sector_t* sec, int secnum);
#define MAXSPECIALCROSS 8
#define FATSPREAD (ANG90/8)
#define SKULLSPEED (20*FRACUNIT)


typedef enum
{
    DI_EAST,
    DI_NORTHEAST,
    DI_NORTH,
    DI_NORTHWEST,
    DI_WEST,
    DI_SOUTHWEST,
    DI_SOUTH,
    DI_SOUTHEAST,
    DI_NODIR,
    NUMDIRS
} dirtype_t;


//
// P_NewChaseDir related LUT.
//
dirtype_t opposite[9];

dirtype_t diags[4];

mobj_t* soundtarget;
fixed_t xspeed[8] = { FRACUNIT,47000,0,-47000,-FRACUNIT,-47000,0,47000 };
fixed_t yspeed[8] = { 0,47000,FRACUNIT,47000,0,-47000,-FRACUNIT,-47000 };
int TRACEANGLE = 0xc000000;
mobj_t* corpsehit;
mobj_t* vileobj;
fixed_t viletryx;
fixed_t viletryy;
mobj_t* braintargets[32];
int numbraintargets;
int braintargeton;


extern line_t* spechit[MAXSPECIALCROSS];
extern int numspechit;


void A_Fall(mobj_t* actor);
void A_Fire(mobj_t* actor);
void A_ReFire(player_t* player, pspdef_t* psp);
void A_SpawnFly(mobj_t* mo);


//
// ENEMY THINKING
// Enemies are allways spawned
// with targetplayer = -1, threshold = 0
// Most monsters are spawned unaware of all players,
// but some can be made preaware
//


//
// Called by P_NoiseAlert.
// Recursively traverse adjacent sectors,
// sound blocking lines cut off traversal.
//
extern void P_RecursiveSound(sector_t* sec, int soundblocks);


//
// P_NoiseAlert
// If a monster yells at a player,
// it will alert other monsters to the player.
//
extern void P_NoiseAlert(mobj_t* target, mobj_t* emmiter);


//
// P_CheckMeleeRange
//
extern doom_boolean P_CheckMeleeRange(mobj_t* actor);


//
// P_CheckMissileRange
//
extern doom_boolean P_CheckMissileRange(mobj_t* actor);


//
// P_Move
// Move in the current direction,
// returns false if the move is blocked.
//
extern doom_boolean P_Move(mobj_t* actor);


//
// TryWalk
// Attempts to move actor on
// in its current (ob->moveangle) direction.
// If blocked by either a wall or an actor
// returns FALSE
// If move is either clear or blocked only by a door,
// returns TRUE and sets...
// If a door is in the way,
// an OpenDoor call is made to start it opening.
//
extern doom_boolean P_TryWalk(mobj_t* actor);


extern void P_NewChaseDir(mobj_t* actor);


//
// P_LookForPlayers
// If allaround is false, only look 180 degrees in front.
// Returns true if a player is targeted.
//
extern doom_boolean P_LookForPlayers(mobj_t* actor, doom_boolean allaround);


//
// A_KeenDie
// DOOM II special, map 32.
// Uses special tag 666.
//
extern void A_KeenDie(mobj_t* mo);


//
// ACTION ROUTINES
//

//
// A_Look
// Stay in state until a player is sighted.
//
extern void A_Look(mobj_t* actor);


//
// A_Chase
// Actor has a melee attack,
// so it tries to close as fast as possible
//
extern void A_Chase(mobj_t* actor);


//
// A_FaceTarget
//
extern void A_FaceTarget(mobj_t* actor);


//
// A_PosAttack
//
extern void A_PosAttack(mobj_t* actor);


extern void A_SPosAttack(mobj_t* actor);


extern void A_CPosAttack(mobj_t* actor);


extern void A_CPosRefire(mobj_t* actor);


extern void A_SpidRefire(mobj_t* actor);


extern void A_BspiAttack(mobj_t* actor);


//
// A_TroopAttack
//
extern void A_TroopAttack(mobj_t* actor);


extern void A_SargAttack(mobj_t* actor);


extern void A_HeadAttack(mobj_t* actor);


extern void A_CyberAttack(mobj_t* actor);


extern void A_BruisAttack(mobj_t* actor);


//
// A_SkelMissile
//
extern void A_SkelMissile(mobj_t* actor);


extern void A_Tracer(mobj_t* actor);


void A_SkelWhoosh(mobj_t* actor);


extern void A_SkelFist(mobj_t* actor);


//
// PIT_VileCheck
// Detect a corpse that could be raised.
//
extern doom_boolean PIT_VileCheck(mobj_t* thing);


//
// A_VileChase
// Check for ressurecting a body
//
extern void A_VileChase(mobj_t* actor);


//
// A_VileStart
//
extern void A_VileStart(mobj_t* actor);


//
// A_Fire
// Keep fire in front of player unless out of sight
//
extern void A_StartFire(mobj_t* actor);


extern void A_FireCrackle(mobj_t* actor);


extern void A_Fire(mobj_t* actor);


//
// A_VileTarget
// Spawn the hellfire
//
extern void A_VileTarget(mobj_t* actor);


//
// A_VileAttack
//
extern void A_VileAttack(mobj_t* actor);


//
// Mancubus attack,
// firing three missiles (bruisers)
// in three different directions?
// Doesn't look like it. 
//
extern void A_FatRaise(mobj_t* actor);


extern void A_FatAttack1(mobj_t* actor);


extern void A_FatAttack2(mobj_t* actor);


extern void A_FatAttack3(mobj_t* actor);


//
// SkullAttack
// Fly at the player like a missile.
//
extern void A_SkullAttack(mobj_t* actor);


//
// A_PainShootSkull
// Spawn a lost soul and launch it at the target
//
extern void A_PainShootSkull(mobj_t* actor, angle_t angle);


//
// A_PainAttack
// Spawn a lost soul and launch it at the target
// 
extern void A_PainAttack(mobj_t* actor);


extern void A_PainDie(mobj_t* actor);


extern void A_Scream(mobj_t* actor);


extern void A_XScream(mobj_t* actor);


extern void A_Pain(mobj_t* actor);


extern void A_Fall(mobj_t* actor);


//
// A_Explode
//
extern void A_Explode(mobj_t* thingy);


//
// A_BossDeath
// Possibly trigger special effects
// if on first boss level
//
extern void A_BossDeath(mobj_t* mo);


extern void A_Hoof(mobj_t* mo);


extern void A_Metal(mobj_t* mo);


extern void A_BabyMetal(mobj_t* mo);


extern void A_OpenShotgun2(player_t* player, pspdef_t* psp);


extern void A_LoadShotgun2(player_t* player, pspdef_t* psp);


extern void A_CloseShotgun2(player_t* player, pspdef_t* psp);

extern void A_BrainAwake(mobj_t* mo);


extern void A_BrainPain(mobj_t* mo);


extern void A_BrainScream(mobj_t* mo);


extern void A_BrainExplode(mobj_t* mo);


void A_BrainDie(mobj_t* mo)
{
    G_ExitLevel();
}


extern void A_BrainSpit(mobj_t* mo);


// travelling cube sound
extern void A_SpawnSound(mobj_t* mo);


extern void A_SpawnFly(mobj_t* mo);


extern void A_PlayerScream(mobj_t* mo);
extern result_e T_MovePlane(sector_t* sector,
                     fixed_t speed,
                     fixed_t dest,
                     doom_boolean crush,
                     int floorOrCeiling,
                     int direction);


//
// MOVE A FLOOR TO IT'S DESTINATION (UP OR DOWN)
//
extern void T_MoveFloor(floormove_t* floor);


//
// HANDLE FLOOR TYPES
//
extern int EV_DoFloor(line_t* line, floor_e floortype);


//
// BUILD A STAIRCASE!
//
extern int EV_BuildStairs(line_t* line, stair_e type);
#ifdef __GNUG__
#pragma implementation "p_inter.h"
#endif
//#include "p_inter.h"


#define BONUSADD        6




// a weapon is found with two clip loads,
// a big item has five clip loads
int        maxammo[NUMAMMO];
int        clipammo[NUMAMMO];


//
// GET STUFF
//

//
// P_GiveAmmo
// Num is the number of clip loads,
// not the individual count (0= 1/2 clip).
// Returns false if the ammo can't be picked up at all
//

extern doom_boolean
P_GiveAmmo
( player_t*        player,
  ammotype_t        ammo,
  int                num );


//
// P_GiveWeapon
// The weapon name may have a MF_DROPPED flag ored in.
//
extern doom_boolean
P_GiveWeapon
( player_t*        player,
  weapontype_t        weapon,
  doom_boolean        dropped );

 

//
// P_GiveBody
// Returns false if the body isn't needed at all
//
extern doom_boolean
P_GiveBody
( player_t*        player,
  int                num );



//
// P_GiveArmor
// Returns false if the armor is worse
// than the current armor.
//
extern doom_boolean
P_GiveArmor
( player_t*        player,
  int                armortype );



//
// P_GiveCard
//
extern void
P_GiveCard
( player_t*        player,
  card_t        card );


//
// P_GivePower
//
extern doom_boolean
P_GivePower
( player_t*        player,
  int /*powertype_t*/        power );



//
// P_TouchSpecialThing
//
extern void
P_TouchSpecialThing
( mobj_t*        special,
  mobj_t*        toucher );


//
// KillMobj
//
extern void
P_KillMobj
( mobj_t*        source,
  mobj_t*        target );




//
// P_DamageMobj
// Damages both enemies and players
// "inflictor" is the thing that caused the damage
//  creature or missile, can be 0 (slime, etc)
// "source" is the thing to target after taking damage
//  creature or 0
// Source and inflictor are the same for melee attacks.
// Source can be 0 for slime, barrel explosions
// and other environmental stuff.
//
extern void
P_DamageMobj
( mobj_t*        target,
  mobj_t*        inflictor,
  mobj_t*        source,
  int                 damage );

extern void T_FireFlicker(fireflicker_t* flick);


//
// P_SpawnFireFlicker
//
extern void P_SpawnFireFlicker(sector_t* sector);


//
// BROKEN LIGHT FLASHING
//

//
// T_LightFlash
// Do flashing lights.
//
extern void T_LightFlash(lightflash_t* flash);


//
// P_SpawnLightFlash
// After the map has been loaded, scan each sector
// for specials that spawn thinkers
//
extern void P_SpawnLightFlash(sector_t* sector);


//
// STROBE LIGHT FLASHING
//

//
// T_StrobeFlash
//
extern void T_StrobeFlash(strobe_t* flash);


//
// P_SpawnStrobeFlash
// After the map has been loaded, scan each sector
// for specials that spawn thinkers
//
extern void P_SpawnStrobeFlash(sector_t* sector, int fastOrSlow, int inSync);


//
// Start strobing lights (usually from a trigger)
//
extern void EV_StartLightStrobing(line_t* line);


//
// TURN LINE'S TAG LIGHTS OFF
//
extern void EV_TurnTagLightsOff(line_t* line);


//
// TURN LINE'S TAG LIGHTS ON
//
extern void EV_LightTurnOn(line_t* line, int bright);


//
// Spawn glowing light
//
extern void T_Glow(glow_t* g);


extern void P_SpawnGlowingLight(sector_t* sector);
#define MAXSPECIALCROSS 8


fixed_t tmbbox[4];
mobj_t* tmthing;
int tmflags;
fixed_t tmx;
fixed_t tmy;

// If "floatok" true, move would be ok
// if within "tmfloorz - tmceilingz".
doom_boolean floatok;

fixed_t tmfloorz;
fixed_t tmceilingz;
fixed_t tmdropoffz;

// keep track of the line that lowers the ceiling,
// so missiles don't explode against sky hack walls
line_t* ceilingline;

// keep track of special lines as they are hit,
// but don't process them until the move is proven valid

line_t* spechit[MAXSPECIALCROSS];
int numspechit;

mobj_t* linetarget; // who got hit (or 0)
mobj_t* shootthing;

// Height if not aiming up or down
// ???: use slope for monsters?
fixed_t shootz;

int la_damage;
fixed_t attackrange;

fixed_t aimslope;
mobj_t* usething;
doom_boolean crushchange;
doom_boolean nofit;


// slopes to top and bottom of target
extern fixed_t topslope;
extern fixed_t bottomslope;


//
// TELEPORT MOVE
// 

//
// PIT_StompThing
//
extern doom_boolean PIT_StompThing(mobj_t* thing);


//
// P_TeleportMove
//
extern doom_boolean P_TeleportMove(mobj_t* thing, fixed_t x, fixed_t y);


//
// MOVEMENT ITERATOR FUNCTIONS
//

//
// PIT_CheckLine
// Adjusts tmfloorz and tmceilingz as lines are contacted
//
extern doom_boolean PIT_CheckLine(line_t* ld);


//
// PIT_CheckThing
//
extern doom_boolean PIT_CheckThing(mobj_t* thing);


//
// MOVEMENT CLIPPING
//

//
// P_CheckPosition
// This is purely informative, nothing is modified
// (except things picked up).
// 
// in:
//  a mobj_t (can be valid or invalid)
//  a position to be checked
//   (doesn't need to be related to the mobj_t->x,y)
//
// during:
//  special things are touched if MF_PICKUP
//  early out on solid lines?
//
// out:
//  newsubsec
//  floorz
//  ceilingz
//  tmdropoffz
//   the lowest point contacted
//   (monsters won't move to a dropoff)
//  speciallines[]
//  numspeciallines
//
extern doom_boolean P_CheckPosition(mobj_t* thing, fixed_t x, fixed_t y);


//
// P_TryMove
// Attempt to move to a new position,
// crossing special lines unless MF_TELEPORT is set.
//
extern doom_boolean P_TryMove(mobj_t* thing, fixed_t x, fixed_t y);


//
// P_ThingHeightClip
// Takes a valid thing and adjusts the thing->floorz,
// thing->ceilingz, and possibly thing->z.
// This is called for all nearby monsters
// whenever a sector changes height.
// If the thing doesn't fit,
// the z will be set to the lowest value
// and false will be returned.
//
extern doom_boolean P_ThingHeightClip(mobj_t* thing);


//
// SLIDE MOVE
// Allows the player to slide along any angled walls.
//
fixed_t bestslidefrac;
fixed_t secondslidefrac;

line_t* bestslideline;
line_t* secondslideline;

mobj_t* slidemo;

fixed_t tmxmove;
fixed_t tmymove;


//
// P_HitSlideLine
// Adjusts the xmove / ymove
// so that the next move will slide along the wall.
//
extern void P_HitSlideLine(line_t* ld);


//
// PTR_SlideTraverse
//
extern doom_boolean PTR_SlideTraverse(intercept_t* in);


//
// P_SlideMove
// The momx / momy move is bad, so try to slide
// along a wall.
// Find the first line hit, move flush to it,
// and slide along it
//
// This is a kludgy mess.
//
extern void P_SlideMove(mobj_t* mo);

//
// P_LineAttack
//

//
// PTR_AimTraverse
// Sets linetaget and aimslope when a target is aimed at.
//
extern doom_boolean
PTR_AimTraverse(intercept_t* in);


//
// PTR_ShootTraverse
//
extern doom_boolean PTR_ShootTraverse(intercept_t* in);


//
// P_AimLineAttack
//
extern fixed_t P_AimLineAttack(mobj_t* t1, angle_t angle, fixed_t distance);


//
// P_LineAttack
// If damage == 0, it is just a test trace
// that will leave linetarget set.
//
extern void P_LineAttack(mobj_t* t1, angle_t angle, fixed_t distance, fixed_t slope, int damage);


//
// USE LINES
//
extern doom_boolean PTR_UseTraverse(intercept_t* in);


//
// P_UseLines
// Looks for special lines in front of the player to activate.
//
extern void P_UseLines(player_t* player);


//
// RADIUS ATTACK
//
mobj_t* bombsource;
mobj_t* bombspot;
int bombdamage;


//
// PIT_RadiusAttack
// "bombsource" is the creature
// that caused the explosion at "bombspot".
//
extern doom_boolean PIT_RadiusAttack(mobj_t* thing);


//
// P_RadiusAttack
// Source is the creature that caused the explosion at spot.
//
extern void P_RadiusAttack(mobj_t* spot, mobj_t* source, int damage);


//
// SECTOR HEIGHT CHANGING
// After modifying a sectors floor or ceiling height,
// call this routine to adjust the positions
// of all things that touch the sector.
//
// If anything doesn't fit anymore, true will be returned.
// If crunch is true, they will take damage
//  as they are being crushed.
// If Crunch is false, you should set the sector height back
//  the way it was and call P_ChangeSector again
//  to undo the changes.
//

//
// PIT_ChangeSector
//
extern doom_boolean PIT_ChangeSector(mobj_t* thing);


//
// P_ChangeSector
//
extern doom_boolean P_ChangeSector(sector_t* sector, doom_boolean crunch);
fixed_t opentop;
fixed_t openbottom;
fixed_t openrange;
fixed_t lowfloor;
intercept_t intercepts[MAXINTERCEPTS];
intercept_t* intercept_p;
divline_t trace;
doom_boolean earlyout;
int ptflags;


//
// P_AproxDistance
// Gives an estimation of distance (not exact)
//
extern fixed_t P_AproxDistance(fixed_t dx, fixed_t dy);


//
// P_PointOnLineSide
// Returns 0 or 1
//
extern int P_PointOnLineSide(fixed_t x, fixed_t y, line_t* line);


//
// P_BoxOnLineSide
// Considers the line to be infinite
// Returns side 0 or 1, -1 if box crosses the line.
//
extern int P_BoxOnLineSide(fixed_t* tmbox, line_t* ld);


//
// P_PointOnDivlineSide
// Returns 0 or 1.
//
extern int P_PointOnDivlineSide(fixed_t x, fixed_t y, divline_t* line);


//
// P_MakeDivline
//
extern void P_MakeDivline(line_t* li, divline_t* dl);


//
// P_InterceptVector
// Returns the fractional intercept point
// along the first divline.
// This is only called by the addthings
// and addlines traversers.
//
extern fixed_t P_InterceptVector(divline_t* v2, divline_t* v1);


//
// P_LineOpening
// Sets opentop and openbottom to the window
// through a two sided line.
// OPTIMIZE: keep this precalculated
//
extern void P_LineOpening(line_t* linedef);


//
// THING POSITION SETTING
//

//
// P_UnsetThingPosition
// Unlinks a thing from block map and sectors.
// On each position change, BLOCKMAP and other
// lookups maintaining lists ot things inside
// these structures need to be updated.
//
extern void P_UnsetThingPosition(mobj_t* thing);


//
// P_SetThingPosition
// Links a thing into both a block and a subsector
// based on it's x y.
// Sets thing->subsector properly
//
extern void P_SetThingPosition(mobj_t* thing);


//
// BLOCK MAP ITERATORS
// For each line/thing in the given mapblock,
// call the passed PIT_* function.
// If the function returns false,
// exit with false without checking anything else.
//

//
// P_BlockLinesIterator
// The validcount flags are used to avoid checking lines
// that are marked in multiple mapblocks,
// so increment validcount before the first call
// to P_BlockLinesIterator, then make one or more calls
// to it.
//
extern doom_boolean P_BlockLinesIterator(int x, int y, doom_boolean(*func)(line_t*));


//
// P_BlockThingsIterator
//
extern doom_boolean P_BlockThingsIterator(int x, int y, doom_boolean(*func)(mobj_t*));


//
// INTERCEPT ROUTINES
//

//
// PIT_AddLineIntercepts.
// Looks for lines in the given block
// that intercept the given trace
// to add to the intercepts list.
//
// A line is crossed if its endpoints
// are on opposite sides of the trace.
// Returns true if earlyout and a solid line hit.
//
extern doom_boolean PIT_AddLineIntercepts(line_t* ld);


//
// PIT_AddThingIntercepts
//
extern doom_boolean PIT_AddThingIntercepts(mobj_t* thing);


//
// P_TraverseIntercepts
// Returns true if the traverser function returns true
// for all lines.
// 
extern doom_boolean P_TraverseIntercepts(traverser_t func, fixed_t maxfrac);


//
// P_PathTraverse
// Traces a line from x1,y1 to x2,y2,
// calling the traverser function for each.
// Returns true if the traverser function returns true
// for all lines.
//
extern doom_boolean P_PathTraverse(fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2, int flags, doom_boolean(*trav) (intercept_t*));
#define STOPSPEED 0x1000
#define FRICTION 0xe800


//
// P_SetMobjState
// Returns true if the mobj is still present.
//
mapthing_t itemrespawnque[ITEMQUESIZE];
int itemrespawntime[ITEMQUESIZE];
int iquehead;
int iquetail;


extern fixed_t attackrange;


void G_PlayerReborn(int player);
void P_SpawnMapThing(mapthing_t* mthing);


extern doom_boolean P_SetMobjState(mobj_t* mobj, statenum_t state);


//
// P_ExplodeMissile  
//
extern void P_ExplodeMissile(mobj_t* mo);


//
// P_XYMovement  
//
extern void P_XYMovement(mobj_t* mo);


//
// P_ZMovement
//
extern void P_ZMovement(mobj_t* mo);


//
// P_NightmareRespawn
//
extern void P_NightmareRespawn(mobj_t* mobj);


//
// P_MobjThinker
//
extern void P_MobjThinker(mobj_t* mobj);


//
// P_SpawnMobj
//
extern mobj_t* P_SpawnMobj(fixed_t x, fixed_t y, fixed_t z, mobjtype_t type);


//
// P_RemoveMobj
//
extern void P_RemoveMobj(mobj_t* mobj);


//
// P_RespawnSpecials
//
extern void P_RespawnSpecials(void);


//
// P_SpawnPlayer
// Called when a player is spawned on the level.
// Most of the player structure stays unchanged
// between levels.
//
extern void P_SpawnPlayer(mapthing_t* mthing);


//
// P_SpawnMapThing
// The fields of the mapthing should
// already be in host byte order.
//
void P_SpawnMapThing(mapthing_t* mthing)
{
    int i;
    int bit;
    mobj_t* mobj;
    fixed_t x;
    fixed_t y;
    fixed_t z;

    // count deathmatch start positions
    if (mthing->type == 11)
    {
        if (deathmatch_p < &deathmatchstarts[10])
        {
            doom_memcpy(deathmatch_p, mthing, sizeof(*mthing));
            deathmatch_p++;
        }
        return;
    }

    // check for players specially
    if (mthing->type <= 4)
    {
        // save spots for respawning in network games
        playerstarts[mthing->type - 1] = *mthing;
        if (!deathmatch)
            P_SpawnPlayer(mthing);

        return;
    }

    // check for apropriate skill level
    if (!netgame && (mthing->options & 16))
        return;

    if (gameskill == sk_baby)
        bit = 1;
    else if (gameskill == sk_nightmare)
        bit = 4;
    else
        bit = 1 << (gameskill - 1);

    if (!(mthing->options & bit))
        return;

    // find which type to spawn
    for (i = 0; i < NUMMOBJTYPES; i++)
        if (mthing->type == mobjinfo[i].doomednum)
            break;

    if (i == NUMMOBJTYPES)
    {
        //I_Error("Error: P_SpawnMapThing: Unknown type %i at (%i, %i)",
        //        mthing->type,
        //        mthing->x, mthing->y);
        
        
        doom_strcpy(error_buf, "Error: P_SpawnMapThing: Unknown type ");
        doom_concat(error_buf, doom_itoa(mthing->type, 10));
        doom_concat(error_buf, " at (");
        doom_concat(error_buf, doom_itoa(mthing->x, 10));
        doom_concat(error_buf, ", ");
        doom_concat(error_buf, doom_itoa(mthing->y, 10));
        doom_concat(error_buf, ")");
        I_Error(error_buf);
    }

    // don't spawn keycards and players in deathmatch
    if (deathmatch && mobjinfo[i].flags & MF_NOTDMATCH)
        return;

    // don't spawn any monsters if -nomonsters
    if (nomonsters
        && (i == MT_SKULL
            || (mobjinfo[i].flags & MF_COUNTKILL)))
    {
        return;
    }

    // spawn it
    x = mthing->x << FRACBITS;
    y = mthing->y << FRACBITS;

    if (mobjinfo[i].flags & MF_SPAWNCEILING)
        z = ONCEILINGZ;
    else
        z = ONFLOORZ;

    mobj = P_SpawnMobj(x, y, z, i);
    mobj->spawnpoint = *mthing;

    if (mobj->tics > 0)
        mobj->tics = 1 + (P_Random() % mobj->tics);
    if (mobj->flags & MF_COUNTKILL)
        totalkills++;
    if (mobj->flags & MF_COUNTITEM)
        totalitems++;

    mobj->angle = ANG45 * (mthing->angle / 45);
    if (mthing->options & MTF_AMBUSH)
        mobj->flags |= MF_AMBUSH;
}


//
// GAME SPAWN FUNCTIONS
//

//
// P_SpawnPuff
//
extern void P_SpawnPuff(fixed_t x, fixed_t y, fixed_t z);


//
// P_SpawnBlood
// 
extern void P_SpawnBlood(fixed_t x, fixed_t y, fixed_t z, int damage);


//
// P_CheckMissileSpawn
// Moves the missile forward a bit
//  and possibly explodes it right there.
//
extern void P_CheckMissileSpawn(mobj_t* th);


//
// P_SpawnMissile
//
extern mobj_t* P_SpawnMissile(mobj_t* source, mobj_t* dest, mobjtype_t type);


//
// P_SpawnPlayerMissile
// Tries to aim at a nearby monster
//
extern void P_SpawnPlayerMissile(mobj_t* source, mobjtype_t type);
plat_t* activeplats[MAXPLATS];


//
// Move a plat up and down
//
extern void T_PlatRaise(plat_t* plat);


//
// Do Platforms
//  "amount" is only used for SOME platforms.
//
extern int EV_DoPlat(line_t* line, plattype_e type, int amount);

extern void P_ActivateInStasis(int tag);

extern void EV_StopPlat(line_t* line);

extern void P_AddActivePlat(plat_t* plat);

extern void P_RemoveActivePlat(plat_t* plat);
#define LOWERSPEED (FRACUNIT*6)
#define RAISESPEED (FRACUNIT*6)

#define WEAPONBOTTOM (128*FRACUNIT)
#define WEAPONTOP (32*FRACUNIT)

// plasma cells for a bfg attack
#define BFGCELLS 40     


fixed_t swingx;
fixed_t swingy;
fixed_t bulletslope;


//
// P_SetPsprite
//
extern void P_SetPsprite(player_t* player, int position, statenum_t stnum);


//
// P_BringUpWeapon
// Starts bringing the pending weapon up
// from the bottom of the screen.
// Uses player
//
extern void P_BringUpWeapon(player_t* player);


//
// P_CheckAmmo
// Returns true if there is enough ammo to shoot.
// If not, selects the next weapon to use.
//
extern doom_boolean P_CheckAmmo(player_t* player);


//
// P_FireWeapon.
//
extern void P_FireWeapon(player_t* player);


//
// P_DropWeapon
// Player died, so put the weapon away.
//
extern void P_DropWeapon(player_t* player);


//
// A_WeaponReady
// The player can fire the weapon
// or change to another weapon at this time.
// Follows after getting weapon up,
// or after previous attack/fire sequence.
//
extern void A_WeaponReady(player_t* player, pspdef_t* psp);


//
// A_ReFire
// The player can re-fire the weapon
// without lowering it entirely.
//
extern void A_ReFire(player_t* player, pspdef_t* psp);


extern void A_CheckReload(player_t* player, pspdef_t* psp);


//
// A_Lower
// Lowers current weapon,
//  and changes weapon at bottom.
//
extern void A_Lower(player_t* player, pspdef_t* psp);


//
// A_Raise
//
extern void A_Raise(player_t* player, pspdef_t* psp);


//
// A_GunFlash
//
extern void A_GunFlash(player_t* player, pspdef_t* psp);


//
// WEAPON ATTACKS
//

//
// A_Punch
//
extern void A_Punch(player_t* player, pspdef_t* psp);


//
// A_Saw
//
extern void A_Saw(player_t* player, pspdef_t* psp);


//
// A_FireMissile
//
extern void A_FireMissile(player_t* player, pspdef_t* psp);


//
// A_FireBFG
//
extern void A_FireBFG(player_t* player, pspdef_t* psp);


//
// A_FirePlasma
//
extern void A_FirePlasma(player_t* player, pspdef_t* psp);


//
// P_BulletSlope
// Sets a slope so a near miss is at aproximately
// the height of the intended target
//
extern void P_BulletSlope(mobj_t* mo);


//
// P_GunShot
//
extern void P_GunShot(mobj_t* mo, doom_boolean accurate);


//
// A_FirePistol
//
extern void A_FirePistol(player_t* player, pspdef_t* psp);


//
// A_FireShotgun
//
extern void A_FireShotgun(player_t* player, pspdef_t* psp);


//
// A_FireShotgun2
//
extern void A_FireShotgun2(player_t* player, pspdef_t* psp);


//
// A_FireCGun
//
extern void A_FireCGun(player_t* player, pspdef_t* psp);


//
// ?
//
extern void A_Light0(player_t* player, pspdef_t* psp);

extern void A_Light1(player_t* player, pspdef_t* psp);

extern void A_Light2(player_t* player, pspdef_t* psp);


//
// A_BFGSpray
// Spawn a BFG explosion on every monster in view
//
extern void A_BFGSpray(mobj_t* mo);


//
// A_BFGsound
//
extern void A_BFGsound(player_t* player, pspdef_t* psp);


//
// P_SetupPsprites
// Called at start of level for each player.
//
extern void P_SetupPsprites(player_t* player);


//
// P_MovePsprites
// Called every tic by player thinking routine.
//
extern void P_MovePsprites(player_t* player);
#define PADSAVEP() save_p += (4 - ((long long)save_p & 3)) & 3


byte* save_p;


// TODO: [pd] We are loading/saving raw pointers. It will not work with saves from 32bits system. We need to rewrite those functions.
//
// P_ArchivePlayers
//
extern void P_ArchivePlayers(void);


//
// P_UnArchivePlayers
//
extern void P_UnArchivePlayers(void);


//
// P_ArchiveWorld
//
extern void P_ArchiveWorld(void);


//
// P_UnArchiveWorld
//
extern void P_UnArchiveWorld(void);


//
// Thinkers
//
typedef enum
{
    tc_end,
    tc_mobj
} thinkerclass_t;


//
// P_ArchiveThinkers
//
extern void P_ArchiveThinkers(void);


//
// P_UnArchiveThinkers
//
extern void P_UnArchiveThinkers(void);


//
// P_ArchiveSpecials
//
enum
{
    tc_ceiling,
    tc_door,
    tc_floor,
    tc_plat,
    tc_flash,
    tc_strobe,
    tc_glow,
    tc_endspecials
} specials_e;


//
// Things to handle:
//
// T_MoveCeiling, (ceiling_t: sector_t * swizzle), - active list
// T_VerticalDoor, (vldoor_t: sector_t * swizzle),
// T_MoveFloor, (floormove_t: sector_t * swizzle),
// T_LightFlash, (lightflash_t: sector_t * swizzle),
// T_StrobeFlash, (strobe_t: sector_t *),
// T_Glow, (glow_t: sector_t *),
// T_PlatRaise, (plat_t: sector_t *), - active list
//
extern void P_ArchiveSpecials(void);


//
// P_UnArchiveSpecials
//
extern void P_UnArchiveSpecials(void);
#define MAX_DEATHMATCH_STARTS        10


//
// MAP related Lookup tables.
// Store VERTEXES, LINEDEFS, SIDEDEFS, etc.
//
int numvertexes;
vertex_t* vertexes;

int numsegs;
seg_t* segs;

int numsectors;
sector_t* sectors;

int numsubsectors;
subsector_t* subsectors;

int numnodes;
node_t* nodes;

int numlines;
line_t* lines;

int numsides;
side_t* sides;

// BLOCKMAP
// Created from axis aligned bounding box
// of the map, a rectangular array of
// blocks of size ...
// Used to speed up collision detection
// by spatial subdivision in 2D.
//
// Blockmap size.
int bmapwidth;
int bmapheight; // size in mapblocks
short* blockmap; // int for larger maps
// offsets in blockmap are from here
short* blockmaplump;
// origin of block map
fixed_t bmaporgx;
fixed_t bmaporgy;
// for thing chains
mobj_t** blocklinks;

// REJECT
// For fast sight rejection.
// Speeds up enemy AI by skipping detailed
//  LineOf Sight calculation.
// Without special effect, this could be
//  used as a PVS lookup as well.
//
byte* rejectmatrix;

mapthing_t deathmatchstarts[MAX_DEATHMATCH_STARTS];
mapthing_t* deathmatch_p;
mapthing_t playerstarts[MAXPLAYERS];


void P_SpawnMapThing(mapthing_t* mthing);


//
// P_LoadVertexes
//
extern void P_LoadVertexes(int lump);


//
// P_LoadSegs
//
extern void P_LoadSegs(int lump);


//
// P_LoadSubsectors
//
extern void P_LoadSubsectors(int lump);


//
// P_LoadSectors
//
extern void P_LoadSectors(int lump);


//
// P_LoadNodes
//
extern void P_LoadNodes(int lump);


//
// P_LoadThings
//
extern void P_LoadThings(int lump);


//
// P_LoadLineDefs
// Also counts secret lines for intermissions.
//
extern void P_LoadLineDefs(int lump);


//
// P_LoadSideDefs
//
extern void P_LoadSideDefs(int lump);


//
// P_LoadBlockMap
//
extern void P_LoadBlockMap(int lump);


//
// P_GroupLines
// Builds sector line lists and subsector sector numbers.
// Finds block bounding boxes for sectors.
//
extern void P_GroupLines(void);


//
// P_SetupLevel
//
extern void P_SetupLevel(int episode, int map, int playermask, skill_t skill);


//
// P_Init
//
extern void P_Init(void);
fixed_t sightzstart; // eye z of looker
fixed_t topslope;
fixed_t bottomslope; // slopes to top and bottom of target

divline_t strace; // from t1 to t2
fixed_t t2x;
fixed_t t2y;

int sightcounts[2];


//
// P_DivlineSide
// Returns side 0 (front), 1 (back), or 2 (on).
//
extern int P_DivlineSide(fixed_t x, fixed_t y, divline_t* node);


//
// P_InterceptVector2
// Returns the fractional intercept point
// along the first divline.
// This is only called by the addthings and addlines traversers.
//
extern fixed_t P_InterceptVector2(divline_t* v2, divline_t* v1);


//
// P_CrossSubsector
// Returns true
//  if strace crosses the given subsector successfully.
//
extern doom_boolean P_CrossSubsector(int num);


//
// P_CrossBSPNode
// Returns true
//  if strace crosses the given node successfully.
//
extern doom_boolean P_CrossBSPNode(int bspnum);


//
// P_CheckSight
// Returns true
//  if a straight line between t1 and t2 is unobstructed.
// Uses REJECT.
//
extern doom_boolean P_CheckSight(mobj_t* t1, mobj_t* t2);
#define MAXANIMS 32
#define MAXLINEANIMS 64

// 20 adjoining sectors max! [dsl] Useless comment is useless
#define MAX_ADJOINING_SECTORS 20


//
// Animating textures and planes
// There is another anim_t used in wi_stuff, unrelated.
//
typedef struct
{
    doom_boolean istexture;
    int picnum;
    int basepic;
    int numpics;
    int speed;
} anim_t;

//
// source animation definition
//
typedef struct
{
    doom_boolean istexture; // if false, it is a flat
    char* endname;
    char* startname;
    int speed;
} animdef_t;


doom_boolean levelTimer;
int levelTimeCount;
short numlinespecials;
line_t* linespeciallist[MAXLINEANIMS];


extern anim_t anims[MAXANIMS];
extern anim_t* lastanim;


//
// P_InitPicAnims
//

// Floor/ceiling animation sequences,
//  defined by first and last frame,
//  i.e. the flat (64x64 tile) name to
//  be used.
// The full animation sequence is given
//  using all the flats between the start
//  and end entry, in the order found in
//  the WAD file.
//
animdef_t* animdefs;

anim_t anims[MAXANIMS];
anim_t* lastanim;


//
//      Animating line specials
//

extern short numlinespecials;
extern line_t* linespeciallist[MAXLINEANIMS];


extern void P_InitPicAnims(void);


//
// UTILITIES
//

//
// getSide()
// Will return a side_t*
//  given the number of the current sector,
//  the line number, and the side (0/1) that you want.
//
extern side_t* getSide(int currentSector, int line, int side);

//
// getSector()
// Will return a sector_t*
//  given the number of the current sector,
//  the line number and the side (0/1) that you want.
//
extern sector_t* getSector(int currentSector, int line, int side);


//
// twoSided()
// Given the sector number and the line number,
//  it will tell you whether the line is two-sided or not.
//
extern int twoSided(int sector, int line);


//
// getNextSector()
// Return sector_t * of sector next to current.
// 0 if not two-sided line
//
extern sector_t* getNextSector(line_t* line, sector_t* sec);


//
// P_FindLowestFloorSurrounding()
// FIND LOWEST FLOOR HEIGHT IN SURROUNDING SECTORS
//
extern fixed_t P_FindLowestFloorSurrounding(sector_t* sec);


//
// P_FindHighestFloorSurrounding()
// FIND HIGHEST FLOOR HEIGHT IN SURROUNDING SECTORS
//
extern fixed_t P_FindHighestFloorSurrounding(sector_t* sec);


//
// P_FindNextHighestFloor
// FIND NEXT HIGHEST FLOOR IN SURROUNDING SECTORS
// Note: this should be doable w/o a fixed array.
extern fixed_t P_FindNextHighestFloor(sector_t* sec, int currentheight);


//
// FIND LOWEST CEILING IN THE SURROUNDING SECTORS
//
extern fixed_t P_FindLowestCeilingSurrounding(sector_t* sec);


//
// FIND HIGHEST CEILING IN THE SURROUNDING SECTORS
//
extern fixed_t P_FindHighestCeilingSurrounding(sector_t* sec);


//
// RETURN NEXT SECTOR # THAT LINE TAG REFERS TO
//
extern int P_FindSectorFromLineTag(line_t* line, int start);


//
// Find minimum light from an adjacent sector
//
extern int P_FindMinSurroundingLight(sector_t* sector, int max);


//
// EVENTS
// Events are operations triggered by using, crossing,
// or shooting special lines, or by timed thinkers.
//

//
// P_CrossSpecialLine - TRIGGER
// Called every time a thing origin is about
//  to cross a line with a non 0 special.
//
extern void P_CrossSpecialLine(int linenum, int side, mobj_t* thing);


//
// P_ShootSpecialLine - IMPACT SPECIALS
// Called when a thing shoots a special line.
//
extern void P_ShootSpecialLine(mobj_t* thing, line_t* line);


//
// P_PlayerInSpecialSector
// Called every tic frame
//  that the player origin is in a special sector
//
extern void P_PlayerInSpecialSector(player_t* player);


//
// P_UpdateSpecials
// Animate planes, scroll walls, etc.
//
extern void P_UpdateSpecials(void);


//
// Special Stuff that can not be categorized
//
extern int EV_DoDonut(line_t* line);


//
// SPECIAL SPAWNING
//

//
// P_SpawnSpecials
// After the map has been loaded, scan for specials
//  that spawn thinkers
//

// Parses command line parameters.
extern void P_SpawnSpecials(void);
switchlist_t* alphSwitchList;

int switchlist[MAXSWITCHES * 2];
int numswitches;
button_t buttonlist[MAXBUTTONS];


//
// P_InitSwitchList
// Only called at game initialization.
//
extern void P_InitSwitchList(void);


//
// Start a button counting down till it turns off.
//
extern void P_StartButton(line_t* line, bwhere_e w, int texture, int time);


//
// Function that changes wall texture.
// Tell it if switch is ok to use again (1=yes, it's a button).
//
extern void P_ChangeSwitchTexture(line_t* line, int useAgain);


//
// P_UseSpecialLine
// Called when a thing uses a special line.
// Only the front sides of lines are usable.
//
extern doom_boolean P_UseSpecialLine(mobj_t* thing, line_t* line, int side);
extern int EV_Teleport(line_t* line, int side, mobj_t* thing);
int leveltime;

//
// THINKERS
// All thinkers should be allocated by Z_Malloc
// so they can be operated on uniformly.
// The actual structures will vary in size,
// but the first element must be thinker_t.
//

// Both the head and tail of the thinker list.
thinker_t thinkercap;


//
// P_InitThinkers
//
extern void P_InitThinkers(void);


//
// P_AddThinker
// Adds a new thinker at the end of the list.
//
extern void P_AddThinker(thinker_t* thinker);


//
// P_RemoveThinker
// Deallocation is lazy -- it will not actually be freed
// until its thinking turn comes up.
//
extern void P_RemoveThinker(thinker_t* thinker);


//
// P_RunThinkers
//
extern void P_RunThinkers(void);


//
// P_Ticker
//
extern void P_Ticker(void);
#define INVERSECOLORMAP 32

// 16 pixels of bob
#define MAXBOB 0x100000        

#define ANG5 (ANG90/18)


//
// Movement.
//

doom_boolean onground;


//
// P_Thrust
// Moves the given origin along a given angle.
//
extern void P_Thrust(player_t* player, angle_t angle, fixed_t move);


//
// P_CalcHeight
// Calculate the walking / running height adjustment
//
extern void P_CalcHeight(player_t* player);

//
// P_MovePlayer
//
extern void P_MovePlayer(player_t* player);


//
// P_DeathThink
// Fall on your face when dying.
// Decrease POV height to floor height.
//
extern void P_DeathThink(player_t* player);


//
// P_PlayerThink
//
extern void P_PlayerThink(player_t* player);
#define MAXSEGS 32


//
// ClipWallSegment
// Clips the given range of columns
// and includes it in the new clip list.
//
typedef struct
{
    int first;
    int last;
} cliprange_t;


seg_t* curline;
side_t* sidedef;
line_t* linedef;
sector_t* frontsector;
sector_t* backsector;

drawseg_t drawsegs[MAXDRAWSEGS];
drawseg_t* ds_p;

// newend is one past the last valid seg
cliprange_t* newend;
cliprange_t solidsegs[MAXSEGS];

int checkcoord[12][4];


void R_StoreWallRange(int start, int stop);


//
// R_ClearDrawSegs
//
extern void R_ClearDrawSegs(void);


//
// R_ClipSolidWallSegment
// Does handle solid walls,
//  e.g. single sided LineDefs (middle texture)
//  that entirely block the view.
// 
extern void R_ClipSolidWallSegment(int first, int last);

//
// R_ClipPassWallSegment
// Clips the given range of columns,
//  but does not includes it in the clip list.
// Does handle windows,
//  e.g. LineDefs with upper and lower texture.
//
extern void R_ClipPassWallSegment(int first, int last);

//
// R_ClearClipSegs
//
extern void R_ClearClipSegs(void);

//
// R_AddLine
// Clips the given segment
// and adds any visible pieces to the line list.
//
extern void R_AddLine(seg_t* line);

//
// R_CheckBBox
// Checks BSP node/subtree bounding box.
// Returns true
//  if some part of the bbox might be visible.
//
extern doom_boolean R_CheckBBox(fixed_t* bspcoord);

//
// R_Subsector
// Determine floor/ceiling planes.
// Add sprites of things in sector.
// Draw one or more line segments.
//
extern void R_Subsector(int num);


//
// RenderBSPNode
// Renders all subsectors below a given node,
//  traversing subtree recursively.
// Just call with BSP root.
extern void R_RenderBSPNode(int bspnum);
#if defined(DOOM_WIN32)

// #define strncasecmp strnicmp
#elif defined(DOOM_APPLE)

#else
#ifdef LINUX
//#include  <alloca.h>
#endif
#endif
//#include "r_data.h"


//
// Graphics.
// DOOM graphics for walls and sprites
// is stored in vertical runs of opaque pixels (posts).
// A column is composed of zero or more posts,
// a patch or sprite is composed of zero or more columns.
//


//
// Texture definition.
// Each texture is composed of one or more patches,
// with patches being lumps stored in the WAD.
// The lumps are referenced by number, and patched
// into the rectangular texture space using origin
// and possibly other attributes.
//
typedef struct
{
    short originx;
    short originy;
    short patch;
    short stepdir;
    short colormap;
} mappatch_t;


//
// Texture definition.
// A DOOM wall texture is a list of patches
// which are to be combined in a predefined order.
//
typedef struct
{
    char name[8];
    doom_boolean masked;
    short width;
    short height;
    //void **columndirectory; // OBSOLETE
    int columndirectory; // [pd] If it's not used, at least make sure it's the right size! Pointers are 8 bytes in x64
    short patchcount;
    mappatch_t patches[1];
} maptexture_t;


// A single patch from a texture definition,
// basically a rectangular area within
// the texture rectangle.
typedef struct
{
    // Block origin (allways UL),
    // which has allready accounted
    // for the internal origin of the patch.
    int originx;
    int originy;
    int patch;
} texpatch_t;


// A maptexturedef_t describes a rectangular texture,
// which is composed of one or more mappatch_t structures
// that arrange graphic patches.
typedef struct
{
    // Keep name for switch changing, etc.
    char name[8];
    short width;
    short height;

    // All the patches[patchcount]
    //  are drawn back to front into the cached texture.
    short patchcount;
    texpatch_t patches[1];
} texture_t;


int firstflat;
int lastflat;
int numflats;

int firstpatch;
int lastpatch;
int numpatches;

int firstspritelump;
int lastspritelump;
int numspritelumps;

int numtextures;
texture_t** textures;

int* texturewidthmask;
// needed for texture pegging
fixed_t* textureheight;
int* texturecompositesize;
short** texturecolumnlump;
unsigned short** texturecolumnofs;
byte** texturecomposite;

// for global animation
int* flattranslation;
int* texturetranslation;

// needed for pre rendering
fixed_t* spritewidth;
fixed_t* spriteoffset;
fixed_t* spritetopoffset;

lighttable_t* colormaps;

int flatmemory;
int texturememory;
int spritememory;


//
// MAPTEXTURE_T CACHING
// When a texture is first needed,
//  it counts the number of composite columns
//  required in the texture and allocates space
//  for a column directory and any new columns.
// The directory will simply point inside other patches
//  if there is only one patch in a given column,
//  but any columns with multiple patches
//  will have new column_ts generated.
//


//
// R_DrawColumnInCache
// Clip and draw a column
//  from a patch into a cached post.
//
extern void R_DrawColumnInCache(column_t* patch, byte* cache, int originy, int cacheheight);


//
// R_GenerateComposite
// Using the texture definition,
//  the composite texture is created from the patches,
//  and each column is cached.
//
extern void R_GenerateComposite(int texnum);


//
// R_GenerateLookup
//
extern void R_GenerateLookup(int texnum);


//
// R_GetColumn
//
extern byte* R_GetColumn(int tex, int col);


//
// R_InitTextures
// Initializes the texture list
//  with the textures from the world map.
//
extern void R_InitTextures(void);


//
// R_InitFlats
//
extern void R_InitFlats(void);


//
// R_InitSpriteLumps
// Finds the width and hoffset of all sprites in the wad,
//  so the sprite does not need to be cached completely
//  just for having the header info ready during rendering.
//
extern void R_InitSpriteLumps(void);


//
// R_InitColormaps
//
extern void R_InitColormaps(void);


//
// R_InitData
// Locates all the lumps
//  that will be used by all views
// Must be called after W_Init.
//
extern void R_InitData(void);


//
// R_FlatNumForName
// Retrieval, get a flat number for a flat name.
//
extern int R_FlatNumForName(char* name);


//
// R_CheckTextureNumForName
// Check whether texture is available.
// Filter out NoTexture indicator.
//
extern int R_CheckTextureNumForName(char* name);


//
// R_TextureNumForName
// Calls R_CheckTextureNumForName,
//  aborts with error message.
//
extern int R_TextureNumForName(char* name);


//
// R_PrecacheLevel
// Preloads all relevant graphics for the level.
//
extern void R_PrecacheLevel(void);
#define MAXWIDTH 1120
#define MAXHEIGHT 832

// status bar height at bottom of screen
#define SBARHEIGHT 32

#define FUZZTABLE 50 
#define FUZZOFF (SCREENWIDTH)


//
// All drawing to the view buffer is accomplished in this file.
// The other refresh files only know about ccordinates,
//  not the architecture of the frame buffer.
// Conveniently, the frame buffer is a linear one,
//  and we need only the base address,
//  and the total size == width*height*depth/8.,
//

byte* viewimage;
int viewwidth;
int scaledviewwidth;
int viewheight;
int viewwindowx;
int viewwindowy;
byte* ylookup[MAXHEIGHT];
int columnofs[MAXWIDTH];

// Color tables for different players,
//  translate a limited part to another
//  (color ramps used for  suit colors).
//
byte translations[3][256];

//
// R_DrawColumn
// Source is the top of the column to scale.
//
lighttable_t* dc_colormap;
int dc_x;
int dc_yl;
int dc_yh;
fixed_t dc_iscale;
fixed_t dc_texturemid;

// first pixel in a column (possibly virtual) 
byte* dc_source;

// just for profiling 
int dccount;

int fuzzoffset[FUZZTABLE];

int fuzzpos;

byte* dc_translation;
byte* translationtables;


//
// A column is a vertical slice/span from a wall texture that,
// given the DOOM style restrictions on the view orientation,
// will always have constant z depth.
// Thus a special case loop for very fast rendering can
// be used. It has also been used with Wolfenstein 3D.
// 
extern void R_DrawColumn(void);


//
// Spectre/Invisibility.
//

//
// Framebuffer postprocessing.
// Creates a fuzzy image by copying pixels
//  from adjacent ones to left and right.
// Used with an all black colormap, this
//  could create the SHADOW effect,
//  i.e. spectres and invisible players.
//
extern void R_DrawFuzzColumn(void);


//
// R_DrawTranslatedColumn
// Used to draw player sprites
//  with the green colorramp mapped to others.
// Could be used with different translation
//  tables, e.g. the lighter colored version
//  of the BaronOfHell, the HellKnight, uses
//  identical sprites, kinda brightened up.
//
extern void R_DrawTranslatedColumn(void);


//
// R_InitTranslationTables
// Creates the translation tables to map
// the green color ramp to gray, brown, red.
// Assumes a given structure of the PLAYPAL.
// Could be read from a lump instead.
//
extern void R_InitTranslationTables(void);


//
// R_DrawSpan 
// With DOOM style restrictions on view orientation,
// the floors and ceilings consist of horizontal slices
// or spans with constant z depth.
// However, rotation around the world z axis is possible,
// thus this mapping, while simpler and faster than
// perspective correct texture mapping, has to traverse
// the texture at an angle in all but a few cases.
// In consequence, flats are not stored by column (like walls),
// and the inner loop has to step in texture space u and v.
//
int ds_y;
int ds_x1;
int ds_x2;

lighttable_t* ds_colormap;

fixed_t ds_xfrac;
fixed_t ds_yfrac;
fixed_t ds_xstep;
fixed_t ds_ystep;

// start of a 64*64 tile image 
byte* ds_source;

// just for profiling
int dscount;


//
// Draws the actual span.
extern void R_DrawSpan(void);

//
// R_InitBuffer 
// Creats lookup tables that avoid
//  multiplies and other hazzles
//  for getting the framebuffer address
//  of a pixel to draw.
//
extern void R_InitBuffer(int width, int height);


//
// R_FillBackScreen
// Fills the back screen with a pattern
//  for variable screen sizes
// Also draws a beveled edge.
//
extern void R_FillBackScreen(void);


//
// Copy a screen buffer.
//
extern void R_VideoErase(unsigned ofs, int count);


//
// R_DrawViewBorder
// Draws the border around the view
//  for different size windows?
//
void V_MarkRect(int x, int y, int width, int height);

extern void R_DrawViewBorder(void);
#define FIELDOFVIEW 2048 // Fineangles in the SCREENWIDTH wide window.
#define DISTMAP 2


int viewangleoffset;

// increment every time a check is made
int validcount = 1;

lighttable_t* fixedcolormap;

int centerx;
int centery;

fixed_t centerxfrac;
fixed_t centeryfrac;
fixed_t projection;

// just for profiling purposes
int framecount;

int sscount;
int linecount;
int loopcount;

fixed_t viewx;
fixed_t viewy;
fixed_t viewz;

angle_t viewangle;

fixed_t viewcos;
fixed_t viewsin;

player_t* viewplayer;

// 0 = high, 1 = low
int detailshift;

//
// precalculated math tables
//
angle_t clipangle;

// The viewangletox[viewangle + FINEANGLES/4] lookup
// maps the visible view angles to screen X coordinates,
// flattening the arc to a flat projection plane.
// There will be many angles mapped to the same X. 
int viewangletox[FINEANGLES / 2];

// The xtoviewangleangle[] table maps a screen pixel
// to the lowest viewangle that maps back to x ranges
// from clipangle to -clipangle.
angle_t xtoviewangle[SCREENWIDTH + 1];

fixed_t* finecosine;

lighttable_t* scalelight[LIGHTLEVELS][MAXLIGHTSCALE];
lighttable_t* scalelightfixed[MAXLIGHTSCALE];
lighttable_t* zlight[LIGHTLEVELS][MAXLIGHTZ];

// bumped light from gun blasts
int extralight;

doom_boolean setsizeneeded;
int setblocks;
int setdetail;


extern lighttable_t** walllights;
extern int detailLevel;
extern int screenblocks;


void (*colfunc) (void);
void (*basecolfunc) (void);
void (*fuzzcolfunc) (void);
void (*transcolfunc) (void);
void (*spanfunc) (void);


//
// R_AddPointToBox
// Expand a given bbox
// so that it encloses a given point.
//
extern void R_AddPointToBox(int x, int y, fixed_t* box);


//
// R_PointOnSide
// Traverse BSP (sub) tree,
//  check point against partition plane.
// Returns side 0 (front) or 1 (back).
//
extern int R_PointOnSide(fixed_t x, fixed_t y, node_t* node);


extern int R_PointOnSegSide(fixed_t x, fixed_t y, seg_t* line);


//
// R_PointToAngle
// To get a global angle from cartesian coordinates,
//  the coordinates are flipped until they are in
//  the first octant of the coordinate system, then
//  the y (<=x) is scaled and divided by x to get a
//  tangent (slope) value which is looked up in the
//  tantoangle[] table.

extern angle_t R_PointToAngle(fixed_t x, fixed_t y);


extern angle_t R_PointToAngle2(fixed_t x1, fixed_t y1, fixed_t x2, fixed_t y2);


extern fixed_t R_PointToDist(fixed_t x, fixed_t y);


//
// R_InitPointToAngle
//
void R_InitPointToAngle(void)
{
}


//
// R_ScaleFromGlobalAngle
// Returns the texture mapping scale
//  for the current line (horizontal span)
//  at the given angle.
// rw_distance must be calculated first.
//
extern fixed_t R_ScaleFromGlobalAngle(angle_t visangle);


//
// R_InitTables
//
void R_InitTables(void)
{
}


//
// R_InitTextureMapping
//
extern void R_InitTextureMapping(void);


//
// R_InitLightTables
// Only inits the zlight table,
// because the scalelight table changes with view size.
//

extern void R_InitLightTables(void);


//
// R_SetViewSize
// Do not really change anything here,
//  because it might be in the middle of a refresh.
// The change will take effect next refresh.
//

extern void R_SetViewSize(int blocks, int detail);


//
// R_ExecuteSetViewSize
//
extern void R_ExecuteSetViewSize(void);


//
// R_Init
//
extern void R_Init(void);


//
// R_PointInSubsector
//
extern subsector_t* R_PointInSubsector(fixed_t x, fixed_t y);


//
// R_SetupFrame
//
extern void R_SetupFrame(player_t* player);


//
// R_RenderView
//
extern void R_RenderPlayerView(player_t* player);
#define MAXVISPLANES        128
#define MAXOPENINGS        SCREENWIDTH*64


planefunction_t floorfunc;
planefunction_t ceilingfunc;

//
// opening
//

// Here comes the obnoxious "visplane".
visplane_t visplanes[MAXVISPLANES];
visplane_t* lastvisplane;
visplane_t* floorplane;
visplane_t* ceilingplane;

// ?
short openings[MAXOPENINGS];
short* lastopening;

//
// Clip values are the solid pixel bounding the range.
//  floorclip starts out SCREENHEIGHT
//  ceilingclip starts out -1
//
short floorclip[SCREENWIDTH];
short ceilingclip[SCREENWIDTH];

//
// spanstart holds the start of a plane span
// initialized to 0 at start
//
int spanstart[SCREENHEIGHT];
int spanstop[SCREENHEIGHT];

//
// texture mapping
//
lighttable_t** planezlight;
fixed_t planeheight;

fixed_t yslope[SCREENHEIGHT];
fixed_t distscale[SCREENWIDTH];
fixed_t basexscale;
fixed_t baseyscale;

fixed_t cachedheight[SCREENHEIGHT];
fixed_t cacheddistance[SCREENHEIGHT];
fixed_t cachedxstep[SCREENHEIGHT];
fixed_t cachedystep[SCREENHEIGHT];


//
// R_InitPlanes
// Only at game startup.
//
void R_InitPlanes(void)
{
    // Doh!
}


//
// R_MapPlane
//
// Uses global vars:
//  planeheight
//  ds_source
//  basexscale
//  baseyscale
//  viewx
//  viewy
//
// BASIC PRIMITIVE
//
extern void R_MapPlane(int y, int x1, int x2);


//
// R_ClearPlanes
// At begining of frame.
//
extern void R_ClearPlanes(void);


//
// R_FindPlane
//
extern visplane_t* R_FindPlane(fixed_t height, int picnum, int lightlevel);


//
// R_CheckPlane
//
extern visplane_t* R_CheckPlane(visplane_t* pl, int start, int stop);


//
// R_MakeSpans
//
extern void R_MakeSpans(int x, int t1, int b1, int t2, int b2);


//
// R_DrawPlanes
// At the end of each frame.
//
extern void R_DrawPlanes(void);
#define HEIGHTBITS 12
#define HEIGHTUNIT (1<<HEIGHTBITS)


// OPTIMIZE: closed two sided lines as single sided

// True if any of the segs textures might be visible.
doom_boolean segtextured;

// False if the back side is the same plane.
doom_boolean markfloor;
doom_boolean markceiling;

doom_boolean maskedtexture;
int toptexture;
int bottomtexture;
int midtexture;

angle_t rw_normalangle;
// angle to line origin
int rw_angle1;

//
// regular wall
//
int rw_x;
int rw_stopx;
angle_t rw_centerangle;
fixed_t rw_offset;
fixed_t rw_distance;
fixed_t rw_scale;
fixed_t rw_scalestep;
fixed_t rw_midtexturemid;
fixed_t rw_toptexturemid;
fixed_t rw_bottomtexturemid;

int worldtop;
int worldbottom;
int worldhigh;
int worldlow;

fixed_t pixhigh;
fixed_t pixlow;
fixed_t pixhighstep;
fixed_t pixlowstep;

fixed_t topfrac;
fixed_t topstep;

fixed_t bottomfrac;
fixed_t bottomstep;

lighttable_t** walllights;

short* maskedtexturecol;


//
// R_RenderMaskedSegRange
//
extern void R_RenderMaskedSegRange(drawseg_t* ds, int x1, int x2);


//
// R_RenderSegLoop
// Draws zero, one, or two textures (and possibly a masked
//  texture) for walls.
// Can draw or mark the starting pixel of floor and ceiling
//  textures.
// CALLED: CORE LOOPING ROUTINE.
//
extern void R_RenderSegLoop(void);


//
// R_StoreWallRange
// A wall segment will be drawn
//  between start and stop pixels (inclusive).
//
extern void R_StoreWallRange(int start, int stop);
int skyflatnum;
int skytexture;
int skytexturemid;


//
// R_InitSkyMap
// Called whenever the view size changes.
//
extern void R_InitSkyMap(void);
#define MINZ                                (FRACUNIT*4)
#define BASEYCENTER                        100


typedef struct
{
    int x1;
    int x2;

    int column;
    int topclip;
    int bottomclip;
} maskdraw_t;


//
// Sprite rotation 0 is facing the viewer,
//  rotation 1 is one angle turn CLOCKWISE around the axis.
// This is not the same as the angle,
//  which increases counter clockwise (protractor).
// There was a lot of stuff grabbed wrong, so I changed it...
//
fixed_t pspritescale;
fixed_t pspriteiscale;

lighttable_t** spritelights;

// constant arrays
//  used for psprite clipping and initializing clipping
short negonearray[SCREENWIDTH];
short screenheightarray[SCREENWIDTH];

// variables used to look up
//  and range check thing_t sprites patches
spritedef_t* sprites;
int numsprites;

spriteframe_t sprtemp[29];
int maxframe;
char* spritename;
vissprite_t vissprites[MAXVISSPRITES];
vissprite_t* vissprite_p;
int newvissprite;
vissprite_t vsprsortedhead;


//
// INITIALIZATION FUNCTIONS
//

//
// R_InstallSpriteLump
// Local function for R_InitSprites.
//
extern void R_InstallSpriteLump(int lump, unsigned frame, unsigned rotation, doom_boolean flipped);


//
// R_InitSpriteDefs
// Pass a null terminated list of sprite names
//  (4 chars exactly) to be used.
// Builds the sprite rotation matrixes to account
//  for horizontally flipped sprites.
// Will report an error if the lumps are inconsistant. 
// Only called at startup.
//
// Sprite lump names are 4 characters for the actor,
//  a letter for the frame, and a number for the rotation.
// A sprite that is flippable will have an additional
//  letter/number appended.
// The rotation character can be 0 to signify no rotations.
//
extern void R_InitSpriteDefs(char** namelist);

//
// GAME FUNCTIONS
//

//
// R_InitSprites
// Called at program start.
//
extern void R_InitSprites(char** namelist);


//
// R_ClearSprites
// Called at frame start.
//
extern void R_ClearSprites(void);


//
// R_NewVisSprite
//
vissprite_t overflowsprite;

extern vissprite_t* R_NewVisSprite(void);


//
// R_DrawMaskedColumn
// Used for sprites and masked mid textures.
// Masked means: partly transparent, i.e. stored
//  in posts/runs of opaque pixels.
//
short* mfloorclip;
short* mceilingclip;

fixed_t spryscale;
fixed_t sprtopscreen;

extern void R_DrawMaskedColumn(column_t* column);



//
// R_DrawVisSprite
//  mfloorclip and mceilingclip should also be set.
//
extern void R_DrawVisSprite(vissprite_t* vis, int x1, int x2);


//
// R_ProjectSprite
// Generates a vissprite for a thing
//  if it might be visible.
//
extern void R_ProjectSprite(mobj_t* thing);


//
// R_AddSprites
// During BSP traversal, this adds sprites by sector.
//
extern void R_AddSprites(sector_t* sec);


//
// R_DrawPSprite
//
extern void R_DrawPSprite(pspdef_t* psp);


//
// R_DrawPlayerSprites
//
extern void R_DrawPlayerSprites(void);


//
// R_SortVisSprites
//
extern void R_SortVisSprites(void);


//
// R_DrawSprite
//
extern void R_DrawSprite(vissprite_t* spr);


//
// R_DrawMasked
//
extern void R_DrawMasked(void);
#define S_MAX_VOLUME 127

// when to clip out sounds
// Does not fit the large outdoor areas.
#define S_CLIPPING_DIST (1200*0x10000)

// Distance tp origin when sounds should be maxed out.
// This should relate to movement clipping resolution
// (see BLOCKMAP handling).
// Originally: (200*0x10000).
#define S_CLOSE_DIST (160*0x10000)

#define S_ATTENUATOR ((S_CLIPPING_DIST-S_CLOSE_DIST)>>FRACBITS)

// Adjustable by menu.
#define NORM_VOLUME snd_MaxVolume

#define NORM_PITCH 128
#define NORM_PRIORITY 64
#define NORM_SEP 128

#define S_PITCH_PERTURB 1
#define S_STEREO_SWING (96*0x10000)

// percent attenuation from front to back
#define S_IFRACVOL 30

#define NA 0
#define S_NUMCHANNELS 2


// Current music/sfx card - index useless
//  w/o a reference LUT in a sound module.
extern int snd_MusicDevice;
extern int snd_SfxDevice;
// Config file? Same disclaimer as above.
extern int snd_DesiredMusicDevice;
extern int snd_DesiredSfxDevice;


typedef struct
{
    // sound information (if null, channel avail.)
    sfxinfo_t* sfxinfo;

    // origin of sound
    void* origin;

    // handle of the sound being played
    int handle;
} channel_t;


// the set of channels available
 channel_t* channels_s_sound;

// whether songs are mus_paused
 doom_boolean mus_paused;

// music currently being played
 musicinfo_t* mus_playing_s_sound;

 int nextcleanup;


// These are not used, but should be (menu).
// Maximum volume of a sound effect.
// Internal default is max out of 0-15.
int snd_SfxVolume;

// Maximum volume of music. Useless so far.
int snd_MusicVolume;

// following is set
//  by the defaults code in M_misc:
// number of channels available
int numChannels;


//
// Prototypes
//
int S_getChannel(void* origin, sfxinfo_t* sfxinfo);
int S_AdjustSoundParams(mobj_t* listener, mobj_t* source, int* vol, int* sep, int* pitch);
void S_StopChannel(int cnum);


//
// Initializes sound stuff, including volume
// Sets channels, SFX and music volume,
//  allocates channel buffer, sets S_sfx lookup.
//
extern void S_Init(int sfxVolume, int musicVolume);


//
// Per level startup code.
// Kills playing sounds at start of level,
//  determines music if any, changes music.
//
extern void S_Start(void);


extern void S_StartSoundAtVolume(void* origin_p, int sfx_id, int volume);


extern void S_StartSound(void* origin, int sfx_id);


extern void S_StopSound(void* origin);


//
// Stop and resume music, during game PAUSE.
//
extern void S_PauseSound(void);


extern void S_ResumeSound(void);


//
// Updates music & sounds
//
extern void S_UpdateSounds(void* listener_p);


extern void S_SetMusicVolume(int volume);


void S_SetSfxVolume(int volume)
{
    if (volume < 0 || volume > 127)
    {
        //I_Error("Error: Attempt to set sfx volume at %d", volume);
        doom_strcpy(error_buf, "Error: Attempt to set sfx volume at ");
        doom_concat(error_buf, doom_itoa(volume, 10));
        I_Error(error_buf);
    }

    snd_SfxVolume = volume;
}


//
// Starts some music with the music id found in sounds.h.
//
extern void S_StartMusic(int m_id);


extern void S_ChangeMusic(int musicnum, int looping);


extern void S_StopMusic(void);


extern void S_StopChannel(int cnum);


//
// Changes volume, stereo-separation, and pitch variables
//  from the norm of a sound effect to be played.
// If the sound is not audible, returns a 0.
// Otherwise, modifies parameters and returns 1.
//
extern int S_AdjustSoundParams(mobj_t* listener, mobj_t* source, int* vol, int* sep, int* pitch);


//
// S_getChannel :
// If none available, return -1.  Otherwise channel #.
//
extern int S_getChannel(void* origin, sfxinfo_t* sfxinfo);
musicinfo_t* S_music;

//
// Information about all the sfx
//
sfxinfo_t* S_sfx;
extern doom_boolean                automapactive;


//
// Hack display negative frags.
//  Loads and store the stminus lump.
//
patch_t* sttminus;


extern void STlib_init(void);

// ?
extern void STlib_initNum(st_number_t* n, int x, int y, patch_t** pl, int* num, doom_boolean* on, int width);

// 
// A fairly efficient way to draw a number
//  based on differences from the old number.
// Note: worth the trouble?
//
extern void STlib_drawNum(st_number_t* n, doom_boolean refresh);
//
extern void STlib_updateNum(st_number_t* n, doom_boolean refresh);

//
extern void STlib_initPercent(st_percent_t* p, int x, int y, patch_t** pl, int* num, doom_boolean* on, patch_t* percent);

extern void STlib_updatePercent(st_percent_t* per, int refresh);

extern void STlib_initMultIcon(st_multicon_t* i, int x, int y, patch_t** il, int* inum, doom_boolean* on);

extern void STlib_updateMultIcon(st_multicon_t* mi, doom_boolean refresh);

extern void STlib_initBinIcon(st_binicon_t* b, int x, int y, patch_t* i, doom_boolean* val, doom_boolean* on);

extern void STlib_updateBinIcon(st_binicon_t* bi, doom_boolean refresh);
#define STARTREDPALS 1
#define STARTBONUSPALS 9
#define NUMREDPALS 8
#define NUMBONUSPALS 4
// Radiation suit, green shift.
#define RADIATIONPAL 13

// N/256*100% probability
//  that the normal face state will change
#define ST_FACEPROBABILITY 96

// For Responder
#define ST_TOGGLECHAT KEY_ENTER

// Location of status bar
#define ST_X 0
#define ST_X2 104

#define ST_FX 143
#define ST_FY 169

// Should be set to patch width
//  for tall numbers later on
#define ST_TALLNUMWIDTH (tallnum[0]->width)

// Number of status faces.
#define ST_NUMPAINFACES 5
#define ST_NUMSTRAIGHTFACES 3
#define ST_NUMTURNFACES 2
#define ST_NUMSPECIALFACES 3

#define ST_FACESTRIDE (ST_NUMSTRAIGHTFACES + ST_NUMTURNFACES + ST_NUMSPECIALFACES)

#define ST_NUMEXTRAFACES 2

#define ST_NUMFACES (ST_FACESTRIDE * ST_NUMPAINFACES + ST_NUMEXTRAFACES)

#define ST_TURNOFFSET (ST_NUMSTRAIGHTFACES)
#define ST_OUCHOFFSET (ST_TURNOFFSET + ST_NUMTURNFACES)
#define ST_EVILGRINOFFSET (ST_OUCHOFFSET + 1)
#define ST_RAMPAGEOFFSET (ST_EVILGRINOFFSET + 1)
#define ST_GODFACE (ST_NUMPAINFACES*ST_FACESTRIDE)
#define ST_DEADFACE (ST_GODFACE+1)

#define ST_FACESX 143
#define ST_FACESY 168

#define ST_EVILGRINCOUNT (2*TICRATE)
#define ST_STRAIGHTFACECOUNT (TICRATE/2)
#define ST_TURNCOUNT (1*TICRATE)
#define ST_OUCHCOUNT (1*TICRATE)
#define ST_RAMPAGEDELAY (2*TICRATE)

#define ST_MUCHPAIN 20

// Location and size of statistics,
// justified according to widget type.
// Problem is, within which space? STbar? Screen?
// Note: this could be read in by a lump.
//       Problem is, is the stuff rendered
//       into a buffer,
//       or into the frame buffer?

// AMMO number pos.
#define ST_AMMOWIDTH 3        
#define ST_AMMOX 44
#define ST_AMMOY 171

// HEALTH number pos.
#define ST_HEALTHWIDTH 3        
#define ST_HEALTHX 90
#define ST_HEALTHY 171

// Weapon pos.
#define ST_ARMSX 111
#define ST_ARMSY 172
#define ST_ARMSBGX 104
#define ST_ARMSBGY 168
#define ST_ARMSXSPACE 12
#define ST_ARMSYSPACE 10

// Frags pos.
#define ST_FRAGSX 138
#define ST_FRAGSY 171        
#define ST_FRAGSWIDTH 2

// ARMOR number pos.
#define ST_ARMORWIDTH 3
#define ST_ARMORX 221
#define ST_ARMORY 171

// Key icon positions.
#define ST_KEY0WIDTH 8
#define ST_KEY0HEIGHT 5
#define ST_KEY0X 239
#define ST_KEY0Y 171
#define ST_KEY1WIDTH ST_KEY0WIDTH
#define ST_KEY1X 239
#define ST_KEY1Y 181
#define ST_KEY2WIDTH ST_KEY0WIDTH
#define ST_KEY2X 239
#define ST_KEY2Y 191

// Ammunition counter.
#define ST_AMMO0WIDTH 3
#define ST_AMMO0HEIGHT 6
#define ST_AMMO0X 288
#define ST_AMMO0Y 173
#define ST_AMMO1WIDTH ST_AMMO0WIDTH
#define ST_AMMO1X 288
#define ST_AMMO1Y 179
#define ST_AMMO2WIDTH ST_AMMO0WIDTH
#define ST_AMMO2X 288
#define ST_AMMO2Y 191
#define ST_AMMO3WIDTH ST_AMMO0WIDTH
#define ST_AMMO3X 288
#define ST_AMMO3Y 185

// Indicate maximum ammunition.
// Only needed because backpack exists.
#define ST_MAXAMMO0WIDTH 3
#define ST_MAXAMMO0HEIGHT 5
#define ST_MAXAMMO0X 314
#define ST_MAXAMMO0Y 173
#define ST_MAXAMMO1WIDTH ST_MAXAMMO0WIDTH
#define ST_MAXAMMO1X 314
#define ST_MAXAMMO1Y 179
#define ST_MAXAMMO2WIDTH ST_MAXAMMO0WIDTH
#define ST_MAXAMMO2X 314
#define ST_MAXAMMO2Y 191
#define ST_MAXAMMO3WIDTH ST_MAXAMMO0WIDTH
#define ST_MAXAMMO3X 314
#define ST_MAXAMMO3Y 185

// pistol
#define ST_WEAPON0X 110 
#define ST_WEAPON0Y 172

// shotgun
#define ST_WEAPON1X 122 
#define ST_WEAPON1Y 172

// chain gun
#define ST_WEAPON2X 134 
#define ST_WEAPON2Y 172

// missile launcher
#define ST_WEAPON3X 110 
#define ST_WEAPON3Y 181

// plasma gun
#define ST_WEAPON4X 122 
#define ST_WEAPON4Y 181

 // bfg
#define ST_WEAPON5X 134
#define ST_WEAPON5Y 181

// WPNS title
#define ST_WPNSX 109 
#define ST_WPNSY 191

 // DETH title
#define ST_DETHX 109
#define ST_DETHY 191

//Incoming messages window location
#define ST_MSGTEXTX 0
#define ST_MSGTEXTY 0
// Dimensions given in characters.
#define ST_MSGWIDTH 52
// Or shall I say, in lines?
#define ST_MSGHEIGHT 1

#define ST_OUTTEXTX 0
#define ST_OUTTEXTY 6

// Width, in characters again.
#define ST_OUTWIDTH 52 
 // Height, in lines. 
#define ST_OUTHEIGHT 1

#define ST_MAPWIDTH (doom_strlen(mapnames[(gameepisode - 1) * 9 + (gamemap - 1)]))

#define ST_MAPTITLEX (SCREENWIDTH - ST_MAPWIDTH * ST_CHATFONTWIDTH)

#define ST_MAPTITLEY 0
#define ST_MAPHEIGHT 1


player_t* plyr; // main player in game
doom_boolean st_firsttime; // ST_Start() has just been called
int veryfirsttime; // used to execute ST_Init() only once
int lu_palette; // lump number for PLAYPAL
unsigned int st_clock; // used for timing
int st_msgcounter; // used for making messages go away
st_chatstateenum_t st_chatstate; // used when in chat
st_stateenum_t st_gamestate; // whether in automap or first-person
doom_boolean st_statusbaron; // whether left-side main status bar is active
doom_boolean st_chat; // whether status bar chat is active
doom_boolean st_oldchat; // value of st_chat before message popped up
doom_boolean st_cursoron; // whether chat window has the cursor on
doom_boolean st_notdeathmatch; // !deathmatch
doom_boolean st_armson; // !deathmatch && st_statusbaron
doom_boolean st_fragson; // !deathmatch
patch_t* sbar; // main bar left
patch_t* tallnum[10]; // 0-9, tall numbers
patch_t* tallpercent; // tall % sign
patch_t* shortnum[10]; // 0-9, short, yellow (,different!) numbers
patch_t* keys[NUMCARDS]; // 3 key-cards, 3 skulls
patch_t* faces[ST_NUMFACES]; // face status patches
patch_t* faceback; // face background
patch_t* armsbg; // main bar right
patch_t* arms[6][2]; // weapon ownership patches
st_number_t w_ready; // ready-weapon widget
st_number_t w_frags; // in deathmatch only, summary of frags stats
st_percent_t w_health; // health widget
st_binicon_t w_armsbg; // arms background
st_multicon_t w_arms[6]; // weapon ownership widgets
st_multicon_t w_faces; // face status widget
st_multicon_t w_keyboxes[3]; // keycard widgets
st_percent_t w_armor; // armor widget
st_number_t w_ammo[4]; // ammo widgets
st_number_t w_maxammo[4]; // max ammo widgets
int st_fragscount; // number of frags so far in deathmatch
int st_oldhealth; // used to use appopriately pained face
doom_boolean oldweaponsowned[NUMWEAPONS]; // used for evil grin
int st_facecount; // count until face changes
int st_faceindex; // current face index, used by w_faces
int keyboxes[3]; // holds key-type for each key box on bar
int st_randomnumber; // a random number per tick
int st_palette;
doom_boolean st_stopped;


// Massive bunches of cheat shit
//  to keep it from being easy to figure them out.
// Yeah, right...
unsigned char cheat_mus_seq[9];

unsigned char cheat_choppers_seq[11];

unsigned char cheat_god_seq[6];

unsigned char cheat_ammo_seq[6];

unsigned char cheat_ammonokey_seq[5];

// Smashing Pumpkins Into Samml Piles Of Putried Debris. 
unsigned char cheat_noclip_seq[11];

//
unsigned char cheat_commercial_noclip_seq[7];

unsigned char cheat_powerup_seq[7][10];

unsigned char cheat_clev_seq[10];

// my position cheat
unsigned char cheat_mypos_seq[8];

// Now what?
cheatseq_t cheat_mus;
cheatseq_t cheat_god;
cheatseq_t cheat_ammo;
cheatseq_t cheat_ammonokey;
cheatseq_t cheat_noclip;
cheatseq_t cheat_commercial_noclip;

cheatseq_t cheat_powerup[7];

cheatseq_t cheat_choppers;
cheatseq_t cheat_clev;
cheatseq_t cheat_mypos;


extern char* mapnames[];
extern int doom_flags;


void ST_Stop(void);


//
// STATUS BAR CODE
//

extern void ST_refreshBackground(void);


// Respond to keyboard input events,
//  intercept cheats.
extern doom_boolean ST_Responder(event_t* ev);


extern int ST_calcPainOffset(void);


//
// This is a not-very-pretty routine which handles
//  the face states and their timing.
// the precedence of expressions is:
//  dead > evil grin > turned head > straight ahead
//
extern void ST_updateFaceWidget(void);


extern void ST_updateWidgets(void);


extern void ST_Ticker(void);


extern void ST_doPaletteStuff(void);


extern void ST_drawWidgets(doom_boolean refresh);


extern void ST_doRefresh(void);


extern void ST_diffDraw(void);


extern void ST_Drawer(doom_boolean fullscreen, doom_boolean refresh);


extern void ST_loadGraphics(void);

extern void ST_loadData(void);

extern void ST_unloadGraphics(void);

extern void ST_unloadData(void);

extern void ST_initData(void);

extern void ST_createWidgets(void);

extern void ST_Start(void);

extern void ST_Stop(void);

extern void ST_Init(void);
extern int
SlopeDiv
( unsigned        num,
  unsigned        den);




int* finetangent;

int* finesine;


angle_t* tantoangle;
byte* screens[5];

int dirtybox[4];

// Now where did these came from?
byte gammatable[5][256];

int usegamma;


//
// V_MarkRect 
// 
extern void V_MarkRect(int x, int y, int width, int height);


//
// V_CopyRect 
// 
extern void V_CopyRect(int srcx,
                int srcy,
                int srcscrn,
                int width,
                int height,
                int destx,
                int desty,
                int destscrn);


//
// V_DrawPatch
// Masks a column based masked pic to the screen. 
//
extern void V_DrawPatch(int x, int y, int scrn, patch_t* patch);


//
// V_DrawPatchFlipped 
// Masks a column based masked pic to the screen.
// Flips horizontally, e.g. to mirror face.
//
extern void V_DrawPatchFlipped(int x, int y, int scrn, patch_t* patch);


extern void V_DrawPatchRectDirect(int x, int y, int scrn, patch_t* patch, int src_x, int src_w);


//
// V_DrawPatchDirect
// Draws directly to the screen on the pc. 
//
void V_DrawPatchDirect(int x, int y, int scrn, patch_t* patch)
{
    V_DrawPatch(x, y, scrn, patch);
}


//
// V_DrawBlock
// Draw a linear block of pixels into the view buffer.
//
extern void V_DrawBlock(int x, int y, int scrn, int width, int height, byte* src);


//
// V_GetBlock
// Gets a linear block of pixels from the view buffer.
//
extern void V_GetBlock(int x, int y, int scrn, int width, int height, byte* dest);


//
// V_Init
// 
extern void V_Init(void);
lumpinfo_t* lumpinfo;
int numlumps;
void** lumpcache;
int reloadlump;
char* reloadname;
int info[2500][10];
int profilecount;


extern void doom_strupr(char* s);


extern void ExtractFileBase(char* path, char* dest);


//
// LUMP BASED ROUTINES.
//

//
// W_AddFile
// All files are optional, but at least one file must be
//  found (PWAD, if all required lumps are present).
// Files with a .wad extension are wadlink files
//  with multiple lumps.
// Other files are single lumps with the base filename
//  for the lump name.
//
// If filename starts with a tilde, the file is handled
//  specially to allow map reloads.
// But: the reload feature is a fragile hack...
extern void W_AddFile(char* filename);


//
// W_Reload
// Flushes any of the reloadable lumps in memory
//  and reloads the directory.
//
extern void W_Reload(void);


//
// W_InitMultipleFiles
// Pass a null terminated list of files to use.
// All files are optional, but at least one file
//  must be found.
// Files with a .wad extension are idlink files
//  with multiple lumps.
// Other files are single lumps with the base filename
//  for the lump name.
// Lump names can appear multiple times.
// The name searcher looks backwards, so a later file
//  does override all earlier ones.
//
extern void W_InitMultipleFiles(char** filenames);



//
// W_CheckNumForName
// Returns -1 if name not found.
//
extern int W_CheckNumForName(char* name);


//
// W_GetNumForName
// Calls W_CheckNumForName, but bombs out if not found.
//
extern int W_GetNumForName(char* name);


//
// W_LumpLength
// Returns the buffer size needed to load the given lump.
//
extern int W_LumpLength(int lump);


//
// W_ReadLump
// Loads the lump into the given buffer,
//  which must be >= W_LumpLength().
//
extern void W_ReadLump(int lump, void* dest);


//
// W_CacheLumpNum
//
extern void* W_CacheLumpNum(int lump, int tag);


//
// W_CacheLumpName
//
extern void* W_CacheLumpName(char* name, int tag);
#define NUMEPISODES 4
#define NUMMAPS 9

// GLOBAL LOCATIONS
#define WI_TITLEY 2
#define WI_SPACINGY 33

// SINGPLE-PLAYER STUFF
#define SP_STATSX 50
#define SP_STATSY 50

#define SP_TIMEX 16
#define SP_TIMEY (SCREENHEIGHT-32)

// NET GAME STUFF
#define NG_STATSY 50
#define NG_STATSX (32 + SHORT(star->width)/2 + 32*!dofrags)

#define NG_SPACINGX 64

// DEATHMATCH STUFF
#define DM_MATRIXX 42
#define DM_MATRIXY 68

#define DM_SPACINGX 40

#define DM_TOTALSX 269

#define DM_KILLERSX 10
#define DM_KILLERSY 100
#define DM_VICTIMSX 5
#define DM_VICTIMSY 50

#define FB 0

// States for single-player
#define SP_KILLS                0
#define SP_ITEMS                2
#define SP_SECRET                4
#define SP_FRAGS                6 
#define SP_TIME                        8 
#define SP_PAR                        ST_TIME

#define SP_PAUSE                1

// in seconds
#define SHOWNEXTLOCDELAY        4
//#define SHOWLASTLOCDELAY        SHOWNEXTLOCDELAY


typedef enum
{
    ANIM_ALWAYS,
    ANIM_RANDOM,
    ANIM_LEVEL
} animenum_t;


typedef struct
{
    int x;
    int y;
} point_t;


//
// Animation.
// There is another anim_t used in p_spec.
//
typedef struct
{
    animenum_t type;

    // period in tics between animations
    int period;

    // number of animation frames
    int nanims;

    // location of animation
    point_t loc;

    // ALWAYS: n/a,
    // RANDOM: period deviation (<256),
    // LEVEL: level
    int data1;

    // ALWAYS: n/a,
    // RANDOM: random base period,
    // LEVEL: n/a
    int data2;

    // actual graphics for frames of animations
    patch_t* p[3];

    // following must be initialized to zero before use!

    // next value of bcnt (used in conjunction with period)
    int nexttic;

    // last drawn animation frame
    int lastdrawn;

    // next frame number to animate
    int ctr;

    // used by RANDOM and LEVEL when animating
    int state;
} anim_t_wi_stuff;


point_t* lnodes[NUMEPISODES];


//
// Animation locations for episode 0 (1).
// Using patches saves a lot of space,
//  as they replace 320x200 full screen frames.
//
anim_t_wi_stuff epsd0animinfo[10];

anim_t_wi_stuff epsd1animinfo[9];

anim_t_wi_stuff epsd2animinfo[6];

int NUMANIMS[NUMEPISODES];

anim_t_wi_stuff* anims_wi_stuff[NUMEPISODES];


//
// GENERAL DATA
//

//
// Locally used stuff.
//

// used to accelerate or skip a stage
int acceleratestage;

// wbs->pnum
int me;

// specifies current state
stateenum_t state;

// contains information passed into intermission
wbstartstruct_t* wbs;

wbplayerstruct_t* plrs;  // wbs->plyr[]

// used for general timing
int cnt;

// used for timing of background animation
int bcnt;

// signals to refresh everything for one frame
int firstrefresh;

int cnt_kills[MAXPLAYERS];
int cnt_items[MAXPLAYERS];
int cnt_secret[MAXPLAYERS];
int cnt_time;
int cnt_par;
int cnt_pause;

// # of commercial levels
int NUMCMAPS;


//
// GRAPHICS
//

// background (map of levels).
patch_t* bg;

// You Are Here graphic
patch_t* yah[2];

// splat
patch_t* splat;

// %, : graphics
patch_t* percent;
patch_t* colon;

// 0-9 graphic
patch_t* num[10];

// minus sign
patch_t* wiminus;

// "Finished!" graphics
patch_t* finished;

// "Entering" graphic
patch_t* entering;

// "secret"
patch_t* sp_secret;

// "Kills", "Scrt", "Items", "Frags"
patch_t* kills;
patch_t* secret;
patch_t* items;
patch_t* frags;

// Time sucks.
patch_t* time_patch;
patch_t* par;
patch_t* sucks;

// "killers", "victims"
patch_t* killers;
patch_t* victims;

// "Total", your face, your dead face
patch_t* total;
patch_t* star;
patch_t* bstar;

// "red P[1..MAXPLAYERS]"
patch_t* p[MAXPLAYERS];

// "gray P[1..MAXPLAYERS]"
patch_t* bp[MAXPLAYERS];

// Name graphics of each level (centered)
patch_t** lnames;

doom_boolean snl_pointeron;
int dm_state;
int dm_frags[MAXPLAYERS][MAXPLAYERS];
int dm_totals[MAXPLAYERS];
int cnt_frags[MAXPLAYERS];
int dofrags;
int ng_state;
int sp_state;


//
// CODE
//

extern void WI_slamBackground(void);


// Draws "<Levelname> Finished!"
extern void WI_drawLF(void);


// Draws "Entering <LevelName>"
extern void WI_drawEL(void);

extern void WI_drawOnLnode(int n, patch_t* c[]);


extern void WI_initAnimatedBack(void);


extern void WI_updateAnimatedBack(void);


extern void WI_drawAnimatedBack(void);


//
// Draws a number.
// If digits > 0, then use that many digits minimum,
//  otherwise only use as many as necessary.
// Returns new x position.
//
extern int WI_drawNum(int x, int y, int n, int digits);


extern void WI_drawPercent(int x, int y, int p);


//
// Display level completion time and par,
//  or "sucks" message if overflow.
//
extern void WI_drawTime(int x, int y, int t);


extern void WI_End(void);


extern void WI_initNoState(void);


extern void WI_updateNoState(void);


extern void WI_initShowNextLoc(void);


extern void WI_updateShowNextLoc(void);


extern void WI_drawShowNextLoc(void);


extern void WI_drawNoState(void);


extern int WI_fragSum(int playernum);


extern void WI_initDeathmatchStats(void);


extern void WI_updateDeathmatchStats(void);


extern void WI_drawDeathmatchStats(void);


extern void WI_initNetgameStats(void);


extern void WI_updateNetgameStats(void);


extern void WI_drawNetgameStats(void);


extern void WI_initStats(void);


extern void WI_updateStats(void);


extern void WI_drawStats(void);


extern void WI_checkForAccelerate(void);


// Updates stuff each tick
extern void WI_Ticker(void);


extern void WI_loadData(void);


extern void WI_unloadData(void);


extern void WI_Drawer(void);


extern void WI_initVariables(wbstartstruct_t* wbstartstruct);


extern void WI_Start(wbstartstruct_t* wbstartstruct);
#define ZONEID 0x1d4a11
#define MINFRAGMENT 64
#define MEM_ALIGN sizeof(void *)


typedef struct
{
    // total bytes malloced, including header
    int size;

    // start / end cap for linked list
    memblock_t blocklist;

    memblock_t* rover;
} memzone_t;


memzone_t* mainzone;


//
// Z_Init
//
extern void Z_Init(void);


//
// Z_Free
//
extern void Z_Free(void* ptr);


//
// Z_Malloc
// You can pass a 0 user if the tag is < PU_PURGELEVEL.
//
extern void* Z_Malloc(int size, int tag, void* user);


//
// Z_FreeTags
//
extern void Z_FreeTags(int lowtag, int hightag);

//
// Z_CheckHeap
//
extern void Z_CheckHeap(void);


//
// Z_ChangeTag
//
extern void Z_ChangeTag2(void* ptr, int tag);

//#endif // DOOM_IMPLEMENTATION
