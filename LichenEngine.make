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
INCLUDES += -Iextlib/include -Iengine/include -Igame/include
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS += -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm -lglfw3 -lgdi32 -lopengl32 -lglew32
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
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -flto -O3 -mwindows
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -flto -O3 -std=c++17 -mwindows
ALL_LDFLAGS += $(LDFLAGS) -Lextlib/lib -L/usr/lib32 -m32 -flto -s

else ifeq ($(config),profiler)
TARGETDIR = bin
TARGET = $(TARGETDIR)/LichenEngine_profiler-windows-x86.exe
OBJDIR = bin/obj/profiler
DEFINES +=
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

GENERATED += $(OBJDIR)/AACircle.o
GENERATED += $(OBJDIR)/AACollider.o
GENERATED += $(OBJDIR)/AARay.o
GENERATED += $(OBJDIR)/AARectangle.o
GENERATED += $(OBJDIR)/AStar.o
GENERATED += $(OBJDIR)/ActiveArea.o
GENERATED += $(OBJDIR)/Alien.o
GENERATED += $(OBJDIR)/Attack.o
GENERATED += $(OBJDIR)/Biagia.o
GENERATED += $(OBJDIR)/Bullet.o
GENERATED += $(OBJDIR)/Camera.o
GENERATED += $(OBJDIR)/CameraFollower.o
GENERATED += $(OBJDIR)/Circle.o
GENERATED += $(OBJDIR)/Collider.o
GENERATED += $(OBJDIR)/Color.o
GENERATED += $(OBJDIR)/Combat.o
GENERATED += $(OBJDIR)/Component.o
GENERATED += $(OBJDIR)/Controls.o
GENERATED += $(OBJDIR)/Critter.o
GENERATED += $(OBJDIR)/Dialogue.o
GENERATED += $(OBJDIR)/DialogueDTO.o
GENERATED += $(OBJDIR)/DistanceTrigger.o
GENERATED += $(OBJDIR)/Draw.o
GENERATED += $(OBJDIR)/Dummy.o
GENERATED += $(OBJDIR)/ElementLoader.o
GENERATED += $(OBJDIR)/Emitter.o
GENERATED += $(OBJDIR)/EndScene.o
GENERATED += $(OBJDIR)/EndScreen.o
GENERATED += $(OBJDIR)/Enemy.o
GENERATED += $(OBJDIR)/EnemyFactory.o
GENERATED += $(OBJDIR)/EnemyTest.o
GENERATED += $(OBJDIR)/Engine.o
GENERATED += $(OBJDIR)/Enum.o
GENERATED += $(OBJDIR)/Equipment.o
GENERATED += $(OBJDIR)/EventChain.o
GENERATED += $(OBJDIR)/Fade.o
GENERATED += $(OBJDIR)/Filter.o
GENERATED += $(OBJDIR)/FitzGerald.o
GENERATED += $(OBJDIR)/FontHandler.o
GENERATED += $(OBJDIR)/GameObject.o
GENERATED += $(OBJDIR)/GameStats.o
GENERATED += $(OBJDIR)/Generic.o
GENERATED += $(OBJDIR)/Image.o
GENERATED += $(OBJDIR)/IndexBuffer.o
GENERATED += $(OBJDIR)/Input.o
GENERATED += $(OBJDIR)/Inventory.o
GENERATED += $(OBJDIR)/Item.o
GENERATED += $(OBJDIR)/JsonParser.o
GENERATED += $(OBJDIR)/LoopSprite.o
GENERATED += $(OBJDIR)/MainGame.o
GENERATED += $(OBJDIR)/MainMenu.o
GENERATED += $(OBJDIR)/Malachi.o
GENERATED += $(OBJDIR)/Minion.o
GENERATED += $(OBJDIR)/Music.o
GENERATED += $(OBJDIR)/MusicPlayer.o
GENERATED += $(OBJDIR)/OnDelete.o
GENERATED += $(OBJDIR)/Particles.o
GENERATED += $(OBJDIR)/PenguinBody.o
GENERATED += $(OBJDIR)/PenguinCannon.o
GENERATED += $(OBJDIR)/Physics.o
GENERATED += $(OBJDIR)/Player.o
GENERATED += $(OBJDIR)/Progress.o
GENERATED += $(OBJDIR)/Projectile.o
GENERATED += $(OBJDIR)/Rectangle.o
GENERATED += $(OBJDIR)/Renderer.o
GENERATED += $(OBJDIR)/Resources.o
GENERATED += $(OBJDIR)/Scene.o
GENERATED += $(OBJDIR)/Shader.o
GENERATED += $(OBJDIR)/SimpleMovement.o
GENERATED += $(OBJDIR)/Slime.o
GENERATED += $(OBJDIR)/SlimeEnemy.o
GENERATED += $(OBJDIR)/Sound.o
GENERATED += $(OBJDIR)/Spawner.o
GENERATED += $(OBJDIR)/Sprite.o
GENERATED += $(OBJDIR)/StageScene.o
GENERATED += $(OBJDIR)/StateMachine.o
GENERATED += $(OBJDIR)/TestScene.o
GENERATED += $(OBJDIR)/Text.o
GENERATED += $(OBJDIR)/Texture.o
GENERATED += $(OBJDIR)/TileMap.o
GENERATED += $(OBJDIR)/TileSet.o
GENERATED += $(OBJDIR)/TimedText.o
GENERATED += $(OBJDIR)/Timer.o
GENERATED += $(OBJDIR)/TitleScene.o
GENERATED += $(OBJDIR)/Tools.o
GENERATED += $(OBJDIR)/UIBagMenu.o
GENERATED += $(OBJDIR)/UIBasicComponents.o
GENERATED += $(OBJDIR)/UIComponent.o
GENERATED += $(OBJDIR)/UIController.o
GENERATED += $(OBJDIR)/UIItem.o
GENERATED += $(OBJDIR)/UIPlayerBar.o
GENERATED += $(OBJDIR)/Vector2.o
GENERATED += $(OBJDIR)/VertexArray.o
GENERATED += $(OBJDIR)/VertexBuffer.o
GENERATED += $(OBJDIR)/VertexBufferLayout.o
GENERATED += $(OBJDIR)/Window.o
GENERATED += $(OBJDIR)/Xrand.o
GENERATED += $(OBJDIR)/main.o
OBJECTS += $(OBJDIR)/AACircle.o
OBJECTS += $(OBJDIR)/AACollider.o
OBJECTS += $(OBJDIR)/AARay.o
OBJECTS += $(OBJDIR)/AARectangle.o
OBJECTS += $(OBJDIR)/AStar.o
OBJECTS += $(OBJDIR)/ActiveArea.o
OBJECTS += $(OBJDIR)/Alien.o
OBJECTS += $(OBJDIR)/Attack.o
OBJECTS += $(OBJDIR)/Biagia.o
OBJECTS += $(OBJDIR)/Bullet.o
OBJECTS += $(OBJDIR)/Camera.o
OBJECTS += $(OBJDIR)/CameraFollower.o
OBJECTS += $(OBJDIR)/Circle.o
OBJECTS += $(OBJDIR)/Collider.o
OBJECTS += $(OBJDIR)/Color.o
OBJECTS += $(OBJDIR)/Combat.o
OBJECTS += $(OBJDIR)/Component.o
OBJECTS += $(OBJDIR)/Controls.o
OBJECTS += $(OBJDIR)/Critter.o
OBJECTS += $(OBJDIR)/Dialogue.o
OBJECTS += $(OBJDIR)/DialogueDTO.o
OBJECTS += $(OBJDIR)/DistanceTrigger.o
OBJECTS += $(OBJDIR)/Draw.o
OBJECTS += $(OBJDIR)/Dummy.o
OBJECTS += $(OBJDIR)/ElementLoader.o
OBJECTS += $(OBJDIR)/Emitter.o
OBJECTS += $(OBJDIR)/EndScene.o
OBJECTS += $(OBJDIR)/EndScreen.o
OBJECTS += $(OBJDIR)/Enemy.o
OBJECTS += $(OBJDIR)/EnemyFactory.o
OBJECTS += $(OBJDIR)/EnemyTest.o
OBJECTS += $(OBJDIR)/Engine.o
OBJECTS += $(OBJDIR)/Enum.o
OBJECTS += $(OBJDIR)/Equipment.o
OBJECTS += $(OBJDIR)/EventChain.o
OBJECTS += $(OBJDIR)/Fade.o
OBJECTS += $(OBJDIR)/Filter.o
OBJECTS += $(OBJDIR)/FitzGerald.o
OBJECTS += $(OBJDIR)/FontHandler.o
OBJECTS += $(OBJDIR)/GameObject.o
OBJECTS += $(OBJDIR)/GameStats.o
OBJECTS += $(OBJDIR)/Generic.o
OBJECTS += $(OBJDIR)/Image.o
OBJECTS += $(OBJDIR)/IndexBuffer.o
OBJECTS += $(OBJDIR)/Input.o
OBJECTS += $(OBJDIR)/Inventory.o
OBJECTS += $(OBJDIR)/Item.o
OBJECTS += $(OBJDIR)/JsonParser.o
OBJECTS += $(OBJDIR)/LoopSprite.o
OBJECTS += $(OBJDIR)/MainGame.o
OBJECTS += $(OBJDIR)/MainMenu.o
OBJECTS += $(OBJDIR)/Malachi.o
OBJECTS += $(OBJDIR)/Minion.o
OBJECTS += $(OBJDIR)/Music.o
OBJECTS += $(OBJDIR)/MusicPlayer.o
OBJECTS += $(OBJDIR)/OnDelete.o
OBJECTS += $(OBJDIR)/Particles.o
OBJECTS += $(OBJDIR)/PenguinBody.o
OBJECTS += $(OBJDIR)/PenguinCannon.o
OBJECTS += $(OBJDIR)/Physics.o
OBJECTS += $(OBJDIR)/Player.o
OBJECTS += $(OBJDIR)/Progress.o
OBJECTS += $(OBJDIR)/Projectile.o
OBJECTS += $(OBJDIR)/Rectangle.o
OBJECTS += $(OBJDIR)/Renderer.o
OBJECTS += $(OBJDIR)/Resources.o
OBJECTS += $(OBJDIR)/Scene.o
OBJECTS += $(OBJDIR)/Shader.o
OBJECTS += $(OBJDIR)/SimpleMovement.o
OBJECTS += $(OBJDIR)/Slime.o
OBJECTS += $(OBJDIR)/SlimeEnemy.o
OBJECTS += $(OBJDIR)/Sound.o
OBJECTS += $(OBJDIR)/Spawner.o
OBJECTS += $(OBJDIR)/Sprite.o
OBJECTS += $(OBJDIR)/StageScene.o
OBJECTS += $(OBJDIR)/StateMachine.o
OBJECTS += $(OBJDIR)/TestScene.o
OBJECTS += $(OBJDIR)/Text.o
OBJECTS += $(OBJDIR)/Texture.o
OBJECTS += $(OBJDIR)/TileMap.o
OBJECTS += $(OBJDIR)/TileSet.o
OBJECTS += $(OBJDIR)/TimedText.o
OBJECTS += $(OBJDIR)/Timer.o
OBJECTS += $(OBJDIR)/TitleScene.o
OBJECTS += $(OBJDIR)/Tools.o
OBJECTS += $(OBJDIR)/UIBagMenu.o
OBJECTS += $(OBJDIR)/UIBasicComponents.o
OBJECTS += $(OBJDIR)/UIComponent.o
OBJECTS += $(OBJDIR)/UIController.o
OBJECTS += $(OBJDIR)/UIItem.o
OBJECTS += $(OBJDIR)/UIPlayerBar.o
OBJECTS += $(OBJDIR)/Vector2.o
OBJECTS += $(OBJDIR)/VertexArray.o
OBJECTS += $(OBJDIR)/VertexBuffer.o
OBJECTS += $(OBJDIR)/VertexBufferLayout.o
OBJECTS += $(OBJDIR)/Window.o
OBJECTS += $(OBJDIR)/Xrand.o
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

