/*
 * -------------------------------------------------------------------
 * EmonESP Serial to Emoncms gateway
 * -------------------------------------------------------------------
 * Adaptation of Chris Howells OpenEVSE ESP Wifi
 * by Trystan Lea, Glyn Hudson, OpenEnergyMonitor
 * All adaptation GNU General Public License as below.
 *
 * -------------------------------------------------------------------
 *
 * This file is part of OpenEnergyMonitor.org project.
 * EmonESP is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * EmonESP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with EmonESP; see the file COPYING.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "emonesp.h"
#include "input.h"

String input_string="";
String last_datastr="";

boolean input_get(JsonDocument &data)
{
  boolean gotData = false;
  String line;

  // If data from test API e.g `http://<IP-ADDRESS>/input?string=CT1:3935,CT2:325,T1:12.5,T2:16.9,T3:11.2,T4:34.7`
  if(input_string.length() > 0) {
    line = input_string;
    input_string = "";
    gotData = true;
  }
  // If data received on serial
  else if (Serial.available()) {
    // Could check for string integrity here
    line = Serial.readStringUntil('\n');
    gotData = true;
  }

  if(gotData)
  {
    // Get rid of any whitespace, newlines etc
    line.trim();

    if(line.length() > 0) {
      DEBUG.printf("Got '%s'\n", line.c_str());
      last_datastr = line;
    } else {
      gotData = false;
    }
  }

  return gotData;
}
