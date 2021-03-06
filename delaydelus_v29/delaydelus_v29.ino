
#include <S25FLx_FIFO.h>

#include <Bounce2.h>
#define BOUNCE_LOCK-OUT


// smd v4 really really

#define cs  10  
#define cs2  10  

#define shift_pin  28   
#define mode_pin  22
#define left_button_pin  3   
#define right_button_pin  4   

#define left_select_pin  0  
#define right_select_pin  29   


#define input_pin  A1  
#define left_pot_pin  A5  
#define middle_pot_pin   A3 
#define right_pot_pin  A2  

#define red_pin  5  
#define blue_pin   6 
#define green_pin  20  

static byte pins[8] ={ 
  9,30,27,7,1,32,25,2}; 

/*
// back to dip 
 #define cs  10  
 #define cs2  10  
 
 #define shift_pin  14   
 #define mode_pin  15
 #define left_button_pin  6   
 #define right_button_pin  7   
 
 #define left_select_pin  29  
 #define right_select_pin  28   
 
 
 #define input_pin  A9  
 #define left_pot_pin  A8  
 #define middle_pot_pin   A7 
 #define right_pot_pin  A6 
 
 
 #define red_pin  5  
 #define blue_pin   3 
 #define green_pin  4  
 
 static byte pins[8] ={   31,33,24,26,30,32,25,27}; 
 */


flash flash;  //starts flash class and initilzes SPI


Bounce left_db = Bounce(); 
Bounce right_db = Bounce(); 
Bounce shift_db = Bounce(); 
Bounce mode_db = Bounce(); 

//IntervalTimer timer0;
IntervalTimer timer1;


#include <EEPROM.h>

byte res_tick; 

#define NUM_SAMPS 28000 // The audio sample rate is 29.4Khz so this gies us jsut under a second and uses up just abotu all the available ram

volatile int16_t dly_buffer[NUM_SAMPS];



#define filterSamples   35        
int smootha0 [filterSamples];  
int smootha1 [filterSamples];   
int smootha2 [filterSamples];   

int rawData1, smoothData1;  
int rawData2, smoothData2; 

int fbb[4]={
};
int fbc;

//delay
long write_head, read_head;
int lerp_dly;
int filter, feedback,fb_tmp_inv,fb_tmp;

int master_env,pad_rst_c;
byte p_mode;
uint16_t d,t,prev,j;
uint32_t prevm;
uint8_t in;

byte s;
uint16_t pot0,pot1,pot0_t,pot1_t,pot_c;

int16_t adc_buf[32]={
};
int16_t adc_buf2[32]={
};

int16_t read_buf[16][64]={
};

int32_t real_loc[16]={
};

uint8_t pot0_r[32]={
};
uint8_t pot1_r[32]={
};
uint16_t pt0,pt1;
int out0[16]={
  j
};
int out1[16]={
};
int out2[16]={
};
uint32_t r_loc[16]={
};
uint32_t s_len[16]={
};
uint32_t ps_len[16]={
};

uint8_t amp[16]={
};
uint8_t pad_b[16]={
};


uint8_t bank_sel[16]={
};

uint8_t pad_b0,pad_b1, pad_b2,pad_b3;
byte pad_amp0,pad_amp1,pad_amp2;

uint8_t out_buf[32]={
};
int32_t e4k_d,e4k_t;
uint8_t buf_c,read_c,flash_c;
byte record2,record0,record1,record3;
byte rec_en=0;
byte ready1,ready2,ready0;
byte play=0;
byte erased=0;
byte playthrough=0;
int ainf;
int sample_out,dly_out;

uint16_t pmaybe;
uint32_t dds_res,tune;
byte rec_en_b;
uint32_t w_loc,r_loc0,r_loc1,r_loc2,b_loc,loc0,erase_b;
unsigned long temp,dds_d,dds_t,loop_m,loop_t;
int  ain;
uint16_t ain2;
/////////dds defs
volatile uint32_t dx[16]={
};
int32_t dxflip[16]={
};

byte sample_step;
int pot12;
uint32_t acc[16]={
};
volatile uint32_t s_loc[16]={
};
int16_t comb=128;
byte play_trig[16]={
};
int16_t out[16]={
};

