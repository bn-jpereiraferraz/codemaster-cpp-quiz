# CodeMaster C++ Quiz Game 🎮

A fully-featured, educational C++ quiz application demonstrating **advanced Object-Oriented Programming** principles with a gamified terminal interface. Built as a comprehensive teaching tool for mastering C++ concepts through hands-on implementation.

---

## 🚀 Quick Start

### Compile
```bash
g++ -Wall -Wextra -std=c++11 -o quiz main.cpp quiz.cpp
```

### Run
```bash
./quiz
```

---

## ✨ Features

### ✅ Phase 1: Core Experience (Complete)
- 🎨 **Colorful Terminal UI** - ANSI escape codes for stunning visual feedback
- 📊 **Smart Progress Tracking** - Real-time progress bar and statistics display
- 🔥 **Streak System** - Build combos with milestone celebrations (3, 5, 10+)
- 🏆 **Achievement Badges** - Unlock rewards for exceptional performance
- 💯 **Live Statistics** - Detailed stats every 5 questions
- 📁 **300 C++ Questions** - Comprehensive question bank covering all topics
- 🎯 **Smart Grading** - Letter grades (A-D) with detailed feedback
- 🎨 **ASCII Art Banner** - Professional game introduction

### ✅ Phase 2: Advanced Game Mechanics (Complete)
- ⏱️ **Timer System** - Configurable countdown (15/30/60s or disabled)
- ⚡ **Speed Bonuses** - Double points for answering in under half the time
- 💡 **Lifelines** - Game show style helps:
  - **50/50** - Remove 2 wrong answers (Multiple Choice only)
  - **Skip** - Skip question without penalty
  - **Hint** - Coming soon!
- 🎲 **Question Shuffling** - Randomized order every session
- 📊 **Difficulty Filters** - Choose Easy (5pts), Medium (10pts), Hard (15pts), or Mixed
- 🎯 **Question Count Selection** - 50-300 questions per session
- 💾 **Save/Load System** - Auto-save every 5 questions, resume anytime
- 🎪 **Interactive Menu** - Flashy main menu with configuration options
- ✅ **Input Validation** - Prevents accidental wrong answers from typos

### 🚧 Phase 3: Persistence & Analytics (Planned)
- 📈 **Player Statistics Dashboard**
  - Total questions answered across all sessions
  - Overall accuracy percentage
  - Category performance breakdown
  - Personal best scores and streaks
- 💾 **High Score Leaderboard**
  - Top 10 scores with player names
  - Filter by difficulty level
  - Date and time stamps
- 📊 **Performance Analytics**
  - Questions answered by topic
  - Improvement tracking over time
  - Weak areas identification
  - Practice recommendations
- 🎯 **Custom Question Sets**
  - Create focused practice sets
  - Topic-specific quizzes
  - Bookmark difficult questions

### 🎯 Phase 4: Multiplayer & Social (Future Vision)
- 👥 **Local Multiplayer** - Turn-based quiz battles
- 🌐 **Online Leaderboards** - Global ranking system
- 🏅 **Achievements System** - Unlock badges and titles
- 📱 **Cross-Platform** - Desktop, web, and mobile versions

---

## 🏗️ Architecture

### Project Structure
```
cppquiz/
├── quiz.h              # Class declarations and interfaces
├── quiz.cpp            # Full implementation (1400+ lines)
├── main.cpp            # Clean entry point (4-line main!)
├── questions.txt       # 300 C++ questions (MC + T/F)
├── savegame.dat        # Auto-generated save file
├── README.md           # This documentation
└── .gitignore          # Git ignore patterns
```

### Class Hierarchy
```
ColorTheme (Static Utility)
    └── ANSI codes + visual helpers

Question (Abstract Base)
    ├── MultipleChoiceQuestion (A/B/C/D)
    └── TrueFalseQuestion

Timer
    └── Chrono-based countdown

Lifelines
    └── One-time use helpers

QuizGame (Manager)
    ├── Question loading & parsing
    ├── Game loop & state management
    ├── Scoring & streak tracking
    ├── Save/Load functionality
    └── Menu system
```

