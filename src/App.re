open Belt;
type state = {
  todos: array(Types.item),
  dragElement: option(Types.item),
};

let lastId = ref(0);

let reducer = (state, action: Types.action) => {
  switch (action) {
  | NewTodo(text) =>
    lastId := lastId^ + 1;
    {
      todos:
        Array.concat(state.todos, [|{id: lastId^, isDone: false, text}|]),
      dragElement: None,
    };
  | Toggle(id) => {
      todos:
        Array.map(state.todos, todo =>
          todo.id === id ? {...todo, isDone: !todo.isDone} : todo
        ),
      dragElement: None,
    }
  | Update(id, text) => {
      todos:
        Array.map(state.todos, todo =>
          todo.id === id ? {...todo, text} : todo
        ),
      dragElement: None,
    }
  | Delete(id) => {
      todos: Array.keep(state.todos, todo => todo.id !== id),
      dragElement: None,
    }
  | Drag(id) =>
    Array.reduce(state.todos, {todos: [||], dragElement: None}, (acc, item) =>
      if (item.id === id) {
        {
          dragElement: Some(item),
          todos: Array.concat(acc.todos, [|item|]),
        };
      } else {
        {dragElement: None, todos: acc.todos};
      }
    )
  | Drop(id) =>
    Array.reduce(state.todos, {todos: [||], dragElement: None}, (acc, item) =>
      if (item.id === id) {
        {
          dragElement: None,
          todos:
            switch (state.dragElement) {
            | None => acc.todos
            | Some(dItem) => Array.concat(acc.todos, [|item, dItem|])
            },
        };
      } else {
        {dragElement: None, todos: acc.todos};
      }
    )
  };
};

[@react.component]
let make = () => {
  let ({todos}: state, dispatch) =
    React.useReducer(reducer, {todos: [||], dragElement: None});

  <div className=AppStyles.appContainer>
    <h1 className=AppStyles.heading> {React.string("TODO List")} </h1>
    {ReasonReact.array(
       Array.map(todos, todo =>
         <TodoItem key={"todo" ++ string_of_int(todo.id)} dispatch todo />
       ),
     )}
    <AddTodo dispatch />
  </div>;
};