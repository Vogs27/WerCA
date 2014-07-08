#include <SPI.h>
//Including PCD8544 library andr graph lib
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
//Including BLE libraries
#include <lib_aci.h>
#include <aci_setup.h>
#include "uart_over_ble.h"

//Put the nRF8001 setup in the RAM of the nRF8001.
#include "services.h"

// Initialize display:
// Software SPI:
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 10, 3);

//Some variables for display:
static const unsigned char logo32[] = 
{
  B00000000, B00000000, B00000001, B11100000, //                        ####    
  B00000000, B00000000, B00000011, B11000000, //                       ####     
  B00000000, B00000000, B00000011, B11000000, //                       ####     
  B00000000, B00000000, B00000011, B11000000, //                       ####     
  B00000000, B00000000, B00000111, B10000000, //                      ####      
  B00000000, B00000000, B00000111, B00000000, //                      ###       
  B00000000, B00000000, B00001111, B00000000, //                     ####       
  B00000000, B00000000, B00001111, B00000000, //                     ####       
  B00000011, B11111000, B00011110, B00000000, //       #######      ####        
  B00001111, B11111110, B00011110, B00000000, //     ###########    ####        
  B00011111, B11111110, B00111100, B00000000, //    ############   ####         
  B00111110, B00111100, B00111100, B00000000, //   #####   ####    ####         
  B01111100, B00000100, B00111100, B00000000, //  #####       #    ####         
  B01111000, B00000000, B01111000, B01000000, //  ####            ####    #     
  B11110000, B00000000, B01111000, B01000000, // ####             ####    #     
  B11110000, B00000000, B11110000, B11100000, // ####            ####    ###    
  B11110000, B00000000, B11110000, B11100000, // ####            ####    ###    
  B11110000, B00000001, B11100000, B11100000, // ####           ####     ###    
  B11110000, B00000001, B11100000, B11110000, // ####           ####     ####   
  B01111000, B00000011, B11000000, B11110000, //  ####         ####      ####   
  B01111100, B00000011, B11000000, B01111000, //  #####        ####       ####  
  B00111111, B10000011, B11000000, B01111000, //   #######     ####       ####  
  B00011111, B10000111, B10000000, B00111100, //    ######    ####         #### 
  B00001111, B10000111, B10000000, B00111100, //     #####    ####         #### 
  B00000001, B10001111, B00000000, B00011110, //        ##   ####           ####
  B00000000, B00001111, B00000000, B00000000, //             ####               
  B00000000, B00011110, B00000000, B00000000, //            ####                
  B00000000, B00011110, B00000000, B00000000, //            ####                
  B00000000, B00111100, B00000000, B00000000, //           ####                 
  B00000000, B00111100, B00000000, B00000000, //           ####                 
  B00000000, B00111100, B00000000, B00000000, //           ####                 
  B00000000, B01111000, B00000000, B00000000, //          ####                  
};

static const unsigned char phone78[] = 
{
  B11100000, // ###     
  B11110000, // ####
  B11000000, // ##
  B11100000, // ###
  B01110000, //  ###
  B00011110, //   #####
  B00001111, //     ####
};

static const unsigned char mail710[] = 
{
  B11111111, B11111111,  //################
  B11000000, B00000011,  //##            ##
  B10110000, B00001101,  //# ##        ## #
  B10001100, B00110001,  //#   ##    ##   #
  B10000001, B10000001,  //#      ##      #
  B10000000, B00000001,  //#              #
  B11111111, B11111111,  //################
};

static const unsigned char msg716[] = 
{
  B11111111, B11111111, // ################
  B11111111, B11111111, // ################
  B11111111, B11111111, // ################
  B11111111, B11111111, // ################
  B00011100, B00000000, //    ###
  B00011000, B00000000, //    ##
  B00010000, B00000000, //    #
};

static const unsigned char oth714[] = 
{
  B00000000, B00000000, //
  B00000000, B00000000, //
  B11100011, B10001110, //###   ###   ###
  B11100011, B10001110, //###   ###   ###
  B11100011, B10001110, //###   ###   ###
  B00000000, B00000000, //
  B00000000, B00000000, //
};

