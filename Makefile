CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Find SFML headers - try common locations
SFML_INCLUDE ?= 
ifeq ($(shell uname), Darwin)
	# macOS - check Homebrew installation first
	SFML_PREFIX := /opt/homebrew/opt/sfml
	ifeq ($(shell test -d $(SFML_PREFIX) && echo yes || echo no),yes)
		SFML_INCLUDE = -I$(SFML_PREFIX)/include
		LDFLAGS += -L$(SFML_PREFIX)/lib
	else
		# Fallback to other common paths
		SFML_INCLUDE = -I/usr/local/include -I/opt/local/include
		LDFLAGS += -L/usr/local/lib -L/opt/local/lib
	endif
endif

SOURCES = src/main.cpp src/Button.cpp src/MorseDecoder.cpp
HEADERS = src/Button.hpp src/MorseDecoder.hpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = build/morse_decoder
APP_NAME = Morse
BUNDLE_DIR = bundle/$(APP_NAME).app
BUNDLE_EXEC = $(BUNDLE_DIR)/Contents/MacOS/$(APP_NAME)
BUNDLE_ID = com.example.$(shell echo $(APP_NAME) | tr '[:upper:]' '[:lower:]')

all: $(TARGET) install-assets

$(TARGET): $(OBJECTS)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c -o $@ $<

install-assets:
	@mkdir -p build/assets
	@cp -R assets/* build/assets/ 2>/dev/null || true


bundle: all
	@echo "Creating app bundle in bundle/"
	@rm -rf $(BUNDLE_DIR)
	@mkdir -p $(BUNDLE_DIR)/Contents/MacOS
	@mkdir -p $(BUNDLE_DIR)/Contents/Resources
	@cp $(TARGET) $(BUNDLE_EXEC)
	@chmod +x $(BUNDLE_EXEC)
	@cp -R assets $(BUNDLE_DIR)/Contents/Resources/ 2>/dev/null || true
	@if [ -f assets/icon.icns ]; then cp assets/icon.icns $(BUNDLE_DIR)/Contents/Resources/; fi
	@cp -R assets $(BUNDLE_DIR)/Contents/MacOS/assets 2>/dev/null || true
	@cp -R assets $(BUNDLE_DIR)/Contents/assets 2>/dev/null || true
	@cp assets/*.ttf $(BUNDLE_DIR)/Contents/Resources/ 2>/dev/null || true
	@printf '%s\n' \
	  '<?xml version="1.0" encoding="UTF-8"?>' \
	  '<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">' \
	  '<plist version="1.0">' \
	  '<dict>' \
	  '    <key>CFBundleName</key>' \
	  '    <string>$(APP_NAME)</string>' \
	  '    <key>CFBundleExecutable</key>' \
	  '    <string>$(APP_NAME)</string>' \
	  '    <key>CFBundleIdentifier</key>' \
	  '    <string>$(BUNDLE_ID)</string>' \
	  '    <key>CFBundleIconFile</key>' \
	  '    <string>icon.icns</string>' \
	  '    <key>CFBundlePackageType</key>' \
	  '    <string>APPL</string>' \
	  '    <key>CFBundleVersion</key>' \
	  '    <string>1.0</string>' \
	  '</dict>' \
	  '</plist>' > $(BUNDLE_DIR)/Contents/Info.plist
	@echo "Bundle created at $(BUNDLE_DIR)"

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf build/assets

rebuild: clean all

.PHONY: all clean rebuild install-assets
.PHONY: bundle
