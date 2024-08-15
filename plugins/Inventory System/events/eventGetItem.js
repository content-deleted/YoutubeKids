export const id = "INVENTORY_GET_ITEM_EVENT";
export const name = "Inventory Get Item ID";
const groups = ["Inventory"];

export const fields = [
  // {
  //   key: "slot_id",
  //   label: "Slot to get item id from",
  //   type: "number",
  //   defaultValue: 1,
  // },
  {
    key: "slot_id_variable",
    label: "Variable to get slot ID",
    type: "variable",
    defaultValue: "LAST_VARIABLE",
  },
  // {
  //   key: `idFromVariable`,
  //   label: "Use variable for slot id?",
  //   type: "checkbox",
  //   defaultValue: "true",
  // },
  {
    key: "store_variable",
    label: "Variable to store ID",
    type: "variable",
    defaultValue: "LAST_VARIABLE",
  },
];



export const compile = (input, helpers) => {
  const { _stackPop, getVariableAlias, _stackPushConst, _stackPushReference, _stackPush, _callNative, appendRaw, _displayText, _overlayClear, _overlayMoveTo, textDialogue, _overlayWait, _loadText, _string, _addNL, _loadStructuredText } = helpers;

  // if(!input.idFromVariable)
  //   _stackPushConst(input.slot_id);
  // else {
    const va = getVariableAlias(input.slot_id_variable);
    _stackPush(va);
  // }

  const variableAlias = getVariableAlias(input.store_variable);
  _stackPush(variableAlias);

  _callNative("inventory_get_item_id");

  _stackPop(2);

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
