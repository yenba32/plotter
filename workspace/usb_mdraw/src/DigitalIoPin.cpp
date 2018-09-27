#include "DigitalIoPin.h"

DigitalIoPin::DigitalIoPin(int port, int pin, bool input, bool pullup, bool invert) {
	ioport = port;
	iopin = pin;
	selected = false;
	softinvert = false;

	if (input && pullup && invert) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, port, pin);
	} else if (input && pullup) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN));
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, port, pin);
	} else if (input) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, (IOCON_DIGMODE_EN));
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, port, pin);
	} else if (!input) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, IOCON_MODE_INACT | IOCON_DIGMODE_EN);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, port, pin);
		if (invert) {
			softinvert = true;
			Chip_GPIO_SetPinState(LPC_GPIO, port, pin, true); // Initial state off
		} else {
			Chip_GPIO_SetPinState(LPC_GPIO, port, pin, false); // Initial state off
		}
	}
}


DigitalIoPin::~DigitalIoPin()
{

}

bool DigitalIoPin::read() {
	if ((Chip_GPIO_GetPinState(LPC_GPIO, ioport, iopin))) {
		if (softinvert) {
			return false;
		} else {
			return true;
		}
	} else {
		if (softinvert) {
			return true;
		} else {
			return false;
		}
	}
}

void DigitalIoPin::write(bool value) {
	if (softinvert) {
		Chip_GPIO_SetPinState(LPC_GPIO, ioport, iopin, !value);
	} else {
		Chip_GPIO_SetPinState(LPC_GPIO, ioport, iopin, value);
	}
}

bool DigitalIoPin::checkSelected() {
	return selected;
}

void DigitalIoPin::setSelected(bool value) {
	selected = value;
}
