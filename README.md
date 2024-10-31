# 6-DOF

This project brings servo-controlled movements to life with smooth, automated motion, using Lerp functions to match SolidWorks-simulated ranges. In the main loop, it calculates elapsed time relative to each step and moves the "heave" motion through up, center, and down positions every 500ms for a total of 2 seconds. Then, it sequences through sway, surge, heave, pitch, roll, and yaw in a smooth 12-second cycle. If any movements are too subtle, the code recalibrates to add more noticeable motion based on updated simulation settings.
<br>
<br>
<br>
START OF PROJECT~

The first step of this project was to design a Stewart platform in SolidWorks, capturing precise measurements of the platform’s positions as it moves through all six degrees of freedom (6DOF). I decided to add a cool spaceman design on top of the platform for the theme of the game I will be going with later in the project:
<div style="display: flex; justify-content: center;">
  <img src="Images/SW Screenshot.png" alt="Stewart Platform Design" width="400" style="margin-right: 20px;"/>
  <img src="Images/Spaceman Screenshot .png" alt="Spaceman Design" width="400" style="margin-right: 20px;"/>
</div>
<br>
<br>
<br>

SOLIDOWRKS DRAWING~

<div align="center">
  <img src="Images/Drawling of platform.png" alt="Stewart Platform Design Drawing" width="600"/>
</div>


<br>
<br>
<br>
<br>
<br>


PLATFORM ASSEMBLED~



  
#LICENSE INFO This source code is available for viewing only. Usage of the code in any form is prohibited without explicit permission. Please refer to the LICENSE file for more details.
