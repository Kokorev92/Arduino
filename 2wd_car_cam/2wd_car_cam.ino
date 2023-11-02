
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 03 ESP32 CAM RC Car Robot with Pan and Tilt Mount SM (Station Mode)
/*
 * Reference :
 * - ESP32-CAM Pan and Tilt Video Streaming Web Server (2 Axis) : https://randomnerdtutorials.com/esp32-cam-pan-and-tilt-2-axis/
 * - ESP32Servo (Author: Kevin Harrington,John K. Bennett) : - https://www.arduino.cc/reference/en/libraries/esp32servo/
 *                                                           - https://github.com/madhephaestus/ESP32Servo
 * - Timer on ESP32 : https://openlabpro.com/guide/timer-on-esp32/
 * - HTML DOM TouchEvent : https://www.w3schools.com/jsref/obj_touchevent.asp
 * - HTML DOM MouseEvent : https://www.w3schools.com/jsref/obj_mouseevent.asp
 * - Add Space Between Buttons in HTML : https://www.delftstack.com/howto/html/html-space-between-buttons/
 * - CSS Buttons : https://www.w3schools.com/css/css3_buttons.asp
 * - How TO - Range Sliders : https://www.w3schools.com/howto/howto_js_rangeslider.asp
 * - CameraCarWithPanTiltControl by un0038998 : https://github.com/un0038998/CameraCarWithPanTiltControl
 * - ESP32-CAM Remote Controlled Car Robot Web Server : https://randomnerdtutorials.com/esp32-cam-car-robot-web-server/
 * - ESP32-CAM AI-Thinker Pinout Guide: GPIOs Usage Explained : https://randomnerdtutorials.com/esp32-cam-ai-thinker-pinout/
 * - ESP32-CAM: high resolution pinout and specs : https://www.mischianti.org/2021/09/02/esp32-cam-high-resolution-pinout-and-specs/
 * - HTML vs Body: How to Set Width and Height for Full Page Size : https://www.freecodecamp.org/news/html-page-width-height/
 * - ESP32 PWM with Arduino IDE (Analog Output) : https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
 * - ESP32 PWM Frequency selection : https://rntlab.com/question/esp32-pwm-frequency-selection/
 * - arduino-esp32/cores/esp32/esp32-hal-ledc.c : https://github.com/espressif/arduino-esp32/blob/2fd39b1aff1c1f2be60bbd9b5fbd9c88638b0fcc/cores/esp32/esp32-hal-ledc.c
 * - ESP32 PWM Tutorial & Examples (AnalogWrite) – Arduino : https://deepbluembedded.com/esp32-pwm-tutorial-examples-analogwrite-arduino/
 * 
 * and from various other sources.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                            IMPORTANT INFORMATION                                                                                //
//                                                                            ---------------------                                                                                //
//                                                                                                                                                                                  //
// > This project uses ESP32-CAM, L298N DC Motor Driver Module, DC Step Down Module (2 pieces), Servo (2 pieces) and DC Motor (4 pieces).                                           //
//   To power the modules and devices above, I recommend using a 12V Main Power Supply with 2A or more amperage.                                                                    //
//   12V Main Power Supply to power the L298N DC Motor Driver Module + DC Motor and DC Step Down Module,                                                                            //
//   while to power the ESP32-CAM and Servo using the DC Step Down Module whose output must be set to 5V.                                                                           //
//   For more information about this project (including other supporting components), please take a look at the installation image I shared with this code file.                    //
//   Look at the installation image carefully, because I wrote a lot of important information there.                                                                                //
//                                                                                                                                                                                  //
// > I suggest that every time you upload the program code to the ESP32-CAM, make sure that the switch that connects the Power Supply to the L298N DC Motor Driver Module is off    //
//   (OFF/0). Then if the process of uploading the program code to the ESP32-CAM is complete, you can change the switch to on (ON/1).                                               //
//   I suggest this because from what I experienced, if the switch is on when uploading the program code to the ESP32-CAM, the DC Motor will spin.                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// I realized that the HTML code in this project could have been better or simpler. But because of my limited knowledge on WEB programming,                                         //
// then that code is the best code I can make. If you can make it better or simpler, I hope you can share it with me or with the video viewers of this project.                     //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sorry if my English is confusing, I use the help of an online translator because my English is not good.                                                                         //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ======================================== Including the libraries. */
#include "esp_camera.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <WiFi.h>
#include "esp_http_server.h"
#include <ESP32Servo.h>
#include "html_page.h"
/* ======================================== */

