#include "chip.h"

class DigitalIoPin {
public:
	DigitalIoPin(int port, int pin, bool input = true, bool pullup = true, bool invert = false);
	virtual ~DigitalIoPin();
	bool read();
	void write(bool value);;
	bool checkSelected();
	void setSelected(bool value);
private:
	int ioport;
	int iopin;
	bool softinvert;
	bool selected;
};