static const unsigned char incoming2216[] =
{
  B00011000, B00000000, //    ##           
  B00111100, B00000000, //   ####          
  B01111100, B00000000, //  #####          
  B01111110, B00000000, //  ######         
  B11111110, B00010000, // #######    #    
  B11111110, B00001000, // #######     #   
  B11111100, B00100100, // ######    #  #  
  B11111000, B10010010, // #####   #  #  # 
  B01111000, B01001001, //  ####    #  #  #
  B01111001, B00100101, //  ####  #  #  # #
  B01111000, B10010101, //  ####   #  # # #
  B01111100, B00010101, //  #####     # # #
  B00111100, B00000101, //   ####       # #
  B00111110, B00000000, //   #####         
  B00011111, B00000000, //    #####        
  B00001111, B10011000, //     #####  ##   
  B00001111, B11111100, //     ##########  
  B00000111, B11111110, //      ########## 
  B00000011, B11111111, //       ##########
  B00000001, B11111111, //        #########
  B00000000, B01111110, //          ###### 
  B00000000, B00011100, //            ###  
};

int lastRow = 0; 
int rowStartY [4] = {11, 19, 27, 35};
int sleepPin = 0;

/**
Include the services_lock.h to put the setup in the OTP memory of the nRF8001.
This would mean that the setup cannot be changed once put in.
However this removes the need to do the setup of the nRF8001 on every reset.
*/
#ifdef SERVICES_PIPE_TYPE_MAPPING_CONTENT
    static services_pipe_type_mapping_t
        services_pipe_type_mapping[NUMBER_OF_PIPES] = SERVICES_PIPE_TYPE_MAPPING_CONTENT;
#else
    #define NUMBER_OF_PIPES 0
    static services_pipe_type_mapping_t * services_pipe_type_mapping = NULL;
#endif

/* Store the setup for the nRF8001 in the flash of the AVR to save on RAM */
static hal_aci_data_t setup_msgs[NB_SETUP_MESSAGES] PROGMEM = SETUP_MESSAGES_CONTENT;

static struct aci_state_t aci_state;  //see BLE documentation

//Temporary buffers for sending ACI commands
static hal_aci_evt_t  aci_data;

//Timing change state variable
static bool timing_change_done          = false;

/*
Used to test the UART TX characteristic notification
*/
static uart_over_ble_t uart_over_ble;
static uint8_t         uart_buffer[20];
static uint8_t         uart_buffer_len = 0;
static uint8_t         dummychar = 0;

//Implementazioni variabili ELP
char ELP_data[20];
unsigned char ore;
unsigned char minuti;
char incoming_number[15];
char incoming_name[16];
unsigned char phone_battery;
unsigned char werca_battery;
//ELP elements:
// 0 = mode
// 1 = sms
// 2 = calls
// 3 = email
// 4 = oth

/* Define how assert should function in the BLE library */
void __ble_assert(const char *file, uint16_t line)
{
  while(1);
}

void setup(void)
{
    pinMode(sleepPin, OUTPUT);
  digitalWrite(sleepPin, HIGH);
  delay(500);  //il tasto va premuto per almeno 500ms (mezzo secondo) per accendere il dispositivo
  digitalWrite(sleepPin, LOW);
  display.begin();
 /**
  Point ACI data structures to the the setup data that the nRFgo studio generated for the nRF8001
  */
  if (NULL != services_pipe_type_mapping)
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = &services_pipe_type_mapping[0];
  }
  else
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = NULL;
  }
  aci_state.aci_setup_info.number_of_pipes    = NUMBER_OF_PIPES;
  aci_state.aci_setup_info.setup_msgs         = setup_msgs;
  aci_state.aci_setup_info.num_setup_msgs     = NB_SETUP_MESSAGES;
  
