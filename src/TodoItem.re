module Styles = {
  open Css;
  let text = isDone => {
    let baseStyle =
      style([
        flexGrow(1.0),
        margin(zero),
        padding2(~v=rem(0.25), ~h=rem(0.75)),
      ]);
    switch (isDone) {
    | false => baseStyle
    | true =>
      merge([
        baseStyle,
        style([textDecoration(`lineThrough), color(grey)]),
      ])
    };
  };
  let delButton =
    style([
      border(px(0), `none, white),
      display(`flex),
      alignItems(center),
      cursor(`pointer),
      opacity(0.512),
      hover([opacity(1.0)]),
    ]);
  let checkBox = style([margin(zero), cursor(`pointer)]);
};

[@react.component]
let make = (~todo: Types.item, ~dispatch: Types.action => unit) => {
  let (isActive, setActive) = React.useState(() => false);
  let onSubmitText = text => dispatch(Update(todo.id, text));
  let handleDragStart = ev => Js.log(ev);

  <div
    className={SharedStyles.itemContainer(isActive)}
    onClick={_ => setActive(_ => false)}>
    <div
      className=SharedStyles.actionContainer
      draggable=true
      onDragStart=handleDragStart>
      {Icons.getIcon(DragHandle)}
    </div>
    <div className=SharedStyles.actionContainer>
      <input
        type_="checkbox"
        value={string_of_bool(todo.isDone)}
        onChange={_event => dispatch(Toggle(todo.id))}
        className=Styles.checkBox
      />
    </div>
    <EditableField
      text={todo.text}
      onSubmit=onSubmitText
      isDone={todo.isDone}
    />
    <div className=SharedStyles.actionContainer>
      <button
        className=Styles.delButton onClick={_ => dispatch(Delete(todo.id))}>
        {Icons.getIcon(Remove)}
      </button>
    </div>
  </div>;
};