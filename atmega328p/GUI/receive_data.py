import serial
serialPort = serial.Serial(
    port = 'COM8',
    baudrate = 9600,
    timeout = 1,
    bytesize = serial.EIGHTBITS,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE
    )
while(1):

    # Read data out of the buffer until a carraige return / new line is found
    serialString = serialPort.readline()

    # Print the contents of the serial data
    print(serialString)

    # Tell the device connected over the serial port that we recevied the data!
    # The b at the beginning is used to indicate bytes!
    serialPort.write(b"Thank you for sending data \r\n")
