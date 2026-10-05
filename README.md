# C++ Quiz Game

A comprehensive, terminal-based C++ programming quiz application featuring multiple game modes, persistent statistics tracking, and an intelligent hint system. Developed with modern C++ practices emphasizing memory safety, clean architecture, and SOLID principles.

[![Language](https://img.shields.io/badge/C++-14-blue.svg)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com)
[![Code Quality](https://img.shields.io/badge/quality-B+-yellow.svg)](CODE_REVIEW_REPORT.md)

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Game Modes](#game-modes)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
- [Building](#building)
- [Configuration](#configuration)
- [Technical Details](#technical-details)
- [Known Limitations](#known-limitations)
- [Documentation](#documentation)

---

## Overview

C++ Quiz Game is a feature-rich educational application designed to test and improve C++ programming knowledge. The application includes over 360 questions across 27 categories, six distinct game modes with varying difficulty levels, and comprehensive statistics tracking for performance analysis.

**Key Statistics:**
- **Lines of Code:** ~6,000
- **Files:** 104 (52 headers, 52 implementations)
- **Questions:** 360+
- **Categories:** 27
- **Game Modes:** 6
- **Memory Leaks:** 0 (Valgrind verified)

---

## Features

### Core Functionality

**Question Database**
- 360+ curated questions covering C++ programming concepts
- 27 distinct categories (OOP, STL, Templates, Memory Management, etc.)
- Three difficulty levels: Easy (5 points), Medium (10 points), Hard (15 points)
- Two question types: Multiple Choice and True/False

**Game Mechanics**
- Six unique game modes with different scoring systems and mechanics
- Three-tier progressive hint system (unlimited use, 10% penalty per hint)
- Configurable timer system (5-600 seconds per question)
- Lifeline system: 50/50 elimination and question skip
- Save/Load functionality for interrupted sessions

**Statistics & Progress**
- Comprehensive career statistics tracking
- Mode-specific performance records
- Category-based performance analysis
- Achievement system for milestone tracking
- High score persistence across sessions

### Technical Features

**Code Quality**
- Smart pointer usage throughout (std::unique_ptr)
- Zero memory leaks (RAII pattern)
- Custom exception hierarchy for robust error handling
- Type-safe enumerations (enum class)
- Interface segregation principle implementation
- Const-correctness enforcement

**Architecture**
- Layered architecture with clear separation of concerns
- Dependency inversion through interface abstractions
- Strategy pattern for game mode implementation
- Repository pattern for question management
- Factory pattern for question creation

---

## Prerequisites

### Required

- **Compiler:** GCC 5.0+ or Clang 3.4+ with C++14 support
- **Build System:** GNU Make 3.81+
- **Operating System:** Linux, macOS, or Windows (WSL/MinGW)

### Recommended

- Terminal with ANSI escape code support for color output
- UTF-8 character encoding for box-drawing characters

### Verification

```bash
g++ --version    # Verify compiler (should support -std=c++14)
make --version   # Verify GNU Make installation
```

---

## Installation

### Quick Start

```bash
git clone <repository-url>
cd cppquiz
make run
```

### Step-by-Step

```bash
# 1. Clone repository
git clone <repository-url>
cd cppquiz

# 2. Build project
make

# 3. Run executable
./build/quiz
```

### Directory Setup

The build process automatically creates required directories:
- `build/` - Compiled binaries and object files
- `build/obj/` - Object file hierarchy mirroring source structure

---

## Usage

### Starting the Application

```bash
./build/quiz
```

### Main Menu

The application presents four main options:

1. **New Quiz** - Initialize a new game session
   - Select game mode
   - Configure settings (difficulty, timer, lifelines)
   - Optional: Load previously saved game

2. **Configure Settings** - Adjust global game parameters
   - Question count (5-100)
   - Difficulty level (Easy/Medium/Hard/Mixed)
   - Category filter (All or specific category)
   - Timer settings (5-600 seconds or disabled)
   - Lifeline availability

3. **View Statistics** - Access performance data
   - Career overview (total games, accuracy, high scores)
   - Mode-specific statistics
   - Category performance breakdown
   - Achievement progress

4. **Exit** - Terminate application

### In-Game Commands

**Answer Formats:**
- Multiple Choice: `A`, `B`, `C`, or `D`
- True/False: `TRUE` or `FALSE`

**Lifeline Commands:**
- `hint` - Display progressive hint (3 levels available)
- `5050` - Eliminate two incorrect answers (Multiple Choice only, once per question)
- `skip` - Skip current question (if lifeline available)

### Example Gameplay

```
Question 1/10                                       Score: 0/100

Lifelines: Hint (3), 50/50 (1), Skip (1)

╔════════════════════════════════════════════════════════════╗
║  Category: OOP Concepts                                    ║
║  What is the primary purpose of virtual functions in C++?  ║
║                                                            ║
╠════════════════════════════════════════════════════════════╣
║  A │ Enable runtime polymorphism                           ║
║  B │ Improve compilation speed                             ║
║  C │ Reduce memory usage                                   ║
║  D │ Prevent inheritance                                   ║
╚════════════════════════════════════════════════════════════╝

Timer: 30 seconds

Your answer (or 'hint', '5050', 'skip'): A

✓ Correct! +10 points

Current Score: 10/100
```

---

## Game Modes

| Mode | Description | Characteristics |
|------|-------------|-----------------|
| **Classic** | Traditional quiz format | Standard rules, configurable settings, all features enabled |
| **Quick Attack** | Time-intensive challenge | 30-second timer per question, bonus points for speed |
| **Survival** | Lives-based elimination | Start with 3 lives, game ends when all lives lost |
| **Marathon** | Comprehensive assessment | All available questions, cumulative scoring |
| **Lightning** | Rapid-fire questions | 15-second timer, quick succession, high-pressure |
| **Practice** | Learning mode | No score tracking, unlimited hints, no time limit |

---

## Project Structure

```
cppquiz/
├── include/                    # Header files
│   ├── core/                  # Core game engine
│   │   ├── Constants.h        # Centralized constants
│   │   ├── GameRunner.h       # Main game orchestrator
│   │   ├── QuizGame.h         # Primary game controller
│   │   ├── GameSession.h      # Session state management
│   │   ├── GameConfiguration.h # Settings management
│   │   ├── QuestionBank.h     # Question repository
│   │   ├── CommonGameLoop.h   # Shared game loop logic
│   │   ├── GameExceptions.h   # Exception hierarchy
│   │   ├── IGameState.h       # Composite state interface
│   │   ├── IQuestionProvider.h
│   │   ├── IScoreTracker.h
│   │   ├── IGameplayState.h
│   │   ├── IConfigurationProvider.h
│   │   └── IStatisticsProvider.h
│   │
│   ├── models/                # Data structures
│   │   ├── Question.h         # Abstract base class
│   │   ├── MultipleChoiceQuestion.h
│   │   ├── TrueFalseQuestion.h
│   │   ├── Achievement.h
│   │   ├── LiveStats.h
│   │   └── ResultsSummary.h
│   │
│   ├── modes/                 # Game mode implementations
│   │   ├── GameModes.h
│   │   ├── ModeSetup.h
│   │   └── ModeRules.h
│   │
│   ├── ui/                    # User interface layer
│   │   ├── ColorTheme.h
│   │   ├── AsciiArt.h
│   │   ├── QuestionRenderer.h
│   │   ├── QuestionPresenter.h
│   │   ├── ResultsDisplay.h
│   │   ├── LiveStatsDisplay.h
│   │   ├── AchievementDisplay.h
│   │   ├── MenuSystem.h
│   │   ├── ConfigurationUI.h
│   │   ├── StatisticsMenu.h
│   │   └── SaveGameUI.h
│   │
│   ├── systems/               # Game systems
│   │   ├── Timer.h
│   │   ├── GlobalTimer.h
│   │   ├── Lifelines.h
│   │   ├── LifelineHandler.h
│   │   ├── Lives.h
│   │   ├── statistics.h
│   │   ├── StatisticsData.h
│   │   ├── StatisticsRepository.h
│   │   └── StatisticsPresenter.h
│   │
│   ├── processors/            # Business logic
│   │   ├── QuestionProcessor.h
│   │   ├── QuestionParser.h
│   │   ├── ScoreCalculator.h
│   │   ├── GradeCalculator.h
│   │   └── AchievementChecker.h
│   │
│   ├── controllers/           # Flow controllers
│   │   ├── MenuController.h
│   │   └── ResultsManager.h
│   │
│   ├── persistence/           # Data persistence
│   │   └── GameSaveManager.h
│   │
│   └── utils/                 # Utility functions
│       ├── InputValidator.h
│       ├── AnswerValidator.h
│       ├── StringUtils.h
│       └── QuestionFile.h
│
├── src/                       # Implementation files
│   └── [mirrors include/ structure]
│
├── data/                      # Game data
│   └── questions.txt          # Question database
│
├── saves/                     # Save game files
├── build/                     # Build artifacts
│   ├── obj/                   # Object files
│   └── quiz                   # Executable
│
├── docs/                      # Documentation
│   ├── REFACTORING_PLAN.md
│   ├── PROJECT_STRUCTURE.md
│   └── IMPLEMENTATION_TRACKER.md
│
├── Makefile                   # Build configuration
├── README.md                  # This file
├── CODE_REVIEW_REPORT.md      # Quality assessment
└── FINAL_REFACTORING_REPORT.md # Refactoring history
```

---

## Architecture

### Design Patterns

**Factory Pattern**
- `QuestionParser` creates appropriate Question subclass instances based on type

**Strategy Pattern**
- Game modes implement different strategies for scoring and progression

**Repository Pattern**
- `QuestionBank` manages question collection with filtering and retrieval

**Interface Segregation**
- `IGameState` composed of five focused interfaces
- Clients depend only on required interfaces

**RAII (Resource Acquisition Is Initialization)**
- Smart pointers (std::unique_ptr) for automatic memory management
- Exception-safe resource handling

### Architectural Layers

```
┌──────────────────────────────────────┐
│         UI Layer                     │
│  (ColorTheme, Renderers, Displays)   │
├──────────────────────────────────────┤
│      Controller Layer                │
│  (MenuController, ResultsManager)    │
├──────────────────────────────────────┤
│       Core Logic Layer               │
│  (GameRunner, QuizGame, GameLoop)    │
├──────────────────────────────────────┤
│     Business Logic Layer             │
│  (Processors, Calculators)           │
├──────────────────────────────────────┤
│        Model Layer                   │
│  (Question, GameSession, Config)     │
├──────────────────────────────────────┤
│       System Layer                   │
│  (Statistics, Timer, Lifelines)      │
└──────────────────────────────────────┘
```

### Interface Hierarchy

```cpp
IGameState (Composite Interface)
├── IQuestionProvider       // Question access methods
├── IScoreTracker          // Score management
├── IGameplayState         // Lifelines, lives, timer
├── IConfigurationProvider // Settings access
└── IStatisticsProvider    // Statistics tracking
```

This design allows components to depend only on the interfaces they need, improving testability and reducing coupling.

---

## Building

### Build Commands

```bash
make              # Compile project
make run          # Compile and execute
make clean        # Remove build artifacts
make rebuild      # Clean followed by build
make help         # Display available targets
```

### Compiler Configuration

**Standard Flags:**
```makefile
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14 -Iinclude
LDFLAGS = -lm
```

**Debug Build:**
```bash
make CXXFLAGS="-g -O0 -Wall -Wextra -std=c++14 -Iinclude"
```

**Optimized Build:**
```bash
make CXXFLAGS="-O3 -DNDEBUG -Wall -Wextra -std=c++14 -Iinclude"
```

**Strict Compilation:**
```bash
make CXXFLAGS="-Wall -Wextra -Werror -pedantic -std=c++14 -Iinclude"
```

### Build Process

The Makefile automatically:
1. Creates necessary directories (`build/`, `build/obj/`)
2. Generates dependency files (.d) for header tracking
3. Compiles source files with appropriate flags
4. Links object files into executable
5. Places final binary in `build/quiz`

---

## Configuration

### Question Database Format

Questions are stored in `data/questions.txt` using a structured text format:

```
CATEGORY: Memory Management
DIFFICULTY: Hard
TYPE: MC
QUESTION: What is the primary advantage of std::unique_ptr over raw pointers?
OPTIONS: A) Automatic memory deallocation | B) Faster execution | C) Smaller size | D) Thread safety
ANSWER: A
HINT1: Consider RAII principles
HINT2: What happens when the pointer goes out of scope?
HINT3: No manual delete required
---
```

**Field Specifications:**
- `CATEGORY`: String, one of 27 predefined categories
- `DIFFICULTY`: Easy, Medium, or Hard
- `TYPE`: MC (Multiple Choice) or TF (True/False)
- `QUESTION`: Question text
- `OPTIONS`: Pipe-separated list (Multiple Choice only)
- `ANSWER`: A/B/C/D for MC, TRUE/FALSE for TF
- `HINT1`, `HINT2`, `HINT3`: Progressive hints
- `---`: Question delimiter

### Runtime Configuration

All settings configurable through in-game menu:

**Question Settings:**
- Count: 5-100 questions per game
- Difficulty: Easy, Medium, Hard, or Mixed
- Category: All or specific category filter

**Timer Settings:**
- Duration: 5-600 seconds per question
- Mode: Enabled or Disabled

**Gameplay Settings:**
- Lifelines: Enabled or Disabled
- Game Mode: One of six available modes

### Persistence Files

**Save Game Format:**
- Location: `saves/savegame.dat`
- Format: Binary
- Contents: Game state, score, configuration, question progress

**Statistics Format:**
- Location: `statistics.dat`
- Format: Binary
- Contents: Career stats, mode records, category performance

---

## Technical Details

### Memory Management

**Smart Pointer Strategy:**
```cpp
// Owning pointers
std::vector<std::unique_ptr<Question>> allQuestions;

// Non-owning pointers (references into allQuestions)
std::vector<Question*> filteredQuestions;
```

**Benefits:**
- Automatic cleanup via RAII
- Exception-safe resource management
- Clear ownership semantics
- Zero memory leaks (Valgrind verified)

### Exception Handling

**Exception Hierarchy:**
```cpp
GameException (base)
├── FileException          // File I/O errors
├── ParseException         // Question parsing errors
├── InvalidStateException  // Invalid game state
├── ConfigurationException // Configuration errors
└── SaveLoadException      // Save/Load failures
```

**Error Recovery:**
- Try-catch blocks at system boundaries
- Graceful degradation with fallback defaults
- User-friendly error messages
- No crashes on invalid input

### Type Safety

**Enum Classes:**
```cpp
enum class Gamemode { Classic, QuickAttack, Survival, ... };
enum class Difficulty { Easy, Medium, Hard, Mixed };
```

**Benefits:**
- Scoped enumeration names
- No implicit integer conversions
- Type-safe comparisons

### Performance Characteristics

**Time Complexity:**
- Question loading: O(n) where n = question count
- Filtering by difficulty: O(n)
- Filtering by category: O(n)
- Random selection: O(1)
- Score calculation: O(1)

**Space Complexity:**
- Question storage: O(n)
- Filtered questions: O(m) where m ≤ n
- Statistics: O(1) fixed size

---

## Known Limitations

### Current Version

**Architectural:**
1. Console-only interface (UI logic tightly coupled to std::cout/std::cin)
2. Statistics class handles multiple responsibilities (storage, calculation, persistence, display)
3. Static methods throughout reduce testability
4. No dependency injection framework

**Functional:**
1. Time bonus calculation referenced but not implemented
2. Question export functionality exists but incomplete
3. No network/multiplayer support
4. Limited to terminal-based interaction

**Platform-Specific:**
1. Requires ANSI escape code support (Windows 10+ Terminal, WSL, or third-party console)
2. Box-drawing characters may not render correctly in all terminals
3. UTF-8 encoding required for proper character display

**Performance:**
1. Entire question database loaded into memory
2. Linear search for category/difficulty filtering
3. Statistics file loaded/saved in entirety

### Planned Improvements

Refer to [CODE_REVIEW_REPORT.md](CODE_REVIEW_REPORT.md) for detailed improvement roadmap:

**High Priority:**
- Refactor Statistics class into smaller, focused classes
- Abstract I/O layer for GUI support and testability
- Eliminate remaining magic string constants
- Implement dependency injection

**Medium Priority:**
- Add comprehensive unit test suite
- Implement time bonus calculation
- Optimize question filtering algorithms
- Add plugin architecture for extensibility

**Low Priority:**
- Create GUI version
- Add multiplayer support
- Implement question editor
- Add localization support

---

## Documentation

### Available Documents

| Document | Purpose |
|----------|---------|
| [README.md](README.md) | Project overview, installation, usage |
| [CODE_REVIEW_REPORT.md](CODE_REVIEW_REPORT.md) | Detailed code quality assessment and recommendations |
| [FINAL_REFACTORING_REPORT.md](FINAL_REFACTORING_REPORT.md) | Refactoring history and completed improvements |
| [docs/PROJECT_STRUCTURE.md](docs/PROJECT_STRUCTURE.md) | Detailed architecture documentation |
| [docs/REFACTORING_PLAN.md](docs/REFACTORING_PLAN.md) | Future improvement roadmap |

### Code Documentation

- Header files contain interface documentation
- Implementation files include algorithm explanations where necessary
- Complex logic sections annotated with clarifying comments

---

## Quality Metrics

| Metric | Value | Tool |
|--------|-------|------|
| Lines of Code | ~6,000 | cloc |
| Files | 104 | find |
| Average File Size | ~57 lines | cloc |
| Cyclomatic Complexity | Low-Medium | Manual review |
| Memory Leaks | 0 | Valgrind |
| Code Quality Score | B+ (85%) | Manual review |
| Compilation Warnings | 0 | g++ -Wall -Wextra |

### SOLID Principles Compliance

| Principle | Score | Notes |
|-----------|-------|-------|
| Single Responsibility | B- | Most classes compliant; Statistics class violates |
| Open/Closed | A- | Virtual methods enable extension |
| Liskov Substitution | A | Proper polymorphism throughout |
| Interface Segregation | A+ | IGameState split into 5 focused interfaces |
| Dependency Inversion | B+ | Interfaces used, but static methods reduce score |

---

## Version Information

**Version:** 1.0  
**Release Date:** October 2026  
**C++ Standard:** C++14  
**Status:** Stable - Production Ready (Console)

---

## Support

**Issue Reporting:**
- Technical issues: See [CODE_REVIEW_REPORT.md](CODE_REVIEW_REPORT.md)
- Bug reports: GitHub Issues
- Feature requests: GitHub Discussions

**Development:**
- Contribution guidelines: See project structure and code style sections
- Build issues: Verify prerequisites and compiler version
- Runtime issues: Check terminal ANSI support and UTF-8 encoding

---

**Last Updated:** October 5, 2026   
**Build Status:** Passing  