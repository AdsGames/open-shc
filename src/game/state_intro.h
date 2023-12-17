/**
 * @file state_intro.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Intro state
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

/**
 * @brief Intro state
 *
 */
class StateIntro : public oshc::core::state::State
{
  public:
    /**
     * @brief Construct a new State Intro object
     *
     */
    explicit StateIntro(oshc::core::state::StateEngine &engine) : oshc::core::state::State(engine){};

    /**
     * @brief Destroy the State Intro object
     *
     */
    ~StateIntro() override = default;

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
