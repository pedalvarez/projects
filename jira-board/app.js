const storageKey = "jira-board-theme";
const seedTasks = [
  { id: crypto.randomUUID(), title: "Define API contract", column: "todo" },
  { id: crypto.randomUUID(), title: "Build authentication flow", column: "inprogress" },
  { id: crypto.randomUUID(), title: "Run QA on payment checkout", column: "review" },
  { id: crypto.randomUUID(), title: "Deploy staging build", column: "done" },
];

const lists = [...document.querySelectorAll(".task-list")];
const template = document.getElementById("task-template");
const form = document.getElementById("new-task-form");
const titleInput = document.getElementById("new-task-title");
const themeToggle = document.getElementById("theme-toggle");
const body = document.body;
const prefersDarkScheme = window.matchMedia("(prefers-color-scheme: dark)");

let tasks = [...seedTasks];

function setTheme(theme) {
  body.dataset.theme = theme;
  themeToggle.setAttribute("aria-pressed", String(theme === "dark"));
  themeToggle.querySelector(".theme-toggle-label").textContent = theme === "dark" ? "Light mode" : "Dark mode";
}

function initializeTheme() {
  const savedTheme = localStorage.getItem(storageKey);
  const initialTheme = savedTheme ?? (prefersDarkScheme.matches ? "dark" : "light");

  setTheme(initialTheme);
}

function render() {
  lists.forEach((list) => {
    list.innerHTML = "";
    const columnTasks = tasks.filter((task) => task.column === list.dataset.column);

    columnTasks.forEach((task) => {
      const node = template.content.firstElementChild.cloneNode(true);
      node.dataset.taskId = task.id;
      node.querySelector(".task-title").textContent = task.title;
      attachDragHandlers(node);
      list.appendChild(node);
    });

    const count = list.closest(".column").querySelector(".task-count");
    count.textContent = String(columnTasks.length);
  });
}

function attachDragHandlers(taskNode) {
  taskNode.addEventListener("dragstart", (event) => {
    taskNode.classList.add("dragging");
    event.dataTransfer.effectAllowed = "move";
    event.dataTransfer.setData("text/plain", taskNode.dataset.taskId);
  });

  taskNode.addEventListener("dragend", () => {
    taskNode.classList.remove("dragging");
  });
}

lists.forEach((list) => {
  list.addEventListener("dragover", (event) => {
    event.preventDefault();
    list.classList.add("drag-over");
    event.dataTransfer.dropEffect = "move";
  });

  list.addEventListener("dragleave", () => {
    list.classList.remove("drag-over");
  });

  list.addEventListener("drop", (event) => {
    event.preventDefault();
    list.classList.remove("drag-over");
    const taskId = event.dataTransfer.getData("text/plain");
    const targetColumn = list.dataset.column;

    tasks = tasks.map((task) => (task.id === taskId ? { ...task, column: targetColumn } : task));
    render();
  });
});

form.addEventListener("submit", (event) => {
  event.preventDefault();
  const title = titleInput.value.trim();

  if (!title) {
    return;
  }

  tasks.unshift({ id: crypto.randomUUID(), title, column: "todo" });
  titleInput.value = "";
  render();
});

themeToggle.addEventListener("click", () => {
  const nextTheme = body.dataset.theme === "dark" ? "light" : "dark";
  localStorage.setItem(storageKey, nextTheme);
  setTheme(nextTheme);
});

prefersDarkScheme.addEventListener("change", (event) => {
  if (!localStorage.getItem(storageKey)) {
    setTheme(event.matches ? "dark" : "light");
  }
});

initializeTheme();
render();
