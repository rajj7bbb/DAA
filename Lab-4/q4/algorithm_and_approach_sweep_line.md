# Algorithm & Approach

A naive approach of checking every timestamp or testing interval overlaps pairwise would take $\mathcal{O}(n^2)$ time. Instead, we use an **Event-Driven Sweep-Line Algorithm**:

---

### **Step 1: Event Representation**
Decompose each person's attendance interval $[a_i, b_i]$ into two discrete chronological events:
* **Entry Event:** $(\text{time} = a_i, \text{type} = +1)$ — a person arrives.
* **Exit Event:** $(\text{time} = b_i, \text{type} = -1)$ — a person leaves.

For $n$ persons, create an array of $2n$ events.

---

### **Step 2: Sorting Events**
* Sort all $2n$ events in ascending order of their `time` using `qsort` ($\mathcal{O}(2n \log(2n)) = \mathcal{O}(n \log n)$).
* Because all timestamps are strictly distinct, there are no simultaneous entry/exit conflicts to resolve.

---

### **Step 3: Sweep-Line Linear Scan**
1. Initialize `count = 0`, `maxCount = 0`, and `maxTime = 0`.
2. Sweep through the sorted events from left to right:
   * **Update running attendance:** `count += events[i].type`
   * **If `count > maxCount`:**
     * `maxCount = count`
     * `maxTime = events[i].time`

---

### **Time Complexity Analysis**
$$\text{Total Time Complexity} = \underbrace{\mathcal{O}(n)}_{\text{Input / Event Creation}} + \underbrace{\mathcal{O}(n \log n)}_{\text{Sorting } 2n \text{ Events}} + \underbrace{\mathcal{O}(n)}_{\text{Linear Sweep}} = \mathcal{O}(n \log n)$$
