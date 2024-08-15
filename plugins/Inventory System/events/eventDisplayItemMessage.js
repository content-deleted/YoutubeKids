export const id = "INVENTORY_DISPLAY_ITEM_MESSAGE";
export const name = "Display Inventory Message";
const groups = ["Inventory"];

export const fields = [
  {
    key: "item_id",
    label: "ID of item to display message for",
    type: "variable",
    defaultValue: "100",
  },
  {
    key: "message_type",
    label: "Message type to perform ['give','drop','description']",
    type: "text",
    defaultValue: "give",
  }
];


export const compile = (input, helpers) => {
    const { _stackPush, _stackPop, getVariableAlias, _stackPushConst, _callNative, appendRaw, _displayText, _overlayClear, _overlayMoveTo, textDialogue, _overlayWait, _loadText, _string, _addNL, _loadStructuredText } = helpers;
    _overlayClear(0, 0, 20, 18, ".UI_COLOR_WHITE", true);
    _overlayMoveTo(0, 14, ".OVERLAY_IN_SPEED");


    const va = getVariableAlias(input.item_id);
    _stackPush(va);

    switch(input.message_type) {
    case "give":
        _callNative("inventory_add");
        _callNative("inventory_get_item_give_message");
        break;
    case "drop":
        _callNative("inventory_remove");
        _callNative("inventory_get_item_drop_message");
        break;
    case "description":
        _callNative("inventory_get_item_description_message");
        break;
    }
    _stackPop(1);

    _displayText();

    _overlayWait(true, [
        ".UI_WAIT_WINDOW",
        ".UI_WAIT_TEXT",
        ".UI_WAIT_BTN_A",
    ]);

    _overlayMoveTo(0, 18, ".OVERLAY_OUT_SPEED");
    _overlayWait(true, [".UI_WAIT_WINDOW", ".UI_WAIT_TEXT"]);

    _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
  waitUntilAfterInitFade: true,
};
