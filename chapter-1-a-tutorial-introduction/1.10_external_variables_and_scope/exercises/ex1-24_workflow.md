# Program Workflow Visualization (Exercise 1-24)

This document visualizes how the C syntax checking program works using a **State Machine** and a **Stack**.

---

## 1. High-Level Workflow
This diagram illustrates the macro-level processing steps of the syntax checker:

```text
  +----------------------+
  | Input C Source Code  |
  +-----------+----------+
              |
              v
  +-----------+----------+
  |  ex1-24 Syntax Checker |
  +-----------+----------+
              |
      +-------+-------+
      |               |
      v               v
+-----+-----+   +-----+-----+
|  Comment  |   | String/   |
|  Filter   |   | Char Lit  |
+-----+-----+   +-----+-----+
      |               |
      +-------+-------+
              |
              v
  +-----------+----------+
  |  Verify Nesting      |
  |  Using Stack Array   |
  +-----------+----------+
              |
      +-------+-------+
      |               | (Success)
      |               +-------------> [ Success Message ]
      |
      | (Mismatch / Unmatched)
      +-----------------------------> [ Error: Print Line & Symbol ]
```

---

## 2. State Transition Diagram (FSM)
The program transitions between different states to ensure it only checks brackets when inside normal code, ignoring any brackets inside comments or string/character literals.

```text
                 +-------------------+
                 |       Start       |
                 +---------+---------+
                           |
                           v
                 +---------+---------+
           +---->|      NORMAL       |<----+
           |     +----+--------+-----+     |
           |          |        |           |
           | Get "/*" |        | Get "//"  |
           |          v        v           |
           |     +----+----+ +-+-------+   |
           |     |  MULTI  | | SINGLE  |   |
           |     | COMMENT | | COMMENT |   |
           |     +----+----+ +-+-------+   |
           |          |        |           |
           | Get "*/" |        | Get "\n"  |
           +----------+        +-----------+
                      |        |
                      +---+----+
                          |
             Get '"'/'\'' |
                          v
                 +--------+----------+
                 |       QUOTE       |
                 +--------+----------+
                          |
                          | Get matching quote
                          | (not escaped)
                          v
                 (Return to NORMAL)
```

---

## 3. Detailed Algorithm Flowchart (Workflow)
The flowchart below traces the processing flow for each character read from the input file:

```text
               +--------------------------------------+
               |    Read character c from my_getchar  | <-------------------+
               +------------------+-------------------+                     |
                                  |                                         |
                                  v                                         |
                            /-----------?\                                  |
                           /   c == EOF?  \                                 |
                           \-------------/                                  |
                              /         \                                   |
                       Yes   /           \  No                              |
                            v             v                                 |
                    /------------?\  /----------?\                          |
                   / Stack empty? \  |  What is  |                          |
                   \--------------/  |    c?     |                          |
                       /       \     \----------/                          |
                Yes   /         \ No   /   |   \                            |
                     v           v    /    |    \                           |
                [Success]   [Error:  /     |     \                          |
                            Unclosed/      |      \                         |
                            Bracket]       |       \                        |
                                   /       |        \                       |
         Slash '/'                /     Quote       Opening Bracket         |
     +---------------------------+    '"' or '\''   '{', '[', '('           |
     |                                     |               |                |
     v                                     v               v                |
+----+----+                           +----+----+     +----+----+           |
|Read char|                           |Call     |     |Push c   |           |
|d        |                           |skip_    |     |to Stack |           |
+----+----+                           |quote    |     +----+----+           |
     |                                +----+----+          |                |
     +------------+------------+           |               |                |
     | d=='*'     | d=='/'     | else      |               |                |
     v            v            v           |               |                |
+----+----+  +----+----+  +----+----+      |               |                |
|Call     |  |Call     |  |Call     |      |               |                |
|skip_    |  |skip_    |  |check_   |      |               |                |
|comment  |  |single_  |  |char(d)  |      |               |                |
|         |  |comment  |  |         |      |               |                |
+----+----+  +----+----+  +----+----+      |               |                |
     |            |            |           |               |                |
     +------------+------------+           +---------------+----------------+
     |                                                     |
     +-----------------------------------------------------+
     |
     | Closing Bracket '}', ']', ')'
     v
+----+----+
|Pop and  |
|check c  |
+----+----+
     |
     +--------------------+
     | Match              | Mismatch or Stack empty
     v                    v
[Continue]          [Report Error with line_num]
     |                    |
     +--------------------+
     |
     +----------------------------------------------------------------------+
```

---

## 4. Step-by-Step Stack Trace Example
With the input: `int main() { (a[0]); }`

| Character Read | Checking State | Stack Operation | Stack State (Bottom to Top) | Check Result |
| :---: | :---: | :---: | :---: | :---: |
| `i, n, t, ...` | Normal | Ignore | Empty `[]` | Valid |
| `(` | Normal | **Push** `'('` | `['(']` | Valid |
| `)` | Normal | **Pop** and match `'('` | Empty `[]` | Match `()` |
| `{` | Normal | **Push** `'{'` | `['{']` | Valid |
| `(` | Normal | **Push** `'('` | `['{', '(']` | Valid |
| `[` | Normal | **Push** `'['` | `['{', '(', '[']` | Valid |
| `]` | Normal | **Pop** and match `'['` | `['{', '(']` | Match `[]` |
| `)` | Normal | **Pop** and match `'('` | `['{']` | Match `()` |
| `}` | Normal | **Pop** and match `'{'` | Empty `[]` | Match `{}` |
| `EOF` | End of file | Check if empty | Empty `[]` | **Success** |