---

## 🎓 C++ Concepts Demonstrated

### Core OOP Principles
- **Inheritance** - Base `Question` class with specialized children
- **Polymorphism** - Virtual functions for runtime dispatch
- **Encapsulation** - Private data, public interfaces
- **Abstraction** - Pure virtual functions enforcing contracts

### Advanced Techniques
- **RAII** - Resource management in constructors/destructors
- **Virtual Destructors** - Proper cleanup through base pointers
- **Override Keyword** - Compile-time safety for virtual functions
- **Dynamic Casting** - Runtime type checking (`dynamic_cast<>`)
- **Initializer Lists** - Efficient member initialization
- **Enum Classes** - Type-safe difficulty levels

### Modern C++ (C++11)
- **`std::chrono`** - Precise time measurement for timers
- **`std::random_device`** & **`std::mt19937`** - Modern randomization
- **`std::shuffle`** - STL algorithm for question randomization
- **Auto Type Deduction** - Cleaner code with `auto`
- **Range-Based For Loops** - Simplified iteration

### Standard Library
- **`std::vector`** - Dynamic arrays for question storage
- **`std::string`** - String manipulation and parsing
- **`std::ifstream`/`std::ofstream`** - File I/O for questions and saves
- **`std::getline`** - Line-by-line file reading

### Design Patterns
- **Abstract Factory** - Question parsing creates correct subtype
- **State Pattern** - Lifeline availability management
- **Template Method** - Base `Question` defines structure, children implement details

---

## 🎮 Gameplay Guide

### Main Menu
```
╔═══════════════════════════════════════╗
║                                       ║
║        🎮 MAIN MENU 🎮                ║
║                                       ║
╚═══════════════════════════════════════╝

▸ [1] Start New Quiz
▸ [2] Configure Settings
▸ [3] Exit Game
```

### Configuration Options
1. **Question Count**: 50-300 questions
2. **Difficulty**: Easy (5pts) / Medium (10pts) / Hard (15pts) / Mixed
3. **Timer**: Off / 60s / 30s / 15s
4. **Lifelines**: Enabled / Disabled

### During Quiz
- **Answer Format**: Type `A`, `B`, `C`, or `D` for multiple choice
- **True/False**: Type `true` or `false` (or `t`/`f`)
- **Lifelines**: Type `5050` or `skip` instead of an answer
- **Auto-Save**: Progress saved every 5 questions

### Scoring System
- **Base Points**: 5 (Easy) / 10 (Medium) / 15 (Hard)
- **Speed Bonus**: Double points if answered in < half the time
- **Streaks**: Build combos for motivation (no point bonus)
- **Grades**: A (80%+) / B (60-79%) / C (40-59%) / D (<40%)

---

## 📝 Question File Format

### Structure
```
# Comments start with #

# Multiple Choice (MC)
MC|Question text?|points|option1,option2,option3,option4|CorrectLetter

# True/False (TF)
TF|Statement here|points|true/false
```

### Examples
```
MC|What keyword declares a constant?|10|const,define,final,static|A
TF|C++ supports multiple inheritance|10|true
MC|Which STL container is LIFO?|15|queue,stack,deque,vector|B
```

### Topics Covered (300 Questions)
- C++ Basics & Syntax
- Data Types & Variables
- Operators & Expressions
- Control Flow (if/switch/loops)
- Functions & Overloading
- Pointers & References
- Memory Management (new/delete)
- OOP (Classes, Inheritance, Polymorphism)
- Virtual Functions & Abstract Classes
- STL Containers & Algorithms
- Templates & Generic Programming
- Exception Handling
- Smart Pointers (unique_ptr, shared_ptr)
- Move Semantics & Rvalue References
- Lambda Expressions
- Constexpr & Compile-Time Programming
- Threading & Concurrency
- Modern C++ (C++11/14/17/20+)

