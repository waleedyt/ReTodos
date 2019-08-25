open Css;
let actionContainer =
  style([
    width(rem(2.0)),
    display(`flex),
    justifyContent(center),
    alignItems(center),
    cursor(`pointer),
    flex3(~grow=0.0, ~shrink=0.0, ~basis=`auto),
  ]);

let itemContainer = isActive => {
  let baseStyle =
    style([
      width(auto),
      minHeight(rem(1.85)),
      padding2(~v=rem(0.25), ~h=rem(0.25)),
      display(`flex),
      alignItems(center),
      cursor(text),
      border(px(0), solid, lightgray),
      position(relative),
    ]);
  switch (isActive) {
  | false => baseStyle
  | true =>
    merge([
      baseStyle,
      style([borderTopWidth(px(1)), borderBottomWidth(px(1))]),
    ])
  };
};

let heading = style([display(`block), color(grey)]);

let input =
  style([
    width(`percent(100.0)),
    backgroundColor(white),
    border(px(0), none, white),
    padding2(~v=rem(0.25), ~h=rem(0.75)),
    boxSizing(borderBox),
  ]);