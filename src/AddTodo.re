module Styles = {
  open Css;
  let newLabel = style([position(absolute), left(px(52)), color(grey)]);
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
    <div className=SharedStyles.actionContainer> {Icons.getIcon(Add)} </div>
    <EditableField onSubmit isDone=false onFieldClick />
    {isLabelActive
       ? <div className=Styles.newLabel> {React.string("New Item")} </div>
       : React.null}
  </div>;
};