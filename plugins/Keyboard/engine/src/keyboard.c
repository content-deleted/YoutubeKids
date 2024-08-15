#pragma bank 3

//#include <gbdk/platform.h>
#include "vm.h"
#include "actor.h"
#include "vm_gameboy.h"
// #include "ui.h"

//#include <gb/gb.h>
#include <stdint.h>
// #include <stdio.h>

// extern unsigned char ui_text_data[TEXT_MAX_LENGTH];

// unsigned char buffer_text_data[TEXT_MAX_LENGTH];

// menu data
// menu data
const int lineCount = 5;
const int lineLength = 14;

struct button
{
    int x;
    int y;
    int length;
};
const int buttonCount = 3;
struct button buttons[3] = {
    {.length = 4, .x = 8, .y = 52},
    {.length = 4, .x = 58, .y = 52},
    {.length = 3, .x = 129, .y = 52},
};

const int maxUnderscores = 4;

// Where does the grid of letters start
const int baseX = 25;
const int baseY = 68;
// Spacing px between each line in the letter grid
const int lineSpacing = 8;

int modulo(int a, int b) {
    return ((a % b) + b) % b;
}

// External entrypoint
// SCRIPT_CTX * THIS
void move_keyboard_input(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;
    INT16 *dir_ptr = VM_REF_TO_PTR(FN_ARG1);
    INT16 *temp_ptr = VM_REF_TO_PTR(FN_ARG0);

    int temp = (int)(*temp_ptr);
    int dir = (int)(*dir_ptr);

    int underscoreLength = 1;
    int cursorX = 0;
    int cursorY = 0;
    // very shitty and lazy cursor wrapping code
    if(temp < buttonCount) {
        if(dir < 2) {
            temp = modulo(temp + ((dir == 0) ? -1 : 1), buttonCount);
        } else {
            temp = buttonCount + (lineLength * temp) / buttonCount;
            // place at bottom for up (wrap around)
            if(dir == 2) {
                temp += (lineLength * (lineCount - 1));
            }
        }
    } else {
        if(dir < 2) {
            temp -= buttonCount;
            int line = (temp) / lineLength;
            temp = modulo(temp + ((dir == 0) ? -1 : 1), lineLength);
            temp += buttonCount + line * lineLength;
        } else {
            temp += (dir == 2) ? -lineLength : lineLength;
            if(temp < buttonCount) {
                temp = 0;
            } else if(temp >= (lineCount * lineLength + buttonCount)) {
                temp = 2;
            }
        }
    }

    if(temp < buttonCount) {
        cursorX = buttons[temp].x;
        cursorY = buttons[temp].y;
        underscoreLength = buttons[temp].length;
    } else {
        int letter = temp - buttonCount;
        cursorX = baseX + modulo(letter, lineLength) * 8;
        cursorY = baseY + (letter / lineLength) * (8 + lineSpacing);
    }

    for(int i = 1; i < maxUnderscores+1; i++) {
        actor_t *actor = actors + (UBYTE)(i) + 1;
        int x = cursorX;
        if(i < underscoreLength) x += i * 8;
        actor->pos.x = x * 16;
        actor->pos.y = cursorY * 16;
    }

    vm_set_const(THIS, 0, temp);
}

int specialChars[14] = {
    43,
    45,
    33,
    126,
    47,
    95, // heart
    95, // star
    56,
    54,
    72,
    73,
    47,
    42,
};
// External entrypoint
// SCRIPT_CTX * THIS
void press_keyboard_input(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;
    INT16 *index = VM_REF_TO_PTR(FN_ARG0);
    INT16 *temp_ptr = VM_REF_TO_PTR(FN_ARG1);

    int temp = (int)(*temp_ptr);
    int i = (int)(*index);

    int letter = 32;
    int retIndex = i;
    if(temp == 1) {
        // back
        retIndex-=1;
        vm_set_const(THIS, i, letter);
    } else {
        if(temp > 2) {
            retIndex++;
            if(temp < 2+26) {
                // capitol letters
                letter = 64+ temp -2;
                 // next two are spaces
            } else if(temp > 30 && temp < 30+26) {
                // lowercase
                letter = 96+ temp - 30;
                 // next two are spaces
            } else if(temp > 56) {
                // special
                letter = specialChars[temp - 56];
            }
        }
    }

    //vm_replace_tile_xy(THIS, 9+i, 1, 50, 0, letter);
    // set the cursor
    actor_t *cursor = actors + (UBYTE)(1);
    cursor->pos.x = (9+(retIndex - 1)) * 16 * 8;
    cursor->pos.y = (retIndex) >= 4 ? 0 : (2 * 16 * 8 + 2* 16);

    vm_set_const(THIS, 5, retIndex);
    vm_set_const(THIS, i+1, letter);
}



// // External entrypoint
// // SCRIPT_CTX * THIS
// void start_keyboard_input(SCRIPT_CTX *THIS) OLDCALL BANKED {
//     THIS;
//     INT16 *PTR = VM_REF_TO_PTR(FN_ARG0);
//     char user_input[32];
//     gets(user_input);
//     for(int i = 0; i < 32; i++) {
//         buffer_text_data[i] = buffer_text_data[i];
//         if(buffer_text_data[i] == '\0') {
//             break;
//         }
//     }
//     PTR = buffer_text_data;
// }
