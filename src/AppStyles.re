open Css;
let appContainer =
  style([
    display(`flex),
    flexDirection(column),
    justifyContent(`spaceEvenly),
    maxWidth(`px(700)),
    margin(`auto),
    boxSizing(`borderBox),
  ]);

let heading = style([display(`block), color(grey)]);