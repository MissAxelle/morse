# Morse Code Decoder

A compact desktop application written in C++ (C++17) using SFML 3.x that lets you manually decode Morse code via keyboard or on‑screen buttons. It’s lightweight, cross‑platform, and designed for quick local use.

**Highlights**

- Real-time Morse sequence display and decoded word output
- Full dictionary: letters A–Z and digits 0–9
- Keyboard and mouse input (DOT, DASH, VALIDATE)
- Clean, simple UI with hover and flash feedback
- Build with `make` (includes `Makefile`)

---

**Quick Links**

- Build: `make`
- Run: `./build/morse_decoder`

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Requirements](#requirements)
- [Build & Run](#build--run)
- [Usage](#usage)
- [Project Layout](#project-layout)
- [Assets](#assets)
- [Development Notes](#development-notes)
- [Contributing](#contributing)
- [License](#license)

---

## About

This project provides a small GUI tool to manually enter Morse code and decode it into text. Input can be entered symbol‑by‑symbol (dot/dash), then validated to append the decoded character to the current word.

The application is intentionally minimal and self‑contained — its only runtime dependency is SFML 3.x.

## Features

- Manual input via keyboard: `.` or `D` → DOT, `-` or `K` → DASH, `Enter` → VALIDATE
- On‑screen buttons for DOT, DASH and VALIDATE (mouse click)
- Immediate visual feedback: sequence, decoded word, error messages (3s)
- Full Morse dictionary (A–Z, 0–9)
- Cross‑platform build support (Makefile)

## Requirements

- C++17 compatible compiler (clang++ / g++)
- SFML 3.x (graphics, window, system)
- A modern OS: macOS, Linux or Windows

If using macOS, install SFML with Homebrew:

```bash
brew install sfml
```

## Build & Run

From the project root:

```bash
make
./morse_decoder
```

Common `make` targets:

- `make` — build executable
- `make clean` — remove build artifacts
- `make rebuild` — clean and build
- `make bundle` — create a macOS `.app` bundle in the `bundle/` folder (uses `assets/icon.icns` when present)

To create a macOS application bundle (the bundle will be placed in `bundle/`, not `build/`):

```bash
make bundle
# Open the bundle in Finder (macOS)
open bundle/Morse.app
# Or run the bundled executable directly
bundle/Morse.app/Contents/MacOS/Morse
```

If you prefer manual compilation (example macOS):

```bash
clang++ -std=c++17 -o morse_decoder src/main.cpp src/Button.cpp src/MorseDecoder.cpp \
  -I/usr/local/include -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system
```

## Usage

1. Launch the app.
2. Use keyboard or click the DOT/DASH buttons to build a Morse sequence.
3. Press `Enter` or click VALIDATE to decode the sequence to a character.
4. The decoded character appends to the current word shown at the top.
5. Press `Backspace` to clear the current word and start over.

Example: To type `A` (.-)

1. Press `D` (or click DOT) → sequence shows `.`
2. Press `K` (or click DASH) → sequence shows `.-`
3. Press `Enter` (or click VALIDATE) → word shows `A`

## Project Layout

```
morse/
│
├─ assets/
│  │
│  ├─ SpecialElite-Regular.ttf      # retro typewriter font
│  └─ icon.icns                     # app icon
│
├─ src/
│  │
│  ├─ main.cpp                      # main loop
│  ├─ Button.cpp                    # button logic
│  ├─ Button.hpp                    # button header
│  ├─ MorseDecoder.cpp              # morse dictionnary
│  └─ MorseDecoder.hpp              # morse dictionnary header
│
├─ .gitignore                       # prevent builds from being commited
├─ build/                           # built executable & copied assets       (ignored)
├─ bundle/                          # built .app                             (ignored)
├─ LICENSE                          # MIT license
├─ Makefile                         # used to compile
└─ README.md                        # this file
```

## Assets

All visual resources used by the application are stored in the `assets/` folder.

You can easily customize the appearance of the application by replacing:
- the **font** file
- the **application icon**

Simply drop your new files into the `assets/` folder. If you change the file names, make sure to update:
- the font file name in `main.cpp`
- the icon file name in the `Makefile`

This ensures the build system and the application can correctly locate and load the new assets.

## Development Notes

- UI: 1000×600 window, 60 FPS, dark theme
- Buttons implemented in `src/Button.*` with hover & flash animations
- Decoder logic in `src/MorseDecoder.*` using an `unordered_map<string,char>`
- Font loading uses a list of candidate paths and prints helpful diagnostics if missing

## Contributing

Small improvements, bug fixes and documentation updates are welcome. Suggested steps:

1. Fork the repository
2. Create a feature branch
3. Run `make` and ensure changes build
4. Open a PR with a brief description

If adding new assets, include instructions or permissive licenses for bundled fonts.

## License

This project is provided under the MIT License — see `LICENSE`.

---
