/**
 * @file state_game.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Game state
 * @version 0.1
 * @date 2023-12-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "../core/state.h"

namespace oshc::state
{
class StateGame : public oshc::core::state::State
{
  public:
    /**
     * @brief Construct a new State Game object
     *
     */
    explicit StateGame(oshc::core::state::StateEngine &engine) : oshc::core::state::State(engine){};

    /**
     * @brief Destroy the State Game object
     *
     */
    ~StateGame() override = default;

    /**
     * @brief Init state
     *
     */
    void init() override{};

    /**
     * @brief Update state
     *
     */
    void update() override{};

    /**
     * @brief Render state
     *
     */
    void render() override{};

    /**
     * @brief Destroy state
     *
     */
    void destroy() override{};
};

} // namespace oshc::state