---

## 🛠️ Development Roadmap

### ✅ Phase 0: Foundation (Complete)
- [x] Core class architecture
- [x] Question loading system
- [x] Basic game loop
- [x] File I/O implementation

### ✅ Phase 1: Polish & UX (Complete)
- [x] Color theme system
- [x] Progress visualization
- [x] Streak tracking
- [x] Achievement system
- [x] 300-question bank

### ✅ Phase 2: Game Mechanics (Complete)
- [x] Timer system with countdown
- [x] Speed bonus calculation
- [x] Lifeline implementation (50/50, Skip)
- [x] Question shuffling & filtering
- [x] Difficulty selection
- [x] Save/Load functionality
- [x] Interactive menu system
- [x] Input validation

### 🚧 Phase 3: Persistence (Next Priority)
- [ ] Player profile system
- [ ] Statistics tracking across sessions
- [ ] High score leaderboard (top 10)
- [ ] Performance analytics dashboard
- [ ] Category-specific stats
- [ ] Custom question sets

### 🎯 Phase 4: Expansion (Future)
- [ ] Hint system implementation
- [ ] Question editor tool
- [ ] Import/export question packs
- [ ] GUI version (Qt/wxWidgets)
- [ ] Web version (WASM)
- [ ] Multiplayer mode
- [ ] Online features

---

## 🔧 Technical Implementation Details

### Save File Structure
```ini
# CodeMaster Quiz Save File
VERSION=1.0

# Progress
CURRENT_QUESTION=47
TOTAL_QUESTIONS=300

# Scores
EARNED_SCORE=380
TOTAL_SCORE=470
CORRECT_COUNT=38

# Streaks
CURRENT_STREAK=5
BEST_STREAK=8
TOTAL_BONUS=50

# Settings
DIFFICULTY=0
TIMER_ENABLED=true
TIME_LIMIT=30
LIFELINES_ENABLED=true

# Lifeline States
LIFELINE_5050_USED=false
LIFELINE_SKIP_USED=true
LIFELINE_HINT_USED=true
```

### Memory Management
- All questions allocated with `new` in parsing
- Stored as `Question*` pointers for polymorphism
- Destructor uses RAII to `delete` all questions
- No memory leaks (proper cleanup guaranteed)

### Timer Implementation
- Uses `std::chrono::steady_clock` for precision
- Immune to system clock changes
- Measures elapsed time in seconds
- Supports pause/resume functionality

---

## 📚 Learning Resources

### Recommended Reading
- [C++ Reference](https://en.cppreference.com/)
- [LearnCpp.com](https://www.learncpp.com/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)

### Related Topics
- Object-Oriented Design Patterns
- Modern C++ Best Practices
- STL Deep Dive
- Memory Management Strategies

---

## 🤝 Contributing

This is an educational project perfect for learning:
- How to structure a real C++ application
- OOP principles in practice
- File I/O and data parsing
- Terminal UI design
- State management
- Testing and debugging

### Extension Ideas
- Add more question categories
- Implement network multiplayer
- Create a graphical interface
- Port to mobile platforms
- Add voice/audio feedback
- Integrate with online APIs

---

## 📄 License

Educational project - Free to use and modify for learning purposes.

---

## 🎯 Project Goals Achieved

✅ **Educational Value** - Demonstrates 20+ C++ concepts  
✅ **Professional Structure** - Clean separation of concerns  
✅ **Modern C++** - Uses C++11 features appropriately  
✅ **User Experience** - Polished UI with clear feedback  
✅ **Maintainability** - Well-commented, organized code  
✅ **Extensibility** - Easy to add features or modify  
✅ **Completeness** - Fully functional from menu to save system  

---

**Status**: Phase 2 Complete ✅ | Phase 3 Planned 🚧

**Last Updated**: August 2026
