# Resistor Library: Friend Function Refactor

**Project Architect:** Lenny Mubea

An educational C++ mini-library for EEE students to practice **encapsulation** and **clean engineering computation** by refactoring “getter-heavy” code into **friend-function** based engineering utilities.

---

## 1) The Current Problem

The starter code represents a `Resistor` as a C++ class with private data (`label`, `resistance`, `tolerance`) and public *getters* such as:

- `r1.getR()` for resistance (Ω)
- `r1.getT()` for tolerance (fraction, e.g., `0.05` for 5%)
- `r1.getL()` for label

This approach is fine for tiny programs, but it becomes **clunky** in real engineering formulas because you end up writing expressions like:

- `V = I * r.getR()`
- `P = (V*V) / r.getR()`
- `Rmin = r.getR() * (1 - r.getT())`

As formulas grow (more components, more steps, more checks), getter-chaining hurts readability and makes the “engineering meaning” harder to see.

---

## 2) The Design Goal

We refactor toward **friend functions** so engineering logic can access a resistor’s private fields *directly*, without bloating the public API or chaining getters everywhere.

### Why friend functions?

- **Cleaner formulas:** engineering code reads like engineering not spaghetti code.
- **Encapsulation preserved:** component data stays private; only selected engineering functions are trusted.
- **Efficient access:** no additional indirection or extra temporary objects.

In this lab, you will only edit:

1. **Friend declarations inside `class Resistor`**, and
2. **Function implementations at the bottom of `main.cpp`**

This enforces a realistic pattern: the component stays “closed,” while engineering utilities evolve.

---

## 3) Team Member Tasks (Choose One)

Implement exactly **one** of the tasks below.

### Important signature rule
All task functions are designed to accept at least one `Resistor` parameter so they can be found via **ADL (Argument-Dependent Lookup)** when called from `main()`.

For each task, add:

1) A friend declaration inside `class Resistor`:

```cpp
friend /* signature here */;
```

2) The matching function definition at the bottom of the file.

---

### Task 1: Series Combiner

**C++ signature**
```cpp
double seriesResistance(const Resistor& a, const Resistor& b);
```

**Engineering formula**

$R_{eq} = R_1 + R_2$

---

### Task 2: Power Safety

**C++ signature**
```cpp
bool isPowerSafe(const Resistor& r, double voltageV, double maxPowerW);
```

**Engineering formula**

$P = \dfrac{V^2}{R}$

Return `true` if $P \le P_{max}$.

---

### Task 3: Tolerance Range

**C++ signature**
```cpp
void toleranceRange(const Resistor& r, double& rMin, double& rMax);
```

**Engineering formulas**

$R_{min} = R(1 - t)$

$R_{max} = R(1 + t)$

Where $t$ is tolerance as a fraction (e.g., 5% → $t=0.05$).

---

### Task 4: Voltage Drop

**C++ signature**
```cpp
double voltageDrop(const Resistor& r, double currentA);
```

**Engineering formula**

$V = IR$

---

### Task 5:  Thermal Derating

**C++ signature**
```cpp
double thermalDeratedMaxPower(const Resistor& r, double ratedPowerW, double ambientTempC);
```

**Engineering model (simple linear derating)**

Let $T_{start}=70^\circ C$ and $T_{max}=155^\circ C$.

- If $T \le T_{start}$: $P_{max}(T)=P_{rated}$
- If $T \ge T_{max}$: $P_{max}(T)=0$
- Otherwise:

$P_{max}(T) = P_{rated}\left(1 - \dfrac{T - T_{start}}{T_{max} - T_{start}}\right)$

---

### Task 6: Parallel Combiner

**C++ signature**
```cpp
double parallelResistance(const Resistor& a, const Resistor& b);
```

**Engineering formula**

$\dfrac{1}{R_{eq}} = \dfrac{1}{R_1} + \dfrac{1}{R_2}$

(Equivalently $R_{eq} = \dfrac{R_1R_2}{R_1 + R_2}$)

---

### Task 7: AC Impedance

**C++ signature**
```cpp
double acImpedanceMagnitude(const Resistor& r);
```

**Engineering fact (ideal resistor)**

$Z = R$ and $|Z| = R$

---

### Task 8: Quality Control

**C++ signature**
```cpp
bool qualityCheck(const Resistor& r, string& report);
```

**Engineering checks **

- Resistance must be positive: $R > 0$
- Tolerance must be sensible: $0 \le t < 1$
- Label must be non-empty

Return `true` if all checks pass; otherwise return `false` and write a short failure reason into `report`.

---

## 4 Git Workflow 

Follow this exactly 

1) **Clone the repository**

```bash
git clone <PASTE_GITHUB_REPO_URL_HERE>
cd Resistor-Lab
```

2) **Create a feature branch** (replace `X` with your task letter and number)

```bash
git checkout -b feature-task-X
```

3) **Implement your logic**

- Open `main.cpp`
- Only edit:
  - the `class Resistor` friend declarations, and
  - the bottom of the file where you place your function definition(s)

4) **Test in `main()`**

- Call your function(s) in `main()` and print results.
- Make sure it compiles and runs.

Example build (Linux/macOS):

```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o resistor_lab
./resistor_lab
```

5) **Stage your changes**

```bash
git add main.cpp
```

6) **Commit with the required message format**

```bash
git commit -m "Refactor: Added [YourFunctionName] friend function for Task [N]"
```

Example:

- `Refactor: Added parallelCombiner friend function for Task 6`

7) **Push your branch**

```bash
git push -u origin feature-task-X
```

8) **Open a Pull Request on GitHub**

- Go to the repo on GitHub
- Click **Compare & pull request**
- Add a short description (what you implemented + how you tested)
- Request a review

---

## 5) Conflict Resolution 

Merge conflicts are normal; don’t panic.

1) **Pull the latest changes**

```bash
git checkout feature-task-X
git pull origin main
```

2) If Git reports a conflict in `main.cpp`, open it and look for markers:

```text
<<<<<<< HEAD
...your code...
=======
...their code...
>>>>>>> origin/main
```

3) **Decide the final correct code**

- Keep the correct friend declarations
- Keep both task implementations if they don’t clash
- Remove the conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`)

4) **Mark as resolved and finish**

```bash
git add main.cpp
git commit -m "Resolve merge conflict"
git push
```

---

### Notes

- Keep functions small and focused.
- Validate units (Ω, V, A, W, °C).
- Avoid changing the public getters unless explicitly instructed.
- For more detailed instructions look at the Contributor Guide doc.
