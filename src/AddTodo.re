module Styles = {
  open Css;
  let newLabel =
    style([
      position(absolute),
      left(px(80)),
      color(grey),
      pointerEvents(none),
    ]);
};

[@react.component]
let make = (~dispatch: Types.action => unit) => {
  let (isLabelActive, setLabelActive) = React.useState(() => true);

  let onFieldClick = _ => {
    setLabelActive(_ => false);
  };
  let onSubmit = text =>
    if (String.length(text) > 0) {
      dispatch(NewTodo(text));
    } else {
      setLabelActive(_ => true);
    };

  <div className={SharedStyles.itemContainer(isLabelActive)}>
    <div className=SharedStyles.actionContainer />
    <div className=SharedStyles.actionContainer> {Icons.getIcon(Add)} </div>
    {isLabelActive
       ? <div className=Styles.newLabel> {React.string("New Item")} </div>
       : React.null}
    <EditableField onSubmit isDone=false onFieldClick />
  </div>;
};