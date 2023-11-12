#include <string>
#include "states.hpp"

/*
TODO 
- Docs for each function 
- Implement scaled dynamics
- Implement CR3BP
- Implement orbital elements samplers


*/


// Dynamics function 

void PlanarCentralBody(State4D_ECI state, Control2D control, State4D_ECI& state_dot);

void CentralBody(State6D_ECI state, Control3D control, State6D_ECI& state_dot);

void PlanarCentralBodyScaled(State4D_ECI state, Control2D control, State4D_ECI& state_dot);

void CentralBodyScaled(State6D_ECI state, Control3D control, State6D_ECI& state_dot);

void CR3BP(State6D state, Control3D control, State6D& state_dot);


// Helpers 

void SampleOrbit(State6D_OE orb_elem_min, State6D_OE orb_elem_max, State4D_ECI &sampled_eci_state);

void SampleOrbit(State6D_OE orb_elem_min, State6D_OE orb_elem_max, State6D_ECI &sampled_eci_state);

// TODO will just use above
void SampleOrbit(std::string region, State6D_ECI &sampled_eci_state);


// Sample within a given delta OE around the current orbit 
void SampleAroundOrbit(State6D_ECI current_state, State6D_ECI &sampled_eci_state);

State6D_ECI OE2ECI(State6D_OE orbital_elements);

State6D_OE ECI2OE(State6D_ECI eci_state);