/////////rec defs

byte rec_start,rec_over;
byte playback=1;
uint32_t wp,rp,eep;
byte rec_set,record_setup,pplay,precord_b,record_b,erase_b5;
;
byte rec_ready[16]={
};
byte rec_trig[16]={
};
byte jump;
////touchy
uint16_t t23;
byte preload[16]={
};
uint32_t abs_loc,flip;
byte temp1111;
byte tick;
uint16_t dds_tune;
byte rec_happend;
int jjj;
byte left_button,right_button,d7,pd7,pd6,d6;
int accstep;
byte left_en[16] ={
};
byte right_en[16] ={
};
byte er_trig[16] ={
};
byte record_step;
byte in_mode_b,shift_b,pin_mode_b,pshift_b,er_en;
int shift_b_c,shift_b_ms;
byte shift_b_en=0;
int dds_r;
int testj;

int16_t comb_temp;


byte rrq[16]={
};
long read_flag[16]={
};
byte  loaded[16]={
};
int pot12raw;
byte pd7m,d7m;
boolean right_ch,left_ch;
int left_state,right_state;
byte lerp_tick;
int jhjh;
int fh_hi_t,fh_dds_t,fh_loop_t;
byte mode_state,shift_state, mode_ch,shift_ch;
long envm;
byte env_latch;
int out_f;
int out_off;
int mod_in,post_mod,p_mod_in;
float am_mod1;
byte master_mode;
byte upload=0;
byte up_bank_cnt;
int spitch;
int fm_mod;
long pad_len=0x010000; //length of default sample blocks in 16b

uint16_t bank_rst_c;
uint32_t sample_d,sample_t;

byte ppd7;
int pitch_pot;
int rev;
byte pot_tick;
volatile int16_t voice_bank[4]={
  100,100,100,100};
int fh_post_mod,fh_dly_out;
long sc,prev5,full_cnt,psc;
byte pr,rt;
byte blink1,load_done;
long load_cnt;
int fh0,fh1,pot0raw;
byte mod_mode;
byte rec_lock,rec_i;
int pot10,pot10raw,to_dly_temp;
int filter2,post_mod_f;
int left_pot,middle_pot,right_pot,mp_smooth,mpf;
int trigger_cut = 80;
int lockout,lockout_t,thru_env,thru_mode,shift_pressed;
uint32_t rec_locf;
uint32_t spid,spir;
int16_t saw_test;
int32_t rc;
byte rst_i;
int fh_sample_d;
byte poll_tick;
float lf;
byte mchan=1;

byte midi_pitch_en;
byte midi_dly_en;

uint16_t midi_pitch;
uint16_t midi_dly_len;
uint16_t midi_dly_fb;

byte warning;
int blue_out,red_out,grn_out,blue_out2,red_out2,grn_out2,Lj;
uint32_t prevs,prev_led0;
byte ledtick;
int threshold1,threshold2;
byte fader;
int  shift_low_cnt, shift_held_low;
uint16_t tap_tempo_cnt,mraw;
uint32_t tap_tempo_c,tap_tempo_p,prev_tap_micros, tap_ave;
uint32_t tap_bank[4]={};
short tap_bank_cnt,tap_latch;
int32_t tap_rate;
short midi_tap,p_midi_tap;
long poff;
////////////////////////////////

const int dds_rate=36; //36=29.4 kHz
const byte ab_len=10; //read
uint8_t buf_len=32; //write
const uint16_t pitch_max=380;

////////////////////////////////

