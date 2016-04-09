import pgback
from pgback import *

buff = ''

def logger_write(opaque, offset, value, size):
    global buff
    buff = buff + chr(value)
    if (value == ord('\n')):
        print("PY LOGGER message: " + buff)
        buff = ""

def logger_read(opaque, offset, size):
    return 0;

def init_module(dev, init_data):
    print("called init_module in py\n")
    mr = py_alloc_memory_region();

    py_qsdk_set_mr(dev, mr);
    
    
def instantiate_module(dev, opaque):
    print("called instantiate_module in py\n")
    py_set_io_operations(dev, logger_read, logger_write, 4);
    
def init_qsdk_module():
    py_register_device(
        name = "py_logger",
        dev_init = init_module,
        dev_inst = instantiate_module,
        dev_delete = None,
        init_data = None)