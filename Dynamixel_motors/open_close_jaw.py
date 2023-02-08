#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os

if os.name == 'nt':
    import msvcrt
    def getch():
        return msvcrt.getch().decode()
else:
    import sys, tty, termios
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    def getch():
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

from dynamixel_sdk import *                 # Uses Dynamixel SDK library

# DYNAMIXEL Protocol Version (1.0 / 2.0)
# https://emanual.robotis.com/docs/en/dxl/protocol2/
PROTOCOL_VERSION            = 2.0

# Define the proper baudrate to search DYNAMIXELs. Note that XL320's baudrate is 1 M bps.
BAUDRATE                = 57600

# Factory default ID of all DYNAMIXEL is 1
DXL_ID                      = 1

# Use the actual port assigned to the U2D2.
# ex) Windows: "COM*", Linux: "/dev/ttyUSB*", Mac: "/dev/tty.usbserial-*"
DEVICENAME                  = '/dev/ttyUSB0'

# Initialize PortHandler instance
# Set the port path
# Get methods and members of PortHandlerLinux or PortHandlerWindows
portHandler = PortHandler(DEVICENAME)

# Initialize PacketHandler instance
# Set the protocol version
# Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
packetHandler = PacketHandler(PROTOCOL_VERSION)

# Open port
if portHandler.openPort():
    print("Succeeded to open the port")
else:
    print("Failed to open the port")
    print("Press any key to terminate...")
    getch()
    quit()


# Set port baudrate
if portHandler.setBaudRate(BAUDRATE):
    print("Succeeded to change the baudrate")
else:
    print("Failed to change the baudrate")
    print("Press any key to terminate...")
    getch()
    quit()

# Try to ping the Dynamixel
# Get Dynamixel model number
dxl_model_number, dxl_comm_result, dxl_error = packetHandler.ping(portHandler, DXL_ID)
print(f"dxl_model_number is: {dxl_model_number}")
print(f"dxl_comm_result is: {dxl_comm_result}")
print(f"dxl_error is: {dxl_error}")
print(f"COMM_SUCCESS is {COMM_SUCCESS}")
if dxl_comm_result != COMM_SUCCESS:
    print("statement 0")
    print("%s" % packetHandler.getTxRxResult(dxl_comm_result))
elif dxl_error != 0:
    print("statement 1")
    print("%s" % packetHandler.getRxPacketError(dxl_error))
else:
    print("statement 2")
    print("[ID:%03d] ping Succeeded. Dynamixel model number : %d" % (DXL_ID, dxl_model_number))

def torque_enable():
    TORQUE_ENABLE_REG = 64
    TORQUE_ENABLE = 1
    result, error = packetHandler.write4ByteTxRx(portHandler, DXL_ID, TORQUE_ENABLE_REG, TORQUE_ENABLE)
    return

def torque_disable():
    TORQUE_ENABLE_REG = 64
    TORQUE_ENABLE = 0
    result, error = packetHandler.write4ByteTxRx(portHandler, DXL_ID, TORQUE_ENABLE_REG, TORQUE_ENABLE)
    return

def read_operation_mode():
    OPERATING_MODE_REG = 11
    data, result, error = packetHandler.read1ByteTxRx(portHandler, DXL_ID, OPERATING_MODE_REG)
    print(f"data is: {data}")
    print(f"result is: {result}")
    print(f"error is: {error}")
    return data

def set_current_position_mode():
    OPERATING_MODE_REG = 11
    OPERATION_MODE = 5
    result, error = packetHandler.write1ByteTxRx(portHandler, DXL_ID, OPERATING_MODE_REG, OPERATION_MODE)
    return

def set_goal_current(GOAL_CURRENT):
    GOAL_CURRENT_REG = 102
    result, error = packetHandler.write2ByteTxRx(portHandler, DXL_ID, GOAL_CURRENT_REG, GOAL_CURRENT)
    return

def read_present_position():
    PRESENT_POSITION_REG = 132
    PRESENT_POSITION, result, error = packetHandler.read4ByteTxRx(portHandler, DXL_ID, PRESENT_POSITION_REG)
    return PRESENT_POSITION

def set_goal_position(GOAL_POSITION):
    GOAL_POSITION_REG = 116
    result, error = packetHandler.write4ByteTxRx(portHandler, DXL_ID, GOAL_POSITION_REG, GOAL_POSITION)
    return

def read_present_current():
    PRESENT_CURRENT_REG = 126
    PRESENT_CURRENT, result, error = packetHandler.read2ByteTxRx(portHandler, DXL_ID, PRESENT_CURRENT_REG)
    return PRESENT_CURRENT


import datetime


torque_enable()
set_current_position_mode()
read_operation_mode()
set_goal_current(10)
print(f"current position is {read_present_position()}")
set_goal_position(1000)

time.sleep(1)

torque_disable()

# Close port
portHandler.closePort()
