/*
 * KeyID.h
 *
 *  Created on: Dec 25, 2021
 *      Author: Harrison
 */

#ifndef INC_KEYID_H_
#define INC_KEYID_H_

/**
 * USB HID Keyboard scan codes as per USB spec 1.11
 * plus some additional codes
 * 
 * Created by MightyPork, 2016
 * Public domain
 * 
 * Adapted from:
 * https://source.android.com/devices/input/keyboard-devices.html
 */

/**
 * Modifier masks - used for the first byte in the HID report.
 * NOTE: The second byte in the report is reserved, 0x00
 */
#define KEY_MOD_LCTRL 0x01
#define KEY_MOD_LSHIFT 0x02
#define KEY_MOD_LALT 0x04
#define KEY_MOD_LMETA 0x08
#define KEY_MOD_RCTRL 0x10
#define KEY_MOD_RSHIFT 0x20
#define KEY_MOD_RALT 0x40
#define KEY_MOD_RMETA 0x80

/**
 * Scan codes - last N slots in the HID report (usually 6).
 * 0x00 if no key pressed.
 * 
 * If more than N keys are pressed, the HID reports 
 * KEY_ERR_OVF in all slots to indicate this condition.
 */

#define KEY_NONE 0x00     // No key pressed
#define KEY_ERR_OVF 0x01  //  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
// 0x02 //  Keyboard POST Fail
// 0x03 //  Keyboard Error Undefined
#define KEY_A 0x04  // Keyboard a and A
#define KEY_B 0x05  // Keyboard b and B
#define KEY_C 0x06  // Keyboard c and C
#define KEY_D 0x07  // Keyboard d and D
#define KEY_E 0x08  // Keyboard e and E
#define KEY_F 0x09  // Keyboard f and F
#define KEY_G 0x0a  // Keyboard g and G
#define KEY_H 0x0b  // Keyboard h and H
#define KEY_I 0x0c  // Keyboard i and I
#define KEY_J 0x0d  // Keyboard j and J
#define KEY_K 0x0e  // Keyboard k and K
#define KEY_L 0x0f  // Keyboard l and L
#define KEY_M 0x10  // Keyboard m and M
#define KEY_N 0x11  // Keyboard n and N
#define KEY_O 0x12  // Keyboard o and O
#define KEY_P 0x13  // Keyboard p and P
#define KEY_Q 0x14  // Keyboard q and Q
#define KEY_R 0x15  // Keyboard r and R
#define KEY_S 0x16  // Keyboard s and S
#define KEY_T 0x17  // Keyboard t and T
#define KEY_U 0x18  // Keyboard u and U
#define KEY_V 0x19  // Keyboard v and V
#define KEY_W 0x1a  // Keyboard w and W
#define KEY_X 0x1b  // Keyboard x and X
#define KEY_Y 0x1c  // Keyboard y and Y
#define KEY_Z 0x1d  // Keyboard z and Z

#define KEY_1 0x1e  // Keyboard 1 and !
#define KEY_2 0x1f  // Keyboard 2 and @
#define KEY_3 0x20  // Keyboard 3 and #
#define KEY_4 0x21  // Keyboard 4 and $
#define KEY_5 0x22  // Keyboard 5 and %
#define KEY_6 0x23  // Keyboard 6 and ^
#define KEY_7 0x24  // Keyboard 7 and &
#define KEY_8 0x25  // Keyboard 8 and *
#define KEY_9 0x26  // Keyboard 9 and (
#define KEY_0 0x27  // Keyboard 0 and )

