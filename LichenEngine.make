# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

RESCOMP = windres
INCLUDES += -Iextlib/include -I/engine/lib -I/game/lib
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS += -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lfreetype -lm -lglfw3 -lgdi32 -lopengl32 -lglew32 -lsoloud_static_x86 -lirrKlang
LDDEPS +=
LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),debug)
TARGETDIR = bin
TARGET = $(TARGETDIR)/LichenEngine_debug-windows-x86.exe
OBJDIR = bin/obj/debug
DEFINES += -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -g
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -g -std=c++17
ALL_LDFLAGS += $(LDFLAGS) -Lextlib/lib -L/usr/lib32 -m32

else ifeq ($(config),release)
TARGETDIR = bin
TARGET = $(TARGETDIR)/LichenEngine_release-windows-x86.exe
OBJDIR = bin/obj/release
DEFINES += -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -O2 -std=c++17
ALL_LDFLAGS += $(LDFLAGS) -Lextlib/lib -L/usr/lib32 -m32 -s

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/Camera.o
GENERATED += $(OBJDIR)/CameraFollower.o
GENERATED += $(OBJDIR)/Circle.o
GENERATED += $(OBJDIR)/Collider.o
GENERATED += $(OBJDIR)/Color.o
GENERATED += $(OBJDIR)/Component.o
GENERATED += $(OBJDIR)/Draw.o
GENERATED += $(OBJDIR)/Engine.o
GENERATED += $(OBJDIR)/FontHandler.o
GENERATED += $(OBJDIR)/GameObject.o
GENERATED += $(OBJDIR)/Generic.o
GENERATED += $(OBJDIR)/Image.o
GENERATED += $(OBJDIR)/IndexBuffer.o
GENERATED += $(OBJDIR)/Input.o
GENERATED += $(OBJDIR)/Music.o
GENERATED += $(OBJDIR)/Rect.o
GENERATED += $(OBJDIR)/Renderer.o
GENERATED += $(OBJDIR)/Resources.o
GENERATED += $(OBJDIR)/ScreenFade.o
GENERATED += $(OBJDIR)/ScreenFilter.o
GENERATED += $(OBJDIR)/Shader.o
GENERATED += $(OBJDIR)/Sound.o
GENERATED += $(OBJDIR)/Sprite.o
GENERATED += $(OBJDIR)/State.o
GENERATED += $(OBJDIR)/Text.o
GENERATED += $(OBJDIR)/Texture.o
GENERATED += $(OBJDIR)/TileMap.o
GENERATED += $(OBJDIR)/TileSet.o
GENERATED += $(OBJDIR)/Timer.o
GENERATED += $(OBJDIR)/Tools.o
GENERATED += $(OBJDIR)/Vector2.o
GENERATED += $(OBJDIR)/VertexArray.o
GENERATED += $(OBJDIR)/VertexBuffer.o
GENERATED += $(OBJDIR)/VertexBufferLayout.o
GENERATED += $(OBJDIR)/Window.o
GENERATED += $(OBJDIR)/Xrand.o
GENERATED += $(OBJDIR)/glm.o
GENERATED += $(OBJDIR)/main.o
OBJECTS += $(OBJDIR)/Camera.o
OBJECTS += $(OBJDIR)/CameraFollower.o
OBJECTS += $(OBJDIR)/Circle.o
OBJECTS += $(OBJDIR)/Collider.o
OBJECTS += $(OBJDIR)/Color.o
OBJECTS += $(OBJDIR)/Component.o
OBJECTS += $(OBJDIR)/Draw.o
OBJECTS += $(OBJDIR)/Engine.o
OBJECTS += $(OBJDIR)/FontHandler.o
OBJECTS += $(OBJDIR)/GameObject.o
OBJECTS += $(OBJDIR)/Generic.o
OBJECTS += $(OBJDIR)/Image.o
OBJECTS += $(OBJDIR)/IndexBuffer.o
OBJECTS += $(OBJDIR)/Input.o
OBJECTS += $(OBJDIR)/Music.o
OBJECTS += $(OBJDIR)/Rect.o
OBJECTS += $(OBJDIR)/Renderer.o
OBJECTS += $(OBJDIR)/Resources.o
OBJECTS += $(OBJDIR)/ScreenFade.o
OBJECTS += $(OBJDIR)/ScreenFilter.o
OBJECTS += $(OBJDIR)/Shader.o
OBJECTS += $(OBJDIR)/Sound.o
OBJECTS += $(OBJDIR)/Sprite.o
OBJECTS += $(OBJDIR)/State.o
OBJECTS += $(OBJDIR)/Text.o
OBJECTS += $(OBJDIR)/Texture.o
OBJECTS += $(OBJDIR)/TileMap.o
OBJECTS += $(OBJDIR)/TileSet.o
OBJECTS += $(OBJDIR)/Timer.o
OBJECTS += $(OBJDIR)/Tools.o
OBJECTS += $(OBJDIR)/Vector2.o
OBJECTS += $(OBJDIR)/VertexArray.o
OBJECTS += $(OBJDIR)/VertexBuffer.o
OBJECTS += $(OBJDIR)/VertexBufferLayout.o
OBJECTS += $(OBJDIR)/Window.o
OBJECTS += $(OBJDIR)/Xrand.o
OBJECTS += $(OBJDIR)/glm.o
OBJECTS += $(OBJDIR)/main.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking LichenEngine
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning LichenEngine
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) del /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/Camera.o: engine/src/Camera.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CameraFollower.o: engine/src/CameraFollower.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Circle.o: engine/src/Circle.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Collider.o: engine/src/Collider.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Color.o: engine/src/Color.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Component.o: engine/src/Component.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Draw.o: engine/src/Draw.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Engine.o: engine/src/Engine.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/FontHandler.o: engine/src/FontHandler.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/GameObject.o: engine/src/GameObject.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Generic.o: engine/src/Generic.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Image.o: engine/src/Image.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/IndexBuffer.o: engine/src/IndexBuffer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Input.o: engine/src/Input.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Music.o: engine/src/Music.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Rect.o: engine/src/Rect.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Renderer.o: engine/src/Renderer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Resources.o: engine/src/Resources.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ScreenFade.o: engine/src/ScreenFade.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ScreenFilter.o: engine/src/ScreenFilter.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Shader.o: engine/src/Shader.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Sound.o: engine/src/Sound.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Sprite.o: engine/src/Sprite.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/State.o: engine/src/State.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Text.o: engine/src/Text.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Texture.o: engine/src/Texture.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TileMap.o: engine/src/TileMap.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TileSet.o: engine/src/TileSet.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Timer.o: engine/src/Timer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Tools.o: engine/src/Tools.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Vector2.o: engine/src/Vector2.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexArray.o: engine/src/VertexArray.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexBuffer.o: engine/src/VertexBuffer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexBufferLayout.o: engine/src/VertexBufferLayout.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Window.o: engine/src/Window.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Xrand.o: engine/src/Xrand.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/glm.o: extlib/include/GLM/detail/glm.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/main.o: game/src/main.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif