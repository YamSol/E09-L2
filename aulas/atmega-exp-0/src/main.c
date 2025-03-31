#include <avr/io.h>

#define LED_GREEN   0
#define LED_YELLOW  1
#define LED_RED     2


void setup() {

    DDRD |= (1<<LED_GREEN | 1<<LED_YELLOW | 1<<LED_RED);
    
}

void loop() {
    while(1) {

	PORTD ^= (1<<LED_YELLOW);

    }
}

int main() {
    setup();
    loop();
}