#define KEY_ENTER 0x28       // Keyboard Return (ENTER)
#define KEY_ESC 0x29         // Keyboard ESCAPE
#define KEY_BACKSPACE 0x2a   // Keyboard DELETE (Backspace)
#define KEY_TAB 0x2b         // Keyboard Tab
#define KEY_SPACE 0x2c       // Keyboard Spacebar
#define KEY_MINUS 0x2d       // Keyboard - and _
#define KEY_EQUAL 0x2e       // Keyboard = and +
#define KEY_LEFTBRACE 0x2f   // Keyboard [ and {
#define KEY_RIGHTBRACE 0x30  // Keyboard ] and }
#define KEY_BACKSLASH 0x31   // Keyboard \ and |
#define KEY_HASHTILDE 0x32   // Keyboard Non-US # and ~
#define KEY_SEMICOLON 0x33   // Keyboard ; and :
#define KEY_APOSTROPHE 0x34  // Keyboard ' and "
#define KEY_GRAVE 0x35       // Keyboard ` and ~
#define KEY_COMMA 0x36       // Keyboard , and <
#define KEY_DOT 0x37         // Keyboard . and >
#define KEY_SLASH 0x38       // Keyboard / and ?
#define KEY_CAPSLOCK 0x39    // Keyboard Caps Lock

#define KEY_F1 0x3a   // Keyboard F1
#define KEY_F2 0x3b   // Keyboard F2
#define KEY_F3 0x3c   // Keyboard F3
#define KEY_F4 0x3d   // Keyboard F4
#define KEY_F5 0x3e   // Keyboard F5
#define KEY_F6 0x3f   // Keyboard F6
#define KEY_F7 0x40   // Keyboard F7
#define KEY_F8 0x41   // Keyboard F8
#define KEY_F9 0x42   // Keyboard F9
#define KEY_F10 0x43  // Keyboard F10
#define KEY_F11 0x44  // Keyboard F11
#define KEY_F12 0x45  // Keyboard F12

#define KEY_SYSRQ 0x46       // Keyboard Print Screen
#define KEY_SCROLLLOCK 0x47  // Keyboard Scroll Lock
#define KEY_PAUSE 0x48       // Keyboard Pause
#define KEY_INSERT 0x49      // Keyboard Insert
#define KEY_HOME 0x4a        // Keyboard Home
#define KEY_PAGEUP 0x4b      // Keyboard Page Up
#define KEY_DELETE 0x4c      // Keyboard Delete Forward
#define KEY_END 0x4d         // Keyboard End
#define KEY_PAGEDOWN 0x4e    // Keyboard Page Down
#define KEY_RIGHT 0x4f       // Keyboard Right Arrow
#define KEY_LEFT 0x50        // Keyboard Left Arrow
#define KEY_DOWN 0x51        // Keyboard Down Arrow
#define KEY_UP 0x52          // Keyboard Up Arrow

#define KEY_NUMLOCK 0x53     // Keyboard Num Lock and Clear
#define KEY_KPSLASH 0x54     // Keypad /
#define KEY_KPASTERISK 0x55  // Keypad *
#define KEY_KPMINUS 0x56     // Keypad -
#define KEY_KPPLUS 0x57      // Keypad +
#define KEY_KPENTER 0x58     // Keypad ENTER
#define KEY_KP1 0x59         // Keypad 1 and End
#define KEY_KP2 0x5a         // Keypad 2 and Down Arrow
#define KEY_KP3 0x5b         // Keypad 3 and PageDn
#define KEY_KP4 0x5c         // Keypad 4 and Left Arrow
#define KEY_KP5 0x5d         // Keypad 5
#define KEY_KP6 0x5e         // Keypad 6 and Right Arrow
#define KEY_KP7 0x5f         // Keypad 7 and Home
#define KEY_KP8 0x60         // Keypad 8 and Up Arrow
#define KEY_KP9 0x61         // Keypad 9 and Page Up
#define KEY_KP0 0x62         // Keypad 0 and Insert
#define KEY_KPDOT 0x63       // Keypad . and Delete

#define KEY_102ND 0x64    // Keyboard Non-US \ and |
#define KEY_COMPOSE 0x65  // Keyboard Application
#define KEY_POWER 0x66    // Keyboard Power
#define KEY_KPEQUAL 0x67  // Keypad =

