export const id = "INVENTORY_START_EVENT";
export const name = "Init Inventory";
const groups = ["Inventory"];

export const fields = [
  {
    key: "inventory_start",
    label: "Index of variable where inventory starts",
    type: "variable",
    defaultValue: "100",
  }
];


export const compile = (input, helpers) => {
  const { _stackPop, _stackPushConst, _callNative, _addNL } = helpers;

  _stackPushConst(input.direction_num);

  _callNative("inventory_init");

  _stackPop(1);

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
