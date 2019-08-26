type item = {
  id: int,
  text: string,
  isDone: bool,
};

type action =
  | NewTodo(string)
  | Toggle(int)
  | Update(int, string)
  | Delete(int)
  | DragStart(int)
  | DragStop(int);