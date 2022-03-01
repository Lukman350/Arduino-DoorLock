// mengincludekan modul Keypad dan servo
#include <Keypad.h>
#include <Servo.h>

Servo myservo;  // membuat variabel servo
const String password = "1234";
int posisi = 0; // membuat variabel posisi
const byte ROWS = 4; // banyaknya baris pada keypad
const byte COLS = 4; // banyaknya kolom pada keypad

// membuat array untuk menampung karakter yang akan ditampilkan pada keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {6, 7, 8, 9}; // baris pada keypad
byte colPins[COLS] = {2, 3, 4, 5}; // kolom pada keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // membuat keypad
int redPin = 12; // pin untuk menyalakan led merah
int greenPin = 13; // pin untuk menyalakan led hijau

void setup() {
    pinMode(redPin, OUTPUT); // membuat pin merah menjadi output
    pinMode(greenPin, OUTPUT); // membuat pin hijau menjadi output
    myservo.attach(11); // membuat servo menjadi pin 11
    lockPosition(true); // membuat servo menjadi posisi terkunci
}

void loop() {
    char key = keypad.getKey(); // membuat variabel key untuk mengambil keypad yang diinputkan

    if (key) {
        if (key == password.charAt(posisi)) { // jika key yang diinputkan sama dengan karakter pada posisi
            posisi++; // posisi bertambah
            if (posisi == password.length()) { // jika posisi sama dengan panjang password
                lockPosition(false); // membuat servo menjadi posisi terbuka
                posisi = 0; // posisi dikembalikan ke 0
            }
        } else {
            posisi = 0; // posisi dikembalikan ke 0
        }
    }

    delay(100); // delay 100 ms
}

void lockPosition(int locked) {
    if (locked) {
        digitalWrite(redPin, HIGH); // menyalakan led merah
        digitalWrite(greenPin, LOW); // mematikan led hijau
        myservo.write(0); // membuat servo menjadi posisi terkunci
    } else {
        digitalWrite(redPin, LOW); // mematikan led merah
        digitalWrite(greenPin, HIGH); // menyalakan led hijau
        myservo.write(90); // membuat servo menjadi posisi terbuka
    }
}