/* ======================================== Select camera model. */
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WITHOUT_PSRAM
//#define CAMERA_MODEL_M5STACK_WITHOUT_PSRAM
#define CAMERA_MODEL_AI_THINKER
/* ======================================== */

/* ======================================== GPIO of camera models. */
#if defined(CAMERA_MODEL_WROVER_KIT)
  #define PWDN_GPIO_NUM    -1
  #define RESET_GPIO_NUM   -1
  #define XCLK_GPIO_NUM    21
  #define SIOD_GPIO_NUM    26
  #define SIOC_GPIO_NUM    27
  
  #define Y9_GPIO_NUM      35
  #define Y8_GPIO_NUM      34
  #define Y7_GPIO_NUM      39
  #define Y6_GPIO_NUM      36
  #define Y5_GPIO_NUM      19
  #define Y4_GPIO_NUM      18
  #define Y3_GPIO_NUM       5
  #define Y2_GPIO_NUM       4
  #define VSYNC_GPIO_NUM   25
  #define HREF_GPIO_NUM    23
  #define PCLK_GPIO_NUM    22

#elif defined(CAMERA_MODEL_M5STACK_PSRAM)
  #define PWDN_GPIO_NUM     -1
  #define RESET_GPIO_NUM    15
  #define XCLK_GPIO_NUM     27
  #define SIOD_GPIO_NUM     25
  #define SIOC_GPIO_NUM     23
  
  #define Y9_GPIO_NUM       19
  #define Y8_GPIO_NUM       36
  #define Y7_GPIO_NUM       18
  #define Y6_GPIO_NUM       39
  #define Y5_GPIO_NUM        5
  #define Y4_GPIO_NUM       34
  #define Y3_GPIO_NUM       35
  #define Y2_GPIO_NUM       32
  #define VSYNC_GPIO_NUM    22
  #define HREF_GPIO_NUM     26
  #define PCLK_GPIO_NUM     21

#elif defined(CAMERA_MODEL_M5STACK_PSRAM_B)
  #define PWDN_GPIO_NUM     -1
  #define RESET_GPIO_NUM    15
  #define XCLK_GPIO_NUM     27
  #define SIOD_GPIO_NUM     22
  #define SIOC_GPIO_NUM     23
  
  #define Y9_GPIO_NUM       19
  #define Y8_GPIO_NUM       36
  #define Y7_GPIO_NUM       18
  #define Y6_GPIO_NUM       39
  #define Y5_GPIO_NUM        5
  #define Y4_GPIO_NUM       34
  #define Y3_GPIO_NUM       35
  #define Y2_GPIO_NUM       32
  #define VSYNC_GPIO_NUM    25
  #define HREF_GPIO_NUM     26
  #define PCLK_GPIO_NUM     21

#elif defined(CAMERA_MODEL_M5STACK_WITHOUT_PSRAM)
  #define PWDN_GPIO_NUM     -1
  #define RESET_GPIO_NUM    15
  #define XCLK_GPIO_NUM     27
  #define SIOD_GPIO_NUM     25
  #define SIOC_GPIO_NUM     23
  
  #define Y9_GPIO_NUM       19
  #define Y8_GPIO_NUM       36
  #define Y7_GPIO_NUM       18
  #define Y6_GPIO_NUM       39
  #define Y5_GPIO_NUM        5
  #define Y4_GPIO_NUM       34
  #define Y3_GPIO_NUM       35
  #define Y2_GPIO_NUM       17
  #define VSYNC_GPIO_NUM    22
  #define HREF_GPIO_NUM     26
  #define PCLK_GPIO_NUM     21

