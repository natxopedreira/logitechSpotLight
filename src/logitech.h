

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ofMain.h"
#include "hidapi/hidapi.h"
#include <typeinfo>
#include <errno.h>
#define MAX_STR 255
#define SPOTHLIGHT 50494

#define BOTON 1
#define DERECHA 79
#define IZQUIERDA 80

class logitech
{
private:
    hid_device *handle_teclas = nullptr;
    hid_device *handle_boton = nullptr;
    hid_device *vibration_boton = nullptr;
    unsigned char buf_teclas[4];
    unsigned char buf_boton[4];
    wchar_t wstr[MAX_STR];
    int res;
    struct hid_device_info *devs, *cur_dev;

    char path_flechas[100];
    char path_boton[100];

    // debounce
    long last_button_call;
public:

    ofEvent<int> onRemoteData;

    ~logitech()
    {
        hid_close(handle_teclas);
        hid_close(handle_boton);
        hid_exit();
        handle_teclas = NULL;
        delete handle_teclas;

        handle_boton = NULL;
        delete handle_boton;

        devs = NULL;
        delete devs;

        cur_dev = NULL;
        delete cur_dev;
    }

    void setup(){
        // disable mouse
        ofSystem("xinput --disable  'Logitech USB Receiver Mouse'");

        // disable keys
        ofSystem("xinput --disable  'Logitech USB Receiver'");

        // init
        res = hid_init();

        last_button_call = ofGetElapsedTimeMillis();

        devs = hid_enumerate(0x0, 0x0);
        cur_dev = devs;

        while (cur_dev) {
            /*
            printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
            printf("\n");
            printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
            printf("  Product:      %ls\n", cur_dev->product_string);
            printf("  Release:      %hx\n", cur_dev->release_number);
            printf("  Interface:    %d\n",  cur_dev->interface_number);
            printf("  Usage (page): 0x%hx (0x%hx)\n", cur_dev->usage, cur_dev->usage_page);
            printf("\n");
            */

           
                        
            if(cur_dev->product_id == SPOTHLIGHT){

                if(cur_dev->interface_number == 0){
                    handle_teclas = hid_open_path(cur_dev->path);
                    hid_set_nonblocking(handle_teclas, 1);
                }

                if(cur_dev->interface_number == 1){
                    // teclas avanzar retroceder
                    handle_boton = hid_open_path(cur_dev->path);
                    hid_set_nonblocking(handle_boton, 1);
                }
                if(cur_dev->interface_number == 2){
                    // teclas avanzar retroceder
                    vibration_boton = hid_open_path(cur_dev->path);
                    hid_set_nonblocking(vibration_boton, 1);
                }
            }

            cur_dev = cur_dev->next;
        }
        hid_free_enumeration(devs);

        if(handle_teclas && handle_boton){
           ofLog(OF_LOG_NOTICE, "spotlight esta OK ");
        }else{
            ofLog(OF_LOG_ERROR, "ERROR accediendo a spotlight");
            ofExit();
        }

    }

    void update(){
        
        hid_read(handle_boton, buf_boton, 4);
        hid_read(handle_teclas, buf_teclas, 4);

        int tecla_pressed;

        if(buf_boton[1]==BOTON && ofGetElapsedTimeMillis()-last_button_call>200){
            //cout << "BOTON" << endl;
            last_button_call = ofGetElapsedTimeMillis();
            tecla_pressed = OF_KEY_INSERT;
            ofNotifyEvent(onRemoteData, tecla_pressed);
        }
        if(buf_teclas[2]==DERECHA && ofGetElapsedTimeMillis()-last_button_call>200){
            //cout << "BOTON DERECHA" << endl;
            last_button_call = ofGetElapsedTimeMillis();
            tecla_pressed = OF_KEY_RIGHT;
            ofNotifyEvent(onRemoteData, tecla_pressed);
        }
        if(buf_teclas[2]==IZQUIERDA && ofGetElapsedTimeMillis()-last_button_call>200){
            //cout << "BOTON IZQUIERDA" << endl;
            last_button_call = ofGetElapsedTimeMillis();
            tecla_pressed = OF_KEY_LEFT;
            ofNotifyEvent(onRemoteData, tecla_pressed);
        }

    }

    void vibrate( int _vlen,  int _vint){
        const uint8_t vlen = _vlen; // 0 y 10
        const uint8_t vint = _vint; // 25 y 255

        // unsigned char vibrate[] = {0x10, 0x01, 0x09, 0x1a, 0x00, 0xe8, 0x80};
        const uint8_t vibrateCmd[] = {0x10, 0x01, 0x09, 0x1a, vlen, 0xe8, vint};

        
        res = hid_write(vibration_boton, vibrateCmd, sizeof(vibrateCmd));
        //cout << "vibbbra" << errno << " :: "<<res << endl;
    }

};


