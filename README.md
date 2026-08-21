# CodeMaster Quiz Game 🎮

An educational C++ project demonstrating **Object-Oriented Programming** principles through a gamified programming quiz application.

## 📚 Learning Objectives

This project teaches:
- **Classes and Objects** - Creating blueprints and instances
- **Inheritance** - Building class hierarchies
- **Polymorphism** - Using virtual functions for runtime behavior
- **Abstract Classes** - Defining interfaces with pure virtual functions
- **Encapsulation** - Public, private, and protected access modifiers
- **Header/Implementation separation** - Professional C++ project structure

---

## 🏗️ Project Structure

```
cppquiz/
├── quiz.h          # Header file - Class declarations (blueprints)
├── quiz.cpp        # Implementation file - Method definitions
├── main.cpp        # Entry point - Game loop and user interaction
└── README.md       # This file
```

### Why separate files?
- **quiz.h** - Declarations only (what exists, not how it works)
- **quiz.cpp** - Implementations (the actual code that runs)
- **main.cpp** - Uses the classes to create the game
- This separation is standard in C++ for maintainability and compilation efficiency

---

## 🎯 Class Hierarchy

```
Question (Abstract Base Class)
    │
    ├── MultipleChoiceQuestion
    │       └── Options: A, B, C, D
    │       └── Stores correct answer as char
    │
    └── TrueFalseQuestion
            └── Stores correct answer as bool
```

### Question (Base Class)
**Purpose:** Abstract blueprint for all question types

**Members:**
- `questionText` (protected) - The question string
- `points` (protected) - Points awarded for correct answer

**Methods:**
- `Question(text, pts)` - Constructor
- `virtual ~Question()` - Virtual destructor (enables proper cleanup)
- `virtual void display() = 0` - Pure virtual (child must implement)
- `virtual bool checkAnswer(answer) = 0` - Pure virtual
- `int get_points()` - Returns points value

**Why Abstract?**
- The `= 0` makes methods pure virtual
- Cannot create Question objects directly
- Forces child classes to implement display() and checkAnswer()

### MultipleChoiceQuestion (Child Class)
**Purpose:** Questions with 4 options (A, B, C, D)

**Additional Members:**
- `vector<string> options` - The four answer choices
- `char correctAnswer` - Which option is correct ('A', 'B', 'C', or 'D')

**Implements:**
- `display()` - Shows question and all options
- `checkAnswer(answer)` - Checks if user's answer matches correctAnswer

### TrueFalseQuestion (Child Class)
**Purpose:** Simple true/false questions

**Additional Members:**
- `bool correctAnswer` - The correct answer (true or false)

**Implements:**
- `display()` - Shows question with True/False prompt
- `checkAnswer(answer)` - Checks if user's answer is correct

---

## 🔑 Key C++ Concepts Demonstrated

### 1. Virtual Functions
```cpp
virtual void display() = 0;  // Pure virtual
```
- Enables **polymorphism** - runtime decision of which method to call
- Without `virtual`, C++ uses pointer type (wrong behavior)
- With `virtual`, C++ uses actual object type (correct behavior)

**Example:**
```cpp
Question* q = new MultipleChoiceQuestion(...);
q->display();  // Calls MultipleChoiceQuestion::display(), NOT Question::display()
```

### 2. Virtual Destructor
```cpp
virtual ~Question();
```
- **Critical** for inheritance with dynamic memory
- Ensures child destructors are called when deleting through base pointer
- Without it: memory leaks when `delete basePointer;` only calls base destructor

### 3. Override Keyword
```cpp
void display() override;
```
- Documents that we're overriding a virtual function
- Compiler error if function signature doesn't match parent
- Catches typos and mistakes at compile-time

### 4. Protected Access
```cpp
protected:
    string questionText;
```
- Accessible by this class AND child classes
- Not accessible from outside the class hierarchy
- Perfect for data that children need but users shouldn't modify

### 5. Initializer Lists
```cpp
Question::Question(string text, int pts) 
    : questionText(text), points(pts) {
}
```
- Initializes members BEFORE constructor body runs
- More efficient than assignment in constructor body
- Required for const members and references

---

## 🔨 How to Compile and Run

### Compile (with warnings)
```bash
g++ -Wall -Wextra -o quiz main.cpp quiz.cpp
```

### Run
```bash
./quiz
```

### Compile flags explained:
- `-Wall` - Enable all common warnings
- `-Wextra` - Enable extra warnings
- `-o quiz` - Output executable named "quiz"
- Link both `.cpp` files (header is included automatically)

---

## 📝 Implementation Progress

- [x] **Step 1:** Create header file structure (quiz.h)
  - [x] Base Question class
  - [x] MultipleChoiceQuestion class
  - [x] TrueFalseQuestion class

- [x] **Step 2:** Implement base class methods (quiz.cpp)
  - [x] Question constructor
  - [x] Question destructor
  - [x] get_points() method

- [ ] **Step 3:** Implement MultipleChoiceQuestion methods
  - [ ] Constructor
  - [ ] Destructor
  - [ ] display()
  - [ ] checkAnswer()

- [ ] **Step 4:** Implement TrueFalseQuestion methods
  - [ ] Constructor
  - [ ] Destructor
  - [ ] display()
  - [ ] checkAnswer()

- [ ] **Step 5:** Create QuizGame class
  - [ ] Store questions in a vector
  - [ ] Track score
  - [ ] Game loop

- [ ] **Step 6:** Create main.cpp
  - [ ] Create question objects
  - [ ] Run quiz game
  - [ ] Display final score

---

## 🎓 What You'll Learn

By completing this project, you'll understand:

1. **Why inheritance?** - Code reuse and logical hierarchies
2. **Why virtual functions?** - Polymorphism and dynamic binding
3. **Why abstract classes?** - Enforcing interfaces across child classes
4. **Why protected members?** - Controlled access for inheritance
5. **Why header files?** - Clean separation of interface and implementation

---

## 🚀 Future Enhancements

Once the basic version works, you can add:
- [ ] Load questions from a file
- [ ] Random question order
- [ ] Difficulty levels
- [ ] Timer for each question
- [ ] High score tracking
- [ ] Categories (C++, Algorithms, Data Structures)
- [ ] Hint system (costs points)
- [ ] Multiple quiz sessions

---

## 📖 Resources

- [C++ Classes Tutorial](https://cplusplus.com/doc/tutorial/classes/)
- [C++ Inheritance](https://cplusplus.com/doc/tutorial/inheritance/)
- [Virtual Functions Explained](https://cplusplus.com/doc/tutorial/polymorphism/)

---

**Built with 💻 for learning C++ OOP concepts**
