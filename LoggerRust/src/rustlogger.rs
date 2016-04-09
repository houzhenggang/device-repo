extern crate libc;
use std::ptr;
use std::mem::size_of;

extern {
    fn register_device(name: &RsDevInit);
    
    fn alloc_memory_region() -> *mut libc::c_void;
    
    fn set_io_operations(
        dev: *mut libc::c_void,
        read: extern fn(*mut libc::c_void, i64, i32) -> i64,
        write: extern fn(*mut libc::c_void, i64, i64, i32),
        size: i32);
        
    fn qsdk_set_mr(dev: *mut libc::c_void, mr: *mut libc::c_void);
}

struct RsDevInit {
    name: *const u8,
    init_data: *mut libc::c_void,
    dev_init: extern fn(dev: *mut libc::c_void, init_data: *mut libc::c_void) -> *mut libc::c_void,
    dev_inst: extern fn(dev: *mut libc::c_void, opaque: *mut libc::c_void),
    dev_delete: extern fn(dev: *mut libc::c_void, opaque: *mut libc::c_void)
}

struct LoggerStruct {
    buffer: [char; 32],
    msg_pos: i32,
    mr: *mut libc::c_void
}

extern fn rust_logger_delete(_dev: *mut libc::c_void, _opaque: *mut libc::c_void)
{

}

extern fn rust_logger_write(opaque: *mut libc::c_void, _offset: i64, value: i64, _size: i32)
{
    let rlogger: &mut LoggerStruct = unsafe { &mut *(opaque as *mut LoggerStruct) };
    
    rlogger.buffer[rlogger.msg_pos as usize] = (std::char::from_u32(value as u32)).unwrap_or('0');
    rlogger.msg_pos += 1;
    
    if value == 10 /* 10 is \n */
    {
        print!("RUST LOGGER message: ");
        for x in 0..rlogger.msg_pos
        {
            print!("{}", rlogger.buffer[x as usize]);
        }
        rlogger.msg_pos = 0;
    }
}

extern fn rust_logger_read(_opaque: *mut libc::c_void, _offset: i64, _size: i32) -> i64
{
    return 0;
}

extern fn rust_logger_init(dev: *mut libc::c_void, _init_data: *mut libc::c_void) -> *mut libc::c_void
{
    let mut rlogger: &mut LoggerStruct;
    
    unsafe 
    {
        let malloc_mem: *mut libc::c_void = libc::malloc(size_of::<LoggerStruct>());
        
        rlogger = &mut *(malloc_mem as *mut LoggerStruct);
        rlogger.msg_pos = 0;
        rlogger.buffer = ['\0'; 32];
        rlogger.mr = alloc_memory_region();

        qsdk_set_mr(dev, rlogger.mr);
        
        return malloc_mem;
    }
}

extern fn rust_logger_inst(dev: *mut libc::c_void, _opaque: *mut libc::c_void)
{
    unsafe 
    {
        set_io_operations(dev, rust_logger_read, rust_logger_write, 0x50);
    }
}

#[no_mangle]
pub extern "C" fn init_qsdk_module()
{
    let dev_init = RsDevInit {
        name: "rust_logger".as_ptr(),
        init_data: ptr::null_mut(),
        dev_init: rust_logger_init,
        dev_inst: rust_logger_inst,
        dev_delete: rust_logger_delete
        };

    unsafe 
    {
        register_device(&dev_init);
    }
}
