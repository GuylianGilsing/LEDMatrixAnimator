const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const comPort = "COM3";
const port = new SerialPort(comPort, {
    baudRate: 19200,
});

const lineStream = port.pipe(new Readline());

let flip = false;
lineStream.on('data', (data) => {
    console.log(data);

    setTimeout(() => {
        if(flip)
        {
            port.write("off");
            flip = false;
        }
        else
        {
            port.write("on");
            flip = true;
        }
    }, 1000);
});