#define KEY_F13 0x68  // Keyboard F13
#define KEY_F14 0x69  // Keyboard F14
#define KEY_F15 0x6a  // Keyboard F15
#define KEY_F16 0x6b  // Keyboard F16
#define KEY_F17 0x6c  // Keyboard F17
#define KEY_F18 0x6d  // Keyboard F18
#define KEY_F19 0x6e  // Keyboard F19
#define KEY_F20 0x6f  // Keyboard F20
#define KEY_F21 0x70  // Keyboard F21
#define KEY_F22 0x71  // Keyboard F22
#define KEY_F23 0x72  // Keyboard F23
#define KEY_F24 0x73  // Keyboard F24

#define KEY_OPEN 0x74        // Keyboard Execute
#define KEY_HELP 0x75        // Keyboard Help
#define KEY_PROPS 0x76       // Keyboard Menu
#define KEY_FRONT 0x77       // Keyboard Select
#define KEY_STOP 0x78        // Keyboard Stop
#define KEY_AGAIN 0x79       // Keyboard Again
#define KEY_UNDO 0x7a        // Keyboard Undo
#define KEY_CUT 0x7b         // Keyboard Cut
#define KEY_COPY 0x7c        // Keyboard Copy
#define KEY_PASTE 0x7d       // Keyboard Paste
#define KEY_FIND 0x7e        // Keyboard Find
#define KEY_MUTE 0x7f        // Keyboard Mute
#define KEY_VOLUMEUP 0x80    // Keyboard Volume Up
#define KEY_VOLUMEDOWN 0x81  // Keyboard Volume Down
// 0x82  Keyboard Locking Caps Lock
// 0x83  Keyboard Locking Num Lock
// 0x84  Keyboard Locking Scroll Lock
#define KEY_KPCOMMA 0x85  // Keypad Comma
// 0x86  Keypad Equal Sign
#define KEY_RO 0x87                // Keyboard International1
#define KEY_KATAKANAHIRAGANA 0x88  // Keyboard International2
#define KEY_YEN 0x89               // Keyboard International3
#define KEY_HENKAN 0x8a            // Keyboard International4
#define KEY_MUHENKAN 0x8b          // Keyboard International5
#define KEY_KPJPCOMMA 0x8c         // Keyboard International6
// 0x8d  Keyboard International7
// 0x8e  Keyboard International8
// 0x8f  Keyboard International9
#define KEY_HANGEUL 0x90         // Keyboard LANG1
#define KEY_HANJA 0x91           // Keyboard LANG2
#define KEY_KATAKANA 0x92        // Keyboard LANG3
#define KEY_HIRAGANA 0x93        // Keyboard LANG4
#define KEY_ZENKAKUHANKAKU 0x94  // Keyboard LANG5
// 0x95  Keyboard LANG6
// 0x96  Keyboard LANG7
// 0x97  Keyboard LANG8
// 0x98  Keyboard LANG9
// 0x99  Keyboard Alternate Erase
// 0x9a  Keyboard SysReq/Attention
// 0x9b  Keyboard Cancel
// 0x9c  Keyboard Clear
// 0x9d  Keyboard Prior
// 0x9e  Keyboard Return
// 0x9f  Keyboard Separator
// 0xa0  Keyboard Out
// 0xa1  Keyboard Oper
// 0xa2  Keyboard Clear/Again
// 0xa3  Keyboard CrSel/Props
// 0xa4  Keyboard ExSel

