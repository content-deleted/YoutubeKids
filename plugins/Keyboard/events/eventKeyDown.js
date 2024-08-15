export const id = "PRESS_KEYBOARD";
export const name = "Handle Keyboard Pressed";
const groups = ["EVENT_GROUP_DIALOGUE"];

export const fields = [
  {
    key: "index_variable",
    label: "Select Index Variable",
    type: "variable",
    defaultValue: "LAST_VARIABLE",
  },
  {
    key: "cursor_variable",
    label: "Select Cursor Variable",
    type: "variable",
    defaultValue: "LAST_VARIABLE",
  },
//   ...Array(4).map(x=>(
//     {
//         key: "name_variable_"+x,
//         label: "Variable To Store Character "+x,
//         type: "variable",
//         defaultValue: "LAST_VARIABLE",
//     }
//   ))
];

export const compile = (input, helpers) => {
  const { _stackPop, getVariableAlias, _stackPushConst, _stackPushReference, _stackPush, _callNative, appendRaw, _displayText, _overlayClear, _overlayMoveTo, textDialogue, _overlayWait, _loadText, _string, _addNL, _loadStructuredText } = helpers;

  const variableAlias1 = getVariableAlias(input.cursor_variable);
  _stackPush(variableAlias1);

  const variableAlias2 = getVariableAlias(input.index_variable);
  _stackPush(variableAlias2);

//   for(let i= 0; i < 4; i++) {
//     const a = getVariableAlias(input["name_variable_"+i]);
//     _stackPush(a);
//   }

  _callNative("press_keyboard_input");

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