#elif defined(CAMERA_MODEL_AI_THINKER)
  #define PWDN_GPIO_NUM     32
  #define RESET_GPIO_NUM    -1
  #define XCLK_GPIO_NUM      0
  #define SIOD_GPIO_NUM     26
  #define SIOC_GPIO_NUM     27
  
  #define Y9_GPIO_NUM       35
  #define Y8_GPIO_NUM       34
  #define Y7_GPIO_NUM       39
  #define Y6_GPIO_NUM       36
  #define Y5_GPIO_NUM       21
  #define Y4_GPIO_NUM       19
  #define Y3_GPIO_NUM       18
  #define Y2_GPIO_NUM        5
  #define VSYNC_GPIO_NUM    25
  #define HREF_GPIO_NUM     23
  #define PCLK_GPIO_NUM     22
#else
  #error "Camera model not selected"
#endif
/* ======================================== */

/* ======================================== GPIO for controlling dc motors. */
// For more details, please see the installation picture.
#define Motor_R_Dir_Pin   2
#define Motor_R_PWM_Pin   3
#define Motor_L_Dir_Pin   13
#define Motor_L_PWM_Pin   12
/* ======================================== */

/* ======================================== SERVOs GPIO */
#define servo_LeftRight_Pin   14
#define servo_UpDown_Pin      15
/* ======================================== */

// LEDs GPIO
#define LED_OnBoard 4

/* ======================================== Variables declaration */
// setting PWM properties for LED
const int PWM_LED_Freq = 5000;
const int PWM_LED_Channel = 6;
const int PWM_LED_resolution = 8;

// setting PWM properties for DC Motor
const int PWM_Mtr_Freq = 5000;
const int PWM_Mtr_Resolution = 8;
const int PWM_Channel_Mtr_R = 4;
const int PWM_Channel_Mtr_L = 5;

// Variable for DC Motor/Motor Drive PWM value
int PWM_Motor_DC = 0;

// Variable for servo position
int servo_LeftRight_Pos = 75;
int servo_UpDown_Pos = 75;
/* ======================================== */

/* ======================================== Initialize servos */
/*
 * Maybe in this section you are a little confused, why did I initialize 4 servos, even though in this project only 2 servos are used. Below is a brief explanation.
 * 
 * The ESP32 has 4 hardware timers (please correct me if I'm wrong). If only initialize 2 servos, then automatically based on servo library, 
 * then servo_1 will use timer_0 (channel_0) and servo_2 will use timer_1 (channel_1). 
 * That would be a problem because timer_0 (channel_0) and timer_1 (channel_1) are already in use by the camera.
 * 
 * Therefore, initialization of 4 servos is used, so that the 2 servos that are actually used will shift to timer_2 (channel_2) and timer_3 (channel_3). Below is the simple flow:
 * 
 * servo_Dummy_1    --> timer_0 or channel_0
 * servo_Dummy_2    --> timer_1 or channel_1
 * servo_LeftRight  --> timer_2 or channel_2
 * servo_UpDown     --> timer_3 or channel_3
 * 
 * Based on the flow above, the initialization of servo_Dummy_1 and servo_Dummy_2 is only used to shift the timer, 
 * so the 2 servos used in this project will use timer_2 (channel_2) and timer_3 (channel_3). 
 * servo_Dummy_1 and servo_Dummy_2 are not actually used, because timer_0 (channel_0) and timer_1 (channel_1) are already used by the camera.
 */
Servo servo_Dummy_1;
Servo servo_Dummy_2;
Servo servo_LeftRight;
Servo servo_UpDown;
/* ======================================== */

/* ======================================== Access Point Declaration and Configuration. */
const char* ssid = "esp_camera";  //--> access point name
const char* password = "12345678"; //--> access point password

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
/* ======================================== */


/* ======================================== */
#define PART_BOUNDARY "123456789000000000000987654321"
static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";
/* ======================================== */

