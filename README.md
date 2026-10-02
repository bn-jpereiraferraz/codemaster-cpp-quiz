# 🎮 C++ Quiz Game

A comprehensive C++ programming quiz game with multiple game modes, achievements, statistics tracking, and a hint system.

---

## 📂 Project Structure

```
cppquiz/
├── include/          # Header files (.h)
│   ├── core/         # Core game engine
│   ├── models/       # Data models (Question, etc.)
│   ├── modes/        # Game mode implementations
│   ├── ui/           # User interface layer
│   ├── systems/      # Game systems (timers, lifelines, etc.)
│   ├── processors/   # Business logic processors (future)
│   └── utils/        # Utility classes (future)
│
├── src/              # Source files (.cpp)
│   └── [mirrors include/ structure]
│
├── data/             # Game data (questions.txt)
├── saves/            # Save game files
├── build/            # Build artifacts
├── docs/             # Documentation
└── tests/            # Unit tests (future)
```

---

## 🚀 Quick Start

```bash
make              # Build the game
make run          # Build and run
make clean        # Clean build artifacts
make help         # Show all commands
```

---

## 🎯 Features

- ✅ 360 Questions across 27 categories
- ✅ 6 Game Modes (Classic, Quick Attack, Survival, Marathon, Lightning, Practice)
- ✅ 3-Level Hint System (unlimited use)
- ✅ Lifelines (50/50, Skip)
- ✅ Statistics Tracking
- ✅ Save/Load System
- ✅ Achievement System

See full documentation in docs/ folder.

**Status**: ✅ Project restructuring complete | 🚧 Next: Input validation
