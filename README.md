---

# C++ CLI Todo Manager 📝

A simple command-line TODO manager written in C++. Allows you to **view**, **add**, **mark as done**, and **delete** TODO items.

---

## Features

* **View TODOs** with clear status (`✔` done, `X` not done)
* **Add TODOs** with multi-word names and details
* **Mark TODOs as done** and persist changes
* **Delete TODOs in memory** by marking them as `ID = -1`
* Simple **text file storage** (`./todos/todos`)
* Lightweight, pure C++ implementation, no external libraries

---

## Folder Structure

```
.
├── run.sh          # Build script
├── source/         # All .cpp source files
├── include/        # Header files (.h / .hpp)
└── todos/          # Folder containing the todo file
    └── todos       # Text file storing all todos
```

---

## Build & Run

### 1️⃣ Build

Use the included `run.sh` script:

```bash
./run.sh
```

* Cleans old files
* Compiles all `.cpp` files in `source/`
* Links them into an executable called `app`
* Deletes intermediate object files
* ✅ Prints success message when done

---

### 2️⃣ Run

```bash
./app
```

You’ll see a menu like:

```
Welcome! Please pick an action:
1-View TODOs
2-Add TODO
3-Mark a TODO as done
4-Delete a TODO
Option:
```

---

## Usage

* **View TODOs:** Shows all current todos with their status.
* **Add TODO:** Enter a name and details. IDs are automatically assigned.
* **Mark as Done:** Enter the ID of a todo to mark it as done.
* **Delete TODO:** Enter the ID of a todo to remove it from memory (ID is set to -1).

> Note: Deleted todos remain in the file but are ignored in display and further operations.

---

## Example `todos` file

```text
#ID$NAME$DETAILS$ISDONE
0$Code an OS$Become the second Terry Davis$0
1$Write blog$Publish a new post about C++$1
```

---

## Notes

* Multi-word names and details are fully supported.
* IDs are automatically incremented and never reused for new todos.
* The program is fully terminal-based and lightweight.

---

## License

MIT License – free to use, modify, and share!

---
