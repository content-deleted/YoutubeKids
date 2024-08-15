#pragma bank 255

//#include <gbdk/platform.h>
#include "vm.h"
#include "actor.h"
#include "vm_gameboy.h"
#include "ui.h"
#include "inventory_data.h"

//#include <gb/gb.h>
#include <stdint.h>
// #include <stdio.h>

// this is how to access the ui text pointer
extern unsigned char ui_text_data[TEXT_MAX_LENGTH];

// unsigned char buffer_text_data[TEXT_MAX_LENGTH];

const UBYTE INVENTORY_MAX = 12;
UBYTE INVENTORY_CURRENT=0;
UBYTE INVENTORY_SLOTS[12] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
// External entrypoint
// SCRIPT_CTX * THIS
void inventory_init(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;
    INT16 *temp_ptr = VM_REF_TO_PTR(FN_ARG0);
    UBYTE start = (UBYTE)(*temp_ptr);

    for(int i = start; i < start + INVENTORY_MAX; i++){
        vm_set_const(THIS, i, 0);
    }
    // save for later fuck getting this passed every op
    //INVENTORY_START = start;
}

// SCRIPT_CTX * THIS
void inventory_add(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;
    INT16 *temp_ptr = VM_REF_TO_PTR(FN_ARG0);
    UBYTE id = (UBYTE)(*temp_ptr);

    //vm_set_const(THIS, INVENTORY_START+INVENTORY_CURRENT, id);

    INVENTORY_SLOTS[INVENTORY_CURRENT] = id;

    INVENTORY_CURRENT++;
}

// SCRIPT_CTX * THIS
void inventory_remove(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;
    INT16 *temp_ptr = VM_REF_TO_PTR(FN_ARG0);
    UBYTE id = (UBYTE)(*temp_ptr);

    bool found = false;
    // shift over the array
    for(int i = 0; i < INVENTORY_MAX; i++) {
        UBYTE cur = INVENTORY_SLOTS[i];
        if(cur == id) {
            found = true;
        }
        if (found) {
            if (i + 1 < INVENTORY_MAX) {
                INVENTORY_SLOTS[i] = INVENTORY_SLOTS[i+1];
            } else {
                INVENTORY_SLOTS[i] = 0;
            }
        }
    }

    if(found)INVENTORY_CURRENT--;
}

// SCRIPT_CTX * THIS
void inventory_get_item_names(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;

    // shift over the array
    int text_ptr = 0;
    for(int i = 0; i < INVENTORY_CURRENT; i++) {
        UBYTE cur = INVENTORY_SLOTS[i];
        if(cur == 0) continue;
        for(int j = 0; j < 10; j++) {
            const int nameId = cur-1;
            if(inventory_names[nameId][j] == '\0') break;
            ui_text_data[text_ptr] = inventory_names[nameId][j];
            text_ptr++;
        }
        ui_text_data[text_ptr] = '\n';
        text_ptr++;
    }
    ui_text_data[text_ptr] = '\0';
}

// SCRIPT_CTX * THIS
void inventory_get_item_id(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;

    INT16 *temp_ptr = VM_REF_TO_PTR(FN_ARG1);
    UBYTE slot_id = (UBYTE)(*temp_ptr);

    INT16 cur = (INT16)INVENTORY_SLOTS[slot_id];

    vm_set_const(THIS, 0, cur);
}

// SCRIPT_CTX * THIS
void inventory_get_item_give_message(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;

    INT16 *temp_ptr = VM_REF_TO_PTR(FN_ARG0);
    UBYTE id = (UBYTE)(*temp_ptr);

    int text_ptr = 0;

    char * message1 = "Got item: [";
    for(int i = 0; i < 11; i++) {
        ui_text_data[text_ptr] = message1[i];
        text_ptr++;
    }
    for(int i = 0; i < 10; i++) {
        const int nameId = id-1;
        if(inventory_names[nameId][i] == '\0') break;
        ui_text_data[text_ptr] = inventory_names[nameId][i];
        text_ptr++;
    }
    char * message2 = "]!";
    for(int i = 0; i < 2; i++) {
        ui_text_data[text_ptr] = message2[i];
        text_ptr++;
    }
    ui_text_data[text_ptr] = '\0';
}

// SCRIPT_CTX * THIS
void inventory_get_item_drop_message(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;

    INT16 *temp_ptr = VM_REF_TO_PTR(FN_ARG0);
    UBYTE id = (UBYTE)(*temp_ptr);

    int text_ptr = 0;

    char message1[] = "Lost item: [";
    for(int i = 0; i < 12; i++) {
        ui_text_data[text_ptr] = message1[i];
        text_ptr++;
    }
    for(int i = 0; i < 10; i++) {
        const int nameId = id-1;
        if(inventory_names[nameId][i] == '\0') break;
        ui_text_data[text_ptr] = inventory_names[nameId][i];
        text_ptr++;
    }
    char message2[] = "]!";
    for(int i = 0; i < 2; i++) {
        ui_text_data[text_ptr] = message2[i];
        text_ptr++;
    }
    ui_text_data[text_ptr] = '\0';
}

// SCRIPT_CTX * THIS
void inventory_get_item_description_message(SCRIPT_CTX *THIS) OLDCALL BANKED {
    THIS;

    INT16 *temp_ptr = VM_REF_TO_PTR(FN_ARG0);
    UBYTE id = (UBYTE)(*temp_ptr);

    int text_ptr = 0;

    for(int i = 0; i < 200; i++) {
        const int nameId = id-1;
        if(inventory_descriptions[nameId][i] == '\0') break;
        ui_text_data[text_ptr] = inventory_descriptions[nameId][i];
        text_ptr++;
    }

    // end the string data
    ui_text_data[text_ptr] = '\0';
}