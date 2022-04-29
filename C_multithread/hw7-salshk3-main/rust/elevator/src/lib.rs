use std::os::raw::c_char;
use std::ffi::CString;
use lazy_static::lazy_static;
use std::sync::{Mutex};

mod constants;
use constants::*;

struct Elevator {
    at: i32,
    direction: i32,
}

extern "C" {
    fn log_msg(level: i32, msg: *const c_char);
}

lazy_static!{
    static ref ONE_AT_A_TIME: Mutex<()> = Mutex::new(());
    static ref ELEVATOR: Mutex<Elevator> = Mutex::new(Elevator{at: 0, direction: 1});
}

pub fn log(msg: String) {
    unsafe {
        let cs = CString::new(msg).unwrap();
        log_msg(9,cs.as_ptr());
    }
}

#[no_mangle]
pub fn scheduler_init() {
//    println!("scheduler init!");
}

#[no_mangle]
pub fn passenger_request(passenger: i32, from_floor: i32, to_floor: i32, 
                         enter: fn(i32, i32), exit: fn(i32, i32)) {
    let _ticket = ONE_AT_A_TIME.lock();
    
    loop {
        let el=ELEVATOR.lock().unwrap();
        if (*el).at == from_floor { 
            enter(passenger, 0);
            break;
        }
    }
    
    loop {
        let el=ELEVATOR.lock().unwrap();
        if (*el).at == to_floor {        
            exit(passenger, 0);
            break;
        }
    }
}

#[no_mangle]
pub fn elevator_ready(elevator_no: i32, at_floor: i32, 
                      move_direction: fn(i32, i32), 
                      door_open: fn(i32), door_close: fn(i32)) {
    if elevator_no == 0 {
        
        {
            let mut el = ELEVATOR.lock().unwrap();
            match at_floor {
                floor if floor == FLOORS-1 => {(*el).direction = -1;}
                0 => {(*el).direction = 1;}
                _ => {}
            }
            move_direction(0,(*el).direction);
            (*el).at += (*el).direction;
            door_open(0);        
        }
        std::thread::sleep(std::time::Duration::from_micros(1));
        {
            let _el = ELEVATOR.lock().unwrap();
            door_close(0);
        }
    }
}