long hi_t;
void setup() {

  randomSeed(A1);



 // Serial.begin(9600);
  //  while (!Serial) {}

  delay(200);

  Serial.println("hey");        

  pinMode(cs, OUTPUT);
  pinMode(cs2, OUTPUT);

  for (int i = 0; i < 10; i++) 
  {
    pinMode(pins[i],INPUT_PULLUP);
  }


  
  pinMode(5, OUTPUT); //red
  pinMode(20, OUTPUT); //grenn
  pinMode(6, OUTPUT); //blue

  pinMode(left_select_pin, OUTPUT);
  pinMode(right_select_pin, OUTPUT);

  pinMode(right_button_pin, INPUT_PULLUP);
  pinMode(left_button_pin, INPUT_PULLUP);

  pinMode(shift_pin, INPUT_PULLUP);
  pinMode(mode_pin, INPUT_PULLUP);




  left_db.attach(right_button_pin);
  left_db.interval(1);

  right_db.attach(left_button_pin);
  right_db.interval(1);

  shift_db.attach(shift_pin);
  shift_db.interval(1);

  mode_db.attach(mode_pin);
  mode_db.interval(1);


  r_loc1=64000;
  
  //delay(1000); //just so you can see the first printout
  ee_ret();


  right_ch = right_db.update();
  right_state = right_db.read();

  left_ch = left_db.update();
  left_state = left_db.read();
  if (right_state==0)
  {
    for (int i = 0; i < 8; ++i)
    {
      bank_sel[i]=0;    
    }
  }

  analogReadResolution(8); 
  analogReadAveraging(4); //4 dosent help much? and past that it's expensive? 4 helps a litle
  analogWriteResolution(12);

  mraw=analogRead(middle_pot_pin);
  uint16_t log3=pow(mraw,2);
  mp_smooth=log3>>8;
  lerp_dly=map(mp_smooth,0,255,NUM_SAMPS-4,16);
        
  pinMode(right_pot_pin, INPUT);

  SPIFIFO.begin(10,SPI_CLOCK_24MHz);

  //flash.erase_all();

  //usbMIDI.setHandleNoteOn(OnNoteOn) ;

  dds_tune=1/(dds_rate*.000001);
  timer1.begin(hi, dds_rate); 
  
  right_ch = right_db.update();
  left_ch = left_db.update();

  if (left_db.read()==0){
    mchan=2;
  }
  
   if (right_db.read()==0){
    mchan=3;
  }
  
    if (right_db.read()==0 && left_db.read()==0){
    mchan=4;
  }


}



////////////////////////////////////////////////////////////////////////////////////


