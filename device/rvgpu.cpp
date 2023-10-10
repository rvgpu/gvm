/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include "rvgpu.hpp"

#include "rvg_sim.hpp"
#include "rvg_phy.hpp"

RVGPU::RVGPU() {
    dev = new RVGSim();

    dev->TestFact();
}