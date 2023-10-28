# On-Orbit Optimal Kinodynamic Planning for Low-Thrust Trajectory Maneuvers

Group: Ibrahima, Juan, Nayana, Fausto

For our project, we would like to design and generate a low-thrust trajectory for a spacecraft orbital transfer (i.e. GEO to GTO transfer maneuver)[1]. This problem presents extensive challenges as the dynamics are highly nonlinear, the spacecraft has little control authority (several orders of magnitude difference compared to traditional chemically propelled trajectory), and is typically underactuated. Furthermore, those trajectories span over weeks and months involving a significant problem size and potential numerical difficulties.

We want to leverage the cost-to-go function of linear quadratic regulation (LQR) as a cost metric to extend a particular sampling-based planner (e.g. RRT*) and compare this approach to other optimal-based sampling-based planners. In particular, we take inspiration from [2]. We plan on implementing our approach in C++ with visualization in ROS/Rviz or Meshcat.  

[1] Tracy, Kevin, and Zac Manchester. “Low-Thrust Trajectory Optimization Using the Kustaanheimo-Stiefel Transformation”. AAS/AIAA Space Flight Mechanics Meeting. Charlotte, NC.

[2] Perez, Alejandro, et al. "LQR-RRT*: Optimal sampling-based motion planning with automatically derived extension heuristics." 2012 IEEE International Conference on Robotics and Automation. IEEE, 2012.

# TODO (non-exhaustive)
- Planar dynamics
- RRT, RRT* implementation (+ others if necessary)
- LQR cost-to-go
- Orbit sampling (LEO, MEO, GEO, GTO, Lunar)
- Conversion orbital elements >< cartesian state 
- DeltaV instead of thrust 
- Automated file saving trajectory + format
- Automated visualizer, spacecraft mesh + planets/solar system/background (need to handle the scale)


