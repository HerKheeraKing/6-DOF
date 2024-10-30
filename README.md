# 6-DOF

This project brings servo-controlled movements to life with smooth, automated motion, using Lerp functions to match SolidWorks-simulated ranges. In the main loop, it calculates elapsed time relative to each step and moves the "heave" motion through up, center, and down positions every 500ms for a total of 2 seconds. Then, it sequences through sway, surge, heave, pitch, roll, and yaw in a smooth 12-second cycle. If any movements are too subtle, the code recalibrates to add more noticeable motion based on updated simulation settings.



#LICENSE INFO This source code is available for viewing only. Usage of the code in any form is prohibited without explicit permission. Please refer to the LICENSE file for more details.