// 0xb0  Keypad 00
// 0xb1  Keypad 000
// 0xb2  Thousands Separator
// 0xb3  Decimal Separator
// 0xb4  Currency Unit
// 0xb5  Currency Sub-unit
#define KEY_KPLEFTPAREN 0xb6   // Keypad (
#define KEY_KPRIGHTPAREN 0xb7  // Keypad )
// 0xb8  Keypad {
// 0xb9  Keypad }
// 0xba  Keypad Tab
// 0xbb  Keypad Backspace
// 0xbc  Keypad A
// 0xbd  Keypad B
// 0xbe  Keypad C
// 0xbf  Keypad D
// 0xc0  Keypad E
// 0xc1  Keypad F
// 0xc2  Keypad XOR
// 0xc3  Keypad ^
// 0xc4  Keypad %
// 0xc5  Keypad <
// 0xc6  Keypad >
// 0xc7  Keypad &
// 0xc8  Keypad &&
// 0xc9  Keypad |
// 0xca  Keypad ||
// 0xcb  Keypad :
// 0xcc  Keypad #
// 0xcd  Keypad Space
// 0xce  Keypad @
// 0xcf  Keypad !
// 0xd0  Keypad Memory Store
// 0xd1  Keypad Memory Recall
// 0xd2  Keypad Memory Clear
// 0xd3  Keypad Memory Add
// 0xd4  Keypad Memory Subtract
// 0xd5  Keypad Memory Multiply
// 0xd6  Keypad Memory Divide
// 0xd7  Keypad +/-
// 0xd8  Keypad Clear
// 0xd9  Keypad Clear Entry
// 0xda  Keypad Binary
// 0xdb  Keypad Octal
// 0xdc  Keypad Decimal
// 0xdd  Keypad Hexadecimal

#define KEY_LEFTCTRL 0xe0    // Keyboard Left Control
#define KEY_LEFTSHIFT 0xe1   // Keyboard Left Shift
#define KEY_LEFTALT 0xe2     // Keyboard Left Alt
#define KEY_LEFTMETA 0xe3    // Keyboard Left GUI
#define KEY_RIGHTCTRL 0xe4   // Keyboard Right Control
#define KEY_RIGHTSHIFT 0xe5  // Keyboard Right Shift
#define KEY_RIGHTALT 0xe6    // Keyboard Right Alt
#define KEY_RIGHTMETA 0xe7   // Keyboard Right GUI

#define KEY_MEDIA_PLAYPAUSE 0xe8
#define KEY_MEDIA_STOPCD 0xe9
#define KEY_MEDIA_PREVIOUSSONG 0xea
#define KEY_MEDIA_NEXTSONG 0xeb
#define KEY_MEDIA_EJECTCD 0xec
#define KEY_MEDIA_VOLUMEUP 0xed
#define KEY_MEDIA_VOLUMEDOWN 0xee
#define KEY_MEDIA_MUTE 0xef
#define KEY_MEDIA_WWW 0xf0
#define KEY_MEDIA_BACK 0xf1
#define KEY_MEDIA_FORWARD 0xf2
#define KEY_MEDIA_STOP 0xf3
#define KEY_MEDIA_FIND 0xf4
#define KEY_MEDIA_SCROLLUP 0xf5
#define KEY_MEDIA_SCROLLDOWN 0xf6
#define KEY_MEDIA_EDIT 0xf7
#define KEY_MEDIA_SLEEP 0xf8
#define KEY_MEDIA_COFFEE 0xf9
#define KEY_MEDIA_REFRESH 0xfa
#define KEY_MEDIA_CALC 0xfb

