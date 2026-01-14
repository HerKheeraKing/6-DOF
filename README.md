<h1 align="center">6-DOF Mini Flight Simulator</h1>

##### <p align="center"> Ever wondered how theme park rides or flight simulators make your body feel like you're moving, even when you're not?
</p>

  <p align="center"> This mini Stewart platform is a scaled-down, servo-powered replica designed to recreate that same sensation! Just like the full-size flight simulator we've been building at Uni.
  </p>


<div align="center">
  <img src="Images/SP-Body-Transparent-Photoroom.png" width="400" />
</div>  

<br><br>
#### Stewart Platform SOLIDWORKS Drawing:
<div align="left">
<img src="Images/Stewart Platform Drawing.png" width="600" />
</div>


# How it works:
🔁 Smooth motion control: Servo motors use Lerp functions to match real movement ranges from our SolidWorks simulation.

⏱️ Timing-based movement: Every 500ms, the platform shifts through heave positions up, center, and down for a total of 2 seconds.

🎯 Full motion cycle: Then it glides through a 12-second loop of:
→ sway, surge, heave, pitch, roll, and yaw

🛠️ Auto-adjusts for clarity: If the movements feel too subtle, the code automatically recalibrates to make the motion more noticeable.

Tools: SolidWorks, Arduino, Fabrication
<br><br>

## Demo Videos  

##### 🎮 POV: Mini Stewart Platform in Action -> Click To Watch!
<p align="left">
  <a href="https://youtu.be/SF3ZUqv63FA">
    <img src="Images/Car rides stewart.png" width="400" alt="Car Ride Demo"/>
  </a>
</p>

<br>

##### 🎥 Stewart Platform Self Demo -> Click To Watch!
<p align="left">
  <a href="https://youtu.be/Fm8VqOVstzQ">
    <img src="Images/stewart self.png" width="400" alt="Full-Cycle Demo"/>
  </a>
</p>

<br><br><br>
#### 📄 LICENSE INFO 
This source code is available for viewing only. Usage of the code in any form is prohibited without explicit permission. Please refer to the LICENSE file for more details.
