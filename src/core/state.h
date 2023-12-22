/**
 * @file state.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Central game state management
 * @version 0.1
 * @date 2023-12-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <memory>

namespace oshc::core::state
{

// Class
class State;

/**
 * @brief Enum of possible game states
 *
 */
enum class ProgramState
{
    STATE_INIT,
    STATE_INTRO,
    STATE_GAME,
    STATE_MENU,
    STATE_EXIT,
    STATE_NULL
};

/**
 * @brief State engine
 *
 */
class StateEngine
{
  public:
    /**
     * @brief Update active state
     *
     */
    void update();

    /**
     * @brief Render active state
     *
     */
    void render() const;

    /**
     * @brief Set the Next State
     *
     * @param state Next state id
     */
    void set_next_state(const ProgramState state);

    /**
     * @brief Get the active state id
     *
     * @return ProgramState
     */
    ProgramState get_active_state_id() const;

  private:
    /**
     * @brief Internal state change routine
     *
     */
    void change_state();

    /// @breif Next state in queue
    ProgramState m_next_state{ProgramState::STATE_NULL};

    /// @breif Active state
    ProgramState m_active_state{ProgramState::STATE_NULL};

    /// @brief Pointer to active state
    std::unique_ptr<State> m_state{nullptr};
};

/**
 * @brief State base class
 *
 */
class State
{
  public:
    /**
     * @brief Create a new state
     *
     * @param engine State engine reference
     */
    explicit State() = default;

    /// @brief Default destructor
    virtual ~State() = default;

    /**
     * @brief On state init
     *
     */
    virtual void init() = 0;

    /**
     * @brief On state render
     *
     */
    virtual void render() = 0;

    /**
     * @brief On state destroy
     *
     */
    virtual void destroy() = 0;

    /**
     * @brief On state update
     *
     */
    virtual void update() = 0;
};

} // namespace oshc::core::state
