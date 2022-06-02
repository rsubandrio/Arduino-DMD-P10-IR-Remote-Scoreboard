// DEFINES
// definisi pin
#define IR_POS_PIN 3 // pin memakai pin ini karena habis pin vcc
#define IR_NEG_PIN 4 // pin memakai pin ini karena habis pin gnd
#define IR_RCV_PIN 2 // pin penerima signal IR

// definisi tombol remote
#define A_POINT_UP 69 // hasil pembacaan IR tombol 1 untuk nambah poin A
#define A_POINT_DN 68 // hasil pembacaan IR tombol 4 untuk mengurangi poin A
#define A_WIN_UP 7    // hasil pembacaan IR tombol 7 untuk nambah win A
#define A_WIN_DN 22   // hasil pembacaan IR tombol * untuk mengurangi win A

#define B_POINT_UP 71 // hasil pembacaan IR tombol 3 untuk nambah poin B
#define B_POINT_DN 67 // hasil pembacaan IR tombol 6 untuk mengurangi poin B
#define B_WIN_UP 9    // hasil pembacaan IR tombol 9 untuk nambah win B
#define B_WIN_DN 13   // hasil pembacaan IR tombol # untuk mengurangi win B

#define SET_UP 70 // untuk menambah set tombol no 2
#define SET_DN 64 // untuk mengurangi set tombol no 5

#define HOUR_BTN 21   // untuk set jam tombol no 8
#define MINUTE_BTN 25 // untuk set menit tombol no 0

#define RESET_DISP 28 // untuk reset score tombol OK
#define RESET_SYS0 8  // untuk restart system tombol panah kiri
#define RESET_SYS1 90 // untuk reset system tombol panah kanan

#define BRIGHTNESS_UP 24 // untuk menambah kecerahan tombol panah atas
#define BRIGHTNESS_DN 82 // untuk mengurangi kecerahan tombol panah bawah

// definisi jenis remote
#define IR_SMALLD_NEC

// definisi panel p10
#define PANJANG 2 // jumlah panel ke samping
#define LEBAR 1   // jumlah panel ke bawah

// diperlukan untuk kedip jam
#define INTERVAL 1000 // interval blink

// INCLUDES
// harus include ini untuk arduino
#include <Arduino.h>

// Libraries
// remote control decoder (tidak perlu encoder)
#include <IRsmallDecoder.h>

// librari untuk mengendalikan panel P10
#include <SPI.h>             // library SPI yg dibutuhkan oleh DMD2
#include <DMD2.h>            // library
#include <segment8x16.H>     // font
#include <font4x6.h>         // font
#include <font6x7.h>         // font
#include <font5x7.h>         // font
#include <DejaVuSansBold9.h> // font

// library untuk RTC
#include <Wire.h> // library untuk komunikasi serial dengan RTC
#include <RTC.h>  // library RTC

// library untuk eeprom
#include <eewl.h>

// GLOBAL VARIABLES
// remote control
IRsmallDecoder irDecoder(IR_RCV_PIN);
irSmallD_t irData;

// Dot Matrix Display
SPIDMD dmd(PANJANG, LEBAR);
DMD_TextBox box(dmd, 0, 3);

// Real Time Clock
static DS3231 RTC;

// Others
unsigned long prevMillis = 0;
bool blink = 1;
byte score_a, score_b, win_a, win_b, set, hour, minute, brightness, arrow_dir;
EEWL s_a(score_a, 50, 10);
EEWL s_b(score_b, 50, 100);
EEWL w_a(win_a, 25, 200);
EEWL w_b(win_b, 25, 250);
EEWL theSet(set, 10, 300);
EEWL a_d(arrow_dir, 50, 350);

// FUNCTIONS DEFINITIONS
void (*resetFunc)(void) = 0;
void drawTime();
void drawScore_a(String);
void drawScore_b(String);
void drawWin(String, bool);
void drawSet(String);
void drawArrow(bool);
void resetDisplay();