/*
  Tell the ACI library, the MCU to nRF8001 pin connections.
  The Active pin is optional and can be marked UNUSED
  */
  aci_state.aci_pins.board_name = BOARD_DEFAULT; //See board.h for details REDBEARLAB_SHIELD_V1_1 or BOARD_DEFAULT
  aci_state.aci_pins.reqn_pin   = 9; //SS for Nordic board, 9 for REDBEARLAB_SHIELD_V1_1
  aci_state.aci_pins.rdyn_pin   = 8; //3 for Nordic board, 8 for REDBEARLAB_SHIELD_V1_1
  aci_state.aci_pins.mosi_pin   = MOSI;
  aci_state.aci_pins.miso_pin   = MISO;
  aci_state.aci_pins.sck_pin    = SCK;

  aci_state.aci_pins.spi_clock_divider      = SPI_CLOCK_DIV16;  //SPI_CLOCK_DIV8  = 2MHz SPI speed (DOESN'T WORK)
                                                                //SPI_CLOCK_DIV16 = 1MHz SPI speed 
  aci_state.aci_pins.reset_pin              = 4; //4 for Nordic board, UNUSED for REDBEARLAB_SHIELD_V1_1
  aci_state.aci_pins.active_pin             = UNUSED;
  aci_state.aci_pins.optional_chip_sel_pin  = UNUSED;

  aci_state.aci_pins.interface_is_interrupt = false; //Interrupts still not available in Chipkit
  aci_state.aci_pins.interrupt_number       = 1;

  lib_aci_init(&aci_state, false);
}

void uart_over_ble_init(void)
{
  uart_over_ble.uart_rts_local = true;
}

bool uart_tx(uint8_t *buffer, uint8_t buffer_len)
{
  bool status = false;

  if (lib_aci_is_pipe_available(&aci_state, PIPE_UART_OVER_BTLE_UART_TX_TX) &&
      (aci_state.data_credit_available >= 1))
  {
    status = lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, buffer, buffer_len);
    if (status)
    {
      aci_state.data_credit_available--;
    }
  }

  return status;
}

bool uart_process_control_point_rx(uint8_t *byte, uint8_t length)
{
  bool status = false;
  aci_ll_conn_params_t *conn_params;

  if (lib_aci_is_pipe_available(&aci_state, PIPE_UART_OVER_BTLE_UART_CONTROL_POINT_TX) )
  {
    switch(*byte)
    {
      /*
      Queues a ACI Disconnect to the nRF8001 when this packet is received.
      May cause some of the UART packets being sent to be dropped
      */
      case UART_OVER_BLE_DISCONNECT:
        /*
        Parameters:
        None
        */
        lib_aci_disconnect(&aci_state, ACI_REASON_TERMINATE);
        status = true;
        break;


      /*
      Queues an ACI Change Timing to the nRF8001
      */
      case UART_OVER_BLE_LINK_TIMING_REQ:
        /*
        Parameters:
        Connection interval min: 2 bytes
        Connection interval max: 2 bytes
        Slave latency:           2 bytes
        Timeout:                 2 bytes
        Same format as Peripheral Preferred Connection Parameters (See nRFgo studio -> nRF8001 Configuration -> GAP Settings
        Refer to the ACI Change Timing Request in the nRF8001 Product Specifications
        */
        conn_params = (aci_ll_conn_params_t *)(byte+1);
        lib_aci_change_timing( conn_params->min_conn_interval,
                                conn_params->max_conn_interval,
                                conn_params->slave_latency,
                                conn_params->timeout_mult);
        status = true;
        break;

      /*
      Clears the RTS of the UART over BLE
      */
      case UART_OVER_BLE_TRANSMIT_STOP:
        /*
        Parameters:
        None
        */
        uart_over_ble.uart_rts_local = false;
        status = true;
        break;


      /*
      Set the RTS of the UART over BLE
      */
      case UART_OVER_BLE_TRANSMIT_OK:
        /*
        Parameters:
        None
        */
        uart_over_ble.uart_rts_local = true;
        status = true;
        break;
    }
  }

  return status;
}

