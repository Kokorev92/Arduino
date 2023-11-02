#pragma once

/* ======================================== HTML code for index / main page */
static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<html>

  <head>
  
    <title>ESP32-CAM RC ROBOT CAR</title>
    
    <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no">
    
    <style>
    
      body {
        font-family: Arial; 
        text-align: center; 
        padding-top: 10px;
        max-width: 400px;   
        margin: 0 auto;
      }

      /* ----------------------------------- Slider */
      .slidecontainer {
        width: 100%;
      }

      .slider {
        -webkit-appearance: none;
        width: 100%;
        height: 5px;
        border-radius: 5px;
        background: #d3d3d3;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
      }

      .slider:hover {
        opacity: 1;
      }

      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 13px;
        height: 13px;
        border-radius: 50%;
        background: #04AA6D;
        cursor: pointer;
      }

      .slider::-moz-range-thumb {
        width: 13px;
        height: 13px;
        border-radius: 50%;
        background: #04AA6D;
        cursor: pointer;
      }
      /* ----------------------------------- */
      
      /* ----------------------------------- Button */
      .button {
        display: inline-block;
        padding: 5px;
        font-size: 8px;
        cursor: pointer;
        text-align: center;
        text-decoration: none;
        outline: none;
        color: #fff;
        background-color: #4CAF50;
        border: none;
        border-radius: 15px;
        box-shadow: 0 2px #999;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        width: 20%;
        height: 20px;
      }

      .button:hover {background-color: #3e8e41}

      .button:active {
        background-color: #3e8e41;
        box-shadow: 0 0px #666;
        transform: translateY(2px);
      }
      /* ----------------------------------- */
      
      /* ----------------------------------- */
      .space {
        width: 15%;
        height: auto;
        display: inline-block;
      }
      /* ----------------------------------- */

      /* ----------------------------------- Stream Viewer */
      img {
        width: 320px ;
        height: 240px ; 
      }
      /* ----------------------------------- */
      
    </style>
    
  </head>
  
  <body>
  
    <h3>ESP32-CAM RC ROBOT CAR</h3>
    
    <img src="" id="vdstream">
    
    <br><br>

    <div>
      <!-- The "T" and "M" suffixes are used to differentiate between touch screen input and mouse pointer input on buttons. -->
      <button class="button" ontouchstart="button_ontouchstart_handle('FT')" ontouchend="button_ontouchend_handle()" onmousedown="button_onmousedown_handle('FM')" onmouseup="button_onmouseup_handle()"><b>FORWARD</b></button>
      <br><br>
      <button class="button" ontouchstart="button_ontouchstart_handle('LT')" ontouchend="button_ontouchend_handle()" onmousedown="button_onmousedown_handle('LM')" onmouseup="button_onmouseup_handle()"><b>LEFT</b></button>
      <div class="space"></div>
      <button class="button" ontouchstart="button_ontouchstart_handle('RT')" ontouchend="button_ontouchend_handle()" onmousedown="button_onmousedown_handle('RM')" onmouseup="button_onmouseup_handle()"><b>RIGHT</b></button>
      <br><br>
      <button class="button" ontouchstart="button_ontouchstart_handle('BT')" ontouchend="button_ontouchend_handle()" onmousedown="button_onmousedown_handle('BM')" onmouseup="button_onmouseup_handle()"><b>BACKWARD</b></button>
    </div>
    
    <br>
    
    <table style="width:320px;margin:auto;table-layout:fixed" CELLSPACING=10>
      <tr>
        <td style="text-align:left;width:50px;">Speed</td>
        <td style="width:200px;">
          <div class="slidecontainer">
            <input type="range" min="0" max="10" value="5" class="slider" id="mySlider_pwm_Speed">
          </div>
        </td>
        <td style="text-align:right;font-weight:normal;width:20px;" id="slider_pwm_Speed_id">NN</td>
      </tr>
      
      <tr>
        <td>LED</td>
        <td>
          <div class="slidecontainer">
            <input type="range" min="0" max="10" value="0" class="slider" id="mySlider_pwm_LED">
          </div>
        </td>
        <td style="text-align:right;" id="slider_pwm_LED_id">NN</td>
      </tr>
      
      <tr>
        <td>Pan</td>
        <td>
          <div class="slidecontainer">
            <input type="range" min="0" max="180" value="75" class="slider" id="mySlider_Pan">
          </div>
        </td>
        <td style="text-align:right;" id="slider_Pan_id">NN</td>
      </tr>
      
      <tr>
        <td>Tilt</td>
        <td>
          <div class="slidecontainer">
            <input type="range" min="0" max="180" value="75" class="slider" id="mySlider_Tilt">
          </div>
        </td>
        <td style="text-align:right;" id="slider_Tilt_id">NN</td>
      </tr>
    </table>
    
    <script>
      /* ----------------------------------- Calls the video stream link and displays it. */ 
      window.onload = document.getElementById("vdstream").src = window.location.href.slice(0, -1) + ":81/stream";
      /* ----------------------------------- */
      
      /* ----------------------------------- Variables to get and display the values of the sliders. */
      var slider_pwm_Speed = document.getElementById("mySlider_pwm_Speed");
      var show_slider_pwm_Speed = document.getElementById("slider_pwm_Speed_id")
      show_slider_pwm_Speed.innerHTML = slider_pwm_Speed.value;
      send_cmd("SS," + slider_pwm_Speed.value);
      
      var slider_pwm_LED = document.getElementById("mySlider_pwm_LED");
      var show_slider_pwm_LED = document.getElementById("slider_pwm_LED_id")
      show_slider_pwm_LED.innerHTML = slider_pwm_LED.value;
      
      var slider_Pan = document.getElementById("mySlider_Pan");
      var show_slider_Pan = document.getElementById("slider_Pan_id")
      show_slider_Pan.innerHTML = slider_Pan.value;
      
      var slider_Tilt = document.getElementById("mySlider_Tilt");
      var show_slider_Tilt = document.getElementById("slider_Tilt_id")
      show_slider_Tilt.innerHTML = slider_Tilt.value;

      let slider_PanTilt_send_rslt = "";
      /* ----------------------------------- */
      
      /* ----------------------------------- Variable declarations for timers and their intervals. */
      /* :::::::::::::::::::::::::::::::::::::::::::::::: myTmr */
      // This timer is used to send commands to stop the rotation of the dc motor (the robot car stops).
      // Actually, when "ontouchend" and "onmouseup" the robot car stop command has been sent, but to make sure the stop command is sent,
      // I created this timer to send the stop command once again. In essence the stop command will be sent 2 times.
      var myTmr;
      var myTmr_Interval = 500;
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: myTmr_PanTiltCtr */
      // This timer is used to handle sending request data to control the servos on the Pan and Tilt Camera Mount using the "range slider".
      // Sending data requests to control servos must use a "delay" with the next sending of data requests.
      // Therefore this timer is used as a "delay".
      // Based on what I experienced, without "delay", there will be errors in the process of controlling the servos using the "range slider".
      // My knowledge is limited to web/html/javascript programming. So to solve that error, then using timer is the best I can do.
      // But the error does not occur on sending requests to "control the LED" and "Adjust Speed" using the "range slider".
      var myTmr_PanTiltCtr;
      var myTmr_PanTiltCtr_Interval = 200;
      var myTmr_PanTiltCtr_Start = 1;
      var myTmr_PanTiltCtr_Send = 0;
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */
      /* ----------------------------------- */

      // Variable declarations to differentiate the sending of button commands when the button is held down or just a single press.
      var onmousedown_stat = 0;

      /* ----------------------------------- Variable declaration for sending commands to ESP32 Cam from index/web page. */
      let btn_commands_rslt = "";
      /* ----------------------------------- */

      // Variable declarations to distinguish between button presses using the mouse or using the touch screen (on a mobile browser or in a browser on a touch screen device).
      var join_TM = 0;

      /* ---------------------------------------------------------------------- Update the current slider value (each time you drag the slider handle) */
      /* :::::::::::::::::::::::::::::::::::::::::::::::: slider_pwm_Speed */
      slider_pwm_Speed.oninput = function() {
        show_slider_pwm_Speed.innerHTML = slider_pwm_Speed.value;
        let slider_pwm_Speed_send = "SS," + slider_pwm_Speed.value;
        send_cmd(slider_pwm_Speed_send);
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: slider_pwm_LED */
      slider_pwm_LED.oninput = function() {
        show_slider_pwm_LED.innerHTML = slider_pwm_LED.value;
        let slider_pwm_LED_send = "SL," + slider_pwm_LED.value;
        send_cmd(slider_pwm_LED_send);
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: slider_Pan */
      slider_Pan.oninput = function() {
        show_slider_Pan.innerHTML = slider_Pan.value;
        let slider_Pan_send = "SP," + slider_Pan.value;
        slider_PanTilt_send_rslt = slider_Pan_send;
        myTmr_PanTiltCtr_Send = 1;
        if (myTmr_PanTiltCtr_Start == 1) {
          myTmr_PanTiltCtr = setInterval(myTimer_PanTiltCtr, myTmr_PanTiltCtr_Interval);
          myTmr_PanTiltCtr_Start = 0;
        }
      }

      slider_Pan.onchange = function() {
        myTmr_PanTiltCtr_Start = 1;
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */

      /* :::::::::::::::::::::::::::::::::::::::::::::::: slider_Tilt */
      slider_Tilt.oninput = function() {
        show_slider_Tilt.innerHTML = slider_Tilt.value;
        let slider_Tilt_send = "ST," + slider_Tilt.value;
        slider_PanTilt_send_rslt = slider_Tilt_send;
        myTmr_PanTiltCtr_Send = 1;
        if (myTmr_PanTiltCtr_Start == 1) {
          myTmr_PanTiltCtr = setInterval(myTimer_PanTiltCtr, myTmr_PanTiltCtr_Interval);
          myTmr_PanTiltCtr_Start = 0;
        }
      }

      slider_Tilt.onchange = function() {
        myTmr_PanTiltCtr_Start = 1;
      }
      /* :::::::::::::::::::::::::::::::::::::::::::::::: */
      /* ---------------------------------------------------------------------- */

      /* ---------------------------------------------------------------------- Functions to handle input of buttons. */
      function button_onmousedown_handle(cmds) {
        clearInterval(myTmr);
        btn_commands_rslt = cmds.substring(0, 1);
        if (join_TM == 0) {
          if (onmousedown_stat == 0) {
            send_btn_cmd(btn_commands_rslt);
            onmousedown_stat = 1;
          }   
        }  
      }

      function button_ontouchstart_handle(cmds) {
        clearInterval(myTmr);
        join_TM = 1;
        btn_commands_rslt = cmds.substring(0, 1);
        if (onmousedown_stat == 0) {
          send_btn_cmd(btn_commands_rslt);
          onmousedown_stat = 1;
        }
      }
      
      function button_onmouseup_handle() {
        if (join_TM == 0) {
          onmousedown_stat = 0;
          send_btn_cmd("S");  
          myTmr = setInterval(myTimer, myTmr_Interval);
        }
      }

      function button_ontouchend_handle() {
        join_TM = 1;
        onmousedown_stat = 0;
        send_btn_cmd("S");
        myTmr = setInterval(myTimer, myTmr_Interval);
      }
      /* ----------------------------------------------------------------------

      /* ---------------------------------------------------------------------- myTimer */
      function myTimer() {
        send_btn_cmd("S");
        clearInterval(myTmr);
      }
      /* ---------------------------------------------------------------------- */

      /* ---------------------------------------------------------------------- myTimer_PanTiltCtr */
      function myTimer_PanTiltCtr() {
        if (myTmr_PanTiltCtr_Send == 1) {
          send_cmd(slider_PanTilt_send_rslt);
          if (myTmr_PanTiltCtr_Start == 1) clearInterval(myTmr_PanTiltCtr);
          myTmr_PanTiltCtr_Send = 0;
        }
      }
      /* ---------------------------------------------------------------------- */

      /* ---------------------------------------------------------------------- Function to send commands to the ESP32 Cam whenever the button is clicked/touched. */
      function send_btn_cmd(cmds) {
        let btn_cmd = "B," + cmds;
        send_cmd(btn_cmd);
      }
      /* ---------------------------------------------------------------------- */
      
      /* ---------------------------------------------------------------------- Function for sending commands */
      function send_cmd(cmds) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/action?go=" + cmds, true);
        xhr.send();
      }
      /* ---------------------------------------------------------------------- */
    </script>
  
  </body>
  
</html>
)rawliteral";
/* ======================================== */
