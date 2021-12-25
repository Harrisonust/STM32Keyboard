/*
 * KeyID.h
 *
 *  Created on: Dec 25, 2021
 *      Author: Harrison
 */

#ifndef INC_KEYID_H_
#define INC_KEYID_H_

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