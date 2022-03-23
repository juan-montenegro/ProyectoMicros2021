import time
from flask import Flask, render_template
from flask_serial import Serial
from flask import send_file
from flask_socketio import SocketIO
from flask_bootstrap import Bootstrap
import json
import math
import eventlet
from decimal import Decimal

eventlet.monkey_patch()

app = Flask(__name__)
app.config['SERIAL_TIMEOUT'] = 0.1
app.config['SERIAL_PORT'] = 'COM8'
app.config['SERIAL_BAUDRATE'] = 9600
app.config['SERIAL_BYTESIZE'] = 8
app.config['SERIAL_PARITY'] = 'N'
app.config['SERIAL_STOPBITS'] = 1

ser = Serial(app)
socketio = SocketIO(app)
bootstrap = Bootstrap(app)


def pol2cart(rho, phi):
    x = rho * math.cos(math.radians(phi))
    y = rho * math.sin(math.radians(phi))
    return(x, y)


@app.route('/')
def index():
    return render_template('page/html/try.html')


@socketio.on('send')
def handle_send(json_str):
    json_str = str.encode(json_str)
    type(json_str)
    print(json_str)
    time.sleep(2)
    #data = json.loads(json_str)
    ser.on_send(b"%s" % json_str)
    #print("send to serial: %s" % data['message'])


@ser.on_message()
def handle_message(msg):
    print(msg)
    try:
        string = msg.decode("utf-8").rstrip('\n')
        string = string.replace(' ', '')
        splitted_data = string.split('|')
        distance_float = float(splitted_data[2])
        angle_float = 90 - float(splitted_data[1])
        cartesian_x, cartesian_y = pol2cart(distance_float, angle_float)
        json_data = {
            'key': int(splitted_data[0]),
            'angle': splitted_data[1],
            'distance': splitted_data[2],
            'x': cartesian_x,
            'y': cartesian_y
        }
        print(json_data)
        # print("receive a message:", msg.decode("utf-8").rstrip('\n'))
        socketio.emit("serial_message", data={
            "message": json_data})
    except Exception as e:
        print(e)


@ ser.on_log()
def handle_logging(level, info):
    print(level, info)


if __name__ == '__main__':
    # Warning!!!
    # this must use `debug=False`
    # if you use `debug=True`,it will open serial twice, it will open serial failed!!!
    socketio.run(app, debug=False)
