open Belt;
type state = {todos: array(Types.item)};

let lastId = ref(0);

let reducer = (state, action: Types.action) => {
  switch (action) {
  | NewTodo(text) =>
    lastId := lastId^ + 1;
    {
      todos:
        Array.concat(state.todos, [|{id: lastId^, isDone: false, text}|]),
    };
  | Toggle(id) => {
      todos:
        Array.map(state.todos, todo =>
          todo.id === id ? {...todo, isDone: !todo.isDone} : todo
        ),
    }
  | Update(id, text) => {
      todos:
        Array.map(state.todos, todo =>
          todo.id === id ? {...todo, text} : todo
        ),
    }
  | Delete(id) => {todos: Array.keep(state.todos, todo => todo.id !== id)}
  };
};

[@react.component]
let make = () => {
  let ({todos}: state, dispatch) =
    React.useReducer(reducer, {todos: [||]});

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