$(OBJDIR)/AACircle.o: engine/src/Components/AACircle.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/AACollider.o: engine/src/Components/AACollider.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/AARay.o: engine/src/Components/AARay.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/AARectangle.o: engine/src/Components/AARectangle.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CameraFollower.o: engine/src/Components/CameraFollower.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Collider.o: engine/src/Components/Collider.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Component.o: engine/src/Components/Component.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Fade.o: engine/src/Components/Fade.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Filter.o: engine/src/Components/Filter.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Generic.o: engine/src/Components/Generic.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Sound.o: engine/src/Components/Sound.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Sprite.o: engine/src/Components/Sprite.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/StateMachine.o: engine/src/Components/StateMachine.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Text.o: engine/src/Components/Text.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TileMap.o: engine/src/Components/TileMap.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TileSet.o: engine/src/Components/TileSet.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Camera.o: engine/src/Core/Camera.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Engine.o: engine/src/Core/Engine.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Enum.o: engine/src/Core/Enum.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/GameObject.o: engine/src/Core/GameObject.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Input.o: engine/src/Core/Input.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Music.o: engine/src/Core/Music.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Renderer.o: engine/src/Core/Renderer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Resources.o: engine/src/Core/Resources.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Scene.o: engine/src/Core/Scene.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Window.o: engine/src/Core/Window.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Draw.o: engine/src/Graphics/Draw.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/FontHandler.o: engine/src/Graphics/FontHandler.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Image.o: engine/src/Graphics/Image.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/IndexBuffer.o: engine/src/Graphics/IndexBuffer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Shader.o: engine/src/Graphics/Shader.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Texture.o: engine/src/Graphics/Texture.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexArray.o: engine/src/Graphics/VertexArray.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexBuffer.o: engine/src/Graphics/VertexBuffer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexBufferLayout.o: engine/src/Graphics/VertexBufferLayout.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Circle.o: engine/src/Math/Circle.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Physics.o: engine/src/Math/Physics.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Rectangle.o: engine/src/Math/Rectangle.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Vector2.o: engine/src/Math/Vector2.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/AStar.o: engine/src/Tools/AStar.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Color.o: engine/src/Tools/Color.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Particles.o: engine/src/Tools/Particles.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Timer.o: engine/src/Tools/Timer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Tools.o: engine/src/Tools/Tools.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Xrand.o: engine/src/Tools/Xrand.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Player.o: game/src/Character/Player.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/DialogueDTO.o: game/src/DTO/DialogueDTO.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Dialogue.o: game/src/Dialogue.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Dummy.o: game/src/Dummy.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Biagia.o: game/src/Enemy/Biagia.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Enemy.o: game/src/Enemy/Enemy.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/EnemyFactory.o: game/src/Enemy/EnemyFactory.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/FitzGerald.o: game/src/Enemy/FitzGerald.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Malachi.o: game/src/Enemy/Malachi.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Projectile.o: game/src/Enemy/Projectile.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Slime.o: game/src/Enemy/Slime.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SlimeEnemy.o: game/src/Enemy/SlimeEnemy.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/EnemyTest.o: game/src/EnemyTest.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Alien.o: game/src/Legacy/Alien.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Bullet.o: game/src/Legacy/Bullet.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/EndScene.o: game/src/Legacy/EndScene.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/GameStats.o: game/src/Legacy/GameStats.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Minion.o: game/src/Legacy/Minion.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/PenguinBody.o: game/src/Legacy/PenguinBody.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/PenguinCannon.o: game/src/Legacy/PenguinCannon.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/StageScene.o: game/src/Legacy/StageScene.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TitleScene.o: game/src/Legacy/TitleScene.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Attack.o: game/src/Mechanics/Attack.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Combat.o: game/src/Mechanics/Combat.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Equipment.o: game/src/Mechanics/Equipment.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Inventory.o: game/src/Mechanics/Inventory.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Item.o: game/src/Mechanics/Item.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Progress.o: game/src/Mechanics/Progress.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Critter.o: game/src/Npc/Critter.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/EndScreen.o: game/src/Scene/EndScreen.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MainGame.o: game/src/Scene/MainGame.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MainMenu.o: game/src/Scene/MainMenu.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestScene.o: game/src/TestScene.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ActiveArea.o: game/src/Tools/ActiveArea.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Controls.o: game/src/Tools/Controls.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/DistanceTrigger.o: game/src/Tools/DistanceTrigger.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ElementLoader.o: game/src/Tools/ElementLoader.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Emitter.o: game/src/Tools/Emitter.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/EventChain.o: game/src/Tools/EventChain.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/JsonParser.o: game/src/Tools/JsonParser.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/LoopSprite.o: game/src/Tools/LoopSprite.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/MusicPlayer.o: game/src/Tools/MusicPlayer.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/OnDelete.o: game/src/Tools/OnDelete.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/SimpleMovement.o: game/src/Tools/SimpleMovement.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Spawner.o: game/src/Tools/Spawner.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TimedText.o: game/src/Tools/TimedText.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/UIBagMenu.o: game/src/UserInterface/UIBagMenu.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/UIBasicComponents.o: game/src/UserInterface/UIBasicComponents.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/UIComponent.o: game/src/UserInterface/UIComponent.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/UIController.o: game/src/UserInterface/UIController.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/UIItem.o: game/src/UserInterface/UIItem.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/UIPlayerBar.o: game/src/UserInterface/UIPlayerBar.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/main.o: game/src/main.cpp
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif