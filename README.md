# CodeMaster C++ Quiz Game 🎮

An educational C++ project demonstrating **Object-Oriented Programming** principles through a gamified programming quiz application with colorful terminal UI.

## 📚 Learning Objectives

This project teaches:
- **Classes and Objects** - Creating blueprints and instances
- **Inheritance** - Building class hierarchies
- **Polymorphism** - Using virtual functions for runtime behavior
- **Abstract Classes** - Defining interfaces with pure virtual functions
- **Encapsulation** - Public, private, and protected access modifiers
- **Header/Implementation separation** - Professional C++ project structure
- **File I/O** - Reading questions from external files
- **ANSI Colors** - Terminal styling and visual feedback

---

## ✨ Features

### ✅ Implemented (Phase 1 Complete!)
- 🎨 **Colorful Terminal UI** - ANSI color codes for beautiful output
- 📊 **Progress Tracking** - Real-time progress bar and stats
- 🔥 **Streak System** - Build combos with consecutive correct answers (3, 5, 10+ milestones!)
- 🏆 **Achievements** - Earn badges for performance (Perfect Score, Sharpshooter, Scholar)
- 💯 **Live Statistics** - View stats every 5 questions (score, accuracy, streak)
- 📁 **100 Questions** - Comprehensive C++ quiz loaded from file
- 🎯 **Smart Grading** - A-D grades with percentage and detailed feedback
- 🎨 **ASCII Art Banner** - Professional game intro

### 🚧 Planned (Phase 2 - Not Started)
- ⏱️ **Timer System** - Countdown per question with time pressure
- 🎯 **Speed Bonuses** - Extra points for fast answers
- 💡 **Lifelines** - 50/50, Skip, and Hint (game show style!)
- 🎲 **Question Shuffling** - Random order each playthrough
- 📊 **Difficulty Levels** - Easy/Medium/Hard categories

### 🎯 Future (Phase 3)
- 💾 **High Score Leaderboard** - Persistent top scores
- 📈 **Player Statistics** - Track performance across sessions
- 🎮 **Practice vs Quiz Mode** - Different game modes

---

## 🏗️ Project Structure

```
cppquiz/
├── quiz.h          # Header file - Class declarations
├── quiz.cpp        # Implementation file - Method definitions
├── main.cpp        # Entry point - Clean 4-line main!
├── questions.txt   # 100 C++ questions (MC and T/F)
├── README.md       # This file
└── .gitignore      # Git ignore patterns
```

### Why separate files?
- **quiz.h** - Declarations only (what exists, not how it works)
- **quiz.cpp** - Implementations (the actual code that runs)
- **main.cpp** - Uses the classes (stays clean - all logic in classes!)
- This separation is standard in C++ for maintainability and compilation efficiency

---

## 🎯 Class Architecture

```
ColorTheme (Static utility class)
    └── ANSI color codes and visual elements

Question (Abstract Base Class)
    ├── MultipleChoiceQuestion
    │       └── 4 options (A, B, C, D)
    └── TrueFalseQuestion
            └── True or False

QuizGame (Game Manager)
    ├── Manages question vector
    ├── Tracks scores and streaks
    ├── Handles game loop
    └── Displays results and achievements
```

### ColorTheme Class
**Purpose:** Centralize all visual styling

**Static Members:**
- Color constants (RED, GREEN, YELLOW, CYAN, BOLD, etc.)
- `print_banner()` - ASCII art header
- `print_separator()` - Visual dividers
- `print_correct_message(points)` - Success feedback
- `print_wrong_message()` - Failure feedback
- `print_question_header(current, total)` - Question numbering
- `print_progress_bar(current, total)` - Visual progress

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

### QuizGame (Manager Class)
**Purpose:** Orchestrates the entire quiz experience

**Private Members:**
- `vector<Question*> questions` - Stores all questions (polymorphism!)
- `totalScore`, `earnedScore` - Score tracking
- `correctCount` - Number of correct answers
- `currentStreak`, `bestStreak` - Streak tracking

**Public Methods:**
- `QuizGame()` - Constructor (initializes all stats to 0)
- `~QuizGame()` - Destructor (cleans up all dynamically allocated questions)
- `add_question(Question*)` - Add a question to the quiz
- `load_from_file(filename)` - Load questions from text file
- `load_default_questions()` - Fallback hardcoded questions
- `run()` - Main game loop
- `display_results()` - Final score and grade
- `display_achievements()` - Badges and accomplishments

**Private Helper Methods:**
- `parse_question_line(line)` - Parse file format into Question objects
- `display_live_stats(current, total)` - Show stats during quiz

---

## 🔑 Key C++ Concepts Demonstrated

### 1. Virtual Functions & Polymorphism
```cpp
virtual void display() = 0;  // Pure virtual
```
- Enables **runtime polymorphism** - which method to call decided at runtime
- Without `virtual`, C++ uses pointer type (wrong behavior)
- With `virtual`, C++ uses actual object type (correct behavior)

**Example:**
```cpp
Question* q = new MultipleChoiceQuestion(...);
q->display();  // Calls MultipleChoiceQuestion::display()!
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

### 4. Protected Access Modifier
```cpp
protected:
    string questionText;
