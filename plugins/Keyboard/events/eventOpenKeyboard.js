export const id = "OPEN_KEYBOARD";
export const name = "Handle Keyboard Input";
const groups = ["EVENT_GROUP_DIALOGUE"];

export const fields = [
  {
    key: "index_variable",
    label: "Select Index Variable",
    type: "variable",
    defaultValue: "LAST_VARIABLE",
  },
  {
    key: `direction_num`,
    label: "Direction",
    type: "number",
    min: 0,
    max: 3,
    width: "50%",
    defaultValue: 1,
  },
];



export const compile = (input, helpers) => {
  const { _stackPop, getVariableAlias, _stackPushConst, _stackPushReference, _stackPush, _callNative, appendRaw, _displayText, _overlayClear, _overlayMoveTo, textDialogue, _overlayWait, _loadText, _string, _addNL, _loadStructuredText } = helpers;

//   const { getVariableAlias, actorGetPosition, _set, _declareLocal } = helpers;

//   const actors = Array(5).map((x,i) => getVariableAlias(i));
//   const actorRefs = _declareLocal("actor", 4);
//   _set(actorRef, variableAlias);

//   const afterbuttonsLable = getNextLabel();
//   const indexRef = getVariableAlias(input.index_variable);

//   actorGetPosition(input.vectorX, input.vectorY, input.units);

//   appendRaw(`
// VM_IF_CONST             .LT, ${indexRef}, ${buttons.length}, ${afterbuttonsLable}$, 0
// `);
//   let rowCount = buttons.length;
//   let nextRowLabel = null;
//   for(let i = 0; i < lineLenghts.length; i++) {
//     nextRowLabel = getNextLabel();
//     rowCount += lineLenghts[i];
//     appendRaw(`
//     VM_IF_CONST             .LT, ${indexRef}, ${rowCount}, ${nextRowLabel}$, 0
//     `);

//     _label(nextRowLabel);
//   }
//   _label(afterbuttonsLable);

  // I tried ^
  _stackPushConst(input.direction_num);
  console.log(input.direction_num);

  const variableAlias = getVariableAlias(input.index_variable);
  _stackPush(variableAlias);

  _callNative("move_keyboard_input");

  _stackPop(2);

  // appendRaw(`
  // VM_PUSH_CONST 0  ; This is our text pointer
  // VM_CALL_NATIVE start_keyboard_input
  // VM_POP 1
  // `);

    // _overlayClear(0, 0, 20, 18, ".UI_COLOR_WHITE", true);
    // _overlayMoveTo(0, 14, ".OVERLAY_IN_SPEED");
    // _displayText();

    // _overlayWait(true, [
    //     ".UI_WAIT_WINDOW",
    //     ".UI_WAIT_TEXT",
    //     ".UI_WAIT_BTN_A",
    // ]);

    // _overlayMoveTo(0, 18, ".OVERLAY_OUT_SPEED");
    // _overlayWait(true, [".UI_WAIT_WINDOW", ".UI_WAIT_TEXT"]);

    // appendRaw(`; go back to start of the loop if the character is not null
    //     VM_IF_CONST  .NE, .ARG0, 1, LINK_TEXT_LOOP_START, 0

    //     VM_POP 2
    // `);

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
