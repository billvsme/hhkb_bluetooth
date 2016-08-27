#include <hidboot.h>
#include <usbhub.h>

uint8_t CurrentReport[12] = {0x0C, 0x00, 0xA1, 0x01, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t UpReport[12] = {0x0C, 0x00, 0xA1, 0x01, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t KeyOemToXm(uint8_t key) {
  return key;
};

uint8_t ModeOemToXm(uint8_t mod) {
  return mod;
};

uint8_t* BTHidReport(uint8_t mod, uint8_t key) {  
  CurrentReport[4] = ModeOemToXm(mod);
  CurrentReport[7] = KeyOemToXm(key);
  return CurrentReport;
};

void sendReport(uint8_t report[12]) {
  Serial.write(report[0]);
  Serial.write(report[1]);
  Serial.write(report[2]);
  Serial.write(report[3]);
  Serial.write(report[4]);
  Serial.write(report[5]);
  Serial.write(report[6]);
  Serial.write(report[7]);
  Serial.write(report[8]);
  Serial.write(report[9]);
  Serial.write(report[10]);
  Serial.write(report[11]);
}

class KbdRptParser : public KeyboardReportParser
{
  protected:
    void OnKeyDown  (uint8_t mod, uint8_t key);
    void OnKeyUp  (uint8_t mod, uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  uint8_t* report = BTHidReport(mod, key);
  sendReport(report);
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  sendReport(UpReport);
}


USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

uint32_t next_time;

KbdRptParser Prs;

void setup()
{
  Serial.begin( 9600 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  next_time = millis() + 5000;

  HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);
}

void loop()
{
  Usb.Task();
}
