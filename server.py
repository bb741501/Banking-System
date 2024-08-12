# server.py
from flask import Flask, request, jsonify
import ctypes
import os
app = Flask(__name__)

# Load the C++ shared library

libbank = ctypes.CDLL(r'C:\Users\Biswajit Biswas\Downloads\Project\Banking_System_Cpp\libbank.dll')




# Define C++ functions to call
libbank.addUser.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_double]
libbank.addUser.restype = ctypes.c_bool

libbank.authenticate.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
libbank.authenticate.restype = ctypes.POINTER(ctypes.c_void_p)

libbank.transfer.argtypes = [ctypes.POINTER(ctypes.c_void_p), ctypes.c_char_p, ctypes.c_double]
libbank.transfer.restype = ctypes.c_bool

libbank.getBalance.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
libbank.getBalance.restype = ctypes.c_double

@app.route('/add_user', methods=['POST'])
def add_user():
    data = request.json
    username = data['username'].encode('utf-8')
    password = data['password'].encode('utf-8')
    balance = data['balance']
    success = libbank.addUser(username, password, balance)
    return jsonify({'success': success})

@app.route('/login', methods=['POST'])
def login():
    data = request.json
    username = data['username'].encode('utf-8')
    password = data['password'].encode('utf-8')
    user = libbank.authenticate(username, password)
    if user:
        return jsonify({'success': True})
    else:
        return jsonify({'success': False})

@app.route('/transfer', methods=['POST'])
def transfer():
    data = request.json
    from_username = data['from_username'].encode('utf-8')
    to_username = data['to_username'].encode('utf-8')
    amount = data['amount']

    # Authenticate sender (mocked)
    sender_user = libbank.authentica