/* ======================================== Empty handle to esp_http_server */
httpd_handle_t index_httpd = NULL;
httpd_handle_t stream_httpd = NULL;
/* ======================================== */


/* ________________________________________________________________________________ Index handler function to be called during GET or uri request */
static esp_err_t index_handler(httpd_req_t *req){
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)INDEX_HTML, strlen(INDEX_HTML));
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ stream handler function to be called during GET or uri request. */
static esp_err_t stream_handler(httpd_req_t *req){
  camera_fb_t * fb = NULL;
  esp_err_t res = ESP_OK;
  size_t _jpg_buf_len = 0;
  uint8_t * _jpg_buf = NULL;
  char * part_buf[64];

  res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
  if(res != ESP_OK){
    return res;
  }

  /* ---------------------------------------- Loop to show streaming video from ESP32 Cam camera. */
  while(true){
    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed (stream_handler)");
      res = ESP_FAIL;
    } else {
      if(fb->width > 400){
        if(fb->format != PIXFORMAT_JPEG){
          bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
          esp_camera_fb_return(fb);
          fb = NULL;
          if(!jpeg_converted){
            Serial.println("JPEG compression failed");
            res = ESP_FAIL;
          }
        } else {
          _jpg_buf_len = fb->len;
          _jpg_buf = fb->buf;
        }
      }
    }
    if(res == ESP_OK){
      size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
      res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
    }
    if(res == ESP_OK){
      res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
    }
    if(res == ESP_OK){
      res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
    }
    if(fb){
      esp_camera_fb_return(fb);
      fb = NULL;
      _jpg_buf = NULL;
    } else if(_jpg_buf){
      free(_jpg_buf);
      _jpg_buf = NULL;
    }
    if(res != ESP_OK){
      break;
    }
  }
  /* ---------------------------------------- */
  return res;
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ cmd handler function to be called during GET or uri request. */
static esp_err_t cmd_handler(httpd_req_t *req){
  char*  buf;
  size_t buf_len;
  char variable[32] = {0,};
   
  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1) {
    buf = (char*)malloc(buf_len);
    if(!buf){
      httpd_resp_send_500(req);
      return ESP_FAIL;
    }
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
      if (httpd_query_key_value(buf, "go", variable, sizeof(variable)) == ESP_OK) {
      } else {
        free(buf);
        httpd_resp_send_404(req);
        return ESP_FAIL;
      }
    } else {
      free(buf);
      httpd_resp_send_404(req);
      return ESP_FAIL;
    }
    free(buf);
  } else {
    httpd_resp_send_404(req);
    return ESP_FAIL;
  }
 
  int res = 0;

  Serial.println();
  Serial.print("Incoming command : ");
  Serial.println(variable);
  String getData = String(variable);
  String resultData = getValue(getData, ',', 0);

  /* ---------------------------------------- Controlling the LEDs on the ESP32-CAM Board with PWM. */
  // Example :
  // Incoming command = S,10
  // S = Slider
  // 10 = slider value
  // I set the slider value range from 0 to 10.
  // Then the slider value is changed from 0 - 10 or vice versa to 0 - 255 or vice versa.
  if (resultData == "SL") {
    resultData = getValue(getData, ',', 1);
    int pwm = map(resultData.toInt(), 0, 20, 0, 255);
    ledcWrite(PWM_LED_Channel, pwm);
    Serial.print("PWM LED On Board : ");
    Serial.println(pwm);
  }
  /* ---------------------------------------- */

  /* ---------------------------------------- Controlling the servos on the Pan and Tilt Camera Mount. */
  if (resultData == "SP") {
    resultData = getValue(getData, ',', 1);
    servo_LeftRight_Pos = resultData.toInt();
    servo_LeftRight.write(servo_LeftRight_Pos);
    Serial.print("Pan Servo Value : ");
    Serial.println(servo_LeftRight_Pos);
  }

  if (resultData == "ST") {
    resultData = getValue(getData, ',', 1);
    servo_UpDown_Pos = resultData.toInt();
    servo_UpDown.write(servo_UpDown_Pos);
    Serial.print("Tilt Servo Value : ");
    Serial.println(servo_UpDown_Pos);
  }
  /* ---------------------------------------- */

  /* ---------------------------------------- Controlling the speed of dc motors with PWM. */
  if (resultData == "SS") {
    resultData = getValue(getData, ',', 1);
    int pwm = map(resultData.toInt(), 0, 10, 0, 255);
    PWM_Motor_DC = pwm;
    Serial.print("PWM Motor DC Value : ");
    Serial.println(PWM_Motor_DC);
  }
  /* ---------------------------------------- */

  /* ---------------------------------------- Processes and executes commands received from the index page/web server. */
  // Example :
  // Incoming Command = B,F
  // B = Button
  // F = Command for the car to move forward.
  
  if (resultData == "B") {
    resultData = getValue(getData, ',', 1);

    if (resultData == "F") {
      Move_Forward(PWM_Motor_DC);
    }

    if (resultData == "B") {
      Move_Backward(PWM_Motor_DC);
    }

    if (resultData == "R") {
      Move_Right(PWM_Motor_DC);
    }

    if (resultData == "L") {
      Move_Left(PWM_Motor_DC);
    }

    if (resultData == "S") {
      Move_Stop();
    }

    Serial.print("Button : ");
    Serial.println(resultData);
  }
  /* ---------------------------------------- */
  
  if(res){
    return httpd_resp_send_500(req);
  }
 
  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  return httpd_resp_send(req, NULL, 0);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ Subroutine for starting the web server / startCameraServer. */
