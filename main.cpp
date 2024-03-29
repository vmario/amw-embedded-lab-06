#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"

#include <avr/interrupt.h>

/**
 * Odczytuje wynik pomiaru napięcia z ADC i przelicza go na temperaturę.
 *
 * @return Temperatura w °C.
 */
double measure()
{
	return 0;
}

/**
 * Konfiguruje i uruchamia ADC.
 */
void adcInitialize()
{
}

/**
 * Obsługa przerwania przepełnienia Timer/Counter1.
 */
ISR(TIMER1_OVF_vect)
{
}

/**
 * Obsługa przerwania komparatora Timer/Counter0.
 */
ISR(TIMER0_OVF_vect)
{
	display.print(measure(), 2);
	display.refresh();
}

/**
 * Funkcja główna.
 */
int main()
{
	shifter.initialize();
	timer.initialize();
	adcInitialize();

	sei();

	while (true) {
	}
}
