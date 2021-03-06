#ifndef ENGINE_H
#define ENGINE_H

#define GLFW_INCLUDE_GLCOREARB

#include <memory>
#include "component_manager.h"
#include "utility/fps_counter.h"
#include "input/input_system.h"
#include "graphics/ui/font_generator.h"
#include "graphics/graphics_system.h"
#include "graphics/shader_manager.h"
#include "graphics/texture_manager.h"
#include "utility/config_manager.h"
#include "game/scene.h"
#include "utility/debug_parser.h"
#include "graphics/ui/text_area.h"
#include "script/scripting_system.h"
#include "sound/sound_system.h"

/**
 * @brief      Class for engine.
 */
class [[scriptable]] Engine : public std::enable_shared_from_this<Engine> {
  private:
    std::shared_ptr<ComponentManager> component_manager;
    std::shared_ptr<Utility::FPSCounter> fps_counter;
    std::shared_ptr<Input::InputSystem> input_system;
    std::shared_ptr<Graphics::UI::FontGenerator> font_generator;
    std::shared_ptr<Graphics::GraphicsSystem> graphics_system;
    std::shared_ptr<Graphics::ShaderManager> shader_manager;
    std::shared_ptr<Graphics::TextureManager> texture_manager;
    std::shared_ptr<Utility::ConfigManager> config_manager;
    std::shared_ptr<Script::ScriptingSystem> scripting_system;
    std::shared_ptr<Sound::SoundSystem> sound_system;

    //Bool represents if the scene is active;
    std::map<std::shared_ptr<Game::Scene>, bool> scenes;

    float viewport_tile_width;
    float viewport_tile_height;

    bool time_to_exit;
    std::shared_ptr<Graphics::Camera> camera_component;

    void loadScriptingSystemSave();

  public:
    /**
     * @brief      Engine constructor
     */
    Engine();
    /**
     * @brief      Engine destructor
     */
    virtual ~Engine() = default;

    /**
     * @brief      Adds a scene to the engine.
     *
     * @param[in]  scene  The scene
     */
    [[scriptable]] void addScene(std::shared_ptr<Game::Scene> scene) noexcept;
    /**
     * @brief      Finds a scene by name
     *
     * @param[in]  name  The name
     *
     * @return     The scene, nullptr if it doesn't exist
     */
    [[scriptable]] std::shared_ptr<Game::Scene> findSceneByName(const std::string& name) noexcept;

    /**
     * @brief      Gets the scenes.
     *
     * @return     The scenes.
     */
    [[scriptable]] std::map<std::shared_ptr<Game::Scene>, bool> getScenes() const noexcept;

    /**
     * @brief      Activates a scene by name
     *
     * @param[in]  name  The name
     */
    [[scriptable]] void activateScene(const std::string& name);
    /**
     * @brief      Deactivates a scene by name
     *
     * @param[in]  name  The name
     */
    [[scriptable]] void deactivateScene(const std::string& name);
    /**
     * @brief      Gets the scene names.
     *
     * @return     The scene names.
     */
    [[scriptable]] std::vector<std::string> getSceneNames() const noexcept;
    /**
     * @brief      Gets the active scene names.
     *
     * @return     The active scene names.
     */
    [[scriptable]] std::vector<std::string> getActiveSceneNames() const noexcept;

    /**
     * @brief      This is to signal the engine that it is time to shut down
     */
    [[scriptable]] void timeToExit() noexcept;

    /**
     * @brief      Sets up the engine
     *
     * @param[in]  config_path  The configuration path
     */
    void setup(const std::string config_path);
    /**
     * @brief      Triggers the main loop for the engine
     */
    void mainLoop();
    /**
     * @brief      Cleans up before exiting.
     */
    void cleanUp();

};

#endif