void startCameraWebServer(){
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;

  httpd_uri_t index_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = index_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t cmd_uri = {
    .uri       = "/action",
    .method    = HTTP_GET,
    .handler   = cmd_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t stream_uri = {
    .uri       = "/stream",
    .method    = HTTP_GET,
    .handler   = stream_handler,
    .user_ctx  = NULL
  };
    
  if (httpd_start(&index_httpd, &config) == ESP_OK) {
      httpd_register_uri_handler(index_httpd, &index_uri);
      httpd_register_uri_handler(index_httpd, &cmd_uri);
  }

  config.server_port += 1;
  config.ctrl_port += 1;  
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
      httpd_register_uri_handler(stream_httpd, &stream_uri);
  }

  Serial.println();
  Serial.println("Camera Server started successfully");
  Serial.print("Camera Stream Ready! Go to: http://");
  Serial.println(local_ip);
  Serial.println();
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ String function to process the data command */
// I got this from : https://www.electroniclinic.com/reyax-lora-based-multiple-sensors-monitoring-using-arduino/
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ The subroutine for the robot car is moving forward. */
void Move_Forward(int pwm_val) {
  int pwm_result = 255 - pwm_val;
  digitalWrite(Motor_R_Dir_Pin, HIGH);
  ledcWrite(PWM_Channel_Mtr_R, pwm_result);
  digitalWrite(Motor_L_Dir_Pin, HIGH);
  ledcWrite(PWM_Channel_Mtr_L, pwm_result);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ The subroutine for the robot car is moving backwards. */
void Move_Backward(int pwm_val) {
  digitalWrite(Motor_R_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_R, pwm_val);
  digitalWrite(Motor_L_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_L, pwm_val);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ The subroutine for the robot car turns right (rotates right). */
void Move_Right(int pwm_val) {
  int pwm_result = 255 - pwm_val;
  digitalWrite(Motor_R_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_R, pwm_val);
  digitalWrite(Motor_L_Dir_Pin, HIGH);
  ledcWrite(PWM_Channel_Mtr_L, pwm_result);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ The subroutine for the robot car turns left (rotates left). */
void Move_Left(int pwm_val) {
  int pwm_result = 255 - pwm_val;
  digitalWrite(Motor_R_Dir_Pin, HIGH);
  ledcWrite(PWM_Channel_Mtr_R, pwm_result);
  digitalWrite(Motor_L_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_L, pwm_val);
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ */
void Move_Stop() {
  digitalWrite(Motor_R_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_R, 0);
  digitalWrite(Motor_L_Dir_Pin, LOW);
  ledcWrite(PWM_Channel_Mtr_L, 0);
}
/* ________________________________________________________________________________ The subroutine for the robot car stops (stops moving). */

/* ________________________________________________________________________________ VOID SETUP() */
void setup() {
  // put your setup code here, to run once:

  // Disable brownout detector.
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  /* ---------------------------------------- Init serial communication speed (baud rate). */
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  Serial.println();
  /* ---------------------------------------- */

  pinMode(LED_OnBoard, OUTPUT);

  /* ---------------------------------------- Setting Servos */
  Serial.println();
  Serial.println("------------");
  Serial.println("Start setting Servos...");
  servo_LeftRight.setPeriodHertz(50); //--> // Standard 50hz servo
  servo_UpDown.setPeriodHertz(50);    //--> // Standard 50hz servo
  servo_Dummy_1.attach(14, 1000, 2000);
  servo_Dummy_2.attach(15, 1000, 2000);
  servo_LeftRight.attach(servo_LeftRight_Pin, 1000, 2000);
  servo_UpDown.attach(servo_UpDown_Pin, 1000, 2000);
  
  servo_LeftRight.write(servo_LeftRight_Pos);
  servo_UpDown.write(servo_UpDown_Pos);
  Serial.println("Setting up the servos was successful.");
  Serial.println("------------");
  /* ---------------------------------------- */
  
  delay(500);

  /* ---------------------------------------- The pin to set the direction of rotation of the motor is set as OUTPUT. */
  pinMode(Motor_R_Dir_Pin, OUTPUT);
  pinMode(Motor_L_Dir_Pin, OUTPUT);
  /* ---------------------------------------- */

  /* ---------------------------------------- Setting PWM. */
  // Set the PWM for the On Board LED.
  Serial.println();
  Serial.println("------------");
  Serial.println("Start setting PWM for LED On Board...");
  ledcAttachPin(LED_OnBoard, PWM_LED_Channel);
  ledcSetup(PWM_LED_Channel, PWM_LED_Freq, PWM_LED_resolution);
  Serial.println("Setting the PWM for LED On Board was successful.");
  Serial.println();

  // Set the PWM for DC Motor / Motor Drive.
  Serial.println("Start setting PWM for DC Motor...");
  ledcAttachPin(Motor_R_PWM_Pin, PWM_Channel_Mtr_R);
  ledcAttachPin(Motor_L_PWM_Pin, PWM_Channel_Mtr_L);
  ledcSetup(PWM_Channel_Mtr_R, PWM_Mtr_Freq, PWM_Mtr_Resolution);
  ledcSetup(PWM_Channel_Mtr_L, PWM_Mtr_Freq, PWM_Mtr_Resolution);
  Serial.println("Setting the PWM for the DC Motor was successful.");
  Serial.println("------------");
  /* ---------------------------------------- */

  delay(500);

  /* ---------------------------------------- Camera configuration. */
  Serial.println();
  Serial.println("------------");
  Serial.println("Start configuring and initializing the camera...");
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()){
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    ESP.restart();
  }
  
  Serial.println("Configure and initialize the camera successfully.");
  Serial.println("------------");
  Serial.println();
  /* ---------------------------------------- */

  /* ---------------------------------------- Start Access Points Mode. */
Serial.println();
Serial.println("------------");
Serial.println("Start Access Point Mode...");
WiFi.softAP(ssid, password);
WiFi.softAPConfig(local_ip, gateway, subnet);
Serial.println("Access Point Mode Started Successfully.");
Serial.println("------------");
Serial.println();
/* ---------------------------------------- */

  // Start camera web server
  startCameraWebServer(); 
}
/* ________________________________________________________________________________ */

/* ________________________________________________________________________________ VOID LOOP */
void loop() {
  // put your main code here, to run repeatedly:
  
}
/* ________________________________________________________________________________ */
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
