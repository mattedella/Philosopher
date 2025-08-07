# 🍝 Dining Philosophers Problem

This project is an implementation of the classic **Dining Philosophers problem** written in **C** using **POSIX threads (pthreads)**.

---

## 🧠 Problem Overview

Five philosophers sit around a table. Each philosopher thinks and occasionally needs to eat. To eat, a philosopher needs **two forks**, one from the left and one from the right.

The challenge is to create a concurrency-safe system that:
- Prevents **deadlocks** (where no philosopher can proceed)
- Avoids **starvation** (where a philosopher never gets to eat)
- Ensures **data integrity** and **mutual exclusion**

---

## 🛠️ Implementation Details

- Language: **C**
- Library: **POSIX threads (pthread)**
- Synchronization: **mutexes**
- Each philosopher is a **thread**
- Forks are **mutexes** shared between neighbors
- Optional: Timestamped logging for actions

---

## 📦 Project Structure

```text
.
├── philo
│   ├── Makefile
│   ├── philo.c
│   ├── philo.h
│   ├── routine.c
│   ├── utils.c
│   └── utils_II.c
└── README.md

```

---

## 🚦 How It Works

1. Each philosopher thread loops through:
   - Thinking 🤔
   - Picking up the left and right forks 🍴
   - Eating 😋
   - Putting down the forks
   - Sleeping 😴

2. The program ensures:
   - No deadlocks (using strategies like odd/even fork order)
   - Minimal starvation (through careful synchronization)
   - Clear and timestamped output

---

## ⚙️ Compilation and Usage

### Build

```bash
make
```

### Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example

```bash
./philo 5 800 200 200
```

This launches 5 philosophers, each with:
- 800ms to die without eating
- 200ms to eat
- 200ms to sleep

Optional final argument ensures simulation stops when all philosophers have eaten the specified number of times.

---

## 📋 Rules

- A philosopher dies if they don’t eat within `time_to_die` milliseconds
- Output must be:
  - Synchronized (no mixed messages)
  - Timestamped (in ms from start)
  - Clear (e.g., `123 2 is eating`)

---

## 🔒 Common Synchronization Techniques

- **One mutex per fork**
- **Single mutex for printing**
- **Avoiding circular wait** (e.g., odd philosophers pick left first, even pick right first)

---

## ✅ Bonus Ideas

If basic requirements are met, you may implement:
- A second version using **semaphores**
- A monitor thread to check for dead philosophers
- Visualization of states
- Dynamic addition of philosophers

---

## 📄 License

This project is developed as part of the **42 School** curriculum. Feel free to reuse, modify, and learn from it!

---

## 🙌 Credits

Built by students at [42 Firenze](https://42firenze.it), with love and sockets ❤️