uint8_t getKeyIDByChar(const char ch) {
    if (ch == 'a' || ch == 'A')
        return 0x04;
    else if (ch == 'b' || ch == 'B')
        return 0x05;
    else if (ch == 'c' || ch == 'C')
        return 0x06;
    else if (ch == 'd' || ch == 'D')
        return 0x07;
    else if (ch == 'e' || ch == 'E')
        return 0x08;
    else if (ch == 'f' || ch == 'F')
        return 0x09;
    else if (ch == 'g' || ch == 'G')
        return 0x0A;
    else if (ch == 'h' || ch == 'H')
        return 0x0B;
    else if (ch == 'i' || ch == 'I')
        return 0x0C;
    else if (ch == 'j' || ch == 'J')
        return 0x0D;
    else if (ch == 'k' || ch == 'K')
        return 0x0E;
    else if (ch == 'l' || ch == 'L')
        return 0x0F;
    else if (ch == 'm' || ch == 'M')
        return 0x10;
    else if (ch == 'n' || ch == 'N')
        return 0x11;
    else if (ch == 'o' || ch == 'O')
        return 0x12;
    else if (ch == 'p' || ch == 'P')
        return 0x13;
    else if (ch == 'q' || ch == 'Q')
        return 0x14;
    else if (ch == 'r' || ch == 'R')
        return 0x15;
    else if (ch == 's' || ch == 'S')
        return 0x16;
    else if (ch == 't' || ch == 'T')
        return 0x17;
    else if (ch == 'u' || ch == 'U')
        return 0x18;
    else if (ch == 'v' || ch == 'V')
        return 0x19;
    else if (ch == 'w' || ch == 'W')
        return 0x1A;
    else if (ch == 'x' || ch == 'X')
        return 0x1B;
    else if (ch == 'y' || ch == 'Y')
        return 0x1C;
    else if (ch == 'z' || ch == 'Z')
        return 0x1D;

    else if (ch == '1' || ch == '!')
        return 0x1E;
    else if (ch == '2' || ch == '@')
        return 0x1F;
    else if (ch == '3' || ch == '#')
        return 0x20;
    else if (ch == '4' || ch == '$')
        return 0x21;
    else if (ch == '5' || ch == '%')
        return 0x22;
    else if (ch == '6' || ch == '^')
        return 0x23;
    else if (ch == '7' || ch == '&')
        return 0x24;
    else if (ch == '8' || ch == '*')
        return 0x25;
    else if (ch == '9' || ch == '(')
        return 0x26;
    else if (ch == '0' || ch == ')')
        return 0x27;

    else if (ch == '-' || ch == '_')
        return 0x2D;
    else if (ch == '=' || ch == '+')
        return 0x2E;
    else if (ch == '[' || ch == '{')
        return 0x2F;
    else if (ch == ']' || ch == '}')
        return 0x30;
    else if (ch == '\\' || ch == '|')
        return 0x31;
    else if (ch == '`' || ch == '~')
        return 0x32;
    else if (ch == ';' || ch == ':')
        return 0x33;
    else if (ch == '\'' || ch == '\"')
        return 0x34;
    else if (ch == ',' || ch == '<')
        return 0x36;
    else if (ch == '.' || ch == '>')
        return 0x37;
    else if (ch == '/' || ch == '?')
        return 0x38;
    else
        return 0x00;
}