//HERE STARTS THE REAL USEFULL CODE
void aci_loop()
{
  static bool setup_required = false;

  // We enter the if statement only when there is a ACI event available to be processed
  if (lib_aci_event_get(&aci_state, &aci_data))
  {
    aci_evt_t * aci_evt;
    aci_evt = &aci_data.evt;
    switch(aci_evt->evt_opcode)
    {
      /**
      As soon as you reset the nRF8001 you will get an ACI Device Started Event
      */
      case ACI_EVT_DEVICE_STARTED:
      {
        aci_state.data_credit_total = aci_evt->params.device_started.credit_available;
        switch(aci_evt->params.device_started.device_mode)
        {
          case ACI_DEVICE_SETUP:
            /**
            When the device is in the setup mode
            */
            setup_required = true;
            break;

          case ACI_DEVICE_STANDBY:
            //Looking for a phone by sending radio advertisements
            //When a Phone connects to us we will get an ACI_EVT_CONNECTED event from the nRF8001
            if (aci_evt->params.device_started.hw_error)
            {
              delay(20); //Handle the HW error event correctly.
            }
            else
            {
              lib_aci_connect(0/* in seconds : 0 means forever */, 0x0050 /* advertising interval 50ms*/);
display.clearDisplay();
  display.setContrast(25);
  display.setTextSize(1);              
  display.setTextColor(BLACK);
  display.setCursor(9, 0);
  display.println("Waiting  for");
  display.setCursor(12, 8);
  display.println("connection");
  display.drawBitmap(20, 26, logo32, 32, 32, BLACK);
  display.display();    
}
            break;
        }
      }
      break; //ACI Device Started Event

      case ACI_EVT_CMD_RSP:
        //If an ACI command response event comes with an error -> stop
        if (ACI_STATUS_SUCCESS != aci_evt->params.cmd_rsp.cmd_status)
        {
          //ACI ReadDynamicData and ACI WriteDynamicData will have status codes of
          //TRANSACTION_CONTINUE and TRANSACTION_COMPLETE
          //all other ACI commands will have status code of ACI_STATUS_SCUCCESS for a successful command
        }
        if (ACI_CMD_GET_DEVICE_VERSION == aci_evt->params.cmd_rsp.cmd_opcode)
        {
          //Store the version and configuration information of the nRF8001 in the Hardware Revision String Characteristic
          lib_aci_set_local_data(&aci_state, PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET,
            (uint8_t *)&(aci_evt->params.cmd_rsp.params.get_device_version), sizeof(aci_evt_cmd_rsp_params_get_device_version_t));
        }
        break;

      case ACI_EVT_CONNECTED:
          display.clearDisplay();
  display.setCursor(12, 0);
  display.println("Connection");
  display.setCursor(11, 8);
  display.println("successful!");
  display.display();
  delay(1500);
        uart_over_ble_init();
        timing_change_done              = false;
        aci_state.data_credit_available = aci_state.data_credit_total;

        /*
        Get the device version of the nRF8001 and store it in the Hardware Revision String
        */
        lib_aci_device_version();
        break;

      case ACI_EVT_PIPE_STATUS:
        if (lib_aci_is_pipe_available(&aci_state, PIPE_UART_OVER_BTLE_UART_TX_TX) && (false == timing_change_done))
        {
          lib_aci_change_timing_GAP_PPCP(); // change the timing on the link as specified in the nRFgo studio -> nRF8001 conf. -> GAP.
                                            // Used to increase or decrease bandwidth
          timing_change_done = true;
        }
        break;
        
      case ACI_EVT_TIMING:
        lib_aci_set_local_data(&aci_state,
                                PIPE_UART_OVER_BTLE_UART_LINK_TIMING_CURRENT_SET,
                                (uint8_t *)&(aci_evt->params.timing.conn_rf_interval), /* Byte aligned */
                                PIPE_UART_OVER_BTLE_UART_LINK_TIMING_CURRENT_SET_MAX_SIZE);
        break;

      case ACI_EVT_DISCONNECTED:
        lib_aci_connect(0/* in seconds  : 0 means forever */, 0x0050 /* advertising interval 50ms*/);
display.clearDisplay();
  display.setContrast(25);
  display.setTextSize(1);              
  display.setTextColor(BLACK);
  display.setCursor(9, 0);
  display.println("Waiting  for");
  display.setCursor(12, 8);
  display.println("connection");
  display.drawBitmap(20, 26, logo32, 32, 32, BLACK);
  display.display();
        break;

      case ACI_EVT_DATA_RECEIVED:
  
        if (PIPE_UART_OVER_BTLE_UART_RX_RX == aci_evt->params.data_received.rx_data.pipe_number)
          {
            for(int i=0; i<aci_evt->len - 2; i++)
            {
              ELP_data[i] = aci_evt->params.data_received.rx_data.aci_data[i]; //CREA BUFFER VSP
            }            
            uart_buffer_len = aci_evt->len - 2;
            if (lib_aci_is_pipe_available(&aci_state, PIPE_UART_OVER_BTLE_UART_TX_TX))
            {
              /*Do this to test the loopback otherwise comment it out*/
              /*
              if (!uart_tx(&uart_buffer[0], aci_evt->len - 2))
              {
                Serial.println(F("UART loopback failed"));
              }
              else
              {
                Serial.println(F("UART loopback OK"));
              }
              */
            }
        }
        if (PIPE_UART_OVER_BTLE_UART_CONTROL_POINT_RX == aci_evt->params.data_received.rx_data.pipe_number)
        {
          uart_process_control_point_rx(&aci_evt->params.data_received.rx_data.aci_data[0], aci_evt->len - 2); //Subtract for Opcode and Pipe number
        }
        break;

      case ACI_EVT_DATA_CREDIT:
        aci_state.data_credit_available = aci_state.data_credit_available + aci_evt->params.data_credit.credit;
        break;

      case ACI_EVT_PIPE_ERROR:
        //See the appendix in the nRF8001 Product Specication for details on the error codes
display.clearDisplay();
display.print("ERROR. RESTART DEVICE!");
        //Increment the credit available as the data packet was not sent.
        //The pipe error also represents the Attribute protocol Error Response sent from the peer and that should not be counted
        //for the credit.
        if (ACI_STATUS_ERROR_PEER_ATT_ERROR != aci_evt->params.pipe_error.error_code)
        {
          aci_state.data_credit_available++;
        }
        break;

      case ACI_EVT_HW_ERROR:
        display.println("HARDWARE ERROR, CALL SUPPORT");
        display.println(aci_evt->params.hw_error.line_num, DEC);

        for(uint8_t counter = 0; counter <= (aci_evt->len - 3); counter++)
        {
        }
        lib_aci_connect(0/* in seconds, 0 means forever */, 0x0050 /* advertising interval 50ms*/);
  display.clearDisplay();
  display.setContrast(25);
  display.setTextSize(1);              
  display.setTextColor(BLACK);
  display.setCursor(9, 0);
  display.println("Waiting  for");
  display.setCursor(12, 8);
  display.println("connection");
  display.drawBitmap(20, 26, logo32, 32, 32, BLACK);
  display.display();
        break;

    }
  }
  else
  {
    //Serial.println(F("No ACI Events available"));
    // No event in the ACI Event queue and if there is no event in the ACI command queue the arduino can go to sleep
    // Arduino can go to sleep now
    // Wakeup from sleep from the RDYN line
  }

  /* setup_required is set to true when the device starts up and enters setup mode.
   * It indicates that do_aci_setup() should be called. The flag should be cleared if
   * do_aci_setup() returns ACI_STATUS_TRANSACTION_COMPLETE.
   */
  if(setup_required)
  {
    if (SETUP_SUCCESS == do_aci_setup(&aci_state))
    {
      setup_required = false;
    }
  }
}

