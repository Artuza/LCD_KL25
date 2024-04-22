#include <MKL25Z4.H>
// Define pins for LCD
DigitalOut rs(PTE20); // Example pin
DigitalOut en(PTE21); // Example pin
BusOut data(PTE22, PTE23, PTE29, PTE30); // Example pins for D4, D5, D6, D7

// Function prototypes
void lcdToggleEnable();
void lcdSendNibble(int nibble);
void lcdSendByte(int address, int data);
void lcdInit();
void lcdPrint(char *string);

int main() {
    lcdInit();
    lcdPrint("Hello, World!");
    while (true) {}
}

void lcdToggleEnable() {
    wait_us(600);
    en = 1;
    wait_us(600);
    en = 0;
    wait_us(600);
}

void lcdSendNibble(int nibble) {
    data = nibble & 0x0F;
    lcdToggleEnable();
}

void lcdSendByte(int address, int dataByte) {
    rs = address;
    lcdSendNibble(dataByte >> 4);
    lcdSendNibble(dataByte);
}

void lcdInit() {
    wait_ms(15);
    lcdSendNibble(0x03);
    wait_ms(5);
    lcdSendNibble(0x03);
    wait_us(150);
    lcdSendNibble(0x03);
    lcdSendNibble(0x02);
    lcdSendByte(0, 0x28);
    lcdSendByte(0, 0x0C);
    lcdSendByte(0, 0x06);
    lcdSendByte(0, 0x01);
    wait_ms(2);
}

void lcdPrint(char *string) {
    while (*string) {
        lcdSendByte(1, *string++);
    }
}
