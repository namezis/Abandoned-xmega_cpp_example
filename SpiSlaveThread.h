/* This file has been prepared for Doxygen automatic documentation generation.*/
/*
 * Copyright (C) 2012 Yuriy Kulikov
 *      Universitaet Erlangen-Nuernberg
 *      LS Informationstechnik (Kommunikationselektronik)
 *      Support email: Yuriy.Kulikov.87@googlemail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Framework
#include "Serial.h"
#include "Spi.h"
#include "Thread.h"

/** Example thread for Spi Slave driver */
class SpiSlaveThread: public Thread {
private:
    /** Pointer to SpiSlave to use */
    SpiSlave * spiSlave;
    /** Pointer to USART buffer to use */
    Serial * serial;
public:
    SpiSlaveThread(SpiSlave * spiSlave, Serial * serial, const char *name, unsigned short stackDepth, char priority);
    void run();
};