void loop() {



  fader++;
  if (fader>16)
  {
    fader=0;
  }
  if (play_trig[fader]==0){
    static byte fade_step=128;
    if(out[fader]<-fade_step){
      out[fader]+=fade_step;
    }
    if(out[fader]>fade_step){
      out[fader]-=fade_step;
    }

    if(out[fader]>=-fade_step && out[fader]<=fade_step){
      out[fader]=0;
    }


  }


  loop_m=micros();

  MIDIchk();
  LEDs();
  pots();
  poll();
  controls(); 
 // print_ctrl();
 // printer();

  loop_t=micros()-loop_m;
  fh1=find_high(4,500,loop_t);




}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void MIDIchk(){
  p_midi_tap=midi_tap;
  if (usbMIDI.read()) {
    
    if (usbMIDI.getChannel()==mchan) {
      if (usbMIDI.getType()==1){
   
        analogWrite(red_pin,500);
        analogWrite(green_pin,500);
        analogWrite(blue_pin,500);


          if(usbMIDI.getData1()==35){        //midi clock is not supported in usbMidi yet so it's b0
          midi_tap=1;
        }

          if(usbMIDI.getData1()!=35){        
          midi_tap=0;
        }

        for (byte i=0;i<16;i++){
          if(usbMIDI.getData1()==i+36){
            play_trig[i]=1;
            poly_add(i);
            acc[i+bank_sel[i]]=0;
          }
        }
      }

      if (usbMIDI.getType()==3){  
        if (usbMIDI.getData1()==20){
          midi_pitch_en=1;
          midi_pitch=usbMIDI.getData2()*3;  //127 *3 = 381. Def pitch_max is 380 but in case this chages we'll clip it at pitch_max
            if (midi_pitch>pitch_max){
            midi_pitch=pitch_max;
            }  
          
        }
        if (usbMIDI.getData1()==21){
          midi_pitch_en=1;
          byte rev_t=usbMIDI.getData2();  //127 *3 = 381. Def pitch_max is 380 but in case this chages we'll clip it at pitch_max
          if (rev_t<64){
            rev=0;
          }  
          
          if (rev_t>=64){
            rev=1;
          }  
        }
        
        if (usbMIDI.getData1()==22){
          midi_dly_en=1;
          midi_dly_len=usbMIDI.getData2(); 
        }
        
        if (usbMIDI.getData1()==23){
          midi_dly_en=1;
          midi_dly_fb=usbMIDI.getData2(); 
        }
        
        
      }

    }

  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void printer(){
  int fh_dds_t=find_high(0,10000,dds_t);


  if (millis()-prevm>500 && master_mode!=99){
    prevm=millis();

    for (int i = 0; i < 16; ++i)
     {
     Serial.print(s_len[i]);    
     Serial.print(" ");
     
     }
          Serial.println();

  }

}


void print_ctrl(){
  int fh_dds_t=find_high(0,10000,dds_t);

  if (millis()-prevm>300){
    prevm=millis();

    /*
    for (int i = 0; i < 16; ++i)
     {
     Serial.print(s_len[i]);    
     Serial.print(" ");
     
     }
     Serial.println();  
     
     
     for (int i = 0; i < 16; ++i)
     {
     Serial.print(s_loc[i]);    
     Serial.print(" ");
     
     }
     Serial.println();  
     
     for (int i = 0; i < 8; ++i)
     {
     Serial.print(bank_sel[i]);    
     Serial.print(" ");
     
     }
     Serial.println();  
     
     for (int i = 0; i < 4; ++i)
     {
     Serial.print(voice_bank[i]);    
     Serial.print(" ");
     
     }
     Serial.println();  
     */

    Serial.println();       
    Serial.print("R ");      
    Serial.print(right_state);      
    Serial.print(" : "); 
    for (int i = 0; i < 8; ++i)
    {
      Serial.print(right_en[i]);   
      Serial.print(" ");

    }

    Serial.println();       
    Serial.print("L ");      
    Serial.print(left_state);      
    Serial.print(" : "); 
    for (int i = 0; i < 8; ++i)
    {
      Serial.print(left_en[i]);   
      Serial.print(" ");

    }

    Serial.println();
    Serial.println();


    //Serial.println(fh_dds_t);       
    Serial.println(left_pot);       
    Serial.println(middle_pot);       
    Serial.println(right_pot);       
    Serial.println();       
    Serial.println();       

  }

}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




int fhc[16];
int prevfh[16];

uint16_t find_high (byte n, int16_t ave, int16_t in){
  fhc[n]++;
  in = abs(in);

  if (fhc[n]>=ave){
    prevfh[n]=0;
    fhc[n]=0;
  }

  if (fhc[n]<ave){

    if (prevfh[n]<in){
      prevfh[n]=in;
    }

    else{
    }

  }


  return prevfh[n];

}




////////////////////////////////////////////////////////////////////////////////////


void LEDs(){
  /*
prev_led0++;
   if (prev_led0>20000){
   prev_led0=0;
   */

  if ((millis()-prev_led0)>50){
    prev_led0=millis();

    warning=!warning;


    if(master_mode==0){  //normal
      blue_out2=2000;
      grn_out2=500;
      red_out2=0;
    }

    if(master_mode==1){  //mod

      if (mod_mode==0){
        blue_out2=100;
        grn_out2=2000+(mod_in*50);
        red_out2=0;
      }

      if (mod_mode==1){
        blue_out2=100;
        grn_out2=1800+(mod_in*50);
        red_out2=900;
      }
    }

    if(master_mode==2){  //record

      if (sample_step==0){
        blue_out2=0;
        grn_out2=0;
        red_out2=2000;
      }

      if (sample_step==1){
        blue_out2=0;
        grn_out2=warning*500;
        red_out2=2000+(warning*500);
      }

      if (sample_step==2){
        blue_out2=0;
        grn_out2=warning*64;
        red_out2=warning*250;
      }

      if (sample_step==3){
        blue_out2=0;
        grn_out2=0;
        red_out2=2000;
      }
    }

    if(master_mode==3){  //through
      blue_out2=1000+(mod_in*50);
      grn_out2=0+(thru_mode*600)+(mod_in*50);
      red_out2=700+(mod_in);
    }

    analogWrite(blue_pin,(blue_out+blue_out2));
    analogWrite(green_pin,(grn_out+grn_out2));
    analogWrite(red_pin,(red_out+red_out2));



  }


}


void ee_store(byte pad){
  //Serial.print("ee_stored "); Serial.println(pad);

  byte byte3 = s_len[pad] >> 24;
  byte byte2 = s_len[pad] >> 16;
  byte byte1 = s_len[pad] >> 8;
  byte byte0 = s_len[pad] & 255;

  EEPROM.write(pad+(4*pad),   byte3);
  EEPROM.write(pad+(4*pad)+1, byte2);
  EEPROM.write(pad+(4*pad)+2, byte1);
  EEPROM.write(pad+(4*pad)+3, byte0);

  for (int i = 0; i < 8; ++i)
  {
    EEPROM.write(100+i,bank_sel[i]);
  }


}



void ee_ret(){


//early versions had these read from the eeprom but the eeprom can get corrupted or errased randomly it seems.
//These don't change anyway soooo

  s_len[0]=63625; //upload 1 bass808_len
  s_len[1]=7872; //upload2 clap004_len=7872;
  s_len[2]=38000; //1 boooh
  s_len[3]=15495; //2 beats
  s_len[4]=19155; //2 sqeak
  s_len[5]=57375; //3 lion
  s_len[6]=15495; //2 "siren" 
  s_len[7]=45745; //3 BWWWWWEEEEEERRWWAAAAAAAAAAAAA

  for (byte i=8;i<16;i++){
    byte byte3 = EEPROM.read(i+(4*i));
    byte byte2 = EEPROM.read(i+(4*i)+1);
    byte byte1 = EEPROM.read(i+(4*i)+2);
    byte byte0 = EEPROM.read(i+(4*i)+3);

    //  Serial.print(byte3); Serial.print(" ");
    //  Serial.print(byte2); Serial.print(" ");
    //  Serial.print(byte1); Serial.print(" ");
    //  Serial.println(byte0);

    s_len[i]= (byte3<<24)+(byte2<<16)+(byte1<<8)+(byte0);

    uint32_t tlen = (byte3<<24)+(byte3<<16)+(byte3<<8)+(byte0);
    if (tlen>65530){
      tlen=65530;
    }
    
    Serial.print("LEN "); 
    Serial.print(i);
    Serial.print(" "); 
    Serial.println(s_len[i]); 

  }

  for (byte i=0;i<8;i++){

    bank_sel[i]=EEPROM.read(100+i);
    if (bank_sel[i]>16)
    {
      Serial.print(bank_sel[i]); 
      Serial.println(" huh"); 

      bank_sel[i]=0;
    } 
    Serial.print("bank_sel "); 
    Serial.print(i);
    Serial.print(" "); 
    Serial.println(bank_sel[i]); 

  }



}


void E_pad(unsigned long pad){

  uint32_t loc = (pad*pad_len)<<1; 

  analogWrite(3,0); 
  analogWrite(4,0); 

  //so jsut like in read and write to flash, we errase with a doubled loc and add singles to it
  int flicker = (millis()%127)+127;

  analogWrite(5,flicker); //red

  flash.erase_4k(loc);
  Serial.print("erased ");   
  Serial.println(loc,HEX);

  flicker = (millis()%127)+127;
  analogWrite(5,flicker); //red

  loc+=0x001000;
  flash.erase_4k(loc);


  flicker = (millis()%127)+127;
  analogWrite(5,flicker); //red


  Serial.print("erased ");    
  Serial.println(loc,HEX);

  loc+=0x001000;
  flash.erase_4k(loc);


  flicker = (millis()%127)+127;
  analogWrite(5,flicker); //red

  Serial.print("erased ");    
  Serial.println(loc,HEX);

  loc+=0x010000;
  flash.erase_4k(loc);

  analogWrite(5,0); //red


  Serial.print("erased ");    
  Serial.println(loc,HEX);

  Serial.print(pad); 
  Serial.println(" erased????");

}



