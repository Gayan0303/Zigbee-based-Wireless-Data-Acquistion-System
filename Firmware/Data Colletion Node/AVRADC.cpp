/* 
* AVRADC.cpp
*
* Created: 17-12-2024 14:45:23
* Author: ganap
*/


#include "AVRADC.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <functional>

namespace AVRADC {

	class ADC {
		public:
		using Handler = std::function<void(uint8_t pin, uint16_t value)>;

		private:
		Handler _adc_handler;
		uint8_t _adc_pin_qty = 0;

		public:
		// Synchronous ADC Read
		uint16_t read(uint8_t prescaler, uint8_t vref, uint8_t pin) {
			#ifdef MUX5
			if (pin > 7) {
				ADCSRB |= _BV(MUX5);
				ADMUX = vref | (pin - 8);
				} else {
				ADCSRB &= ~(_BV(MUX5));
				ADMUX = vref | pin;
			}
			#else
			ADMUX = vref | pin;
			#endif
			ADCSRA = _BV(ADEN) | _BV(ADSC) | prescaler;  // Enable ADC and start conversion
			while (!(ADCSRA & _BV(ADIF)));              // Wait for conversion to finish

			return (ADCL | (ADCH << 8));                // Combine ADCL and ADCH
		}

		// Asynchronous ADC Start
		void start(uint8_t prescaler, uint8_t vref, uint8_t pin_qty, Handler handler) {
			_adc_handler = handler;
			_adc_pin_qty = pin_qty;
			ADMUX = vref;

			#ifdef MUX5
			ADCSRB &= ~(_BV(MUX5));
			#endif
			ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIE) | prescaler;  // Enable ADC, start conversion, and enable interrupt
		}

		// Stop ADC
		void stop() {
			ADCSRA = 0;
		}

		#ifdef ENABLE_ADC_INT
		// Interrupt Service Routine
		friend void ADC_vect_ISR();
		#endif
	};

	#ifdef ENABLE_ADC_INT
	// Global ADC instance for ISR
	static ADC* adc_instance = nullptr;

	// Link the ADC object to the ISR
	void ADC_vect_ISR() {
		static uint8_t cur_pin = 0;

		if (adc_instance && adc_instance->_adc_handler) {
			adc_instance->_adc_handler(cur_pin, ADCL | (ADCH << 8));
		}

		cur_pin++;
		if (cur_pin >= adc_instance->_adc_pin_qty)
		cur_pin = 0;

		#ifdef MUX5
		if (cur_pin > 7) {
			ADCSRB |= _BV(MUX5);
			ADMUX = (ADMUX & 0xe0) | (cur_pin - 8);
			} else {
			ADCSRB &= ~(_BV(MUX5));
			ADMUX = (ADMUX & 0xe0) | cur_pin;
		}
		#else
		ADMUX = (ADMUX & 0xe0) | cur_pin;
		#endif

		ADCSRA |= _BV(ADSC);  // Start next conversion
	}

	// Link the ISR
	ISR(ADC_vect) {
		ADC_vect_ISR();
	}
	#endif

}  // namespace AtmegaADC