uint8_t getKeyIDByRC(const uint8_t r, const uint8_t c) {
#if defined(KEYBOARD_LAYOUT_84)
    if (r == 0 && c == 0)
        return 0x29;  //esc
    else if (r == 0 && c == 1)
        return 0x3A;  //F1
    else if (r == 0 && c == 2)
        return 0x3B;  //F2
    else if (r == 0 && c == 3)
        return 0x3C;  //F3
    else if (r == 0 && c == 4)
        return 0x3D;  //F4
    else if (r == 0 && c == 5)
        return 0x3E;  //F5
    else if (r == 0 && c == 6)
        return 0x3F;  //F6
    else if (r == 0 && c == 7)
        return 0x40;  //F7	//previous
    else if (r == 0 && c == 8)
        return 0x41;  //F8	//pause
    else if (r == 0 && c == 9)
        return 0x42;  //F9	//next
    else if (r == 0 && c == 10)
        return 0x43;  //F10	//(un)mute
    else if (r == 0 && c == 11)
        return 0x44;  //F11	//vloumn down
    else if (r == 0 && c == 12)
        return 0x45;  //F12	//volumn up
    else if (r == 0 && c == 13)
        return 0x46;  //PrtScn
    else if (r == 1 && c == 0)
        return getKeyIDByChar('/');  //splash
    else if (r == 1 && c == 1)
        return getKeyIDByChar('1');  //1
    else if (r == 1 && c == 2)
        return getKeyIDByChar('2');  //2
    else if (r == 1 && c == 3)
        return getKeyIDByChar('3');  //3
    else if (r == 1 && c == 4)
        return getKeyIDByChar('4');  //4
    else if (r == 1 && c == 5)
        return getKeyIDByChar('5');  //5
    else if (r == 1 && c == 6)
        return getKeyIDByChar('6');  //6
    else if (r == 1 && c == 7)
        return getKeyIDByChar('7');  //7
    else if (r == 1 && c == 8)
        return getKeyIDByChar('8');  //8
    else if (r == 1 && c == 9)
        return getKeyIDByChar('9');  //9
    else if (r == 1 && c == 10)
        return getKeyIDByChar('0');  //0
    else if (r == 1 && c == 11)
        return getKeyIDByChar('-');  //-
    else if (r == 1 && c == 12)
        return getKeyIDByChar('=');  //=
    else if (r == 1 && c == 13)
        return 0x2A;  //backspace
    else if (r == 2 && c == 0)
        return 0x2B;  //tab
    else if (r == 2 && c == 1)
        return getKeyIDByChar('q');  //q
    else if (r == 2 && c == 2)
        return getKeyIDByChar('w');  //w
    else if (r == 2 && c == 3)
        return getKeyIDByChar('e');  //e
    else if (r == 2 && c == 4)
        return getKeyIDByChar('r');  //r
    else if (r == 2 && c == 5)
        return getKeyIDByChar('t');  //t
    else if (r == 2 && c == 6)
        return getKeyIDByChar('y');  //y
    else if (r == 2 && c == 7)
        return getKeyIDByChar('u');  //u
    else if (r == 2 && c == 8)
        return getKeyIDByChar('i');  //i
    else if (r == 2 && c == 9)
        return getKeyIDByChar('o');  //o
    else if (r == 2 && c == 10)
        return getKeyIDByChar('p');  //p
    else if (r == 2 && c == 11)
        return getKeyIDByChar('[');  //[
    else if (r == 2 && c == 12)
        return getKeyIDByChar(']');  //]
    else if (r == 2 && c == 13)
        return getKeyIDByChar('\\');  //back slash
    else if (r == 3 && c == 0)
        return 0x39;  //Caplock
    else if (r == 3 && c == 1)
        return getKeyIDByChar('a');  //a
    else if (r == 3 && c == 2)
        return getKeyIDByChar('s');  //s
    else if (r == 3 && c == 3)
        return getKeyIDByChar('d');  //d
    else if (r == 3 && c == 4)
        return getKeyIDByChar('f');  //f
    else if (r == 3 && c == 5)
        return getKeyIDByChar('g');  //g
    else if (r == 3 && c == 6)
        return getKeyIDByChar('h');  //h
    else if (r == 3 && c == 7)
        return getKeyIDByChar('j');  //j
    else if (r == 3 && c == 8)
        return getKeyIDByChar('k');  //k
    else if (r == 3 && c == 9)
        return getKeyIDByChar('l');  //l
    else if (r == 3 && c == 10)
        return getKeyIDByChar(';');  //;
    else if (r == 3 && c == 11)
        return getKeyIDByChar('\'');  //'
    else if (r == 3 && c == 12)
        return 0x28;  //enter
    else if (r == 3 && c == 13)
        return 0x4C;  //del
    else if (r == 4 && c == 0)
        return 0x00;  //leftshift
    else if (r == 4 && c == 1)
        return getKeyIDByChar('z');  //z
    else if (r == 4 && c == 2)
        return getKeyIDByChar('x');  //x
    else if (r == 4 && c == 3)
        return getKeyIDByChar('c');  //c
    else if (r == 4 && c == 4)
        return getKeyIDByChar('v');  //v
    else if (r == 4 && c == 5)
        return getKeyIDByChar('b');  //b
    else if (r == 4 && c == 6)
        return getKeyIDByChar('n');  //n
    else if (r == 4 && c == 7)
        return getKeyIDByChar('m');  //m
    else if (r == 4 && c == 8)
        return getKeyIDByChar(',');  //,
    else if (r == 4 && c == 9)
        return getKeyIDByChar('.');  //.
    else if (r == 4 && c == 10)
        return 0x38;  ///
    else if (r == 4 && c == 11)
        return 0x00;  //right shift
    else if (r == 4 && c == 12)
        return 0x4D;  //end
    else if (r == 4 && c == 13)
        return 0x4A;  //home
    else if (r == 5 && c == 0)
        return 0x00;  //left ctrl
    else if (r == 5 && c == 1)
        return 0xE3;  //left os
    else if (r == 5 && c == 2)
        return 0xE2;  //left alt
    else if (r == 5 && c == 3)
        return 0x2C;  //space
    else if (r == 5 && c == 4)
        return 0xE6;  //right alt
    else if (r == 5 && c == 5)
        return 0xE7;  //right os
    else if (r == 5 && c == 6)
        return 0x00;  //fn
    else if (r == 5 && c == 7)
        return 0x00;  //right ctrl
    else if (r == 5 && c == 8)
        return 0x50;  //left
    else if (r == 5 && c == 9)
        return 0x51;  //down
    else if (r == 5 && c == 10)
        return 0x52;  //up
    else if (r == 5 && c == 11)
        return 0x4F;  //right
    else if (r == 5 && c == 12)
        return 0x4E;  //pgdown
    else if (r == 5 && c == 13)
        return 0x4B;  //pgup
    else
        return 0x00;
#elif defined(KEYBOARD_LAYOUT_16)
    if (r == 0 && c == 0)
        return getKeyIDByChar('a');
    else if (r == 0 && c == 1)
        return getKeyIDByChar('b');
    else if (r == 0 && c == 2)
        return getKeyIDByChar('c');
    else if (r == 0 && c == 3)
        return getKeyIDByChar('d');
    else if (r == 1 && c == 0)
        return getKeyIDByChar('e');
    else if (r == 1 && c == 1)
        return getKeyIDByChar('f');
    else if (r == 1 && c == 2)
        return getKeyIDByChar('g');
    else if (r == 1 && c == 3)
        return getKeyIDByChar('h');
    else if (r == 2 && c == 0)
        return getKeyIDByChar('i');
    else if (r == 2 && c == 1)
        return getKeyIDByChar('j');
    else if (r == 2 && c == 2)
        return getKeyIDByChar('k');
    else if (r == 2 && c == 3)
        return getKeyIDByChar('l');
    else if (r == 3 && c == 0)
        return getKeyIDByChar('m');
    else if (r == 3 && c == 1)
        return getKeyIDByChar('n');
    else if (r == 3 && c == 2)
        return getKeyIDByChar('o');
    else if (r == 3 && c == 3)
        return getKeyIDByChar('p');
    else
        return 0x00;
#endif
    return 0x00;
}

uint8_t getKeyAsciiByRC(const uint8_t r, const uint8_t c) {
#if defined(KEYBOARD_LAYOUT_84)
    return 0x00;
#elif defined(KEYBOARD_LAYOUT_16)
    if (r == 0 && c == 0)
        return 'a';
    else if (r == 0 && c == 1)
        return 'b';
    else if (r == 0 && c == 2)
        return 'c';
    else if (r == 0 && c == 3)
        return 'd';
    else if (r == 1 && c == 0)
        return 'e';
    else if (r == 1 && c == 1)
        return 'f';
    else if (r == 1 && c == 2)
        return 'g';
    else if (r == 1 && c == 3)
        return 'h';
    else if (r == 2 && c == 0)
        return 'i';
    else if (r == 2 && c == 1)
        return 'j';
    else if (r == 2 && c == 2)
        return 'k';
    else if (r == 2 && c == 3)
        return 'l';
    else if (r == 3 && c == 0)
        return 'm';
    else if (r == 3 && c == 1)
        return 'n';
    else if (r == 3 && c == 2)
        return 'o';
    else if (r == 3 && c == 3)
        return 'p';
    else
        return 0x00;
#endif
    return 0x00;
}

#endif