void setup()
{
  Serial.begin(115200);
  RTC.begin();
  pinMode(IR_POS_PIN, OUTPUT);
  pinMode(IR_NEG_PIN, OUTPUT);
  digitalWrite(IR_POS_PIN, HIGH);
  digitalWrite(IR_NEG_PIN, LOW);

  Serial.println();
  Serial.println(F("Arduino 2 Panel P10 Scoreboard."));
  Serial.println(F("Programmed by Rio Subandrio - riopapaika@gmail.com"));
  Serial.println();

  brightness = 25; // 0 s/d 100
  dmd.setBrightness(brightness);
  dmd.begin();

  dmd.drawFilledBox(0, 0, 63, 15);
  delay(100);
  for (short x = 0; x < 8; x++)
  {
    dmd.drawBox(0, 7 - x, 63, 8 + x, GRAPHICS_OFF);
    delay(100);
  }

  dmd.selectFont(font6x7);
  dmd.drawString(10, -1, F("PT."));
  dmd.drawString(33, -1, F("WKP"));
  dmd.drawString(17, 8, F("2022"));

  delay(1000);

  for (short x = 0; x < 32; x++)
  {
    dmd.drawLine(0 + x, 0, 0 + x, 16);
    dmd.drawLine(63 - x, 0, 63 - x, 16);
    delay(50);
  }

  dmd.selectFont(font6x7);
  dmd.drawString(25, -1, F("Rio"), GRAPHICS_INVERSE);
  dmd.drawString(2, 8, F("Subandrio"), GRAPHICS_INVERSE);
  delay(250);
  dmd.clearScreen();
  dmd.drawString(25, -1, F("Rio"), GRAPHICS_ON);
  dmd.drawString(2, 8, F("Subandrio"), GRAPHICS_ON);
  delay(250);

  dmd.selectFont(DejaVuSansBold9);
  dmd.clearScreen();
  const char *pesan = "Selamat datang di Gedung Olah Raga PT. Waru Kaltim Plantation     ";
  while (*pesan)
  {
    box.print(*pesan);
    pesan++;
    delay(100);
  }

  dmd.clearScreen();
  dmd.drawString(12, 3, F("Selamat"));
  delay(1000);
  dmd.drawString(3, 3, F("Bertanding!!"));
  delay(1000);

  s_a.get(score_a);
  s_b.get(score_b);
  w_a.get(win_a);
  w_b.get(win_b);
  theSet.get(set);
  a_d.get(arrow_dir);

  if (!s_a.get(score_a) || !s_b.get(score_b) || !w_a.get(win_a) || !w_b.get(win_b) || !theSet.get(set))
  {
    Serial.println(F("Tidak ada data score di eeprom!"));
  }

  Serial.println(F("Waiting for a NEC remote control IR signal..."));
  Serial.println(F("held\t addr\t cmd"));

  dmd.clearScreen();

  drawTime();
  drawScore_a((score_a < 10 ? "0" : "") + String(score_a));
  drawScore_b((score_b < 10 ? "0" : "") + String(score_b));
  drawWin(String(win_a), 0);
  drawWin(String(win_b), 1);
  drawSet(String(set));
  drawArrow(arrow_dir);

  // resetDisplay();

  hour = RTC.getHours();
  minute = RTC.getMinutes();
}

void loop()
{
  unsigned long currMillis = millis();
  if (irDecoder.dataAvailable(irData))
  {                                    // 5th: if the decoder has some new data available,
    Serial.print(irData.keyHeld, HEX); // 6th: do something with the data.
    Serial.print(F("\t "));
    Serial.print(irData.addr, HEX);
    Serial.print(F("\t "));
    Serial.println(irData.cmd);
    switch (irData.cmd)
    {
    case A_POINT_UP:
      score_a++;
      score_a = score_a > 99 ? 0 : score_a;
      score_a = score_a < 0 ? 99 : score_a;
      drawScore_a((score_a < 10 ? "0" : "") + String(score_a));
      drawArrow(0);
      arrow_dir = 0;
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        s_a.put(score_a);
        a_d.put(arrow_dir);
      }
      break;
    case A_POINT_DN:
      score_a--;
      score_a = score_a > 99 ? 0 : score_a;
      score_a = score_a < 0 ? 99 : score_a;
      drawScore_a((score_a < 10 ? "0" : "") + String(score_a));
      drawArrow(0);
      arrow_dir = 0;
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        s_a.put(score_a);
        a_d.put(arrow_dir);
      }
      break;
    case A_WIN_UP:
      win_a++;
      win_a = win_a > 9 ? 0 : win_a;
      win_a = win_a < 0 ? 9 : win_a;
      drawWin(String(win_a), 0);
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        w_a.put(win_a);
      }
      break;
    case A_WIN_DN:
      win_a--;
      win_a = win_a < 0 ? 9 : win_a;
      win_a = win_a > 9 ? 0 : win_a;
      drawWin(String(win_a), 0);
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        w_a.put(win_a);
      }
      break;

    case B_POINT_UP:
      score_b++;
      score_b = score_b > 99 ? 0 : score_b;
      score_b = score_b < 0 ? 99 : score_b;
      drawScore_b((score_b < 10 ? "0" : "") + String(score_b));
      drawArrow(1);
      arrow_dir = 1;
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        s_b.put(score_b);
        a_d.put(arrow_dir);
      }
      break;
    case B_POINT_DN:
      score_b--;
      score_b = score_b < 0 ? 99 : score_b;
      score_b = score_b > 99 ? 0 : score_b;
      drawScore_b((score_b < 10 ? "0" : "") + String(score_b));
      drawArrow(1);
      arrow_dir = 1;
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        s_b.put(score_b);
        a_d.put(arrow_dir);
      }
      break;
    case B_WIN_UP:
      win_b++;
      win_b = win_b > 9 ? 0 : win_b;
      win_b = win_b < 0 ? 9 : win_b;
      drawWin(String(win_b), 1);
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        w_b.put(win_b);
      }
      break;
    case B_WIN_DN:
      win_b--;
      win_b = win_b > 9 ? 0 : win_b;
      win_b = win_b < 0 ? 9 : win_b;
      drawWin(String(win_b), 1);
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        w_b.put(win_b);
      }
      break;

    case SET_UP:
      set++;
      set = set > 9 ? 0 : set;
      set = set < 0 ? 9 : set;
      drawSet(String(set));
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        theSet.put(set);
      }
      break;
    case SET_DN:
      set--;
      set = set > 9 ? 0 : set;
      set = set < 0 ? 9 : set;
      drawSet(String(set));
      if (irData.keyHeld == 0)
      {
        // hanya simpan ke eeprom jika key tidak ditahan
        theSet.put(set);
      }
      break;

    case HOUR_BTN:
      hour++;
      hour = hour > 23 ? 0 : hour;
      RTC.setTime(hour, RTC.getMinutes(), RTC.getSeconds());
      drawTime();
      break;
    case MINUTE_BTN:
      minute++;
      minute = minute > 59 ? 0 : minute;
      RTC.setTime(RTC.getHours(), minute, RTC.getSeconds());
      drawTime();
      break;

    case RESET_DISP:
      resetDisplay();
      break;

    case BRIGHTNESS_UP:
      brightness++;
      brightness = brightness > 100 ? 100 : brightness;
      dmd.setBrightness(brightness);
      break;
    case BRIGHTNESS_DN:
      brightness--;
      brightness = brightness < 0 ? 0 : brightness;
      dmd.setBrightness(brightness);
      break;

    case RESET_SYS0:
    case RESET_SYS1:
      resetFunc();
      break;

    default:
      break;
    }
  }
  if (currMillis - prevMillis >= INTERVAL)
  {
    prevMillis = currMillis;
    blink = !blink;
  }

  drawTime();
}