```
- Accessible by this class AND child classes
- Not accessible from outside the class hierarchy
- Perfect for data that children need but users shouldn't modify

### 5. Initializer Lists
```cpp
QuizGame::QuizGame() 
    : totalScore(0), earnedScore(0), correctCount(0) {
}
```
- Initializes members BEFORE constructor body runs
- More efficient than assignment in constructor body
- Required for const members and references

### 6. File I/O
```cpp
ifstream file("questions.txt");
while (getline(file, line)) {
    Question* q = parse_question_line(line);
    add_question(q);
}
```
- Reading from external files
- String parsing with `find()`, `substr()`, `stoi()`
- Comma-separated value parsing

### 7. RAII (Resource Acquisition Is Initialization)
```cpp
QuizGame::~QuizGame() {
    for (Question* q : questions) {
        delete q;  // Cleanup in destructor
    }
}
```
- Resources acquired in constructor
- Resources released in destructor
- Automatic cleanup when object goes out of scope

---

## 🔨 How to Compile and Run

### Compile
```bash
g++ -Wall -Wextra -std=c++11 -o quiz main.cpp quiz.cpp
```

### Run
```bash
./quiz
```

### Compile flags explained:
- `-Wall` - Enable all common warnings
- `-Wextra` - Enable extra warnings
- `-std=c++11` - Use C++11 standard (for chrono, auto, etc.)
- `-o quiz` - Output executable named "quiz"

---

## 📝 Development Progress

### ✅ Phase 0: Core Implementation (Complete!)
- [x] Header file structure (quiz.h)
  - [x] Base Question class
  - [x] MultipleChoiceQuestion class
  - [x] TrueFalseQuestion class
- [x] Base class implementations (quiz.cpp)
  - [x] Question constructor/destructor
  - [x] MultipleChoiceQuestion implementation
  - [x] TrueFalseQuestion implementation
- [x] QuizGame class
  - [x] Question storage (vector of pointers)
  - [x] Score tracking
  - [x] Game loop
  - [x] File loading system
- [x] Main entry point (main.cpp)
  - [x] Clean 4-line main function
  - [x] File loading with fallback

### ✅ Phase 1: Visual Enhancements (Complete!)
- [x] ColorTheme class
  - [x] ANSI color codes
  - [x] ASCII art banner
  - [x] Visual elements (separators, headers)
- [x] Progress tracking
  - [x] Progress bar
  - [x] Live stats display
- [x] Streak system
  - [x] Track consecutive correct answers
  - [x] Milestone celebrations (3, 5, 10+)
  - [x] Best streak tracking
- [x] Achievements system
  - [x] Perfect Score badge
  - [x] Streak achievements
  - [x] Accuracy badges (Sharpshooter, Scholar)
- [x] Enhanced results
  - [x] Colorful grade display
  - [x] Detailed statistics
  - [x] Achievement summary
- [x] 100 Educational Questions
  - [x] Created comprehensive question bank
  - [x] Covers all major C++ topics

### 🚧 Phase 2: Game Mechanics (Not Started)
- [ ] Timer system
  - [ ] Timer class implementation
  - [ ] Countdown display
  - [ ] Time-up handling
- [ ] Speed bonuses
  - [ ] Calculate bonus based on time
  - [ ] Display bonus points
- [ ] Lifelines system
  - [ ] 50/50 (remove wrong answers)
  - [ ] Skip question
  - [ ] Hint display
- [ ] Question shuffling
  - [ ] Random order per session
- [ ] Difficulty levels
  - [ ] Easy/Medium/Hard selection

### 🎯 Phase 3: Persistence (Planned)
- [ ] High score system
  - [ ] Save top 10 scores
  - [ ] Load and display leaderboard
- [ ] Player statistics
  - [ ] Total questions answered
  - [ ] Overall accuracy
  - [ ] Best streak ever
- [ ] Progress tracking
  - [ ] Questions by category
  - [ ] Improvement over time

---

## 📖 Question File Format

Questions are stored in `questions.txt` with this format:

```
# Comments start with #
MC|Question text?|points|option1,option2,option3,option4|CorrectLetter
TF|Statement here|points|true/false
```

**Examples:**
```
MC|What is polymorphism?|10|Many forms,One form,No form,Virtual form|A
TF|C++ supports multiple inheritance|10|true
```

---

## 🎓 What You'll Learn

By completing this project, you understand:

1. **Why inheritance?** - Code reuse and logical hierarchies
2. **Why virtual functions?** - Polymorphism and dynamic binding
3. **Why abstract classes?** - Enforcing interfaces across child classes
4. **Why protected members?** - Controlled access for inheritance
5. **Why header files?** - Clean separation of interface and implementation
6. **Why ANSI codes?** - Terminal styling without external libraries
7. **Why file I/O?** - Separating data from code

---

## 🎮 Gameplay Features

- **Colorful UI** - Green for correct, red for wrong, cyan for info
- **Progress Bar** - Visual indicator of quiz completion
- **Streak Tracking** - Build combos for extra motivation
- **Live Stats** - View performance every 5 questions
- **Achievements** - Unlock badges based on performance
- **Smart Grading** - A (80%+), B (60%+), C (40%+), D (below 40%)

---

## 📖 Resources

- [C++ Classes Tutorial](https://cplusplus.com/doc/tutorial/classes/)
- [C++ Inheritance](https://cplusplus.com/doc/tutorial/inheritance/)
- [Virtual Functions Explained](https://cplusplus.com/doc/tutorial/polymorphism/)
- [ANSI Escape Codes](https://en.wikipedia.org/wiki/ANSI_escape_code)

---

## 🤝 Contributing

This is an educational project. Feel free to fork and extend it with:
- More question categories
- Different quiz formats
- Network multiplayer
- GUI version
- Mobile port

---

**Built with 💻 for learning C++ OOP concepts**

**Current Status:** Phase 1 Complete ✅ | Phase 2 In Progress 🚧