bool stringComplete = false;  // whether the string is complete
uint8_t stringIndex = 0;      //Initialize the index to store incoming chars

void loop() {

  //Process any ACI commands or events
  aci_loop();
  
         
 /*
  if (stringComplete) 
  {
    Serial.print(F("Sending: "));
    Serial.println((char *)&uart_buffer[0]);

    uart_buffer_len = stringIndex + 1;

    if (!lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, uart_buffer, uart_buffer_len))
    {
      Serial.println(F("Serial input dropped"));
    }

    // clear the uart_buffer:
    for (stringIndex = 0; stringIndex < 20; stringIndex++)
    {
      uart_buffer[stringIndex] = ' ';
    }

    // reset the flag and the index in order to receive more data
    stringIndex    = 0;
    stringComplete = false;
  }
  //For ChipKit you have to call the function that reads from Serial
  #if defined (__PIC32MX__)
    if (Serial.available())
    {
      serialEvent();
    }
  #endif
  */
switch(ELP_data[0]){
  case 'B':
    display.drawBitmap(0, 11, incoming2216, 16, 22, BLACK);
    display.setCursor(0, 35);
    display.println("Incoming call");
/* if(VSP[4]==0){    SOSTITUIRE VSP CON EQUIVALENTE IN ELP
      display.print("Unknown");
    }
    else{
      display.print(VSP[4]);
    } */
    break;
  case 'C':
    digitalWrite(sleepPin, HIGH);
  default: //l'ordine di chiamata delle seguenti funioni determina la loro priorità di visualizzazione sul display
    messages(ELP_data[1]);
    calls(ELP_data[2]);
    mail(ELP_data[3]);
    oth(ELP_data[4]);
    lastRow = 0;
    break;
  }
  for(int i = 0; i <= 6; i++){
    ELP_data[i] = 0;
  }
  delay(100);
}

