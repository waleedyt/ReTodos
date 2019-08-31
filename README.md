# ReTodos

## What is ReTodos? Does it benefits world in any way?
It's a pet project to learn ReasonML and Reason React.
Currently, only benefit it may give to someone is to read code and learn a few ReasonML centric concepts which may not be found in docs.

## What did i learn out of it?
1. Usage of `contentEditable` instead of plain `input` field to edit todos was new and interesting, in fact its preferable once you realize the feature set that comes with it
2. Mutating HTML node via `innerHTML` and `dangerouslySetInnerHTML` with reason types and all
3. Usage of `bs-webapi` to manipulate innerhHTML of an HTML element in Reason React
4. Usage of `bs-css` or css-in-js(emotion) solution in Reason React
5. Usage of HTML5 native drag and drop api for sorting todos
6. Pattern matching, its just mind blowing how much simpler conditional flows become and how much ReasonML/Ocaml can infer to catch bugs
7. Usage of strict type checking baked in language which makes state management easier and more error proof
8. How natural React and Hooks API feels when you write them in a functional language
9. How ridiculously-blazing-fast bucklescript is when compared with any other transpiler or compiler and yes it would be a disgrace to compare with babel

## What feature set it supports?
- [x] CRUD operations for todo, duh!
- [x] Mark a todo as done
- [x] Text editing functionality with HTML5 `contentEditable` API, works like Google Keep
- [x] Sort with Drag and Drop

## Todos left for ReTodos :) in order to make it usable, at least for myself:
- [ ] Store state in local storage
- [ ] Support login via Google
- [ ] Sync state with google sheets
- [ ] Convert to Progressive Web App

## Steps to start application:
1. `yarn install`
2. `yarn start` to run the bucklescript compiler
3. `yarn server` to start the dev server to serve compiled `.js` files

