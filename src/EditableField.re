open Belt;
module Styles = {
  open Css;
  let text = isDone => {
    let baseStyle =
      style([
        flexGrow(1.0),
        margin(zero),
        padding2(~v=rem(0.25), ~h=rem(0.75)),
        focus([outline(px(0), none, white)]),
        width(`percent(100.0)),
        whiteSpace(`preWrap),
        wordWrap(`breakWord),
        minHeight(rem(1.5)),
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
  let inputContainer = style([flex3(~grow=1.0, ~shrink=1.0, ~basis=`auto)]);
};

[@react.component]
let make = (~text="", ~onSubmit, ~isDone, ~onFieldClick=() => ()) => {
  let divRef = React.useRef(Js.Nullable.null);

  let onKeyPress = event =>
    if (!ReactEvent.Keyboard.shiftKey(event)) {
      switch (ReactEvent.Keyboard.key(event)) {
      | "Enter" =>
        onSubmit(ReactEvent.Synthetic.currentTarget(event)##innerHTML);
        ignore(
          Webapi.Dom.(
            divRef
            ->React.Ref.current
            ->Js.Nullable.toOption
            ->Option.flatMap(Element.asHtmlElement)
            ->Option.map(__x => HtmlElement.setInnerHTML(__x, ""))
          ),
        );
        ReactEvent.Synthetic.preventDefault(event);
      | _ => ()
      };
    };

  <div className=Styles.inputContainer>
    <div
      contentEditable=true
      dangerouslySetInnerHTML={"__html": text}
      ref={ReactDOMRe.Ref.domRef(divRef)}
      onDrop={e => ReactEvent.Mouse.preventDefault(e)}
      className={Styles.text(isDone)}
      onClick={_ => onFieldClick()}
      onBlur={e =>
        onSubmit(ReactEvent.Synthetic.currentTarget(e)##innerHTML)
      }
      onKeyPress
    />
  </div>;
};