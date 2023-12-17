/**
 * @file state_init.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Initial state
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
 * @brief Initial state
 *
 */
class StateInit : public oshc::core::state::State
{
  public:
    /**
     * @brief Construct a new State Init object
     *
     */
    using State::State;

    /**
     * @brief Destroy the State Init object
     *
     */
    ~StateInit() override = default;

    /**
     * @brief Init state
     *
     */
    void init() override;

    /**
     * @brief Update state
     *
     */
    void update() override;

    /**
     * @brief Render state
     *
     */
    void render() override;

    /**
     * @brief Destroy state
     *
     */
    void destroy() override;

  private:
    /// @brief Fake loader
    int m_fake_loader = 0;
};

} // namespace oshc::state