// FUNCTIONS
void drawTime()
{
  dmd.selectFont(font5x7);
  if (RTC.getHours() < 10)
  {
    dmd.drawString(19, 0, "0" + String(RTC.getHours()));
  }
  else
  {
    dmd.drawString(19, 0, String(RTC.getHours()));
  }

  if (RTC.getMinutes() < 10)
  {
    dmd.drawString(34, 0, "0" + String(RTC.getMinutes()));
  }
  else
  {
    dmd.drawString(34, 0, String(RTC.getMinutes()));
  }

  dmd.drawFilledBox(31, 1, 32, 2, blink ? GRAPHICS_OFF : GRAPHICS_ON);
  dmd.drawFilledBox(31, 4, 32, 5, blink ? GRAPHICS_OFF : GRAPHICS_ON);
}

void drawScore_a(String score)
{
  dmd.selectFont(segment8x16);
  dmd.drawString(0, 0, score);
}

void drawScore_b(String score)
{
  dmd.selectFont(segment8x16);
  dmd.drawString(47, 0, score);
}

void drawArrow(bool direction)
{
  // direction left = 0, right = 1
  if (!direction)
  {
    dmd.drawLine(18, 12, 18, 12);
    dmd.drawLine(19, 11, 19, 13);
    dmd.drawLine(20, 10, 20, 14);

    dmd.drawLine(43, 10, 43, 14, GRAPHICS_OFF);
    dmd.drawLine(44, 11, 44, 13, GRAPHICS_OFF);
    dmd.drawLine(45, 12, 45, 12, GRAPHICS_OFF);
  }
  else
  {
    dmd.drawLine(18, 12, 18, 12, GRAPHICS_OFF);
    dmd.drawLine(19, 11, 19, 13, GRAPHICS_OFF);
    dmd.drawLine(20, 10, 20, 14, GRAPHICS_OFF);

    dmd.drawLine(43, 10, 43, 14);
    dmd.drawLine(44, 11, 44, 13);
    dmd.drawLine(45, 12, 45, 12);
  }
}

void drawWin(String win, bool direction)
{
  dmd.selectFont(font4x6);
  if (!direction)
  {
    dmd.drawString(23, 9, win);
  }
  else
  {
    dmd.drawString(37, 9, win);
  }
}

void drawSet(String set)
{
  dmd.selectFont(font6x7);
  dmd.drawString(29, 7, set);
}

void resetDisplay()
{
  dmd.clearScreen();
  brightness = 25;
  dmd.setBrightness(25);
  score_a = 0;
  score_b = 0;
  win_a = 0;
  win_b = 0;
  set = 1;
  drawTime();
  drawScore_a("00");
  drawScore_b("00");
  drawWin("0", 0);
  drawWin("0", 1);
  drawSet("1");
}