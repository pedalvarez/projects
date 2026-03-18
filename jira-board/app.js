const storageKey = "jira-board-theme";
const defaultTheme = "light";
const seedTasks = [
  { id: createTaskId(), title: "Define API contract", column: "todo" },
  { id: createTaskId(), title: "Build authentication flow", column: "inprogress" },
  { id: createTaskId(), title: "Run QA on payment checkout", column: "review" },
  { id: createTaskId(), title: "Deploy staging build", column: "done" },
];

const lists = [...document.querySelectorAll(".task-list")];
const template = document.getElementById("task-template");
const form = document.getElementById("new-task-form");
const titleInput = document.getElementById("new-task-title");
const themeToggle = document.getElementById("theme-toggle");
const themeToggleLabel = themeToggle.querySelector(".theme-toggle-label");
const body = document.body;
const prefersDarkScheme = window.matchMedia("(prefers-color-scheme: dark)");

let tasks = [...seedTasks];

function createTaskId() {
  if (typeof crypto !== "undefined" && typeof crypto.randomUUID === "function") {
    return crypto.randomUUID();
  }

  return `task-${Date.now()}-${Math.random().toString(16).slice(2)}`;
}

function setTheme(theme) {
  const normalizedTheme = theme === "dark" ? "dark" : defaultTheme;

  body.dataset.theme = normalizedTheme;
  themeToggle.setAttribute("aria-pressed", String(normalizedTheme === "dark"));
  themeToggleLabel.textContent = normalizedTheme === "dark" ? "Light mode" : "Dark mode";
}

function initializeTheme() {
  const savedTheme = localStorage.getItem(storageKey);
  const initialTheme = savedTheme ?? (prefersDarkScheme.matches ? "dark" : defaultTheme);

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

function handleDrop(event, list) {
  event.preventDefault();
  list.classList.remove("drag-over");

  const taskId = event.dataTransfer.getData("text/plain");
  const targetColumn = list.dataset.column;

  tasks = tasks.map((task) => (task.id === taskId ? { ...task, column: targetColumn } : task));
  render();
}

function syncSystemTheme(event) {
  if (!localStorage.getItem(storageKey)) {
    setTheme(event.matches ? "dark" : defaultTheme);
  }
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
    handleDrop(event, list);
  });
});

form.addEventListener("submit", (event) => {
  event.preventDefault();
  const title = titleInput.value.trim();

  if (!title) {
    return;
  }

  tasks.unshift({ id: createTaskId(), title, column: "todo" });
  titleInput.value = "";
  render();
});

themeToggle.addEventListener("click", () => {
  const nextTheme = body.dataset.theme === "dark" ? defaultTheme : "dark";
  localStorage.setItem(storageKey, nextTheme);
  setTheme(nextTheme);
});

if (typeof prefersDarkScheme.addEventListener === "function") {
  prefersDarkScheme.addEventListener("change", syncSystemTheme);
} else if (typeof prefersDarkScheme.addListener === "function") {
  prefersDarkScheme.addListener(syncSystemTheme);
}

initializeTheme();
render();