void messages(int numbmsg){
  if (numbmsg != 0){
    display.drawBitmap(0, rowStartY[lastRow], msg716, 16, 7, BLACK);
    display.setCursor(18, rowStartY[lastRow]);
    display.print(numbmsg);
    if(numbmsg==1){
      display.print(" message");
    }
    else {
      display.print(" messages");
    }
    display.display();
    lastRow = lastRow ++;
  }
}

void calls(int numbcall){
  if(numbcall != 0){
    display.drawBitmap(0, rowStartY[lastRow], phone78, 8, 7, BLACK);
    display.setCursor(8, rowStartY[lastRow]);
    display.print(numbcall);
    if(numbcall==1){
      display.print(" call");
    }
    else {
      display.print(" calls");
    }
    display.display();
    lastRow = lastRow ++;
  }
}

void mail(int numbmail){
  if(numbmail != 0){
    display.drawBitmap(0, rowStartY[lastRow], mail710, 14, 7, BLACK);
    display.setCursor(12, rowStartY[lastRow]);
    display.print(numbmail);
    display.print(" mail");
    display.display();
    lastRow = lastRow ++;
  }
}

void oth(int numboth){
  if(numboth != 0){
    display.drawBitmap(0, rowStartY[lastRow], oth714, 15, 7, BLACK);
    display.setCursor(17, rowStartY[lastRow]);
    display.print(numboth);
    if(numboth==1){
      display.print(" other");
    }
    else {
      display.print(" others");
    }
    display.display();
    lastRow = lastRow ++;
  }
}

/*
 COMMENT ONLY FOR ARDUINO
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 Serial Event is NOT compatible with Leonardo, Micro, Esplora

void serialEvent() {

  while(Serial.available() > 0){
    // get the new byte:
    dummychar = (uint8_t)Serial.read();
    if(!stringComplete)
    {
      if (dummychar == '\n')
      {
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it
        stringIndex--;
        stringComplete = true;
      }
      else
      {
        if(stringIndex > 19)
        {
          Serial.println("Serial input truncated");
          stringIndex--;
          stringComplete = true;
        }
        else
        {
          // add it to the uart_buffer
          uart_buffer[stringIndex] = dummychar;
          stringIndex++;
        }
      }
    }
  }
}
*/
