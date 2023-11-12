#include "astrodynamics.hpp"



void PlanarCentralBody(State4D_ECI x, Control2D u, State4D_ECI& next_state)
{
    // Velocity
    for (int i = 0; i < 2; i++) {
        next_state[i] = x[i + 2]; 
    }

    // Acceleration
    double norm_r = std::sqrt(x[0] * x[0] + x[1] * x[1]);
    for (int i = 2; i < 4; i++) {
        next_state[i] = - (MU / std::pow(norm_r, 3)) * x[i] + u[i - 2]; // Control input is acceleration
    }
}

void CentralBody(State6D_ECI x, Control3D u, State6D_ECI& next_state)
{
    // Velocity
    for (int i = 0; i < 3; i++) {
        next_state[i] = x[i + 3]; 
    }

    // Acceleration
    double norm_r = std::sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
    for (int i = 3; i < 6; i++) {
        next_state[i] = - (MU / std::pow(norm_r, 3)) * x[i] + u[i - 3]; // Control input is acceleration
    }
}

void PlanarCentralBodyScaled(State4D_ECI x, Control2D u, State4D_ECI& next_state)
{
    // Update next_state based on scaled calculations
}

void CentralBodyScaled(State6D_ECI state, Control3D control, State6D_ECI& next_state)
{
    // Update next_state based on scaled calculations
}

void CR3BP(State6D state, Control3D control, State6D& state_dot)
{
    // Update state_dot for CR3BP
}


void SampleOrbit(State6D_OE orb_elem_min, State6D_OE orb_elem_max, State4D_ECI &sampled_eci_state)
{

}

void SampleOrbit(State6D_OE orb_elem_min, State6D_OE orb_elem_max, State6D_ECI &sampled_eci_state)
{

}

void SampleOrbit(std::string region, State6D_ECI &sampled_eci_state)
{

}

void SampleAroundOrbit(State6D_ECI current_state, State6D_ECI &sampled_eci_state)
{

}


State6D_ECI OE2ECI(State6D_OE orbital_elements)
{

}

State6D_OE ECI2OE(State6D_ECI eci_state)
{
    
}