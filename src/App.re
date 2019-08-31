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
  | Drag(id) => {
      todos: state.todos,
      dragElement: Array.keep(state.todos, todo => todo.id === id)[0],
    }
  | Drop(id) => {
      todos:
        switch (state.dragElement) {
        | None => state.todos
        | Some(dragElement) =>
          let dragIndex =
            switch (
              Array.getIndexBy(state.todos, todo => todo.id === dragElement.id)
            ) {
            | None => 0
            | Some(index) => index
            };

          let dropIndex =
            switch (Array.getIndexBy(state.todos, todo => todo.id === id)) {
            | None => Array.length(state.todos)
            | Some(index) => index
            };

          if (dragIndex < dropIndex) {
            let beforeDrag =
              Array.slice(state.todos, ~offset=0, ~len=dragIndex);
            let dragToDrop =
              Array.slice(
                state.todos,
                ~offset=dragIndex + 1,
                ~len=dropIndex - dragIndex,
              );
            let dropToEnd =
              Array.slice(
                state.todos,
                ~offset=dropIndex + 1,
                ~len=Array.length(state.todos) - dropIndex,
              );

            Array.concatMany([|
              beforeDrag,
              dragToDrop,
              [|dragElement|],
              dropToEnd,
            |]);
          } else {
            let beforeDrop =
              Array.slice(state.todos, ~offset=0, ~len=dropIndex);
            let dropToDrag =
              Array.slice(
                state.todos,
                ~offset=dropIndex,
                ~len=dragIndex - dropIndex,
              );
            let dragToEnd =
              Array.slice(
                state.todos,
                ~offset=dragIndex + 1,
                ~len=Array.length(state.todos) - (dragIndex + 1),
              );

            Array.concatMany([|
              beforeDrop,
              [|dragElement|],
              dropToDrag,
              dragToEnd,
            |]);
          };
        },
      dragElement: None,
    }
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