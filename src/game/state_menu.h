/**
 * @file state_menu.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Menu state
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
class StateMenu : public oshc::core::state::State
{
  public:
    /**
     * @brief Construct a new State Menu object
     *
     */
    explicit StateMenu(oshc::core::state::StateEngine &engine) : oshc::core::state::State(engine){};

    /**
     * @brief Destroy the State Menu object
     *
     */
    ~StateMenu() override = default;

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
    void render() override;

    /**
     * @brief Destroy state
     *
     */
    void destroy() override{};
};

} // namespace oshc::state
